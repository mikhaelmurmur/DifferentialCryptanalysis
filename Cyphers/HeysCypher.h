#pragma once
#include "Cypher.h"

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
	const static int RoundNumber = 7;

	void applyRound(Block& block, const RoundKey& roundKey);
	void applyFinalBlur(Block& block, const RoundKey& roundKey);
	RoundKey getRoundKey(const KeyData& key, unsigned int round);
	Block getBlock(const Data& data, int roundNumber);
	int performSubstitution(int value);
	Block performShuffle(const Block& block);
	int getNumberOfBlocks(const Data& data);
	void appendBlock(Data& data, const Block& block);
};

