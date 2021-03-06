#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();

    eglView->setFrameSize(1280, 720);
    return CCApplication::sharedApplication()->run();
}

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

/*int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setViewName("Circle Boom ver0.1"); //�� ����
    eglView.setFrameSize(1280, 720);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    // eglView.setDesignResolutionSize(480, 320);

    int ret = CCApplication::sharedApplication().run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
*/