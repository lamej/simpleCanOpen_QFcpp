//****************************************************************************
// File   : bsp_it.cpp
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
#include "Applic_OD.hpp"
#include "ApplicCore.hpp"


static size_t pbCounter = 0;


extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern CAN_HandleTypeDef hcan;

CAN_FilterTypeDef sFilterConfig;

extern "C" {
    void HAL_IncTick(void) {
        uwTick++;
    }
}

extern "C" {
    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        if (htim == &htim7) {  // fired each 1ms
            static QEvt const tickEvt = {TIME_TICK_SIG , 0, 0 };
            QK_ISR_ENTRY();             /* inform QK about entering an ISR */
            the_Ticker0->POST(0, 0); // post a don't-care event to Ticker0    
            QF::PUBLISH(&tickEvt, &l_SysTick_Handler); // publish to subscribers
            QK_ISR_EXIT(); 
        }
        if (htim == &htim6) {  // fired each 1ms
            for (auto timer : bspInstance->sTimeEvtList) {
                if (timer != nullptr) {
                    timer->tick();
                }
            }
        }
    }
}

/*..........................................................................*/
void Q_onAssert(char const *module, int loc) {
    /*
    * NOTE: add here your application-specific error handling
    */
     volatile char data[20];
     for(size_t i = 0; i < 20; ++i) {
         data[i] = *(module + i);
     }
     static int   loc_tmp = loc;
//    (void)module;
//    (void)loc;
//    QS_ASSERTION(module, loc, (uint32_t)10000U); /* report assertion to QS */
    //globalErrors = ERROR_TRACE | Q_ASSERT_ERROR;
    NVIC_SystemReset();
}

//............................................................................
void QK::onIdle(void) {

    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M4 MCU.
    //
    __WFI(); // Wait-For-Interrupt
}

/* QF callbacks ============================================================*/
void QF::onStartup(void) {
    QF_INT_DISABLE();

    sFilterConfig.FilterBank       = 0;
    sFilterConfig.FilterMode       = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale      = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh     = 0x0000;
    sFilterConfig.FilterIdLow      = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow  = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation     = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        /* Filter configuration Error */
        Error_Handler();
    }
    // Start CAN
    if (HAL_CAN_Start(&hcan) != HAL_OK){
        /* Start Error */
        Error_Handler();
    }
    // Enable notifications
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
    {
        /* Notification Error */
        Error_Handler();
    } 

    //    Start Timers
    if (HAL_TIM_Base_Start_IT(&htim6) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }
    if (HAL_TIM_Base_Start_IT(&htim7) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }
    QF_INT_ENABLE();
}

/**
  * @brief  Transmission  complete callback in non blocking mode 
  * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
extern "C" {
    void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
    {
        CANOpenEvt *pe;
        CAN_RxHeaderTypeDef RxHeader;
        CANMsg rxMsg;
        QK_ISR_ENTRY();             /* inform QK about entering an ISR */

        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, rxMsg.data);
        rxMsg.dlc = RxHeader.DLC;
        rxMsg.id  = RxHeader.StdId;
          
        pe = Q_NEW(CANOpenEvt, DATA_ON_CAN0_RECEIVED_SIG);
        pe->length_ = RxHeader.DLC;   
        pe->cob_id_ = RxHeader.StdId;
        for (uint8_t k = 0; k < pe->length_; k++) {
            pe->buffer[k] = rxMsg.data[k];
        }
        QF::PUBLISH((QEvt *)pe, &dummy);
        pbCounter++;
        QK_ISR_EXIT();              /* inform QK about exiting an ISR */
    }

    void HAL_CAN_TxMailbox0CompleteCallback (CAN_HandleTypeDef *hcan) 
    {
        ipcEvt* pe;

        /* Prevent unused argument(s) compilation warning */
        UNUSED(hcan);
        QK_ISR_ENTRY();             /* inform QK about entering an ISR */
        pe = Q_NEW(ipcEvt, ON_CAN0_TX_COMPLETE_SIG);
        QF::PUBLISH((QEvt *)pe, &dummy);
        QK_ISR_EXIT();              /* inform QK about exiting an ISR */
    }
    void HAL_CAN_TxMailbox1CompleteCallback (CAN_HandleTypeDef *hcan) 
    {
        ipcEvt* pe;
        
        /* Prevent unused argument(s) compilation warning */
        UNUSED(hcan);
        QK_ISR_ENTRY();             /* inform QK about entering an ISR */
        pe = Q_NEW(ipcEvt, ON_CAN0_TX_COMPLETE_SIG);
        QF::PUBLISH((QEvt *)pe, &dummy);
        QK_ISR_EXIT();              /* inform QK about exiting an ISR */
    }
    void HAL_CAN_TxMailbox2CompleteCallback (CAN_HandleTypeDef *hcan) 
    {
        ipcEvt* pe;
        /* Prevent unused argument(s) compilation warning */
        UNUSED(hcan);
        QK_ISR_ENTRY();             /* inform QK about entering an ISR */
        pe = Q_NEW(ipcEvt, ON_CAN0_TX_COMPLETE_SIG);
        QF::PUBLISH((QEvt *)pe, &dummy);
        QK_ISR_EXIT();              /* inform QK about exiting an ISR */
    }
}
/*..........................................................................*/
void QK_onIdle(void) {
    /* Put the CPU and peripherals to the low-power mode.
    * you might need to customize the clock management for your application,
    * see the datasheet for your particular Cortex-M MCU.
    */
    /* !!!CAUTION!!!
    * The WFI instruction stops the CPU clock, which unfortunately disables
    * the JTAG port, so the ST-Link debugger can no longer connect to the
    * board. For that reason, the call to __WFI() has to be used with CAUTION.
    *
    * NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
    * reset the board, then connect with ST-Link Utilities and erase the part.
    * The trick with BOOT(0) is that it gets the part to run the System Loader
    * instead of your broken code. When done disconnect BOOT0, and start over.
    */
    //__WFI(); /* Wait-For-Interrupt */
}