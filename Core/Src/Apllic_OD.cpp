//****************************************************************************
// File   : Applic_OD.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-05-23
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "Applic_OD.hpp"


OD* OD::instance;
OD* OD_Instance = OD::getInstance();

void OD::setDriver (CANOpen *drv) {
    driver = drv;
}
void OD::notify (TPDO *pdo) {
    if (driver) {
        driver->notify (pdo);
    }
}
void OD::add_tpdos (TPDO *tpdo) {
    tpdos_vect.push_back(tpdo);
}
void OD::add_rpdos (RPDO *rpdo) {
    rpdos_vect.push_back(rpdo);
}