#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iomanip>
#include<sys/time.h>
#include"gpukernel.h"
using namespace std;
int main(){
	srand(time(NULL));
	int H_N1=16,H_N2=16;//H_N1 is row length and H_N2 is column length
	float elapsedTime=0;

	cout<<"1D Array:"<<endl;
	fcomplexcuda *h_input;
	h_input=(fcomplexcuda *)malloc(H_N1*sizeof(fcomplexcuda));
	for(int i=0;i<H_N1;i++){
		//h_input[i].real=10.0*rand()/RAND_MAX-5;
		//h_input[i].imag=10.0*rand()/RAND_MAX-5;
		h_input[i].real=i+1;
		h_input[i].imag=0;
	}
	cout<<"h_input:"<<endl;
	for(int i=0;i<H_N1;i++){
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].imag<<") ";
		if((i+1)%8==0)
			cout<<endl;
	}
	cout<<endl;

	fft1d(h_input,H_N1,elapsedTime);

	cout<<"FFT1D:"<<endl;
	for(int i=0;i<H_N1;i++){
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].imag<<") ";
		if((i+1)%8==0 && i<H_N1-1)
			cout<<endl;
		else if(i==H_N1-1)
			cout<<endl;
	}
	cout<<endl;

	cout<<"FFT1DGPU time consumption:"<<elapsedTime<<" ms"<<endl;

	ifft1d(h_input,H_N1,elapsedTime);

	cout<<"IFFT1D:"<<endl;
	for(int i=0;i<H_N1;i++){
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h_input[i].imag<<") ";
		if((i+1)%8==0 && i<H_N1-1)
			cout<<endl;
		else if(i==H_N1-1)
			cout<<endl;
	}
	cout<<endl;

	cout<<"IFFT1DGPU time consumption:"<<elapsedTime<<" ms"<<endl;

	cout<<"2D Array:"<<endl;
	fcomplexcuda *h2_input;
	h2_input=(fcomplexcuda *)malloc(H_N1*H_N2*sizeof(fcomplexcuda));
	for(int j=0;j<H_N2;j++){
		for(int i=0;i<H_N1;i++){
			//h2_input[j*H_N1+i].real=10.0*rand()/RAND_MAX-5;
			//h2_input[j*H_N1+i].imag=10.0*rand()/RAND_MAX-5;
			h2_input[j*H_N1+i].real=j*H_N1+i+1;
			h2_input[j*H_N1+i].imag=0;
		}
	}
	cout<<"h2_input:"<<endl;
	for(int j=0;j<H_N2;j++){
		cout<<j+1<<"th row:"<<endl;
		for(int i=0;i<H_N1;i++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].imag<<") ";
			if((i+1)%8==0 && i<H_N1-1)
				cout<<endl;
			else if(i==H_N1-1)
				cout<<endl;
		}
	}
	cout<<endl;

	fft2d(h2_input,H_N1,H_N2,elapsedTime);

	cout<<"FFT2D:"<<endl;
	for(int j=0;j<H_N2;j++){
		cout<<j+1<<"th row:"<<endl;
		for(int i=0;i<H_N1;i++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].imag<<") ";
			if((i+1)%8==0 && i<H_N1-1)
				cout<<endl;
			else if(i==H_N1-1)
				cout<<endl;
		}
	}
	cout<<endl;


	cout<<"FFT2DGPU time consumption:"<<elapsedTime<<" ms"<<endl;

	ifft2d(h2_input,H_N1,H_N2,elapsedTime);

	cout<<"IFFT2D:"<<endl;
	for(int j=0;j<H_N2;j++){
		cout<<j+1<<"th row:"<<endl;
		for(int i=0;i<H_N1;i++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].real<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<h2_input[j*H_N1+i].imag<<") ";
			if((i+1)%8==0 && i<H_N1-1)
				cout<<endl;
			else if(i==H_N1-1)
				cout<<endl;
		}
	}
	cout<<endl;

	cout<<"IFFT2DGPU time consumption:"<<elapsedTime<<" ms"<<endl;

	free(h_input);
	free(h2_input);
	return 0;
}
