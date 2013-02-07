/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

// �˵�

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
    // �˵�����������ť��ͼƬ
    HTEXTURE menu_tex_;
    bsglSprite* menu_;
    HTEXTURE story_tex_;
    // ����ҳ��
    bsglSprite* story_;
    // ���ƽ����µı���
    bool tell_;
};

#endif//HAR_MENU_SCENE_H
