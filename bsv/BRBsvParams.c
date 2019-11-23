//
//  BRBsvParams.c
//  BRCore
//
//  Created by Chen Fei on 11/15/19.
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
#include "BRBsvParams.h"

static const char *BRBsvDNSSeeds[] = {
//    "seed.bitcoinsv.io", "seed.cascharia.com", "seed.satoshisvision.network", NULL
	"174.138.5.253", "206.189.104.98", "34.209.204.38", "42.3.133.32", "221.216.141.226", "50.34.65.219", "60.176.59.49",  
    "95.216.5.89", "34.68.70.123", "5.39.83.142", "54.175.255.217", "47.104.242.36", "52.197.240.45", "47.254.173.235", NULL
};

static const char *BRBsvTestNetDNSSeeds[] = {
	"testnet-seed.bitcoinsv.io", "testnet-seed.cascharia.com", "testnet-seed.bitcoincloud.net", NULL
};

static const BRCheckPoint BRBsvTestNetCheckpoints[] = {
    {    546, uint256("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70")},
    {1155875, uint256("00000000f17c850672894b9a75b63a1e72830bbd5f4c8889b5c1a80e7faef138")},
    {1188697, uint256("0000000000170ed0918077bde7b4d36cc4c91be69fa09211f748240dabe047fb")}
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRBsvCheckpoints[] = {
    { 11111, uint256("0000000069e244f73d78e8fd29ba2fd2ed618bd6fa2ee92559f542fdb26e7c1d")},
    { 33333, uint256("000000002dd5588a74784eaa7ab0507a18ad16a236e7b1ce69f00d7ddfb5d0a6")},
    { 74000, uint256("0000000000573993a3c9e41ce34471c079dcf5f52a0e824a81e7f953b8661a20")},
    {105000, uint256("00000000000291ce28027faea320c8d2b054b2e0fe44a773f3eefb151d6bdc97")},
    {134444, uint256("00000000000005b12ffd4cd315cd34ffd4a594f430ac814c91184a0d42d2b0fe")},
    {168000, uint256("000000000000099e61ea72015e79632f216fe6cb33d7899acb35b75c8303b763")},
    {193000, uint256("000000000000059f452a5f7340de6682a977387c17010ff6e6c3bd83ca8b1317")},
    {210000, uint256("000000000000048b95347e83192f69cf0366076336c639f9b7228e9ba171342e")},
    {216116, uint256("00000000000001b4f4b433e81ee46494af945cf96014816a4e2370f11b23df4e")},
    {225430, uint256("00000000000001c108384350f74090433e7fcf79a606b8e797f065b130575932")},
    {250000, uint256("000000000000003887df1f29024b06fc2200b55f8af8f35453d7be294df2d214")},
    {279000, uint256("0000000000000001ae8c72a0b0c301f67e3afca10e819efa9041e458e9bd7e40")},
    {295000, uint256("00000000000000004d9b4ef50f0f9d686fd69db2e03af35a100370c64632a983")},
    {478558, uint256("0000000000000000011865af4122fe3b144e2cbeea86142e8ff2fb4107352d43")},
    {504031, uint256("0000000000000000011ebf65b60d0a3de80b8175be709d653b4c1a1beeb6ab9c")},
    {530359, uint256("0000000000000000011ada8bd08f46074f44a8f155396f43e38acf9501c49103")},
    {532224, uint256("0000000000000000004684f8d569b4d117c2e76afedc49c846b3c083a96b2ac2")}
};

static int BRBsvVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1;
}

static const BRChainParams BRBsvParamsRecord = {
    BRBsvDNSSeeds,
    8333,                // standardPort
    0xe8f3e1e3,          // magicNumber
    SERVICES_NODE_BCASH, // services
    BRBsvVerifyDifficulty,
    BRBsvCheckpoints,
    sizeof(BRBsvCheckpoints)/sizeof(*BRBsvCheckpoints),
};
const BRChainParams *BRBsvMainNetParams = &BRBsvParamsRecord;

static const BRChainParams BRBsvTestNetParamsRecord = {
    BRBsvTestNetDNSSeeds,
    18333,               // standardPort
    0xf4f3e5f4,          // magicNumber
    SERVICES_NODE_BCASH, // services
    BRBsvVerifyDifficulty,
    BRBsvTestNetCheckpoints,
    sizeof(BRBsvTestNetCheckpoints)/sizeof(*BRBsvTestNetCheckpoints)
};
const BRChainParams *BRBsvTestNetParams = &BRBsvTestNetParamsRecord;
