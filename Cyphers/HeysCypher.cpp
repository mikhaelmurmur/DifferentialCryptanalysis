#include "stdafx.h"
#include "HeysCypher.h"
#include <assert.h>
#include <array>

namespace
{
	using Block = std::vector<bool>;
	using RoundKey = std::vector<bool>;
	using Chunks = std::array<int, 4>;
	const int BlockSize = 16;

	Chunks getChunks(const Block& block)
	{
		Chunks result;
		for (int chunkIndex = 0; chunkIndex < result.size(); ++chunkIndex)
		{
			auto& chunk = result[chunkIndex];
			chunk = 0;
			for (int bitIndex = 0; bitIndex < 4; ++bitIndex)
			{
				chunk ^= static_cast<int>(block[chunkIndex + bitIndex]);
				chunk <<= 1;
			}
		}

		return result;
	}

	void convert(const Chunks& from, Block& to)
	{
		to.clear();
		for (const auto& chunk : from)
		{
			for (int i = 0; i < 4; ++i)
			{
				to.emplace_back((chunk >> i) & 0x1);
			}
		}
	}

	void blockXorKey(Block& block, const RoundKey& roundKey)
	{
		for (int index = 0; index < BlockSize; ++index)
		{
			block[index] = block[index] ^ roundKey[index];
		}
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

		applyFinalBluring(block, getRoundKey(key, RoundNumber));

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
	blockXorKey(block, roundKey);

	auto chunks = getChunks(block);
	for (auto& chunk : chunks)
	{
		chunk = performSubstitution(chunk);
	}

	convert(chunks, block);

	performShuffle(block);
}

void HeysCypher::applyFinalBluring(Block& block, const RoundKey& roundKey)
{
	blockXorKey(block, roundKey);
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

Block HeysCypher::performShuffle(const Block& block)
{
	Block result;
	for (int bitIndex = 0; bitIndex < BlockSize; ++bitIndex)
	{
		auto chunkIndex = bitIndex / 4;
		auto indexInChunk = bitIndex % 4;
		result[chunkIndex + indexInChunk * 4] = block[bitIndex];
	}

	return result;
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
