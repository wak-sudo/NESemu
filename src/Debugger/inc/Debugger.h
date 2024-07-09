#pragma once

#include "CPU.h"

#include <SDL2/SDL.h>
#include <string>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

class Debugger
{
    SDL_GLContext gl_context;
    SDL_Window *window;
    std::string glsl_version;
    ImGuiIO *io;

    void initSDL2();
    void consContext();
    void consWindow();
    void setupImgui();

    void showCPUstats();
    void printSingleRow(const char *rowName, const char *fstItem, const char *sndItem);

    CPU *cpuObj;

    // prev states
    const std::string none = "None";
    std::string prevStates[20];
    std::string prevRegX = none;
    std::string prevRegY = none;
    std::string prevRegSP = none;
    std::string prevRegPC = none;
    std::string prevRegFlags = none;

    std::string prevCarry = none;
    std::string prevZero = none;
    std::string prevInterrupt = none;
    std::string prevDecimal = none;
    std::string prevBflag = none;
    std::string prevUnusedBit = none;
    std::string prevOverflow = none;
    std::string prevNegative = none;

    std::string prevOpcodeName = none;
    std::string prevAdrMode = none;
    std::string prevNoOfBytes = none;
    std::string prevOpcodeNumber = none;
    std::string prevCycles = none;
    std::string prevArgument = none;

    std::string prevCPUstate = none;

public:
    Debugger(CPU *cpuObjArg);
    ~Debugger();
    void show();
};