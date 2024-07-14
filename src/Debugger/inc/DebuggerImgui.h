#pragma once

#include "DebuggerStrings.h"

#include <SDL2/SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

class DebuggerImgui : public DebuggerStrings
{
    SDL_GLContext gl_context;
    SDL_Window *window;
    std::string glsl_version;
    ImGuiIO *io;

    // Cons:
    void initSDL2();
    void consContext();
    void consWindow();
    void setupImgui();

    void newFrame();
    void endFrame();

    // Print:
    void showCPUstate();

    void printSingleRow(std::string rowName, std::string fstItem, std::string sndItem);
    void printSingleRow(const char *rowName, const char *fstItem, const char *sndItem);
    void printSingleRowWithColor(std::string rowName, std::string fstItem, std::string sndItem);
    void printSingleRowWithColor(const char *rowName, const char *fstItem, const char *sndItem);

    void printRegisters();
    void printFlags();
    void printOpcode();
    void printRadioButtons();
    void printCPUstate();

public:
    DebuggerImgui(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg);
    ~DebuggerImgui();
    void show();
};