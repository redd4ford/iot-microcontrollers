/*******************************************************************************
* File Name: b_encoder.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_b_encoder_ALIASES_H) /* Pins b_encoder_ALIASES_H */
#define CY_PINS_b_encoder_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define b_encoder_0			(b_encoder__0__PC)
#define b_encoder_0_PS		(b_encoder__0__PS)
#define b_encoder_0_PC		(b_encoder__0__PC)
#define b_encoder_0_DR		(b_encoder__0__DR)
#define b_encoder_0_SHIFT	(b_encoder__0__SHIFT)
#define b_encoder_0_INTR	((uint16)((uint16)0x0003u << (b_encoder__0__SHIFT*2u)))

#define b_encoder_INTR_ALL	 ((uint16)(b_encoder_0_INTR))


#endif /* End Pins b_encoder_ALIASES_H */


/* [] END OF FILE */
