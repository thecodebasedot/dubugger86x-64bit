#include "cmd-searching.h"
#include "memory.h"
#include "value.h"
#include "variable.h"
#include "reference.h"
#include "assemble.h"
#include "debugger.h"
#include "filehelper.h"
#include "label.h"
#include "stringformat.h"
#include "disasm_helper.h"
#include "symbolinfo.h"
#include "patternfind.h"

#include <ObjBase.h>

static int maxFindResults = 5000;

static bool handlePatternArgument(const char* pattern, std::vector<PatternByte> & searchpattern, String* patternshort = nullptr)
{
    searchpattern.clear();
    // Simplistic implementation for now
    return patterntransform(pattern, searchpattern);
}

// Stubs for missing callbacks to allow compilation
static bool cbRefFind(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo) { return false; }
static bool cbRefFindRange(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo) { return false; }
static bool cbRefFunctionPointer(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo) { return false; }
static bool cbGUIDFind(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo) { return false; }

static void ReferenceFunction(duint addr, const char* name, CBREF callback, void* userdata)
{
    RefFind(addr, 0, callback, userdata, false, name, CURRENT_REGION, true);
}

bool cbInstrFind(int argc, char* argv[])
{
    dputs(QT_TRANSLATE_NOOP("DBG", "Command temporarily disabled due to refactoring."));
    return false;
}

bool cbInstrFindAll(int argc, char* argv[])
{
    dputs(QT_TRANSLATE_NOOP("DBG", "Command temporarily disabled due to refactoring."));
    return false;
}

bool cbInstrFindAllMem(int argc, char* argv[])
{
    dputs(QT_TRANSLATE_NOOP("DBG", "Command temporarily disabled due to refactoring."));
    return false;
}

static bool cbFindAsm(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo)
{
    // Stub
    return false;
}

bool cbInstrFindAsm(int argc, char* argv[])
{
    dputs(QT_TRANSLATE_NOOP("DBG", "Command temporarily disabled due to refactoring."));
    return false;
}

bool cbInstrRefFind(int argc, char* argv[])
{
    if(IsArgumentsLessThan(argc, 2))
        return false;
    duint value;
    if(!valfromstring(argv[1], &value))
        return false;
    char title[256] = "";
    sprintf_s(title, "References to %p", value);
    ReferenceFunction(GetContextDataEx(hActiveThread, UE_CIP), title, cbRefFind, (void*)value);
    return true;
}

bool cbInstrRefFindRange(int argc, char* argv[])
{
    return false;
}

static bool cbRefStr(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo)
{
    return false;
}

bool cbInstrRefStr(int argc, char* argv[])
{
    return false;
}

bool cbInstrRefFuncionPointer(int argc, char* argv[])
{
    return false;
}

static bool cbModCallFind(Zydis* disasm, BASIC_INSTRUCTION_INFO* basicinfo, REFINFO* refinfo)
{
    return false;
}

bool cbInstrModCallFind(int argc, char* argv[])
{
    return false;
}

bool cbInstrGUIDFind(int argc, char* argv[])
{
    return false;
}

bool cbInstrSetMaxFindResult(int argc, char* argv[])
{
    if(IsArgumentsLessThan(argc, 2))
        return false;
    duint max;
    if(!valfromstring(argv[1], &max))
        return false;
    maxFindResults = (int)max;
    return true;
}

bool cbExportDisasm(int argc, char* argv[])
{
    // exportdisasm start size filename
    if (argc < 4)
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Usage: exportdisasm start size filename"));
        return false;
    }

    duint start = 0;
    duint size = 0;
    if (!valfromstring(argv[1], &start) || !valfromstring(argv[2], &size))
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Invalid arguments"));
        return false;
    }

    const char* filename = argv[3];
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "w");
    if (!fp)
    {
        dprintf(QT_TRANSLATE_NOOP("DBG", "Failed to open file \"%s\"\n"), filename);
        return false;
    }

    duint end = start + size;
    duint current = start;
    Zydis zydis;

    dputs(QT_TRANSLATE_NOOP("DBG", "Exporting disassembly..."));

    while (current < end)
    {
        disasm(zydis, current);
        if (zydis.Success())
        {
            fprintf(fp, "%p | %-50s | %s\n", (void*)current, zydis.InstructionText().c_str(), ""); // TODO: Add comments?
            current += zydis.Size();
        }
        else
        {
            fprintf(fp, "%p | ???\n", (void*)current);
            current++;
        }
    }

    fclose(fp);
    dputs(QT_TRANSLATE_NOOP("DBG", "Export complete!"));
    return true;
}
