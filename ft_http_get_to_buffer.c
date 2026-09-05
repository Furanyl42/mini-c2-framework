#include "ft_util.h"

char *ft_http_get_to_buffer(const char *url)
{
    CURL *curl_handle;
    CURLcode res;
    t_memory chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_handle = curl_easy_init();
    if (!curl_handle)
    {
        errprint("curl_easy_init", "failed to initialize");
        return (NULL);
    }
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, ft_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)(&chunk));
    res = curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
    
    if (res != CURLE_OK)
    {
        errprint("curl_easy_perform", curl_easy_strerror(res));
        free(chunk.memory);
        return (NULL);
    }
    free(chunk.memory);
    return (chunk.memory);
}