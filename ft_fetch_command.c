#include "ft_util.h"

char *ft_fetch_command(const char *url, const char *client_id)
{
    char *data;
    char *response;
    int len;

    len = snprintf(NULL, 0, "{\"client_id\":\"%s\",\"status\":\"active\"}", client_id);
    if (len < 0)
    {
        errprint("snprintf", "failed to calculate length");
        return (NULL);
    }

    data = malloc(len + 1);
    if (!data)
    {
        errprint("malloc", "failed to allocate memory");
        return (NULL);
    }

    snprintf(data, len + 1, "{\"client_id\":\"%s\",\"status\":\"active\"}", client_id);
    response = ft_http_post(url, data);
    free(data);
    return (response);
}

