/*This program prints names of the directory given by user recursively*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
char **path_array(char *path, int dir_count, int i);
int path_size(char *path, int size);
int files(char *path, int file_count);
int directories(char *path, int directory_count);
int main()
{
    printf("\n--------------------------------------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n--------------------------------------------------------------------\n");

    int size = 0;
    size = path_size("E:\\", 0);
    if (size < 1024)
    {
        printf("\tSize: %d bytes\n", size);
    }
    else if (size < 1024 * 1024)
    {
        printf("\tSize: %d KB\n", size / 1024);
    }
    else if (size < 1024 * 1024 * 1024)
    {
        printf("\tSize: %d MB\n", size / (1024 * 1024));
    }
    else
    {
        printf("\tSize: %d GB\n", size / (1024 * 1024 * 1024));
    }
    int file_count = 0;
    file_count = files("E:\\", 0);
    printf("\tNumber of files: %d\n", file_count);
    int dir_count = 0;
    dir_count = directories("E:\\", 0);
    printf("\tNumber of directories: %d\n", dir_count);
    char **str = (char **)malloc(sizeof(char *) * dir_count);
    str = path_array("E:\\", dir_count,0);
    // for (int i = 0; i < dir_count; i++)
    // {
    //     printf("%d\t%s\n", i, str[i]);
    // }
    return 0;
}

int path_size(char *path, int size)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        // printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

                size = size + path_size(file_path, size);
            }
            else
            {

                size += data_file.nFileSizeLow;
            }
        }
    }

    FindClose(path_handle);
    if (size < 0)
        size = abs(size);
    return size;
}

int files(char *path, int file_count)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        // printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                file_count = files(file_path, file_count);
            }
            else
            {
                file_count++;
            }
        }
    }

    FindClose(path_handle);
    return file_count;
}

int directories(char *path, int directory_count)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        // printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

                directory_count = directories(file_path, directory_count);
                directory_count++;
            }
            else
            {
            }
        }
    }
    FindClose(path_handle);
    return directory_count;
}

char **path_array(char *path, int dir_count, int i)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        // printf("Cannot be accessed: [%s]\n", path);
    }
    char **str = (char **)malloc(dir_count * sizeof(char *));
    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                str[i] = (char *)malloc(1000 * sizeof(char));
                strcpy(str[i], file_path);
                i++;
                // str[i] = (char *)malloc(1000 * sizeof(char));
                // strcpy(str[i], file_path);
                // i++;
                // printf("%s\n", file_path);
            }
        }
    }
    FindClose(path_handle);
    return str;
}
