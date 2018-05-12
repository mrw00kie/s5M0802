#include <string>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <vector>

#include "compiler.h"


int main(int argc, char* argv[])
{
	// DRAG / PATH
	std::string path;
	if (argc <= 1)
	{
		std::cout << "Enter file path: ";
		std::cin >> path;
	}
	else
		path = argv[1];


	// text file input
	std::ifstream file(path);
	std::string line;

	// programm
	std::vector<_operation> program;
	int text_line = 1;

	// read file and create tokens
	while (std::getline(file, line))
	{
		int opcount = 0;
		std::string operation;
		std::string drain;
		std::string source;

		// remove 'tab'
		line.erase(std::remove(line.begin(), line.end(), 9), line.end());
		// create tokens
		if (!(line[0] == '/' && line[1] == '/'))
		{
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ' || line[i] == ',')
					opcount++;
				else
				{
					char t = toupper(line[i]);
					switch (opcount)
					{
					case 0:
						operation += t;
						break;
					case 1:
						drain += t;
						break;
					case 2:
						source += t;
						break;

					default:
						break;
					}
				}
			}
			if (!operation.empty())
			{
				// store tokenised program
				_operation cmd(operation, drain, source);
				cmd.m_line = text_line;
				program.push_back(cmd);
			}
		}
		text_line++;
	}

	// Compile program
	std::vector<jumpDestination> jumpTable;
	std::vector<std::string> compiledProgram;
	int memoryPos = 0x0200;
	for (unsigned int i = 0; i < program.size(); i++)
	{
		// current line is a jump-destination/ label
		if (program[i].m_operation[0] == ':')
		{
			std::string __label = program[i].m_operation;
			__label.erase(0, 1);
			jumpDestination jd;
			jd.m_line = memoryPos;
			jd.m_label = __label;
			jumpTable.push_back(jd);
		}
		// current line is an operation
		else
		{
			std::string __op = calccode(program[i]);
			if (__op[0] == '$')
				memoryPos += 3;
			else
				memoryPos += (int)(__op.size() / 2);

			compiledProgram.push_back(__op);
		}
	}

	// go through program and replace Jump-labels with jump table
	std::string finalProgram = "";
	for (unsigned int i = 0; i < compiledProgram.size(); i++)
	{
		std::string _currentLine = compiledProgram[i];
		if (_currentLine[0] == '$')
		{
			// Remove prefix and excess
			std::string __label = _currentLine;
			_currentLine.erase(0, 1);
			_currentLine.erase(2, _currentLine.size() - 2);
			__label.erase(0, 4);

			// go through jumptable
			for (unsigned int j = 0; j < jumpTable.size(); j++)
			{
				if (jumpTable[j].m_label == __label)
				{
					std::stringstream ss;
					if (jumpTable[j].m_line < 0x1000)
						ss << "0";
					ss << std::hex << jumpTable[j].m_line;

					std::string _dest = "";
					_dest += ss.str()[2];
					_dest += ss.str()[3];
					_dest += ss.str()[0];
					_dest += ss.str()[1];

					_currentLine += _dest;
					compiledProgram[i] = _currentLine;
				}
			}
			
		}
		finalProgram += compiledProgram[i];
	}

	// Write to file
	path.erase(path.end() - 4, path.end());
	std::ofstream myfile;
	myfile.open(path);
	myfile << "v2.0 raw\n512*0 ";

	for (unsigned int i = 0; i < finalProgram.size(); i ++)
	{
		myfile << finalProgram[i];
		if (i % 2)
			myfile << ' ';
	}

	myfile.close();

	std::cout << finalProgram << std::endl;
	std::cout << "Done ... !" << std::endl;

	system("pause");
	
}