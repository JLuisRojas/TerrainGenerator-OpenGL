#ifndef CENTINEL_H
#define CENTINEL_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "objects.h"
#include "utils/curves.h"
#include "utils/timer.h"
#include "map/terrainMesh.h"

#define PI 3.14159265
#define DURATION 10000.0

// Class that defines the centinel: object that will circulate around the map and
// actualize its height depending on the terrain
class Centinel {
	public:
		Centinel(float _radius, float _separation, int _segments, TerrainMesh *tRef);
		// Attributes
		float radius;
		float separation;				// The separation to the terrain
		TerrainMesh *terrain;		// Reference to the terrain object
		std::vector<BezierTrajectory> path;	// the path list
		int segments;				// Number of segements in the 
		double angleRad;			// Segments angle
		double curveValue;			// the value calculated for p2, p3
		// Angulo rad = (2*PI) / n
		// Curve dist = (4/3) * tan(PI / (2*n))
		// Methods
		void CalculatePath();
		void DrawPath();
		void Update();
		Vertex CamaraOffset(float delta);
		Vertex ModelPos();


	private:
		bool initPos;				// To check if there is a past position ref
		Vertex *pastP;				// Reference to the past position
		Vertex *dirV;				// Current movment direction vector
		Timer *timer;
		float segmentDuration;
		Object *model;
		void CalculateBPoints(double teta, Vertex &a, Vertex &b, int dir);
};

#endif
