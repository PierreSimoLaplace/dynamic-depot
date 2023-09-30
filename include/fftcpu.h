#ifndef _FFTCPU_H
#define _FFTCPU_H
#include<cstring>
#include<typeinfo>
#include"newtool.h"

/* Arrange binary number into reverse order */
int reverseBin(int t,int p);

/* Calculate ith unit root in fft */
fcomplex omega(int i,int N);

/* Calculate ith unit root in ifft */
fcomplex iomega(int i,int N);

/* Used for assignment of single array element */
template<typename T>
void assign(T &a,fcomplex b);
/* template specilization */
template<>
void assign<float>(float &a,fcomplex b);
template<>
void assign<fcomplex>(fcomplex &a,fcomplex b);

/* Typename T can be float or complex<float>,n1 must be 2^int */
template<typename T>
void fft1d(T *input,fcomplex *output,int n1);

/* Typename T can be float or complex<float>,n1 must be 2^int */
template<typename T,typename U>
void ifft1d(T *input,U *output,int n1);

/* Typename T can be float or complex<float>,n1 and n2 must be 2^int */
template<typename T>
void fft2d(T **input,fcomplex **output,int n1,int n2);

/* Typename T can be float or complex<float>,n1 and n2 must be 2^int */
template<typename T,typename U>
void ifft2d(T **input,U **output,int n1,int n2);

#endif
