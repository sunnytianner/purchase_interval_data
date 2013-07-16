//
//  PurchaseIntervalGenerator.cpp
//  purchase_interval_data
//
//  Created by Eagle on 13-7-13.
//  Copyright (c) 2013年 Eagle. All rights reserved.
//

#include "PurchaseIntervalGenerator.h"
//#include "../common/constants.h"
//#include "../common/util.h"
#include "constants.h"
#include "util.h"
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

PurchaseIntervalGenerator::PurchaseIntervalGenerator(string file){
    productIntervalResult = new multimap<int, multimap<int, multimap<int, int> > >;//user{sourceproduct{targetproduct,time}}
    categoryIntervalResult = new multimap<int, multimap<int, multimap<int, int> > >;
    productTransResult = new map<int,map<int,int> >;
    categoryTransResult = new map<int,map<int,int> >;
    //definition of files
    inputFileName = file;
    cout << inputFileName << endl;
    productIntervalResultFileName = inputFileName + "-interval-product";
    categoryIntervalResultFileName = inputFileName + "-interval-category";
    productTransResultFileName = inputFileName + "-trans-product";
    categoryTransResultFileName = inputFileName + "-trans-category";
    userDictFileName = inputFileName + "-interval-ud";
    productDictFileName = inputFileName + "-interval-pd";
    categoryDictFileName = inputFileName + "-interval-cd";
}

PurchaseIntervalGenerator::~PurchaseIntervalGenerator(){
    if (productIntervalResult) {
        delete productIntervalResult;
    }
    if (categoryIntervalResult) {
        delete categoryIntervalResult;
    }
    if (productTransResult) {
        delete productTransResult;
    }
    if (categoryTransResult) {
        delete categoryTransResult;
    }
}

void PurchaseIntervalGenerator::generateProductInterval(){
    cout << "generate product-interval..." << endl;
    int user_index = 1;//current user-index
    int product_index = 1;//current product-index
    map<string,int> userDictMap;//userid-index dictionary in form of map
    map<string,int> productDictMap;//productid-index dictionary in form of map
    string current_user = "";//the current user
    vector<struct productPurchaseTime> userPurchase;//a temp vetcor for containing productPurchaseTime
    multimap<int, int> productTimeMultiMap;//a temp pair for product and time
    multimap<int, multimap<int, int> > sourceProduct;
    
    //open the files
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    
    ofstream productDictFile, userDictFile;
    productDictFile.open(productDictFileName.c_str());
    userDictFile.open(userDictFileName.c_str());
    
    
    while (!inputFile.eof()) {
        string line;
        getline(inputFile,line);
        if(line.size() == 0)
            continue;
        
        vector<string> items = Util::split(line, CONTROL_A);
        long time = atol(items[0].c_str());
        string userId = items[1];
        string productId = items[2];
        
        struct productPurchaseTime productTime;
        productTime.productid = productId;
        productTime.time = time;
        
        if (productDictMap.find(productId) == productDictMap.end()){
            productDictMap[productId] = product_index;
            product_index++;
        }
        
        if (current_user != userId) {
            current_user = userId;//reset the current-userid
            userDictMap[current_user] = user_index;
            user_index++;
            for (int i=0; i<userPurchase.size()-1; i++) {
                for (int j=i+1; j<userPurchase.size(); j++) {
                    if (userPurchase[j].time == userPurchase[i].time) {//if product i and product j are in one basket
                        continue;
                    }
                    productTimeMultiMap.insert(make_pair(productDictMap[userPurchase[j].productid], (userPurchase[j].time - userPurchase[i].time)/(24*60*60*1000)));
                    
                }
                sourceProduct.insert(make_pair(productDictMap[userPurchase[i].productid], productTimeMultiMap));
                productTimeMultiMap.clear();
            }
            productIntervalResult->insert(make_pair(userDictMap[userId], sourceProduct));
            sourceProduct.clear();
            userPurchase.clear();
        }
        else{
            userPurchase.push_back(productTime);
        }
    }
    
    //writing index files
    cout << "Writing index files..." << endl;
    map<string,int>::iterator it;
    for (it=userDictMap.begin(); it!=userDictMap.end(); it++) {
        userDictFile << it->first << " " << it->second << endl;
    }
    for (it=productDictMap.begin(); it!=productDictMap.end(); it++) {
        productDictFile << it->first << " " << it->second << endl;
    }
    
    inputFile.close();
    productDictFile.close();
    userDictFile.close();
}

void PurchaseIntervalGenerator::generateCategoryInterval(){
    
}

void PurchaseIntervalGenerator::generateInterval(){
    
}

void PurchaseIntervalGenerator::outputProductIntervalFile(){
    cout << "Wtriting the product-interval file..." << endl;
    ofstream productIntervalResultFile;
    productIntervalResultFile.open(productIntervalResultFileName.c_str());
    int coCount;//the times a pair-product oc-appearance
    double totalDate;//the sum of date of each pair-product
    string times;//times of pair-product(t1,t2,t3...)
    
    multimap<int, multimap<int, multimap<int, int> > >::iterator user,userEnd;
    userEnd = productIntervalResult->end();//calculate once
    for (user=productIntervalResult->begin(); user!=userEnd; user++) {//for each user
        multimap<int, multimap<int, int> >::iterator sProduct, sProductEnd;
        sProductEnd = user->second.end();
        for (sProduct=user->second.begin(); sProduct!=sProductEnd; sProduct++) {//for each source-product
            set<int> keys = getAllKeys(sProduct->second);
            set<int>::iterator key;
            for (key=keys.begin(); key!=keys.end(); key++) {
                multimap<int, int>::size_type entries = sProduct->second.count(*key);
                multimap<int, int>::iterator tProduct = sProduct->second.find(*key);
                coCount=0;
                totalDate=0;
                times="";
                for (multimap<int, int>::size_type cnt = 0; cnt != entries; ++cnt,++coCount) {
                    int date;
                    date = tProduct->second;
                    totalDate += date;
                    times += Util::itos(date)+",";
                }
                times = times.substr(0,times.length()-1);
                productIntervalResultFile << user->first << " " << sProduct->first << " " << times << " " << coCount << " " << totalDate/coCount << endl;
            }
        }
    }
    
    productIntervalResultFile.close();
}

void PurchaseIntervalGenerator::outputCategoryIntervalFile(){

}

set<int> PurchaseIntervalGenerator::getAllKeys(multimap<int, int> p){
    multimap<int, int>::iterator tProduct;
    set<int> keys;
    for (tProduct = p.begin(); tProduct != p.end(); tProduct++) {
        keys.insert(tProduct->first);
    }
    return keys;
}

void PurchaseIntervalGenerator::generateProductTrans(){
    cout << "generate product-transfer..." << endl;
    int user_index = 1;//current user-index
    int product_index = 1;//current product-index
    map<string,int> userDictMap;//userid-index dictionary in form of map
    map<string,int> productDictMap;//productid-index dictionary in form of map
    string current_user = "";//the current user
    vector<int> userPurchase;//a temp vetcor for containing products purchased by a user
    map<int,int> tProduct;
    
    //open the files
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    
    ofstream productDictFile, userDictFile;
    productDictFile.open(productDictFileName.c_str());
    userDictFile.open(userDictFileName.c_str());
    
    while (!inputFile.eof()) {
        string line;
        getline(inputFile,line);
        if(line.size() == 0)
            continue;
        
        vector<string> items = Util::split(line, CONTROL_A);
        string userId = items[1];
        string productId = items[2];
        
        if (productDictMap.find(productId) == productDictMap.end()){
            productDictMap[productId] = product_index;
            product_index++;
        }
        
        if (current_user != userId) {
            cout << userId << endl;
            current_user = userId;//reset the current-userid
            userDictMap[current_user] = user_index;
            user_index++;
            for (vector<int>::iterator i=userPurchase.begin(); i!=userPurchase.end(); i++) {
                int sourceProduct = *i;
                for (vector<int>::iterator j=i+1; j!=userPurchase.end(); j++) {
                    int targetProduct = *j;
                    if (productTransResult->find(sourceProduct) == productTransResult->end()) {//if no source-product
                        tProduct[targetProduct] = 1;
                        (*productTransResult)[sourceProduct] = tProduct;
                        tProduct.clear();
                    }
                    else{
                        if ((*productTransResult)[sourceProduct].find(targetProduct) != (*productTransResult)[sourceProduct].end()) {
                            (*productTransResult)[sourceProduct][targetProduct] += 1;
                        }
                        else{
                            (*productTransResult)[sourceProduct][targetProduct] = 1;
                        }
                    }
                }
            }
            userPurchase.clear();
        }
        else{
            userPurchase.push_back(productDictMap[productId]);
        }
    }

    //writing index files
    cout << "Writing index files..." << endl;
    map<string,int>::iterator it;
    for (it=userDictMap.begin(); it!=userDictMap.end(); it++) {
        userDictFile << it->first << " " << it->second << endl;
    }
    for (it=productDictMap.begin(); it!=productDictMap.end(); it++) {
        productDictFile << it->first << " " << it->second << endl;
    }
    
    inputFile.close();
    productDictFile.close();
    userDictFile.close();
   
}

void PurchaseIntervalGenerator::outputProductTransFile(){
    cout << "Wtriting the product-transfer file..." << endl;
    ofstream productTransResultFile;
    productTransResultFile.open(productTransResultFileName.c_str());
    
    map<int, map<int, int> >::iterator source,sourceEnd;
    sourceEnd = productTransResult->end();//calculate once
    for (source=productTransResult->begin(); source!=sourceEnd; source++) {
        map<int,int> target = source->second;
        map<int,int>::iterator it,itEnd;
        itEnd = target.end();
        double sum = 0;
        for (it=target.begin(); it!=itEnd; it++) {
            sum += it->second;
        }
        for (it=target.begin(); it!=itEnd; it++) {
            productTransResultFile << source->first << " " << it->first << " " << (it->second) / sum << endl;
        }
    }
    
    productTransResultFile.close();
}