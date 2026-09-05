#include "ft_util.h"

int main(void)
{
    CURLcode global_init_res;
    char *response;
    const char *url;
    const char *data;

    url = "http://127.0.0.1:5000/api/beacon";
    data = "{\"client_id\": \"test42\",\"status\": \"alive\"}";

    global_init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (global_init_res != CURLE_OK)
    {
        errprint("curl_global_init", "failed init");
        return (1);
    }
    
    response = ft_fetch_command(url, data);

    if (response)
    {
        printf("[MINI C2] Response:\n%s\n", response);
        free(response);
    }
    else
    {
        errprint("ft_fetch_command", "failed to get response");
    }

    curl_global_cleanup();
    return (0);
}