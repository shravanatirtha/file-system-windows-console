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
    display("E:\\", 0, 0);
    return 0;
}
void display(char *path, int directory_count, int file_count)
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
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0)
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // printf("Directory: %d - %s\n", directory_count, file_path);
                directory_count++;
                display(file_path, directory_count, file_count);
            }
            else
            {
                // printf("File:  %d - %s\n", file_count, file_path);
                file_count++;
            }
            printf("Path: %s\n\n", file_path);
            printf("Total directories: %d\t | \tTotal files: %d\n", directory_count, file_count);
            printf("\n--------------------------------------------------------------------\n");
        }
    }
    // printf("Directory: %s\n\n", file_path);
    FindClose(path_handle);
    // printf("Total directories: %d\t | \tTotal files: %d\n", directory_count, file_count);
    // printf("\n--------------------------------------------------------------------\n");
}