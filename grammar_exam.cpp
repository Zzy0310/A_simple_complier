//
//  garmmar_exam.cpp
//  Complier
//
//  Created by 张炙炀 on 7/26/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "complier_header.h"
using namespace std;
extern FILE *source;
extern int line,column;

int first_token = 1;
Token cur_token,next_token;

void read(){
    cur_token = next_token;
    next_token = get_token(source);
}

void program(){
    if(first_token == 1){
        read();
        first_token = 0;
    }
    switch(next_token.tag){
        case END:
            cout<<"No problem in garmmar!";
            break;
        case KW_INT:
        case KW_CHAR:
        case KW_VOID:
        case KW_EXTERN:
            segment();
            program();
            break;
        default:
            Error error(2,line,column-1);
            error_message(error);
    }
}

void segment(){
    switch(next_token.tag){
        case KW_EXTERN:
            read();
            type();
            def();
            break;
        case KW_INT:
        case KW_CHAR:
        case KW_VOID:
            type();
            def();
            break;
        default:
            Error error(2,line,column-1);
            error_message(error);
    }
}

void type(){
    read();
    if(cur_token.tag != KW_INT&&cur_token.tag != KW_CHAR&&cur_token.tag != KW_VOID){
        Error error(3,line,column-1);
        error_message(error);
    }
}

void def(){
    switch(next_token.tag){
        case ID:
            read();
            idtail();
            break;
        case MUL:
            read();
            if(next_token.tag == ID){
                read();
                init();
                deflist();
            }
            else{
                Error error(4,line,column-1);
                error_message(error);
            }
            break;
        default:
            Error error(4,line,column-1);
            error_message(error);
    }
}

void varrdef(){
    switch(next_token.tag){
        case LBRACK:
            read();
            if(next_token.tag == NUM){
                read();
            }
            else{
                Error error(5,line,column-1);
                error_message(error);
            }
            if(next_token.tag == RBRACK){
                read();
            }
            else{
                Error error(6,line,column-1);
                error_message(error);
            }
            break;
        case ASSIGN:
        case COMMA:
        case SEMICON:
            init();
            break;
        default:
            Error error(7,line,column-1);
            error_message(error);
        
    }
}

void deflist(){
    switch(next_token.tag){
        case SEMICON:
            read();
            break;
        case COMMA:
            read();
            defdata();
            deflist();
            break;
        default:
            Error error(8,line,column-1);
            error_message(error);
    }
}

void defdata(){
    switch(next_token.tag){
        case ID:
            read();
            varrdef();
            break;
        case MUL:
            read();
            if(next_token.tag == ID){
                read();
                init();
            }
            else{
                Error error(9,line,column-1);
                error_message(error);
            }
            break;
        default:
            Error error(4,line,column-1);
            error_message(error);
    }
}

void idtail(){
    switch (next_token.tag) {
        case LPAREN:
            read();
            para();
            if(next_token.tag == RPAREN){
                read();
                funtail();
            }
            else{
                Error error(11,line,column-1);
                error_message(error);
            }
            break;
        case LBRACK:
        case COMMA:
        case SEMICON:
        case ASSIGN:
            varrdef();
            deflist();
            break;
        default:
        Error error(4,line,column-1);
            error_message(error);
    }
}

void init(){
    switch (next_token.tag) {
        case ASSIGN:
            read();
            expr();
            break;
        case COMMA:
        case SEMICON:
            break;
        default:
            Error error(10,line,column-1);
            error_message(error);
    }
}
    
void para(){
    switch(next_token.tag){
        case KW_INT:
        case KW_CHAR:
        case KW_VOID:
            type();
            paradata();
            paralist();
            break;
        case RPAREN:
            break;
        default:
            Error error(12,line,column-1);
            error_message(error);
            
    }
}

void funtail(){
    switch(next_token.tag){
        case SEMICON:
            read();
            break;
        case LBRAC:
            block();
            break;
        default:
            Error error(13,line,column-1);
            error_message(error);
    }
}

void paradata(){
    switch(next_token.tag){
        case MUL:
            read();
            if(next_token.tag != ID){
                Error error(14,line,column-1);
                error_message(error);
            }
            break;
        case ID:
            read();
            paradatatail();
            break;
        default:
            Error error(4,line,column-1);
            error_message(error);
    }
}


void paralist(){
    switch(next_token.tag){
        case COMMA:
            read();
            type();
            paradata();
            paralist();
            break;
        case RPAREN:
            break;
        default:
            Error error(15,line,column-1);
            error_message(error);
    }
}

void paradatatail(){
    switch(next_token.tag){
        case LBRACK:
            read();
            if(next_token.tag == NUM){
                read();
                if(next_token.tag == RBRACK){
                    read();
                    break;
                }
                else{
                    cout<<"expect a ] )"<<line<<" column:"<<column<<'\n';
                    system("exit");
                }
            }
            else{
                cout<<"expect a NUM )"<<line<<" column:"<<column<<'\n';
                system("exit");
            }
            break;
        case COMMA:
        case RPAREN:
            break;
        default:
            cout<<"expect a [,) or , "<<line<<" column:"<<column<<'\n';
            system("exit");
    }
}

void block(){
    switch(next_token.tag){
        case LBRAC:
            read();
            subprogram();
            if(next_token.tag == RBRAC){
                read();
                break;
            }
            else{
                cout<<"expect a } "<<line<<" column:"<<column<<'\n';
                system("exit");
            }
        default:
            cout<<"expect a {"<<line<<" column:"<<column<<'\n';
            system("exit");
    }
}

void expr(){
    
}

void subprogram(){
    switch(next_token.tag){
        case KW_WHILE:
        case KW_FOR:
        case KW_DO:
        case KW_IF:
        case KW_SWITCH:
        case ID:
        case KW_BREAK:
        case KW_CONTINUE:
        case KW_RETURN:
            statment();
            subprogram();
            break;
        case KW_INT:
        case KW_CHAR:
        case KW_VOID:
            localdef();
            subprogram();
            break;
        case RBRAC:
            break;
        default:
            cout<<"expect a while,for,do,if,switch,id,break,continue,return,int,char,void,or }"<<line<<" column:"<<column<<'\n';
            system("exit");
    }
}

void localdef(){
    switch(next_token.tag){
        case KW_INT:
        case KW_CHAR:
        case KW_VOID:
            type();
            defdata();
            deflist();
            break;
        default:
            cout<<"expect a int,char or void"<<line<<" column:"<<column<<'\n';
            system("exit");
    }
}

void statment(){
    
}



