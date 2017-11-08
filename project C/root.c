#include <stdio.h>
#include <math.h>

int root(){
	double a,b,c,d;
	scanf("%lf %lf %lf",&a,&b,&c);

	if(a==0){
		if(b==0){
			if(c==0){
				printf("R\n");
			}
			else{printf("non\n");}
		}
		else{printf("%lf\n",c/b);}
	}
	else{
		d=b*b-4*a*c;
		if(d<0){printf("non\n");}
		else{
			if(d==0){printf("%lf\n",-b/2/a);}
			else{printf("%lf %lf\n",(-b+sqrt(d))/2/a,(-b-sqrt(d))/2/a);}
		}
	}
	
	return 0;
}

int euclide(int a,int b){
	int c;
	if(a<b){c=a;a=b;b=c;}
	c=a%b;
	if(c==0) printf("gcd: %d\n",b);
		else euclide(b,c);
	return 0;
}

int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	euclide(a,b);
}
