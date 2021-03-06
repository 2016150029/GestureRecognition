//
// Created by bostinshi on 2017/7/27.
//
#include "com_example_monster_airgesture_PhaseProcessI.h"
#include <RangeFinder.h>
#include <SignalProcess.h>

JNIEXPORT jstring
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_getJniString
        (JNIEnv *env, jobject obj) {
    // new 一个字符串，返回Hello World
    return env->NewStringUTF("Hello World");
}

JNIEXPORT jlong
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_createNativeRangeFinder
        (JNIEnv *env, jobject obj, jint inMaxFramesPerSlice, jint inNumFreqs, jfloat inStartFreq,
         jfloat inFreqInterv) {
    return (jlong)(new RangeFinder(inMaxFramesPerSlice, inNumFreqs, inStartFreq, inFreqInterv));
}


JNIEXPORT jfloat
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_getDistanceChange
        (JNIEnv *env, jobject obj, jlong thizptr, jshortArray recordData, jint size) {
    jfloat fDistance = 0.0;
    jshort *carr;
    carr = env->GetShortArrayElements(recordData, 0);
    if (carr == NULL) {
        return 0;
    }
    fDistance = ((RangeFinder *) thizptr)->GetDistanceChange(carr, size);
    //fDistance = RangeFinder::getCosin();//addAll(carr, size);
    env->ReleaseShortArrayElements(recordData, carr, 0);
    return fDistance;
}


JNIEXPORT jfloatArray
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_getBaseBand
        (JNIEnv *env, jobject obj, jlong thizptr, jint size) {
    //创建一个指定大小的数组
    int len = size * 32 * 2;
    jfloatArray jint_arr = env->NewFloatArray(len);
    jfloat * elems = env->GetFloatArrayElements(jint_arr, 0);
    ((RangeFinder *) thizptr)->getBaseBand(elems);
    //同步
    env->ReleaseFloatArrayElements(jint_arr, elems, 0);
    return jint_arr;
}


JNIEXPORT jlong
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_createNativeSignalProcess
        (JNIEnv *env, jobject obj) {
    return (jlong)(new SignalProcess());
}


JNIEXPORT jfloat
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_doActionRecognition
        (JNIEnv *env, jobject obj, jlong thizptr, jfloatArray recordData, jint size) {
    jfloat iRet = 0;
    jfloat * carr;
    carr = env->GetFloatArrayElements(recordData, 0);
    if (carr == NULL) {
        return 0;
    }
    iRet = ((SignalProcess *) thizptr)->doProcess(carr, size);
    //fDistance = RangeFinder::getCosin();//addAll(carr, size);
    env->ReleaseFloatArrayElements(recordData, carr, 0);

    return iRet;
}


JNIEXPORT jfloatArray
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_doActionRecognitionV2
        (JNIEnv *env, jobject obj, jlong thizptr, jfloatArray recordData, jint size, jstring j_str, jstring j_str2) {

    jfloat * carr;
    carr = env->GetFloatArrayElements(recordData, 0);
    if (carr == NULL) {
        return 0;
    }

    int len = 30;
    jfloatArray jint_arr = env->NewFloatArray(len);
    jfloat * elems = env->GetFloatArrayElements(jint_arr, 0);

    const char* c_str;
    c_str = env->GetStringUTFChars(j_str, NULL);
    const char* c_str2;
    c_str2 = env->GetStringUTFChars(j_str2, NULL);
    int iType = ((SignalProcess *) thizptr)->doProcessV2(carr, size, elems, len, c_str, c_str2);
    elems[0] = iType;
    //fDistance = RangeFinder::getCosin();//addAll(carr, size);
    env->ReleaseFloatArrayElements(recordData, carr, 0);
    env->ReleaseFloatArrayElements(jint_arr, elems, 0);
    env->ReleaseStringUTFChars(j_str, c_str);
    env->ReleaseStringUTFChars(j_str2, c_str2);

    return jint_arr;
}


JNIEXPORT jfloat
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_doActionRecognitionV3
        (JNIEnv *env, jobject obj, jlong thizptr, jshortArray recordData, jint size, jstring j_str, jstring j_str2) {

    jshort * carr;
    carr = env->GetShortArrayElements(recordData, 0);
    if (carr == NULL) {
        return 0;
    }

    const char* c_str;
    c_str = env->GetStringUTFChars(j_str, NULL);
    const char* c_str2;
    c_str2 = env->GetStringUTFChars(j_str2, NULL);
    int iType = ((SignalProcess *) thizptr)->doProcessV3(carr, size,  c_str, c_str2);
    //fDistance = RangeFinder::getCosin();//addAll(carr, size);
    env->ReleaseShortArrayElements(recordData, carr, 0);
    env->ReleaseStringUTFChars(j_str, c_str);
    env->ReleaseStringUTFChars(j_str2, c_str2);

    return iType;
}



JNIEXPORT jfloat
JNICALL Java_com_example_monster_airgesture_PhaseProcessI_doInit
        (JNIEnv *env, jobject obj, jlong thizptr, jstring j_str) {
    jfloat iRet = 0;
    const char* c_str;
    c_str = env->GetStringUTFChars(j_str, NULL);

    iRet = ((SignalProcess *) thizptr)->init(c_str);
    env->ReleaseStringUTFChars(j_str, c_str);

    return iRet;
}
