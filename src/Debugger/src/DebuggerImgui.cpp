#include "DebuggerImgui.h"

#include "imgui_memory_editor.h"

void DebuggerImgui::showCPUstate()
{
    ImGui::SetNextWindowSize(ImVec2(340, 550));
    bool closed;
    ImGui::Begin("CPU state", &closed);

    printRadioButtons();

    if (ImGui::BeginTable("table", 3))
    {
        printSingleRow("Field", "Current state", "Old state");
        ImGui::EndTable();
    }

    printRegisters();
    printFlags();
    printOpcode();
    printCPUstate();

    if (ImGui::Button("StepButton"))
    {
        step();
    }

    ImGui::End();
}

void DebuggerImgui::show()
{
    bool done;

    MemoryEditor mem_edit;
    MemoryEditor stack_edit;

    u8* const stackMem = memory + StackReg::STACK_OFFSET;

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        startFrame();

        mem_edit.DrawWindow("Memory view", memory, memorySize);
        stack_edit.DrawWindow("Stack view", stackMem, StackReg::STACK_MAX_SIZE);

        showCPUstate();

        endFrame();
    }
}

void DebuggerImgui::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void DebuggerImgui::endFrame()
{
    const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::Render();
    glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}