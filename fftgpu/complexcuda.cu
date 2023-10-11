#include"complexcuda.h"

/* Overload operator + */
template<typename T>
__host__ __device__ complexcuda<T> complexcuda<T>::operator+(const complexcuda &obj){
	complexcuda res;
	res.real=this->real+obj.real;
	res.imag=this->imag+obj.imag;
	return res;
}

/* Overload operator - */
template<typename T>
__host__ __device__ complexcuda<T> complexcuda<T>::operator-(const complexcuda &obj){
	complexcuda res;
	res.real=this->real-obj.real;
	res.imag=this->imag-obj.imag;
	return res;
}

/* Overload operator * */
template<typename T>
__host__ __device__ complexcuda<T> complexcuda<T>::operator*(const complexcuda &obj){
	complexcuda res;
	res.real=this->real*obj.real-this->imag*obj.imag;
	res.imag=this->real*obj.imag+this->imag*obj.real;
	return res;
}

/* Overload operator / */
template<typename T>
__host__ __device__ complexcuda<T> complexcuda<T>::operator/(const complexcuda &obj){
	complexcuda res;
	T denom=obj.real*obj.real+obj.imag*obj.imag;
	res.real=(this->real*obj.real+this->imag*obj.imag)/denom;
	res.imag=(this->imag*obj.real-this->real*obj.imag)/denom;
	return res;
}

/* Overload operator = */
template<typename T>
__host__ __device__ void complexcuda<T>::operator=(const complexcuda &obj){
	this->real=obj.real;
	this->imag=obj.imag;
}

/* Overload operator += */
template<typename T>
__host__ __device__ void complexcuda<T>::operator+=(const complexcuda &obj){
	*this=*this+obj;
}

/* Overload operator -= */
template<typename T>
__host__ __device__ void complexcuda<T>::operator-=(const complexcuda &obj){
	*this=*this-obj;
}

/* Overload operator *= */
template<typename T>
__host__ __device__ void complexcuda<T>::operator*=(const complexcuda &obj){
	*this=*this*obj;
}

/* Overload operator /= */
template<typename T>
__host__ __device__ void complexcuda<T>::operator/=(const complexcuda &obj){
	*this=*this/obj;
}

/* Overload type-cast operator int */
template<typename T>
__host__ __device__ complexcuda<T>::operator int(){
	return int(this->real);
}

/* Overload type-cast operator float */
template<typename T>
__host__ __device__ complexcuda<T>::operator float(){
	return float(this->real);
}

/* Overload type-cast operator double */
template<typename T>
__host__ __device__ complexcuda<T>::operator double(){
	return double(this->real);
}
#if 0
/* Overload type-cast operator complexcuda<int> */
template<typename T>
__host__ __device__ complexcuda<T>::operator complexcuda<int>(){
	complexcuda<int> res;
	res.real=int(this->real);
	res.imag=int(this->imag);
	return res;
}

/* Overload type-cast operator complexcuda<float> */
template<typename T>
__host__ __device__ complexcuda<T>::operator complexcuda<float>(){
	complexcuda<float> res;
	res.real=float(this->real);
	res.imag=float(this->imag);
	return res;
}

/* Overload type-cast operator complexcuda<double> */
template<typename T>
__host__ __device__ complexcuda<T>::operator complexcuda<double>(){
	complexcuda<double> res;
	res.real=double(this->real);
	res.imag=double(this->imag);
	return res;
}
#endif
