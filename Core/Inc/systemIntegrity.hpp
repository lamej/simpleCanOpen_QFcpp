//****************************************************************************
// File   : systemIntegrity.hpp
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

struct SystemTag {
    QActive super;
    QTimeEvt timeEvt;                             /*..... timeout timer .....*/ 
    bool  LEDtoggle;
};

class SystemIntegrity : public QActive {
    public:
        SystemIntegrity (void);
        
    protected:
        Q_STATE_DECL(initial);
        Q_STATE_DECL(run);
        
    private:
        QTimeEvt timeEvt20ms;
};