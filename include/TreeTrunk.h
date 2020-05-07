//
// Created by nissi on 5/2/2020.
//

#ifndef GRAFICASOPENGL_TREETRUNK_H
#define GRAFICASOPENGL_TREETRUNK_H

#include "Cube.h"
#include "WorldObject.h"

class TreeTrunk : public Cube, public WorldObject {
public:
    TreeTrunk() : Cube(), WorldObject() {
        std::vector<GLfloat> trunkColors(this->vertices.size());
        for (int i = 0; i < this->vertices.size(); i+=3) {
            trunkColors[i] = 67.0f / 255.0f;
            trunkColors[i+1] = 57.0f / 255.0f;
            trunkColors[i+2] = 10.0f / 255.0f;
        }
        this->setColors(trunkColors);
    }

//    void handleEvent(const SDL_Event &event) override;
};


#endif //GRAFICASOPENGL_TREETRUNK_H
