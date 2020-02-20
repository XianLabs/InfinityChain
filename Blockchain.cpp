#include "Blockchain.h"

Blockchain::Blockchain()
{
	_vChain.emplace_back(Block(0, "Infinity Block"));
	_nDifficulty = 5;
}

void Blockchain::AddBlock(Block bNew)
{
	bNew.sPrevHash = _GetLastBlock().sHash;
	bNew.MineBlock(_nDifficulty);
	_vChain.push_back(bNew);
}

Block Blockchain::_GetLastBlock() const
{
	return _vChain.back();
}