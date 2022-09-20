#include "C:/Program Files/Java/jdk1.8.0_202/include/jni.h"
#include "C:/Program Files/Java/jdk1.8.0_202/include/win32/jni_md.h"
#include <stdio.h>
#include "FileSystem.h"
#include <windows.h>
#include <dirent.h>
JNIEXPORT void JNICALL Java_FileSystem_fileSystem(JNIEnv *env, jobject clsobj, jstring path)
{
    int directoryCount = 0;
    int fileCount = 0;
    int totalSize = 0;
    const char *pathName = (*env)->GetStringUTFChars(env, path, NULL);
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", pathName);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        printf("Cannot be accessed: [%s]\n", pathName);
        return;
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                directoryCount++;
            }
            else
            {
                fileCount++;
                totalSize += data_file.nFileSizeLow;
            }
        }
    }
    printf("path: %s\n", pathName);
    printf("directoryCount: %d\n", directoryCount);
    printf("fileCount: %d\n", fileCount);
    printf("totalSize: %d\n", totalSize);
    FindClose(path_handle);
    (*env)->ReleaseStringUTFChars(env, path, pathName);
}