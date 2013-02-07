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
    // ����
    HTEXTURE bg_tex_;
    bsglSprite* bg_;
    // ��Ϸ����
    HTEXTURE gameover_tex_;
    bsglSprite* gameover_;
    // ׷�ĵ��˿�
    HTEXTURE poker_tex_;
    bsglSprite* poker_;
    // ƽ����
    HTEXTURE line_tex_;
    bsglSprite* line_;
    // һ�������ɽ��
    HTEXTURE beat_tex_;
    bsglSprite* beat_;
    // ��Ѫ��
    HTEXTURE red_tex_;
    bsglSprite* red_;
    // ��ʾѪ���ĵ�ͼ
    HTEXTURE blood_tex_;
    bsglSprite* blood_;

    // �ܲ��Ķ���
    HTEXTURE run_tex_;
    bsglAnimation* run_;

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
    //bsglFont* font_;

    // ���¹ؿ���last�����һ���ĵ�ͼԪ�ص�λ�ã��ý���
    void UpdateLevel(float last, std::vector<int> level);
};

#endif//HAR_GAME_SCENE_H
