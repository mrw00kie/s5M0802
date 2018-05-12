#pragma once


class _operation
{
public:
	_operation(std::string op, std::string dr, std::string sr)
	{
		m_operation = op;
		m_drain = dr;
		m_source = sr;
		m_line = -1;
	}

	std::string m_operation;
	std::string m_drain;
	std::string m_source;
	int m_line;

};

struct jumpDestination
{
	std::string m_label;
	int m_line;
};

std::string calccode(_operation input)
{
	// operations without parameters
	if (input.m_drain.empty() && input.m_source.empty())
	{
		// SET/CLEAR FLAGS
		if (input.m_operation == "SEZ") return "01";
		if (input.m_operation == "CLZ") return "02";
		if (input.m_operation == "SEC") return "03";
		if (input.m_operation == "CLC") return "04";
		if (input.m_operation == "SEK") return "05";
		if (input.m_operation == "CLK") return "06";
		if (input.m_operation == "SEI") return "07";
		if (input.m_operation == "CLI") return "08";
		if (input.m_operation == "HLT") return "0f";
		// RETURN
		if (input.m_operation == "RET") return "6f";
		// mov DX,$[AX,BX] || mov $[AX,BX],DX
		if (input.m_operation == "LDX") return "9d";
		if (input.m_operation == "STX") return "9e";
		// Error
		std::cout << "ERROR ! line " << input.m_line << " Operation unknown or missing Operands ! "<< input.m_operation << std::endl;
		return "00";
	}
	// operations with one parameter
	else if (input.m_source.empty())
	{
		// PUSH
		if (input.m_operation == "PUSH")
		{
			if (input.m_drain == "AX") return "70";
			if (input.m_drain == "BX") return "71";
			if (input.m_drain == "CX") return "72";
			if (input.m_drain == "DX") return "73";
			if (input.m_drain == "FR") return "75";
			
			// Error
			std::cout << "ERROR ! line " << input.m_line << " Can not PUSH " << input.m_drain << std::endl;
			return "00";
		}

		// POP
		if (input.m_operation == "POP")
		{
			if (input.m_drain == "AX")  return "76";
			if (input.m_drain == "BX")  return "77";
			if (input.m_drain == "CX")  return "78";
			if (input.m_drain == "DX")  return "79";
			if (input.m_drain == "UPC") return "7a";
			if (input.m_drain == "FR")  return "7b";

			// Error
			std::cout << "ERROR ! line " << input.m_line << " Can not POP " << input.m_drain << std::endl;
			return "00";
		}

		// IN / OUT
		if (input.m_operation == "IN" || input.m_operation == "OUT")
		{
			input.m_drain.erase(std::remove(input.m_drain.begin(), input.m_drain.end(), '$'), input.m_drain.end());
			// Error
			if (input.m_drain.size() != 2)
			{
				// address too big
				std::cout << "ERROR ! line " << input.m_line << " Address is too big/small (only 8-Bit!) " << input.m_drain << std::endl;
				return "00";
			}
			if (input.m_operation == "IN")
				return "7f" + input.m_drain;
			else
				return "7e" + input.m_drain;
		}

		// NOT
		if (input.m_operation == "NOT")
		{
			if (input.m_drain == "AX")  return "3c";
			if (input.m_drain == "BX")  return "3d";

			// Error
			std::cout << "ERROR ! line " << input.m_line << " illegal (NOT) operand " << input.m_drain << std::endl;
			return "00";
		}

		// DEC CX/INC CX
		if (input.m_operation == "INC" && input.m_drain == "CX") return "3f";
		if (input.m_operation == "DEC" && input.m_drain == "CX") return "3E";
		// ERROR
		if (input.m_operation == "INC" || input.m_operation == "DEC")
		{
			std::cout << "ERROR ! line " << input.m_line << " can not INC/DEC " << input.m_drain << std::endl;
			return "00";
		}

		// call and jumps
		if (input.m_operation == "CALL")	return "$6e-" + input.m_drain;
		if (input.m_operation == "JMP")		return "$60-" + input.m_drain;
		if (input.m_operation == "JZ")		return "$62-" + input.m_drain;
		if (input.m_operation == "JNZ")		return "$64-" + input.m_drain;
		if (input.m_operation == "JC")		return "$66-" + input.m_drain;
		if (input.m_operation == "JNC")		return "$68-" + input.m_drain;

	}
	// operations with two parameter
	else
	{
		// Error
		if ((input.m_drain.find('$') != std::string::npos) && (input.m_source.find('$') != std::string::npos))
		{
			// two addresses
			std::cout << "ERROR ! line " << input.m_line << " Operation does not use two addresses ! " << input.m_operation << std::endl;
			return "00";
		}
		if ((input.m_drain.find('#') != std::string::npos) && (input.m_source.find('#') != std::string::npos))
		{
			// two intermediates
			std::cout << "ERROR ! line " << input.m_line << " Operation does not use two intermediates ! " << input.m_operation << std::endl;
			return "00";
		}
		// SOURCE is Intermediate
		if (input.m_source.find('#') != std::string::npos)
		{
			input.m_source.erase(0, 1);

			// MOV Intermediate
			if (input.m_operation == "MOV")
			{
				if (input.m_drain == "AX") return "80" + input.m_source;
				if (input.m_drain == "BX") return "81" + input.m_source;
				if (input.m_drain == "CX") return "82" + input.m_source;
				if (input.m_drain == "DX") return "83" + input.m_source;
				if (input.m_drain == "SP") return "84" + input.m_source;
				if (input.m_drain == "FR") return "85" + input.m_source;
				// Error
				std::cout << "ERROR ! line " << input.m_line << " Unknown Drain for MOV Intermediate " << input.m_drain << std::endl;
				return "00";
			}

			// ALU Intermediate
			if (input.m_drain == "AX")
			{
				if (input.m_operation == "ADD") return "c0" + input.m_source;
				if (input.m_operation == "ADC") return "c1" + input.m_source;
				if (input.m_operation == "SUB") return "c2" + input.m_source;
				if (input.m_operation == "SBB") return "c3" + input.m_source;
				if (input.m_operation == "MUL") return "c4" + input.m_source;
				if (input.m_operation == "DIV") return "c5" + input.m_source;
				if (input.m_operation == "SHR") return "c6" + input.m_source;
				if (input.m_operation == "SHL") return "c7" + input.m_source;
				if (input.m_operation == "AND") return "c8" + input.m_source;
				if (input.m_operation == "OR")  return "c9" + input.m_source;
				if (input.m_operation == "XOR") return "ca" + input.m_source;
			}

			// Error
			std::cout << "ERROR ! line " << input.m_line << " Unknown Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
			return "00";
		}

		// DRAIN is Address
		if (input.m_drain.find('$') != std::string::npos)
		{
			// Error
			if (input.m_operation != "MOV")
			{
				std::cout << "ERROR ! line " << input.m_line << " Operation does not use an address as drain " << input.m_operation << std::endl;
				return "00";
			}

			input.m_drain.erase(0, 1);

			// INDEXED
			if (input.m_drain.find('+') != std::string::npos)
			{
				int __startPos;
				if (input.m_drain.find("CX+") != std::string::npos)
					__startPos = input.m_drain.find("CX+");
				else
					__startPos = input.m_drain.find("+CX");
				input.m_drain.erase(__startPos, 3);

				if (input.m_source == "AX") return "b2" + input.m_drain;
				if (input.m_source == "BX") return "b3" + input.m_drain;

			}

			// SHORT ADDRESS
			if (input.m_drain.size() == 2)
			{
				if (input.m_source == "AX") return "a4" + input.m_drain;
				if (input.m_source == "BX") return "a5" + input.m_drain;
				if (input.m_source == "CX") return "a6" + input.m_drain;
				if (input.m_source == "DX") return "a7" + input.m_drain;
				if (input.m_source == "FR") return "aa" + input.m_drain;
				if (input.m_source == "SP") return "ab" + input.m_drain;

				// Error
				std::cout << "ERROR ! line " << input.m_line << " Unknown parameter for MOV to address " << input.m_source << std::endl;
				return "00";
			}
			// LONG ADDRESS
			if (input.m_drain.size() == 4)
			{
				// flip address
				std::string __t = "";
				__t += input.m_drain[2];
				__t += input.m_drain[3];
				__t += input.m_drain[0];
				__t += input.m_drain[1];

				if (input.m_source == "AX") return "94" + __t;
				if (input.m_source == "BX") return "95" + __t;
				if (input.m_source == "CX") return "96" + __t;
				if (input.m_source == "DX") return "97" + __t;
				if (input.m_source == "SP") return "99" + __t;
				if (input.m_source == "FR") return "9b" + __t;

				// Error
				std::cout << "ERROR ! line " << input.m_line << " Unknown operand for MOV register to address(long) " << input.m_source << std::endl;
				return "00";
			}

			// Error
			std::cout << "ERROR ! line " << input.m_line << " Unknown Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
			return "00";
		}
		// SOURCE is Address
		if (input.m_source.find('$') != std::string::npos)
		{
			input.m_source.erase(0, 1);

			// INDEXED
			if (input.m_source.find('+') != std::string::npos)
			{
				if (input.m_operation != "MOV")
				{
					// Error
					std::cout << "ERROR ! line " << input.m_line << " Unknown Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
					return "00";
				}
				int __startPos;
				if (input.m_source.find("CX+") != std::string::npos)
					__startPos = input.m_source.find("CX+");
				else
					__startPos = input.m_source.find("+CX");
				input.m_source.erase(__startPos, 3);
				
				if (input.m_drain == "AX") return "b0" + input.m_source;
				if (input.m_drain == "BX") return "b1" + input.m_source;

			}

			// SHORT ADDRESS
			if (input.m_source.size() == 2)
			{
				if (input.m_operation == "MOV")
				{
					if (input.m_drain == "AX") return "a0" + input.m_source;
					if (input.m_drain == "BX") return "a1" + input.m_source;
					if (input.m_drain == "CX") return "a2" + input.m_source;
					if (input.m_drain == "DX") return "a3" + input.m_source;
					if (input.m_drain == "FR") return "a8" + input.m_source;
					if (input.m_drain == "SP") return "a9" + input.m_source;

					// Error
					std::cout << "ERROR ! line " << input.m_line << " Unknown parameter for MOV address to register " << input.m_source << std::endl;
					return "00";
				}

				if (input.m_drain == "AX")
				{
					if (input.m_operation == "ADD") return "e0" + input.m_source;
					if (input.m_operation == "ADC") return "e1" + input.m_source;
					if (input.m_operation == "SUB") return "e2" + input.m_source;
					if (input.m_operation == "SBB") return "e3" + input.m_source;
					if (input.m_operation == "MUL") return "e4" + input.m_source;
					if (input.m_operation == "DIV") return "e5" + input.m_source;
					if (input.m_operation == "SHR") return "e6" + input.m_source;
					if (input.m_operation == "SHL") return "e7" + input.m_source;
					if (input.m_operation == "AND") return "e8" + input.m_source;
					if (input.m_operation == "OR")  return "e9" + input.m_source;
					if (input.m_operation == "XOR") return "ea" + input.m_source;
				}
			}
			// Long Address
			if (input.m_source.size() == 4)
			{
				// flip address
				std::string __t = "";
				__t += input.m_source[2];
				__t += input.m_source[3];
				__t += input.m_source[0];
				__t += input.m_source[1];

				if (input.m_operation == "MOV")
				{
					if (input.m_drain == "AX") return "90" + __t;
					if (input.m_drain == "BX") return "91" + __t;
					if (input.m_drain == "CX") return "92" + __t;
					if (input.m_drain == "DX") return "93" + __t;
					if (input.m_drain == "SP") return "98" + __t;
					if (input.m_drain == "FR") return "9a" + __t;

					// Error
					std::cout << "ERROR ! line " << input.m_line << " Unknown operand for MOV address (long) to register "  << input.m_drain << std::endl;
					return "00";
				}
			}

			// Error
			std::cout << "ERROR ! line " << input.m_line << " Unknown Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
			return "00";
		}

		// No Addresses
		// MOV
		if (input.m_operation == "MOV")
		{
			if (input.m_source == "AX")
			{
				if (input.m_drain == "BX") return "10";
				if (input.m_drain == "CX") return "11";
				if (input.m_drain == "DX") return "12";
				if (input.m_drain == "SP") return "1e";
			}
			if (input.m_source == "BX")
			{
				if (input.m_drain == "AX") return "13";
				if (input.m_drain == "CX") return "14";
				if (input.m_drain == "DX") return "15";
				if (input.m_drain == "SP") return "1f";
			}
			if (input.m_source == "CX")
			{
				if (input.m_drain == "AX") return "16";
				if (input.m_drain == "BX") return "17";
				if (input.m_drain == "DX") return "18";
			}
			if (input.m_source == "DX")
			{
				if (input.m_drain == "AX") return "19";
				if (input.m_drain == "BX") return "1a";
				if (input.m_drain == "CX") return "1b";
			}
			if (input.m_source == "SP")
			{
				if (input.m_drain == "AX") return "1c";
				if (input.m_drain == "BX") return "1d";
			}
			// Error
			std::cout << "ERROR ! line " << input.m_line << " Illegal MOV Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
			return "00";
		}
		// ALU
		if (input.m_drain == "AX" && input.m_source == "BX")
		{
			if (input.m_operation == "ADD") return "30";
			if (input.m_operation == "ADC") return "31";
			if (input.m_operation == "SUB") return "32";
			if (input.m_operation == "SBB") return "33";
			if (input.m_operation == "MUL") return "34";
			if (input.m_operation == "DIV") return "35";
			if (input.m_operation == "SHR") return "36";
			if (input.m_operation == "SHL") return "37";
			if (input.m_operation == "AND") return "38";
			if (input.m_operation == "OR")  return "39";
			if (input.m_operation == "XOR") return "3a";
		}
	}

	// Error
	std::cout << "ERROR ! line " << input.m_line << " Unknown Operation " << input.m_operation << " " << input.m_drain << "," << input.m_source << std::endl;
	return "00";
}