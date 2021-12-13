/*******************************************************************************
* File Name: c_register_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "c_register.h"

/* Check for removal by optimization */
#if !defined(c_register_Sync_ctrl_reg__REMOVED)

static c_register_BACKUP_STRUCT  c_register_backup = {0u};

    
/*******************************************************************************
* Function Name: c_register_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void c_register_SaveConfig(void) 
{
    c_register_backup.controlState = c_register_Control;
}


/*******************************************************************************
* Function Name: c_register_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void c_register_RestoreConfig(void) 
{
     c_register_Control = c_register_backup.controlState;
}


/*******************************************************************************
* Function Name: c_register_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void c_register_Sleep(void) 
{
    c_register_SaveConfig();
}


/*******************************************************************************
* Function Name: c_register_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void c_register_Wakeup(void)  
{
    c_register_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
