//****************************************************************************
// File   : ApplicCore.hpp
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

#include "cabinCallHandler.hpp"
#include "LedCallHandler.hpp"
#include "RPDO2_DataUnpacker.hpp"
#include "digitalInputHandler.hpp"

class STimeEvt;

class ApplicCore : public QActive {
    public:
        ApplicCore (void);
        STimeEvt         *pDisplayDriver;
        
        uint32_t internalDisplay;
        uint32_t externalDisplay;
        uint32_t call = 0;
        uint32_t digitalInput;
        uint32_t doorStatus;
        uint32_t arrow;
        bool     gong;
        bool     timedLight;
        
        uint32_t netWorkCounter = 0;
    
    protected: 
        Q_STATE_DECL(initial);
        Q_STATE_DECL(run);
        Q_STATE_DECL(commProblem);
        
    private:
        QTimeEvt  timeEvt50ms;                           /*..... timeout timer .....*/
        CabinCallHandler    *cabinCall;         // TPDO1
        DigitalInputHandler *input;             // TPDO2
        LedCallHandler      *ledCabinCall;      // RPDO1
        RPDO2_DataUnpacker  *rpdo2DataUnpacker;  //RPDO2
};