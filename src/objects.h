#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <GLUT/glut.h>
#include "utils/transformations.h"

class Vertex {
	public:
		static Vertex *zero;
		float x;
		float y;
		float z;

		Vertex(float x, float y, float z);
		Vertex();
		Vertex(Vertex *v);
		void Print();
		double Magnitude();
        void Normalize();
        double Dot(Vertex other);

		// Operator overloading
		Vertex* operator+(const Vertex &b);
		Vertex* operator-(const Vertex &b);
		Vertex* operator*(const Vertex &b);
		Vertex* operator*(const float &b);
		Vertex* operator-();
		bool operator==(const Vertex &b);

		static Vertex* UnitVectorXZ(double teta);
		static Vertex* CrossProduct(Vertex a, Vertex b);
        static Vertex* CalculateNormal(Vertex v1, Vertex v2, Vertex v3);
};

class Face {
	public:
		std::vector<int> vertices; // Lista con indices de vertices
        Vertex *normal;
        float ilumination = 0.0;
        bool visible = true;
        float key;

		// Metodo agrega un indice a lista de vertices
		void Add(int i);
		void Print();
        void CalculateIlum(Vertex cam);
        void CalculateKey(std::vector<Vertex> _vertices);

        // Operators
        bool operator<(const Face& str) const;
};

class Object {
	public:
		std::string name;			// Name of the obj
		std::vector<Vertex> vertices;	// List of vertices
		std::vector<Face> faces;		// List of faces
		Vertex *pivot;

		Vertex *rotation;				// Reference to the current rotation
		Vertex *position;

		Object(std::string _name);
		Object(Object *other);
		void AddVertex(Vertex v);
		void AddFace(Face f);
        void CalculateNormals();
        void CalculateIluminations(Vertex cam);
        void CheckVisibility(Vertex cam);
        void SortFaces();
		void Print();
		void DrawWireframe();
        void Draw();
		void SetPivot(int index);
		void SetPivot(Vertex point);
		void MoveTo(Vertex point);
		void Scale(float ratio);
		void Scale(float sx, float sy, float sz);
		void Rotate(double angle, char axis);
		void RotateTo(double angle, char axis);
		void ApplyT(Transformation t);
		void ApplyT(std::vector<Transformation> trans);
		Vertex GetCentroid();

	private:
		void ApplyHCoord(float h_coord[4], Vertex *v);
		float* ToHCoord(Vertex v);
};

std::vector<std::string> parseLine(std::string str, std::string delimeter, int start);
std::vector<Object> readObjFile(std::string path);

#endif
