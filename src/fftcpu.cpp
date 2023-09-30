#include"fftcpu.h"
const float PI=4*atan(1);

/* Arrange binary number into reverse order */
int reverseBin(int t,int p){
	int res=0,i;
	while(p--){
		i=t&1;
		t>>=1;
		res+=i*pow(2,p);
	}
	return res;
}

/* Calculate ith unit root in fft */
fcomplex omega(int i,int N){
	fcomplex w;
	w.real(cos(2*PI*i/N));
	w.imag(sin(-2*PI*i/N));
	return w;
}

/* Calculate ith unit root in ifft */
fcomplex iomega(int i,int N){
	fcomplex w;
	w.real(cos(2*PI*i/N));
	w.imag(sin(2*PI*i/N));
	return w;
}

/* Used for assignment of single array element */
template<typename T>
void assign(T &a,fcomplex b){
	a=b;
};
/* template specilization */
template<>
void assign<float>(float &a,fcomplex b){
	a=b.real();
}
template<>
void assign<fcomplex>(fcomplex &a,fcomplex b){
	a=b;
}

/* Typename T can be float or complex<float>,n1 must be 2^int */
template<typename T>
void fft1d(T *input,fcomplex *output,int n1){
	int k,l,i,t;
	int p=0;
	while(n1>pow(2,p))
		p++;
	for(t=0;t<n1;t++){
		i=reverseBin(t,p);
		output[t]=fcomplex(input[i]);
	}
	for(k=1;k<=p;k++)
		for(l=0;l<n1/pow(2,k);l++)
			for(i=0;i<pow(2,k-1);i++){
				fcomplex temp;
				fcomplex w=omega(i,pow(2,k));
				int index1=l*pow(2,k)+i;
				int index2=l*pow(2,k)+i+pow(2,k-1);
				temp=output[index1];
				output[index1]=output[index1]+w*output[index2];
				output[index2]=temp-w*output[index2];
			}
}
/* Preinstantiation of fft1d */
template void fft1d<fcomplex>(fcomplex *,fcomplex *,int);
template void fft1d<float>(float *,fcomplex *,int);

/* Typename T can be float or complex<float>,n1 must be 2^int */
template<typename T,typename U>
void ifft1d(T *input,U *output,int n1){
	int k,l,i,t;
	int p=0;
	fcomplex *subs=alloc_1d(subs,n1);
	zero_1d(subs,n1);
	while(n1>pow(2,p))
		p++;
	for(t=0;t<n1;t++){
		i=reverseBin(t,p);
		subs[t]=fcomplex(input[i]);
	}
	for(k=1;k<=p;k++)
		for(l=0;l<n1/pow(2,k);l++)
			for(i=0;i<pow(2,k-1);i++){
				fcomplex temp;
				fcomplex w=iomega(i,pow(2,k));
				int index1=l*pow(2,k)+i;
				int index2=l*pow(2,k)+i+pow(2,k-1);
				temp=subs[index1];
				subs[index1]=subs[index1]+w*subs[index2];
				subs[index2]=temp-w*subs[index2];
			}
	for(t=0;t<n1;t++){
		subs[t]/=n1;
		/* The value of typeid().name() here are based on Linux version 3.10.0-1160.41.1.el7.x86_64 and gcc version 4.8.5 20150623 (Red Hat 4.8.5-44) (GCC) while may differ from compiler operating system */
		/*
		if(strcmp(typeid(output).name(),"Pf")==0){
			output[t]=subs[t].real();
		}else if(strcmp(typeid(output).name(),"PSt7complexIfE")==0){
			output[t]=subs[t];
		}
		*/
		/*
		if(strcmp(typeid(output).name(),typeid(float *).name())==0){
			output[t]=subs[t].real();
		}else if(strcmp(typeid(output).name(),typeid(fcomplex *).name())==0){
			output[t]=subs[t];
		}
		*/
		assign(output[t],subs[t]);
	}
	free_1d(subs);
}
/* Preinstantiation of ifft1d */
template void ifft1d<fcomplex,float>(fcomplex *,float *,int);
template void ifft1d<float,float>(float *,float *,int);
template void ifft1d<fcomplex,fcomplex>(fcomplex *,fcomplex *,int);
template void ifft1d<float,fcomplex>(float *,fcomplex *,int);

/* Typename T can be float or complex<float>,n1 and n2 must be 2^int */
template<typename T>
void fft2d(T **input,fcomplex **output,int n1,int n2){
	int i,j;
	T *input1dFft1=alloc_1d(input1dFft1,n2);
	fcomplex *output1dFft=alloc_1d(output1dFft,n2);
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++)
			input1dFft1[j]=input[i][j];
		fft1d(input1dFft1,output1dFft,n2);
		for(j=0;j<n2;j++)
			output[i][j]=output1dFft[j];
	}
	free_1d(input1dFft1);
	free_1d(output1dFft);

	fcomplex *input1dFft2=alloc_1d(input1dFft2,n1);
	output1dFft=alloc_1d(output1dFft,n1);
	for(j=0;j<n2;j++){
		for(i=0;i<n1;i++)
			input1dFft2[i]=output[i][j];
		fft1d(input1dFft2,output1dFft,n1);
		for(i=0;i<n1;i++)
			output[i][j]=output1dFft[i];
	}
	free_1d(input1dFft2);
	free_1d(output1dFft);
}
/* Preinstantiation of fft2d */
template void fft2d<fcomplex>(fcomplex **,fcomplex **,int,int);
template void fft2d<float>(float **,fcomplex **,int,int);

/* Typename T can be float or complex<float>,n1 and n2 must be 2^int */
template<typename T,typename U>
void ifft2d(T **input,U **output,int n1,int n2){
	int i,j;
	T *input1dFft1=alloc_1d(input1dFft1,n2);
	fcomplex *output1dFft=alloc_1d(output1dFft,n2);
	fcomplex **output2dFft=alloc_2d(output2dFft,n1,n2);
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++)
			input1dFft1[j]=input[i][j];
		ifft1d(input1dFft1,output1dFft,n2);
		for(j=0;j<n2;j++)
			output2dFft[i][j]=output1dFft[j];
	}
	free_1d(input1dFft1);
	free_1d(output1dFft);
	
	fcomplex *input1dFft2=alloc_1d(input1dFft2,n1);
	output1dFft=alloc_1d(output1dFft,n1);
	for(j=0;j<n2;j++){
		for(i=0;i<n1;i++)
			input1dFft2[i]=output2dFft[i][j];
		ifft1d(input1dFft2,output1dFft,n1);
		for(i=0;i<n1;i++)
			output2dFft[i][j]=output1dFft[i];
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++){
			assign(output[i][j],output2dFft[i][j]);
		}
	free_1d(input1dFft2);
	free_1d(output1dFft);
	free_2d(output2dFft,n1);
}
/* Preinstantiation of ifft2d */
template void ifft2d<fcomplex,float>(fcomplex **,float **,int,int);
template void ifft2d<float,float>(float **,float **,int,int);
template void ifft2d<fcomplex,fcomplex>(fcomplex **,fcomplex **,int,int);
template void ifft2d<float,fcomplex>(float **,fcomplex **,int,int);
