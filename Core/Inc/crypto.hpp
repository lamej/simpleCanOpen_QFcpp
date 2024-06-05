//****************************************************************************
// File   : Crypto.hpp
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

#pragma once

#include <vector>



extern std::vector<uint8_t> crypto_key_iv; // Declare as extern

class Crypto {
public:
    Crypto(const std::vector<uint8_t>& key);

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext);

    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext);
    

private:
    std::vector<uint8_t> S;
    uint8_t i, j, k, z, a, w, lastCipherByte;

    std::vector<uint8_t> process(const std::vector<uint8_t>& data);
    std::vector<uint8_t> encrypt_(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decrypt_(const std::vector<uint8_t>& data);
    
    void initialize (const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv);
    void update(void);
    void shuffle(void);
    void whip(size_t r);
    void crush(void);
    void absorbNibble(uint8_t x);
    void absorb(const std::vector<uint8_t>& I);
    uint8_t getOutput(void);
    void absorbOutput(uint8_t outputByte);
        
};
