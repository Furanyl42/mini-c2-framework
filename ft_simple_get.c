#include "ft_util.h"

int ft_simple_get(const char *url)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (!curl)
	{
		errprint("CURL", "Cant init");
		return (-1);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	{
		errprint("CURL", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		return (-1);
	}
	
	curl_easy_cleanup(curl);
	return (0);
}