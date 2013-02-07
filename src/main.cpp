/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#include <windows.h>
#include <bsgl.h>
#include "scene.h"
#include "menu_scene.h"
#include "credit_scene.h"
#include "game_scene.h"

BSGL* bsgl = 0;

// ����
Scene* scene = 0;
MenuScene* menu = 0;
CreditScene* credit = 0;
GameScene* game = 0;

// ��Ч
//HEFFECT beat1;
//HEFFECT beat2;
//HEFFECT beat3;

bool FrameFunc() {
    bsgl->Control_GetState();

#ifndef NDEBUG
    // �л������ģʽ
    if( bsgl->Control_IsUp(INP_TAB) ) {
        static int mode = 0;
        ++mode;
        if( mode >=3 ) mode = 0;
        bsgl->System_SetStateInt(BSGL_POLYMODE, mode);
    }
#endif

    // ��ESC�˳�
    if( bsgl->Control_IsPassing(INP_ESC) ) {
        if( MessageBoxA(0, "Really want to quit this game?", "Confirmation", MB_YESNO|MB_ICONQUESTION ) == IDYES ) {
            return true;
        }
    }

    // ��������
    return scene->Update();
}

#ifndef NDEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
    bsgl = bsglCreate(BSGL_VERSION);

    bsgl->System_SetStateInt(BSGL_SCREENWIDTH, 800);
    bsgl->System_SetStateInt(BSGL_SCREENHEIGHT, 600);
    bsgl->System_SetStateFunc(BSGL_RENDERFUNC, FrameFunc); //����֡������
    bsgl->System_SetStateInt(BSGL_NUMOFLFPS, 1);
    bsgl->System_SetStateInt(BSGL_NUMOFRFPS, 30);              //ÿ��30֡
    bsgl->System_SetStateString(BSGL_TITLE, "Heart A Run"); //����
    bsgl->System_SetStateBool(BSGL_WINDOWED, true);       //����ģʽ
    //bsgl->System_SetState(BSGL_HIDEMOUSE, false);     //���������
    bsgl->System_SetStateString(BSGL_LOGFILE, "game.log");  //��־


    if(bsgl->System_Initiate()) {
        // ��ʼ����Ϸ����
        menu = new MenuScene();
        credit = new CreditScene();
        game = new GameScene();
        //beat1 = bsgl->Effect_Load("media/beat1.ogg");
        //beat2 = bsgl->Effect_Load("media/beat2.ogg");
        //beat3 = bsgl->Effect_Load("media/beat3.ogg");

        // ��ʼ����Ϊ�˵����Ǹ�BSGL LOGO�������Զ��ӵģ�
        scene = menu;

        // ��ʼ�������
        bsgl->Random_Seed(timeGetTime());

        // �������棬������Ϸ��ѭ������ѭ���в��ϵ�ˢ֡������
        bsgl->System_Start();

        // �ͷ���Ϸ����
        //bsgl->Effect_Free(beat3);
        //bsgl->Effect_Free(beat2);
        //bsgl->Effect_Free(beat1);
        delete game;
        delete credit;
        delete menu;
    }else {
        // ������Ϣ
        MessageBoxA(NULL, bsgl->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }

    bsgl->System_Shutdown();

    bsgl->Release();

    return 0;
}
