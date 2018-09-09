/*
Assignment 3 Header File
Russell Horvath
CIS*2500
*/
#include <stdio.h>
#include <stdlib.h>
#ifndef MEMCHECK_H
#define MEMCHECK_H
/* redefine functions */
#define calloc(nmemb,size) memcheck_calloc(nmemb, size , __FILE__ , __LINE__)
#define realloc(ptr,size) memcheck_realloc(ptr, size , __FILE__ , __LINE__)
#define malloc(size) memcheck_malloc(size , __FILE__ , __LINE__)
#define free(ptr) memcheck_free(ptr, __FILE__ , __LINE__)
#define main() memcheck_main()
/* function prototypes */
void *memcheck_calloc(size_t nmemb, size_t size, char *file, int line);
void *memcheck_realloc(void *ptr, size_t size, char *file, int line);
void *memcheck_malloc(size_t size, char *file, int line);
void memcheck_free(void *ptr, char *file, int line);
int memcheck_main();
#endif
