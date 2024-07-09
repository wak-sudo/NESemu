#include "Debugger.h"

#include "Util.h"

#include <iostream>

#include "imgui_memory_editor.h"

void Debugger::show()
{
    bool done;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    u64 memSize = 1024;
    u8 *mem = new u8[memSize];

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

        // mem_edit.DrawWindow("Memory Editor", mem, memSize);

        showCPUstats();

        ImGui::Render();
        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    delete[] mem;
}

void Debugger::showCPUstats()
{
    ImGui::SetNextWindowSize(ImVec2(640, 780), ImGuiCond_FirstUseEver);
    bool closed;
    ImGui::Begin("CPU state", &closed);

    static Util::NumericalSystems setNumeralSystem = Util::HEX; // it has to be static, dunno why.

    std::string cusPrintReg(u8 val, std::string & update)
    {
        update = Util::toSystem(val, setNumeralSystem);
        return Util::toSystem(val, setNumeralSystem);
    }

    std::string cusPrintFlags(u8 val )

    std::string cusPrint(u16 val, std::string & update)
    {
        update = Util::toSystem(val, setNumeralSystem);
        return Util::toSystem(val, setNumeralSystem);
    }

    if (ImGui::RadioButton("Hex", setNumeralSystem == Util::HEX))
    {
        setNumeralSystem = Util::HEX;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Dec", setNumeralSystem == Util::DEC))
    {
        setNumeralSystem = Util::DEC;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Bin", setNumeralSystem == Util::BIN))
    {
        setNumeralSystem = Util::BIN;
    }

    if (ImGui::BeginTable("table", 3))
    {
        printSingleRow("Field", "Current state", "Old state");
        ImGui::EndTable();
    }

    if (ImGui::CollapsingHeader("Regs"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRow("Reg A:", cusPrint(cpuObj->getRegA(), prevStates[0]), prevStates[0]);
            printSingleRow("Reg X:", cusPrint(cpuObj->getRegX(), prevStates[1]), prevStates[1]);
            printSingleRow("Reg Y:", cusPrint(cpuObj->getRegY(), prevStates[2]), prevStates[2]);
            printSingleRow("Reg PC:", cusPrint(cpuObj->getRegPC(), prevStates[3]), prevStates[3]);
            printSingleRow("Reg SP:", cusPrint(cpuObj->getRegSP(), prevStates[4]), prevStates[4]);
            printSingleRow("Reg Flags:", cusPrint(cpuObj->getRegFlags(), prevStates[5]), prevStates[5]);
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader("Flags"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRow("Carry", cusPrint(cpuObj->getRegA(), prevStates[6]), prevStates[6]);
            printSingleRow("Zero", cusPrint(cpuObj->getRegA(), prevStates[7]), prevStates[7]);
            printSingleRow("Interrupt Disable", cusPrint(cpuObj->getRegA(), prevStates[8]), prevStates[8]);
            printSingleRow("Decimal", cusPrint(cpuObj->getRegA(), prevStates[9]), prevStates[9]);
            printSingleRow("B flag", cusPrint(cpuObj->getRegA(), prevStates[10]), prevStates[10]);
            printSingleRow("Unused", cusPrint(cpuObj->getRegA(), prevStates[11]), prevStates[11]);
            printSingleRow("Overflow", cusPrint(cpuObj->getRegA(), prevStates[12]), prevStates[12]);
            printSingleRow("Negative", cusPrint(cpuObj->getRegA(), prevStates[13]), prevStates[13]);
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader("Current instruction"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRow("Name:", "Old cont", "New cont");
            printSingleRow("Adr. mode:", "Old cont", "New cont");
            printSingleRow("No. of bytes:", "Old cont", "New cont");
            printSingleRow("Opcode:", "Old cont", "New cont");
            printSingleRow("Cycles:", "Old cont", "New cont");
            printSingleRow("Argument:", "Old cont", "New cont");
            ImGui::EndTable();
        }
    }

    if (ImGui::BeginTable("table", 3))
    {
        printSingleRow("CPU state:", "Old cont", "New cont");
        ImGui::EndTable();
    }

    if (ImGui::Button("StepButton"))
    {
        std::cout << "Step!" << std::endl;
    }

    ImGui::End();
}

void Debugger::printSingleRow(const char *rowName, const char *fstItem, const char *sndItem)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(fstItem);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(sndItem);
}