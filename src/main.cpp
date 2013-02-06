/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "lib/vc/hge.lib")
#pragma comment(lib, "lib/vc/hgehelp.lib")

#include "../include/hge.h"
#include "scene.h"
#include "menu_scene.h"
#include "credit_scene.h"
#include "game_scene.h"

HGE* hge = 0;

// ����
Scene* scene = 0;
MenuScene* menu = 0;
CreditScene* credit = 0;
GameScene* game = 0;

// ��Ч
HEFFECT beat1;
HEFFECT beat2;
HEFFECT beat3;

bool FrameFunc() {
    // ��ESC�˳�
    if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
        if( MessageBoxA(0, "Really want to quit this game?", "Confirmation", MB_YESNO|MB_ICONQUESTION ) == IDYES ) {
            return true;
        }
    }

    // ��������
    return scene->Update();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    hge = hgeCreate(HGE_VERSION);

    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc); //����֡������
    hge->System_SetState(HGE_FPS, 30);              //ÿ��30֡
    hge->System_SetState(HGE_TITLE, "Heart A Run"); //����
    hge->System_SetState(HGE_WINDOWED, true);       //����ģʽ
    hge->System_SetState(HGE_HIDEMOUSE, false);     //���������
    hge->System_SetState(HGE_LOGFILE, "game.log");  //��־


    if(hge->System_Initiate()) {
        // ��ʼ����Ϸ����
        menu = new MenuScene();
        credit = new CreditScene();
        game = new GameScene();
        beat1 = hge->Effect_Load("media/beat1.ogg");
        beat2 = hge->Effect_Load("media/beat2.ogg");
        beat3 = hge->Effect_Load("media/beat3.ogg");

        // ��ʼ����Ϊ�˵����Ǹ�HGE LOGO�������Զ��ӵģ�
        scene = menu;

        // ��ʼ�������
        hge->Random_Seed(timeGetTime());

        // �������棬������Ϸ��ѭ������ѭ���в��ϵ�ˢ֡������
        hge->System_Start();

        // �ͷ���Ϸ����
        hge->Effect_Free(beat3);
        hge->Effect_Free(beat2);
        hge->Effect_Free(beat1);
        delete game;
        delete credit;
        delete menu;
    }else {
        // ������Ϣ
        MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }

    hge->System_Shutdown();

    hge->Release();

    return 0;
}
