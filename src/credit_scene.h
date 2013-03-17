/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#ifndef HAR_CREDIT_SCENE_H
#define HAR_CREDIT_SCENE_H

#include "scene.h"
#include <bsglsprite.h>

class CreditScene : public Scene {
public:
    CreditScene();
    ~CreditScene();

    bool Update();
private:
    BSGL* bsgl_;
    // only one image
    HTEXTURE credit_tex_;
    bsglSprite* credit_;
};

#endif//HAR_CREDIT_SCENE_H
