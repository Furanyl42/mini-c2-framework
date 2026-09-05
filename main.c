#include "ft_util.h"

int main(void)
{
    CURLcode global_init_res;
    char *response;

    global_init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (global_init_res != CURLE_OK)
    {
        errprint("curl_global_init", "failed");
        return (1);
    }
    
    printf("=== ft_http_get_to_buffer ===\n");
    response = ft_http_get_to_buffer("http://127.0.0.1:5000/api/beacon");

    if (response)
    {
        printf("Response: %s\n", response);
        free(response);
    }
    else
    {
        errprint("ft_http_get_to_buffer", "failed to get response");
    }

    curl_global_cleanup();
    return (0);
}