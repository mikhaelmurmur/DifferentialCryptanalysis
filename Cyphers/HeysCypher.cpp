#include "stdafx.h"
#include "HeysCypher.h"

Cypher::Data HeysCypher::encrypt(const Data& data, const KeyData& key)
{
	Data encryptedData;
	auto totalBlockNumber = getNumberOfBlocks(data);
	for(int blockNumber = 0;blockNumber < totalBlockNumber;++blockNumber)
	{
		Block block = getBlock(data, blockNumber);
		applyRound(block);
		appendBlock(encryptedData, block);
	}

	return encryptedData;
}

Cypher::Data HeysCypher::decrypt(const Data& data, const KeyData& key)
{
	return Data();
}

void HeysCypher::applyRound(Block& block)
{

}

HeysCypher::RoundKey HeysCypher::getRoundKey(const KeyData& key, unsigned int round)
{

	return RoundKey();
}

HeysCypher::Block HeysCypher::getBlock(const Data& data, int roundNumber)
{
	return Block();
}

int HeysCypher::getNumberOfBlocks(const Data& data)
{
	return 0;
}

void HeysCypher::appendBlock(Data& data, const Block& block)
{
	
}
