#include "ft_util.h"

int main(void)
{
    CURLcode global_init_res;
    char *response;
    const char *url;
    const char *data;

    url = "http://127.0.0.1:5000/api/beacon";
    data = "clientid-1234";

    global_init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    logme(1, "Initializing client...");
    if (global_init_res != CURLE_OK)
    {
        errprint("curl_global_init", "failed init");
        return (1);
    }
    logme(1, "Sending beacon to server...");
    
    response = ft_fetch_command(url, data);


    if (response)
    {
        logme(1, "Received response:");
        logme(0, response);
        free(response);
    }
    else
    {
        errprint("ft_fetch_command", "failed to get response");
    }
    logme(1, "Cleaning up...");
    curl_global_cleanup();
    logme(1, "Client finished.");
    return (0);
}