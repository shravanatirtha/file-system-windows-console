/*This program prints the files names of the directory given by user recursively with the path and number of files and directories in it*/
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
char **display(char *path, int directory_count, int file_count, char **str);
int j=0;
char **temp;
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
    char **str = (char **)malloc(sizeof(char *) * 29);
     temp = (char **)malloc(sizeof(char *) * 29);
    char **ref = display("E:\\", 0, 0, str);
    printf("%s\n", ref);
    return 0;
}
char **display(char *path, int i, int file_count, char **ref)
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
                ref[i] = (char *)malloc(1000 * sizeof(char));
                strcpy(ref[i], file_path);
               //strcpy(ref[0],"lksmdl");
                printf("%d\t%s--%d\n", i, ref[i],++j);
                temp[j] = (char *)malloc(10 * sizeof(char));
                strcpy(temp[j],ref[i]);
                i++;
                // printf("%s", file_path);
                display(file_path, i, file_count, ref);

                // strcpy(ref[i], file_path);
            }
        }
    }
    // for (int i = 0; i < 2; i++)
    //      printf("%s\n", ref[i]);
    
    FindClose(path_handle);
    return temp;
}