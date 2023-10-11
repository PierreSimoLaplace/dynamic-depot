# fftgpu
**Attention:This version is developed based on linux.**  
Header file are placed in document `include` and you can learn about how to use API for
executing `fftgpu` conveniently and rapidly.Because cuda don't support c++ `<complex>` in kernel function,
i create a `complexcuda` class suitable for kernel function and overload basic operator including basic 
arithmetic operator,basic assigning operator and basic type-cast operator.All details are listed in 
`complexcuda.cu` and `complexcuda.h`.  
Compile format:  
`nvcc demo.cu -I./include -I./ -L./lib64 -lcudart -lfftgpu -o demo.out`
