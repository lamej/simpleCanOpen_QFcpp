//****************************************************************************
// File   : ledCallHandler.hpp
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
#include "rpdos.hpp"

class LedCallHandler : public STimeEvt, public RPDO {
    public:
        LedCallHandler (uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type);
        virtual void tick (void) override;
        virtual void receive (const uint8_t data[]) override;
        
    private:
        uint8_t index = 0;
        uint32_t display2serialize = 0;
        uint32_t ledCall_tmp = 0;        
        uint32_t ledCall = 0;
};