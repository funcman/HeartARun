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

// 场景
Scene* scene = 0;
MenuScene* menu = 0;
CreditScene* credit = 0;
GameScene* game = 0;

// 音效
//HEFFECT beat1;
//HEFFECT beat2;
//HEFFECT beat3;

bool FrameFunc() {
    bsgl->Control_GetState();

#ifndef NDEBUG
    // 切换多边形模式
    if( bsgl->Control_IsUp(INP_TAB) ) {
        static int mode = 0;
        ++mode;
        if( mode >=3 ) mode = 0;
        bsgl->System_SetStateInt(BSGL_POLYMODE, mode);
    }
#endif

    // 按ESC退出
    if( bsgl->Control_IsPassing(INP_ESC) ) {
        if( MessageBoxA(0, "Really want to quit this game?", "Confirmation", MB_YESNO|MB_ICONQUESTION ) == IDYES ) {
            return true;
        }
    }

    // 场景更新
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
    bsgl->System_SetStateFunc(BSGL_RENDERFUNC, FrameFunc); //设置帧处理函数
    bsgl->System_SetStateInt(BSGL_NUMOFLFPS, 1);
    bsgl->System_SetStateInt(BSGL_NUMOFRFPS, 30);              //每秒30帧
    bsgl->System_SetStateString(BSGL_TITLE, "Heart A Run"); //标题
    bsgl->System_SetStateBool(BSGL_WINDOWED, true);       //窗口模式
    //bsgl->System_SetState(BSGL_HIDEMOUSE, false);     //不隐藏鼠标
    bsgl->System_SetStateString(BSGL_LOGFILE, "game.log");  //日志


    if(bsgl->System_Initiate()) {
        // 初始化游戏对象
        menu = new MenuScene();
        credit = new CreditScene();
        game = new GameScene();
        //beat1 = bsgl->Effect_Load("media/beat1.ogg");
        //beat2 = bsgl->Effect_Load("media/beat2.ogg");
        //beat3 = bsgl->Effect_Load("media/beat3.ogg");

        // 初始场景为菜单（那个BSGL LOGO是引擎自动加的）
        scene = menu;

        // 初始随机种子
        bsgl->Random_Seed(timeGetTime());

        // 启动引擎，进入游戏主循环，主循环中不断地刷帧处理函数
        bsgl->System_Start();

        // 释放游戏对象
        //bsgl->Effect_Free(beat3);
        //bsgl->Effect_Free(beat2);
        //bsgl->Effect_Free(beat1);
        delete game;
        delete credit;
        delete menu;
    }else {
        // 错误信息
        MessageBoxA(NULL, bsgl->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }

    bsgl->System_Shutdown();

    bsgl->Release();

    return 0;
}
