//
// Created by nissi on 5/2/2020.
//

#include "TreeTrunk.h"

void TreeTrunk::handleEvent(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_R:
                this->scale(glm::vec3(1.05));
                break;
            case SDL_SCANCODE_F:
                this->scale(glm::vec3(0.95));
                break;
            default:
                break;
        }
    }
}
