#pragma once

#include "CPU.h"
#include "FlagsReg.h"

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

typedef u8 (FlagsReg::*flagFun)() const;

class Debugger
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

    // Print:
    Util::NumericalSystems numeralSystem = Util::HEX;
    const char *valToStrBaseGeneric(u64 val) const;
    const char *byteToStrBase(u8 val) const;
    const char *shortToStrBase(u16 val) const;
    void printSingleRow(const char *rowName, const char *fstItem, const char *sndItem);
    void printByteAndUpdate(const char *rowName, u8 currentState, u8 &oldStateToBeUpdated);
    void printShortAndUpdate(const char *rowName, u16 currentState, u16 &oldStateToBeUpdated);
    void printNameAndUpdate();
    void printAdrModeAndUpdate(CPU::ADR_MODE currentMode);
    void printFlagsRegAndUpdate();
    void printArgument(u8 noOfBytes);
    void printCPUstate();
    void printFlagState(const char *rowName, flagFun fun);

    // Debugger
    void showCPUstate();

    static const std::unordered_map<u8, const char *> opcodeToName;
    static const std::unordered_map<CPU::ADR_MODE, const char *> adrModeToName;
    static const std::unordered_map<CPU::CPU_STATE, const char *> cpuStateToName;

    CPU *cpuObj;
    u8 *memory;
    u64 memorySize;

    // prev states
    const std::string none = "None";
    u8 prevRegA = 0;
    u8 prevRegX = 0;
    u8 prevRegY = 0;
    u8 prevRegSP = 0;
    u16 prevRegPC = 0;
    FlagsReg prevRegFlags;

    std::string prevOpcodeName = none;
    std::string prevAdrModeName = none;
    std::string prevArgument = none;
    u8 prevNoOfBytes = 0;
    u8 prevOpcodeNumber = 0;
    u8 prevCycles = 0;

    std::string prevCPUstate = none;

public:
    Debugger(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg);
    ~Debugger();
    void show();
};