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
    // ���������ʵ��һ������������Ѿ����ھͲ�Create
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

    // һ��ʼ��������
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
            // ��Start�Ƚ�����
            if( y>=280 && y<350 ) {
                tell_ = true;
            }
            // �е�Creditsҳ��
            if( y>=390 && y<460 && !tell_ ) {
                scene = credit;
                return false;
            }
        }
        // �˳���Ϸ
        if( x>660 && y>510) {
            return true;
        }
    }

    bsgl_->Gfx_BeginScene();
    bsgl_->Gfx_Clear(0);

    // ��������¾���Ⱦ���µ�ͼ���е��뵭��Ч��
    if(!tell_) {
        menu_->Render(0,0);
    }else {
        // ���Ƶ��뵭���ı�����6�룬ÿ��30֡
        static int fff = 30*6;
        fff--;
        // ��ʵû����ȫ������е���Ϸ���ˣ����ɵ������������⣬û��֤���պ��Ÿ㣻���߰�Enter��
        if( fff < 3 || bsgl_->Control_IsUp(INP_ENTER) ) {
            game->Restart();
            scene = game;
        }
        // ������ɫʵ�ֵĵ��뵭��
        int ccc = story_->GetColor();
        // ����
        if(fff>=165)
            story_->SetColor(ccc+=0xFF000000/15);
        // ����ͣ������
        // ����
        else if(fff<15)
            story_->SetColor(ccc-=0xFF000000/15);
        story_->Render(0,0);
    }

    bsgl_->Gfx_EndScene();

    return false;
}
