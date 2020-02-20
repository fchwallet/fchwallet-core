/*
 * BreadWallet
 *
 * Created by Ed Gamble <ed@breadwallet.com> on 1/22/18.
 * Copyright (c) 2018 Breadwinner AG.  All right reserved.
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.core;

/**
 *
 */
public class BRCoreChainParams extends BRCoreJniReference {

    private BRCoreChainParams (long jniReferenceAddress) {
        super (jniReferenceAddress);
    }

    //
    public native int getJniMagicNumber ();

    //
    //
    //

    public static BRCoreChainParams mainnetChainParams =
            new BRCoreChainParams(createJniMainnetChainParams());

    private static native long createJniMainnetChainParams ();

    public static BRCoreChainParams testnetChainParams =
            new BRCoreChainParams(createJniTestnetChainParams());

    private static native long createJniTestnetChainParams ();

    public static BRCoreChainParams mainnetBcashChainParams =
            new BRCoreChainParams(createJniMainnetBcashChainParams());

    private static native long createJniMainnetBcashChainParams();

    public static BRCoreChainParams testnetBcashChainParams =
            new BRCoreChainParams(createJniTestnetBcashChainParams());

    private static native long createJniTestnetBcashChainParams();

    public static BRCoreChainParams mainnetBsvChainParams =
            new BRCoreChainParams(createJniMainnetBsvChainParams());

    private static native long createJniMainnetBsvChainParams ();

    public static BRCoreChainParams testnetBsvChainParams =
            new BRCoreChainParams(createJniTestnetBsvChainParams());

    private static native long createJniTestnetBsvChainParams();

    public static BRCoreChainParams mainnetXsvChainParams =
            new BRCoreChainParams(createJniMainnetXsvChainParams());

    private static native long createJniMainnetXsvChainParams ();

    public static BRCoreChainParams mainnetFchChainParams =
            new BRCoreChainParams(createJniMainnetFchChainParams());

    private static native long createJniMainnetFchChainParams();

    public static BRCoreChainParams testnetFchChainParams =
            new BRCoreChainParams(createJniTestnetFchChainParams());

    private static native long createJniTestnetFchChainParams();
}
