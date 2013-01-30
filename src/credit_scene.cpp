/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include "credit_scene.h"
#include "menu_scene.h"

extern Scene* scene;
extern MenuScene* menu;

CreditScene::CreditScene() {
    hge_ = hgeCreate(HGE_VERSION);

    credit_tex_ = hge_->Texture_Load("media/credit.png");
    if( credit_tex_ == 0 ) {
        MessageBoxA(NULL, hge_->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    credit_ = new hgeSprite(credit_tex_, 0, 0, 800, 600);
}

CreditScene::~CreditScene() {
    delete credit_;
    hge_->Texture_Free(credit_tex_);
}

bool CreditScene::Update() {
    float x, y;
    hge_->Input_GetMousePos(&x, &y);

    // 没什么好说的，按返回就回到菜单
    if( hge_->Input_KeyUp(HGEK_LBUTTON) ) {
        if( x>660 && y>510) {
            scene = menu;
            return false;
        }
    }

    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear(0);
    credit_->Render(0,0);   //渲染上去
    hge_->Gfx_EndScene();

    return false;
}
