#include "xWing.h"

// Constructor for the xWing class
// Args:
//      _separation: the ship separation with the ground
//      tRef: object reference to the terrain mesh
xWing::xWing(float _separation, TerrainMesh *tRef) {
    model = new Object(&readObjFile("modelos/x-wing.obj")[0]);
    separation = _separation;
    terrain = tRef;

    // Modifications to the initial position of the spaceship
    model->RotateTo(180, 'y');
    //model->RotateTo(-90, 'x');
    model->MoveTo(Vertex(0.0, 0.0, 30.0));

    started = false;
    norms = false;
    wireframe = true;
}

// Recalculates normal and checks visibility
void xWing::UpdateVisibility(Vertex cam) {
    if(norms) {
        model->CalculateNormals();
        model->CheckVisibility(cam);
        model->CalculateIluminations(cam);
    }
}

// Draws the object
void xWing::Draw() {
    if(wireframe)
        model->DrawWireframe();
    else
        model->Draw();
}

// Gets the current position of the xWing
Vertex xWing::GetPosition() {
    return Vertex(model->position);
}

// Updates the position and rotation of xWing
void xWing::Update() {
    float x = model->position->x;
    float z = model->position->z;

    float t_height = terrain->GetHeight(x, z) + separation;

    if(!started) {
        started = true;
        past_height = t_height;
    } else {
        float height_diff = t_height - past_height;
        t_height = past_height + (height_diff * 1.0/5.0);
        // Obtain the angle of inclination
        double teta = to_degrees(atan2(t_height - past_height, 1));
        double p_teta = model->rotation->x;

        double diff = teta - p_teta;
        diff *= 1.0/4.0;

        model->RotateTo(p_teta + diff, 'x');
        past_height = t_height;
    }

    model->MoveTo(Vertex(x, t_height, z));
}
