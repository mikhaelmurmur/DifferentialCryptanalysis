// Analysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <HeysCypher.h>


int main()
{
	HeysCypher cypher;

	HeysCypher::Data dataToEncypher{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	HeysCypher::Data keydata{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	auto data = cypher.encrypt(dataToEncypher, keydata);

	for (const auto&& el : data)
	{
		std::cout << el;
	}

    return 0;
}

