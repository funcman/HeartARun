/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#ifndef HAR_MENU_SCENE_H
#define HAR_MENU_SCENE_H

#include "scene.h"
#include <bsglsprite.h>

class MenuScene : public Scene {
public:
    MenuScene();
    ~MenuScene();

    bool Update();
private:
    BSGL* bsgl_;
    // menu background with buttons
    HTEXTURE menu_tex_;
    bsglSprite* menu_;
    HTEXTURE story_tex_;
    // the story page
    bsglSprite* story_;
    // the value of fade controllin
    bool tell_;
};

#endif//HAR_MENU_SCENE_H
