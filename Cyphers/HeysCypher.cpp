#include "stdafx.h"
#include "HeysCypher.h"
#include <assert.h>

namespace
{
	using Block = std::vector<bool>;
	using Chunks = std::array<int, 4>;
	Chunks getChunks(const Block& block)
	{
		return Chunks();
	}

	void convert(const Chunks& from, Block& to)
	{

	}
}

Cypher::Data HeysCypher::encrypt(const Data& data, const KeyData& key)
{
	Data encryptedData;
	auto totalBlockNumber = getNumberOfBlocks(data);
	for (int blockNumber = 0; blockNumber < totalBlockNumber; ++blockNumber)
	{
		auto block = getBlock(data, blockNumber);
		for (int roundIndex = 0; roundIndex < RoundNumber; ++roundIndex)
		{
			auto roundKey = getRoundKey(key, roundIndex);
			applyRound(block, roundKey);
		}

		appendBlock(encryptedData, block);
	}

	return encryptedData;
}

Cypher::Data HeysCypher::decrypt(const Data& data, const KeyData& key)
{
	return Data();
}

void HeysCypher::applyRound(Block& block, const RoundKey& roundKey)
{
	for (int index = 0; index < BlockSize; ++index)
	{
		block[index] = block[index] ^ roundKey[index];
	}

	auto chunks = getChunks(block);
	for (auto& chunk : chunks)
	{
		chunk = performSubstitution(chunk);
	}

	convert(chunks, block);

	performShuffle(block);
}

HeysCypher::RoundKey HeysCypher::getRoundKey(const KeyData& key, unsigned int roundNumber)
{
	const auto roundKeyBegin = key.begin() + BlockSize * roundNumber;
	RoundKey roundKey(roundKeyBegin, roundKeyBegin + RoundKeySize);
	return roundKey;
}

HeysCypher::Block HeysCypher::getBlock(const Data& data, int roundNumber)
{
	const auto blockBegin = data.begin() + BlockSize * roundNumber;
	Block block(blockBegin, blockBegin + BlockSize);
	return block;
}

int HeysCypher::performSubstitution(int value)
{
	const static int SBoxSize = 16;
	assert(value <= SBoxSize);
	const static std::array<int, SBoxSize> SBox{ 0x4, 0x5, 0x1, 0xC, 0x7, 0xE, 0x9, 0x2, 0xA, 0xF, 0xB, 0xD, 0x0, 0x8, 0x6, 0x3 };
	return SBox[value];
}

void HeysCypher::performShuffle(Block& block)
{

}

int HeysCypher::getNumberOfBlocks(const Data& data)
{
	assert(data.size() % BlockSize == 0);
	return static_cast<int>(data.size()) / BlockSize;
}

void HeysCypher::appendBlock(Data& data, const Block& block)
{
	data.insert(data.end(), block.begin(), block.end());
}
