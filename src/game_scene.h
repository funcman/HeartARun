/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#ifndef HAR_GAME_SCENE_H
#define HAR_GAME_SCENE_H

#include <vector>
#include <list>
#include "scene.h"
#include "../include/hgesprite.h"
#include "../include/hgeanim.h"
#include "../include/hgefont.h"

class GameScene : public Scene {
public:
    GameScene();
    ~GameScene();

    void Restart();
    bool Update();
private:
    HGE* hge_;
    // ����
    HTEXTURE bg_tex_;
    hgeSprite* bg_;
    // ��Ϸ����
    HTEXTURE gameover_tex_;
    hgeSprite* gameover_;
    // ׷�ĵ��˿�
    HTEXTURE poker_tex_;
    hgeSprite* poker_;
    // ƽ����
    HTEXTURE line_tex_;
    hgeSprite* line_;
    // һ�������ɽ��
    HTEXTURE beat_tex_;
    hgeSprite* beat_;
    // ��Ѫ��
    HTEXTURE red_tex_;
    hgeSprite* red_;
    // ��ʾѪ���ĵ�ͼ
    HTEXTURE blood_tex_;
    hgeSprite* blood_;

    // �ܲ��Ķ���
    HTEXTURE run_tex_;
    hgeAnimation* run_;

    float y_;           //�ĵĸ߶�
    float yinc_;        //�ĵ�y����ٶ�
    float g_;           //����
    bool in_air_;       //���ڿ���
    int heath_;         //HP

    // �ĵ�ͼԪ��
    struct Beat {
        int type;   //0֧��1һ���2��Ѫ��
        float pos;  //λ�ã�0�����ұߣ����������󣬱Ƚ���ֵ��趨 = =��
        bool flag1; //ײ����
        bool flag2; //�ӹ�Ѫ��
        bool flag3; //��Ч�Ź���
    };

    // �Ƿ���ƨ
    bool game_over_;
    // �˿�λ��
    float poker_pos_;
    // �ĵ��ٶ�
    float speed_;
    // �˿��ٶ�
    float poker_speed_;
    // �ĵ�ͼ����
    std::list<Beat> beats;

    // ���˶�Զ
    float distance_;

    // �֡�
    hgeFont* font_;

    // ���¹ؿ���last�����һ���ĵ�ͼԪ�ص�λ�ã��ý���
    void UpdateLevel(float last, std::vector<int> level);
};

#endif//HAR_GAME_SCENE_H
