#include"gpukernel.h"

/* API:Fourier Transform 1d,h_n1 must be 2^int */
void fft1d(fcomplexcuda *h_input,int h_n1,float &elapsedTime){
	int h_p1=0;
	float h_PI=4*atan(1);
	int h_2n1=h_n1/2;
	while(h_n1>pow(2,h_p1)){
		h_p1++;
	}

	cudaMemcpyToSymbol(d_n1,&h_n1,sizeof(int));
	cudaMemcpyToSymbol(d_2n1,&h_2n1,sizeof(int));
	cudaMemcpyToSymbol(p1,&h_p1,sizeof(int));
	cudaMemcpyToSymbol(PI,&h_PI,sizeof(float));

	fcomplexcuda *d_input;
	cudaMalloc((void **)&d_input,h_n1*sizeof(fcomplexcuda));

	dim3 dimBlock(BLOCK_SIZE);
	dim3 dimGrid((h_n1+dimBlock.x-1)/dimBlock.x);
	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);

	cudaEventRecord(beg,0);
	cudaMemcpy(d_input,h_input,h_n1*sizeof(fcomplexcuda),cudaMemcpyHostToDevice);
	fft1dKernel<<<dimGrid,dimBlock>>>(d_input);
	cudaMemcpy(h_input,d_input,h_n1*sizeof(fcomplexcuda),cudaMemcpyDeviceToHost);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaEventDestroy(beg);
	cudaEventDestroy(end);

	cudaFree(d_input);
}

/* Builtin:Kernel function of Fourier Transform 1d */
__global__ void fft1dKernel(fcomplexcuda *d_input){
	__shared__ int p2k,p2kAdd1;
	int idx=threadIdx.x+blockIdx.x*blockDim.x;
	int sign;
	int indexLeft;
	fcomplexcuda w;
	if(idx<d_n1){
		for(int k=0;k<p1;k++){
			if(threadIdx.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idx%p2kAdd1<p2k?1:-1;
			w=omega(idx%p2k,p2kAdd1);
			indexLeft=idx/p2kAdd1*p2k+idx%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx]=d_input[indexLeft]+w*d_input[indexLeft+d_2n1];
			//__syncthreads();
			__threadfence();
		}
	}

}

/* API:Inverse Fourier Transform 1d,h_n1 must be 2^int */
void ifft1d(fcomplexcuda *h_input,int h_n1,float &elapsedTime){
	int h_p1=0;
	float h_PI=4*atan(1);
	int h_2n1=h_n1/2;
	while(h_n1>pow(2,h_p1)){
		h_p1++;
	}

	cudaMemcpyToSymbol(d_n1,&h_n1,sizeof(int));
	cudaMemcpyToSymbol(d_2n1,&h_2n1,sizeof(int));
	cudaMemcpyToSymbol(p1,&h_p1,sizeof(int));
	cudaMemcpyToSymbol(PI,&h_PI,sizeof(float));

	fcomplexcuda *d_input;
	cudaMalloc((void **)&d_input,h_n1*sizeof(fcomplexcuda));

	dim3 dimBlock(BLOCK_SIZE);
	dim3 dimGrid((h_n1+dimBlock.x-1)/dimBlock.x);
	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);

	cudaEventRecord(beg,0);
	cudaMemcpy(d_input,h_input,h_n1*sizeof(fcomplexcuda),cudaMemcpyHostToDevice);
	ifft1dKernel<<<dimGrid,dimBlock>>>(d_input);
	cudaMemcpy(h_input,d_input,h_n1*sizeof(fcomplexcuda),cudaMemcpyDeviceToHost);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaEventDestroy(beg);
	cudaEventDestroy(end);

	cudaFree(d_input);
}

/* Builtin:Kernel function of Inverse Fourier Transform 1d */
__global__ void ifft1dKernel(fcomplexcuda *d_input){
	__shared__ int p2k,p2kAdd1;
	int idx=threadIdx.x+blockIdx.x*blockDim.x;
	int sign;
	int indexLeft;
	fcomplexcuda w;
	if(idx<d_n1){
		for(int k=0;k<p1;k++){
			if(threadIdx.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idx%p2kAdd1<p2k?1:-1;
			w=iomega(idx%p2k,p2kAdd1);
			indexLeft=idx/p2kAdd1*p2k+idx%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx]=d_input[indexLeft]+w*d_input[indexLeft+d_2n1];
			//__syncthreads();
			__threadfence();
		}
		d_input[idx].real/=d_n1;
		d_input[idx].imag/=d_n1;
	}

}

/* API:Fourier Transform 2d,h_n1 and h_n2 must be 2^int */
void fft2d(fcomplexcuda *h_input,int h_n1,int h_n2,float &elapsedTime){
	int h_p1=0,h_p2=0;
	float h_PI=4*atan(1);
	int h_2n1=h_n1/2;
	int h_2n2=h_n2/2;
	while(h_n1>pow(2,h_p1)){
		h_p1++;
	}
	while(h_n2>pow(2,h_p2)){
		h_p2++;
	}

	cudaMemcpyToSymbol(d_n1,&h_n1,sizeof(int));
	cudaMemcpyToSymbol(d_n2,&h_n2,sizeof(int));
	cudaMemcpyToSymbol(d_2n1,&h_2n1,sizeof(int));
	cudaMemcpyToSymbol(d_2n2,&h_2n2,sizeof(int));
	cudaMemcpyToSymbol(p1,&h_p1,sizeof(int));
	cudaMemcpyToSymbol(p2,&h_p2,sizeof(int));
	cudaMemcpyToSymbol(PI,&h_PI,sizeof(float));

	fcomplexcuda *d_input;
	cudaMalloc((void **)&d_input,h_n1*h_n2*sizeof(fcomplexcuda));

	dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
	dim3 dimGrid((h_n1+dimBlock.x-1)/dimBlock.x,(h_n2+dimBlock.y-1)/dimBlock.y);
	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);

	cudaEventRecord(beg,0);
	cudaMemcpy(d_input,h_input,h_n1*h_n2*sizeof(fcomplexcuda),cudaMemcpyHostToDevice);
	fft2dKernel<<<dimGrid,dimBlock>>>(d_input);
	cudaMemcpy(h_input,d_input,h_n1*h_n2*sizeof(fcomplexcuda),cudaMemcpyDeviceToHost);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaEventDestroy(beg);
	cudaEventDestroy(end);

	cudaFree(d_input);
}

/* Builtin:Kernel function of Fourier Transform 2d */
__global__ void fft2dKernel(fcomplexcuda *d_input){
	__shared__ int p2k,p2kAdd1;
	int idx=threadIdx.x+blockIdx.x*blockDim.x;
	int idy=threadIdx.y+blockIdx.y*blockDim.y;
	int stridey=d_n1*idy;
	int sign;
	int indexLeft;
	fcomplexcuda w;
	if(idx<d_n1 && idy<d_n2){
		for(int k=0;k<p1;k++){
			if(threadIdx.x+threadIdx.y*blockDim.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idx%p2kAdd1<p2k?1:-1;
			w=omega(idx%p2k,p2kAdd1);
			indexLeft=idx/p2kAdd1*p2k+idx%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx+stridey]=d_input[indexLeft+stridey]+w*d_input[indexLeft+d_2n1+stridey];
			//__syncthreads();
			__threadfence();
		}
		//__syncthreads();
		__threadfence();
		for(int k=0;k<p2;k++){
			if(threadIdx.x+threadIdx.y*blockDim.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idy%p2kAdd1<p2k?1:-1;
			w=omega(idy%p2k,p2kAdd1);
			indexLeft=idy/p2kAdd1*p2k+idy%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx+stridey]=d_input[indexLeft*d_n1+idx]+w*d_input[(indexLeft+d_2n2)*d_n1+idx];
			//__syncthreads();
			__threadfence();
		}
	}

}

/* API:Inverse Fourier Transform 2d,h_n1 and h_n2 must be 2^int */
void ifft2d(fcomplexcuda *h_input,int h_n1,int h_n2,float &elapsedTime){
	int h_p1=0,h_p2=0;
	float h_PI=4*atan(1);
	int h_2n1=h_n1/2;
	int h_2n2=h_n2/2;
	while(h_n1>pow(2,h_p1)){
		h_p1++;
	}
	while(h_n2>pow(2,h_p2)){
		h_p2++;
	}

	cudaMemcpyToSymbol(d_n1,&h_n1,sizeof(int));
	cudaMemcpyToSymbol(d_n2,&h_n2,sizeof(int));
	cudaMemcpyToSymbol(d_2n1,&h_2n1,sizeof(int));
	cudaMemcpyToSymbol(d_2n2,&h_2n2,sizeof(int));
	cudaMemcpyToSymbol(p1,&h_p1,sizeof(int));
	cudaMemcpyToSymbol(p2,&h_p2,sizeof(int));
	cudaMemcpyToSymbol(PI,&h_PI,sizeof(float));

	fcomplexcuda *d_input;
	cudaMalloc((void **)&d_input,h_n1*h_n2*sizeof(fcomplexcuda));

	dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
	dim3 dimGrid((h_n1+dimBlock.x-1)/dimBlock.x,(h_n2+dimBlock.y-1)/dimBlock.y);
	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);

	cudaEventRecord(beg,0);
	cudaMemcpy(d_input,h_input,h_n1*h_n2*sizeof(fcomplexcuda),cudaMemcpyHostToDevice);
	ifft2dKernel<<<dimGrid,dimBlock>>>(d_input);
	cudaMemcpy(h_input,d_input,h_n1*h_n2*sizeof(fcomplexcuda),cudaMemcpyDeviceToHost);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaEventDestroy(beg);
	cudaEventDestroy(end);

	cudaFree(d_input);
}

/* Builtin:Kernel function of Inverse Fourier Transform 2d */
__global__ void ifft2dKernel(fcomplexcuda *d_input){
	__shared__ int p2k,p2kAdd1;
	int idx=threadIdx.x+blockIdx.x*blockDim.x;
	int idy=threadIdx.y+blockIdx.y*blockDim.y;
	int stridey=d_n1*idy;
	int sign;
	int indexLeft;
	fcomplexcuda w;
	if(idx<d_n1 && idy<d_n2){
		for(int k=0;k<p1;k++){
			if(threadIdx.x+threadIdx.y*blockDim.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idx%p2kAdd1<p2k?1:-1;
			w=iomega(idx%p2k,p2kAdd1);
			indexLeft=idx/p2kAdd1*p2k+idx%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx+stridey]=d_input[indexLeft+stridey]+w*d_input[indexLeft+d_2n1+stridey];
			//__syncthreads();
			__threadfence();
		}
		d_input[idx+stridey].real/=d_n1;
		d_input[idx+stridey].imag/=d_n1;
		//__syncthreads();
		__threadfence();

		for(int k=0;k<p2;k++){
			if(threadIdx.x+threadIdx.y*blockDim.x==0){
				p2k=dPow(2,k);
				p2kAdd1=dPow(2,k+1);
			}
			__syncthreads();
			sign=idy%p2kAdd1<p2k?1:-1;
			w=iomega(idy%p2k,p2kAdd1);
			indexLeft=idy/p2kAdd1*p2k+idy%p2k;
			w=fcomplexcuda(sign*w.real,sign*w.imag);
			d_input[idx+stridey]=d_input[indexLeft*d_n1+idx]+w*d_input[(indexLeft+d_2n2)*d_n1+idx];
			//__syncthreads();
			__threadfence();
		}
		d_input[idx+stridey].real/=d_n2;
		d_input[idx+stridey].imag/=d_n2;
	}

}

/* Builtin:Calculate ith unit root in fft */
__device__ fcomplexcuda omega(int i,int N){
	fcomplexcuda w;
	w.real=cos(2*PI*i/N);
	w.imag=sin(-2*PI*i/N);
	return w;
}

/* Builtin:Calculate ith unit root in ifft */
__device__ fcomplexcuda iomega(int i,int N){
	fcomplexcuda w;
	w.real=cos(2*PI*i/N);
	w.imag=sin(2*PI*i/N);
	return w;
}

/* Builtin:Calculate x^p fast */
__device__ int dPow(int x,int p){
	int res=1;
	while(p){
		if(p&1)
			res*=x;
		p>>=1;
		x*=x;
	}
	return res;
}
