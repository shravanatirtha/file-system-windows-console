/*This program prints the files names of the directory given by user recursively*/
#include <stdio.h>
#include <windows.h>
// void display(char *files);
int main()
{
    printf("\n--------------------------------------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n--------------------------------------------------------------------\n");
    // printf("\nDirectory: \n");
    // printf("\n--------------------------------------------------------------------\n");

    display("E:\\file-system-using-c\\", 0, 0);
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
        printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0)&& (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
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