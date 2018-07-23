//
//  complier.cpp
//  Complier
//
//  Created by 张炙炀 on 7/23/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#include <iostream>
#include "complier_header.h"
using namespace std;

int main(int argc, const char * argv[]){
    //Read file which will be complied
    FILE *source;
    source = fopen(argv[1],"r");
    if(source == NULL){
        cout<<"Read file error!"<<"\n";
        return -1;
        }
    //lexical process
    Token token(KW_EXTERN,0,0);
    while(token.tag != END){
        token = get_token(source);
        cout<<token.tag<<'\n';
    }
}
