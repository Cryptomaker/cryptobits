// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (         0, uint256("0xbf3ff0be80d2dbf3159515ffc1d026606ed26c8e12b45bcb899f7552f0853291"))
        (         99, uint256("0xd2b4e3564affcfa270c0a0d3037c4b98b7bc24e774db75fea1b7e1f4883e0a59"))
        (         493, uint256("0xc47db3168af90f8273363bd475baf5ba12a85caf688189597f103ae887a414fd"))
        (         1246, uint256("0x44d7d30588503ce07d0f77427a8637aa889fa0c552a5da58fa0d4bf3469615bb"))
        (         2495, uint256("0xb51275730e1423faee36b7b4a8c7f240fbbffa240bcc173b16eb6fddbd4cc39a"))
        (         3249, uint256("0xc4a239118335a2773631c701d063102476593261d17ffd4739f09f9d43d878d0"))
        (         4016, uint256("0xfa3eca3e310e7da62f460456d3f30f994b60963f3014104fbb2b617443880633"))
        (         22531, uint256("0x5eeac09c8749be8a94306579405a655277e6ae5daf888bba569f876751083399"))
        (         22546, uint256("0x319e31accd10075e70f4f473b685d28276ec1c12047c843302b7e1f103f7848b"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
