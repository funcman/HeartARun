/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#ifndef HAR_GAME_SCENE_H
#define HAR_GAME_SCENE_H

#include <vector>
#include <list>
#include "scene.h"
#include <bsglsprite.h>
#include <bsglanim.h>
//#include <bsglfont.h>

class GameScene : public Scene {
public:
    GameScene();
    ~GameScene();

    void Restart();
    bool Update();
private:
    BSGL* bsgl_;
    // background
    HTEXTURE bg_tex_;
    bsglSprite* bg_;
    // game over ui
    HTEXTURE gameover_tex_;
    bsglSprite* gameover_;
    // poker
    HTEXTURE poker_tex_;
    bsglSprite* poker_;
    // straight line
    HTEXTURE line_tex_;
    bsglSprite* line_;
    // normal wave crest
    HTEXTURE beat_tex_;
    bsglSprite* beat_;
    // blood wave crest
    HTEXTURE red_tex_;
    bsglSprite* red_;
    // hp
    HTEXTURE blood_tex_;
    bsglSprite* blood_;

    // run animation
    HTEXTURE run_tex_;
    bsglAnimation* run_;

    float y_;           //y of hero
    float yinc_;        //vertical acceleration of hero
    float g_;           //big G
    bool in_air_;       //in air, jumping
    int heath_;         //HP

    // electrocardiogram element
    struct Beat {
        int type;   //0 straight line,1 normal 2 blood
        float pos;  //position (0 point is right, direction to the left, strange~)
        bool flag1; //has been hit
        bool flag2; //has been treated
        bool flag3; //has played
    };

    // game over
    bool game_over_;
    // poker position
    float poker_pos_;
    // speed of heart
    float speed_;
    // speed of poker
    float poker_speed_;
    // list of electrocardiogram beats
    std::list<Beat> beats;

    // distance
    float distance_;

    // font
    //bsglFont* font_;

    // update level, 'last' is the last electrocardiogram beat position
    void UpdateLevel(float last, std::vector<int> level);
};

#endif//HAR_GAME_SCENE_H
