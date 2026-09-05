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

char *ft_decrypt_from_b64(const char *b64_payload, const unsigned char *key)
{
    unsigned char *decoded;
    unsigned long long decoded_len;
    unsigned long long ciphertext_len;
    char *plaintext;
    size_t bin_max_len;

    bin_max_len = ft_strlen(b64_payload);
    decoded = malloc(bin_max_len);
    if (!decoded)
    {
        errprint("malloc", "failed to allocate memory for decoded");
        return NULL;
    }
    if (sodium_base642bin(decoded, bin_max_len, b64_payload, ft_strlen(b64_payload), NULL, &decoded_len, NULL, sodium_base64_VARIANT_ORIGINAL) != 0)
    {
        errprint("sodium_base642bin", "base64 decoding failed");
        free(decoded);
        return NULL;
    }

    if (decoded_len < crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES)
    {
        errprint("ft_decrypt_from_b64", "decoded payload is too short");
        free(decoded);
        return NULL;
    }
    ciphertext_len = decoded_len - crypto_secretbox_NONCEBYTES;
    plaintext = malloc(ciphertext_len - crypto_secretbox_MACBYTES + 1);
    if (!plaintext)
    {
        errprint("malloc", "failed to allocate memory for plaintext");
        free(decoded);
        return NULL;
    }
    if (crypto_secretbox_open_easy((unsigned char *)plaintext, decoded + crypto_secretbox_NONCEBYTES, ciphertext_len, decoded, key) != 0)
    {
        errprint("crypto_secretbox_open_easy", "decryption failed");
        free(decoded);
        free(plaintext);
        return NULL;
    }
    plaintext[ciphertext_len - crypto_secretbox_MACBYTES] = '\0';
    free(decoded);
    return (plaintext);
}