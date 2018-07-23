//
//  scanner.cpp
//  Complier
//
//  Created by 张炙炀 on 7/23/18.
//  Copyright © 2018 张炙炀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define buffer_size 80

char *buffer = (char*)malloc(buffer_size);
int buff_index = -2,line = 1,column = 0;
long buff_read_size = 0;
char cur_ch = 'a';
void scan(FILE *source){
    if(buffer[buff_index] == '\n'){
        line++;
        column = 0;
    }
    if(buff_index + 1 == buffer_size || buff_index == -2){
        buff_read_size = fread(buffer, 1, buffer_size, source);
        if(buff_read_size != buffer_size){
            buffer[buff_read_size] = EOF;
            fclose(source);
        }
        buff_index = -1;
    }
    buff_index++;
    column++;
    cur_ch = buffer[buff_index];
}
