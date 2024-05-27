//****************************************************************************
// File   : ledCallHandler.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-05-25
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************
#include <string.h>
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "Applic_OD.hpp"
#include "ApplicCore.hpp"
#include "ledCallHandler.hpp"

LedCallHandler::LedCallHandler(uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type) \
    : RPDO(cob_id, inhibit_time, event_time, transmission_type) {
    bspInstance->sTimerAdd(reinterpret_cast<STimeEvt *>(this));
}

#define ITER (16*2)

void LedCallHandler::tick (void) {
    if (index == 0) {
        ledCall_tmp = ledCall;
        display2serialize = 0;
        
        if (ledCall_tmp & 1 << 0) display2serialize |= static_cast<uint32_t>(1) << 15; // S01  
        if (ledCall_tmp & 1 << 1) display2serialize |= static_cast<uint32_t>(1) << 14; // S02  
        if (ledCall_tmp & 1 << 2) display2serialize |= static_cast<uint32_t>(1) << 13; // S03  
        if (ledCall_tmp & 1 << 3) display2serialize |= static_cast<uint32_t>(1) << 12; // S04  
        if (ledCall_tmp & 1 << 4) display2serialize |= static_cast<uint32_t>(1) << 6;  // S05 
        if (ledCall_tmp & 1 << 5) display2serialize |= static_cast<uint32_t>(1) << 7;  // S06
        if (ledCall_tmp & 1 << 6) display2serialize |= static_cast<uint32_t>(1) << 11; // S07 
        if (ledCall_tmp & 1 << 7) display2serialize |= static_cast<uint32_t>(1) << 10; // S08 
        
        if (ledCall_tmp & 1 << 8) display2serialize |= static_cast<uint32_t>(1) << 9;  // S09  
        if (ledCall_tmp & 1 << 9) display2serialize |= static_cast<uint32_t>(1) << 8;  // S10  
        if (ledCall_tmp & 1 << 10) display2serialize |= static_cast<uint32_t>(1) << 3; // S11 
        if (ledCall_tmp & 1 << 11) display2serialize |= static_cast<uint32_t>(1) << 2; // S12 
        if (ledCall_tmp & 1 << 12) display2serialize |= static_cast<uint32_t>(1) << 1; // S13 
        if (ledCall_tmp & 1 << 13) display2serialize |= static_cast<uint32_t>(1) << 0; // S14
        if (ledCall_tmp & 1 << 14) display2serialize |= static_cast<uint32_t>(1) << 4; // S15 
        if (ledCall_tmp & 1 << 15) display2serialize |= static_cast<uint32_t>(1) << 5; // S16         
        
        SR2_setValSTRB(false);
        SR2_setValCLK(false);
        SR2_setValDATA(display2serialize & 1);
        index++;
    } else {
        if (index == ITER + 1) {
            SR2_setValSTRB(true);
            index++;
        } else if (index > ITER + 1) {
            SR2_setValSTRB(false);
            index = 0;
        } else if ((index & 1) == 0) {
            SR2_setValCLK(true);            
            index++;
        } else {
            SR2_setValCLK(false);
            SR2_setValDATA((display2serialize >> (index / 2)) & 1);
            index++;
        }
    }
}

void LedCallHandler::receive (const uint8_t data[]) {
    uint32_t value = 0;
    
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        value |= static_cast<uint32_t>(data[4 + i]) << (8 * i);
    }
    ledCall = value;
}