#pragma once
#include "strmanip.h"
#include <string.h>
#include <stdio.h>

bool SubString(char *string, char *s_string) {
	if(string==NULL || s_string==NULL)
		return false;

	char *p, *s, *temp;

	p = string;
	s = s_string;

	do {
		while(*p==*s && *p!='\0') {
			s++;
			p++;
			if(*s=='\0') {
				return true;
			}
		}
		s = s_string;
	} while(*(p++)!='\0');
	return false;
}

char** SplitString(char *string, int *nWords, char* delim=" \t") {
	if(string==NULL) {
		*nWords = -1;
		return NULL;
	}

	int len = strlen(string);
	int count = 0;
	char* lpCopy;
	char* p;
	char** words;
	char* next;

	p = string;

	while((*p==' ' || *p=='\t') && *(p++)!=0);

	if(*p==0)
		return NULL;

	words = new char*[1024];

	words[count++] = strtok_s(p, delim, &next);

	while(words[count++] = strtok_s(NULL, delim, &next));

	*nWords = count;

	return words;
}

//char** SplitString(char *string, int *nWords) {
//	if(string==NULL) {
//		*nWords = -1;
//		return NULL;
//	}
//
//	int len = strlen(string);
//	int count = 0;
//
//	char** words;
//	char* backup;
//	char* lpCopy = new char[len+1];
//
//	strncpy_s(lpCopy, len+1, string, len+1);
//
//	while((*lpCopy==' ' || *lpCopy=='\t') && *(lpCopy++)!=0);
//		//printf("Beginning whitespace found\n");
//
//	for(int i=0; i<len; i++) {
//		if((lpCopy[i]==' ' || lpCopy[i]=='\t') && i!=len-1)
//		{
//			while(lpCopy[i]==' ' && i<len-1)
//				i++;
//			count++;
//		}
//	}
//
//	count++;
//	*nWords = count;
//
//	words = new char*[count];
//	words[0] = lpCopy;
//	for(int i=0, j=0; i<len; i++){
//		if(lpCopy[i]==' ' || lpCopy[i]=='\t' || lpCopy[i]=='\0') {
//			lpCopy[i] = '\0';
//			j++;
//			i++;
//			while(lpCopy[i]==' ' || lpCopy[i]=='\t')
//				i++;
//			if(i+1<=len)
//				words[j] = lpCopy + i;
//		}
//	}
//	
//	return words;
//}