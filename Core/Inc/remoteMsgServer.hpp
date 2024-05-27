//****************************************************************************
// File   : remoteMSgServer.hpp
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
//****************************************************************************

#pragma once

class CANOpen;

class RemoteMsgServer : public QHsm {
    public:
        RemoteMsgServer (CANOpen* co_);
        
    protected:
        Q_STATE_DECL(initial);
        Q_STATE_DECL(idle);
        Q_STATE_DECL(busy);
        
    private:
        CANOpen* co;
		QEQueue requestQueue;
		QEvt const* requestQSto[10]; 
};