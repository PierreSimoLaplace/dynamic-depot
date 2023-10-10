#include"gemmcpu.h"

/* API:Matrix Multiplication worked by CPU */
void matMulCpu(const Matrix A,const Matrix B,Matrix C){
	for(register int ih=0;ih<A.height;ih++){
		for(register int iw=0;iw<B.width;iw++){
			register float sum=0;
			for(register int ik=0;ik<A.width;ik++)
				sum+=A.elements[ih*A.stride+ik]*B.elements[ik*B.stride+iw];
			C.elements[ih*C.stride+iw]=sum;
		}
	}
}
