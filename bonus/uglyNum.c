#include <stdio.h>
int main(){
int i;
printf("%d\n",1);
for(i=2;i<=10000;i++){
	if(i%2==0||i%5==0||i%3==0)
	printf("%d\n",i);
}

}
