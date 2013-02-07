/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

// 菜单

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
    // 菜单背景，含按钮的图片
    HTEXTURE menu_tex_;
    bsglSprite* menu_;
    HTEXTURE story_tex_;
    // 故事页面
    bsglSprite* story_;
    // 控制讲故事的变量
    bool tell_;
};

#endif//HAR_MENU_SCENE_H
