//****************************************************************************
// File   : cabinCallHandler.cpp
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
//****************************************************************************
#include <string.h>
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "Applic_OD.hpp"
#include "ApllicCore.hpp"
#include "cabinCallHandler.hpp"

CabinCallHandler::CabinCallHandler (uint32_t* pCC, uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type) \
    : pCabinCall(pCC), TPDO(cob_id, inhibit_time, event_time, transmission_type) {
}

void CabinCallHandler::tick (void) {
    getCall();
}

void CabinCallHandler::getCall (void) {
    uint32_t tmp = 0;
    if (E01_readVal()) tmp |= 1 << 0;
    if (E02_readVal()) tmp |= 1 << 1;
    if (E03_readVal()) tmp |= 1 << 2;
    if (E04_readVal()) tmp |= 1 << 3;
    if (E05_readVal()) tmp |= 1 << 4;
    if (E06_readVal()) tmp |= 1 << 5;
    if (E07_readVal()) tmp |= 1 << 6;
    if (E08_readVal()) tmp |= 1 << 7;
    if (E09_readVal()) tmp |= 1 << 8;
    if (E10_readVal()) tmp |= 1 << 9;
    if (E11_readVal()) tmp |= 1 << 10;
    if (E12_readVal()) tmp |= 1 << 11;
    if (E13_readVal()) tmp |= 1 << 12;
    if (E14_readVal()) tmp |= 1 << 13;
    if (E15_readVal()) tmp |= 1 << 14;
    if (E16_readVal()) tmp |= 1 << 15;
    if (index >= FILTER_SIZE) index = 0;
    filtredCall[index] = tmp;
    index++;
    tmp = ~0;
    for (size_t i = 0; i < FILTER_SIZE; ++i) {
        tmp &= filtredCall[i];
    }
    *pCabinCall = tmp;
}