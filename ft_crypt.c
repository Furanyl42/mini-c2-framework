#include "ft_util.h"


char *ft_encrypt_and_b64(const char *message, const unsigned char *key)
{
    unsigned long long msg_len = ft_strlen(message);
    unsigned long long ciphertext_len = msg_len + crypto_secretbox_MACBYTES;
    unsigned long long total_len = ciphertext_len + crypto_secretbox_NONCEBYTES;

    unsigned char *combined;
    char *b64_output;
    size_t b64_len;

    combined = malloc(total_len);
    if (!combined)
    {
        errprint("malloc", "failed to allocate memory for combined");
        return NULL;
    }
    randombytes_buf(combined, crypto_secretbox_NONCEBYTES);
    if (crypto_secretbox_easy(combined + crypto_secretbox_NONCEBYTES, (const unsigned char *)message, msg_len, combined, key) != 0)
    {
        errprint("crypto_secretbox_easy", "encryption failed");
        free(combined);
        return NULL;
    }
    b64_len = sodium_base64_ENCODED_LEN(total_len, sodium_base64_VARIANT_ORIGINAL);
    b64_output = malloc(b64_len);
    if (!b64_output)
    {
        errprint("malloc", "failed to allocate memory for base64 output");
        free(combined);
        return NULL;
    }
    sodium_bin2base64(b64_output, b64_len, combined, total_len, sodium_base64_VARIANT_ORIGINAL);
    free(combined);
    return b64_output;
}