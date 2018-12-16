#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc,char **argv ){
 int i;
 int option=0;
 int percent = 0;
 char* file;
 while((option=getopt(argc,argv,"p:h::"))!=-1){
  switch(option){
   case 'p':
    percent = atoi(optarg);
    break;
   case 'h':
    perror("enter -p for the percent to be searched, and after that the path to data file\n");
    exit(1);
   default:
     fprintf(stderr,"Invalid Syntax",atoi(optarg));
     return 1;
    }
  }
  if(percent>90 || percent<10){
  perror("invalid percent entered, value must be 10 to 90 in increments of 10\n");
  exit(1);
  }
 if(optind<argc){
     file = argv[optind];
     FILE *fp = fopen(file,"rb");
     if(fp == NULL){
     	perror("Bad file provided\n");
	exit(1);
	}else{
	char dat[1000];
	int line = (percent-10)*100;
	fseek(fp,line,SEEK_SET);
	fread(dat,1,1000,fp);
	int i;
	int count=0;
	printf("Reading results from %s\n\n",file);
	for(i=0;i<1000;i++){
	if(dat[i]=='S')
	count++;
	}
	double result = (double)count/10;
	printf("Checking results for -p = %d ...\n\nFound 1000 trials.\n\nSuccess - %.1f%%\n\nFailure - %.1f%%\n",percent,result,100-result);
	}
 }else{
 	perror("You must append a valid path to the source file at the end!\n");
	exit(1);
}
	
 exit(0);
}
