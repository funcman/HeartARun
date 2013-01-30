/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

// 作者

#ifndef HAR_CREDIT_SCENE_H
#define HAR_CREDIT_SCENE_H

#include "scene.h"
#include "../include/hgesprite.h"

class CreditScene : public Scene {
public:
    CreditScene();
    ~CreditScene();

    bool Update();
private:
    HGE* hge_;
    // 就一图
    HTEXTURE credit_tex_;
    hgeSprite* credit_;
};

#endif//HAR_CREDIT_SCENE_H
