// Copyright (c) 2012-2013 The PPCoin developers                -*- c++ -*-
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_STAKING_H__DUZY
#define BITCOIN_STAKING_H__DUZY

#include "uint256.h"
#include <map>
#include <set>

//!<DuzyDoc>: Class Declarations
class CBlockIndex;
class CBlock;
class COutPoint;
class CTransaction;

struct StakeKernel //!<DuzyDoc>TODO: private
{
    //!<DuzyDoc>TODO: fields

protected:
    StakeKernel();
};

//!<DuzyDoc>: Stake - singleton class encapsulating PoS feature for Lux.
class Stake : StakeKernel
{

    Stake();
    ~Stake();

    Stake(const Stake&) = delete;
    void operator=(const Stake&) = delete;

    static Stake kernel;

public://!<DuzyDoc>TODO: private

    unsigned int nStakeMinAge;
    int64_t nReserveBalance;
    int64_t nLastCoinStakeSearchInterval;
    int64_t nLastCoinStakeSearchTime;

    std::set<std::pair<COutPoint, unsigned int> > setStakeSeen;
    std::map<uint256, uint256> mapProofOfStake;
    std::map<unsigned int, unsigned int> mapHashedBlocks;
    std::map<uint256, int64_t> mapRejectedBlocks;

public:

    //!<DuzyDoc>: Stake::Pointer() - returns the staking pointer
    static Stake *Pointer();

    //!<DuzyDoc>: Stake::ComputeNextModifier - compute the hash modifier for proof-of-stake
    bool ComputeNextModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier);

    //!<DuzyDoc>: Stake::CheckHash - check whether stake kernel meets hash target
    //!<DuzyDoc>:       Sets hashProofOfStake on success return
    bool CheckHash(const CBlockIndex* pindexPrev, unsigned int nBits, const CBlock &blockFrom, const CTransaction &txPrev, const COutPoint &prevout, unsigned int& nTimeTx, uint256& hashProofOfStake);

    //!<DuzyDoc>: Stake::CheckProof - check kernel hash target and coinstake signature
    //!<DuzyDoc>:       Sets hashProofOfStake on success return
    bool CheckProof(CBlockIndex* const pindexPrev, const CBlock &block, uint256& hashProofOfStake);

    //!<DuzyDoc>: Stake::GetModifierChecksum - get stake modifier checksum
    unsigned int GetModifierChecksum(const CBlockIndex* pindex);

    //!<DuzyDoc>: Stake::CheckModifierCheckpoints - check stake modifier hard checkpoints
    bool CheckModifierCheckpoints(int nHeight, unsigned int nStakeModifierChecksum);

    //!<DuzyDoc>: Stake::IsActive - check if staking is active.
    bool IsActive();

};

//!<DuzyDoc>: stake - global staking pointer for convenient access of staking kernel.
extern Stake * const stake;

#endif // BITCOIN_STAKING_H__DUZY