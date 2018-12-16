#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <math.h>
#include <signal.h>
gsl_rng_type *_gsl_rng_type;
gsl_rng *_gsl_rng;
int initTool();
void finalizeTool();
int getRDM();
void abortChild(int sig);
void fightForLife(int sig);
struct timespec t;
int peyed;
int i;
int initTool(){
	_gsl_rng = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(_gsl_rng,(long)getpid());
	if(_gsl_rng == NULL)
		return 1;
	else
		return 0;
}

void finalizeTool(){
	gsl_rng_free(_gsl_rng);
	return;
}

int getRDM(){
	return (int)round(30*gsl_rng_uniform(_gsl_rng))+1;
}
int main(int argc,char **argv ){
  t.tv_sec=0;
  t.tv_nsec=500000000L;
  peyed = fork();
  if(peyed==0){
  for(i=1;i<32;i++)
  signal(i,fightForLife);
  while(1){
	printf("child waiting\n");
	nanosleep(&t,NULL);
  }
  }
  for(i=1;i<32;i++)
  signal(i,abortChild);
  initTool();
  sleep(1);
   while(1)
   {
   int sig = getRDM();
	printf("parent sending signal %d\n",sig);
	kill((pid_t)peyed,sig);
	nanosleep(&t,NULL);
   }
   finalizeTool();
 return 0;

}

void fightForLife(int sig){
printf("Signal Received by child %d\n",sig);
}
void abortChild(int sig){
printf("Signal Received by parent %d\n",sig);
kill((pid_t)peyed,SIGKILL);
wait();
printf("Parent will exit now\n");
exit(0);
}
