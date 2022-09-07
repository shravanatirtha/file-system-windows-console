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

    display(path, 0, 0, 0);
    (*env)->CallVoidMethod(env, obj, mid);
}
void display(char *path, int directory_count, int file_count, int file_size)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        printf("Cannot be accessed: [%s]\n", path);
    }
    // typedef struct _WIN32_FIND_DATA { // wfd
    //     DWORD dwFileAttributes;
    //     FILETIME ftCreationTime;
    //     FILETIME ftLastAccessTime;
    //     FILETIME ftLastWriteTime;
    //     DWORD    nFileSizeHigh;
    //     DWORD    nFileSizeLow;
    //     DWORD    dwReserved0;
    //     DWORD    dwReserved1;
    //     TCHAR    cFileName[ MAX_PATH ];
    //     TCHAR    cAlternateFileName[ 14 ];
    // } WIN32_FIND_DATA;

    // FILE_ATTRIBUTE_ARCHIVE	The file or directory is an archive file or directory. Applications use this attribute to mark files for backup or removal.
    // FILE_ATTRIBUTE_COMPRESSED	The file or directory is compressed. For a file, this means that all of the data in the file is compressed. For a directory, this means that compression is the default for newly created files and subdirectories.
    // FILE_ATTRIBUTE_DIRECTORY	The handle identifies a directory.
    // FILE_ATTRIBUTE_ENCRYPTED	The file or directory is encrypted. For a file, this means that all data streams are encrypted. For a directory, this means that encryption is the default for newly created files and subdirectories.
    // FILE_ATTRIBUTE_HIDDEN	The file or directory is hidden. It is not included in an ordinary directory listing.
    // FILE_ATTRIBUTE_NORMAL	The file or directory has no other attributes set. This attribute is valid only if used alone.
    // FILE_ATTRIBUTE_OFFLINE	The file data is not immediately available. Indicates that the file data has been physically moved to offline storage.
    // FILE_ATTRIBUTE_READONLY	The file or directory is read-only. Applications can read the file but cannot write to it or delete it. In the case of a directory, applications cannot delete it.
    // FILE_ATTRIBUTE_REPARSE_POINT	The file has an associated reparse point.
    // FILE_ATTRIBUTE_SPARSE_FILE	The file is a sparse file.
    // FILE_ATTRIBUTE_SYSTEM	The file or directory is part of the operating system or is used exclusively by the operating system.
    // FILE_ATTRIBUTE_TEMPORARY	The file is being used for temporary storage. File systems attempt to keep all of the data in memory for quicker access, rather than flushing it back to mass storage. A temporary file should be deleted by the application as soon as it is no longer needed.

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("\nDirectory Path: %d - %s\n", directory_count, file_path);
                directory_count++;
                display(file_path, directory_count, file_count, file_size);
            }
            else
            {
                // printf("File:  %d - %s\n", file_count, file_path);
                file_count++;
                file_size += data_file.nFileSizeLow;
            }
        }
    }
    printf("Maps to: %s\n", path);
    printf("Directories:  %d \n", directory_count);
    printf("Files:  %d \n", file_count);
    if (file_size <= 1024)
    {
        printf("Total size: %d bytes\n", file_size);
    }
    else if (file_size > 1024 && file_size <= 1048576)
    {
        printf("Total size: %d KB\n", file_size / 1024);
    }
    else if (file_size > 1048576 && file_size <= 1073741824)
    {
        printf("Total size: %d MB\n", file_size / 1048576);
    }
    else if (file_size > 1073741824)
    {
        printf("Total size: %d GB\n", file_size / 1073741824);
    }

    FindClose(path_handle);

    printf("\n--------------------------------------------------------------------\n");
}