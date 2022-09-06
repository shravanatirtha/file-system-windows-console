// gcc -I"C:\Program Files\Java\jdk1.8.0_202\include" -I"C:\Program Files\Java\jdk1.8.0_202\include\win32" -shared -o FileSys.dll FileSystem.c
#include "C:/Program Files/Java/jdk1.8.0_202/include/jni.h"
#include "C:/Program Files/Java/jdk1.8.0_202/include/win32/jni_md.h"
#include <stdio.h>
#include "FileSystem.h"
#include <windows.h>
JNIEXPORT void JNICALL
Java_FileSystem_nativeMethod(JNIEnv *env, jobject obj, jstring pathObj) // , char *path, int directory_count, int file_count
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    if (mid == NULL)
    {
        return;
    }
    char *path = (*env)->GetStringUTFChars(env, pathObj, NULL);
    // printf("\nEnter file path eg: D:\\someFolder\\\n");
    // char path[1000];
    // scanf("%s", path);
    printf("\n--------------------------------------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n--------------------------------------------------------------------\n");

    display(path, 0, 0);
    (*env)->CallVoidMethod(env, obj, mid);
}
void display(char *path, int directory_count, int file_count)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("\nDirectory Path: %d - %s\n", directory_count, file_path);
                directory_count++;
                display(file_path, directory_count, file_count);
            }
            else
            {
                // printf("File:  %d - %s\n", file_count, file_path);
                file_count++;
            }
        }
    }
    printf("Maps to: %s\n", path);
    printf("Directories:  %d \n", directory_count);
    printf("Files:  %d \n", file_count);
    FindClose(path_handle);

    printf("\n--------------------------------------------------------------------\n");
}