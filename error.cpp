//
//  errors.cpp
//  Complier
//
//  Created by 张炙炀 on 7/23/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#include <iostream>
#include "complier_header.h"
using namespace std;

void error_message(Error error){
    switch(error.error_code){
        case 1:
            cout<<"character can't be identified: line:"<<error.line<<" column:"<<error.column<<'\n';
    }
}
