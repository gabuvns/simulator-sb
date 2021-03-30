assembler: ./src/main.cpp  ./src/simulator.cpp
	g++ -o simulator ./src/main.cpp ./src/simulator.cpp -std=gnu++1z