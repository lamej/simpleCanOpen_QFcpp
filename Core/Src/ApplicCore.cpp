//****************************************************************************
// File   : Applic_Core.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-05-21
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************
#include <memory>
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "display.hpp"
#include "Applic_OD.hpp"
#include "Applic.hpp"

/*..........................................................................*/
ApplicCore::ApplicCore (void) : QActive(initial), timeEvt50ms(this, TIMEOUT_20MS_SIG, 0) {   
    timeEvt50ms.armX(20 / TIME_BASE, 20 / TIME_BASE);
    pDisplayDriver = new Display(&internalDisplay, &externalDisplay);
     
    cabinCall = new CabinCallHandler(&call, 0x200 + MB_2_SERIAL16_ID_, 50 / TIME_BASE, 500 / TIME_BASE, 0);   
    OD_Instance->add_tpdos(cabinCall);
    ledCabinCall = new LedCallHandler(0x180 + MB_2_SERIAL16_ID_, 50 / TIME_BASE, 500 / TIME_BASE, 0);
    OD_Instance->add_rpdos(ledCabinCall);
    rpdo2DataUnpacker = new RPDO2_DataUnpacker(0x280 + MB_2_SERIAL16_ID_, 50 / TIME_BASE, 500 / TIME_BASE, 0);
    OD_Instance->add_rpdos(rpdo2DataUnpacker);
    input = new DigitalInputHandler(digitalInput, 0x300 + MB_2_SERIAL16_ID_, 50 / TIME_BASE, 500 / TIME_BASE, 0);   
    OD_Instance->add_tpdos(input);
}

/*..........................................................................*/
Q_STATE_DEF(ApplicCore, initial) {
    (void)e; // unused parameter
    subscribe(DATA_ON_CAN0_RECEIVED_SIG);
    return tran(&run);
}

                                                         //..... QHsm_top .....
Q_STATE_DEF(ApplicCore, run) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            netWorkCounter = 0;
            status = Q_RET_HANDLED;
            break;
        }
        case TIMEOUT_20MS_SIG: {
            if (count > (250 / 20)) {
                count = 0;
                toggleMask ^= (1 << 7) | (1 << 15);
            } else {
                count++;
            }
            if (++netWorkCounter > 10) 
            {
                status = tran(&commProblem);
            }
            else
            {
                cabinCall->tick();
                cabinCall->data[4] = static_cast<uint8_t>(call);
                cabinCall->data[5] = static_cast<uint8_t>(call >> 1*8);
                cabinCall->data[6] = static_cast<uint8_t>(call >> 2*8);
                cabinCall->data[7] = static_cast<uint8_t>(call >> 3*8);
                cabinCall->len = 8;
                OD_Instance->notify(cabinCall);
                input->tick();
                input->data[4] = static_cast<uint8_t>(digitalInput);
                input->len = 8;
                OD_Instance->notify(input);
                internalDisplay = (rpdo2DataUnpacker->unpackedDisplay) | toggleMask;
                externalDisplay = rpdo2DataUnpacker->unpackedDisplay;
                status = Q_RET_HANDLED;
            }
            break;
        }
        case DATA_ON_CAN0_RECEIVED_SIG: {
            netWorkCounter = 0;
            status = Q_RET_HANDLED;
            break;
        }
        default: {
            status = super(&top);
            break;
        }
    }  
    return status;
}

#define ER_ (0x7950)
                                                         //..... QHsm_top .....
Q_STATE_DEF(ApplicCore, commProblem) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            internalDisplay = ER_; // Er
            status = Q_RET_HANDLED;
            break;
        }
        case TIMEOUT_20MS_SIG: {
            if (++count > 12) 
            {   
                count = 0;
                toggle ^= true;
            }
            if (toggle) 
            {
                internalDisplay = ER_;
            }
            else 
            {
                internalDisplay = 0;
            }
            status = Q_RET_HANDLED;
            break;
        }
        case DATA_ON_CAN0_RECEIVED_SIG: {
            status = tran(&run);
            break;
        }
        default: {
            status = super(&top);
            break;
        }
    }  
    return status;
}