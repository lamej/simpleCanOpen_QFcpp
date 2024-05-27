//****************************************************************************
// File   : bsp.cpp
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
#include "qpcpp.hpp"
#include "main.h"
#include "bsp.hpp"

const char *ROM_Version[] = {
    "ROM Version xxxx\n",
    "29/10/2021 -V2.0"
};

BSP* BSP::instance;
BSP* bspInstance = BSP::getInstance();


// registre à décalage pour les afficheurs internes et externes
void SR1_setValSTRB (bool cmd) {
    HAL_GPIO_WritePin(STRB1_GPIO_Port, STRB1_Pin, static_cast<GPIO_PinState>(cmd));
}
void SR1_setValCLK  (bool cmd) {
    HAL_GPIO_WritePin(CLK1_GPIO_Port, CLK1_Pin, static_cast<GPIO_PinState>(cmd));
}
void SR1_setValDATA (bool cmd) {
    HAL_GPIO_WritePin(DATA1_GPIO_Port, DATA1_Pin, static_cast<GPIO_PinState>(cmd));
}

// registre à décalage pour les lumineux d'appels
void SR2_setValSTRB (bool cmd) {
    HAL_GPIO_WritePin(STRB2_GPIO_Port, STRB2_Pin, static_cast<GPIO_PinState>(cmd));
}
void SR2_setValCLK  (bool cmd) {
    HAL_GPIO_WritePin(CLK2_GPIO_Port, CLK2_Pin, static_cast<GPIO_PinState>(cmd));
}
void SR2_setValDATA (bool cmd) {
    HAL_GPIO_WritePin(DATA2_GPIO_Port, DATA2_Pin, static_cast<GPIO_PinState>(cmd));
}

// lire les entrées des appels
bool E01_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E01_GPIO_Port, E01_Pin));
}
bool E02_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E02_GPIO_Port, E02_Pin));
}
bool E03_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E03_GPIO_Port, E03_Pin));
}
bool E04_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E04_GPIO_Port, E04_Pin));
}
bool E05_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E05_GPIO_Port, E05_Pin));
}
bool E06_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E06_GPIO_Port, E06_Pin));
}
bool E07_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E07_GPIO_Port, E07_Pin));
}
bool E08_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E08_GPIO_Port, E08_Pin));
}
bool E09_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E09_GPIO_Port, E09_Pin));
}
bool E10_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E10_GPIO_Port, E10_Pin));
}
bool E11_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E11_GPIO_Port, E11_Pin));
}
bool E12_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E12_GPIO_Port, E12_Pin));
}
bool E13_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E13_GPIO_Port, E13_Pin));
}
bool E14_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E14_GPIO_Port, E14_Pin));
}
bool E15_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E15_GPIO_Port, E15_Pin));
}
bool E16_readVal (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(E16_GPIO_Port, E16_Pin));
}

// commande des portes
void doorClose_ (bool cmd) {
    HAL_GPIO_WritePin(SFP_GPIO_Port, SFP_Pin, static_cast<GPIO_PinState>(cmd));
}
void door1Open_  (bool cmd) {
    HAL_GPIO_WritePin(SOP1_GPIO_Port, SOP1_Pin, static_cast<GPIO_PinState>(cmd));
}
void door2Open_  (bool cmd) {
    HAL_GPIO_WritePin(SOP2_GPIO_Port, SOP2_Pin, static_cast<GPIO_PinState>(cmd));
}

// commande afficheurs externe
void G2_writeVal (bool cmd) {
   HAL_GPIO_WritePin(G2_GPIO_Port, G2_Pin, static_cast<GPIO_PinState>(cmd));
}

// digital Input/Output
void OVL_writeVal (bool cmd) {
   HAL_GPIO_WritePin(OVLO_GPIO_Port, OVLO_Pin, static_cast<GPIO_PinState>(cmd));
} 
void FL_writeVal  (bool cmd) {
   HAL_GPIO_WritePin(FLO_GPIO_Port, FLO_Pin, static_cast<GPIO_PinState>(cmd));
}
bool OVL_readVal  (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(OVLI_GPIO_Port, OVLI_Pin));
}
bool FR_readVal   (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(FR_GPIO_Port, FR_Pin));
}
bool FL_readVal   (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(FLI_GPIO_Port, FLI_Pin));
}
bool PCL_readVal  (void) {
    return not static_cast<bool>(HAL_GPIO_ReadPin(PCL_GPIO_Port, PCL_Pin));
}

// PULL UP, GNG , FM , FD and EC
void pullUP_writeVal (bool cmd) {
   HAL_GPIO_WritePin(PULL_UP_GPIO_Port, PULL_UP_Pin, static_cast<GPIO_PinState>(cmd));
}
void fm_writeVal     (bool cmd) {
   HAL_GPIO_WritePin(FM_GPIO_Port, FM_Pin, static_cast<GPIO_PinState>(cmd));
}
void fd_writeVal     (bool cmd) {
   HAL_GPIO_WritePin(FD_GPIO_Port, FD_Pin, static_cast<GPIO_PinState>(cmd));
}
void gng_writeVal    (bool cmd) {
   HAL_GPIO_WritePin(GNG_GPIO_Port, GNG_Pin, static_cast<GPIO_PinState>(cmd));
}
void ec_writeVal    (bool cmd) {
   HAL_GPIO_WritePin(EC_GPIO_Port, EC_Pin, static_cast<GPIO_PinState>(cmd));
}