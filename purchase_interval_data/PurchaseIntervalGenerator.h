//
//  PurchaseIntervalGenerator.h
//  purchase_interval_data
//
//  Created by Eagle on 13-7-13.
//  Copyright (c) 2013年 Eagle. All rights reserved.
//

#ifndef purchase_interval_data_PurchaseIntervalGenerator_h
#define purchase_interval_data_PurchaseIntervalGenerator_h

#include <string>
#include <map>
#include <utility>
#include <set>

using namespace std;

struct productPurchaseTime{
    string productid;
    long time;
};

struct categoryPurchaseTime{
    string categoryid;
    long time;
};

struct timeInfo{
    string times;
    int count;
    double avg;
};

class PurchaseIntervalGenerator{
private:
    multimap<int, map< int, multimap<int, int> > > * productPersonalIntervalResult;//the result of personal-product-interval in form of{user1:{item1:{item2:time}}}
    multimap<int, map<int, multimap<int, int> > > * categoryPersonalIntervalResult;//the result of personal-category-interval in form of{user1:{item1:{item2:time}}}
    
    map<int, multimap<int,string> > * productIntervalResult;//the result of product-interval in form of{item1:{item2:time}}
    
    map<int,map<int,int> > * productTransResult;//the result of product-transfer in form of{item1:{item2:count}}
    map<int,map<int,int> > * categoryTransResult;//the result of category-transfer in form of{item1:{item2:count}}
    
    string inputFileName;//the data-file name
    string productPersonalIntervalResultFileName;//the file contains the results of personal-product-interval reperesented by index(user-index and product-index),the file is in the form of [user source-product target-product {time1,time2,...} total-number average-interval]
    string categoryPersonalIntervalResultFileName;//the file contains the results of personal-category-interval reperesented by index(user-index and category-index),the file is in the form of [user source-category target-category {time1,time2,...} total-number average-interval]
    string productIntervalResultFileName;////the file contains the results of product-interval reperesented by index(user-index and product-index),the file is in the form of [source-product target-product {time1,time2,...}]
    string productTransResultFileName;//the file contains the results of product-transfer reperesented by index(user-index and product-index),the file is in the form of [source-product target-product count]
    string categoryTransResultFileName;//the file contains the results of category-transfer reperesented by index(user-index and category-index),the file is in the form of [source-category target-category count]
    string userDictFileName;//the dictionary of user-id to user-name,the file is in the form of [id userid]
    string productDictFileName;//the dictionary of product-id to product-name,the file is in the form of [id productid]
    string categoryDictFileName;//the dictionary of category-id to category-name,the file is in the form of [id categoryid]
    
    
public:
    PurchaseIntervalGenerator(string file);//constructor
    ~PurchaseIntervalGenerator();
    
    void generatePersonalProductInterval();//generate the personal interval result of only product
    void generatePersonalCategoryInterval();//generate the personal interval result of only category
    void generatePersonalInterval();//generate the personal interval result of both product and category
    void outputPersonalProductIntervalFile();//output productPersonalIntervalResult in form of file
    void outputPersonalCategoryIntervalFile();//output categoryPersonalIntervalResult in form of file
    
    void generateProductInterval();//generate the interval result of only product without personal,it depends on the result of function generatePersonalProductInterval()
    void outputProductIntervalFile();//output productIntervalResult in form of file
    
    void generateProductTrans();//generate the transaction file of products
    void outputProductTransFile();//output productTransResult in form of file
    void generateCategorTrans();//generate the transaction file of category
    void outputCategorTransFile();//output categoryTransResult in form of file
    
    set<int> getAllKeys(multimap<int, int> p);//get all unique keys of multimap
    set<int> getAllKeys(multimap<int, string> p);//get all unique keys of multimap
};

#endif
