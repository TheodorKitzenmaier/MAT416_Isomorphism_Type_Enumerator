all: isomorphism graph
	g++ iso_calculator.cpp isomorphism.o graph.o -o iso_calculator

testing: isomorphism graph
	g++ testing.cpp isomorphism.o graph.o -o testing

isomorphism: graph
	g++ -c isomorphism.cpp -o isomorphism.o

graph:
	g++ -c graph.cpp -o graph.o

clean:
	rm -f *.o
