#ifndef _GEMMGPU_H
#define _GEMMGPU_H
#define BLOCK_SIZE 32
#include<cuda_runtime.h>

#ifndef _MATRIX
#define _MATRIX
/* Input and output matrix */
class Matrix{
public:
	int width;
	int height;
	int stride;
	float *elements;
};
#endif

/* API:Matrix Multiplication worked by GPU */
void matMulGpu(const Matrix A,const Matrix B,Matrix C,float &elapsedTime);

/* Builtin:Matrix Multiplication kernel workde by GPU */
__global__ void matMulGpuKernel(Matrix d_A,Matrix d_B,Matrix d_C);

/* Builtin:To get certain matrix element */
__device__ float getElement(const Matrix M,int height,int width);

/* Builtin:To set certain matrix element */
__device__ void setElement(Matrix M,int height,int width,float value);

/* Builtin:To get submatrix of original matrix */
__device__ Matrix getSubMatrix(const Matrix M,int height,int width);
#endif
