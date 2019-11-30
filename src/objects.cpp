#include "objects.h"

Vertex* Vertex::zero = new Vertex();

// Constructor for Vertex Object, intializes all at 0.0
Vertex::Vertex() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

// Constructor for Vertex Object, intializes all at coordinates
// Args:
// 		_x: x coordinate
// 		_y: y coordinate
// 		_z: z coordinate
Vertex::Vertex(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

// Constructor for Vertex Object, that creates a vertex from a copy
// of other.
Vertex::Vertex(Vertex *v) {
	x = v->x;
	y = v->y;
	z = v->z;
}

// Obtain the dot product between the vertex and another
double Vertex::Dot(Vertex other) {
    return x*other.x + y*other.y + z*other.z;
}

// Method that obtains the magnitude of the vertex
double Vertex::Magnitude() {
	return sqrt(x*x + y*y + z*z);
}

// Normalizes the componentes of the vertex, by dividing
// by the vertex magnitude
void Vertex::Normalize() {
    double magnitude = Magnitude();
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

// Method that prints the vertex coordiantes
void Vertex::Print() {
	std::cout << "Vertex " << "\n";
	std::cout << "x: " << x << " ";
	std::cout << "y: " << y << " ";
	std::cout << "z: " << z << "\n";
}

// Operation overload
Vertex* Vertex::operator+(const Vertex &b) {
	float xf, yf, zf;
	xf = x + b.x;
	yf = y + b.y;
	zf = z + b.z;

	return new Vertex(xf, yf, zf);
}
Vertex* Vertex::operator-(const Vertex &b) {
	float x, y, z;
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;

	return new Vertex(x, y, z);
}
Vertex* Vertex::operator*(const Vertex &b) {
	float x, y, z;
	x = x + b.x;
	y = y + b.y;
	z = z + b.z;

	return new Vertex(x, y, z);
}
Vertex* Vertex::operator*(const float &b) {
	return new Vertex(x*b, y*b, z*b);
}
Vertex* Vertex::operator-() {
	return new Vertex(-x, -y, -z);
}
bool Vertex::operator==(const Vertex &b) {
	if(x == b.x && y == b.y && z == b.z) {
		return true;
	}
	else
		return false;
}

// Returns a unit vector wiht respect an angle
// Args:
// 		teta: angle formed in radians
Vertex* Vertex::UnitVectorXZ(double teta) {
	double x = cos(teta);
	double z = sin(teta);

	Vertex* v = new Vertex(x, 0.0, z);
	return v;
}

// Method that computs the cross prodcut AxB between two vertices
// Args:
// 		a: Vector A
// 		b: Vector B
Vertex* Vertex::CrossProduct(Vertex a, Vertex b) {
	float x = a.y*b.z - a.z*b.y;
	//float y = a.x*b.z - a.z*b.x;
	float y = a.z*b.x - a.x*b.z;
	float z = a.x*b.y - a.y*b.x;

	return new Vertex(x, y, z);
}

// Calculates the normal with 3 vertices, taking in consideration that the
// vertices are in counter clockwise direction
// Return:
//      normal: a vertex with the normal values
Vertex* Vertex::CalculateNormal(Vertex v1, Vertex v2, Vertex v3) {
    Vertex r1;
    Vertex r2;

    // R1 = (V2 - V1)
    r1.x = v2.x - v1.x;
    r1.y = v2.y - v1.y;
    r1.z = v2.z - v1.z;

    // R2 = (V3 - V1)
    r2.x = v3.x - v1.x;
    r2.y = v3.y - v1.y;
    r2.z = v3.z - v1.z;
        
    // calculates the cross product
    return Vertex::CrossProduct(r1, r2);
}

// Adds the index of a vertex to the face vertices vector
void Face::Add(int i) {
	vertices.push_back(i);
}

// Prints the indices of the face vertices
void Face::Print() {
	std::cout << "Face: ";
	for(int i = 0; i < vertices.size(); i++)
		std::cout << vertices[i] << " ";
	std::cout << "\n";
}

// Method that calculates the ilumination of the face
void Face::CalculateIlum(Vertex cam) {
    float k_a = 0.65; // Ambient reflection
    float k_d = 0.35; // Diffuse reflection
    float k_s = 0.8;
    float I_a = 1.0; // Intensity of ambient light
    float I_l = 0.9;
    float n = 10;
    // The light source direction
    Vertex light = Vertex(1, 1, -1);

    Vertex R = Vertex(normal);
    float a = normal->Dot(light) * 2;
    R.x *= a;
    R.y *= a;
    R.z *= a;
    R.x -= light.x;
    R.y -= light.y;
    R.z -= light.z;

    R.Normalize();
    light.Normalize();
    cam.Normalize();
    
    // Obtains the illumination coeficient
    ilumination = (I_a * k_a) + (I_l * k_d * normal->Dot(light)) + (k_s*pow(R.Dot(cam), n));
    ilumination /= 2.0;
}

// Claculates the face key of the face to perform sorting, we select the
// z component of the nearest vertex of the face
// Args:
//      _vettices: vector containing all the vertices of the object
void Face::CalculateKey(std::vector<Vertex> _vertices) {
    int index, i;
    key = 100000000.0;
    for(i = 0; i < vertices.size(); i++) {
        index = vertices[i];
        if(_vertices[index].z < key) {
            key = _vertices[index].z;
        }
    }
}

// Operator that compaers the faces key value for sorting
bool Face::operator<(const Face& str) const {
    return (key < str.key);
}

// Calculates the normals of the object
void Object::CalculateNormals() {
    for(int i = 0; i < faces.size(); i++) {
        int v1 = faces[i].vertices[0];
        int v2 = faces[i].vertices[1];
        int v3 = faces[i].vertices[2];

        // calculates the cross product
        //faces[i].normal = Vertex::CrossProduct(r1, r2);
        faces[i].normal = Vertex::CalculateNormal(vertices[v1], vertices[v2], vertices[v3]);
        faces[i].normal->Normalize();
    }
}

void Object::CalculateIluminations(Vertex cam) {
    for(int i = 0; i < faces.size(); i++) {
        faces[i].CalculateIlum(cam);
    }
}


// Calculates the visible surfaces of the object
// Args:
//      cam: is the PRP of camera in the scene
void Object::CheckVisibility(Vertex cam) {
    cam.Normalize();

    float visible;
    for(int i = 0; i < faces.size(); i++) {
        visible =faces[i].normal->x*cam.x + faces[i].normal->y*cam.y + faces[i].normal->z*cam.z;

        if(visible > 0) {
            faces[i].visible = true;
        } else {
            faces[i].visible = false;
        }
    }
}

// Sorts the list faces for
void Object::SortFaces() {
    for(int i = 0; i < faces.size(); i++)
        faces[i].CalculateKey(vertices);

    std::sort(faces.begin(), faces.end());
}

// Constructor for the object Object
// Args:
// 		_name: name of the object
Object::Object(std::string _name) {
	name = _name;

	// intializes the pivot at (0, 0, 0)
	pivot = new Vertex();
	// Initializes the rotation to (0, 0, 0)
	rotation = new Vertex();
	position = new Vertex();
}

// Constructor that makes a copy of an object
Object::Object(Object *object) {
	int i;
	name = object->name;
	pivot = new Vertex(object->pivot);
	rotation = new Vertex(object->rotation);
	position = new Vertex(object->position);
	for(i = 0; i < object->vertices.size(); i++)
		vertices.push_back(object->vertices[i]);
	for(i = 0; i < object->faces.size(); i++)
		faces.push_back(object->faces[i]);
}

// Mehthod that adds a Vertex to the object
// Args:
// 		v: Vertex object to add:w
void Object::AddVertex(Vertex v) {
	vertices.push_back(v);
	SetPivot(GetCentroid());
    CalculateNormals();
}

// Method that adds a Face to the object
// Args:
// 		f: object face
void Object::AddFace(Face f) {
	faces.push_back(f);
}

// Method that prints the information about the object
void Object::Print() {
	std::cout << "Object: " << name << "\n";

	for(int i = 0; i < vertices.size(); i++)
			vertices[i].Print();

	for(int i = 0; i < faces.size(); i++)
			faces[i].Print();
}

// Method that draws a white wireframe of the object
void Object::DrawWireframe() {
	for(int f = 0; f < faces.size(); f++) {
		Face face = faces[f];
        if(face.visible) {
		    //glColor3f(1.0, 0.0, 0.0);
		    glColor3f(1.0, 1.0, 1.0);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.vertices.size(); v++) {
			    Vertex vertex = vertices[face.vertices[v]];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
        }
	}
}

// Method that draws the object, uses the face illumination
// to draw the illuminisity of the objct
void Object::Draw() {
    // Firts calculate the normal, and checks visibility
    CalculateNormals();
    for(int f = 0; f < faces.size(); f++) {
		Face face = faces[f];
        // Only draws if the face is visible
        if(face.visible) {
            //face.CalculateIlum();
		    glColor3f(face.ilumination, face.ilumination, face.ilumination);
		    //glColor3f(face.ilumination, 0.0, 0.0);
		    glBegin(GL_POLYGON);
		    for(int v = 0; v < face.vertices.size(); v++) {
			    Vertex vertex = vertices[face.vertices[v]];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();

            /*
            glColor3f(1.0, 0.0, 0.0);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.vertices.size(); v++) {
			    Vertex vertex = vertices[face.vertices[v]];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
            //*/
        }
	}
}

// Method that sets the pivot of the object to a vertex of the object
// Args:
// 		index: index of the vertex in the vertices vector.
void Object::SetPivot(int index) {
	if(index > 0 && index < vertices.size()) {
		delete pivot;
		pivot = new Vertex(vertices[index]);
	}
}

// Method that sets the pivot of the object to a vertex
// Args:
// 		point: vertex of the pivot
void Object::SetPivot(Vertex point) {
	delete pivot;
	pivot = new Vertex(&point);
}

// Method that calculates the centroid of an object
// Returns:
// 		centroid: Vertex with the coordinates of the centroid
Vertex Object::GetCentroid() {
	float avg_x, avg_y, avg_z;
	for(int i = 0; i < vertices.size(); i++) {
		avg_x += vertices[i].x;
		avg_y += vertices[i].y;
		avg_z += vertices[i].z;
	}

	avg_x /= vertices.size();
	avg_y /= vertices.size();
	avg_z /= vertices.size();

	return Vertex(avg_x, avg_y, avg_z);
}

// Method that applys a colum vector of homegenous coordinates, to the
// coordinates of the object.
// 		h_coord: 1d array of size 4 (x, y, z, 1)
void Object::ApplyHCoord(float h_coord[4], Vertex *v) {
	v->x = h_coord[0];
	v->y = h_coord[1];
	v->z = h_coord[2];
}

// Method that convertes the coordinate of the object to homogenous coordinate
// Returns:
// 		coord: 1d array of size 4 (x, y, z, 1)
float* Object::ToHCoord(Vertex v) {
	float* coord = (float*)malloc(sizeof(float)*4);

	*(coord + 0) = v.x;
	*(coord + 1) = v.y;
	*(coord + 2) = v.z;
	*(coord + 3) = 1;

	return coord;
}

void Object::ApplyT(Transformation t) {
	for(int i = 0; i < vertices.size(); i++) {
		ApplyHCoord(t.Compute(ToHCoord(vertices[i])), &vertices[i]);
	}

	ApplyHCoord(t.Compute(ToHCoord(*pivot)), pivot);
}

void Object::ApplyT(std::vector<Transformation> trans) {

}

// Method that moves the pivot to the vertex, using transaltion transformation
// Args:
// 		point: point to move toward
void Object::MoveTo(Vertex point) {
	float dx = point.x - pivot->x;
	float dy = point.y - pivot->y;
	float dz = point.z - pivot->z;

	position->x = point.x;
	position->y = point.y;
	position->z = point.z;

	TTranslate transformation(dx, dy, dz);
	ApplyT(transformation);
}

// Method that scales the object
// Args:
// 		ratio: ratio at witch the object is scaled
void Object::Scale(float ratio) {
	TScale transformation(ratio, ratio, ratio);
	ApplyT(transformation);
}

// Method that scales the object
// Args:
// 		sx: x ratio at witch the object is scaled
// 		sy: y ratio at witch the object is scaled
// 		sz: z ratio at witch the object is scaled
void Object::Scale(float sx, float sy, float sz) {
	TScale transformation(sx, sy, sz);
	ApplyT(transformation);
}

// Method that rotates the object with respect the pivot
// Args:
// 		angle: angle in degrees
// 		axis: axis of the rotation (x, y, z)
void Object::Rotate(double angle, char axis) {
	TRotation *transformation;
	//if(pivot == Vertex::zero)
		transformation = new TRotation(angle, axis, pivot->x, pivot->y, pivot->z);
	//else
	//	transformation = new TRotation(angle, axis);

	ApplyT(*transformation);
}

// Method that rotates the object to some rotation, in respect to the pivot
void Object::RotateTo(double angle, char axis) {
	switch(axis) {
		case 'x':
			angle = angle - rotation->x;
			rotation->x += angle;
			break;
		case 'y':
			angle = angle - rotation->y;
			rotation->y += angle;
			break;
		case 'z':
			angle = angle - rotation->z;
			rotation->z += angle;
			break;
	}
	TRotation *transformation;
	//if(pivot == Vertex::zero)
		transformation = new TRotation(angle, axis, pivot->x, pivot->y, pivot->z);
	//else
	//	transformation = new TRotation(angle, axis);

	ApplyT(*transformation);
}

// Function that seprates the elements of a string seprated by a delimeter
// and returns it in a vector
// Args:
// 		str: string that will be parsed
// 		delimeter: delimeter that separats the elements of the string
// 		start: index where to start the parsign
// Returns:
// 		elements: vector of strings, with the separated elements
std::vector<std::string> parseLine(std::string str, std::string delimeter, int start) {
	size_t pos = 0;				// position of the element to find
	std::vector<std::string> elements;	// vector that will return
	std::string elem;				// the current element of the string

	// Loops trough all the slices of the string
	while((pos = str.find(delimeter, start)) != std::string::npos) {
		// extracts the substring
		elem = str.substr(start, pos-start);
		// Changes the start index
		start = pos + delimeter.length();

		elements.push_back(elem);
	}

	// If there were elements, adds the last one
	if(elements.size() > 0) {
		elem = str.substr(start, str.length()-start);
		elements.push_back(elem);
	}

	return elements;
}

// Function that reads an .obj file and returns Object objects that
// represent the 3d object
// Args:
// 		path: string of the file path
// Returns:
// 		objects: vector of all the Objects read
std::vector<Object> readObjFile(std::string path) {
	std::vector<Object> objects; 	// list with objects to return
	Object* obj;				// The current working object
	int count = 0;				// number of objects read
	int vertex_offset = 0;		// Offset of vertex if there exists multiple objects

	std::string file_line;			// the line of the file being read
	std::string delimeter = " ";		// delimeter that separates the string

	// reads files
	std::ifstream file(path);

	// goes line by line through the file
	while(getline(file, file_line)) {
		// obtaint the prefix of the line
		// wich determins if it is an object, vertex or face
		size_t pos = file_line.find(delimeter);
		std::string prefijo = file_line.substr(0, pos);

		// If there exists a prefix
		if(pos != std::string::npos) {
			// Obtains the elements of the line
			std::vector<std::string> elements;
			elements = parseLine(file_line, delimeter, 0);
			elements.erase(elements.begin()); // erases the first one (prefix)

			// If the prefix is "o", creates new Object
			if(prefijo == "o") {
				// Si ya existe un objeto, cambiar el offset de vertices
				if(objects.size() > 0) {
					vertex_offset += objects[objects.size()-1].vertices.size();
				}
				objects.push_back(Object(elements[0]));
			}

			// If the prefix is "v", adds a vertex to the last Object
			if(prefijo == "v") {
				// Veryfies that there exists an object in the current context
				if(objects.size() > 0) {
					float x = stof(elements[0]);
					float y = stof(elements[1]);
					float z = stof(elements[3]);

					Vertex v(x, y, z);
					objects[objects.size() - 1].AddVertex(v);
				}
			}

			// If the prefix is "f", add a face to the last object
			if(prefijo == "f") {
				// Veryfies that there exists an object in the current context
				if(objects.size() > 0) {
					Face f;
				
					for(int i = 0; i < elements.size(); i++) {
						// Substracts one because of the offset, and various objs offset
						f.Add(stoi(elements[i]) - 1 - vertex_offset);
					}

					objects[objects.size()-1].AddFace(f);
				}
			}
		}
	}

	return objects;
}
