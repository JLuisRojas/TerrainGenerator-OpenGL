#include "centinel.h"

// Constructor for the centinel:
// Args:
// 		separation: the distance between the terrain and the centinel
// 		segments: the numbers of segments that form the circle
// 		tRef: reference to the main TerrainMesh object
Centinel::Centinel(float _radius, float _separation, int _segments, TerrainMesh *tRef) {
	model = new Object(&readObjFile("modelos/x-wing.obj")[0]);
	//model->SetPivot(model->GetCentroid());
	radius = _radius;
	separation = _separation;
	segments = _segments;
	terrain = tRef;
	
	dirV = new Vertex();

	angleRad = (2.0 * PI) / segments;
	curveValue = (4.0 / 3.0) * tan(PI / (2.0 * segments));

	timer = new Timer();
	segmentDuration = DURATION / segments;
}

// Method that calculates all the sub-bezier trajectories
void Centinel::CalculatePath() {
	double startAngle;
	double endAngle;
		Vertex *p1, *p2, *p3, *p4;
		p1 = new Vertex();
		p2 = new Vertex();
		p3 = new Vertex();
		p4 = new Vertex();
	for(int i = 0; i < segments; i++) {
		startAngle = (double)i * angleRad;
		endAngle = (double)(i+1) * angleRad;

		
		CalculateBPoints(startAngle, *p1, *p2, -1);
		CalculateBPoints(endAngle, *p4, *p3, 1);

		p1->y = terrain->GetHeight(p1->x, p1->z) + separation;
		p2->y = p1->y;//terrain->GetHeight(p2->x, p2->z) + separation;
		p4->y = terrain->GetHeight(p4->x, p4->z) + separation;
		p3->y = p4->y;//terrain->GetHeight(p3->x, p3->z) + separation;

		path.push_back(BezierTrajectory(new Vertex(p1), new Vertex(p2), new Vertex(p3), new Vertex(p4), 0.0));
	}
}

// Calcualtes the pair of points in order to form the bezier curves
// Args:
// 		teta: the angle in radians of the curve segment
void Centinel::CalculateBPoints(double teta, Vertex &a, Vertex &b, int dir) {
	// Calculates the unit vector wiht the angle
	Vertex *unit_v = Vertex::UnitVectorXZ(teta);

	// Obtains the two vectors to obtain the cross product
	Vertex *A = new Vertex(unit_v);
	Vertex *B = new Vertex(0, -curveValue, 0);
	Vertex *C = *Vertex::CrossProduct(*A, *B) * (dir * radius);

	a = new Vertex(*unit_v * radius);
	b = new Vertex(*C + a);

	delete unit_v; delete A; delete B; delete C;
}

void Centinel::DrawPath() {
	//for(int i = 0; i < path.size(); i++) {
		//drawBezier(path[i]);
	//}
	model->DrawWireframe();
}

Vertex Centinel::CamaraOffset(float delta) {
	float z = cos(to_radians(model->rotation->y)) * delta;
	float x = sin(to_radians(model->rotation->y)) * delta;

	return Vertex(x, model->position->y, z);
}

Vertex Centinel::ModelPos() {
	return Vertex(model->position->x, model->position->y, model->position->z);
}

void Centinel::Update() {
	double delta = timer->Delta();

	if(delta >= DURATION) {
		timer->Restart();
		delta = 0.0;
	}

	double trans = delta / DURATION;
	double d_segment = (double)segments * trans;
	int segment = floor(d_segment);
	float t = (delta - (segment*segmentDuration)) / segmentDuration;

	Vertex current = path[segment].getPosition(t);
	model->MoveTo(current);
	
	if(initPos == false) {
		initPos = true;
	} else {
		delete dirV;
		dirV = new Vertex(current.x - pastP->x, current.y - pastP->y, current.z - pastP->z);
		// rotation Y
		// tan x/z
		double r_y = 90.0 - to_degrees(atan2(dirV->z, dirV->x));
		// rotation x
		// tan z/y
		double r_x = 90 -to_degrees(atan2(dirV->y, dirV->z));
		// rotation z
		// tan x/y
		double r_z = to_degrees(atan2(dirV->x-pastP->x, dirV->y-pastP->y));

		double r_f = to_degrees(atan2(dirV->y, sqrt(pow(dirV->x,2)+pow(dirV->z, 2))));

		//printf("%f %f %f\n", dirV->x, dirV->y, dirV->z);

		model->RotateTo(r_y, 'y');
		//model->RotateTo(r_x, 'x');
		//model->RotateTo(r_z, 'z');
		delete pastP;

	}

	pastP = new Vertex(&current);

}
