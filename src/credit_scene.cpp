/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "credit_scene.h"
#include <stdio.h>
#if defined(WIN32)
#include <windows.h>
#endif
#include "menu_scene.h"

extern Scene* scene;
extern MenuScene* menu;

CreditScene::CreditScene() {
    bsgl_ = bsglCreate(BSGL_VERSION);

    credit_tex_ = bsgl_->Texture_Load("media/credit.bmp");
    if( credit_tex_ == 0 ) {
#if defined(WIN32)
        MessageBoxA(NULL, bsgl_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl_->System_GetErrorMessage());
#endif
    }
    credit_ = new bsglSprite(credit_tex_, 0, 0, 800, 600);
}

CreditScene::~CreditScene() {
    delete credit_;
    bsgl_->Texture_Free(credit_tex_);
}

bool CreditScene::Update() {
    int x, y;
    x = bsgl_->Control_GetMouseX();
    y = bsgl_->Control_GetMouseY();

    // 没什么好说的，按返回就回到菜单
    if( bsgl_->Control_IsUp(INP_MOUSEL) ) {
        if( x>660 && y>510) {
            scene = menu;
            return false;
        }
    }

    bsgl_->Gfx_BeginScene();
    bsgl_->Gfx_Clear(0);
    credit_->Render(0,0);   //渲染上去
    bsgl_->Gfx_EndScene();

    return false;
}
