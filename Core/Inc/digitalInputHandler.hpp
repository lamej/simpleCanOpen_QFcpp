//****************************************************************************
// File   : digitalInput.hpp
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
//****************************************************************************
#pragma once

#include "tpdos.hpp"

class DigitalInputHandler : public TPDO {
    public:
        DigitalInputHandler (uint32_t& digitalInput, uint32_t cob_id, uint16_t inhibit_time, uint16_t event_time, uint8_t transmission_type);
        void tick (void);
        
    private:
        void getInput (void);
        
    private:
        uint32_t *pDigitalInput;
        uint32_t filtredInput[FILTER_SIZE];
        size_t   index = 0;
};