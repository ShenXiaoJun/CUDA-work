//龙格库达方法数学原理及实现 https://blog.csdn.net/u013007900/article/details/45922331
#include <stdio.h>
#include <stdlib.h>

//double y[],d[];
void Func(double *y, double *d)  {
	d[0]=y[1]; /*y0'=y1*/
	d[1]=-y[0]; /*y1'=y0*/
	d[2]=-y[2]; /*y2'=y2*/
	return;
}

//int n; //微分方程组中方程的个数，也是未知函数的个数
//int k; //积分的步数(包括起始点这一步)
//double t; //积分的起始点t0
//double h; //积分的步长
//double y[]; //存放n个未知函数在起始点t处的函数值,返回时,其初值在二维数组z的第零列中
//double z[]; //二维数组,体积为n x k.返回k个积分点上的n个未知函数值
void RKT(double t, double *y, int n, double h, int k, double (*z)[11]){
	int i=0,j=0,l=0;
	double a[4]={0.f},*b=NULL,*d=NULL;

	b=(double *)malloc(n*sizeof(double)); /*分配存储空间*/
	if(b == NULL) { printf("内存分配失败\n"); exit(1); }

	d=(double *)malloc(n*sizeof(double)); /*分配存储空间*/
	if(d == NULL) { printf("内存分配失败\n"); exit(1); } /*后面应用RK4公式中用到的系数*/

	a[0]=h/2.0;
	a[1]=h/2.0;
	a[2]=h;
	a[3]=h;
	for(i=0; i<=n-1; i++)
		z[i][0]=y[i]; /*将初值赋给数组z的相应位置*/

	for(l=1; l<=k-1; l++) {
		Func(y,d);
		for (i=0; i<=n-1; i++)
			b[i]=y[i];
		for (j=0; j<=2; j++) {
			for (i=0; i<=n-1; i++) {
				y[i]=z[i][l-1]+a[j]*d[i];
				b[i]=b[i]+a[j+1]*d[i]/3.0;
			}
			Func(y,d);
		}
		for(i=0; i<=n-1; i++)
			y[i]=b[i]+h*d[i]/6.0;
		for(i=0; i<=n-1; i++)
			z[i][l]=y[i];
		t=t+h;
	}
	free(b); /*释放存储空间*/
	free(d); /*释放存储空间*/
	return;
}
int main() {
	int i=0,j=0;
	double t=0.f, h=0.f, y[3]={0.f}, z[3][11]={0.f};
	y[0]=-1.0;
	y[1]=0.0;
	y[2]=1.0;
	t=0.0;
	h=0.01;
	RKT(t,y,3,h,11,z);
	printf("\n");
	for (i=0; i<=10; i++) /*打印输出结果*/
	{
		t=i*h;
		printf("t=%5.2f\t   ",t);
		for (j=0; j<=2; j++)
			printf("y(%d)=%e  ",j,z[j][i]);
		printf("\n");
	}
}


