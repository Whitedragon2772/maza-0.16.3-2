// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_POW_H
#define BITCOIN_POW_H

#include <consensus/params.h>
#include <primitives/block.h>   // Maza: MinotaurX+Hive1.2: For POW_TYPE

#include <stdint.h>

class CBlockHeader;
class CBlockIndex;
class uint256;
class CBlock;

// Maza: Hive
struct BeePopGraphPoint {
    int immaturePop;
    int maturePop;
};

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&);
unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params&);
unsigned int DarkGravityWave(const CBlockIndex* pindexLast, const Consensus::Params& params);                               // Maza:  (DGW) diff adjust implementation
unsigned int GetNextWorkRequiredBTC(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&);   // Maza: initial diff adjust implementation
unsigned int GetNextHiveWorkRequired(const CBlockIndex* pindexLast, const Consensus::Params& params);                       // Maza: Hive: Get the current Bee Hash Target
unsigned int GetNextWorkRequiredLWMA(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, const POW_TYPE powType); // Maza: MinotaurX+Hive1.2: LWMA difficulty adjustment for all pow types
bool CheckHiveProof(const CBlock* pblock, const Consensus::Params& params);                                                 // Maza: Hive: Check the hive proof for given block
bool GetNetworkHiveInfo(int& immatureBees, int& immatureBCTs, int& matureBees, int& matureBCTs, CAmount& potentialLifespanRewards, const Consensus::Params& consensusParams, bool recalcGraph = false); // Maza: Hive: Get count of all live and gestating BCTs on the network

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params&);



#endif // BITCOIN_POW_H
