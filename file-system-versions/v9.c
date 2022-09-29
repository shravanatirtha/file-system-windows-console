/*This program prints the files names of the directory given by user path*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
void display(char *path);
char **ref;
int j = 0;
int main()
{
    printf("\n-----------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n-----------------------------------------\n");
    ref = (char **)malloc(sizeof(char *) * 29);
    display("E:\\");
    for (int i = 0; i < 29; i++)
        printf("%d\t %s\n", i, ref[i]);
    return 0;
}
void display(char *path)
{
    char file_path[1000];
    sprintf(file_path, "%s\\*.*", path);
    HANDLE path_handle = NULL;
    WIN32_FIND_DATA data_file;
    if ((path_handle = FindFirstFile(file_path, &data_file)) == INVALID_HANDLE_VALUE)
    {
        // printf("Path not found: [%s]\n", path);
    }
    while (FindNextFile(path_handle, &data_file))
    {
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                ref[j] = (char *)malloc(1000 * sizeof(char));
                strcpy(ref[j], file_path);
                j++;
                display(file_path);
            }
        }
    }
    FindClose(path_handle);
}