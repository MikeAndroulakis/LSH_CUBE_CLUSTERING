CC=g++
CXXFLAGS = -g -Wall
CPPFLAGS = -I eigen
LDLIBS   = -lm
DEPS = Clustering.h	ClassicClustering.h	LshClustering.h	HypercubeClustering.h	ClusteringReading.h	ImageCollection.h	../Lsh/LSH.h	../Cube/Cube.h	../Cube/h_Function_Cube.h	../Cube/Cube_Struct.h	../Functions_for_both_algorithms/h_Function.h	../Functions_for_both_algorithms/Reading.h	../Functions_for_both_algorithms/Modulos.h	../Functions_for_both_algorithms/Calculate_Distances.h	../Functions_for_both_algorithms/Quicksort.h	../Functions_for_both_algorithms/Writing.h	../Lsh/Hash.h ../Cube/f_Function_Cube.h
OBJ = main_clustering.o Clustering.o	ClassicClustering.o	LshClustering.o	HypercubeClustering.o	ClusteringReading.o	ImageCollection.o	../Functions_for_both_algorithms/Calculate_Distances.o	../Lsh/LSH.o	../Cube/Cube.o	../Cube/h_Function_Cube.o	../Cube/Cube_Struct.o	../Functions_for_both_algorithms/h_Function.o	../Functions_for_both_algorithms/Reading.o	../Functions_for_both_algorithms/Modulos.o	../Functions_for_both_algorithms/Calculate_Distances.o	../Functions_for_both_algorithms/Quicksort.o	../Functions_for_both_algorithms/Writing.o	../Lsh/Hash.o	../Cube/f_Function_Cube.o

%o.: %.c ${DEPS}
	$(CC) -c -O3 -o $@ $< $(CXXFLAGS)
cluster: $(OBJ)
	$(CC) -O3 -o $@ $^ $(CXXFLAGS)
clean:
	rm -f *.o cluster
