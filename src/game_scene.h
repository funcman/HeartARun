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
    // 背景
    HTEXTURE bg_tex_;
    bsglSprite* bg_;
    // 游戏结束
    HTEXTURE gameover_tex_;
    bsglSprite* gameover_;
    // 追心的扑克
    HTEXTURE poker_tex_;
    bsglSprite* poker_;
    // 平的线
    HTEXTURE line_tex_;
    bsglSprite* line_;
    // 一般的心跳山峰
    HTEXTURE beat_tex_;
    bsglSprite* beat_;
    // 加血的
    HTEXTURE red_tex_;
    bsglSprite* red_;
    // 表示血量的底图
    HTEXTURE blood_tex_;
    bsglSprite* blood_;

    // 跑步的动画
    HTEXTURE run_tex_;
    bsglAnimation* run_;

    float y_;           //心的高度
    float yinc_;        //心的y轴加速度
    float g_;           //重力
    bool in_air_;       //正在空中
    int heath_;         //HP

    // 心电图元素
    struct Beat {
        int type;   //0支线1一般峰2加血峰
        float pos;  //位置（0点在右边，方向是向左，比较奇怪的设定 = =）
        bool flag1; //撞上了
        bool flag2; //加过血了
        bool flag3; //音效放过了
    };

    // 是否嗝屁
    bool game_over_;
    // 扑克位置
    float poker_pos_;
    // 心的速度
    float speed_;
    // 扑克速度
    float poker_speed_;
    // 心电图链表
    std::list<Beat> beats;

    // 跑了多远
    float distance_;

    // 字～
    //bsglFont* font_;

    // 更新关卡，last是最后一个心电图元素的位置，好接上
    void UpdateLevel(float last, std::vector<int> level);
};

#endif//HAR_GAME_SCENE_H
