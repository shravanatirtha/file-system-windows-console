/*This program prints the files names of the directory given by user recursively with the path and number of files and directories in it*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
void display(char *path, int directory_count, int file_count);
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
    // char **ref = (char **)malloc(sizeof(char *) * 29);
    display("E:\\", 0, 0);
    // for (int i = 0; i < 29; i++)
    //     printf("%s\n", ref[i]);
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
    char **ref = (char **)malloc(sizeof(char *) * 29);
    int i = 0;
    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // printf("%s\n", file_path);
                ref[i] = (char *)malloc(1000 * sizeof(char));
                strcpy(ref[i], file_path);
                printf("%s\n", ref[i]);
                i++;
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
    FindClose(path_handle);
    // return ref;
}