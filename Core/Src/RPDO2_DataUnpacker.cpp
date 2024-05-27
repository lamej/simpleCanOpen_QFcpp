//****************************************************************************
// File   : RPDO2_DataUnpacker.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-02-01
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "RPDO2_DataUnpacker.hpp"

RPDO2_DataUnpacker::RPDO2_DataUnpacker (uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type) : \
    RPDO(cob_id, inhibit_time, event_time, transmission_type) {
}

void RPDO2_DataUnpacker::receive (const uint8_t data[]) {
    uint32_t value = 0;
    uint32_t tmp;
    
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        value |= static_cast<uint32_t>(data[4 + i]) << (8 * i);
    }
    tmp = (((value & 0x3F80) << 1) + (value & 0x7F)) & 0x00007FFF; 
    tmp |= ((value & 0x03FC000) << 2);    
    unpackedDisplay = tmp;
    (value & (1 << 22)) ? G2_writeVal(true)   : G2_writeVal(false); 
    (value & (1 << 25)) ? fm_writeVal(true)   : fm_writeVal(false);
    (value & (1 << 26)) ? fd_writeVal(true)   : fd_writeVal(false);
    (value & (1 << 24)) ? gng_writeVal(true)  : gng_writeVal(false);
    (value & (1 << 27)) ? door1Open_(true)    : door1Open_(false);
    (value & (1 << 28)) ? door2Open_(true)    : door2Open_(false);
    (value & (1 << 29)) ? doorClose_(true)    : doorClose_(false);
    (value & (1 << 30)) ? ec_writeVal(false)  : ec_writeVal(true);
    
}