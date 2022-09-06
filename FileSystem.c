// gcc -I"C:\Program Files\Java\jdk1.8.0_202\include" -I"C:\Program Files\Java\jdk1.8.0_202\include\win32" -shared -o FileSys.dll FileSystem.c
#include "C:/Program Files/Java/jdk1.8.0_202/include/jni.h"
#include "C:/Program Files/Java/jdk1.8.0_202/include/win32/jni_md.h"
#include <stdio.h>
#include "FileSystem.h"

JNIEXPORT void JNICALL
Java_FileSystem_nativeMethod(JNIEnv *env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    if (mid == NULL)
    {
        return;
    }
    printf("\nHello from C\n");
    (*env)->CallVoidMethod(env, obj, mid);
}