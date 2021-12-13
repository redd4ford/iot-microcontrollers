/*******************************************************************************
* File Name: b_encoder_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_b_encoder_isr_H)
#define CY_ISR_b_encoder_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void b_encoder_isr_Start(void);
void b_encoder_isr_StartEx(cyisraddress address);
void b_encoder_isr_Stop(void);

CY_ISR_PROTO(b_encoder_isr_Interrupt);

void b_encoder_isr_SetVector(cyisraddress address);
cyisraddress b_encoder_isr_GetVector(void);

void b_encoder_isr_SetPriority(uint8 priority);
uint8 b_encoder_isr_GetPriority(void);

void b_encoder_isr_Enable(void);
uint8 b_encoder_isr_GetState(void);
void b_encoder_isr_Disable(void);

void b_encoder_isr_SetPending(void);
void b_encoder_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the b_encoder_isr ISR. */
#define b_encoder_isr_INTC_VECTOR            ((reg32 *) b_encoder_isr__INTC_VECT)

/* Address of the b_encoder_isr ISR priority. */
#define b_encoder_isr_INTC_PRIOR             ((reg32 *) b_encoder_isr__INTC_PRIOR_REG)

/* Priority of the b_encoder_isr interrupt. */
#define b_encoder_isr_INTC_PRIOR_NUMBER      b_encoder_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable b_encoder_isr interrupt. */
#define b_encoder_isr_INTC_SET_EN            ((reg32 *) b_encoder_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the b_encoder_isr interrupt. */
#define b_encoder_isr_INTC_CLR_EN            ((reg32 *) b_encoder_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the b_encoder_isr interrupt state to pending. */
#define b_encoder_isr_INTC_SET_PD            ((reg32 *) b_encoder_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the b_encoder_isr interrupt. */
#define b_encoder_isr_INTC_CLR_PD            ((reg32 *) b_encoder_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_b_encoder_isr_H */


/* [] END OF FILE */
