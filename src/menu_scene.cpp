/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "menu_scene.h"
#include "credit_scene.h"
#include "game_scene.h"

extern Scene* scene;
extern CreditScene* credit;
extern GameScene* game;

MenuScene::MenuScene() {
    // 引擎对象其实是一个单件，如果已经存在就不Create
    hge_ = hgeCreate(HGE_VERSION);

    menu_tex_ = hge_->Texture_Load("media/menu.png");
    if( menu_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    menu_ = new hgeSprite(menu_tex_, 0, 0, 800, 600);

    story_tex_ = hge_->Texture_Load("media/story.jpg");
    if( story_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    story_ = new hgeSprite(story_tex_, 0, 0, 800, 600);
    story_->SetColor(0x00FFFFFF);

    // 一开始不讲故事
    tell_ = false;
}

MenuScene::~MenuScene() {
    delete story_;
    hge_->Texture_Free(story_tex_);
    delete menu_;
    hge_->Texture_Free(menu_tex_);
}

bool MenuScene::Update() {
    float x, y;
    hge_->Input_GetMousePos(&x, &y);

    if( hge_->Input_KeyUp(HGEK_LBUTTON) ) {
        if( x>= 190 && x<420 ) {
            // 按Start先讲故事
            if( y>=280 && y<350 ) {
                tell_ = true;
            }
            // 切到Credits页面
            if( y>=390 && y<460 && !tell_ ) {
                scene = credit;
                return false;
            }
        }
        // 退出游戏
        if( x>660 && y>510) {
            return true;
        }
    }

    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear(0);

    // 如果讲故事就渲染故事的图，有淡入淡出效果
    if(!tell_) {
        menu_->Render(0,0);
    }else {
        // 控制淡入淡出的变量，6秒，每秒30帧
        static int fff = 30*6;
        fff--;
        // 其实没等完全淡完就切到游戏里了，怀疑淡完再切有问题，没验证，凑合着搞；或者按Enter切
        if( fff < 3 || hge_->Input_KeyUp(HGEK_ENTER) ) {
            game->Restart();
            scene = game;
        }
        // 控制颜色实现的淡入淡出
        int ccc = story_->GetColor();
        // 淡入
        if(fff>=165)
            story_->SetColor(ccc+=0xFF000000/15);
        // 故事停个几秒
        // 淡出
        else if(fff<15)
            story_->SetColor(ccc-=0xFF000000/15);
        story_->Render(0,0);
    }

    hge_->Gfx_EndScene();

    return false;
}
