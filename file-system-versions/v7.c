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
    int size = 0;
    size = display("c:\\users\\", 0, 0, 0);
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
    printf("%d", size);
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
        //  printf("Cannot be accessed: [%s]\n", path);
    }

    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // printf("\nDirectory Path: %d - %s\n", directory_count, file_path);
                directory_count++;
                size=size+display(file_path, directory_count, file_count, size);
            }
            else
            {
                // printf("File:  %d - %s\n", file_count, file_path);
                file_count++;
                size += data_file.nFileSizeLow;
                // display(file_path, directory_count, file_count, size);
            }
        }
    }
    

    FindClose(path_handle);
    return size;
}