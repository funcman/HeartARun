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
    // ���������ʵ��һ������������Ѿ����ھͲ�Create
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

    // һ��ʼ��������
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

    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear(0);

    // ��������¾���Ⱦ���µ�ͼ���е��뵭��Ч��
    if(!tell_) {
        menu_->Render(0,0);
    }else {
        // ���Ƶ��뵭���ı�����6�룬ÿ��30֡
        static int fff = 30*6;
        fff--;
        // ��ʵû����ȫ������е���Ϸ���ˣ����ɵ������������⣬û��֤���պ��Ÿ㣻���߰�Enter��
        if( fff < 3 || hge_->Input_KeyUp(HGEK_ENTER) ) {
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

    hge_->Gfx_EndScene();

    return false;
}
