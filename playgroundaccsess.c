#include <unistd.h>
#include <stdio.h>


int main()
{
	printf("%i", access("/usr/bin/apt", X_OK));
}
