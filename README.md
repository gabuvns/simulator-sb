# Custom Machine Code Runtime Simulator 
Simulator created for "Basic Software" class at University of Brasilia.
There is also an assembler avaiable at [assembler](https://github.com/gabuvns/assembler-sb) and one [linker](https://github.com/gabuvns/linker-sb).

Simulador desenvolvido para a disciplina de Software Básico na Universidade de Brasília.
Existe também um [montador](https://github.com/gabuvns/assembler-sb) disponível e um [ligador](https://github.com/gabuvns/linker-sb).

## Getting Started
This program executes the code generated with this [linker](https://github.com/gabuvns/linker-sb).
Just follow along to get the project running

## Prerequisites
Pretty simple, you only need: 

```
g++ (GCC)
gnu make (opt)
```
(Your version of g++ must support c++17, if your are using gcc 5.0 or newer, you should be good)

## Compiling

#### First option is to simply use make

```
make 
```

#### Or you can compile manually:

```
g++ -o simulator ./src/main.cpp ./src/simulator.cpp -std=gnu++1z
```

## Usage 
This program takes the name of the file to be executed.

```
./simulator <inputFileName>
./simulator inputFile.obj
```
## Começando :brazil:
Este montador suporta as instruções disponíveis na tabela disponível no início do README.

## Pré-requisitos
Precisamos apenas de:

```
g++ (GCC)
gnu make (opt)
```
(A versão do GCC deve ter suporte para c++17, se sua versão é superior ao gcc 5.0, fique tranquilo.)

## Compilando

#### A primeira opção é simplesmente utilizar o comando make

```
make 
```

#### Ou então pode-se compilar manualmente

```
g++ -o simulator ./src/main.cpp ./src/simulator.cpp -std=gnu++1z
```

## Uso 
O programa recebe somente o nome do programa a ser executado
```
./simulator <inputFileName> 
./simulator inputFile.obj 
```

## Author

* **Carlos Gabriel Vilas Novas Soares** - [Github](https://github.com/gabuvns)
