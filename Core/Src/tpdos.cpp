//****************************************************************************
// File   : tpdos.cpp
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
#include <cstdint>
#include "tpdos.hpp"

TPDO::TPDO (uint32_t id, uint16_t it, uint16_t et, uint8_t tt) : \
    cob_id(id), inhibit_time(it), event_time(et), transmission_type(tt) {
    evtTime     = event_time;
    inhibitTime = inhibit_time;
}