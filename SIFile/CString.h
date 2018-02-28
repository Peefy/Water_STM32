#ifndef _C_STRING_H_
#define _C_STRING_H_

#include "stdio.h"
#include "stdbool.h"

/**
  ******************************************************************************
  * @file    CString.c
  * @author  DuGu
  * @version V1.0.2
  * @date    08/06/2016
  * @brief   Some Function
  ******************************************************************************
**/

char * CStringCopy(char *destination , char * source);//

char *CStringConnact(char *target,char * source);//

int CStringLetterFirstIndexOf( char*string, char letter);
int CStringLetterLastIndexOf(char *string,char letter);

char *CStringAfterLetterFisrt(char *string, char letter);
char *CStringAfterLetterLast( char *string, char letter);

int CStringLetterCount(const char *string,char letter);

bool CStringContainsLetter( char *string,char letter);
bool CStringContainsSubString(char *s1,char *s2);

char * CStringSubString( char *s1, char *s2);
char *CStringReserse(char *string);//
int CStringCompare(const char *s1, const char *s2);
unsigned int CStringFirstOneLetterNotInSecondIndexOf(const char *s1, const char *s2);
char * CStringRemoveSubString(char *string, char *substring);//
int CStringLenth(char * string);
char *CStringReplaceSubString(char *source, char *old , char *news);//

#endif
