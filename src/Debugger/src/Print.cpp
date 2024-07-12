#include "Debugger.h"

#include <stdexcept>

void Debugger::printByteAndUpdate(const char *rowName, u8 currentState, u8 &oldStateToBeUpdated)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(byteToStrBase(currentState));
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(byteToStrBase(oldStateToBeUpdated));
    oldStateToBeUpdated = currentState;
}

void Debugger::printShortAndUpdate(const char *rowName, u16 currentState, u16 &oldStateToBeUpdated)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(shortToStrBase(currentState));
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(shortToStrBase(oldStateToBeUpdated));
    oldStateToBeUpdated = currentState;
}

void Debugger::printNameAndUpdate()
{
    const u8 currentOpcode = cpuObj->getCurrentIns();
    const auto it = opcodeToName.find(currentOpcode);
    if (it == opcodeToName.end())
        throw std::runtime_error("Debugger::printNameAndUpdate(const char *rowName)"); // maybe automate this?
    std::string currentOpcodeName = it->second;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted("Name: ");
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(currentOpcodeName.c_str());
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(prevOpcodeName.c_str());
    prevOpcodeName = currentOpcodeName;
}

void Debugger::printCPUstate()
{
    const auto itCPUmode = cpuStateToName.find(cpuObj->getState());
    if (itCPUmode == cpuStateToName.end())
        throw std::runtime_error("Debugger::printCPUstate()");
    const char *cpuState = itCPUmode->second;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted("CPU state: ");
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(cpuState);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(prevCPUstate.c_str());
    prevCPUstate = cpuState;
}

void Debugger::printAdrModeAndUpdate(CPU::ADR_MODE currentMode)
{
    const auto itAdrMode = adrModeToName.find(currentMode);
    if (itAdrMode == adrModeToName.end())
        throw std::runtime_error("Debugger::showCPUstats()");
    const char *adrModeName = itAdrMode->second;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted("Adr. mode:");
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(adrModeName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(prevAdrModeName.c_str());
    prevAdrModeName = adrModeName;
}

// TODO: 3 above functions can be merged but it is not trivial if possible.

void Debugger::printFlagsRegAndUpdate()
{
    const FlagsReg currentFlags = cpuObj->getRegFlagsObj();
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted("Reg Flags:");
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(byteToStrBase(currentFlags.getVal()));
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(byteToStrBase(prevRegFlags.getVal()));
    prevRegFlags = currentFlags;
}

void Debugger::printFlagState(const char *rowName, flagFun fun)
{
    const char *vals[] = {"False", "True"};
    const FlagsReg currentFlags = cpuObj->getRegFlagsObj();
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(rowName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(vals[(currentFlags.*fun)()]);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(vals[(prevRegFlags.*fun)()]);
}

void Debugger::printArgument(u8 noOfBytes)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted("Argument:");
    ImGui::TableNextColumn();
    if (noOfBytes == 0)
    {
        ImGui::TextUnformatted("None");
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(prevArgument.c_str());

        prevArgument = "None";
    }
    else
    {
        const u16 curPC = cpuObj->getRegPC();
        const u16 val = Util::getBytesFromMemAfterIdx(memory, curPC, noOfBytes);
        const std::string argStr = shortToStrBase(val);

        ImGui::TextUnformatted(argStr.c_str());
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(prevArgument.c_str());

        prevArgument = argStr;
    }
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

const char* Debugger::valToStrBaseGeneric(u64 val) const
{
    return Util::toSystem(val, numeralSystem).c_str();
}

const char* Debugger::byteToStrBase(u8 val) const // this is not needed
{
    return valToStrBaseGeneric(val);
}

const char* Debugger::shortToStrBase(u16 val) const
{
    return valToStrBaseGeneric(val);
}