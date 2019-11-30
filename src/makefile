all: main

main: main.o xWing.o objects.o timer.o drawing.o curves.o transformations.o heightMap.o terrainMesh.o
	g++ main.o objects.o timer.o xWing.o drawing.o curves.o transformations.o heightMap.o terrainMesh.o -o main -framework GLUT -framework OpenGL -w

main.o: main.cpp
	g++ -c main.cpp -w

xWing.o: xWing.cpp
	g++ -c xWing.cpp -w

objects.o: objects.cpp
	g++ -c objects.cpp -w

timer.o: utils/timer.cpp
	g++ -c utils/timer.cpp -w

drawing.o: utils/drawing.cpp
	g++ -c utils/drawing.cpp

curves.o: utils/curves.cpp
	g++ -c utils/curves.cpp

transformations.o: utils/transformations.cpp
	g++ -c utils/transformations.cpp -w

heightMap.o: map/heightMap.cpp
	g++ -c map/heightMap.cpp -w

terrainMesh.o: map/terrainMesh.cpp
	g++ -c map/terrainMesh.cpp -w
