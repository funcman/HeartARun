/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "menu_scene.h"
#if defined(WIN32)
#include <windows.h>
#endif
#include "credit_scene.h"
#include "game_scene.h"

extern Scene* scene;
extern CreditScene* credit;
extern GameScene* game;

MenuScene::MenuScene() {
    // 引擎对象其实是一个单件，如果已经存在就不Create
    bsgl_ = bsglCreate(BSGL_VERSION);

    menu_tex_ = bsgl_->Texture_Load("media/menu.bmp");
    if( menu_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    menu_ = new bsglSprite(menu_tex_, 0, 0, 800, 600);

    story_tex_ = bsgl_->Texture_Load("media/story.bmp");
    if( story_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    story_ = new bsglSprite(story_tex_, 0, 0, 800, 600);
    story_->SetColor(0x00FFFFFF);

    // 一开始不讲故事
    tell_ = false;
}

MenuScene::~MenuScene() {
    delete story_;
    bsgl_->Texture_Free(story_tex_);
    delete menu_;
    bsgl_->Texture_Free(menu_tex_);
}

bool MenuScene::Update() {
    int x, y;
    x = bsgl_->Control_GetMouseX();
    y = bsgl_->Control_GetMouseY();

    if( bsgl_->Control_IsUp(INP_MOUSEL) ) {
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

    bsgl_->Gfx_BeginScene();
    bsgl_->Gfx_Clear(0);

    // 如果讲故事就渲染故事的图，有淡入淡出效果
    if(!tell_) {
        menu_->Render(0,0);
    }else {
        // 控制淡入淡出的变量，6秒，每秒30帧
        static int fff = 30*6;
        fff--;
        // 其实没等完全淡完就切到游戏里了，怀疑淡完再切有问题，没验证，凑合着搞；或者按Enter切
        if( fff < 3 || bsgl_->Control_IsUp(INP_ENTER) ) {
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

    bsgl_->Gfx_EndScene();

    return false;
}
