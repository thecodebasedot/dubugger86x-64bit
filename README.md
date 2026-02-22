# x64dbg (Enhanced Reverse Engineering Edition)

<img width="100" src="https://github.com/x64dbg/x64dbg/raw/development/src/bug_black.png"/>

An open-source binary debugger for Windows, aimed at malware analysis and reverse engineering of executables you do not have the source code for. This fork includes additional features specifically designed for **automated reverse engineering, code extraction, and patching**.

## New Features (Reverse Engineering & Patching)

This version includes powerful new commands to facilitate a complete reverse engineering workflow directly from the debugger:

### 1. `automod` (Auto-Analysis & Extraction)

Automatically analyzes the loaded executable, identifies the main module, and extracts the full disassembly to a file. This effectively gives you the "source code" (in assembly) of the target application.

**Usage:**

```bash
automod
```

- **Output:** Generates `dump_<target>.asm` containing the disassembly.
- **Workflow:** Load an EXE -> Run `automod` -> Open the .asm file to study the code.

### 2. `patchfile` (Save Patched Binary)

After modifying the code in memory (using the `asm` command or GUI), you can save the changes back to a functioning executable file. This allows for creating cracked or modified versions of software.

**Usage:**

```bash
patchfile <new_filename.exe>
```

- **Example:** `patchfile cracked_game.exe`

### 3. `applypatch` (Scripted Patching)

Apply a list of patches from a text file. This is useful for automating the patching process or sharing cracks/fixes.

**Usage:**

```bash
applypatch <patch_script.txt>
```

- **Script Format:**
  ```text
  0x00401000 nop
  0x00401001 mov eax, 1
  ```

### 4. `dumpprocess` (Full Dump)

Dumps all loaded modules (EXE and DLLs) from memory to disk. Useful for unpacking malware or extracting resources.

**Usage:**

```bash
dumpprocess [directory]
```

## Installation & Usage

1.  Clone this repository.
2.  Build the project using CMake.
3.  Run `x64\x64dbg.exe` or `x32\x32dbg.exe`.
4.  To use the headless mode for automation, run `bin\x64\headless.exe`.

## Original Credits

- Debugger core by [TitanEngine Community Edition](https://github.com/x64dbg/TitanEngine)
- Disassembly powered by [Zydis](https://zydis.re)
- Assembly powered by [XEDParse](https://github.com/x64dbg/XEDParse) and [asmjit](https://github.com/asmjit)
- Import reconstruction powered by [Scylla](https://github.com/NtQuery/Scylla)

## Contributing

This is a community effort. Feel free to open issues or submit pull requests for new reverse engineering features!
