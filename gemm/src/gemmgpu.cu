#include"gemmgpu.h"

/* API:Matrix Multiplication worked by GPU */
void matMulGpu(const Matrix A,const Matrix B,Matrix C,float &elapsedTime){
	size_t size;
	Matrix d_A;
	d_A.width=A.width;d_A.height=A.height;d_A.stride=A.stride;
	Matrix d_B;
	d_B.width=B.width;d_B.height=B.height;d_B.stride=B.stride;
	Matrix d_C;
	d_C.width=C.width;d_C.height=C.height;d_C.stride=C.stride;

	cudaEvent_t beg,end;
	cudaEventCreate(&beg);
	cudaEventCreate(&end);
	cudaEventRecord(beg,0);

	size=d_A.width*d_A.height*sizeof(float);
	cudaMalloc(&d_A.elements,size);
	cudaMemcpy(d_A.elements,A.elements,size,cudaMemcpyHostToDevice);

	size=d_B.width*d_B.height*sizeof(float);
	cudaMalloc(&d_B.elements,size);
	cudaMemcpy(d_B.elements,B.elements,size,cudaMemcpyHostToDevice);

	size=d_C.width*d_C.height*sizeof(float);
	cudaMalloc(&d_C.elements,size);

	dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
	dim3 dimGrid((d_B.width+dimBlock.x-1)/dimBlock.x,(d_A.height+dimBlock.y-1)/dimBlock.y);
	matMulGpuKernel<<<dimGrid,dimBlock>>>(d_A,d_B,d_C);
	
	cudaMemcpy(C.elements,d_C.elements,size,cudaMemcpyDeviceToHost);
	cudaEventRecord(end,0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime,beg,end);

	cudaEventDestroy(beg);
	cudaEventDestroy(end);

	cudaFree(d_A.elements);
	cudaFree(d_B.elements);
	cudaFree(d_C.elements);
}

/* Builtin:Matrix Multiplication kernel workde by GPU */
__global__ void matMulGpuKernel(const Matrix d_A,const Matrix d_B,Matrix d_C){
	int blockWidth=blockIdx.x;
	int blockHeight=blockIdx.y;
	float sum=0;
	int width=threadIdx.x;
	int height=threadIdx.y;

	__shared__ float sharedA[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ float sharedB[BLOCK_SIZE][BLOCK_SIZE];

	Matrix Csub=getSubMatrix(d_C,blockHeight,blockWidth);

	for(int num=0;num<(d_A.width+BLOCK_SIZE-1)/BLOCK_SIZE-1;num++){
		Matrix Asub=getSubMatrix(d_A,blockHeight,num);
		Matrix Bsub=getSubMatrix(d_B,num,blockWidth);

		if((num*BLOCK_SIZE+width)<d_A.width && (blockHeight*BLOCK_SIZE+height)<d_A.height)
			sharedA[height][width]=getElement(Asub,height,width);
		if((blockWidth*BLOCK_SIZE+width)<d_B.width && (num*BLOCK_SIZE+height)<d_B.height)
			sharedB[height][width]=getElement(Bsub,height,width);
		
		__syncthreads();
		
		for(int index=0;index<BLOCK_SIZE;index++)
			sum+=sharedA[height][index]*sharedB[index][width];

		__syncthreads();
	}
	{
		int num=(d_A.width+BLOCK_SIZE-1)/BLOCK_SIZE-1;
		Matrix Asub=getSubMatrix(d_A,blockHeight,num);
		Matrix Bsub=getSubMatrix(d_B,num,blockWidth);

		if((num*BLOCK_SIZE+width)<d_A.width && (blockHeight*BLOCK_SIZE+height)<d_A.height)
			sharedA[height][width]=getElement(Asub,height,width);
		if((blockWidth*BLOCK_SIZE+width)<d_B.width && (num*BLOCK_SIZE+height)<d_B.height)
			sharedB[height][width]=getElement(Bsub,height,width);
		
		__syncthreads();

		if((blockHeight*BLOCK_SIZE+height)<d_A.height && (blockWidth*BLOCK_SIZE+width)<d_B.width){
			for(int index=0,length=d_A.width%BLOCK_SIZE;index<(length>0?length:BLOCK_SIZE);index++)
				sum+=sharedA[height][index]*sharedB[index][width];
		}

		__syncthreads();

		if((blockHeight*BLOCK_SIZE+height)<d_A.height && (blockWidth*BLOCK_SIZE+width)<d_B.width)
			setElement(Csub,height,width,sum);
	}

}

/* Builtin:To get certain matrix element */
__device__ float getElement(const Matrix M,int height,int width){
	return M.elements[height*M.stride+width];
}

/* Builtin:To set certain matrix element */
__device__ void setElement(Matrix M,int height,int width,float value){
	M.elements[height*M.stride+width]=value;
}

/* Builtin:To get submatrix of original matrix */
__device__ Matrix getSubMatrix(const Matrix M,int height,int width){
	Matrix Msub;
	Msub.width=BLOCK_SIZE;Msub.height=BLOCK_SIZE;Msub.stride=M.stride;
	Msub.elements=&M.elements[height*Msub.height*Msub.stride+width*Msub.width];
	return Msub;
}
