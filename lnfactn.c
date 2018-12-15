#include <math.h>
#include <stdio.h>
int main(){
int i=0;
double curFact = 0;
double curApprx = 0;
double error=0;
double errorP=0;
printf("N\tln(Factorial)\tStirling's Formula\tError\tError Percent\n");
for(i=1;i<=100;i++){
curFact+=log(i);
curApprx=i*log(i)-i;
error = curFact - curApprx;
if(error<0)
error *=-1;
if(curFact==0)
errorP=100;
else
errorP = error/curFact*100;
printf("%d\t%.7f\t%.7f\t%.7f\t%.7f\n",i,curFact,curApprx,error,errorP);
}

}
