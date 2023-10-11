#include<iostream>
#include"fftcpu.cpp"
using namespace std;
int main(){
	int n1=4,n2=8;
	float *M1=alloc_1d(M1,n1);
	float *M3=alloc_1d(M3,n1);
	fcomplex *M2=alloc_1d(M2,n1);
	int i,j;
	/*
	for(i=0;i<n1;i++)
		M1[i]=i+1;
	fft1d(M1,M2,n1);
	cout<<"fft result:"<<endl;
	for(i=0;i<n1;i++){
		cout<<"("<<M2[i].real()<<","<<M2[i].imag()<<") ";
		if(i>0 && i%4==0)
			cout<<endl;
	}
	cout<<endl;
	cout<<"ifft result:"<<endl;
	ifft1d(M2,M3,n1);
	for(i=0;i<n1;i++){
		cout<<"("<<M3[i]<<") ";
		if(i>0 && i%4==0)
			cout<<endl;
	}
	cout<<endl;
	*/
	float **A1=alloc_2d(A1,n1,n2);
	float **A2=alloc_2d(A2,n1,n2);
	fcomplex **A3=alloc_2d(A3,n1,n2);
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			A1[i][j]=i+j+1;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"A1["<<i<<"]["<<j<<"]="<<A1[i][j]<<" ";
		}
		cout<<endl;
	}
	fft2d(A1,A3,n1,n2);
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"("<<A3[i][j].real()<<","<<A3[i][j].imag()<<") ";
		}
		cout<<endl;
	}
	ifft2d(A3,A2,n1,n2);
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"A2["<<i<<"]["<<j<<"]="<<A2[i][j]<<" ";
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
