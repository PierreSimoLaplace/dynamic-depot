#ifndef _COMPLEXCUDA_H
#define _COMPLEXCUDA_H
#include<cuda_runtime.h>
template<typename T>
class complexcuda{
public:
	T real;
	T imag;

	/* Constructor */
	__host__ __device__ complexcuda(T re=0,T im=0):real(re),imag(im){}

	/* Overload operator + */
	__host__ __device__ complexcuda operator+(const complexcuda &obj);

	/* Overload operator - */
	__host__ __device__ complexcuda operator-(const complexcuda &obj);

	/* Overload operator * */
	__host__ __device__ complexcuda operator*(const complexcuda &obj);

	/* Overload operator / */
	__host__ __device__ complexcuda operator/(const complexcuda &obj);

	/* Overload operator = */
	__host__ __device__ void operator=(const complexcuda &obj);

	/* Overload operator += */
	__host__ __device__ void operator+=(const complexcuda &obj);

	/* Overload operator -= */
	__host__ __device__ void operator-=(const complexcuda &obj);

	/* Overload operator *= */
	__host__ __device__ void operator*=(const complexcuda &obj);

	/* Overload operator /= */
	__host__ __device__ void operator/=(const complexcuda &obj);

	/* Overload type-cast operator int */
	__host__ __device__ operator int();

	/* Overload type-cast operator float */
	__host__ __device__ operator float();

	/* Overload type-cast operator double */
	__host__ __device__ operator double();
	#if 0
	/* Overload type-cast operator complexcuda<int> */
	__host__ __device__ operator complexcuda<int>();

	/* Overload type-cast operator complexcuda<float> */
	__host__ __device__ operator complexcuda<float>();

	/* Overload type-cast operator complexcuda<double> */
	__host__ __device__ operator complexcuda<double>();
	#endif
};
template class complexcuda<int>;
template class complexcuda<float>;
template class complexcuda<double>;
#endif
