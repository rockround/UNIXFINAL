#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char **argv ){
 int pype[2];
 char *ipath;
 char *opath;
 if(argc!=3){
	perror("Insufficient arguments. Enter the source file name, followed by the target.");
	exit(1);
 }
 ipath= argv[1];
 opath= argv[2];
   int fdo;
 if(pipe(pype)==-1){
   perror("Bad Pipe\n");
   return 1;
 }
  int peyed = fork();
  if(peyed==0){
   close(pype[0]);
   dup2(pype[1],1);
   if(access(ipath,R_OK)==-1){
	perror("Check to make sure that your input file exists, and that you have read permissions for it");
	exit(1);
   }
   execl("/bin/cat","cat","-b",ipath,NULL);
  }
   close(pype[1]);
   fdo = open(opath,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP);
   char reading_buf[1];
   while(read(pype[0],reading_buf,1)>0)
   {
		write(fdo,reading_buf,1);
		printf(reading_buf);
   }
   close(pype[0]); 
   close(fdo);
 return 0;

}
