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

// 场景
Scene* scene = 0;
MenuScene* menu = 0;
CreditScene* credit = 0;
GameScene* game = 0;

// 音效
HEFFECT beat1;
HEFFECT beat2;
HEFFECT beat3;

bool FrameFunc() {
    // 按ESC退出
    if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
        if( MessageBoxA(0, "Really want to quit this game?", "Confirmation", MB_YESNO|MB_ICONQUESTION ) == IDYES ) {
            return true;
        }
    }

    // 场景更新
    return scene->Update();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    hge = hgeCreate(HGE_VERSION);

    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc); //设置帧处理函数
    hge->System_SetState(HGE_FPS, 30);              //每秒30帧
    hge->System_SetState(HGE_TITLE, "Heart A Run"); //标题
    hge->System_SetState(HGE_WINDOWED, true);       //窗口模式
    hge->System_SetState(HGE_HIDEMOUSE, false);     //不隐藏鼠标
    hge->System_SetState(HGE_LOGFILE, "game.log");  //日志


    if(hge->System_Initiate()) {
        // 初始化游戏对象
        menu = new MenuScene();
        credit = new CreditScene();
        game = new GameScene();
        beat1 = hge->Effect_Load("media/beat1.ogg");
        beat2 = hge->Effect_Load("media/beat2.ogg");
        beat3 = hge->Effect_Load("media/beat3.ogg");

        // 初始场景为菜单（那个HGE LOGO是引擎自动加的）
        scene = menu;

        // 初始随机种子
        hge->Random_Seed(timeGetTime());

        // 启动引擎，进入游戏主循环，主循环中不断地刷帧处理函数
        hge->System_Start();

        // 释放游戏对象
        hge->Effect_Free(beat3);
        hge->Effect_Free(beat2);
        hge->Effect_Free(beat1);
        delete game;
        delete credit;
        delete menu;
    }else {
        // 错误信息
        MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }

    hge->System_Shutdown();

    hge->Release();

    return 0;
}
