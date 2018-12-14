#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_math.h>
gsl_rng_type *_gsl_rng_type;
gsl_rng *_gsl_rng;
int initTool();
void finalizeTool();
double getRDM();

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

double getRDM(){
	return(gsl_rng_uniform(_gsl_rng));
}
int main(int argc,char **argv ){
 int trials = 0;
 int successes = 0;
 int option = 0;
 int seconds = 0;
 int i;
 while((option=getopt(argc,argv,"s:t:"))!=-1){
  switch(option){
   case 's':
   seconds = atoi(optarg);
    break;
   case 't':
    trials=atoi(optarg);
  }
 initTool();
 for(i=0;i<trials;i++){
 double j = gsl_hypot(getRDM(),getRDM());
 if(j<=1)
  successes++;
 }
 finalizeTool();
  double pi = (double)successes/trials*4;
  printf("Estimated Value:%.3f\n",pi);
 return 0;

}


}
