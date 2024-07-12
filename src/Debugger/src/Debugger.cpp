#include "Debugger.h"

#include "Util.h"

#include <iostream>

#include "imgui_memory_editor.h"

void Debugger::show()
{
    bool done;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    MemoryEditor mem_edit;

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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(/*&show_demo_window*/);

        /*{
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            //ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
            ImGui::End();
        }*/

        // mem_edit.DrawWindow("Memory Editor", memory, memorySize);

        showCPUstate();

        ImGui::Render();
        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

}

void Debugger::showCPUstate()
{
    ImGui::SetNextWindowSize(ImVec2(640, 780), ImGuiCond_FirstUseEver);
    bool closed;
    ImGui::Begin("CPU state", &closed);

    // static Util::NumericalSystems tempNumeralSystem = Util::HEX; // it has to be static, dunno why.

    if (ImGui::RadioButton("Hex", numeralSystem == Util::HEX))
        numeralSystem = Util::HEX;
    ImGui::SameLine();
    if (ImGui::RadioButton("Dec", numeralSystem == Util::DEC))
        numeralSystem = Util::DEC;
    ImGui::SameLine();
    if (ImGui::RadioButton("Bin", numeralSystem == Util::BIN))
        numeralSystem = Util::BIN;

    if (ImGui::BeginTable("table", 3))
    {
        printSingleRow("Field", "Current state", "Old state");
        ImGui::EndTable();
    }

    if (ImGui::CollapsingHeader("Regs"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printByteAndUpdate("Reg A:", cpuObj->getRegA(), prevRegA);
            printByteAndUpdate("Reg X:", cpuObj->getRegX(), prevRegX);
            printByteAndUpdate("Reg Y:", cpuObj->getRegY(), prevRegY);
            printShortAndUpdate("Reg PC:", cpuObj->getRegPC(), prevRegPC);
            printByteAndUpdate("Reg SP:", cpuObj->getRegSP(), prevRegSP);
            printFlagsRegAndUpdate();
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader("Flags"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printFlagState("Carry", &FlagsReg::getFlagCarry);
            printFlagState("Zero", &FlagsReg::getFlagZero);
            printFlagState("Interrupt Disable", &FlagsReg::getFlagInd);
            printFlagState("Decimal", &FlagsReg::getFlagDecimal);
            printFlagState("Break", &FlagsReg::getFlagBreak);
            printFlagState("Unused", &FlagsReg::getFlagUnused);
            printFlagState("Overflow", &FlagsReg::getFlagOverflow);
            printFlagState("Negative", &FlagsReg::getFlagNegative);
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader("Current instruction"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            const u8 currentOpcode = cpuObj->getCurrentIns();
            const auto opcodeInfo = cpuObj->getOpcodeInfo(currentOpcode);
            const u8 currentCycles = std::get<0>(opcodeInfo);
            const CPU::ADR_MODE currentMode = std::get<1>(opcodeInfo);
            const u8 currentBytes = std::get<2>(opcodeInfo);

            printNameAndUpdate(); // maybe printSingleRow
            printByteAndUpdate("Opcode:", currentOpcode, prevOpcodeNumber);
            printAdrModeAndUpdate(currentMode);
            printByteAndUpdate("No. of bytes:", currentBytes, prevNoOfBytes);
            printByteAndUpdate("Cycles:", currentCycles, prevCycles);
            printArgument(currentBytes);
            ImGui::EndTable();
        }
    }

    if (ImGui::BeginTable("table", 3))
    {
        printCPUstate();
        ImGui::EndTable();
    }

    if (ImGui::Button("StepButton"))
    {
        std::cout << "Step!" << std::endl;
    }

    ImGui::End();
}