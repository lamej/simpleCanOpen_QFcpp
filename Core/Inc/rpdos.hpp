//****************************************************************************
// File   : rpdos.hpp
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

class RPDO  {
    public:
        RPDO (uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type);
        
        uint8_t        len;
        uint8_t        data[8];
        uint16_t       evtTime;
        uint16_t       inhibitTime;
        
        
        const uint32_t cob_id;       
        const uint16_t inhibit_time;
        
        virtual void receive (const uint8_t data[]) = 0;
        
    private:       
        const uint16_t event_time;
        const uint8_t  transmission_type;
};