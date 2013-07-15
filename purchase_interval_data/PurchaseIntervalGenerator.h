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

using namespace std;

class PurchaseIntervalGenerator{
private:
    multimap<int, multimap<int, pair<int, int>>> * productResult;//the result of product-interval in form of{user1:{item1:{item2:time}}}
    multimap<int, multimap<int, pair<int, int>>> * categoryResult;//the result of product-interval in form of{user1:{item1:{item2:time}}}
    string inputFile;//the data-file name
    string productResultFile;//the file contains the results of product-interval reperesented by index(user-index and product-index),the file is in the form of [user source-product target-product {time1,time2,...} total-number average-interval]
    string categoryResultFile;//the file contains the results of category-interval reperesented by index(user-index and category-index),the file is in the form of [user source-category target-category {time1,time2,...} total-number average-interval]
    string userDictFile;//the dictionary of user-id to user-name,the file is in the form of [id userid]
    string productDictFile;//the dictionary of product-id to product-name,the file is in the form of [id productid]
    string categoryDictFile;//the dictionary of category-id to category-name,the file is in the form of [id categoryid]
public:
    PurchaseIntervalGenerator(string file);//constructor
    ~PurchaseIntervalGenerator();
    void generateProductInterval();//generate the interval result of only product
    void generateCategoryInterval();//generate the interval result of only category
    void generateInterval();//generate the interval result of both product and category
};

#endif
