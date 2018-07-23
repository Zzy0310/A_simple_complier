//
//  complier_header.h
//  Complier
//
//  Created by 张炙炀 on 7/23/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#ifndef complier_header_h
#define complier_header_h
using namespace std;

enum Tag{
    ID,NUM,CH,STR,
    KW_EXTERN,
    KW_INT,KW_CHAR,KW_VOID,
    KW_IF,KW_ELSE,KW_SWITCH,KW_CASE,KW_WHILE,KW_DO,KW_FOR,KW_BREAK,KW_CONTINUE,
    KW_RETURN,
    KW_DEFAULT,
    LEA,
    NOT,AND,OR,EQU,NEQU,
    ADD,SUB,MUL,DIV,MOD,INC,DEC,
    ASSIGN,GT,GE,LT,LE,
    COMMA,COLON,SEMICON,LPAREN,RPAREN,LBRACK,RBRACK,LBRAC,RBRAC,
    ERROR,END
};

class Token{
public:
    Tag tag;
    int line,column;
    Token(Tag a,int b,int c){tag = a;line = b;column = c;}
    Token(){}
};

class Id:public Token{
public:
    string name;
    Id(string a,int b,int c){tag = ID;name = a;line = b;column = c;}
};

class Num:public Token{
public:
    int val;
    Num(int a,int b,int c){tag = NUM;val = a;line = b;column = c;}
};

class Char:public Token{
public:
    char val;
    Char(char a,int b,int c){tag = CH;val = a;line = b;column = c;}
};

class String:public Token{
public:
    string val;
    String(string a,int b,int c){tag = STR;val = a;line = b;column = c;}
};

class Error:public Token{
public:
    int error_code;
    Error(int a,int b,int c){tag = ERROR;error_code = a;line = b;column = c;}
};

void scan(FILE *source);
Token get_token(FILE *source);
void get_token_init();

void error_message(Error error);



#endif /* complier_header_h */
