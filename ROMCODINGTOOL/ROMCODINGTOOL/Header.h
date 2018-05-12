#include <string>

int rom_one(std::string x)
{
	if (x == "DL/SB")
		return 0x1;
	if (x == "DL/DB")
		return 0x2;
	if (x == "AX/SB")
		return 0x4;
	if (x == "BX/SB")
		return 0x8;
	
	if (x == "DX/SB")
		return 0x10;
	if (x == "SB/DB")
		return 0x20;
	if (x == "DB/SB")
		return 0x40;
	if (x == "SB/CX")
		return 0x80;

	if (x == "SB/SP")
		return 0x100;
	if (x == "FR/DB")
		return 0x200;
	if (x == "SP/SB")
		return 0x400;
	if (x == "CX/SB")
		return 0x800;

	if (x == "SB/AX")
		return 0x1000;
	if (x == "SB/BX")
		return 0x2000;
	if (x == "SB/DX")
		return 0x4000;
	if (x == "SB/B")
		return 0x8000;

	if (x == "DB/A")
		return 0x10000;
	if (x == "0/A")
		return 0x20000;
	if (x == "!DB/A")
		return 0x40000;
	if (x == "ADL/PCL")
		return 0x80000;

	if (x == "ADH/PCH")
		return 0x100000;
	if (x == "INTVEC")
		return 0x200000;
	if (x == "HLT")
		return 0x400000;


	return 0;
}

int rom_two(std::string x)
{
	if (x == "1/ADH")
		return 0x1;
	if (x == "0/ADH")
		return 0x2;
	if (x == "ADL/ABL")
		return 0x4;
	if (x == "ADH/ABH")
		return 0x8;

	if (x == "SB/ADL")
		return 0x10;
	if (x == "ADL/SB")
		return 0x20;
	if (x == "SB/ADH")
		return 0x40;
	if (x == "ADH/SB")
		return 0x80;

	if (x == "ADL/UPCL")
		return 0x100;
	if (x == "ADH/UPCH")
		return 0x200;
	if (x == "ADL/KPCL")
		return 0x400;
	if (x == "ADH/KPCH")
		return 0x800;

	if (x == "ADL/SP")
		return 0x1000;
	if (x == "DL/ADL")
		return 0x2000;
	if (x == "DL/ADH")
		return 0x4000;
	if (x == "PCL/ADL")
		return 0x8000;

	if (x == "PCH/ADH")
		return 0x10000;
	if (x == "ADL/A")
		return 0x20000;
	if (x == "ADH/A")
		return 0x40000;
	if (x == "INT/ADL")
		return 0x80000;

	if (x == "SP/ADL")
		return 0x100000;
	if (x == "CX/ADL")
		return 0x200000;
	if (x == "DSP")
		return 0x400000;
	if (x == "ISP")
		return 0x800000;

	if (x == "IPC")
		return 0x1000000;
	if (x == "ICX")
		return 0x2000000;
	if (x == "DCX")
		return 0x4000000;
	if (x == "KOR")
		return 0x8000000;

	if (x == "CALLVEC")
		return 0x10000000;
	if (x == "RETVEC")
		return 0x20000000;

	return 0;
}

int rom_three(std::string x)
{
	if (x == "ALUOP")
		return 0x1;
	if (x == "AND")
		return 0x2;
	if (x == "SHL")
		return 0x4;
	if (x == "SHR")
		return 0x8;

	if (x == "OR")
		return 0x10;
	if (x == "XOR")
		return 0x20;
	if (x == "NOT")
		return 0x40;
	if (x == "ADD")
		return 0x80;

	if (x == "ADC")
		return 0x100;
	if (x == "SUB")
		return 0x200;
	if (x == "SBB")
		return 0x400;
	if (x == "MUL")
		return 0x800;

	if (x == "DIV")
		return 0x1000;
	if (x == "0/B")
		return 0x2000;
	if (x == "1/B")
		return 0x4000;
	if (x == "CLK")
		return 0x8000;

	if (x == "SEK")
		return 0x10000;
	if (x == "CLI")
		return 0x20000;
	if (x == "SEI")
		return 0x40000;
	if (x == "CLZ")
		return 0x80000;

	if (x == "SEZ")
		return 0x100000;
	if (x == "CLC")
		return 0x200000;
	if (x == "SEC")
		return 0x400000;
	if (x == "DEV")
		return 0x800000;

	if (x == "R/W")
		return 0x1000000;
	if (x == "D/IR")
		return 0x2000000;
	if (x == "CYEND")
		return 0x4000000;
	if (x == "DB/FR")
		return 0x8000000;

	return 0;
}