/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "game_scene.h"

extern Scene* scene;

extern HEFFECT beat1;
extern HEFFECT beat2;
extern HEFFECT beat3;

// 若干障碍参数，012是心电图元素的type
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
// 障碍数组
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
    font_->SetColor(0xFF85BA81);    //字体颜色
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
    poker_pos_ = 50.0f; //扑克初始位置
    speed_ = 4.0f;      //正常心的速度
    poker_speed_ = 1.8f;//扑克的速度
    beats.clear();
    run_->Play();
    yinc_ = 0.0f;
    g_ = 0.98f;
    in_air_ = false;
    y_ = 396;           //平地的y轴高度
    heath_ = 5;         //五滴血
    // 填关卡
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
    // 游戏刚开始时都是平的没障碍
    std::vector<int> b;
    int iii = 0;
    for( ; iii<6; iii++) b.push_back(0);
    UpdateLevel(800.0f+116.0f, b);//平线加进去
    UpdateLevel(800.0f-(iii-1)*116.0f, levels[hge_->Random_Int(0,levels.size()-1)]);//随机一个障碍参数进去
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

    // 还没有嗝屁则更新游戏逻辑
    if( !game_over_ ) {
        // 加速
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
        // 减速
        if( hge_->Input_GetKeyState(HGEK_SHIFT) ) {
            speed_ -= 1.0f;
            if(speed_<2.0f) speed_=2.0f;
            poker_speed_ += 0.3f;
            if(poker_speed_>2.0f) poker_speed_ = 2.0f;
        }
        // 跳
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
        // 根据速度设置动画
        run_->SetSpeed(speed_/4.0f*6);
        run_->Update(hge_->Timer_GetDelta());
        // 移动，其实是移动障碍
        int c = 0;
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            itr->pos += speed_;
            // 统计有多少障碍不需要了
            if(itr->pos > 1500) {
                c++;
            }
        }
        distance_ += speed_;
        // 不需要的障碍就删掉，反正是队列，直接按数目从一头删除就行
        for( int i=0; i<c; i++) {
            beats.pop_front();
        }
        // 如果所有障碍都进入场景中，就添加一次障碍，随机添加某一组障碍参数
        if( beats.back().pos >= 0.0f ) {
            UpdateLevel(beats.back().pos, levels[hge_->Random_Int(0,levels.size()-1)]);
        }

        // 扑克的位置，如果扑克被甩到初始位置，就停在那
        poker_pos_+=poker_speed_;
        if(poker_pos_ < 50.0f) poker_pos_=50.0f;

        // 碰撞判定
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            float sound_speed = 20.0f-4.0f/3;
            // 播音效
            if( itr->type!=0 && 800.0f-itr->pos <=190.0f && itr->flag3 ) {
                // 按心的速度播
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
            // 碰撞
            if( itr->type!=0 && itr->flag1 && 800.0f-itr->pos+20.0f < 180.0f+170.0f*0.3f && 800.0f-itr->pos+100.0f > 180.0f) {
                if( y_ > 600-230 ) {
                    // 掉血
                    heath_--;
                    itr->flag1 = false;
                }else if(itr->type==2 && itr->flag2 && itr->flag1) {
                    // 加血
                    heath_++;
                    if(heath_>5) heath_=5;
                    itr->flag2 = false;
                }
            }
        }

        // 判断是否追上
        if( poker_pos_ > 699 || heath_<=0 ) {
            game_over_ = true;
        }
    }

    // 嗝屁时请按重玩
    else {
        if( hge_->Input_KeyUp(HGEK_LBUTTON) ) {
            if( x>=448 && x<508 && y>=336 && y<396 ) {
                Restart();
            }
        }
    }

    // 渲染
    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear(0);

    // 渲染背景
    bg_->Render(0,0);

    // 渲染心电图
    for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
        if(itr->type==0){line_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==1){beat_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==2){red_->Render(800.0f-itr->pos, 600-268);}
    }

    // 渲染扑克
    poker_->Render(poker_pos_, 5);

    // 渲染血量
    blood_->SetTextureRect(0, 122.0f/5.0*(5-heath_), 158, 122.0f-122.0f/5.0*(5-heath_));
    blood_->RenderEx(180.0f+4.5f, y_+126.0f/5.0*(5-heath_)*0.3f+4.0f, 0, 0.3f, 0.3f);

    // 渲染猪脚
    run_->RenderEx(180, y_, 0, 0.3f, 0.3f);

    // 如果嗝屁，渲染嗝屁界面
    if( game_over_ ) {
        gameover_->Render((800-320)/2, (600-240)/2);
        // 打印分数，即距离
        font_->printf(515, 275, HGETEXT_RIGHT, "%d M", (int)distance_);
    }

    hge_->Gfx_EndScene();

    return false;
}
