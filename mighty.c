#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char **argv ){
 int pype[2];
 char *ipath;
 char *opath;
 argv[1] = ipath;
 argv[2] = opath;
   int fdo;
 if(pipe(pype)==-1){
   perror("Bad Pipe\n");
   return 1;
 }
  int peyed = fork();
  if(peyed==0){
   close(pype[0]);
   dup2(pype[1],1);
   execlp("/bin/cat","cat","-b",ipath,NULL);
  }
   close(pype[1]);
   fdo = open(opath,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP);
   char reading_buf[1000];
   while(read(pype[0],reading_buf,1000)>0)
   {
		write(fdo,reading_buf,strlen(reading_buf));
   }
   close(pype[0]); 
   close(fdo);
 return 0;

}
