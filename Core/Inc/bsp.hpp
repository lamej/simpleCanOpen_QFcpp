//****************************************************************************
// File   : bsp.hpp
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

#include <vector>
#include "sTimer.hpp"

using namespace QP;
extern QP::QActive *the_Ticker0;

extern const char *ROM_Version[];

#define FILTER_SIZE (3)  // for digital input

#define TIME_BASE       5            /*..... each tick time after 5ms .....*/
#if (TIME_BASE > 5)
    #error "TIME_BASE must be less than 5, else you must change 5 / TIME_BASE in program "
#endif

class BSP {
    private: 
        static BSP *instance;
        BSP (void) {}
 
    public:
        void sTimerAdd (STimeEvt* timer) {
            sTimeEvtList.push_back(timer);
        }
        
        static BSP* getInstance(void) {
            if (instance == nullptr) {
                instance = new BSP();
            }
            return instance;
        }
        
    public:       
        std::vector<STimeEvt* > sTimeEvtList;
        
    private:
        
};

struct CANMsg { 
    uint32_t id;
    uint32_t dlc;
    uint32_t rtr;
    uint8_t  data[8];
};

enum eCPUStatus {
    CPU_NORMAL_RESET = 0,
    CPU_RESET_BY_WWDG
};

enum {
    MASTER_ID_ = 0x00,
    EXT_CARD1CAB_ID_,  
    EXT_CARD2CAB_ID_,   
    REMOTE_CONTROL_ID_,
    DISPLAY_ID_,
    DUPLEX_MASTER_ID_,
    DUPLEX_SLAVE_ID_,
    VOICE_PLAYER_ID_,
    EXT_CARD1PAL_ID_,    
    EXT_CARD2PAL_ID_,	 
    RFID_READER_ID_,                                        
    MB_2_SERIAL16_ID_,             
    MAX_ID_
};

class ipcEvt : public QEvt {
    public:
        uint16_t value;
        uint16_t param1;
        uint16_t param2;
        uint8_t  attrib;
};

class TPDO;
class RPDO;
class CANOpenEvt : public QEvt {
    public:
                                                   /*..... CAN messages .....*/
        CAN_TxHeaderTypeDef TxMessage;
        uint32_t cob_id_;
        uint8_t  frame_type_;
        uint8_t  frame_format_;
        uint8_t  length_;
__attribute__((aligned(4)))
        uint8_t  buffer[9];
                                                  /*..... PDO parameters .....*/
        TPDO     *tpdo_;              /*..... process data object number .....*/
        RPDO     *rpdo_;
};

enum AX71V2Signals {
                                               /*..... keyboard signals .....*/
    TIME_TICK_SIG = Q_USER_SIG,
    LEDSys_TIMING_SIG,
    KEY_PRESSED_SIG,
    KEY_PRESSED_UP_SIG,
    KEY_PRESSED_DOWN_SIG,
    KEY_PRESSED_VALID_SIG,
    KEY_PRESSED_ESC_SIG,
                                                      /*..... PDO SIGNAL .....*/
    PDO_INIT_SIG,                                                     
    RPDO_RC_SIG,                     /*..... key_id provient du console ......*/
    TPDO_RC_SIG,    /*..... console de programmation: message à afficher .....*/
    TPDO_DSPLY_SIG,            /*..... donnée pour l'afficheur matriciel .....*/
    TPDO_AS300_SIG,      /*..... données envoyées au synthétiseur vocale .....*/
    CANOPEN_TX_SIG,
    CANOPEN_NOTIFY_SIG,
    ADC_ON_COMPLETE_SIG,                /*..... données dispo sur le ADC .....*/
    ADC_MVL_LOW_SIG,                      /*..... main Voltage Level Low .....*/
    ADC_MVL_HIGH_SIG,                    /*..... main Voltage Level High .....*/

                                                    /* device network signals */
    DATA_ON_CAN0_RECEIVED_SIG,
    ON_CAN0_TX_COMPLETE_SIG,
    TRANSMIT_REQUEST_SIG,
    HEARTBEAT_SIG,
    HEARTBEAT_FAULT_SIG,

                                              /*..... automatic leveling .....*/
    AUTO_LEVELING_OFF_SIG,
    AUTO_LEVELING_ON_SIG,

    TPDO1_DPLX_SIG,
    TPDO2_DPLX_SIG,
    TPDO3_DPLX_SIG,
    TPDO1_FROM_DPLX_SIG,
    TPDO2_FROM_DPLX_SIG,
    TPDO3_FROM_DPLX_SIG,

    LIFT_DELTA_STAR_ON_SIG,                      /* démarrage étoile triangle */
    LIFT_DELTA_STAR_OFF_SIG,                     /* démarrage étoile triangle */
    LIFT_ISO_NIVELAGE_ACTIVATE_SIG,        /* mettre en marche l'iso nivelage */
    LIFT_ISO_NIVELAGE_CANCEL_SIG,                   /* arrêter l'iso nivelage */

                                   /* definition of the maximum published sig */
    MAX_PUB_SIG,
    /*..... direct post sig .....*/
    TIMEOUT_10MS_SIG,
    TIMEOUT_FILTER_25MS_SIG,
    TIMEOUT_20MS_SIG,
    PARAM_TIMEOUT_SIG,
    PARAM_POLL_TIMEOUT_SIG,
    LIFT_TIMEOUT_SIG,
    LIFT_TIMEOUT_S_SIG,
    LIFT_POLL_TIMEOUT_SIG,
    LIFT_TO_PATINAGE_SIG,
    LIFT_CALL_TIME_BLINK_SIG
};

// registre à décalage pour les afficheurs internes et externes
void SR1_setValSTRB (bool cmd);
void SR1_setValCLK  (bool cmd);
void SR1_setValDATA (bool cmd);

// registre à décalage pour les lumineux d'appels
void SR2_setValSTRB (bool cmd);
void SR2_setValCLK  (bool cmd);
void SR2_setValDATA (bool cmd);

// lire les entrées des appels
bool E01_readVal (void);
bool E02_readVal (void);
bool E03_readVal (void);
bool E04_readVal (void);
bool E05_readVal (void);
bool E06_readVal (void);
bool E07_readVal (void);
bool E08_readVal (void);
bool E09_readVal (void);
bool E10_readVal (void);
bool E11_readVal (void);
bool E12_readVal (void);
bool E13_readVal (void);
bool E14_readVal (void);
bool E15_readVal (void);
bool E16_readVal (void);

// commande des portes
void doorClose_  (bool cmd);
void door1Open_  (bool cmd);
void door2Open_  (bool cmd);

// commande afficheurs externe
void G2_writeVal (bool cmd);

// digital Input/Output
void OVL_writeVal (bool cmd);
void FL_writeVal  (bool cmd);
bool OVL_readVal  (void);
bool FR_readVal   (void);
bool FL_readVal   (void);
bool PCL_readVal  (void);

// PULL UP, GNG , FM, FD and EC
void pullUP_writeVal (bool cmd);
void fm_writeVal     (bool cmd);
void fd_writeVal     (bool cmd);
void gng_writeVal    (bool cmd);
void ec_writeVal     (bool cmd);



extern BSP* bspInstance;