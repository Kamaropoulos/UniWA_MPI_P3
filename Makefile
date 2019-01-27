MPICPP=mpic++
MPIEXEC=mpiexec -n 4
CPPFLAGS=-Wall -g3

all: dirs bin/main

run: bin/main
	$(MPIEXEC) ./bin/main

# .PHONY: demo
# demo: bin/main
# 	$(MPIEXEC) ./bin/main testfile.in

dirs:
	mkdir -p obj/test obj/lib bin

bin/main: obj/NetworkParameters.o obj/Topology.o obj/NetworkParameters.o obj/SumCartesian2DSendRecv.o dirs
	$(MPICPP) $(CPPFLAGS) -o bin/main src/main.cpp obj/NetworkParameters.o obj/Topology.o obj/IO.o obj/SumCartesian2DSendRecv.o

obj/Topology.o: src/Topology.cpp obj/NetworkParameters.o obj/IO.o dirs
	$(MPICPP) $(CPPFLAGS) -o obj/Topology.o -c src/Topology.cpp

obj/IO.o: src/IO.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/IO.o -c src/IO.cpp

obj/NetworkParameters.o: src/NetworkParameters.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/NetworkParameters.o -c src/NetworkParameters.cpp

obj/SumCartesian2DSendRecv.o: src/SumCartesian2DSendRecv.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/SumCartesian2DSendRecv.o -c src/SumCartesian2DSendRecv.cpp

.PHONY: clean
clean:
	rm -rf bin obj