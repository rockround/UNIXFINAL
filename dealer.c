#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(int argc,char **argv ){
 int i;
 int trials = 0;
 int option = 0;
 int verbose =0;
 int successes = 0;
 int pype[2];
 int log = 0;
 char *path;
 int paasento=-1;
 char *percent;
 while((option=getopt(argc,argv,"v::p:h::t:o:"))!=-1){
  switch(option){
   case 'v':
    verbose =1;
    break;
   case 'p':
   paasento = atoi(optarg);
   if(paasento>100){
	fprintf(stderr,"Invalid input for percent, number must be an integer between 0 and 100\n");
	return 1;
   }else{
    percent = optarg;
    }
    break;
   case 'h':
    printf("Use -v for verbose output, -p followed by an integer (0-100) percent probability. End output with the number of trials desired, and optionally -t for from 1-8 concurrent processes.\n");
    return 1;
   case 'o':
    path = optarg;
    log = 1;
    break;
   case '?':
     fprintf(stderr,"Invalid input, see -h for help on syntax\n");
     return 1;
    }
  }
  if(paasento == -1){
	fprintf(stderr,"Please include the percent parameter after -p as an integer between 0 and 100\n");
	return 1;
}
  if(optind<argc){
     trials = atoi(argv[optind]);
     if(trials==0){
       fprintf(stderr,"Invalid input: Enter a valid integer for the number of trials, greater than 0 at the end\n");
       return 1;
     }
   }else{
    fprintf(stderr,"Invalid input: You must enter the number of trials greater than 0 at the end of your argument\n");
    return 1;
   }
 printf("\n");
   int fd=0;
   if(log==1)
   	fd = open(path,O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
 for(i=0;i<trials;i++){
 if(pipe(pype)==-1){
   fprintf(stderr,"Bad Pipe\n");
   return 1;
 }
  int peyed = fork();
  if(peyed==0){
   close(pype[0]);
   dup2(pype[1],1);
   execlp("./Hand","Hand","-p",percent,NULL);
  }
   close(pype[1]);
   char reading_buf[20];
   char msg[400];
   while(read(pype[0],reading_buf,20)>0)
   {
	sprintf(msg,"PID %d returned %s.\n",peyed,reading_buf);
   	if(strcmp(reading_buf,"Success")==0)
		successes++;
   	if(verbose==1){
		printf(msg);
		}
	if(log==1){
		write(fd,msg,strlen(msg));
		}
   }
   close(pype[0]);
   wait();
   }
   if(log==1){
   	printf("Results were printed in %s\n",path);
   	close(fd);
	}
   float rate = (float)successes/trials*100;
  printf("\nCreated %d trials.\nSuccess - %.2f\%\nFailure - %.2f\%\n",trials,rate,100-rate);
 return 0;

}
