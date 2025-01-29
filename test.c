#include "built-ins.h"
#include <limits.h>

int main(int argc, char **argv)
{
	char *str;

	str = NULL;
	str = getcwd(NULL, 0);
	printf ("%s\n", str);
	chdir("~/projects/");
	str = NULL;
	str = getcwd(NULL, 0);
	printf ("%s\n", str);
	PATH_MAX;
	
}