#include<stdio.h>
#include<string.h>

void main(){
	FILE* fptr;
	FILE* ftpw;
	
	char data[50];
	fptr = fopen("file.c","r");
	
	if (fptr == NULL){
		printf("file has no contents or failed to open");
	}
	else
	{
		fptw = fopen("removed.c","w");
			
	
