/*This program prints the files names of the directory given by user recursively*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
// void display(char *files);
int main()
{
    // char path[1000];
    // scanf("%s", path);
    // int directory_count = 1;
    // int file_count = 1;
    // display("E:\\", directory_count, file_count);
    printf("\nFile system information\n");
    int size = display("E:\\", 1, 1, 0);
    printf("\nTotal size of the file system is %d bytes", size);
    return 0;
}
int display(char *path, int directory_count, int file_count, int file_size)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // printf("Directory: %d - %s\n", directory_count, file_path);
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

    FindClose(path_handle);
    return file_size;
}