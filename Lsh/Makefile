CC=g++
CXXFLAGS = -g -Wall
CPPFLAGS = -I eigen
LDLIBS   = -lm
DEPS = Hash.h		LSH.h		../Functions_for_both_algorithms/Calculate_Distances.h		../Functions_for_both_algorithms/h_Function.h	../Functions_for_both_algorithms/Modulos.h			../Functions_for_both_algorithms/Quicksort.h		../Functions_for_both_algorithms/Reading.h		../Functions_for_both_algorithms/Writing.h
OBJ = mainLSH.o	Hash.o	LSH.o	../Functions_for_both_algorithms/Calculate_Distances.o	../Functions_for_both_algorithms/h_Function.o	../Functions_for_both_algorithms/Modulos.o	../Functions_for_both_algorithms/Quicksort.o	../Functions_for_both_algorithms/Reading.o		../Functions_for_both_algorithms/Writing.o

%o.: %.c ${DEPS}
	$(CC) -c -O3 -o $@ $< $(CXXFLAGS)
lsh: $(OBJ)
	$(CC) -O3 -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.o lsh
