CXXFLAGS = -std=c++0x -c -g -O2
OMP = g++
OMPFLAGS = -fopenmp -O2
MPI = mpic++
MPIFLAGS = -O2

all: driver

driver : Driver.o Node.o
	$(CXX) $^ -o $@

clean:
	$(RM) *.o
	$(RM) .depend

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
