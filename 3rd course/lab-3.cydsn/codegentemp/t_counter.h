/*******************************************************************************
* File Name: t_counter.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the t_counter
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_t_counter_H)
#define CY_TCPWM_t_counter_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} t_counter_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  t_counter_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define t_counter_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define t_counter_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define t_counter_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define t_counter_QUAD_ENCODING_MODES            (0lu)
#define t_counter_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define t_counter_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define t_counter_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define t_counter_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define t_counter_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define t_counter_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define t_counter_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define t_counter_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define t_counter_TC_RUN_MODE                    (0lu)
#define t_counter_TC_COUNTER_MODE                (0lu)
#define t_counter_TC_COMP_CAP_MODE               (2lu)
#define t_counter_TC_PRESCALER                   (0lu)

/* Signal modes */
#define t_counter_TC_RELOAD_SIGNAL_MODE          (0lu)
#define t_counter_TC_COUNT_SIGNAL_MODE           (3lu)
#define t_counter_TC_START_SIGNAL_MODE           (0lu)
#define t_counter_TC_STOP_SIGNAL_MODE            (0lu)
#define t_counter_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define t_counter_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define t_counter_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define t_counter_TC_START_SIGNAL_PRESENT        (0lu)
#define t_counter_TC_STOP_SIGNAL_PRESENT         (0lu)
#define t_counter_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define t_counter_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define t_counter_PWM_KILL_EVENT                 (0lu)
#define t_counter_PWM_STOP_EVENT                 (0lu)
#define t_counter_PWM_MODE                       (4lu)
#define t_counter_PWM_OUT_N_INVERT               (0lu)
#define t_counter_PWM_OUT_INVERT                 (0lu)
#define t_counter_PWM_ALIGN                      (0lu)
#define t_counter_PWM_RUN_MODE                   (0lu)
#define t_counter_PWM_DEAD_TIME_CYCLE            (0lu)
#define t_counter_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define t_counter_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define t_counter_PWM_COUNT_SIGNAL_MODE          (3lu)
#define t_counter_PWM_START_SIGNAL_MODE          (0lu)
#define t_counter_PWM_STOP_SIGNAL_MODE           (0lu)
#define t_counter_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define t_counter_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define t_counter_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define t_counter_PWM_START_SIGNAL_PRESENT       (0lu)
#define t_counter_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define t_counter_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define t_counter_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define t_counter_TC_PERIOD_VALUE                (1000lu)
#define t_counter_TC_COMPARE_VALUE               (65535lu)
#define t_counter_TC_COMPARE_BUF_VALUE           (65535lu)
#define t_counter_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define t_counter_PWM_PERIOD_VALUE               (65535lu)
#define t_counter_PWM_PERIOD_BUF_VALUE           (65535lu)
#define t_counter_PWM_PERIOD_SWAP                (0lu)
#define t_counter_PWM_COMPARE_VALUE              (65535lu)
#define t_counter_PWM_COMPARE_BUF_VALUE          (65535lu)
#define t_counter_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define t_counter__LEFT 0
#define t_counter__RIGHT 1
#define t_counter__CENTER 2
#define t_counter__ASYMMETRIC 3

#define t_counter__X1 0
#define t_counter__X2 1
#define t_counter__X4 2

#define t_counter__PWM 4
#define t_counter__PWM_DT 5
#define t_counter__PWM_PR 6

#define t_counter__INVERSE 1
#define t_counter__DIRECT 0

#define t_counter__CAPTURE 2
#define t_counter__COMPARE 0

#define t_counter__TRIG_LEVEL 3
#define t_counter__TRIG_RISING 0
#define t_counter__TRIG_FALLING 1
#define t_counter__TRIG_BOTH 2

#define t_counter__INTR_MASK_TC 1
#define t_counter__INTR_MASK_CC_MATCH 2
#define t_counter__INTR_MASK_NONE 0
#define t_counter__INTR_MASK_TC_CC 3

#define t_counter__UNCONFIG 8
#define t_counter__TIMER 1
#define t_counter__QUAD 3
#define t_counter__PWM_SEL 7

#define t_counter__COUNT_UP 0
#define t_counter__COUNT_DOWN 1
#define t_counter__COUNT_UPDOWN0 2
#define t_counter__COUNT_UPDOWN1 3


/* Prescaler */
#define t_counter_PRESCALE_DIVBY1                ((uint32)(0u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY2                ((uint32)(1u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY4                ((uint32)(2u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY8                ((uint32)(3u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY16               ((uint32)(4u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY32               ((uint32)(5u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY64               ((uint32)(6u << t_counter_PRESCALER_SHIFT))
#define t_counter_PRESCALE_DIVBY128              ((uint32)(7u << t_counter_PRESCALER_SHIFT))

/* TCPWM set modes */
#define t_counter_MODE_TIMER_COMPARE             ((uint32)(t_counter__COMPARE         <<  \
                                                                  t_counter_MODE_SHIFT))
#define t_counter_MODE_TIMER_CAPTURE             ((uint32)(t_counter__CAPTURE         <<  \
                                                                  t_counter_MODE_SHIFT))
#define t_counter_MODE_QUAD                      ((uint32)(t_counter__QUAD            <<  \
                                                                  t_counter_MODE_SHIFT))
#define t_counter_MODE_PWM                       ((uint32)(t_counter__PWM             <<  \
                                                                  t_counter_MODE_SHIFT))
#define t_counter_MODE_PWM_DT                    ((uint32)(t_counter__PWM_DT          <<  \
                                                                  t_counter_MODE_SHIFT))
#define t_counter_MODE_PWM_PR                    ((uint32)(t_counter__PWM_PR          <<  \
                                                                  t_counter_MODE_SHIFT))

/* Quad Modes */
#define t_counter_MODE_X1                        ((uint32)(t_counter__X1              <<  \
                                                                  t_counter_QUAD_MODE_SHIFT))
#define t_counter_MODE_X2                        ((uint32)(t_counter__X2              <<  \
                                                                  t_counter_QUAD_MODE_SHIFT))
#define t_counter_MODE_X4                        ((uint32)(t_counter__X4              <<  \
                                                                  t_counter_QUAD_MODE_SHIFT))

/* Counter modes */
#define t_counter_COUNT_UP                       ((uint32)(t_counter__COUNT_UP        <<  \
                                                                  t_counter_UPDOWN_SHIFT))
#define t_counter_COUNT_DOWN                     ((uint32)(t_counter__COUNT_DOWN      <<  \
                                                                  t_counter_UPDOWN_SHIFT))
#define t_counter_COUNT_UPDOWN0                  ((uint32)(t_counter__COUNT_UPDOWN0   <<  \
                                                                  t_counter_UPDOWN_SHIFT))
#define t_counter_COUNT_UPDOWN1                  ((uint32)(t_counter__COUNT_UPDOWN1   <<  \
                                                                  t_counter_UPDOWN_SHIFT))

/* PWM output invert */
#define t_counter_INVERT_LINE                    ((uint32)(t_counter__INVERSE         <<  \
                                                                  t_counter_INV_OUT_SHIFT))
#define t_counter_INVERT_LINE_N                  ((uint32)(t_counter__INVERSE         <<  \
                                                                  t_counter_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define t_counter_TRIG_RISING                    ((uint32)t_counter__TRIG_RISING)
#define t_counter_TRIG_FALLING                   ((uint32)t_counter__TRIG_FALLING)
#define t_counter_TRIG_BOTH                      ((uint32)t_counter__TRIG_BOTH)
#define t_counter_TRIG_LEVEL                     ((uint32)t_counter__TRIG_LEVEL)

/* Interrupt mask */
#define t_counter_INTR_MASK_TC                   ((uint32)t_counter__INTR_MASK_TC)
#define t_counter_INTR_MASK_CC_MATCH             ((uint32)t_counter__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define t_counter_CC_MATCH_SET                   (0x00u)
#define t_counter_CC_MATCH_CLEAR                 (0x01u)
#define t_counter_CC_MATCH_INVERT                (0x02u)
#define t_counter_CC_MATCH_NO_CHANGE             (0x03u)
#define t_counter_OVERLOW_SET                    (0x00u)
#define t_counter_OVERLOW_CLEAR                  (0x04u)
#define t_counter_OVERLOW_INVERT                 (0x08u)
#define t_counter_OVERLOW_NO_CHANGE              (0x0Cu)
#define t_counter_UNDERFLOW_SET                  (0x00u)
#define t_counter_UNDERFLOW_CLEAR                (0x10u)
#define t_counter_UNDERFLOW_INVERT               (0x20u)
#define t_counter_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define t_counter_PWM_MODE_LEFT                  (t_counter_CC_MATCH_CLEAR        |   \
                                                         t_counter_OVERLOW_SET           |   \
                                                         t_counter_UNDERFLOW_NO_CHANGE)
#define t_counter_PWM_MODE_RIGHT                 (t_counter_CC_MATCH_SET          |   \
                                                         t_counter_OVERLOW_NO_CHANGE     |   \
                                                         t_counter_UNDERFLOW_CLEAR)
#define t_counter_PWM_MODE_ASYM                  (t_counter_CC_MATCH_INVERT       |   \
                                                         t_counter_OVERLOW_SET           |   \
                                                         t_counter_UNDERFLOW_CLEAR)

#if (t_counter_CY_TCPWM_V2)
    #if(t_counter_CY_TCPWM_4000)
        #define t_counter_PWM_MODE_CENTER                (t_counter_CC_MATCH_INVERT       |   \
                                                                 t_counter_OVERLOW_NO_CHANGE     |   \
                                                                 t_counter_UNDERFLOW_CLEAR)
    #else
        #define t_counter_PWM_MODE_CENTER                (t_counter_CC_MATCH_INVERT       |   \
                                                                 t_counter_OVERLOW_SET           |   \
                                                                 t_counter_UNDERFLOW_CLEAR)
    #endif /* (t_counter_CY_TCPWM_4000) */
#else
    #define t_counter_PWM_MODE_CENTER                (t_counter_CC_MATCH_INVERT       |   \
                                                             t_counter_OVERLOW_NO_CHANGE     |   \
                                                             t_counter_UNDERFLOW_CLEAR)
#endif /* (t_counter_CY_TCPWM_NEW) */

/* Command operations without condition */
#define t_counter_CMD_CAPTURE                    (0u)
#define t_counter_CMD_RELOAD                     (8u)
#define t_counter_CMD_STOP                       (16u)
#define t_counter_CMD_START                      (24u)

/* Status */
#define t_counter_STATUS_DOWN                    (1u)
#define t_counter_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   t_counter_Init(void);
void   t_counter_Enable(void);
void   t_counter_Start(void);
void   t_counter_Stop(void);

void   t_counter_SetMode(uint32 mode);
void   t_counter_SetCounterMode(uint32 counterMode);
void   t_counter_SetPWMMode(uint32 modeMask);
void   t_counter_SetQDMode(uint32 qdMode);

void   t_counter_SetPrescaler(uint32 prescaler);
void   t_counter_TriggerCommand(uint32 mask, uint32 command);
void   t_counter_SetOneShot(uint32 oneShotEnable);
uint32 t_counter_ReadStatus(void);

void   t_counter_SetPWMSyncKill(uint32 syncKillEnable);
void   t_counter_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   t_counter_SetPWMDeadTime(uint32 deadTime);
void   t_counter_SetPWMInvert(uint32 mask);

void   t_counter_SetInterruptMode(uint32 interruptMask);
uint32 t_counter_GetInterruptSourceMasked(void);
uint32 t_counter_GetInterruptSource(void);
void   t_counter_ClearInterrupt(uint32 interruptMask);
void   t_counter_SetInterrupt(uint32 interruptMask);

void   t_counter_WriteCounter(uint32 count);
uint32 t_counter_ReadCounter(void);

uint32 t_counter_ReadCapture(void);
uint32 t_counter_ReadCaptureBuf(void);

void   t_counter_WritePeriod(uint32 period);
uint32 t_counter_ReadPeriod(void);
void   t_counter_WritePeriodBuf(uint32 periodBuf);
uint32 t_counter_ReadPeriodBuf(void);

void   t_counter_WriteCompare(uint32 compare);
uint32 t_counter_ReadCompare(void);
void   t_counter_WriteCompareBuf(uint32 compareBuf);
uint32 t_counter_ReadCompareBuf(void);

void   t_counter_SetPeriodSwap(uint32 swapEnable);
void   t_counter_SetCompareSwap(uint32 swapEnable);

void   t_counter_SetCaptureMode(uint32 triggerMode);
void   t_counter_SetReloadMode(uint32 triggerMode);
void   t_counter_SetStartMode(uint32 triggerMode);
void   t_counter_SetStopMode(uint32 triggerMode);
void   t_counter_SetCountMode(uint32 triggerMode);

void   t_counter_SaveConfig(void);
void   t_counter_RestoreConfig(void);
void   t_counter_Sleep(void);
void   t_counter_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define t_counter_BLOCK_CONTROL_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define t_counter_BLOCK_CONTROL_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define t_counter_COMMAND_REG                    (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define t_counter_COMMAND_PTR                    ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define t_counter_INTRRUPT_CAUSE_REG             (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define t_counter_INTRRUPT_CAUSE_PTR             ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define t_counter_CONTROL_REG                    (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__CTRL )
#define t_counter_CONTROL_PTR                    ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__CTRL )
#define t_counter_STATUS_REG                     (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__STATUS )
#define t_counter_STATUS_PTR                     ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__STATUS )
#define t_counter_COUNTER_REG                    (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__COUNTER )
#define t_counter_COUNTER_PTR                    ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__COUNTER )
#define t_counter_COMP_CAP_REG                   (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__CC )
#define t_counter_COMP_CAP_PTR                   ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__CC )
#define t_counter_COMP_CAP_BUF_REG               (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__CC_BUFF )
#define t_counter_COMP_CAP_BUF_PTR               ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__CC_BUFF )
#define t_counter_PERIOD_REG                     (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__PERIOD )
#define t_counter_PERIOD_PTR                     ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__PERIOD )
#define t_counter_PERIOD_BUF_REG                 (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define t_counter_PERIOD_BUF_PTR                 ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define t_counter_TRIG_CONTROL0_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define t_counter_TRIG_CONTROL0_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define t_counter_TRIG_CONTROL1_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define t_counter_TRIG_CONTROL1_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define t_counter_TRIG_CONTROL2_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define t_counter_TRIG_CONTROL2_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define t_counter_INTERRUPT_REQ_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR )
#define t_counter_INTERRUPT_REQ_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR )
#define t_counter_INTERRUPT_SET_REG              (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_SET )
#define t_counter_INTERRUPT_SET_PTR              ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_SET )
#define t_counter_INTERRUPT_MASK_REG             (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_MASK )
#define t_counter_INTERRUPT_MASK_PTR             ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_MASK )
#define t_counter_INTERRUPT_MASKED_REG           (*(reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_MASKED )
#define t_counter_INTERRUPT_MASKED_PTR           ( (reg32 *) t_counter_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define t_counter_MASK                           ((uint32)t_counter_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define t_counter_RELOAD_CC_SHIFT                (0u)
#define t_counter_RELOAD_PERIOD_SHIFT            (1u)
#define t_counter_PWM_SYNC_KILL_SHIFT            (2u)
#define t_counter_PWM_STOP_KILL_SHIFT            (3u)
#define t_counter_PRESCALER_SHIFT                (8u)
#define t_counter_UPDOWN_SHIFT                   (16u)
#define t_counter_ONESHOT_SHIFT                  (18u)
#define t_counter_QUAD_MODE_SHIFT                (20u)
#define t_counter_INV_OUT_SHIFT                  (20u)
#define t_counter_INV_COMPL_OUT_SHIFT            (21u)
#define t_counter_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define t_counter_RELOAD_CC_MASK                 ((uint32)(t_counter_1BIT_MASK        <<  \
                                                                            t_counter_RELOAD_CC_SHIFT))
#define t_counter_RELOAD_PERIOD_MASK             ((uint32)(t_counter_1BIT_MASK        <<  \
                                                                            t_counter_RELOAD_PERIOD_SHIFT))
#define t_counter_PWM_SYNC_KILL_MASK             ((uint32)(t_counter_1BIT_MASK        <<  \
                                                                            t_counter_PWM_SYNC_KILL_SHIFT))
#define t_counter_PWM_STOP_KILL_MASK             ((uint32)(t_counter_1BIT_MASK        <<  \
                                                                            t_counter_PWM_STOP_KILL_SHIFT))
#define t_counter_PRESCALER_MASK                 ((uint32)(t_counter_8BIT_MASK        <<  \
                                                                            t_counter_PRESCALER_SHIFT))
#define t_counter_UPDOWN_MASK                    ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                            t_counter_UPDOWN_SHIFT))
#define t_counter_ONESHOT_MASK                   ((uint32)(t_counter_1BIT_MASK        <<  \
                                                                            t_counter_ONESHOT_SHIFT))
#define t_counter_QUAD_MODE_MASK                 ((uint32)(t_counter_3BIT_MASK        <<  \
                                                                            t_counter_QUAD_MODE_SHIFT))
#define t_counter_INV_OUT_MASK                   ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                            t_counter_INV_OUT_SHIFT))
#define t_counter_MODE_MASK                      ((uint32)(t_counter_3BIT_MASK        <<  \
                                                                            t_counter_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define t_counter_CAPTURE_SHIFT                  (0u)
#define t_counter_COUNT_SHIFT                    (2u)
#define t_counter_RELOAD_SHIFT                   (4u)
#define t_counter_STOP_SHIFT                     (6u)
#define t_counter_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define t_counter_CAPTURE_MASK                   ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                  t_counter_CAPTURE_SHIFT))
#define t_counter_COUNT_MASK                     ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                  t_counter_COUNT_SHIFT))
#define t_counter_RELOAD_MASK                    ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                  t_counter_RELOAD_SHIFT))
#define t_counter_STOP_MASK                      ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                  t_counter_STOP_SHIFT))
#define t_counter_START_MASK                     ((uint32)(t_counter_2BIT_MASK        <<  \
                                                                  t_counter_START_SHIFT))

/* MASK */
#define t_counter_1BIT_MASK                      ((uint32)0x01u)
#define t_counter_2BIT_MASK                      ((uint32)0x03u)
#define t_counter_3BIT_MASK                      ((uint32)0x07u)
#define t_counter_6BIT_MASK                      ((uint32)0x3Fu)
#define t_counter_8BIT_MASK                      ((uint32)0xFFu)
#define t_counter_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define t_counter_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define t_counter_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(t_counter_QUAD_ENCODING_MODES     << t_counter_QUAD_MODE_SHIFT))       |\
         ((uint32)(t_counter_CONFIG                  << t_counter_MODE_SHIFT)))

#define t_counter_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(t_counter_PWM_STOP_EVENT          << t_counter_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(t_counter_PWM_OUT_INVERT          << t_counter_INV_OUT_SHIFT))         |\
         ((uint32)(t_counter_PWM_OUT_N_INVERT        << t_counter_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(t_counter_PWM_MODE                << t_counter_MODE_SHIFT)))

#define t_counter_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(t_counter_PWM_RUN_MODE         << t_counter_ONESHOT_SHIFT))
            
#define t_counter_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(t_counter_PWM_ALIGN            << t_counter_UPDOWN_SHIFT))

#define t_counter_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(t_counter_PWM_KILL_EVENT      << t_counter_PWM_SYNC_KILL_SHIFT))

#define t_counter_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(t_counter_PWM_DEAD_TIME_CYCLE  << t_counter_PRESCALER_SHIFT))

#define t_counter_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(t_counter_PWM_PRESCALER        << t_counter_PRESCALER_SHIFT))

#define t_counter_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(t_counter_TC_PRESCALER            << t_counter_PRESCALER_SHIFT))       |\
         ((uint32)(t_counter_TC_COUNTER_MODE         << t_counter_UPDOWN_SHIFT))          |\
         ((uint32)(t_counter_TC_RUN_MODE             << t_counter_ONESHOT_SHIFT))         |\
         ((uint32)(t_counter_TC_COMP_CAP_MODE        << t_counter_MODE_SHIFT)))
        
#define t_counter_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(t_counter_QUAD_PHIA_SIGNAL_MODE   << t_counter_COUNT_SHIFT))           |\
         ((uint32)(t_counter_QUAD_INDEX_SIGNAL_MODE  << t_counter_RELOAD_SHIFT))          |\
         ((uint32)(t_counter_QUAD_STOP_SIGNAL_MODE   << t_counter_STOP_SHIFT))            |\
         ((uint32)(t_counter_QUAD_PHIB_SIGNAL_MODE   << t_counter_START_SHIFT)))

#define t_counter_PWM_SIGNALS_MODES                                                              \
        (((uint32)(t_counter_PWM_SWITCH_SIGNAL_MODE  << t_counter_CAPTURE_SHIFT))         |\
         ((uint32)(t_counter_PWM_COUNT_SIGNAL_MODE   << t_counter_COUNT_SHIFT))           |\
         ((uint32)(t_counter_PWM_RELOAD_SIGNAL_MODE  << t_counter_RELOAD_SHIFT))          |\
         ((uint32)(t_counter_PWM_STOP_SIGNAL_MODE    << t_counter_STOP_SHIFT))            |\
         ((uint32)(t_counter_PWM_START_SIGNAL_MODE   << t_counter_START_SHIFT)))

#define t_counter_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(t_counter_TC_CAPTURE_SIGNAL_MODE  << t_counter_CAPTURE_SHIFT))         |\
         ((uint32)(t_counter_TC_COUNT_SIGNAL_MODE    << t_counter_COUNT_SHIFT))           |\
         ((uint32)(t_counter_TC_RELOAD_SIGNAL_MODE   << t_counter_RELOAD_SHIFT))          |\
         ((uint32)(t_counter_TC_STOP_SIGNAL_MODE     << t_counter_STOP_SHIFT))            |\
         ((uint32)(t_counter_TC_START_SIGNAL_MODE    << t_counter_START_SHIFT)))
        
#define t_counter_TIMER_UPDOWN_CNT_USED                                                          \
                ((t_counter__COUNT_UPDOWN0 == t_counter_TC_COUNTER_MODE)                  ||\
                 (t_counter__COUNT_UPDOWN1 == t_counter_TC_COUNTER_MODE))

#define t_counter_PWM_UPDOWN_CNT_USED                                                            \
                ((t_counter__CENTER == t_counter_PWM_ALIGN)                               ||\
                 (t_counter__ASYMMETRIC == t_counter_PWM_ALIGN))               
        
#define t_counter_PWM_PR_INIT_VALUE              (1u)
#define t_counter_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_t_counter_H */

/* [] END OF FILE */
