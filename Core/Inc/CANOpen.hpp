//****************************************************************************
// File   : CANOpen.hpp
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

#include <memory>
#include <vector>
#include "remoteMsgServer.hpp"
#include "tpdos.hpp"
#include "rpdos.hpp"
#include "crypto.hpp"  // algorithme SpritzBC

class CANOpen : public QActive {
    public:
    CANOpen (uint32_t id);
    RemoteMsgServer* msgServer;
    void notify (TPDO *pdo);
    
    protected: 
        Q_STATE_DECL(initial);
        Q_STATE_DECL(run);
        
    private:
                std::vector<uint8_t> crypto_key = crypto_key_iv;
		QTimeEvt  timeEvt__;                           /*..... timeout timer .....*/
		uint8_t   qs_dummy;
		uint32_t  time_stamp;
		
		void transmit (TPDO *pdo);
		void processTPDOs (void);
		void processRPDOs (const QEvt *e);
		const uint32_t cob_id;
};

class PDO_ComParam {
    public:
    PDO_ComParam(void) {}
};

class PDO_MapParam {
    public:
    PDO_MapParam(void) {}
};

class IPDO {
    public:
    IPDO (void) {}
    
    protected:
    PDO_ComParam *pdoComParam;
    PDO_MapParam *pdoMapParam;
};
