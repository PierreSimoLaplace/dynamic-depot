LIBCODE=./src/gpukernel.cu
LIBOBJ=./src/gpukernel.o
LIBSO=./lib64/libfftgpu.so
MAINCODE=demo.cu
MAINOBJ=demo.out
LSF=qsub.lsf

compile:$(MAINCODE)
	nvcc $(MAINCODE) -I./include -I./ -L./lib64 -lcudart -lfftgpu -o $(MAINOBJ)

libso:$(LIBOBJ)
	nvcc -Xcompiler -shared $(LIBOBJ) -o $(LIBSO)
$(LIBOBJ):$(LIBCODE)
	nvcc -Xcompiler -fpic -c $(LIBCODE) -I./include -I./ -o $(LIBOBJ)

run:
	bsub<$(LSF)

.PHONY:clean
clean:
	rm ./error.*.txt ./out.*.txt ./$(MAINOBJ)

.PHONY:cleanlib
cleanlib:
	rm $(LIBOBJ) $(LIBSO)
