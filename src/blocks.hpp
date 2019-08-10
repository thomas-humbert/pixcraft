#pragma once

#include <cstdint>
#include <vector>
#include <memory>

typedef uint32_t BlockId;

class Block;
namespace BlockRegistry {
	BlockId registerBlock(Block* block);
	
	Block& fromId(BlockId id);
	unsigned int registeredCount();
	
	extern const BlockId STONE_ID;
	extern const BlockId DIRT_ID;
	extern const BlockId GRASS_ID;
	extern const BlockId TRUNK_ID;
	extern const BlockId LEAVES_ID;
	extern const BlockId WATER_ID;
};

enum class BlockRendering {
	opaqueCube, transparentCube, translucentCube
};

class Block {
	friend BlockId BlockRegistry::registerBlock(Block* block);
	
public:
	Block();
	virtual ~Block() = default;
	
	virtual uint8_t getFaceTexture(uint8_t face);
	
	Block* rendering(BlockRendering rendering);
	Block* mainTexture(uint8_t texture);
	
	BlockId id();
	BlockRendering rendering();
	uint8_t mainTexture();
	
	static Block& fromId(BlockId id);

private:
	BlockId _id;
	BlockRendering _rendering;
	int8_t _mainTexture;
	
	void setId(BlockId id);
};

class GrassBlock : public Block {
	using Block::Block;
	uint8_t getFaceTexture(uint8_t face) override;
};

class TrunkBlock : public Block {
	using Block::Block;
	uint8_t getFaceTexture(uint8_t face) override;
};
