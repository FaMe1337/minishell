#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char *go_up_directory(char *str)
{
	int n = 0;
	char *res;
	while (str[n])
		n++;
	while (str[n] != '/')
	{

	}
	return (str);
}

int main(void)
{
	char *arr;
	char *new_arr;

	arr = malloc (1000);
	printf("\n %s \n", getcwd(arr, 1000));
	new_arr = go_up_directory(arr);
	chdir(new_arr);
}