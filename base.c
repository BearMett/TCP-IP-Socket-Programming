
	/*
	 *  filename.c
	 *  Written by SW. YOON
	 */

#include<stdio.h>
#include<>

void error_handling (char* message);


int main(int argc,char ** argv)
{
	return 0;
}


void error_handling (char* message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
