//****************************************************************************
// File   : digitalInputHandler.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-05-22
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
#include "digitalInputHandler.hpp"

DigitalInputHandler::DigitalInputHandler (uint32_t& digitalInput, uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type) \
    : l_digitalInput(digitalInput), TPDO(cob_id, inhibit_time, event_time, transmission_type) {
}

void DigitalInputHandler::tick (void) {
    getInput();
}

void DigitalInputHandler::getInput (void) {
    uint32_t tmp = 0;
    if (PCL_readVal() == false) tmp |= 1 << 0;
    if (FL_readVal())  tmp |= 1 << 1;
    if (OVL_readVal()) tmp |= 1 << 2;
    if (FR_readVal())  tmp |= 1 << 3;
    
    if (index >= FILTER_SIZE) index = 0;
    filtredInput[index] = tmp;
    index++;
    tmp = ~0;
    for (size_t i = 0; i < FILTER_SIZE; ++i) {
        tmp &= filtredInput[i];
    }
    l_digitalInput = tmp;
}