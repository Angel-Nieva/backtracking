#ifndef ARRAY_H
#define ARRAY_H
#include "../incl/array.h"

int * openFile(const char * filename,int *col,int *fil);
void writeFile(int *ciudad,int col,const char*filename,int fil);
char * ciudadToString(int *ciudad,int col,int fil);

#endif