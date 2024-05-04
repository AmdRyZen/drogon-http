
#ifndef DROGON_HTTP_AESOPENSSL_H
#define DROGON_HTTP_AESOPENSSL_H

#include <string>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <string>

class aesOpenssl {
public:
    [[gnu::always_inline]] inline static std::vector<unsigned char> PKCS5Padding(const std::vector<unsigned char>& input, int block_size);

    [[gnu::always_inline]] inline static std::vector<unsigned char> stringToBytes(const std::string& str);

    [[gnu::always_inline]] inline static std::string AesCBCPk5EncryptBase64(const std::string& origData, const std::string& keyHex, const std::string& ivHex);

    [[gnu::always_inline]] inline static std::string AesCBCPk5DecryptBase64(const std::string& ciphertextBase64, const std::string& keyHex, const std::string& ivHex);
};

std::vector<unsigned char> aesOpenssl::PKCS5Padding(const std::vector<unsigned char>& input, const int block_size) {
    const std::vector<unsigned char>::size_type padding = block_size - input.size() % block_size;
    std::vector<unsigned char> padded_input(input);
    padded_input.insert(padded_input.end(), padding, padding);
    return padded_input;
}

std::vector<unsigned char> aesOpenssl::stringToBytes(const std::string& str) {
    return {str.begin(), str.end()};
}

std::string aesOpenssl::AesCBCPk5EncryptBase64(const std::string& origData, const std::string& keyHex, const std::string& ivHex) {
    const std::vector<unsigned char> key = stringToBytes(keyHex);
    const std::vector<unsigned char> iv = stringToBytes(ivHex);
    //std::vector<unsigned char> origData = hexStringToBytes(origDataHex);
    const std::vector<unsigned char> origDataBytes = stringToBytes(origData);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());

    const std::vector<unsigned char> padded_data = PKCS5Padding(origDataBytes, EVP_CIPHER_CTX_block_size(ctx));
    std::vector<unsigned char> ciphertext(padded_data.size() + EVP_CIPHER_CTX_block_size(ctx));

    int len;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, padded_data.data(), static_cast<int>(padded_data.size()));
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    BUF_MEM *bufferPtr;
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    BIO_push(b64, bio);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, ciphertext.data(), ciphertext_len);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bufferPtr);
    BIO_set_close(b64, BIO_NOCLOSE);
    BIO_free_all(b64);

    std::string encoded(bufferPtr->data, bufferPtr->length);
    BUF_MEM_free(bufferPtr);

    return encoded;
}

std::string aesOpenssl::AesCBCPk5DecryptBase64(const std::string& ciphertextBase64, const std::string& keyHex, const std::string& ivHex) {
    const std::vector<unsigned char> key = stringToBytes(keyHex);
    const std::vector<unsigned char> iv = stringToBytes(ivHex);

    // Decode Base64 ciphertext
    //BUF_MEM *bufferPtr;
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new_mem_buf(ciphertextBase64.c_str(), static_cast<int>(ciphertextBase64.length()));

    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    std::vector<unsigned char> ciphertext(ciphertextBase64.length());
    const int ciphertext_len = BIO_read(bio, ciphertext.data(), static_cast<int>(ciphertextBase64.length()));
    BIO_free_all(bio);

    // Decrypt ciphertext
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());

    std::vector<unsigned char> plaintext(ciphertext_len + EVP_CIPHER_CTX_block_size(ctx));
    int len;
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext_len);
    int plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Remove PKCS5 padding
    const int padding = plaintext[plaintext_len - 1];
    plaintext_len -= padding;

    return {reinterpret_cast<char*>(plaintext.data()), static_cast<std::string::size_type>(plaintext_len)};
}


#endif  //DROGON_HTTP_AESOPENSSL_H