//
//  BRCryptoAmount.c
//  BRCore
//
//  Created by Ed Gamble on 3/19/19.
//  Copyright © 2019 breadwallet. All rights reserved.
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

#include "BRCryptoAmount.h"

#include <stdlib.h>
#include <assert.h>

#include "support/BRInt.h"
#include "ethereum/util/BRUtilMath.h"

struct BRCryptoAmountRecord {
    BRCryptoCurrency currency;
    BRCryptoBoolean isNegative;
    UInt256 value;
};

/* private */ extern BRCryptoAmount
cryptoAmountCreate (BRCryptoCurrency currency,
                    BRCryptoBoolean isNegative,
                    UInt256 value) {
    BRCryptoAmount amount = malloc (sizeof (struct BRCryptoAmountRecord));

    amount->currency = currency; // RefCount
    amount->isNegative = isNegative;
    amount->value = value;

    return amount;
}

extern BRCryptoAmount
cryptoAmountCreateDouble (double value,
                          BRCryptoUnit unit) {
    UInt256 v = UINT256_ZERO;
    return cryptoAmountCreate (cryptoUnitGetCurrency(unit),
                               value < 0.0,
                               v);
}

extern BRCryptoAmount
cryptoAmountCreateInteger (int64_t value,
                           BRCryptoUnit unit) {
    UInt256 v = UINT256_ZERO;
    return cryptoAmountCreate (cryptoUnitGetCurrency(unit),
                               value < 0.0,
                               v);
}


static void
cryptoAmountRelease (BRCryptoAmount amount) {
    // amount - RefCount
    free (amount);
}

extern BRCryptoCurrency
cryptoAmountGetCurrency (BRCryptoAmount amount) {
    return amount->currency;
}

extern BRCryptoBoolean
cryptoAmountIsNegative (BRCryptoAmount amount) {
    return amount->isNegative;
}

extern BRCryptoBoolean
cryptoAmountIsCompatible (BRCryptoAmount a1,
                          BRCryptoAmount a2) {
    return cryptoCurrencyIsIdentical(a1->currency, a2->currency);
}

static BRCryptoComparison
cryptoCompareUInt256 (UInt256 v1, UInt256 v2) {
    switch (compareUInt256 (v1, v2)) {
        case -1: return CRYPTO_COMPARE_LT;
        case  0: return CRYPTO_COMPARE_EQ;
        case +1: return CRYPTO_COMPARE_GT;
        default: assert (0);
    }
}

extern BRCryptoComparison
cryptoAmountCompare (BRCryptoAmount a1,
                     BRCryptoAmount a2) {
    assert (CRYPTO_TRUE == cryptoAmountIsCompatible(a1, a2));

    if (CRYPTO_TRUE == a1->isNegative && CRYPTO_TRUE != a2->isNegative)
        return CRYPTO_COMPARE_LT;
    else if (CRYPTO_TRUE != a1->isNegative && CRYPTO_TRUE == a2->isNegative)
        return CRYPTO_COMPARE_GT;
    else if (CRYPTO_TRUE == a1->isNegative && CRYPTO_TRUE == a2->isNegative)
        // both negative -> swap comparison
        return cryptoCompareUInt256 (a2->value, a1->value);
    else
        // both positive -> same comparison
        return cryptoCompareUInt256 (a1->value, a2->value);
}

extern BRCryptoAmount
cryptoAmountAdd (BRCryptoAmount a1,
                 BRCryptoAmount a2) {
    assert (CRYPTO_TRUE == cryptoAmountIsCompatible(a1, a2));

    int overflow = 0;
    UInt256 sum = addUInt256_Overflow(a1->value, a2->value, &overflow);

    return overflow ? NULL : cryptoAmountCreate (a1->currency, CRYPTO_FALSE, sum);
}

extern BRCryptoAmount
cryptoAmountSub (BRCryptoAmount a1,
                 BRCryptoAmount a2) {
    int overflow = 0;
    int negative = 0;

    if (CRYPTO_TRUE == a1->isNegative && CRYPTO_TRUE != a2->isNegative) {
        // (-x) - y = - (x + y)
        UInt256 value = addUInt256_Overflow (a1->value, a2->value, &overflow);
        return overflow ? NULL : cryptoAmountCreate (a1->currency, CRYPTO_TRUE, value);
    }
    else if (CRYPTO_TRUE != a1->isNegative && CRYPTO_TRUE == a2->isNegative) {
        // x - (-y) = x + y
        UInt256 value = addUInt256_Overflow (a1->value, a2->value, &overflow);
        return overflow ? NULL : cryptoAmountCreate(a1->currency, CRYPTO_FALSE, value);
    }
    else if (CRYPTO_TRUE == a1->isNegative && CRYPTO_TRUE == a2->isNegative) {
        // (-x) - (-y) = y - x
        UInt256 value = subUInt256_Negative (a2->value, a1->value, &negative);
        return cryptoAmountCreate (a1->currency, AS_CRYPTO_BOOLEAN(negative), value);
    }
    else {
        UInt256 value = subUInt256_Negative (a1->value, a2->value, &negative);
        return cryptoAmountCreate (a1->currency, AS_CRYPTO_BOOLEAN(negative), value);
    }
}

extern double
cryptoAmountGetDouble (BRCryptoAmount amount,
                       BRCryptoBoolean *overflow) {
    assert (NULL != overflow);
    *overflow = CRYPTO_FALSE;
    return 0.0;
}

extern int64_t
cryptoAmountGetInteger (BRCryptoAmount amount,
                        BRCryptoBoolean *overflow) {
    assert (NULL != overflow);
    *overflow = CRYPTO_FALSE;
    return 0;
}