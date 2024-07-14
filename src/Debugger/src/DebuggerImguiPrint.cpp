#include "DebuggerImgui.h"

void DebuggerImgui::printRadioButtons()
{
    Util::NumericalSystems tempNumeralSystem = numeralSystem;

    if (ImGui::RadioButton("Hex", numeralSystem == Util::HEX))
        tempNumeralSystem = Util::HEX;
    ImGui::SameLine();
    if (ImGui::RadioButton("Dec", numeralSystem == Util::DEC))
        tempNumeralSystem = Util::DEC;
    ImGui::SameLine();
    if (ImGui::RadioButton("Bin", numeralSystem == Util::BIN))
        tempNumeralSystem = Util::BIN;

    if (tempNumeralSystem != numeralSystem)
    {
        numeralSystem = tempNumeralSystem;
        updateDisplay();
    }
}

void DebuggerImgui::printRegisters()
{
    if (ImGui::CollapsingHeader("Regs"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRowWithColor("A:", RegA_display.current, RegA_display.old);
            printSingleRowWithColor("X:", RegX_display.current, RegX_display.old);
            printSingleRowWithColor("Y:", RegY_display.current, RegY_display.old);
            printSingleRowWithColor("PC:", RegPC_display.current, RegPC_display.old);
            printSingleRowWithColor("SP:", RegSP_display.current, RegSP_display.old);
            printSingleRowWithColor("Flags:", RegFlags_display.current, RegFlags_display.old);
            ImGui::EndTable();
        }
    }
}

void DebuggerImgui::printFlags()
{
    if (ImGui::CollapsingHeader("Flags"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRowWithColor("Carry", CarryFlag_display.current, CarryFlag_display.old);
            printSingleRowWithColor("Zero", ZeroFlag_display.current, ZeroFlag_display.old);
            printSingleRowWithColor("Interrupt Disable", IndFlag_display.current, IndFlag_display.old);
            printSingleRowWithColor("Decimal", DecimalFlag_display.current, DecimalFlag_display.old);
            printSingleRowWithColor("Break", BreakFlag_display.current, BreakFlag_display.old);
            printSingleRowWithColor("Unused", UnusedFlag_display.current, UnusedFlag_display.old);
            printSingleRowWithColor("Overflow", OverflowFlag_display.current, OverflowFlag_display.old);
            printSingleRowWithColor("Negative", NegativeFlag_display.current, NegativeFlag_display.old);
            ImGui::EndTable();
        }
    }
}

void DebuggerImgui::printOpcode()
{
    if (ImGui::CollapsingHeader("Current instruction"))
    {
        if (ImGui::BeginTable("table", 3))
        {
            printSingleRowWithColor("Name:", OpcodeSym_display.current, OpcodeSym_display.old);
            printSingleRowWithColor("Opcode:", OpcodeNumber_display.current, OpcodeNumber_display.old);
            printSingleRowWithColor("Adr. mode:", AdrMode_display.current, AdrMode_display.old);
            printSingleRowWithColor("No. of bytes:", NoOfBytes_display.current, NoOfBytes_display.old);
            printSingleRowWithColor("Cycles:", Cycles_display.current, Cycles_display.old);
            printSingleRowWithColor("Argument: ", Argument_display.current, Argument_display.old);
            ImGui::EndTable();
        }
    }
}

void DebuggerImgui::printSingleRow(const char *rowName, const char *fstItem, const char *sndItem)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(fstItem);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(sndItem);
}

void DebuggerImgui::printSingleRow(std::string rowName, std::string fstItem, std::string sndItem)
{
    printSingleRow(rowName.c_str(), fstItem.c_str(), sndItem.c_str());
}

void DebuggerImgui::printSingleRowWithColor(std::string rowName, std::string fstItem, std::string sndItem)
{
    printSingleRowWithColor(rowName.c_str(), fstItem.c_str(), sndItem.c_str());
}

void DebuggerImgui::printSingleRowWithColor(const char *rowName, const char *fstItem, const char *sndItem)
{
    ImU32 textColor = IM_COL32(255, 255, 255, 255);
    if (strcmp(fstItem, sndItem) != 0)
        textColor = IM_COL32(255, 0, 0, 255);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(fstItem);
    ImGui::TableNextColumn();
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);
    ImGui::TextUnformatted(sndItem);
    ImGui::PopStyleColor();
}

void DebuggerImgui::printCPUstate()
{
    if (ImGui::BeginTable("table", 3))
    {
        printSingleRowWithColor("CPU state: ", CPUstate_display.current, CPUstate_display.old);
        ImGui::EndTable();
    }
}