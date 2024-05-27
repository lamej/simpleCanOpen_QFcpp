//****************************************************************************
// File   : RPDO2_DataUnpacker.hpp
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

#include "rpdos.hpp"

class RPDO2_DataUnpacker : public RPDO  {
    public:
        RPDO2_DataUnpacker (uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type);
        
        virtual void receive (const uint8_t data[]) override;
        
        uint32_t unpackedDisplay;
        
    private:

};