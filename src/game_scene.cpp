/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "game_scene.h"
#if defined(WIN32)
#include <windows.h>
#endif

extern Scene* scene;

extern HEFFECT beat1;
extern HEFFECT beat2;
extern HEFFECT beat3;

// obstacles data, 012 are types of electrocardiogram
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
// obstacles arrays
std::vector< std::vector<int> > levels;
//int level[] = {0,1,0,0,0,1,1};

GameScene::GameScene() {
    bsgl_ = bsglCreate(BSGL_VERSION);

    bg_tex_ = bsgl_->Texture_Load("media/bg.bmp");
    if( bg_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    bg_ = new bsglSprite(bg_tex_, 0, 0, 800, 600);

    gameover_tex_ = bsgl_->Texture_Load("media/gameover.bmp");
    if( gameover_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    gameover_ = new bsglSprite(gameover_tex_, 0, 0, 320, 240);

    poker_tex_ = bsgl_->Texture_Load("media/poker.bmp");
    if( poker_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    poker_ = new bsglSprite(poker_tex_, 0, 0, 70, 92);

    line_tex_ = bsgl_->Texture_Load("media/line.bmp");
    if( line_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    line_ = new bsglSprite(line_tex_, 0, 0, 116, 268);

    beat_tex_ = bsgl_->Texture_Load("media/beat.bmp");
    if( beat_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    beat_ = new bsglSprite(beat_tex_, 0, 0, 116, 268);

    red_tex_ = bsgl_->Texture_Load("media/red.bmp");
    if( red_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    red_ = new bsglSprite(red_tex_, 0, 0, 116, 268);

    run_tex_ = bsgl_->Texture_Load("media/run.bmp");
    if( run_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    run_ = new bsglAnimation(run_tex_, 6, 6, 0, 0, 186, 152);

    blood_tex_ = bsgl_->Texture_Load("media/blood.bmp");
    if( blood_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    blood_ = new bsglSprite(blood_tex_, 0, 0, 158, 126);

    //font_ = new bsglFont("media/font.fnt");
    //font_->SetColor(0xFF85BA81);    //font color
}

GameScene::~GameScene() {
    //delete font_;
    delete blood_;
    bsgl_->Texture_Free(blood_tex_);
    delete run_;
    bsgl_->Texture_Free(run_tex_);
    delete red_;
    bsgl_->Texture_Free(red_tex_);
    delete beat_;
    bsgl_->Texture_Free(beat_tex_);
    delete line_;
    bsgl_->Texture_Free(line_tex_);
    delete poker_;
    bsgl_->Texture_Free(poker_tex_);
    delete gameover_;
    bsgl_->Texture_Free(gameover_tex_);
    delete bg_;
    bsgl_->Texture_Free(bg_tex_);
}

void GameScene::Restart() {
    game_over_ = false;
    poker_pos_ = 50.0f; //initial position of poker
    speed_ = 4.0f;      //speed of normal heart
    poker_speed_ = 1.8f;//speed of poker
    beats.clear();
    run_->Play();
    yinc_ = 0.0f;
    g_ = 0.98f;
    in_air_ = false;
    y_ = 396;           //height of ground on y axis
    heath_ = 5;         //hp is 5
    // fill levels
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
    // no obstacle in the game begining
    std::vector<int> b;
    int iii = 0;
    for( ; iii<6; iii++) b.push_back(0);
    UpdateLevel(800.0f+116.0f, b);//fill straight lines
    UpdateLevel(800.0f-(iii-1)*116.0f, levels[bsgl_->Random_Int(0,levels.size()-1)]);//random fill one obstacles date
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
    int x, y;
    x = bsgl_->Control_GetMouseX();
    y = bsgl_->Control_GetMouseY();

    // update gameplay until game over
    if( !game_over_ ) {
        // speed up
        if( bsgl_->Control_IsPassing(INP_CTRLL) ) {
            speed_ += 1.0f;
            if(speed_>20.0f) speed_=20.0f;
            poker_speed_ -= 0.1f;
            if(poker_speed_<-1.0f) poker_speed_ = -1.0f;
        }else if( !bsgl_->Control_IsPassing(INP_SHIFTR) ) {
            speed_ -= 0.3f;
            if(speed_<4.0f) speed_=4.0f;
            poker_speed_ += 0.1f;
            if(poker_speed_>2.0f) poker_speed_ = 2.0f;
        }
        // speed cut
        if( bsgl_->Control_IsPassing(INP_SHIFTR) ) {
            speed_ -= 1.0f;
            if(speed_<2.0f) speed_=2.0f;
            poker_speed_ += 0.3f;
            if(poker_speed_>2.0f) poker_speed_ = 2.0f;
        }
        // jump
        if( bsgl_->Control_IsPassing(INP_ALTL) && !in_air_ ) {
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
        // set play speed by heart speed
        run_->SetSpeed(speed_/4.0f*6);
        run_->Update(bsgl_->Timer_GetDelta());
        // move, in fact it's obstacles moving
        int c = 0;
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            itr->pos += speed_;
            // count how many obstacles are not needed
            if(itr->pos > 1500) {
                c++;
            }
        }
        distance_ += speed_;
        // delete unnecessary obstacles, just pop the front of queue
        for( int i=0; i<c; i++) {
            beats.pop_front();
        }
        // if all obstacles have been in the game scene, just add obstacles
        if( beats.back().pos >= 0.0f ) {
            UpdateLevel(beats.back().pos, levels[bsgl_->Random_Int(0,levels.size()-1)]);
        }

        // if the position of poker is initial position, just stop
        poker_pos_+=poker_speed_;
        if(poker_pos_ < 50.0f) poker_pos_=50.0f;

        // collision decision
        for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
            float sound_speed = 20.0f-4.0f/3;
            // play sound effects
            if( itr->type!=0 && 800.0f-itr->pos <=190.0f && itr->flag3 ) {
                // by heart speed
                if( speed_ > 4.0f+sound_speed ) {
                    if( speed_ > 4.0f+sound_speed*2) {
                        //bsgl_->Effect_Play(beat3);
                    }else {
                        //bsgl_->Effect_Play(beat2);
                    }
                }else {
                    //bsgl_->Effect_Play(beat1);
                }
                itr->flag3 = false;
            }
            // collision
            if( itr->type!=0 && itr->flag1 && 800.0f-itr->pos+20.0f < 180.0f+170.0f*0.3f && 800.0f-itr->pos+100.0f > 180.0f) {
                if( y_ > 600-230 ) {
                    // be injured
                    heath_--;
                    itr->flag1 = false;
                }else if(itr->type==2 && itr->flag2 && itr->flag1) {
                    // treat
                    heath_++;
                    if(heath_>5) heath_=5;
                    itr->flag2 = false;
                }
            }
        }

        // test whether the catch up
        if( poker_pos_ > 699 || heath_<=0 ) {
            game_over_ = true;
        }
    }

    // restart
    else {
        if( bsgl_->Control_IsUp(INP_MOUSEL) ) {
            if( x>=448 && x<508 && y>=336 && y<396 ) {
                Restart();
            }
        }
    }

    // render
    bsgl_->Gfx_BeginScene();
    bsgl_->Gfx_Clear(0);

    // render background
    bg_->Render(0,0);

    // render electrocardiogram
    for( std::list<Beat>::iterator itr = beats.begin(); itr!=beats.end(); itr++ ) {
        if(itr->type==0){line_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==1){beat_->Render(800.0f-itr->pos, 600-268);}
        if(itr->type==2){red_->Render(800.0f-itr->pos, 600-268);}
    }

    // render poker
    poker_->Render(poker_pos_, 5);

    // render hp
    blood_->SetTextureRect(0, 122.0f/5.0*(5-heath_), 158, 122.0f-122.0f/5.0*(5-heath_));
    blood_->RenderEx(180.0f+4.5f, y_+126.0f/5.0*(5-heath_)*0.3f+4.0f, 0, 0.3f, 0.3f);

    // render hero
    run_->RenderEx(180, y_, 0, 0.3f, 0.3f);

    // if game over, render the gameover ui
    if( game_over_ ) {
        gameover_->Render((800-320)/2, (600-240)/2);
        // print score, namely the distance
        //font_->printf(515, 275, BSGLTEXT_RIGHT, "%d M", (int)distance_);
    }

    bsgl_->Gfx_EndScene();

    return false;
}
