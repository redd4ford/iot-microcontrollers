/*******************************************************************************
* File Name: t_counter_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "t_counter.h"

static t_counter_BACKUP_STRUCT t_counter_backup;


/*******************************************************************************
* Function Name: t_counter_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void t_counter_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: t_counter_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void t_counter_Sleep(void)
{
    if(0u != (t_counter_BLOCK_CONTROL_REG & t_counter_MASK))
    {
        t_counter_backup.enableState = 1u;
    }
    else
    {
        t_counter_backup.enableState = 0u;
    }

    t_counter_Stop();
    t_counter_SaveConfig();
}


/*******************************************************************************
* Function Name: t_counter_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void t_counter_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: t_counter_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void t_counter_Wakeup(void)
{
    t_counter_RestoreConfig();

    if(0u != t_counter_backup.enableState)
    {
        t_counter_Enable();
    }
}


/* [] END OF FILE */
