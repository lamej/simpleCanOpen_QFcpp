//****************************************************************************
// File   : Crypto.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2024-06-02
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************
#include <vector>
#include "crypto.hpp"  // algorithme SpritzBC

std::vector<uint8_t> secondary_key = {0x09, 0xF2, 0x19, 0x4A, 0x87, 0xAE, 0xB8, 0x92};
std::vector<uint8_t> crypto_key_iv = {0x21, 0x23, 0x07, 0x51, 0x22, 0x15, 0x3A, 0xCC};

std::vector<uint8_t> Crypto::encrypt(const std::vector<uint8_t>& plaintext) {
    std::vector<uint8_t> result(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); ++i) {
        result[i] = plaintext[i] ^ secondary_key[i%secondary_key.size()];
    }
    return encrypt_(result);
}

std::vector<uint8_t> Crypto::decrypt(const std::vector<uint8_t>& ciphertext) {
    std::vector<uint8_t> result = decrypt_(ciphertext);
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ secondary_key[i%secondary_key.size()];
    }
    return result;
}


Crypto::Crypto (const std::vector<uint8_t>& key) : i(0), j(0), k(0), z(0), a(0), w(1) {
    S.resize(256);
    for (int v = 0; v < 256; ++v) S[v] = v;
    initialize(key, crypto_key_iv);
}

void Crypto::update() {
    i = (i + w) % 256;
    j = (k + S[(j + S[i]) % 256]) % 256;
    k = (i + k + S[j]) % 256;
    std::swap(S[i], S[j]);
    z = S[(j + S[(i + S[(z + k) % 256]) % 256]) % 256];
}

// This function simulates a hashing effect by updating the state with the output
void Crypto::absorbOutput(uint8_t outputByte) {
    a = (a + outputByte) % 256;
    i = (i + a) % 256;
    j = (j + z) % 256;
    std::swap(S[i], S[j]);
}
void Crypto::shuffle() {
    whip(512);
    crush();
    whip(512);
    crush();
    whip(512);
    a = 0;
}

void Crypto::whip(size_t r) {
    for (size_t v = 0; v < r; ++v) {
        update();
    }
    w = (w + 2) % 256;
    if (w == 0) w = 1; // w must not be 0
}

void Crypto::crush() {
    for (size_t v = 0; v < 128; ++v) {
        if (S[v] > S[255 - v]) {
            std::swap(S[v], S[255 - v]);
        }
    }
}    

void Crypto::absorbNibble(uint8_t x) {
    if (a == 128) shuffle();
    std::swap(S[a], S[128 + x]);
    a++;
}

void Crypto::absorb(const std::vector<uint8_t>& I) {
    for (uint8_t x : I) {
        absorbNibble(x & 0x0F);
        absorbNibble(x >> 4);
    }
}

uint8_t Crypto::getOutput() {
    update();
    return z;
}

void Crypto::initialize(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
    absorb(key);
    shuffle();
    lastCipherByte = iv[0]; // Utiliser l'IV pour le premier XOR de chiffrement
}


std::vector<uint8_t> Crypto::encrypt_(const std::vector<uint8_t>& plaintext) {
    std::vector<uint8_t> ciphertext(plaintext.size());
    for (size_t m = 0; m < plaintext.size(); ++m) {
        uint8_t plaintextByte = plaintext[m] ^ lastCipherByte; // XOR avec le dernier octet chiffré ou l'IV
        lastCipherByte = plaintextByte ^ getOutput(); // Chiffrement Spritz
        ciphertext[m] = lastCipherByte;
        lastCipherByte ^= crypto_key_iv[lastCipherByte % crypto_key_iv.size()];
    }
    return ciphertext;
}

std::vector<uint8_t> Crypto::decrypt_(const std::vector<uint8_t>& ciphertext) {
    std::vector<uint8_t> plaintext(ciphertext.size());
    for (size_t m = 0; m < ciphertext.size(); ++m) {
        uint8_t outputByte = getOutput(); // Générer l'octet de sortie Spritz
        plaintext[m] = ciphertext[m] ^ outputByte ^ lastCipherByte; // XOR avec l'octet de sortie et le dernier octet chiffré ou l'IV
        lastCipherByte = ciphertext[m]; // Mettre à jour le dernier octet chiffré pour le prochain tour
        lastCipherByte ^= crypto_key_iv[lastCipherByte % crypto_key_iv.size()];
    }
    return plaintext;
}