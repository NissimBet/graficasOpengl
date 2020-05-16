//
// Created by jcfflores on 5/16/20.
//

#ifndef GRAFICASOPENGL_MODELCOLORS_H
#define GRAFICASOPENGL_MODELCOLORS_H

#include <unordered_map>
#include <glm/vec3.hpp>

std::unordered_map<std::string,glm::vec3> cabinColors = {
        {"Floor", glm::vec3(0.40f,0.26f,0.13f)},
        {"Roof_3", glm::vec3(0.945f, 0.949f, 0.956f)},
        {"Roof_4", glm::vec3(0.945f, 0.949f, 0.956f)},
        {"Chimney_1", glm::vec3(0.4588f,0.2941f,0.2314f)},
        {"Chimney_2", glm::vec3(0.4588f,0.2941f,0.2314f)},
        {"Chimney_3", glm::vec3(0.4588f,0.2941f,0.2314f)},
        {"Chimney_4", glm::vec3(0.4588f,0.2941f,0.2314f)},
        {"Chimney_Border_1", glm::vec3(0.525f, 0.533f, 0.541f)},
        {"Chimney_Border_2", glm::vec3(0.525f, 0.533f, 0.541f)},
        {"Chimney_Border_3", glm::vec3(0.525f, 0.533f, 0.541f)},
        {"Chimney_Border_4", glm::vec3(0.525f, 0.533f, 0.541f)}
};

glm::vec3 baseColor = glm::vec3(1.0f,0.8f,0.6f);
glm::vec3 downColor = glm::vec3(0.75f,0.75f,0.75f);

std::unordered_map<std::string, glm::vec3> sledColors = {
        {"base5_Cube.004", baseColor},
        {"base4_Cube.003", baseColor},
        {"base3_Cube.002", baseColor},
        {"base2_Cube.001", baseColor},
        {"base1_Cube", baseColor},
        {"soporte5_Cube.011", downColor},
        {"giro4_Cube.016", downColor},
        {"giro5_Cube.017", downColor},
        {"giro1_Cube.012", downColor}
};

glm::vec3 ropeColor = glm::vec3(0.59f,0.94f,1.0f);
glm::vec3 backrestColor = glm::vec3(0.5f,0.28f,0.09f);
glm::vec3 chairTopFaceColor = glm::vec3(0.81,0.39,0.01);
glm::vec3 columnColor = glm::vec3(0.26f,0.17f,0.0f);
glm::vec3 chairColor = glm::vec3(0.67f, 0.0f,0.0f);

std::unordered_map<std::string, glm::vec3> cablewayColors {
        {"TUBEUnionBetweenCableWayAndRope_Cylinder.001", glm::vec3(0.7f,0.72f,0.74f)},
        {"LightBulb_Sphere.002", glm::vec3(0.88f,0.94f,0.0f)},
        {"Rope1_Cube.079",ropeColor},
        {"Rope2_Cube.078", ropeColor},
        {"Roof_Cube.067", glm::vec3(0.67f, 0.0f,0.0f)},
        {"Floor_Cube.066", glm::vec3(0.36f, 0.36f, 0.36f)},
        {"Backrest1_Cube.069", backrestColor},
        {"Backrest2_Cube.068", backrestColor},
        {"Chair1TopFace_Cube.070", chairTopFaceColor},
        {"Chair2TopFace_Cube.074", chairTopFaceColor},
        {"Column12_Cube.065", columnColor},
        {"Column22_Cube.064", columnColor},
        {"Column21_Cube.063", columnColor},
        {"Column11_Cube.062", columnColor},
        {"Chair1FaceIn_Cube.071", chairColor},
        {"Chair2FaceIn_Cube.075", chairColor},
        {"Chair2LateralFace1_Cube.076", chairColor},
        {"Chair1LateralFace2_Cube.077", chairColor},
        {"Chair1LateralFace2.001_Cube.073", chairColor},
        {"Chair1LateralFace1_Cube.072", chairColor},
};

#endif //GRAFICASOPENGL_MODELCOLORS_H
