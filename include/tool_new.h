#ifndef _TOOL_NEW_H
#define _TOOL_NEW_H
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<complex>
//#include<mpi.h>
using namespace std;
typedef complex<float> fcomplex;
typedef complex<double> dcomplex;
typedef complex<int> icomplex;

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
/********************/


template<typename T>
T* alloc_1d(T* M,int n1){
	T* M0;
	M0=new T[n1];
	return M0;
}
template<typename T>
T** alloc_2d(T** M,int n1,int n2){
	int i;
	T** M0;
	M0=new T*[n1];
	for(i=0;i<n1;i++)
		M0[i]=new T[n2];
	return M0;
}
template<typename T>
T*** alloc_3d(T*** M,int n1,int n2,int n3){
	int i,j;
	T*** M0;
	M0=new T**[n1];
	for(i=0;i<n1;i++){
		M0[i]=new T*[n2];
		for(j=0;j<n2;j++)
			M0[i][j]=new T[n3];
	}
	return M0;
}
template<typename T>
T**** alloc_4d(T**** M,int n1,int n2,int n3,int n4){
	int i,j,k;
	T**** M0;
	M0=new T***[n1];
	for(i=0;i<n1;i++){
		M0[i]=new T**[n2];
		for(j=0;j<n2;j++){
			M0[i][j]=new T*[n3];
			for(k=0;k<n3;k++)
				M0[i][j][k]=new T[n4];
		}
	}
	return M0;
}
template<typename T>
void zero_1d(T* M,int n1){
	int i;
	for(i=0;i<n1;i++)
		M[i]=T(0);
}
template<typename T>
void zero_2d(T** M,int n1,int n2){
	int i,j;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++){
			M[i][j]=T(0);
		}
}
template<typename T>
void zero_3d(T*** M,int n1,int n2,int n3){
	int i,j,k;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				M[i][j][k]=T(0);
}
template<typename T>
void zero_4d(T**** M,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					M[i][j][k][l]=T(0);
}
template<typename T>
void free_1d(T* M){
	delete[] M;
}
template<typename T>
void free_2d(T** M,int n1){
	int i;
	for(i=0;i<n1;i++)
		delete[] M[i];
	delete[] M;
}
template<typename T>
void free_3d(T*** M,int n1,int n2){
	int i,j;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++)
			delete[] M[i][j];
		delete[] M[i];
	}
	delete[] M;
}
template<typename T>
void free_4d(T**** M,int n1,int n2,int n3){
	int i,j,k;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			for(k=0;k<n3;k++)
				delete[] M[i][j][k];
			delete[] M[i][j];
		}
		delete[] M[i];
	}
	delete[] M;
}
template<typename T>
void copy_1d(T* M1,T* M2,int n1){
	int i;
	for(i=0;i<n1;i++)
		M2[i]=M1[i];
		
}
template<typename T>
void copy_2d(T** M1,T** M2,int n1,int n2){
	int i,j;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			M2[i][j]=M1[i][j];
}
template<typename T>
void copy_3d(T*** M1,T*** M2,int n1,int n2,int n3){
	int i,j,k;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				M2[i][j][k]=M1[i][j][k];
}
template<typename T>
void copy_4d(T**** M1,T**** M2,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					M2[i][j][k][l]=M1[i][j][k][l];
}
template<typename T>
void read_1d(char* file,T* M,int n1){
	int i;
	ifstream infile;
	infile.open(file,ios::binary);
	if(!infile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		infile.read((char*)&M[i],sizeof(T));
	infile.close();
}
template<typename T>
void read_2d(char* file,T** M,int n1,int n2){
	int i,j;
	ifstream infile;
	infile.open(file,ios::binary);
	if(!infile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			infile.read((char*)&M[i][j],sizeof(T));
	infile.close();
}
template<typename T>
void read_3d(char* file,T*** M,int n1,int n2,int n3){
	int i,j,k;
	ifstream infile;
	infile.open(file,ios::binary);
	if(!infile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				infile.read((char*)&M[i][j][k],sizeof(T));
	infile.close();
}
template<typename T>
void read_4d(char* file,T**** M,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	ifstream infile;
	infile.open(file,ios::binary);
	if(!infile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					infile.read((char*)&M[i][j][k][l],sizeof(T));
	infile.close();
}
template<typename T>
void write_1d(char* file,T* M,int n1){
	int i;
	ofstream outfile;
	outfile.open(file,ios::binary);
	if(!outfile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		outfile.write((char*)&M[i],sizeof(T));
	outfile.close();
}
template<typename T>
void write_2d(char* file,T** M,int n1,int n2){
	int i,j;
	ofstream outfile;
	outfile.open(file,ios::binary);
	if(!outfile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			outfile.write((char*)&M[i][j],sizeof(T));
	outfile.close();
}
template<typename T>
void write_3d(char* file,T*** M,int n1,int n2,int n3){
	int i,j,k;
	ofstream outfile;
	outfile.open(file,ios::binary);
	if(!outfile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				outfile.write((char*)&M[i][j][k],sizeof(T));
	outfile.close();
}
template<typename T>
void write_4d(char* file,T**** M,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	ofstream outfile;
	outfile.open(file,ios::binary);
	if(!outfile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					outfile.write((char*)&M[i][j][k][l],sizeof(T));
	outfile.close();
}
template<typename T>
void write_2d_app(char* file,T** M,int n1,int pos1,int n2,int pos2){
	int i,j;
	ofstream outfile;
	outfile.open(file,ios::binary|ios::app);
	if(!outfile){
		cerr<<"Can't open the file "<<file<<endl;
		exit(1);
	}
	for(i=pos1;i<n1+pos1;i++)
		for(j=pos2;j<n2+pos2;j++)
			outfile.write((char*)&M[i][j],sizeof(T));
	outfile.close();
}
template<typename T>
float mod(T z){
	return sqrt(pow(z.real(),2)+pow(z.imag(),2));
}
template<typename T>
T conjg(T z){
	T c;
	c.real()=z.real();
	c.imag()=-z.imag();
	return c;
}
/*
template<typename T>
void add_complex_1d(T* M1,T* M2,int* n1,MPI_Datatype *dtype){
	int i;
	for(i=0;i<*n1;i++)
		M2[i]+=M1[i];
}
*/
#endif
