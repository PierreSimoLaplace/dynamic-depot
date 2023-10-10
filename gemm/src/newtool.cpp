#include"newtool.h"

template<typename T>
T* alloc_1d(T* M,int n1){
	T* M0;
	M0=new T[n1];
	return M0;
}
template int* alloc_1d<int>(int *,int);
template float* alloc_1d<float>(float *,int);
template double* alloc_1d<double>(double *,int);
template icomplex* alloc_1d<icomplex>(icomplex *,int);
template fcomplex* alloc_1d<fcomplex>(fcomplex *,int);
template dcomplex* alloc_1d<dcomplex>(dcomplex *,int);

template<typename T>
T** alloc_2d(T** M,int n1,int n2){
	int i;
	T** M0;
	M0=new T*[n1];
	for(i=0;i<n1;i++)
		M0[i]=new T[n2];
	return M0;
}
template int** alloc_2d<int>(int **,int,int);
template float** alloc_2d<float>(float **,int,int);
template double** alloc_2d<double>(double **,int,int);
template icomplex** alloc_2d<icomplex>(icomplex **,int,int);
template fcomplex** alloc_2d<fcomplex>(fcomplex **,int,int);
template dcomplex** alloc_2d<dcomplex>(dcomplex **,int,int);

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
template int*** alloc_3d<int>(int ***,int,int,int);
template float*** alloc_3d<float>(float ***,int,int,int);
template double*** alloc_3d<double>(double ***,int,int,int);
template icomplex*** alloc_3d<icomplex>(icomplex ***,int,int,int);
template fcomplex*** alloc_3d<fcomplex>(fcomplex ***,int,int,int);
template dcomplex*** alloc_3d<dcomplex>(dcomplex ***,int,int,int);

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
template int**** alloc_4d<int>(int ****,int,int,int,int);
template float**** alloc_4d<float>(float ****,int,int,int,int);
template double**** alloc_4d<double>(double ****,int,int,int,int);
template icomplex**** alloc_4d<icomplex>(icomplex ****,int,int,int,int);
template fcomplex**** alloc_4d<fcomplex>(fcomplex ****,int,int,int,int);
template dcomplex**** alloc_4d<dcomplex>(dcomplex ****,int,int,int,int);

template<typename T>
void zero_1d(T* M,int n1){
	int i;
	for(i=0;i<n1;i++)
		M[i]=T(0);
}
template void zero_1d<int>(int *,int);
template void zero_1d<float>(float *,int);
template void zero_1d<double>(double *,int);
template void zero_1d<icomplex>(icomplex *,int);
template void zero_1d<fcomplex>(fcomplex *,int);
template void zero_1d<dcomplex>(dcomplex *,int);

template<typename T>
void zero_2d(T** M,int n1,int n2){
	int i,j;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++){
			M[i][j]=T(0);
		}
}
template void zero_2d<int>(int **,int,int);
template void zero_2d<float>(float **,int,int);
template void zero_2d<double>(double **,int,int);
template void zero_2d<icomplex>(icomplex **,int,int);
template void zero_2d<fcomplex>(fcomplex **,int,int);
template void zero_2d<dcomplex>(dcomplex **,int,int);

template<typename T>
void zero_3d(T*** M,int n1,int n2,int n3){
	int i,j,k;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				M[i][j][k]=T(0);
}
template void zero_3d<int>(int ***,int,int,int);
template void zero_3d<float>(float ***,int,int,int);
template void zero_3d<double>(double ***,int,int,int);
template void zero_3d<icomplex>(icomplex ***,int,int,int);
template void zero_3d<fcomplex>(fcomplex ***,int,int,int);
template void zero_3d<dcomplex>(dcomplex ***,int,int,int);

template<typename T>
void zero_4d(T**** M,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					M[i][j][k][l]=T(0);
}
template void zero_4d<int>(int ****,int,int,int,int);
template void zero_4d<float>(float ****,int,int,int,int);
template void zero_4d<double>(double ****,int,int,int,int);
template void zero_4d<icomplex>(icomplex ****,int,int,int,int);
template void zero_4d<fcomplex>(fcomplex ****,int,int,int,int);
template void zero_4d<dcomplex>(dcomplex ****,int,int,int,int);

template<typename T>
void free_1d(T* M){
	delete[] M;
}
template void free_1d<int>(int *);
template void free_1d<float>(float *);
template void free_1d<double>(double *);
template void free_1d<icomplex>(icomplex *);
template void free_1d<fcomplex>(fcomplex *);
template void free_1d<dcomplex>(dcomplex *);

template<typename T>
void free_2d(T** M,int n1){
	int i;
	for(i=0;i<n1;i++)
		delete[] M[i];
	delete[] M;
}
template void free_2d<int>(int **,int);
template void free_2d<float>(float **,int);
template void free_2d<double>(double **,int);
template void free_2d<icomplex>(icomplex **,int);
template void free_2d<fcomplex>(fcomplex **,int);
template void free_2d<dcomplex>(dcomplex **,int);

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
template void free_3d<int>(int ***,int,int);
template void free_3d<float>(float ***,int,int);
template void free_3d<double>(double ***,int,int);
template void free_3d<icomplex>(icomplex ***,int,int);
template void free_3d<fcomplex>(fcomplex ***,int,int);
template void free_3d<dcomplex>(dcomplex ***,int,int);

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
template void free_4d<int>(int ****,int,int,int);
template void free_4d<float>(float ****,int,int,int);
template void free_4d<double>(double ****,int,int,int);
template void free_4d<icomplex>(icomplex ****,int,int,int);
template void free_4d<fcomplex>(fcomplex ****,int,int,int);
template void free_4d<dcomplex>(dcomplex ****,int,int,int);

template<typename T>
void copy_1d(T* M1,T* M2,int n1){
	int i;
	for(i=0;i<n1;i++)
		M2[i]=M1[i];
		
}
template void copy_1d<int>(int *,int *,int);
template void copy_1d<float>(float *,float *,int);
template void copy_1d<double>(double *,double *,int);
template void copy_1d<icomplex>(icomplex *,icomplex *,int);
template void copy_1d<fcomplex>(fcomplex *,fcomplex *,int);
template void copy_1d<dcomplex>(dcomplex *,dcomplex *,int);

template<typename T>
void copy_2d(T** M1,T** M2,int n1,int n2){
	int i,j;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			M2[i][j]=M1[i][j];
}
template void copy_2d<int>(int **,int **,int,int);
template void copy_2d<float>(float **,float **,int,int);
template void copy_2d<double>(double **,double **,int,int);
template void copy_2d<icomplex>(icomplex **,icomplex **,int,int);
template void copy_2d<fcomplex>(fcomplex **,fcomplex **,int,int);
template void copy_2d<dcomplex>(dcomplex **,dcomplex **,int,int);

template<typename T>
void copy_3d(T*** M1,T*** M2,int n1,int n2,int n3){
	int i,j,k;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				M2[i][j][k]=M1[i][j][k];
}
template void copy_3d<int>(int ***,int ***,int,int,int);
template void copy_3d<float>(float ***,float ***,int,int,int);
template void copy_3d<double>(double ***,double ***,int,int,int);
template void copy_3d<icomplex>(icomplex ***,icomplex ***,int,int,int);
template void copy_3d<fcomplex>(fcomplex ***,fcomplex ***,int,int,int);
template void copy_3d<dcomplex>(dcomplex ***,dcomplex ***,int,int,int);

template<typename T>
void copy_4d(T**** M1,T**** M2,int n1,int n2,int n3,int n4){
	int i,j,k,l;
	for(i=0;i<n1;i++)
		for(j=0;j<n2;j++)
			for(k=0;k<n3;k++)
				for(l=0;l<n4;l++)
					M2[i][j][k][l]=M1[i][j][k][l];
}
template void copy_4d<int>(int ****,int ****,int,int,int,int);
template void copy_4d<float>(float ****,float ****,int,int,int,int);
template void copy_4d<double>(double ****,double ****,int,int,int,int);
template void copy_4d<icomplex>(icomplex ****,icomplex ****,int,int,int,int);
template void copy_4d<fcomplex>(fcomplex ****,fcomplex ****,int,int,int,int);
template void copy_4d<dcomplex>(dcomplex ****,dcomplex ****,int,int,int,int);

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
template void read_1d<int>(char *,int *,int);
template void read_1d<float>(char *,float *,int);
template void read_1d<double>(char *,double *,int);
template void read_1d<icomplex>(char *,icomplex *,int);
template void read_1d<fcomplex>(char *,fcomplex *,int);
template void read_1d<dcomplex>(char *,dcomplex *,int);

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
template void read_2d<int>(char *,int **,int,int);
template void read_2d<float>(char *,float **,int,int);
template void read_2d<double>(char *,double **,int,int);
template void read_2d<icomplex>(char *,icomplex **,int,int);
template void read_2d<fcomplex>(char *,fcomplex **,int,int);
template void read_2d<dcomplex>(char *,dcomplex **,int,int);

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
template void read_3d<int>(char *,int ***,int,int,int);
template void read_3d<float>(char *,float ***,int,int,int);
template void read_3d<double>(char *,double ***,int,int,int);
template void read_3d<icomplex>(char *,icomplex ***,int,int,int);
template void read_3d<fcomplex>(char *,fcomplex ***,int,int,int);
template void read_3d<dcomplex>(char *,dcomplex ***,int,int,int);

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
template void read_4d<int>(char *,int ****,int,int,int,int);
template void read_4d<float>(char *,float ****,int,int,int,int);
template void read_4d<double>(char *,double ****,int,int,int,int);
template void read_4d<icomplex>(char *,icomplex ****,int,int,int,int);
template void read_4d<fcomplex>(char *,fcomplex ****,int,int,int,int);
template void read_4d<dcomplex>(char *,dcomplex ****,int,int,int,int);

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
template void write_1d<int>(char *,int *,int);
template void write_1d<float>(char *,float *,int);
template void write_1d<double>(char *,double *,int);
template void write_1d<icomplex>(char *,icomplex *,int);
template void write_1d<fcomplex>(char *,fcomplex *,int);
template void write_1d<dcomplex>(char *,dcomplex *,int);

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
template void write_2d<int>(char *,int **,int,int);
template void write_2d<float>(char *,float **,int,int);
template void write_2d<double>(char *,double **,int,int);
template void write_2d<icomplex>(char *,icomplex **,int,int);
template void write_2d<fcomplex>(char *,fcomplex **,int,int);
template void write_2d<dcomplex>(char *,dcomplex **,int,int);

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
template void write_3d<int>(char *,int ***,int,int,int);
template void write_3d<float>(char *,float ***,int,int,int);
template void write_3d<double>(char *,double ***,int,int,int);
template void write_3d<icomplex>(char *,icomplex ***,int,int,int);
template void write_3d<fcomplex>(char *,fcomplex ***,int,int,int);
template void write_3d<dcomplex>(char *,dcomplex ***,int,int,int);

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
template void write_4d<int>(char *,int ****,int,int,int,int);
template void write_4d<float>(char *,float ****,int,int,int,int);
template void write_4d<double>(char *,double ****,int,int,int,int);
template void write_4d<icomplex>(char *,icomplex ****,int,int,int,int);
template void write_4d<fcomplex>(char *,fcomplex ****,int,int,int,int);
template void write_4d<dcomplex>(char *,dcomplex ****,int,int,int,int);

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
template void write_2d_app<int>(char *,int **,int,int,int,int);
template void write_2d_app<float>(char *,float **,int,int,int,int);
template void write_2d_app<double>(char *,double **,int,int,int,int);
template void write_2d_app<icomplex>(char *,icomplex **,int,int,int,int);
template void write_2d_app<fcomplex>(char *,fcomplex **,int,int,int,int);
template void write_2d_app<dcomplex>(char *,dcomplex **,int,int,int,int);

template<typename T>
float mod(T z){
	return sqrt(pow(z.real(),2)+pow(z.imag(),2));
}
template float mod<icomplex>(icomplex);
template float mod<fcomplex>(fcomplex);
template float mod<dcomplex>(dcomplex);

template<typename T>
T conjg(T z){
	T c;
	c.real()=z.real();
	c.imag()=-z.imag();
	return c;
}
template icomplex conjg<icomplex>(icomplex);
template fcomplex conjg<fcomplex>(fcomplex);
template dcomplex conjg<dcomplex>(dcomplex);

/*
template<typename T>
void add_complex_1d(T* M1,T* M2,int* n1,MPI_Datatype *dtype){
	int i;
	for(i=0;i<*n1;i++)
		M2[i]+=M1[i];
}
template void add_complex_1d<int>(int *,int *,int *,MPI_Datatype *);
template void add_complex_1d<float>(float *,float *,int *,MPI_Datatype *);
template void add_complex_1d<double>(double *,double *,int *,MPI_Datatype *);
template void add_complex_1d<icomplex>(icomplex *,icomplex *,int *,MPI_Datatype *);
template void add_complex_1d<fcomplex>(fcomplex *,fcomplex *,int *,MPI_Datatype *);
template void add_complex_1d<dcomplex>(dcomplex *,dcomplex *,int *,MPI_Datatype *);
*/
