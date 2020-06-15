//
// Created by 顾海军 on 2020/6/14.
//

#include "com_nn_bsdiff_BSDiff.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int __bsdiff(int argc, char * argv[]);
extern int __bspatch(int argc, char * argv[]);

/*
 * Class:     com_nn_bsdiff_BSDiff
 * Method:    diff
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_nn_bsdiff_BSDiff_diff
        (JNIEnv *env, jobject bsdiff, jstring oldFilePath, jstring newFilePath, jstring patchFilePath) {
    int argc = 4;
    char *argv[argc];
    argv[0] = "bsdiff";
    argv[1] = (char *) (*env)->GetStringUTFChars(env, oldFilePath, 0);
    argv[2] = (char *) (*env)->GetStringUTFChars(env, newFilePath, 0);
    argv[3] = (char *) (*env)->GetStringUTFChars(env, patchFilePath, 0);
    int ret = __bsdiff(argc, argv);
    (*env)->ReleaseStringUTFChars(env, oldFilePath, argv[1]);
    (*env)->ReleaseStringUTFChars(env, newFilePath, argv[2]);
    (*env)->ReleaseStringUTFChars(env, patchFilePath, argv[3]);
    return ret;
}

/*
 * Class:     com_nn_bsdiff_BSDiff
 * Method:    patch
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_nn_bsdiff_BSDiff_patch
        (JNIEnv *env, jobject bsdiff, jstring oldFilePath, jstring newFilePath, jstring patchFilePath) {
    int argc = 4;
    char *argv[argc];
    argv[0] = "bspatch";
    argv[1] = (char *) (*env)->GetStringUTFChars(env, oldFilePath, 0);
    argv[2] = (char *) (*env)->GetStringUTFChars(env, newFilePath, 0);
    argv[3] = (char *) (*env)->GetStringUTFChars(env, patchFilePath, 0);
    int ret = __bspatch(argc, argv);
    (*env)->ReleaseStringUTFChars(env, oldFilePath, argv[1]);
    (*env)->ReleaseStringUTFChars(env, newFilePath, argv[2]);
    (*env)->ReleaseStringUTFChars(env, patchFilePath, argv[3]);
    return ret;
}

#ifdef __cplusplus
}
#endif