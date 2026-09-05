#include "ft_util.h"


int main(void)
{
    CURLcode global_init_res;
    char *response;
    char *parsed_response;
    const char *url;
    const char *data;
    unsigned char key[crypto_secretbox_KEYBYTES];
    const char *keystr = "0123456789abcdef0123456789abcdef";
    ft_memcpy((void *)key, (const void *)keystr, crypto_secretbox_KEYBYTES);
    if (sodium_init() < 0)
    {
        errprint("sodium_init", "failed to initialize libsodium");
        return (1);
    }
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
    
    response = ft_fetch_command(url, data, key);

    if (!response)
    {
        errprint("ft_fetch_command", "failed to fetch command");
        curl_global_cleanup();
        return (1);
    }
    
    parsed_response = parse_response(response, key);
    if (!parsed_response)
    {
        errprint("parse_response", "failed to parse response");
        free(response);
        curl_global_cleanup();
        return (1);
    }
    
    logme(1, "Received response:");
    logme(0, parsed_response);
    free(response);
    free(parsed_response);
    
    logme(1, "Cleaning up...");
    curl_global_cleanup();
    logme(1, "Client finished.");
    return (0);
}