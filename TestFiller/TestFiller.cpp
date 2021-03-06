// TestFiller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>

int main()
{
	std::cout << "Enter testcase number to fill: ";
	int testcaseNumber = 0;
	std::cin >> testcaseNumber;
	std::cout << std::endl;
	
	std::cout << "Enter number of bits :";
	int bitNumber = 0;
	std::cin >> bitNumber;
	std::cout << std::endl;

	std::cout << "Enter bits: ";
	std::vector<bool> data(bitNumber);
	for (auto&& bit : data)
	{
		char ch;
		std::cin >> ch;
		bit = ch - '0';
	}

	std::cout << "Thank you!\n";

	std::ofstream testcaseInputFile(testcaseNumber + "\\input.in");
	for (const auto&& bit : data)
	{
		testcaseInputFile << bit;
	}

	std::cout << "Test case file is filled!\n";
	std::cin.get();
	std::cin.get();

    return 0;
}

