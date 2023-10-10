#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sys/time.h>
#include<iomanip>
#include<cublas_v2.h>
#include"gemmgpu.h"
#include"gemmcpu.h"
#define ROW 16
using namespace std;
void matMulBlasGpu(const Matrix TempA,const Matrix TempB,Matrix TempC,float &elapsedTime);
int main(){
	struct timeval beg,end;
	srand(time(NULL));
	Matrix A;//row-major order
	A.width=4;A.height=2;A.stride=A.width;
	A.elements=(float *)malloc(A.width*A.height*sizeof(float));
	Matrix B;//row-major order
	B.width=2;B.height=A.width;B.stride=B.width;
	B.elements=(float *)malloc(B.width*B.height*sizeof(float));
	Matrix C;//row-major order
	C.width=B.width;C.height=A.height;C.stride=C.width;
	C.elements=(float *)malloc(C.width*C.height*sizeof(float));

	cout<<"A:"<<endl;
	for(int i=0;i<A.height;i++){
		cout<<i+1<<"th row:"<<endl;
		for(int j=0;j<A.width;j++){
			//A.elements[i*A.width+j]=10*(1.0*rand()/RAND_MAX)-5;
			A.elements[i*A.width+j]=rand()%10-5;	
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<A.elements[i*A.width+j];
			if((j+1)%ROW==0 && j<A.width-1)
				cout<<endl;
			else if(j==A.width-1)
				cout<<endl;
		}
	}
	cout<<endl;

	cout<<"B:"<<endl;
	for(int i=0;i<B.height;i++){
		cout<<i+1<<"th row:"<<endl;
		for(int j=0;j<B.width;j++){
			//B.elements[i*B.width+j]=10*(1.0*rand()/RAND_MAX)-5;
			B.elements[i*B.width+j]=rand()%10-5;	
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<B.elements[i*B.width+j];
			if((j+1)%ROW==0 && j<B.width-1)
				cout<<endl;
			else if(j==B.width-1)
				cout<<endl;
		}
	}
	cout<<endl;

	
	float elapsedTime=0;
	matMulGpu(A,B,C,elapsedTime);
	cout<<"Time consumption on GPU:"<<elapsedTime<<" ms"<<endl;
	cout<<"C:"<<endl;
	for(int i=0;i<C.height;i++){
		cout<<i+1<<"th row:"<<endl;
		for(int j=0;j<C.width;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<C.elements[i*C.width+j];
			if((j+1)%ROW==0 && j<C.width-1)
				cout<<endl;
			else if(j==C.width-1)
				cout<<endl;
		}
	}
	cout<<endl;

	for(int i=0;i<C.width*C.height;i++)
		C.elements[i]=0;
	gettimeofday(&beg,NULL);
	matMulCpu(A,B,C);
	gettimeofday(&end,NULL);
	cout<<"Time consumption on CPU:"<<float((end.tv_sec-beg.tv_sec)*1000+1.0*(end.tv_usec-beg.tv_usec)/1000)<<" ms"<<endl;

	cout<<"C:"<<endl;
	for(int i=0;i<C.height;i++){
		cout<<i+1<<"th row:"<<endl;
		for(int j=0;j<C.width;j++){
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<C.elements[i*C.width+j];
			if((j+1)%ROW==0 && j<C.width-1)
				cout<<endl;
			else if(j==C.width-1)
				cout<<endl;
		}
	}
	cout<<endl;
	
	
	Matrix TempA;//column-major order
	TempA.height=A.height;TempA.width=A.width;TempA.stride=TempA.width;
	TempA.elements=(float *)malloc(TempA.width*TempA.height*sizeof(float));
	Matrix TempB;//column-major order
	TempB.height=B.height;TempB.width=B.width;TempB.stride=TempB.width;
	TempB.elements=(float *)malloc(TempB.width*TempB.height*sizeof(float));
	Matrix TempC;//column-major order
	TempC.height=C.height;TempC.width=C.width;TempC.stride=TempC.width;
	TempC.elements=(float *)malloc(TempC.width*TempC.height*sizeof(float));

	cout<<"TempA:"<<endl;
	for(int j=0;j<TempA.width;j++){
		cout<<j+1<<"th column:"<<endl;
		for(int i=0;i<TempA.height;i++){
			TempA.elements[j*TempA.height+i]=A.elements[i*TempA.width+j];
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<TempA.elements[j*TempA.height+i];
			if((i+1)%ROW==0 && i<TempA.height-1)
				cout<<endl;
			else if(i==TempA.height-1)
				cout<<endl;
		}
		cout<<endl;
	}
	cout<<endl;

	cout<<"TempB:"<<endl;
	for(int j=0;j<TempB.width;j++){
		cout<<j+1<<"th column:"<<endl;
		for(int i=0;i<TempB.height;i++){
			TempB.elements[j*TempB.height+i]=B.elements[i*TempB.width+j];
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<TempB.elements[j*TempB.height+i];
			if((i+1)%ROW==0 && i<TempB.height-1)
				cout<<endl;
			else if(i==TempB.height-1)
				cout<<endl;
		}
	}
	cout<<endl;

	for(int i=0;i<C.width*C.height;i++)
		C.elements[i]=0;

	elapsedTime=0;
	matMulBlasGpu(TempA,TempB,TempC,elapsedTime);
	cout<<"Time consumption using CUBLAS:"<<elapsedTime<<" ms"<<endl;
	cout<<"C:"<<endl;
	for(int i=0;i<C.height;i++){
		cout<<i+1<<"th row:"<<endl;
		for(int j=0;j<C.width;j++){
			C.elements[i*C.width+j]=TempC.elements[j*C.height+i];
			cout<<fixed<<setprecision(2)<<setiosflags(ios::right)<<setw(6)<<C.elements[i*C.width+j];
			if((j+1)%ROW==0 && j<C.width-1)
				cout<<endl;
			else if(j==C.width-1)
				cout<<endl;
		}
	}
	cout<<endl;
	
	free(A.elements);
	free(B.elements);
	free(C.elements);

	return 0;
}
void matMulBlasGpu(const Matrix TempA,const Matrix TempB,Matrix TempC,float &elapsedTime){
	float alpha=1,beta=0;
	cublasStatus_t status;
	cublasHandle_t handle;
	status=cublasCreate(&handle);

	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);
	cudaEventRecord(beg,0);

	float *d_TempA,*d_TempB,*d_TempC;
	cudaMalloc((void **)&d_TempA,TempA.height*TempA.width*sizeof(float));
	cudaMalloc((void **)&d_TempB,TempB.height*TempB.width*sizeof(float));
	cudaMalloc((void **)&d_TempC,TempC.height*TempC.width*sizeof(float));

	cublasSetVector(TempA.width*TempA.height,sizeof(float),TempA.elements,1,d_TempA,1);
	cublasSetVector(TempB.width*TempB.height,sizeof(float),TempB.elements,1,d_TempB,1);

	cublasSgemm(handle,CUBLAS_OP_N,CUBLAS_OP_N,TempA.height,TempB.width,TempA.width,&alpha,d_TempA,TempA.height,d_TempB,TempB.height,&beta,d_TempC,TempA.height);
	cudaDeviceSynchronize();

	cublasGetVector(TempC.height*TempC.width,sizeof(float),d_TempC,1,TempC.elements,1);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaFree(d_TempA);
	cudaFree(d_TempB);
	cudaFree(d_TempC);
	cudaEventDestroy(beg);
	cudaEventDestroy(end);
	cublasDestroy(handle);
}
