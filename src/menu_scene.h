/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

// �˵�

#ifndef HAR_MENU_SCENE_H
#define HAR_MENU_SCENE_H

#include "scene.h"
#include "../include/hgesprite.h"

class MenuScene : public Scene {
public:
    MenuScene();
    ~MenuScene();

    bool Update();
private:
    HGE* hge_;
    // �˵�����������ť��ͼƬ
    HTEXTURE menu_tex_;
    hgeSprite* menu_;
    HTEXTURE story_tex_;
    // ����ҳ��
    hgeSprite* story_;
    // ���ƽ����µı���
    bool tell_;
};

#endif//HAR_MENU_SCENE_H
