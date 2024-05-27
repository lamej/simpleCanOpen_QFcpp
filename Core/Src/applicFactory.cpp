//****************************************************************************
// File   : applicFactory.cpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-01-26
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
#include <string.h>
#include "Applic_OD.hpp"
#include "ApplicCore.hpp"
#include "CANOpen.hpp"
#include "systemIntegrity.hpp"
#include "applicFactory.hpp"

ApplicFactory* ApplicFactory::instance;
QActive*    AO_AX71V20Core;
QActive*    AO_CANOpen;
QActive*    AO_SystemIntegrity;

ApplicFactory::ApplicFactory() {
    static QEvt const *ApplicCoreQueueSto[40];
    static QEvt const *CANOpenQueueSto[100];
    static QEvt const *systemIntegritySto[40];
       
    
    AO_ApplicCore      = new ApplicCore; 
    AO_CANOpen         = new CANOpen(EXT_CARD1CAB_ID_);
    AO_SystemIntegrity = new SystemIntegrity;

    AO_ApplicCore->start (3U,                                    /* priority */
                      ApplicCoreQueueSto, Q_DIM(ApplicCoreQueueSto),
                      (void *)0, 0U);	             /* no inialization event */
    AO_CANOpen->start  (4U,                                       /* priority */
                      CANOpenQueueSto, Q_DIM(CANOpenQueueSto),
                      (void *)0, 0U);	             /* no inialization event */
    AO_SystemIntegrity->start (5U,                                /* priority */
                      systemIntegritySto, Q_DIM(systemIntegritySto),
                      (void *)0, 0U);		     /* no inialization event */
}