#include "ft_util.h"

char *ft_http_post(const char *url, const char *data)
{
    CURL *curl_handle;
    CURLcode res;
    t_memory chunk;
	struct curl_slist *headers;

	headers = NULL;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_handle = curl_easy_init();
    if (!curl_handle)
    {
        errprint("curl_easy_init", "failed to initialize");
        return (NULL);
    }

	headers = curl_slist_append(headers, "Content-Type: application/json");
	if (!headers)
	{
		errprint("curl_slist_append", "failed to append");
		return (NULL);
	}
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

	res = curl_easy_perform(curl_handle);
	if (res != CURLE_OK)
	{
		errprint("curl_easy_perform", curl_easy_strerror(res));
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl_handle);
		return (NULL);
	}
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl_handle);
	return (chunk.memory);
}
