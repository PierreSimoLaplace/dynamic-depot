#include<iostream>
#include<iomanip>
#include"fftcpu.h"
using namespace std;
int main(){
	int n1=4,n2=8;
	int lf=8;
	float *M1=alloc_1d(M1,n1);
	float *M3=alloc_1d(M3,n1);
	fcomplex *M2=alloc_1d(M2,n1);
	int i,j;
	
	/* 1d FTT and IFFT */
	for(i=0;i<n1;i++)
		M1[i]=i+1;
	cout<<"FFT1d input array:"<<endl;
	for(i=0;i<n1;i++){
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<M1[i];
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	fft1d(M1,M2,n1);
	cout<<"FFT1d result:"<<endl;
	for(i=0;i<n1;i++){
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<M2[i].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<M2[i].imag()<<") ";
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	cout<<"IFFT1d result:"<<endl;
	ifft1d(M2,M3,n1);
	for(i=0;i<n1;i++){
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<M3[i];
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl<<endl;
	
	/* 2d FFT and IFFT */
	float **A1=alloc_2d(A1,n1,n2);
	float **A2=alloc_2d(A2,n1,n2);
	fcomplex **A3=alloc_2d(A3,n1,n2);
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			A1[i][j]=i+j+1;
	cout<<"FFT2d input array:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<A1[i][j];
		}
		cout<<endl;
	}
	fft2d(A1,A3,n1,n2);
	cout<<"FFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<A3[i][j].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<A3[i][j].imag()<<") ";
		}
		cout<<endl;
	}
	ifft2d(A3,A2,n1,n2);
	cout<<"FFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<A2[i][j];
		}
		cout<<endl;
	}
	free_1d(M1);
	free_1d(M2);
	free_1d(M3);
	free_2d(A1,n1);
	free_2d(A2,n1);
	free_2d(A3,n1);
	return 0;
}
