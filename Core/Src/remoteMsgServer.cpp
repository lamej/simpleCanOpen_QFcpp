//****************************************************************************
// File   : applicFactory.hpp
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
#include <stdlib.h>
#include <string.h>
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"
#include "CANOpen.hpp"

extern CAN_HandleTypeDef    hcan;

RemoteMsgServer::RemoteMsgServer (CANOpen* co_) : QHsm (initial), co(co_) {
}


/*..........................................................................*/
Q_STATE_DEF(RemoteMsgServer, initial) {
    (void)e; // unused parameter
    requestQueue.init(requestQSto, Q_DIM(requestQSto));
    return tran(&idle);
}

/*.......... Parametrage wait - absence de console ..........................*/
Q_STATE_DEF(RemoteMsgServer, idle) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            co->recall(&requestQueue);
            status = Q_RET_HANDLED;
            break;
        }
        case TPDO_DSPLY_SIG: 
        case CANOPEN_TX_SIG:
        case DATA_ON_CAN0_RECEIVED_SIG: {
            uint32_t pTxMailBox;
            if (HAL_CAN_AddTxMessage(&hcan, &(((CANOpenEvt* )e)->TxMessage), ((CANOpenEvt* )e)->buffer, &pTxMailBox) != HAL_OK) { 
                co->defer(&requestQueue, e); 
                status = tran(&busy);
            } else {                
                status = Q_RET_HANDLED;
            }
            break;
        }
        case ON_CAN0_TX_COMPLETE_SIG: {
            co->recall(&requestQueue);
            status = Q_RET_HANDLED;
            break;
        }
        case Q_EXIT_SIG: {
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

/*...........................................................................*/
Q_STATE_DEF(RemoteMsgServer, busy) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            status = Q_RET_HANDLED;
            break;
        }
        case TPDO_DSPLY_SIG: 
        case CANOPEN_TX_SIG:
        case DATA_ON_CAN0_RECEIVED_SIG: {
            co->defer(&requestQueue, e);
            status = Q_RET_HANDLED;
            break;
        }
        case ON_CAN0_TX_COMPLETE_SIG: {
            status = tran(&idle);
            break;
        }
        default: {
            status = super(&top);
            break;
        }
    }
    return status;
}
