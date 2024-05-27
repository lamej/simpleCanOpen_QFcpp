//****************************************************************************
// File   : Applic_OD.hpp
// Last Updated for Version: 0.0.1
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
#include "CANOpen.hpp"
#include "tpdos.hpp"
#include "rpdos.hpp"


class OD {
    static OD *instance;
    OD (void) {}
    public:   
        static OD* getInstance () {
            if (instance == nullptr) {
                instance = new OD();
            }
            return instance;
        }
        void add_tpdos (TPDO *tpdo);
        void add_rpdos (RPDO *rpdo);
        void setDriver (CANOpen *drv);
        void notify (TPDO* pdo);  
        std::vector<TPDO *> tpdos_vect;
        std::vector<RPDO *> rpdos_vect;
    private:
        CANOpen *driver = nullptr;
};

extern OD* OD_Instance;