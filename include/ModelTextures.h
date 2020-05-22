//
// Created by nissi on 5/20/2020.
//

#ifndef GRAFICASOPENGL_MODELTEXTURES_H
#define GRAFICASOPENGL_MODELTEXTURES_H

#include "Texture.h"
#include <unordered_map>

unsigned int wallTexture = 0;
unsigned int floorTexture = 0;
unsigned int roofTexture = 0;
unsigned int brickTexture = 0;
unsigned int metalTexture = 0;
unsigned int ropeTexture = 0;
unsigned int leatherTexture = 0;
unsigned int leafTexture = 0;
unsigned int snowTexture = 0;

std::unordered_map<std::string,unsigned int> cabinTextures;
std::unordered_map<std::string, unsigned int> sledTextures;
std::unordered_map<std::string, unsigned int> cablewayTextures;

void loadTextures() {

    std::string wallImage = "textures/wood001.jpg";
    std::string floorImage = "textures/wood002.jpg";
    std::string roofImage = "textures/roof001.jpg";
    std::string brickImage = "textures/bricks001.jpg";
    std::string sledMetalImage = "textures/metal001.jpg";
    std::string cablewayRope = "textures/rope001.jpg";
    std::string cablewayLeather = "textures/leather001.jpg";
    std::string leafImage = "textures/leaf002.jpg";
    std::string snowImage = "textures/snow001.jpg";

    wallTexture = loadTextureFromFile(wallImage.c_str());
    floorTexture = loadTextureFromFile(floorImage.c_str());
    roofTexture = loadTextureFromFile(roofImage.c_str());
    brickTexture = loadTextureFromFile(brickImage.c_str());
    metalTexture = loadTextureFromFile(sledMetalImage.c_str());
    ropeTexture = loadTextureFromFile(cablewayRope.c_str());
    leatherTexture = loadTextureFromFile(cablewayLeather.c_str());
    leafTexture = loadTextureFromFile(leafImage.c_str());
    snowTexture = loadTextureFromFile(snowImage.c_str());

    cabinTextures = {
            {"Floor", floorTexture},
            {"Roof_3", roofTexture},
            {"Roof_4", roofTexture},
            {"Chimney_1", brickTexture},
            {"Chimney_2", brickTexture},
            {"Chimney_3", brickTexture},
            {"Chimney_4", brickTexture},
            {"Chimney_Border_1", brickTexture},
            {"Chimney_Border_2", brickTexture},
            {"Chimney_Border_3", brickTexture},
            {"Chimney_Border_4", brickTexture}
    };

    sledTextures = {
            {"base5_Cube.004",    metalTexture},
            {"base4_Cube.003",    metalTexture},
            {"base3_Cube.002",    metalTexture},
            {"base2_Cube.001",    metalTexture},
            {"base1_Cube",        metalTexture},
            {"soporte5_Cube.011", metalTexture},
            {"giro4_Cube.016",    metalTexture},
            {"giro5_Cube.017",    metalTexture},
            {"giro1_Cube.012",    metalTexture}
    };

    cablewayTextures = {
            {"TUBEUnionBetweenCableWayAndRope_Cylinder.001", metalTexture},
            {"LightBulb_Sphere.002", metalTexture},
            {"Rope1_Cube.079",ropeTexture},
            {"Rope2_Cube.078", ropeTexture},
            {"Roof_Cube.067", metalTexture},
            {"Floor_Cube.066",  metalTexture},
            {"Backrest1_Cube.069", leatherTexture},
            {"Backrest2_Cube.068", leatherTexture},
            {"Chair1TopFace_Cube.070", leatherTexture},
            {"Chair2TopFace_Cube.074", leatherTexture},
            {"Column12_Cube.065", metalTexture},
            {"Column22_Cube.064", metalTexture},
            {"Column21_Cube.063", metalTexture},
            {"Column11_Cube.062", metalTexture},
            {"Chair1FaceIn_Cube.071", leatherTexture},
            {"Chair2FaceIn_Cube.075", leatherTexture},
            {"Chair2LateralFace1_Cube.076", leatherTexture},
            {"Chair1LateralFace2_Cube.077", leatherTexture},
            {"Chair1LateralFace2.001_Cube.073", leatherTexture},
            {"Chair1LateralFace1_Cube.072", leatherTexture},
    };
}


#endif //GRAFICASOPENGL_MODELTEXTURES_H
