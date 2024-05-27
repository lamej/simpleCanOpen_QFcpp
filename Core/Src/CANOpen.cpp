//****************************************************************************
// File   : CANOpen.cpp
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
#include "CANOpen.hpp"
#include "Applic_OD.hpp"

enum {
    HEARTBEAT_PRODUCER_TIME = 1000,
    HEARTBEAT_CONSUMER_TIME = 1500,
                       /*.... internal events (not published to the QF) .....*/
    CO_TIMEOUT_SIG = MAX_PUB_SIG
};


/*..........................................................................*/
CANOpen::CANOpen (uint32_t id) : QActive(initial), cob_id(id), timeEvt__(this, CO_TIMEOUT_SIG, 0) {
}

/*..........................................................................*/
/*..........................................................................*/
Q_STATE_DEF(CANOpen, initial) {
    (void)e; // unused parameter
    subscribe(TIME_TICK_SIG);   //..... period = 10 ms ...
    subscribe(DATA_ON_CAN0_RECEIVED_SIG);
    subscribe(TPDO_DSPLY_SIG);
    subscribe(ON_CAN0_TX_COMPLETE_SIG);
    subscribe(CANOPEN_TX_SIG);
    subscribe(CANOPEN_NOTIFY_SIG);
    msgServer = new RemoteMsgServer(this);
    msgServer->init(qs_dummy);
    OD_Instance->setDriver(this);
    return tran(&run);
}
                                                         //..... QHsm_top .....
                                                        //..... CANopen_top .....
Q_STATE_DEF(CANOpen, run) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {            
            status = Q_RET_HANDLED;
            break;
        }
        case CANOPEN_NOTIFY_SIG: {
            static_cast<CANOpenEvt*>(const_cast<QEvt*>(e))->tpdo_->cos = true;
            status = Q_RET_HANDLED;
            break;
        } 
        case CANOPEN_TX_SIG: {
            ((CANOpenEvt *)e)->TxMessage.StdId = ((CANOpenEvt *)e)->cob_id_;
            ((CANOpenEvt *)e)->TxMessage.DLC = ((CANOpenEvt *)e)->length_;
            ((CANOpenEvt *)e)->TxMessage.RTR = CAN_RTR_DATA;
            ((CANOpenEvt *)e)->TxMessage.IDE = CAN_ID_STD;
            msgServer->dispatch(e, qs_dummy);
            status = Q_RET_HANDLED;
            break;
        }   
        case ON_CAN0_TX_COMPLETE_SIG: {
            msgServer->dispatch(e, qs_dummy);
            status = Q_RET_HANDLED;
            break;
        }
        case TIME_TICK_SIG: {
            time_stamp++;
            processTPDOs();
            for (auto rpdo : OD_Instance->rpdos_vect) {
                if (rpdo->inhibitTime != 0) {
                    rpdo->inhibitTime--;
                }
            }
            status = Q_RET_HANDLED;
            break;
        }
 
        case DATA_ON_CAN0_RECEIVED_SIG: {
            if ((((CANOpenEvt *)e)->cob_id_ == (0x180 + 0x100*0 + MB_2_SERIAL16_ID_)) \
                or (((CANOpenEvt *)e)->cob_id_ == (0x180 + 0x100*1 + MB_2_SERIAL16_ID_))) {
                processRPDOs(e);
            }                          
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

void CANOpen::notify (TPDO* tpdo) {
    CANOpenEvt *pe;
    
    pe = Q_NEW(CANOpenEvt, CANOPEN_NOTIFY_SIG);
    pe->tpdo_ = tpdo;
    QF::PUBLISH((QEvt *)pe, &dummy);
}

void CANOpen::transmit (TPDO *tpdo) {
    if (tpdo->len) {
        CANOpenEvt *pe;
        pe = Q_NEW(CANOpenEvt, CANOPEN_TX_SIG);
        pe->cob_id_ = tpdo->cob_id;
        pe->length_ = 8;
 
        for (uint32_t i = 0; i < 8; i++) {
            (pe->buffer)[i] = tpdo->data[i];
        }
        QF::PUBLISH((QEvt *)pe, &dummy);
    }
}

void CANOpen::processTPDOs() {
    for (auto tpdo : OD_Instance->tpdos_vect) {
        if (tpdo->inhibitTime != 0) {
            tpdo->inhibitTime--;
        } else {
            if ((tpdo->evtTime != 0) and (tpdo->cos == false)) {
                tpdo->evtTime--;
            } else {
                tpdo->inhibitTime = tpdo->inhibit_time;
                tpdo->evtTime     = tpdo->event_time;
                tpdo->cos         = false;
                transmit(tpdo);
            }
        }
    }
}

void CANOpen::processRPDOs (const QEvt *e) {
    auto canOpenEvt = static_cast<const CANOpenEvt*>(e);
    for (auto rpdo : OD_Instance->rpdos_vect) {
        if (rpdo->cob_id == canOpenEvt->cob_id_) {
            rpdo->inhibitTime = rpdo->inhibit_time;
            rpdo->len = reinterpret_cast<CANOpenEvt*>(const_cast<QEvt*>(e))->TxMessage.DLC;
            uint8_t data[8];
            for (uint32_t i = 0; i < 8; i++) {
                data[i] = reinterpret_cast<CANOpenEvt*>(const_cast<QEvt*>(e))->buffer[i];
            }
            rpdo->receive(data);
        }
    }
}