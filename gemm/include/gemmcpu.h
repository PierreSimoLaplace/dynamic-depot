#ifndef _GEMMCPU_H
#define _GEMMCPU_H

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

/* API:Matrix Multiplication worked by CPU */
void matMulCpu(const Matrix A,const Matrix B,Matrix C);

#endif
