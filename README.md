# s5M0802
Just a simple 8-Bit CPU with a quite small/basic jet powerfull instruction set.
The CPU has some MOS 6502 and Intel 80x86 elements e.g. the overall architecture follows the 6502's design ( exept for the 4 general
purpose registers ). The assembler and addressing follows the 80x86's design.

The CPU has 4 general-purpose registers : AX, BX, CX, DX  
  - AX - used as an accumulator  
  - BX - used together with AX in indirect addressing  
  - CX - used as a counter e.g. for loops etc.  
  - DX - used for I/O and is the drain for indirect addressing 
  
Special Registers : SP/ IR/ PCL/ PCH/ ADL/ ADH/ FR  
Exept for PCL/PCH and the SP those registers are not accessible by the user. There are also 2 programcounters one is used when the CPU
is in USER-MODE and the other one is used when the CPU is in KERNEL-MODE. When the CPU is in KERNEL-MODE the CPU is executing code stored
in the ROM but still uses the RAM when reading values exept for intermediates.

## Assembler
Operations :
  - mov
  - add/adc
  - sub/sbb
  - mul/ div
  - shr/ shl
  - and/ or/ xor/ not
  - inc CX/ dec CX
  - jmp/ jz/ jnz/ jc/ jnc/ call/ ret
  - push/ pop
  - in/ out
  - LDX/ STX
  
  ![alt text](https://i.imgur.com/eUQ5uX6.png)  
  
  There are multiple addressing-modes : Direct, Indirect, Zero-Page, Indexed, Intermediate
  Here are examples for those addressing-modes:
  ```git status
  // Intermediate
  mov BX,#8d
  // Zero Page
  mov AX,$7a
  // Direct
  mov DX,$7c0a
  // Indexed
  mov AX,$32+CX
  // Indirect LDX and STX they do not need parameters ( they are fixed ), this is their meaning
  mov DX,$[AX,BX] // LDX
  mov $[AX,BX],DX // STX
  ```
  
  ## Examples
  Here are some example programs and how they work.  
  Memory Dump ( just random dos dump from the internet ):  
  A simple program that reads all the values from a given page and prints the values to the terminal. The CPU uses the CX-register to
  loop through the selected page and uses a function (CALL and RET operations) that converts an hex value to an ASCII value.
  ![alt text](https://i.imgur.com/8sgpNwM.png)  
  Simple file-system :  
  A program that stores text files in RAM (starting locations are fixed: 0x1000/0x1500/0x1A00/...). It echos the input from the keyboard
  back into the RAM and uses indirect addressing in combination with the CX register to store input and to read the files.  
  When creating a file the memory looks something like this: 
  %FILE_NAME%file content....0xFF - "0xFF" marks the end of the file and "%" encloses the file name, the file-starting locations are fixed
  in memory (every 0x500 locations starting at 0x1000) so every file has a max. size of ~1280 characters but the fixed starting positions  
  guaranteed faster search times.
  ![alt text](https://i.imgur.com/jwivnTz.png)  
  ![alt text](https://i.imgur.com/nILyzbh.png)  
  ![alt text](https://i.imgur.com/JDi7lKy.png)  
