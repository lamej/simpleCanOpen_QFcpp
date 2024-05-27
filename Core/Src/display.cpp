//****************************************************************************
// File   : display.cpp
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
#include "applic_OD.hpp"
#include "applic.hpp"
#include "display.hpp"

Display::Display (uint32_t* pInternalDisp, uint32_t* pExternalDisp) : pInternalDisplay(pInternalDisp),
                                                                      pExternalDisplay(pExternalDisp) {
    bspInstance->sTimerAdd(reinterpret_cast<STimeEvt *>(this));
}

#define ITER (24*2)

void Display::tick (void) {
    if (index == 0) {
        internalDisplay_tmp = ~(*pInternalDisplay);
        externalDisplay_tmp = ~(*pExternalDisplay);
        display2serialize = 0;
        
        if (internalDisplay_tmp & 1 << 0) display2serialize |= static_cast<uint32_t>(1) << 5;  // A1
        if (internalDisplay_tmp & 1 << 1) display2serialize |= static_cast<uint32_t>(1) << 4;  // B1
        if (internalDisplay_tmp & 1 << 2) display2serialize |= static_cast<uint32_t>(1) << 1;  // C1
        if (internalDisplay_tmp & 1 << 3) display2serialize |= static_cast<uint32_t>(1) << 2;  // D1
        if (internalDisplay_tmp & 1 << 4) display2serialize |= static_cast<uint32_t>(1) << 3;  // E1
        if (internalDisplay_tmp & 1 << 5) display2serialize |= static_cast<uint32_t>(1) << 6;  // F1
        if (internalDisplay_tmp & 1 << 6) display2serialize |= static_cast<uint32_t>(1) << 7;  // G1
        if (internalDisplay_tmp & 1 << 7) display2serialize |= static_cast<uint32_t>(1) << 0;  // DP1 
        
        if (internalDisplay_tmp & 1 << 8) display2serialize |= static_cast<uint32_t>(1) << 9;   // A2
        if (internalDisplay_tmp & 1 << 9) display2serialize |= static_cast<uint32_t>(1) << 8;   // B2
        if (internalDisplay_tmp & 1 << 10) display2serialize |= static_cast<uint32_t>(1) << 13; // C2
        if (internalDisplay_tmp & 1 << 11) display2serialize |= static_cast<uint32_t>(1) << 14; // D2
        if (internalDisplay_tmp & 1 << 12) display2serialize |= static_cast<uint32_t>(1) << 15; // E2
        if (internalDisplay_tmp & 1 << 13) display2serialize |= static_cast<uint32_t>(1) << 10; // F2
        if (internalDisplay_tmp & 1 << 14) display2serialize |= static_cast<uint32_t>(1) << 11; // G2
        if (internalDisplay_tmp & 1 << 15) display2serialize |= static_cast<uint32_t>(1) << 12; // DP2 
        
        if ((externalDisplay_tmp & 1 << 16) == 0) display2serialize |= static_cast<uint32_t>(1) << 23; // A
        if ((externalDisplay_tmp & 1 << 17) == 0) display2serialize |= static_cast<uint32_t>(1) << 19; // B
        if ((externalDisplay_tmp & 1 << 18) == 0) display2serialize |= static_cast<uint32_t>(1) << 22; // C
        if ((externalDisplay_tmp & 1 << 19) == 0) display2serialize |= static_cast<uint32_t>(1) << 18; // D
        if ((externalDisplay_tmp & 1 << 20) == 0) display2serialize |= static_cast<uint32_t>(1) << 21; // E
        if ((externalDisplay_tmp & 1 << 21) == 0) display2serialize |= static_cast<uint32_t>(1) << 17; // F
        if ((externalDisplay_tmp & 1 << 22) == 0) display2serialize |= static_cast<uint32_t>(1) << 20; // G
        if ((externalDisplay_tmp & 1 << 23) == 0) display2serialize |= static_cast<uint32_t>(1) << 16; // AB 
        
        // if (externalDisplay_tmp & 1 << 24) set the -
        
        
        SR1_setValSTRB(false);
        SR1_setValCLK(false);
        SR1_setValDATA(display2serialize & 1);
        index++;
    } else {
        if (index == ITER + 1) {
            SR1_setValSTRB(true);
            index++;
        } else if (index > ITER + 1) {
            SR1_setValSTRB(false);
            index = 0;
        } else if ((index & 1) == 0) {
            SR1_setValCLK(true);            
            index++;
        } else {
            SR1_setValCLK(false);
            SR1_setValDATA((display2serialize >> (index / 2)) & 1);
            index++;
        }
    }
}