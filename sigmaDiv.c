#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(int argc,char** argv){
if(argc==2)
{
int source = atoi(argv[1]);
int sum=1;
int i;
for(i=2;i<=source/2;i++){
if(source%i==0)
sum+=i;
}
if(sum>source){
	printf("The number %d is an abundant number with abundance %d\n",sum-source);
}else if(sum == source){
	printf("The number %d is a perfect number\n",source);
}else{
	printf("The number %d is a deficient number with deficiency %d\n",source,source-sum);
}
}else{
perror("You need to supply the number for checking!");
exit(1);
}
}
