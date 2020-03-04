//
//  BRFchParams.c
//  BRCore
//
//  Created by Chen Fei on 02/14/20.
//  Copyright © 2020 QuickBlock. All rights reserved.
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
#include "BRFchParams.h"

static const char *BRFchDNSSeeds[] = {
    "seed1.freecash.info.", "seed2.freecash.info.", "seed3.freecash.info.", NULL
};

static const char *BRFchTestNetDNSSeeds[] = {
    NULL
};

static const BRCheckPoint BRFchTestNetCheckpoints[] = {
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRFchCheckpoints[] = {
    {      0, uint256("00000000cbe04361b1d6de82b893a7d8419e76e99dd2073ac0db2ba0e652eea8"), 223904032, 0x1d00ffff }
};

static const BRMerkleBlock *_medianBlock(const BRMerkleBlock *b, const BRSet *blockSet)
{
    const BRMerkleBlock *b0 = NULL, *b1 = NULL, *b2 = b;

    b1 = (b2) ? BRSetGet(blockSet, &b2->prevBlock) : NULL;
    b0 = (b1) ? BRSetGet(blockSet, &b1->prevBlock) : NULL;
    if (b0 && b2 && b0->timestamp > b2->timestamp) b = b0, b0 = b2, b2 = b;
    if (b0 && b1 && b0->timestamp > b1->timestamp) b = b0, b0 = b1, b1 = b;
    if (b1 && b2 && b1->timestamp > b2->timestamp) b = b1, b1 = b2, b2 = b;
    return (b0 && b1 && b2) ? b1 : NULL;
}

static int BRFchVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    const BRMerkleBlock *b, *first, *last;
    int i, sz, size = 0x1d;
    uint64_t t, target, w, work = 0;
    int64_t timespan;

    assert(block != NULL);
    assert(blockSet != NULL);

    if (block && block->height >= 504032) { // D601 hard fork height: https://reviews.bitcoinabc.org/D601
        last = BRSetGet(blockSet, &block->prevBlock);
        last = _medianBlock(last, blockSet);

        for (i = 0, first = block; first && i <= 144; i++) {
            first = BRSetGet(blockSet, &first->prevBlock);
        }

        first = _medianBlock(first, blockSet);

        if (! first) return 1;
        timespan = (int64_t)last->timestamp - first->timestamp;
        if (timespan > 288*10*60) timespan = 288*10*60;
        if (timespan < 72*10*60) timespan = 72*10*60;

        for (b = last; b != first;) {
            // target is in "compact" format, where the most significant byte is the size of the value in bytes, next
            // bit is the sign, and the last 23 bits is the value after having been right shifted by (size - 3)*8 bits
            sz = b->target >> 24, t = b->target & 0x007fffff;

            // work += 2^256/(target + 1)
            w = (t) ? ~0ULL/t : ~0ULL;
            while (sz < size) work >>= 8, size--;
            while (size < sz) w >>= 8, sz--;
            while (work + w < w) w >>= 8, work >>= 8, size--;
            work += w;

            b = BRSetGet(blockSet, &b->prevBlock);
        }

        // work = work*10*60/timespan
        while (work > ~0ULL/(10*60)) work >>= 8, size--;
        work = work*10*60/timespan;

        // target = (2^256/work) - 1
        while (work && ~0ULL/work < 0x8000) work >>= 8, size--;
        target = (work) ? ~0ULL/work : ~0ULL;

        while (size < 1 || target > 0x007fffff) target >>= 8, size++; // normalize target for "compact" format
        target |= size << 24;

        if (target > 0x1d00ffff) target = 0x1d00ffff; // max proof-of-work
        if (target - block->target > 1) return 0;
    }

    return 1;
}

static int BRFchTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRFchParamsRecord = {
    BRFchDNSSeeds,
    8333,                // standardPort
    0xe5f3f4e8,          // magicNumber
    SERVICES_NODE_BCASH, // services
    BRFchVerifyDifficulty,
    BRFchCheckpoints,
    sizeof(BRFchCheckpoints)/sizeof(*BRFchCheckpoints),
};
const BRChainParams *BRFchParams = &BRFchParamsRecord;

static const BRChainParams BRFchTestNetParamsRecord = {
    BRFchTestNetDNSSeeds,
    18333,               // standardPort
    0xf4f3b5f4,          // magicNumber
    SERVICES_NODE_BCASH, // services
    BRFchTestNetVerifyDifficulty,
    BRFchTestNetCheckpoints,
    sizeof(BRFchTestNetCheckpoints)/sizeof(*BRFchTestNetCheckpoints)
};
const BRChainParams *BRFchTestNetParams = &BRFchTestNetParamsRecord;
