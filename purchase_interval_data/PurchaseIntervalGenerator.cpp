//
//  PurchaseIntervalGenerator.cpp
//  purchase_interval_data
//
//  Created by Eagle on 13-7-13.
//  Copyright (c) 2013年 Eagle. All rights reserved.
//

#include "PurchaseIntervalGenerator.h"
#include "../common/constants.h"
#include "../common/util.h"
#include <string>
#include <map>
#include <utility>

using namespace std;

PurchaseIntervalGenerator::PurchaseIntervalGenerator(string file){
    productResult = new multimap<int, multimap<int, pair<int, int>>>;
    categoryResult = new multimap<int, multimap<int, pair<int, int>>>;
    inputFile = file;
    productResultFile = inputFile + "-interval-product";
    categoryResultFile = inputFile + "-interval-category";
    userDictFile = inputFile + "-interval-ud";
    productDictFile = inputFile + "-interval-pd";
    categoryResultFile = inputFile + "-interval-cd";
}

PurchaseIntervalGenerator::~PurchaseIntervalGenerator(){
    if (productResult) {
        delete productResult;
    }
    if (categoryResult) {
        delete categoryResult;
    }
}

void PurchaseIntervalGenerator::generateProductInterval(){
    
}

void PurchaseIntervalGenerator::generateCategoryInterval(){
    
}

void PurchaseIntervalGenerator::generateInterval(){
    
}
