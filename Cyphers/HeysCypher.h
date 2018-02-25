#pragma once
#include "Cypher.h"
#include <array>
class HeysCypher :
	public Cypher
{
public:
	HeysCypher() = default;
	virtual ~HeysCypher() = default;

	virtual Data encrypt(const Data& data, const KeyData& key) override;
	virtual Data decrypt(const Data& data, const KeyData& key) override;

private:
	using Block = std::vector<bool>;
	using RoundKey = std::vector<bool>; 
	const static int BlockSize = 16;
	const static int KeySize = 112;
	const static int RoundKeySize = 16;

	void applyRound(Block& block);
	RoundKey getRoundKey(const KeyData& key, unsigned int round);
	Block getBlock(const Data& data, int roundNumber);
	int getNumberOfBlocks(const Data& data);
	void appendBlock(Data& data, const Block& block);
};

