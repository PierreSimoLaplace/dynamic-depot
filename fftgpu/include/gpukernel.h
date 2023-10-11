#ifndef _FFTGPU_H
#define _FFTGPU_H
#include<cstdio>
#include<cmath>
#include<cuda_runtime.h>
#include"complexcuda.cu"
#define BLOCK_SIZE 32

typedef complexcuda<int> icomplexcuda;
typedef complexcuda<float> fcomplexcuda;
typedef complexcuda<double> dcomplexcuda;
__constant__ int d_n1;
__constant__ int d_n2;
__constant__ int d_2n1;
__constant__ int d_2n2;
__constant__ int p1;
__constant__ int p2;
__constant__ float PI;

/* API:Fourier Transform 1d,h_n1 must be 2^int */
void fft1d(fcomplexcuda *h_input,int h_n1,float &elapsedTime);

/* Builtin:Kernel function of Fourier Transform 1d */
__global__ void fft1dKernel(fcomplexcuda *d_input);

/* API:Inverse Fourier Transform 1d,h_n1 must be 2^int */
void ifft1d(fcomplexcuda *h_input,int h_n1,float &elapsedTime);

/* Builtin:Kernel function of Inverse Fourier Transform 1d */
__global__ void ifft1dKernel(fcomplexcuda *d_input);

/* API:Fourier Transform 2d,h_n1 and h_n2 must be 2^int */
void fft2d(fcomplexcuda *h_input,int h_n1,int h_n2,float &elapsedTime);

/* Builtin:Kernel function of Fourier Transform 2d */
__global__ void fft2dKernel(fcomplexcuda *d_input);

/* API:Inverse Fourier Transform 2d,h_n1 and h_n2 must be 2^int */
void ifft2d(fcomplexcuda *h_input,int h_n1,int h_n2,float &elapsedTime);

/* Builtin:Kernel function of Inverse Fourier Transform 2d */
__global__ void ifft2dKernel(fcomplexcuda *d_input);

/* Builtin:Calculate ith unit root in fft */
__device__ fcomplexcuda omega(int i,int N);

/* Builtin:Calculate ith unit root in ifft */
__device__ fcomplexcuda iomega(int i,int N);

/* Builtin:Calculate x^p fast */
__device__ int dPow(int x,int p);

#endif
