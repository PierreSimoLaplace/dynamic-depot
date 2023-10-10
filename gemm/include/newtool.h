#ifndef _NEWTOOL_H
#define _NEWTOOL_H
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<complex>
//#include<mpi.h>

using namespace std;
typedef complex<int> icomplex;
typedef complex<float> fcomplex;
typedef complex<double> dcomplex;

template<typename T>
T* alloc_1d(T* M,int n1);
template<typename T>
T** alloc_2d(T** M,int n1,int n2);
template<typename T>
T*** alloc_3d(T*** M,int n1,int n2,int n3);
template<typename T>
T**** alloc_4d(T**** M,int n1,int n2,int n3,int n4);
template<typename T>
void zero_1d(T* M,int n1);
template<typename T>
void zero_2d(T** M,int n1,int n2);
template<typename T>
void zero_3d(T*** M,int n1,int n2,int n3);
template<typename T>
void zero_4d(T**** M,int n1,int n2,int n3,int n4);
template<typename T>
void free_1d(T* M);
template<typename T>
void free_2d(T** M,int n1);
template<typename T>
void free_3d(T*** M,int n1,int n2);
template<typename T>
void free_4d(T**** M,int n1,int n2,int n3);
template<typename T>
void copy_1d(T* M1,T* M2,int n1);
template<typename T>
void copy_2d(T** M1,T** M2,int n1,int n2);
template<typename T>
void copy_3d(T*** M1,T*** M2,int n1,int n2,int n3);
template<typename T>
void copy_4d(T**** M1,T**** M2,int n1,int n2,int n3,int n4);
template<typename T>
void read_1d(char* file,T* M,int n1);
template<typename T>
void read_2d(char* file,T** M,int n1,int n2);
template<typename T>
void read_3d(char* file,T*** M,int n1,int n2,int n3);
template<typename T>
void read_4d(char* file,T**** M,int n1,int n2,int n3,int n4);
template<typename T>
void write_1d(char* file,T* M,int n1);
template<typename T>
void write_2d(char* file,T** M,int n1,int n2);
template<typename T>
void write_3d(char* file,T*** M,int n1,int n2,int n3);
template<typename T>
void write_4d(char* file,T**** M,int n1,int n2,int n3,int n4);
template<typename T>
void write_2d_app(char* file,T** M,int n1,int pos1,int n2,int pos2);

template<typename T>
float mod(T z);
template<typename T>
T conjg(T z);
/*
template<typename T>
void add_complex_1d(T* M1,T* M2,int* n1,MPI_Datatype *dtype);
*/

#endif
