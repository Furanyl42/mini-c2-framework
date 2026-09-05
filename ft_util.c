#include "ft_util.h"

void	errprint(const char *name, const char *error)
{
	fprintf(stderr, "[MINI_C2] (%s): Error: %s\n", name, error);
}

void	logme(int istittle, const char *message)
{
	if (istittle)
		fprintf(stdout, "[MINI_C2] %s\n", message);
	else
		fprintf(stdout, "%s\n", message);
}