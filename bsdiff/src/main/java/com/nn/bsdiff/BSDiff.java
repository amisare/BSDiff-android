package com.nn.bsdiff;

public class BSDiff {

    static {
        System.loadLibrary("bsdiff-lib");
    }

    public static native void diff(String oldFilePath,
                                   String newFilePath,
                                   String patchFilePath) throws Exception;

    public static native void patch(String oldFilePath,
                                    String newFilePath,
                                    String patchFilePath) throws Exception;
}
