//
//  get_token.cpp
//  Complier
//
//  Created by 张炙炀 on 7/23/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <map>
#include "complier_header.h"
using namespace std;
extern char cur_ch;
extern int line,column;

int first_time = 1;
map<string,Tag>keywords;

void get_token_init(){
    keywords.insert(make_pair("extern",KW_EXTERN));
    keywords.insert(make_pair("int",KW_INT));
    keywords.insert(make_pair("char",KW_CHAR));
    keywords.insert(make_pair("void",KW_VOID));
    keywords.insert(make_pair("if",KW_IF));
    keywords.insert(make_pair("else",KW_ELSE));
    keywords.insert(make_pair("switch",KW_SWITCH));
    keywords.insert(make_pair("case",KW_CASE));
    keywords.insert(make_pair("while",KW_WHILE));
    keywords.insert(make_pair("do",KW_DO));
    keywords.insert(make_pair("for",KW_FOR));
    keywords.insert(make_pair("break",KW_BREAK));
    keywords.insert(make_pair("continue",KW_CONTINUE));
    keywords.insert(make_pair("return",KW_RETURN));
    keywords.insert(make_pair("default",KW_DEFAULT));
}

Token get_token(FILE *source){
    if(first_time == 1){
        scan(source);
        get_token_init();
        first_time = 0;
    }
    ////////////
    if(cur_ch == EOF){
        Token token(END,line,column-1);
        return token;
    }
    if(cur_ch == ' '||cur_ch == '\n'||cur_ch == '\t'){
        while(cur_ch == ' '||cur_ch == '\n'||cur_ch == '\t'){
            scan(source);
        }
    }
    if(cur_ch == '_'||(cur_ch>='A'&&cur_ch<='Z')||(cur_ch>='a'&&cur_ch<='z')){
        string str;
        str = str + cur_ch;
        while(cur_ch == '_'||(cur_ch>='A'&&cur_ch<='Z')||(cur_ch>='a'&&cur_ch<='z')||(cur_ch>='0'&&cur_ch<='9')){
            scan(source);
            str = str + cur_ch;
        }
        str.pop_back();
        if(keywords.count(str) == 1){
            Tag keyword = keywords[str];
            switch((int)keyword){
                case KW_INT:{
                    Token token(KW_INT,line,column-1);
                    return token;
                }
                case KW_CHAR:{
                    Token token(KW_CHAR,line,column-1);
                    return token;
                }
                case KW_VOID:{
                    Token token(KW_VOID,line,column-1);
                    return token;
                }
                case KW_EXTERN:{
                    Token token(KW_EXTERN,line,column-1);
                    return token;
                }
                case KW_IF:{
                    Token token(KW_IF,line,column-1);
                    return token;
                }
                case KW_ELSE:{
                    Token token(KW_ELSE,line,column-1);
                    return token;
                }
                case KW_SWITCH:{
                    Token token(KW_SWITCH,line,column-1);
                    return token;
                }
                case KW_CASE:{
                    Token token(KW_CASE,line,column-1);
                    return token;
                }
                case KW_DEFAULT:{
                    Token token(KW_DEFAULT,line,column-1);
                    return token;
                }
                case KW_WHILE:{
                    Token token(KW_WHILE,line,column-1);
                    return token;
                }
                case KW_DO:{
                    Token token(KW_DO,line,column-1);
                    return token;
                }
                case KW_FOR:{
                    Token token(KW_FOR,line,column-1);
                    return token;
                }
                case KW_BREAK:{
                    Token token(KW_BREAK,line,column-1);
                    return token;
                }
                case KW_CONTINUE:{
                    Token token(KW_CONTINUE,line,column-1);
                    return token;
                }
                case KW_RETURN:{
                    Token token(KW_RETURN,line,column-1);
                    return token;
                }
            }
        }
        else{
            Id id(str,line,column-1);
            return id;
        }
    }
    ///////////////
    if(cur_ch>='0'&&cur_ch<='9'){
        string str;
        str = str + cur_ch;
        while(cur_ch>='0'&&cur_ch<='9'){
            scan(source);
            str = str + cur_ch;
        }
        str.pop_back();
        int val = atoi(str.c_str());
        Num num(val,line,column-1);
        return num;
    }
    switch(cur_ch){
        case '+':
            scan(source);
            if(cur_ch == '+'){
                scan(source);
                Token token(INC,line,column-1);
                return token;
            }
            else{
                Token token(ADD,line,column-1);
                return token;
            }
        case '-':
            scan(source);
            if(cur_ch == '-'){
                scan(source);
                Token token(DEC,line,column-1);
                return token;
            }
            else{
                Token token(SUB,line,column-1);
                return token;
            }
        case '&':
            scan(source);
            if(cur_ch == '&'){
                scan(source);
                Token token(AND,line,column-1);
                return token;
            }
            else{
                Token token(LEA,line,column-1);
                return token;
            }
        case '|':
            scan(source);
            if(cur_ch == '|'){
                scan(source);
                Token token(OR,line,column-1);
                return token;
            }
            else{
                Token token(ERROR,line,column-1);
                return token;
            }
        case '>':
            scan(source);
            if(cur_ch == '='){
                scan(source);
                Token token(GE,line,column-1);
                return token;
            }
            else{
                Token token(GT,line,column-1);
                return token;
            }
        case '<':
            scan(source);
            if(cur_ch == '='){
                scan(source);
                Token token(LE,line,column-1);
                return token;
            }
            else{
                Token token(LT,line,column-1);
                return token;
            }
        case '=':
            scan(source);
            if(cur_ch == '='){
                scan(source);
                Token token(EQU,line,column-1);
                return token;
            }
            else{
                Token token(ASSIGN,line,column-1);
                return token;
            }
        case '!':
            scan(source);
            if(cur_ch == '='){
                scan(source);
                Token token(NEQU,line,column-1);
                return token;
            }
            else{
                Token token(NOT,line,column-1);
                return token;
            }
        case '*':{
            scan(source);
            Token token(MUL,line,column-1);
            return token;
        }
        case '/':{
            scan(source);
            Token token(DIV,line,column-1);
            return token;
        }
        case '%':{
            scan(source);
            Token token(MOD,line,column-1);
            return token;
        }
        case ',':{
            scan(source);
            Token token(COMMA,line,column-1);
            return token;
        }
        case ':':{
            scan(source);
            Token token(COLON,line,column-1);
            return token;
        }
        case ';':{
            scan(source);
            Token token(SEMICON,line,column-1);
            return token;
        }
        case '(':{
            scan(source);
            Token token(LPAREN,line,column-1);
            return token;
        }
        case ')':{
            scan(source);
            Token token(RPAREN,line,column-1);
            return token;
        }
        case '[':{
            scan(source);
            Token token(LBRACK,line,column-1);
            return token;
        }
        case ']':{
            scan(source);
            Token token(RBRACK,line,column-1);
            return token;
        }
        case '{':{
            scan(source);
            Token token(LBRAC,line,column-1);
            return token;
        }
        case '}':{
            scan(source);
            Token token(RBRAC,line,column-1);
            return token;
        }
        default:{
            scan(source);
            Error error(1,line,column-1);
            error_message(error);
            return error;
        }
    }
    

}
