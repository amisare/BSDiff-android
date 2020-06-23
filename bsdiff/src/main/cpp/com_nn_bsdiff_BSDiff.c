//
// Created by 顾海军 on 2020/6/14.
//

#include "com_nn_bsdiff_BSDiff.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__(( visibility("hidden") ))
extern int __bsdiff(int argc,char *argv[],char **errmsg);
__attribute__(( visibility("hidden") ))
extern int __bspatch(int argc,char * argv[],char **errmsg);

/*
 * Class:     com_nn_bsdiff_BSDiff
 * Method:    diff
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_nn_bsdiff_BSDiff_diff
        (JNIEnv *env, jobject bsdiff, jstring oldFilePath, jstring newFilePath, jstring patchFilePath) {
    int argc = 4;
    char * argv[argc];
    char * errmsg = NULL;
    argv[0] = "bsdiff";
    argv[1] = (char *) (*env)->GetStringUTFChars(env, oldFilePath, 0);
    argv[2] = (char *) (*env)->GetStringUTFChars(env, newFilePath, 0);
    argv[3] = (char *) (*env)->GetStringUTFChars(env, patchFilePath, 0);
    int ret = __bsdiff(argc, argv, &errmsg);
    (*env)->ReleaseStringUTFChars(env, oldFilePath, argv[1]);
    (*env)->ReleaseStringUTFChars(env, newFilePath, argv[2]);
    (*env)->ReleaseStringUTFChars(env, patchFilePath, argv[3]);
    jclass exc = (*env)->FindClass(env, "java/lang/Exception");
    if (errmsg && exc) {
        (*env)->ThrowNew(env, exc, errmsg);
    }
    if (errmsg) free(errmsg);
}

/*
 * Class:     com_nn_bsdiff_BSDiff
 * Method:    patch
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_nn_bsdiff_BSDiff_patch
        (JNIEnv *env, jobject bsdiff, jstring oldFilePath, jstring newFilePath, jstring patchFilePath) {
    int argc = 4;
    char * argv[argc];
    char * errmsg = NULL;
    argv[0] = "bspatch";
    argv[1] = (char *) (*env)->GetStringUTFChars(env, oldFilePath, 0);
    argv[2] = (char *) (*env)->GetStringUTFChars(env, newFilePath, 0);
    argv[3] = (char *) (*env)->GetStringUTFChars(env, patchFilePath, 0);
    int ret = __bspatch(argc, argv, &errmsg);
    (*env)->ReleaseStringUTFChars(env, oldFilePath, argv[1]);
    (*env)->ReleaseStringUTFChars(env, newFilePath, argv[2]);
    (*env)->ReleaseStringUTFChars(env, patchFilePath, argv[3]);
    jclass exc = (*env)->FindClass(env, "java/lang/Exception");
    if (errmsg && exc) {
        (*env)->ThrowNew(env, exc, errmsg);
    }
    if (errmsg) free(errmsg);
}

#ifdef __cplusplus
}
#endif