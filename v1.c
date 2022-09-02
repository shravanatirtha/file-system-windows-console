/*This program just prints the files names of the current directory recursively*/
#include <stdio.h>
#include <dirent.h>
void display(char *files);
int main(int argc, char *files[])
{
    if (argc == 1)
        display(".");
    else
        display(files[1]);
    return 0;
}
void display(char *files)
{

    DIR *directory;
    struct dirent *directory_struc;
    directory = opendir(".");
    if ((directory = opendir(files)) == NULL)
    {
        fprintf(stderr, "can't open %s\n", files);
    }
    while ((directory_struc = readdir(directory)) != NULL)
    {

        printf("%s/%s\n", files, directory_struc->d_name);
    }
    closedir(directory);
}