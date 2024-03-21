#include <iostream>
#include <string>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <cstring>

class AESCipher {
public:
    AESCipher(const std::string& key_str) {
        unsigned char key[EVP_MAX_KEY_LENGTH];
        unsigned char iv[EVP_MAX_IV_LENGTH];
        if (EVP_BytesToKey(EVP_aes_128_cbc(), EVP_sha256(), NULL,
                            reinterpret_cast<const unsigned char*>(key_str.c_str()),
                            key_str.size(), 1, key, iv) != 16) {
            std::cerr << "Error generating key and IV" << std::endl;
            return;
        }

        memset(iv_, 0, sizeof(iv_));
        ctx_ = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx_, EVP_aes_128_cbc(), NULL, key, iv_);
    }

    ~AESCipher() {
        EVP_CIPHER_CTX_free(ctx_);
    }

    std::string encrypt(const std::string& plaintext) {
        int ciphertext_len = plaintext.size() + EVP_MAX_BLOCK_LENGTH;
        unsigned char ciphertext[ciphertext_len];
        int len;
        EVP_EncryptInit_ex(ctx_, NULL, NULL, NULL, NULL);
        EVP_EncryptUpdate(ctx_, ciphertext, &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
        int ciphertext_len2;
        EVP_EncryptFinal_ex(ctx_, ciphertext + len, &ciphertext_len2);
        return std::string(reinterpret_cast<char*>(ciphertext), len + ciphertext_len2);
    }

    std::string decrypt(const std::string& ciphertext) {
        int plaintext_len = ciphertext.size() + EVP_MAX_BLOCK_LENGTH;
        unsigned char plaintext[plaintext_len];
        int len;
        EVP_DecryptInit_ex(ctx_, NULL, NULL, NULL, NULL);
        EVP_DecryptUpdate(ctx_, plaintext, &len, reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
        int plaintext_len2;
        EVP_DecryptFinal_ex(ctx_, plaintext + len, &plaintext_len2);
        return std::string(reinterpret_cast<char*>(plaintext), len + plaintext_len2);
    }

private:
    EVP_CIPHER_CTX* ctx_;
    unsigned char iv_[EVP_MAX_IV_LENGTH];
};