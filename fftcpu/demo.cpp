#include<iostream>
#include<iomanip>
#include<fftw3.h>
#include<ctime>
#include<sys/time.h>
#include"fftcpu.h"
using namespace std;
int main(){
	int n1=4,n2=2;
	int lf=8;
	float *M1=alloc_1d(M1,n1);
	float *M3=alloc_1d(M3,n1);
	fcomplex *M2=alloc_1d(M2,n1);
	int i,j;
	srand(time(NULL));
	struct timeval beg,end;
	
	/* 1d FTT and IFFT */
	for(i=0;i<n1;i++)
		M1[i]=(10.0*rand()/RAND_MAX)-5;
		//M1[i]=(10*rand()/RAND_MAX)-5;
	cout<<"FFT1d input array:"<<endl;
	for(i=0;i<n1;i++){
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M1[i];
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fft1d(M1,M2,n1);
	gettimeofday(&end,NULL);
	cout<<"By fftcpu"<<endl;
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"FFT1d result:"<<endl;
	for(i=0;i<n1;i++){
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M2[i].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M2[i].imag()<<") ";
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	ifft1d(M2,M3,n1);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"IFFT1d result:"<<endl;
	for(i=0;i<n1;i++){
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M3[i];
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl<<endl;

	zero_1d(M2,n1);
	zero_1d(M3,n1);
	fftwf_complex *In,*Out;
	fftwf_plan In2Out,Out2In;
	In=(fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*n1);
	Out=(fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*n1);
	In2Out=fftwf_plan_dft_1d(n1,In,Out,FFTW_FORWARD,FFTW_ESTIMATE);
	Out2In=fftwf_plan_dft_1d(n1,Out,In,FFTW_BACKWARD,FFTW_ESTIMATE);
	cout<<"By fftw3f"<<endl;
	cout<<"FFT1d input array:"<<endl;
	for(i=0;i<n1;i++){
		In[i][0]=M1[i];
		In[i][1]=0;
		Out[i][0]=0;
		Out[i][1]=0;
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<In[i][0];
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fftwf_execute(In2Out);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"FFT1d result:"<<endl;
	for(i=0;i<n1;i++){
		In[i][0]=0;
		In[i][1]=0;
		M2[i].real()=Out[i][0];
		M2[i].imag()=Out[i][1];
		cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M2[i].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M2[i].imag()<<") ";
		if(i>0 && i%lf==0)
			cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fftwf_execute(Out2In);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"IFFT1d result:"<<endl;
	for(i=0;i<n1;i++){
		M3[i]=In[i][0]/n1;
		cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<M3[i];
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
			A1[i][j]=(10.0*rand()/RAND_MAX)-5;
			//A1[i][j]=(10*rand()/RAND_MAX)-5;
	cout<<"By fftcpu"<<endl;
	cout<<"FFT2d input array:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A1[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fft2d(A1,A3,n1,n2);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"FFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A3[i][j].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A3[i][j].imag()<<") ";
		}
		cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	ifft2d(A3,A2,n1,n2);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"IFFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A2[i][j];
		}
		cout<<endl;
	}
	cout<<endl;

	zero_2d(A2,n1,n2);
	zero_2d(A3,n1,n2);
	fftwf_plan In2Out2d,Out2In2d;
	In=(fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*n1*n2);
	Out=(fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*n1*n2);
	In2Out2d=fftwf_plan_dft_2d(n1,n2,In,Out,FFTW_FORWARD,FFTW_ESTIMATE);
	Out2In2d=fftwf_plan_dft_2d(n1,n2,Out,In,FFTW_BACKWARD,FFTW_ESTIMATE);
	//In2Out2d=fftwf_plan_dft_2d(n1,n2,In,Out,FFTW_FORWARD,FFTW_PATIENT);
	//Out2In2d=fftwf_plan_dft_2d(n1,n2,Out,In,FFTW_BACKWARD,FFTW_PATIENT);
	cout<<"By fftw3f"<<endl;
	cout<<"FFT2d input array:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			//In[i+j*n1][0]=A1[i][j];
			//In[i+j*n1][1]=0;
			//Out[i+j*n1][0]=0;
			//Out[i+j*n1][1]=0;
			In[j+i*n2][0]=A1[i][j];
			In[j+i*n2][1]=0;
			Out[j+i*n2][0]=0;
			Out[j+i*n2][1]=0;
		}
	}
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<In[j+i*n2][0];
		}
		cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fftwf_execute(In2Out2d);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"FFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			In[j+i*n2][0]=0;
			In[j+i*n2][1]=0;
			A3[i][j].real()=Out[j+i*n2][0];
			A3[i][j].imag()=Out[j+i*n2][1];
		}
	}
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<"("<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A3[i][j].real()<<","<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A3[i][j].imag()<<") ";
		}
		cout<<endl;
	}
	cout<<endl;
	gettimeofday(&beg,NULL);
	fftwf_execute(Out2In2d);
	gettimeofday(&end,NULL);
	cout<<"Time consumption:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;
	cout<<"IFFT2d result:"<<endl;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			A2[i][j]=In[j+i*n2][0]/(n1*n2);
		}
	}
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(8)<<A2[i][j];
		}
		cout<<endl;
	}
	cout<<endl;

	fftwf_free(In);
	fftwf_free(Out);
	fftwf_destroy_plan(In2Out);
	fftwf_destroy_plan(Out2In);
	fftwf_destroy_plan(In2Out2d);
	fftwf_destroy_plan(Out2In2d);
	free_1d(M1);
	free_1d(M2);
	free_1d(M3);
	free_2d(A1,n1);
	free_2d(A2,n1);
	free_2d(A3,n1);
	return 0;
}
