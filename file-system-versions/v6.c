/*This program prints the files names of the directory given by user recursively*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
char **path_array(char *path, int i, char **ref);
int main()
{
    printf("\n-------------------------------------------\n");
    printf("\nFile system information\n");
    printf("\n--------------------------------------------\n");
    char **str = (char **)malloc(sizeof(char *) * 29);
    char **ref = (char **)malloc(sizeof(char *) * 29);
    str = path_array("E:", 0, ref);
    for (int i = 0; i < 29; i++)
    {
        printf("%d\t%s\n", i, str[i]);
    }
    return 0;
}
char **path_array(char *path, int i, char **ref)
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
        if (strcmp(data_file.cFileName, ".") != 0 && strcmp(data_file.cFileName, "..") != 0 && strcmp(data_file.cFileName, ".metadata") != 0 && strcmp(data_file.cFileName, ".settings") != 0 && (strcmp(data_file.cFileName, ".git") != 0 && strcmp(data_file.cFileName, ".vscode") != 0) && (strcmp(data_file.cFileName, ".config") != 0 && strcmp(data_file.cFileName, "System Volume Information") != 0))
        {
            sprintf(file_path, "%s\\%s", path, data_file.cFileName);
            if (data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

                // printf("Directory: - %s\n", file_path);
                ref[i] = (char *)malloc(1000 * sizeof(char));
                strcpy(ref[i], file_path);
                i++;
                path_array(file_path, i, ref);
            }

        }
    }

    // printf("\n--------------------------------------------------------------------\n");
    FindClose(path_handle);
    return ref;
}