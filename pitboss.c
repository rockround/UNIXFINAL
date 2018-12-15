#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc,char **argv ){
 int i;
 int option=0;
 int percent = 0;
 char* file;
 while((option=getopt(argc,argv,"p:"))!=-1){
  switch(option){
   case 'p':
    percent = atoi(optarg);
    break;
   default:
     fprintf(stderr,"Invalid Syntax",atoi(optarg));
     return 1;
    }
  }
 if(optind<argc){
     file = argv[optind];
 }else{
 	fprintf(stderr,"You must append a valid path to the source file at the end!\n");
	exit(1);
}
	
 exit(0);
}
