//
//  main.cpp
//  purchase_interval_data
//
//  Created by Eagle on 13-7-13.
//  Copyright (c) 2013年 Eagle. All rights reserved.
//

#include <iostream>
#include "PurchaseIntervalGenerator.h"

using namespace std;

int main(int argc, const char * argv[])
{
    PurchaseIntervalGenerator purchaseInterval("/Users/tian19880220/workspace/data/purchase_interval_data/purchase-40-55-1year-uniq-top7.5w-sort");
    //purchaseInterval.generatePersonalProductInterval();
    //purchaseInterval.outputPersonalProductIntervalFile();
    //purchaseInterval.generateProductTrans();
    //purchaseInterval.outputProductTransFile();
    purchaseInterval.generateProductInterval();
    purchaseInterval.outputProductIntervalFile();
}

