#include "blocks.hpp"

#include <vector>
#include <memory>

#include "textures.hpp"


namespace BlockRegistry {
	namespace {
		std::vector<std::unique_ptr<Block>> protoBlocks;
	}
	
	BlockId registerBlock(Block* block) {
		BlockId id = protoBlocks.size() + 1;
		block->setId(id);
		protoBlocks.emplace_back(std::unique_ptr<Block>(block));
		return id;
	}
	
	const BlockId STONE_ID = registerBlock((new Block())->mainTexture(TEX(STONE)));
	const BlockId DIRT_ID = registerBlock((new Block())->mainTexture(TEX(DIRT)));
	const BlockId GRASS_ID = registerBlock(new GrassBlock());
	const BlockId TRUNK_ID = registerBlock(new TrunkBlock());
	const BlockId LEAVES_ID = registerBlock((new Block())->mainTexture(TEX(LEAVES))->rendering(BlockRendering::transparentCube));
	const BlockId WATER_ID = registerBlock((new Block())->mainTexture(TEX(WATER))->rendering(BlockRendering::translucentCube));

	Block& fromId(BlockId id) {
		return *protoBlocks[id - 1];
	}
	
	unsigned int registeredCount() {
		return protoBlocks.size();
	}
}


uint8_t Block::getFaceTexture(uint8_t face) {
	return _mainTexture;
}

BlockId Block::id() { return _id; }
BlockRendering Block::rendering() { return _rendering; }
uint8_t Block::mainTexture() { return _mainTexture; }

Block& Block::fromId(BlockId id) {
	return BlockRegistry::fromId(id);
}


Block::Block() : _id((BlockId) -1), _rendering(BlockRendering::opaqueCube), _mainTexture(TEX(PLACEHOLDER)) { }
void Block::setId(BlockId id) { _id = id; }

Block* Block::rendering(BlockRendering rendering) { _rendering = rendering; return this; }
Block* Block::mainTexture(uint8_t texture) { _mainTexture = texture; return this; }


uint8_t GrassBlock::getFaceTexture(uint8_t face) {
	if(face == 4) {
		return TEX(DIRT);
	} else if(face == 5) {
		return TEX(GRASS_TOP);
	} else {
		return TEX(GRASS_SIDE);
	}
}

uint8_t TrunkBlock::getFaceTexture(uint8_t face) {
	return face >= 4 ? TEX(TRUNK_INSIDE) : TEX(TRUNK_SIDE);
}
