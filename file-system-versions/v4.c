/*This program prints the files names of the directory given by user recursively with the path and number of files and directories in it*/
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
    printf("\n--------------------------------------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n--------------------------------------------------------------------\n");
    int size = display("E:\\file-system-using-c\\", 0, 0, 0);
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
    return 0;
}
int display(char *path, int directory_count, int file_count, int size)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        int x = 0;
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0)
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                directory_count++;
                return display(file_path, directory_count, file_count, size) + size;
            }
            else
            {
                file_count++;
                size += data_file.nFileSizeLow;
            }
        }
    }
    FindClose(path_handle);
}