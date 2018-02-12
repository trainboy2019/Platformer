//
//  main.cpp
//  jsonTest
//
//  Created by Ike Rolader Air on 2/9/18.
//  Copyright © 2018 Ike Rolader. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "json/json.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<vector<int>> allPos;
    std::ifstream ifs("/Users/Ike1/Desktop/3DSBREWMAKER/Platformer/Test/jsonTest/jsonTest/level1.json");
    Json::Reader reader;
    Json::Value obj;
    if (ifs.is_open()) {
        ifs >> obj;
    }
    reader.parse(ifs, obj);
    const Json::Value rows = obj[0];
    for (int index=0;index<rows.size();++index)
        for (int index2=0;index2<rows[index].size();index2++)
            for (int index3=0;index3<rows[index][index2].size();index3++){
                string data=rows[index][index2][index3].get(to_string(index3),-1).asString();
                stringstream convert(data);
                int kind;
                convert >> kind;
                vector<int> pos;
                pos.push_back(index3*8);
                pos.push_back(index*8);
                pos.push_back(index3*8+8);
                pos.push_back(index*8+8);
                pos.push_back(kind);
                allPos.push_back(pos);
            }
    for (int i=0;i<allPos.size();i++){
        for (int j=0; j<allPos[i].size(); j++) {
            cout<<allPos[i][4]<<"\n";
        }
    }
    
    std::ifstream bifs("/Users/Ike1/Desktop/3DSBREWMAKER/Platformer/Test/jsonTest/jsonTest/level1blocks.json");
    Json::Reader breader;
    Json::Value bobj;
    if (bifs.is_open()) {
        bifs >> bobj;
    }
    breader.parse(bifs, bobj);
    for (int bindex=0;bindex<bobj.size();bindex++){
        cout<<bobj[to_string(bindex)]["color"]["r"];
    }
    
    
    return 0;
}
