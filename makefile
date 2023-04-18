hausdorff: main.o nifti1_io.o znzlib.o image.o octree.o panic.o
	g++ -std=c++11 nifti1_io.o znzlib.o octree.o image.o main.o panic.o -o hausdorff
	make tidy

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

nifti1_io.o: 
	g++ -std=c++11 -c utility/nifti/nifti1_io.c

znzlib.o: 
	g++ -std=c++11 -c utility/nifti/znzlib.c

octree.o: octree/octree.cpp octree/octree.h
	g++ -std=c++11 -c octree/octree.cpp

image.o: utility/image.h utility/image.cpp
	g++ -std=c++11 -c utility/image.cpp

panic.o: utility/panic.h utility/panic.cpp
	g++ -std=c++11 -c utility/panic.cpp

tidy:
	rm -f *.o
	
clean:
	rm -f *.o octree
