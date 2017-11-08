/*Primality test*/
//in: x
//out: x is prime, otherwise output its first factor
///complexity: O(x^(1/2))
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int blindtest(int x){
	int s=(int)sqrt(x);
	int i=2;
	while(i<=s){
		if(x%i==0){
			printf("Frist factor = %d\n",i);
		return 1;
		}
		i++;
	}
	printf("Prime\n");
	return 0;
}

int main(int argc, char **argv){
	int x;
	if (argc>1)
		x=atoi(argv[1]);
	else
		scanf("%d",&x);
	printf("/*Primality test: %d*/\n",x);
	blindtest(x);

	return 0;
}