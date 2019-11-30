# Procedural Terrain Generation

<img src="assets/demo4.gif">

Procedural terrain generation using Perlin noise, using OpenGL and GLUT

## Implementation
Details about the implementation can be found [here.](docs/design_document.pdf) We are using Perlin noise to generate the height map, from which we then generate the terrain mesh.

## Requirements
It has been tested only on MacOS, but it should work on Ubuntu also. (check the includes for OpenGL and GLUT)
```
OpenGL <= 2.0
GLUT
```
To compile:
```
$ cd src/
$ make
$ ./main
```

## Resources
The following are great resources in wich the project was based on:

[Procedural Landmass Generation (E01: Introduction)](https://www.youtube.com/watch?v=wbpMiKiSKm8)

[Perlin Noise in C](https://gist.github.com/nowl/828013)
