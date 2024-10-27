#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void case1();
void case2();
void case3();
void case4();
void case5();
void case6();
void case7();
void case8();
void case9();
void case10();
void case11();
void case12();
void case13();
void case14();
void case15();
void case16();
void case17();
void clearInputBuffer();
void exportFileToText();
void exportFileToBinary();
void importFromTextFile(const char* filename);
void importFromBinaryFile(const char* filename);
void generalArrayFunction(void* array, int numElements, size_t elementSize, void (*f)(const void* element));
void printHotelElement(const void* element);


#endif //__FUNCTIONS_H_
