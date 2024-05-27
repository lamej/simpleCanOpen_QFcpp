//****************************************************************************
// File   : systemIntegrity.cpp
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
#include <string>
#include "qpcpp.hpp"
#include "main.h"
#include "wwdg.h"
#include "bsp.hpp"
#include "systemIntegrity.hpp"

enum {
    SYSTEM_TIME = 20,
                       /*.... internal events (not published to the QF) .....*/
    SYS_TIMEOUT_SIG = MAX_PUB_SIG,
};

/*..........................................................................*/
SystemIntegrity::SystemIntegrity (void) : QActive(initial), timeEvt20ms(this, SYS_TIMEOUT_SIG, 0) {
}


/*..........................................................................*/
Q_STATE_DEF(SystemIntegrity, initial) {
    (void)e; // unused parameter
    subscribe(TIME_TICK_SIG);  /*... period = 1 ms ...*/
    timeEvt20ms.armX(SYSTEM_TIME / TIME_BASE, SYSTEM_TIME / TIME_BASE);
    return tran(&run);
}

/*..........................................................................*/
                                                       /*..... QHsm_top .....*/
Q_STATE_DEF(SystemIntegrity, run) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            status = Q_RET_HANDLED;
            break;
        }
        case SYS_TIMEOUT_SIG: {
            HAL_WWDG_Refresh(&hwwdg);
            status = Q_RET_HANDLED;
            break;
        }
        case TIME_TICK_SIG: {
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