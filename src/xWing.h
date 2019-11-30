#ifndef XWING_H
#define XWING_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "objects.h"
#include "utils/timer.h"
#include "map/terrainMesh.h"

class xWing {
    public:
        xWing(float _separation, TerrainMesh *tRef);

        Object *model;
        float separation;
        TerrainMesh *terrain;

        // Control variables
        bool norms;
        bool wireframe;

        void Draw();
        void UpdateVisibility(Vertex cam);
        void Update();
        Vertex GetPosition();

    private:
        bool started;
        float past_height;
};

#endif
