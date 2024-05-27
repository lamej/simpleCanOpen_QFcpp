//****************************************************************************
// File   : display.hpp
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
#pragma once

#include "sTimer.hpp"

class Display : public STimeEvt {
    public:
        Display (uint32_t* pInternalDisp, uint32_t* pExternalDisp);
        virtual void tick (void) override;
        
    private:
        uint8_t index = 0;
        uint32_t display2serialize = 0;
        uint32_t internalDisplay_tmp;
        uint32_t externalDisplay_tmp;
        
        const uint32_t *pInternalDisplay;
        const uint32_t *pExternalDisplay;
};