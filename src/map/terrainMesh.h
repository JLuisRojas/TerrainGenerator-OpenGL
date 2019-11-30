#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include "heightMap.h"
#include "../objects.h"
#include <vector>
#include <stdlib.h>
#include <GLUT/glut.h>

#define NUM_C 4

typedef struct {
    int r;
    int g;
    int b;
}t_color;

t_color interpolateColors(t_color a, t_color b);

// Class that stores the information about the terrain mesh
class TMeshData {
	public:
		std::vector<Vertex> vertices;				// Vertices of the mesh
		std::vector<int> triangles;					// Index of the triangle vertices
        std::vector<Vertex> normals;
        std::vector<bool> visibility;

		//TMeshData(int meshWidth, int meshHeight);
		void AddVertex(float x, float y, float z);
		void AddTriangle(int a, int b, int c);
};

// Class that generates and displays the terrain mesh
// this class is also in charge of acceding the information about the terrain
// **this class is up to change if different behavior of the terrain is desired**
class TerrainMesh {
	public:
		int meshWidth;								// Terrain mesh width
		int meshHeight;								// Terrain mesh height
		int terrainHeight;							// Terrain height
		char originType;
		Vertex *origin;								// Terrain origin
		HeightMap *heightMap;						// Height map that generates mesh

        // Control variables
        bool correction;
        bool coloring;

		TerrainMesh(int _width, int _height,		// Constructor of the terrain class
					int tHeight, char _originType='c');

        void Move();
		void Generate();							// Starts generating the mesh
        void CheckVisibility(Vertex cam);
		void DrawTerrain();							// Draws the terrain mesh
		float GetHeight(float x, float z);

	private:
        t_color GetColor(float height);
        t_color colors[NUM_C];
        int num_colors;
		TMeshData *meshData;
		float offsetX;
		float offsetZ;

};

#endif
