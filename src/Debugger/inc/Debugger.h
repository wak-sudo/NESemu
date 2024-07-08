#pragma once

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

public:
    Debugger();
    ~Debugger();
    void show();
};