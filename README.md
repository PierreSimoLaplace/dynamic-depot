# gemm
**Attention:This version is developed based on linux.**  
Header file are placed in document `include` and you can learn about how to use API for
executing `gemmgpu gemmcpu` and opening array with dynamic memory conveniently and rapidly.
I import `cublas_v2.h` to compare computation efficiency,so you have to link cublas dynamic 
library when compiling.
Compile format:  
`nvcc demo.cu -I./include -L./lib64 -lcudart -lcublas -lgemmcpu -lgemmgpu -o demo.out`
