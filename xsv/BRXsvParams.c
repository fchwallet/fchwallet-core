//
//  BRXsvParams.c
//  BRCore
//
//  Created by Chen Fei on 11/25/19.
//  Copyright © 2019 QuickBlock. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "support/BRInt.h"
#include "support/BRSet.h"
#include "bitcoin/BRPeer.h"
#include "BRXsvParams.h"

static const char *BRXsvDNSSeeds[] = {
    "47.110.137.123", "172.104.64.109", NULL
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRXsvCheckpoints[] = {
    { 2016, uint256("19bcec73c39964df1cbe45300191a47108f1bd9898a8f9cd4624d9a6c2abb642")},
    {10080, uint256("12143eb00d1ab6b8bb93bf92515cd0e2112856bfa8a02b1423364731a8d19a5f")},
    {20160, uint256("36ac74c849e10e26cf09b670a027392c749d0ffce61176f894412b569e4694ef")},
    {30240, uint256("ee5772b09b07a9bf7ff5c4e1fe5a48530c9f9f039b28e037215aa6fdc70b9b9a")}
};

static int BRXsvVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1;
}

static const BRChainParams BRXsvParamsRecord = {
    BRXsvDNSSeeds,
    8333,                // standardPort
    0xe8f3e1e3,          // magicNumber
    SERVICES_NODE_BCASH, // services
    BRXsvVerifyDifficulty,
    BRXsvCheckpoints,
    sizeof(BRXsvCheckpoints)/sizeof(*BRXsvCheckpoints),
};
const BRChainParams *BRXsvMainNetParams = &BRXsvParamsRecord;
const BRChainParams *BRXsvTestNetParams = &BRXsvParamsRecord;
