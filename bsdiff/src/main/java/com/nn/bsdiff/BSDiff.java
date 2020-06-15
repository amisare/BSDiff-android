package com.nn.bsdiff;

public class BSDiff {

    static {
        System.loadLibrary("bsdiff-lib");
    }

    public static native int diff(String oldFilePath,
                                  String newFilePath,
                                  String patchFilePath);

    public static native int patch(String oldFilePath,
                                   String newFilePath,
                                   String patchFilePath);
}
