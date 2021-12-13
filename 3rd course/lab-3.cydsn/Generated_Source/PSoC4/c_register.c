/*******************************************************************************
* File Name: c_register.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "c_register.h"

/* Check for removal by optimization */
#if !defined(c_register_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: c_register_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void c_register_Write(uint8 control) 
{
    c_register_Control = control;
}


/*******************************************************************************
* Function Name: c_register_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 c_register_Read(void) 
{
    return c_register_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
