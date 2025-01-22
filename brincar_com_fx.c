#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char *go_up_directory(char *str)
{
	int n = 0;
	int i = 0;
	char *res;
	while (str[n])
		n++;
	while (str[n] != '/')
	{
		n--;
	}
	res = malloc (n + 10);
	strncpy(res, str, n);
	return (res);
}

void ls(char *path)
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir(path);  // Specify the directory path
    if (dir == NULL) {
        perror("opendir");
        return ;  // Error opening directory
    }

    // Read entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);  // Print the name of each directory entry
    }

    // Close the directory
    closedir(dir);
}

int main(void)
{
	char *arr;
	char *new_arr;
	int i = 0;
	
	arr = getcwd(NULL, 0);
	printf("\n%s\n", getcwd(arr, 0));
	new_arr = go_up_directory(arr);
	printf("\n%s\n", new_arr);
	chdir(new_arr);
	printf("\n%s\n", getcwd(arr, 0));
	ls(arr);
}