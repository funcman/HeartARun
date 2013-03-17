/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/
#if defined(WIN32)
#include <windows.h>
#elif defined(__MACH__)
#include <SDL/SDL.h>
#endif
#include <bsgl.h>
#include "scene.h"
#include "menu_scene.h"
#include "credit_scene.h"
#include "game_scene.h"

BSGL* bsgl = 0;

// Scenes
Scene* scene = 0;
MenuScene* menu = 0;
CreditScene* credit = 0;
GameScene* game = 0;

// Effects
//HEFFECT beat1;
//HEFFECT beat2;
//HEFFECT beat3;

// for non-win32
#if !defined(WIN32)
#include <unistd.h>
#include <time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
unsigned int timeGetTime() {
    struct timespec ts;
// OS X does not have clock_gettime, use clock_get_time
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    return ts.tv_sec*1000 + ts.tv_nsec/1000000;
}
#endif

bool FrameFunc() {
    bsgl->Control_GetState();

#ifndef NDEBUG
    // swtich polygon mode
    if( bsgl->Control_IsUp(INP_TAB) ) {
        static int mode = 0;
        ++mode;
        if( mode >=3 ) mode = 0;
        bsgl->System_SetStateInt(BSGL_POLYMODE, mode);
    }
#endif

// push ESC to exit on windows
#if defined(WIN32)
    if( bsgl->Control_IsPassing(INP_ESC) ) {
        if( MessageBoxA(0, "Really want to quit this game?", "Confirmation", MB_YESNO|MB_ICONQUESTION ) == IDYES ) {
            return true;
        }
    }
#endif

    // update
    return scene->Update();
}

#if defined(NDEBUG) && defined(WIN32)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main(int argc, char** argv) {
#endif
    bsgl = bsglCreate(BSGL_VERSION);

    bsgl->System_SetStateInt(BSGL_SCREENWIDTH, 800);
    bsgl->System_SetStateInt(BSGL_SCREENHEIGHT, 600);
    bsgl->System_SetStateFunc(BSGL_RENDERFUNC, FrameFunc);  // set the frame function
    bsgl->System_SetStateInt(BSGL_NUMOFLFPS, 1);
    bsgl->System_SetStateInt(BSGL_NUMOFRFPS, 30);           // 30 fps
    bsgl->System_SetStateString(BSGL_TITLE, "Heart A Run"); // windows title
    bsgl->System_SetStateBool(BSGL_WINDOWED, true);         // window mode
    //bsgl->System_SetState(BSGL_HIDEMOUSE, false);         // don't hide mouse
    bsgl->System_SetStateString(BSGL_LOGFILE, "game.log");  // the log file


    if(bsgl->System_Initiate()) {
        // game objects initialization
        menu = new MenuScene();
        credit = new CreditScene();
        game = new GameScene();
        //beat1 = bsgl->Effect_Load("media/beat1.ogg");
        //beat2 = bsgl->Effect_Load("media/beat2.ogg");
        //beat3 = bsgl->Effect_Load("media/beat3.ogg");

        // the begining scene is meun
        scene = menu;

        // random seed initialization
        bsgl->Random_Seed(timeGetTime());

        // engine start, into the game loop, and process the frame function in each cycle
        bsgl->System_Start();

        // game objects free
        //bsgl->Effect_Free(beat3);
        //bsgl->Effect_Free(beat2);
        //bsgl->Effect_Free(beat1);
        delete game;
        delete credit;
        delete menu;
    }else {
        // error information
#if defined(WIN32)
        MessageBoxA(NULL, bsgl->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#else
        printf("Error: %s\n", bsgl->System_GetErrorMessage());
#endif
    }

    bsgl->System_Shutdown();

    bsgl->Release();

    return 0;
}
