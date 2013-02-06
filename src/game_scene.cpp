/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "game_scene.h"

extern Scene* scene;

extern HEFFECT beat1;
extern HEFFECT beat2;
extern HEFFECT beat3;

// �����ϰ�������012���ĵ�ͼԪ�ص�type
int level1[] = {0,1,0,0,0,1,1,0,0,1,0,0,2,0,0};
size_t lsize1 = sizeof(level1)/sizeof(int);
int level2[] = {0,0,0,2,1,1,0,0,1,0,0,1,0,0};
size_t lsize2 = sizeof(level2)/sizeof(int);
int level3[] = {0,1,0,0,0,1,1,1,0,0,1,0,0,1,0,0};
size_t lsize3 = sizeof(level3)/sizeof(int);
int level4[] = {0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,2};
size_t lsize4 = sizeof(level4)/sizeof(int);
int level5[] = {0,0,1,0,0,0,0,1,1,2,0,0,1,0};
size_t lsize5 = sizeof(level5)/sizeof(int);
// �ϰ�����
std::vector< std::vector<int> > levels;
//int level[] = {0,1,0,0,0,1,1};

GameScene::GameScene() {
    hge_ = hgeCreate(HGE_VERSION);

    bg_tex_ = hge_->Texture_Load("media/bg.png");
    if( bg_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    bg_ = new hgeSprite(bg_tex_, 0, 0, 800, 600);

    gameover_tex_ = hge_->Texture_Load("media/gameover.png");
    if( gameover_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    gameover_ = new hgeSprite(gameover_tex_, 0, 0, 320, 240);

    poker_tex_ = hge_->Texture_Load("media/poker.png");
    if( poker_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    poker_ = new hgeSprite(poker_tex_, 0, 0, 70, 92);

    line_tex_ = hge_->Texture_Load("media/line.png");
    if( line_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    line_ = new hgeSprite(line_tex_, 0, 0, 116, 268);

    beat_tex_ = hge_->Texture_Load("media/beat.png");
    if( beat_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    beat_ = new hgeSprite(beat_tex_, 0, 0, 116, 268);

    red_tex_ = hge_->Texture_Load("media/red.png");
    if( red_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    red_ = new hgeSprite(red_tex_, 0, 0, 116, 268);

    run_tex_ = hge_->Texture_Load("media/run.png");
    if( run_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    run_ = new hgeAnimation(run_tex_, 6, 6, 0, 0, 186, 152);

    blood_tex_ = hge_->Texture_Load("media/blood.png");
    if( blood_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    blood_ = new hgeSprite(blood_tex_, 0, 0, 158, 126);

    font_ = new hgeFont("media/font.fnt");
    font_->SetColor(0xFF85BA81);    //������ɫ
}

GameScene::~GameScene() {
    delete font_;
    delete blood_;
    hge_->Texture_Free(blood_tex_);
    delete run_;
    hge_->Texture_Free(run_tex_);
    delete red_;
    hge_->Texture_Free(red_tex_);
    delete beat_;
    hge_->Texture_Free(beat_tex_);
    delete line_;
    hge_->Texture_Free(line_tex_);
    delete poker_;
    hge_->Texture_Free(poker_tex_);
    delete gameover_;
    hge_->Texture_Free(gameover_tex_);
    delete bg_;
    hge_->Texture_Free(bg_tex_);
}

void GameScene::Restart() {
    game_over_ = false;
    poker_pos_ = 50.0f; //�˿˳�ʼλ��
    speed_ = 4.0f;      //�����ĵ��ٶ�
    poker_speed_ = 1.8f;//�˿˵��ٶ�
    beats.clear();
    run_->Play();
    yinc_ = 0.0f;
    g_ = 0.98f;
    in_air_ = false;
    y_ = 396;           //ƽ�ص�y��߶�
    heath_ = 5;         //���Ѫ
    // ��ؿ�
    std::vector<int> l1(level1, level1+lsize1);
    levels.push_back(l1);
    std::vector<int> l2(level2, level2+lsize2);
    levels.push_back(l2);
    std::vector<int> l3(level3, level3+lsize3);
    levels.push_back(l3);
    std::vector<int> l4(level4, level4+lsize4);
    levels.push_back(l4);
    std::vector<int> l5(level5, level5+lsize5);
    levels.push_back(l5);
    // ��Ϸ�տ�ʼʱ����ƽ��û�ϰ�
    std::vector<int> b;
    int iii = 0;
    for( ; iii<6; iii++) b.push_back(0);
    UpdateLevel(800.0f+116.0f, b);//ƽ�߼ӽ�ȥ
    UpdateLevel(800.0f-(iii-1)*116.0f, levels[hge_->Random_Int(0,levels.size()-1)]);//���һ���ϰ�������ȥ
    distance_ = 0.0f;
}

void GameScene::UpdateLevel(float last, std::vector<int> level) {
    for( int i=0; i<level.size(); ++i ) {
        last -= 116.0f;
        struct Beat b;
        b.pos = last;
        b.type = level[i];
        b.flag1 = true;
        b.flag2 = true;
        b.flag3 = true;
        beats.push_back(b);
    }
}

bool GameScene::Update() {
    float x, y;
    hge_->Input_GetMousePos(&x, &y);

    // ��û����ƨ�������Ϸ�߼�
    if( !game_over_ ) {
        // ����
        if( hge_->Input_GetKeyState(HGEK_CTRL) ) {
            speed_ += 1.0f;
            if(speed_>20.0f) speed_=20.0f;
            poker_speed_ -= 0.1f;
            if(poker_speed_<-1.0f) poker_speed_ = -1.0f;
        }else if( !hge_->Input_GetKeyState(HGEK_SHIFT) ) {
            speed_ -= 0.3f;
            if(speed_<4.0f) speed_=4.0f;
            poker_speed_ += 0.1f;
            if(poker_speed_>2.0f) poker_speed_ = 2.0f;
        }
        // ����
        if( hge_->Input_GetKeyState(HGEK_SHIFT) ) {
            speed_ -= 1.0f;
            if(speed_<2.0f) speed_=2.0f;
            poker_speed_ += 0.3f;
            if(poker_speed_>2.0f) poker_speed_ = 2.0f;
        }
        // ��
        if( hge_->Input_GetKeyState(HGEK_ALT) && !in_air_ ) {
            yinc_ = -15.0f;
            in_air_ = true;
        }
        if( in_air_ ) {
            yinc_ += g_;
            y_ += yinc_;
            if( yinc_ > 0 && y_ > 396 ) {
                y_ = 396;
                in_air_ = false;
            }
        }
        // �����ٶ����ö���
        run_->SetSpeed(speed_/4.0f*6);
        run_->Update(hge_->Timer_GetDelta());
        // �ƶ�����ʵ���ƶ��ϰ�
        int c = 0;
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            itr->pos += speed_;
            // ͳ���ж����ϰ�����Ҫ��
            if(itr->pos > 1500) {
                c++;
            }
        }
        distance_ += speed_;
        // ����Ҫ���ϰ���ɾ���������Ƕ��У�ֱ�Ӱ���Ŀ��һͷɾ������
        for( int i=0; i<c; i++) {
            beats.pop_front();
        }
        // ��������ϰ������볡���У������һ���ϰ���������ĳһ���ϰ�����
        if( beats.back().pos >= 0.0f ) {
            UpdateLevel(beats.back().pos, levels[hge_->Random_Int(0,levels.size()-1)]);
        }

        // �˿˵�λ�ã�����˿˱�˦����ʼλ�ã���ͣ����
        poker_pos_+=poker_speed_;
        if(poker_pos_ < 50.0f) poker_pos_=50.0f;

        // ��ײ�ж�
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            float sound_speed = 20.0f-4.0f/3;
            // ����Ч
            if( itr->type!=0 && 800.0f-itr->pos <=190.0f && itr->flag3 ) {
                // ���ĵ��ٶȲ�
                if( speed_ > 4.0f+sound_speed ) {
                    if( speed_ > 4.0f+sound_speed*2) {
                        hge_->Effect_Play(beat3);
                    }else {
                        hge_->Effect_Play(beat2);
                    }
                }else {
                    hge_->Effect_Play(beat1);
                }
                itr->flag3 = false;
            }
            // ��ײ
            if( itr->type!=0 && itr->flag1 && 800.0f-itr->pos+20.0f < 180.0f+170.0f*0.3f && 800.0f-itr->pos+100.0f > 180.0f) {
                if( y_ > 600-230 ) {
                    // ��Ѫ
                    heath_--;
                    itr->flag1 = false;
                }else if(itr->type==2 && itr->flag2 && itr->flag1) {
                    // ��Ѫ
                    heath_++;
                    if(heath_>5) heath_=5;
                    itr->flag2 = false;
                }
            }
        }

        // �ж��Ƿ�׷��
        if( poker_pos_ > 699 || heath_<=0 ) {
            game_over_ = true;
        }
    }

    // ��ƨʱ�밴����
    else {
        if( hge_->Input_KeyUp(HGEK_LBUTTON) ) {
            if( x>=448 && x<508 && y>=336 && y<396 ) {
                Restart();
            }
        }
    }

    // ��Ⱦ
    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear(0);

    // ��Ⱦ����
    bg_->Render(0,0);

    // ��Ⱦ�ĵ�ͼ
    for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
        if(itr->type==0){line_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==1){beat_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==2){red_->Render(800.0f-itr->pos, 600-268);}
    }

    // ��Ⱦ�˿�
    poker_->Render(poker_pos_, 5);

    // ��ȾѪ��
    blood_->SetTextureRect(0, 122.0f/5.0*(5-heath_), 158, 122.0f-122.0f/5.0*(5-heath_));
    blood_->RenderEx(180.0f+4.5f, y_+126.0f/5.0*(5-heath_)*0.3f+4.0f, 0, 0.3f, 0.3f);

    // ��Ⱦ���
    run_->RenderEx(180, y_, 0, 0.3f, 0.3f);

    // �����ƨ����Ⱦ��ƨ����
    if( game_over_ ) {
        gameover_->Render((800-320)/2, (600-240)/2);
        // ��ӡ������������
        font_->printf(515, 275, HGETEXT_RIGHT, "%d M", (int)distance_);
    }

    hge_->Gfx_EndScene();

    return false;
}
