#include "terrainMesh.h"

// Class contructor
// Args:
// 		width: width of the terrain in OpenGL units
// 		height: height of the terrain in OpenGL units
// 		originType: 'c' for origin in middle of terrain, 's' for corner
TerrainMesh::TerrainMesh(int _width, int _height, int tHeight, char _originType) {
	meshWidth = _width;
	meshHeight = _height;
	terrainHeight = tHeight;
	originType = _originType;

    meshData = nullptr;
    heightMap = nullptr;

    correction = false;
    coloring = false;

    //num_colors = 8;
    //colors = (t_color*)malloc(sizeof(t_color)*NUM);

    // First red color
    colors[0].r = 255;
    colors[0].g = 115;
    colors[0].b = 115;
    // Second yellow color
    colors[1].r = 255;
    colors[1].g = 255;
    colors[1].b = 115;
    // Fourth pink color
    colors[2].r = 255;
    colors[2].g = 115;
    colors[2].b = 199;
    // Third blue color
    colors[3].r = 115;
    colors[3].g = 253;
    colors[3].b = 255;
    /*
    // First red color
    colors[4].r = 255;
    colors[4].g = 115;
    colors[4].b = 115;
    // Second yellow color
    colors[5].r = 255;
    colors[5].g = 255;
    colors[5].b = 115;
    // Fourth pink color
    colors[6].r = 255;
    colors[6].g = 115;
    colors[6].b = 199;
    // Third blue color
    colors[7].r = 115;
    colors[7].g = 253;
    colors[7].b = 255;
    */

}

// Moves the terrain mesh, offseting in the z axis.
// this achives the effect of scrolling, and the new vaules of the
// height map are generated
void TerrainMesh::Move() {
    if(heightMap != nullptr) {
        heightMap->Offset();
        Generate();
    }
}

// Method that generates the actual mesh of the terrain
void TerrainMesh::Generate() {
    // Check if the mesh was done previously
    if(meshData != nullptr) {
        delete meshData;
    } else {
        terrainHeight = 40;
	    heightMap = new HeightMap(0.03, 4, meshWidth, meshHeight, terrainHeight);
	    heightMap->Generate(1, 4, 0.5, 2.0);
    }
	meshData = new TMeshData;


    // Sets the offset depending on the pivot selected
	if(originType == 'c') {
		offsetX = (meshWidth - 1) / -2.0;
		offsetZ = (meshHeight - 1) / -2.0;
	}

	int vertexCount = 0;
    // Loops through all the points in the terrrain in order to join
    // the vertices and creates triangles
	for(int y = 0; y < meshHeight; y++) {
		for(int x = 0; x < meshWidth; x++) {
			float vertexHeight = heightMap->GetValue(x, y) * terrainHeight;
			meshData->AddVertex(offsetX + x, vertexHeight, offsetZ + y);
            // Creates both triangles for each square
            // Makes sure that the order of the vertices is counter clockwise
			if(x < meshWidth - 1 && y < meshHeight - 1) {
				meshData->AddTriangle(vertexCount, vertexCount + meshWidth + 1, vertexCount+meshWidth);
				meshData->AddTriangle(vertexCount + meshWidth + 1, vertexCount, vertexCount+1);
			}

			vertexCount++;
		}
	}


	for(int i = 0; i < meshData->triangles.size()-3; i+=3) {
        Vertex v1 = meshData->vertices[meshData->triangles[i]];
        Vertex v2 = meshData->vertices[meshData->triangles[i+1]];
        Vertex v3 = meshData->vertices[meshData->triangles[i+2]];

        meshData->normals.push_back(Vertex(Vertex::CalculateNormal(v1, v2, v3)));
        meshData->visibility.push_back(true);
    }
}

// Method that returns the height of some position int the world
// Args:
// 		x: x coordinate in the world
// 		z: z coordinate in the world
float TerrainMesh::GetHeight(float x, float z) {
	float res = 0.0;

	x -= offsetX;
	z -= offsetZ;

	int xr = round(x);
	int zr = round(z);

    // Makes sure that the coordinate is insede the terrain
	if(xr > 0 && xr < meshWidth && zr > 0 && zr < meshHeight) {
		res = heightMap->GetValue(xr, zr) * terrainHeight;
	}

	return res;
}

// Checks wich faces of the terrain are visible
void TerrainMesh::CheckVisibility(Vertex cam) {
    float visible;
    cam.Normalize();
	for(int i = 0; i < meshData->normals.size(); i++) {
        Vertex normal = meshData->normals[i];
        visible = normal.x*cam.x + normal.y*cam.y + normal.z*cam.z;

        if(visible > 0) {
            meshData->visibility[i] = true;
        } else {
            meshData->visibility[i] = false;
        }
    }
}

// Interpolates between two RGB colors
t_color interpolateColors(t_color a, t_color b, float fraction) {
    t_color res;

    res.r = (b.r - a.r)*fraction + a.r;
    res.g = (b.g - a.g)*fraction + a.g;
    res.b = (b.b - a.b)*fraction + a.b;

    return res;
}

// Obtains the color of the height sended, this is done
// by interpolating colors depending on the height range
t_color TerrainMesh::GetColor(float height) {
    // Obtain the fraction, color range, and floor index
    double fracc = height / terrainHeight;
    double color_range = terrainHeight / NUM_C;
    int c_index = floor(fracc * NUM_C);

    // the obtains the relative height and fraction value
    height -= c_index * color_range;
    fracc = height / color_range;

    // Assures that there is no overflow in the indexes
    if(c_index == num_colors-1)
        c_index = num_colors-2;

    // function that interpolates the respective colors
    t_color res = interpolateColors(colors[c_index], colors[c_index+1], fracc);
    return res;
}

// Method that draws the terrain mesh
void TerrainMesh::DrawTerrain() {
    int index;
	for(int i = 0; i < meshData->triangles.size()-3; i+=3) {
        index = i / 3;
        if(meshData->visibility[index]) {
        if(correction) {
        // First draws by filling the triangle with black
        for(int v = 0; v < 3; v++) {
			Vertex vertex = meshData->vertices[meshData->triangles[i+v]];
			if(v == 0) {
				glColor4f(0.0, 0.0, 0.0, 0.0);
				//glBegin(GL_LINE_STRIP);
				glBegin(GL_TRIANGLES);
			
			}
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
        }

        // The it also draws the terrain with wireframe
		for(int v = 0; v < 3; v++) {
			Vertex vertex = meshData->vertices[meshData->triangles[i+v]];
			if(v == 0) {
                // Gets the current color depending on the height of the terrain
                t_color c = GetColor(vertex.y);
                if(coloring)
                    glColor3f(c.r/255.0, c.g/255.0, c.b/255.0);
                else
                    glColor3f(1.0, 1.0, 1.0);

				glBegin(GL_LINE_STRIP);
			
			}
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
        }
	}
}

// Adds a vertex to the mesh data of the terrain
void TMeshData::AddVertex(float x, float y, float z) {
	vertices.push_back(Vertex(x, y, z));
}

// Adds atriangle to the mesh data of the terrain
void TMeshData::AddTriangle(int a, int b, int c) {
	triangles.push_back(a);
	triangles.push_back(b);
	triangles.push_back(c);
}

