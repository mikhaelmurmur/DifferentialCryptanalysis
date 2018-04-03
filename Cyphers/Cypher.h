#pragma once
#include <vector>

class Cypher
{
public:
	Cypher() = default;
	virtual ~Cypher() = default;
	
public:
	using Data = std::vector<bool>;
	using KeyData = std::vector<bool>;

	virtual Data encrypt(const Data& data, const KeyData& key) = 0;
	virtual Data decrypt(const Data& data, const KeyData& key) = 0;
};

