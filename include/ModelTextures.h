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
unsigned int woodTexture = 0;
unsigned int darkWoodTexture = 0;
unsigned int cableTexture = 0;
unsigned int lightbulbTexture = 0;
unsigned int cableFloorTexture = 0;
unsigned int chairsTexture = 0;
unsigned int roofCableTexture = 0;

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
    std::string wood = "textures/texturaMadera.jpg";
    std::string darkWood = "textures/texturaMaderaOscura.jpg";
    std::string cable = "textures/cable.jpg";
    std::string lightbulb = "textures/foco.jpg";
    std::string floor = "textures/piso.jpg";
    std::string chairs = "textures/sillasCarasLaterales.jpg";
    std::string roof = "textures/techo.jpg";

    wallTexture = loadTextureFromFile(wallImage.c_str());
    floorTexture = loadTextureFromFile(floorImage.c_str());
    roofTexture = loadTextureFromFile(roofImage.c_str());
    brickTexture = loadTextureFromFile(brickImage.c_str());
    metalTexture = loadTextureFromFile(sledMetalImage.c_str());
    ropeTexture = loadTextureFromFile(cablewayRope.c_str());
    leatherTexture = loadTextureFromFile(cablewayLeather.c_str());
    leafTexture = loadTextureFromFile(leafImage.c_str());
    snowTexture = loadTextureFromFile(snowImage.c_str());
    woodTexture = loadTextureFromFile(wood.c_str());
    darkWoodTexture = loadTextureFromFile(darkWood.c_str());
    cableTexture = loadTextureFromFile(cable.c_str());
    lightbulbTexture = loadTextureFromFile(lightbulb.c_str());
    cableFloorTexture = loadTextureFromFile(floor.c_str());
    chairsTexture = loadTextureFromFile(chairs.c_str());
    roofCableTexture = loadTextureFromFile(roof.c_str());


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
            {"base5_Cube.004",    woodTexture},
            {"base4_Cube.003",    woodTexture},
            {"base3_Cube.002",    woodTexture},
            {"base2_Cube.001",    woodTexture},
            {"base1_Cube",        woodTexture},
            {"soporte5_Cube.011", darkWoodTexture},
            {"giro4_Cube.016",    darkWoodTexture},
            {"giro5_Cube.017",    darkWoodTexture},
            {"giro1_Cube.012",    darkWoodTexture}
    };

    cablewayTextures = {
            {"TUBEUnionBetweenCableWayAndRope_Cylinder", metalTexture},
            {"LightBulb_Sphere", lightbulbTexture},
            {"Rope1_Cube.039", cableTexture},
            {"Rope2_Cube.038", cableTexture},
            {"Roof_Cube.027", roofCableTexture},
            {"Floor_Cube.026",  cableFloorTexture},
            {"Backrest1_Cube.029", leatherTexture},
            {"Backrest2_Cube.028", leatherTexture},
            {"Chair1TopFace_Cube.030", leatherTexture},
            {"Chair2TopFace_Cube.034", leatherTexture},
            {"Chair1FaceIn_Cube.031", leatherTexture},
            {"Chair2FaceIn_Cube.035", leatherTexture},
            {"Chair2LateralFace1_Cube.036", chairsTexture},
            {"Chair1LateralFace2_Cube.037", chairsTexture},
            {"Chair1LateralFace2.001_Cube.033", chairsTexture},
            {"Chair1LateralFace1_Cube.032", chairsTexture},
    };
}


#endif //GRAFICASOPENGL_MODELTEXTURES_H
