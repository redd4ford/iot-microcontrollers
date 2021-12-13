/*******************************************************************************
* File Name: LCD_char_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_char.h"


static LCD_char_BACKUP_STRUCT LCD_char_backup;


/*******************************************************************************
* Function Name: LCD_char_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_char_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_char_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_char_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_char_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_char_Sleep(void) 
{
    LCD_char_backup.enableState = LCD_char_enableState;
    LCD_char_SaveConfig();
    LCD_char_Stop();
}


/*******************************************************************************
* Function Name: LCD_char_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCD_char_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_char_Wakeup(void) 
{
    LCD_char_RestoreConfig();

    if(LCD_char_backup.enableState == 1u)
    {
        LCD_char_Enable();
    }
}


/* [] END OF FILE */
