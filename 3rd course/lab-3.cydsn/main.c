#include "project.h"

#define RED_COLOR 0b001
#define YELLOW_COLOR 0b010
#define GREEN_COLOR 0b100
#define NO_COLOR 0b000

#define DELAY (3 + 3) * 1000

#define LIGHTS_BAR "RED YELLOW GREEN"

#define SET_RED_COLOR    "SET RED TIME:   "
#define SET_YELLOW_COLOR "SET YELLOW TIME:"
#define SET_GREEN_COLOR  "SET GREEN TIME: "

#define EMPTY_LINE "                "
#define TIME       "TIME=           "

#define POSITION_RED_TIME 0
#define POSITION_YELLOW_TIME 4
#define POSITION_GREEN_TIME 11
#define POSITITON_SET_TIME 5

uint8_t counter = 0;
CYBIT algorithm = 0;

uint8_t red_color_time;
uint8_t yellow_color_time;
uint8_t green_color_time;

uint8_t display_mode = 0;
CYBIT mode_has_changed = 0;

void first_algo_green(const uint8_t* pShift);
void second_algo_green(const uint8_t* pShift);
void first_algo_red(const uint8_t* pShift);
void second_algo_red(const uint8_t* pShift);

struct DisplayCounter
{
    uint8_t position, counter;
};

struct DisplayCounter display_counter = {0, 0};

CY_ISR(t_isr_interrupt)
{
    if (counter >= 20) 
    {
        counter = 0;
    } 
    
    uint8 shift;
    if (algorithm)
    {
        if (counter < green_color_time + yellow_color_time)
        {
            shift = 0;
            second_algo_green(&shift);
        }
        else 
        {
            shift = green_color_time + yellow_color_time;
            second_algo_red(&shift);
        }
    }
    else
    {
        if (counter < red_color_time + yellow_color_time)
        {
            shift = 0;
            first_algo_red(&shift);
        }
        else 
        {
            shift = red_color_time + yellow_color_time;
            first_algo_green(&shift);
        }
    }
    counter++;
    t_counter_ClearInterrupt(t_counter_INTR_MASK_TC);
}

CY_ISR(b_isr_interrupt)
{
    algorithm = algorithm ? 0 : 1;
    counter = 0;
    button_ClearInterrupt();
}

CY_ISR(b_encoder_isr_interrupt)
{
    if (display_mode >= 3)
    {
        display_mode = 0;
    }
    else
    {
        display_mode++;
    }
    mode_has_changed = 1;
    b_encoder_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable;
    
    red_color_time = 8;
    yellow_color_time = 2;
    green_color_time = 8;
    
    display_counter.counter = red_color_time;
    display_counter.position = POSITION_RED_TIME;
    
    t_counter_Start();
    t_isr_StartEx(t_isr_interrupt);
    b_isr_StartEx(b_isr_interrupt);
    b_encoder_isr_StartEx(b_encoder_isr_interrupt);
    
    QuadDec_Start();
    
    LCD_char_Start();
    LCD_char_ClearDisplay();
    LCD_char_Position(0, 5);
    LCD_char_PrintString("Vika Yehorova");
    LCD_char_Position(1, 2);
    LCD_char_PrintString("IoT-2019");
    CyDelay(DELAY);
    LCD_char_ClearDisplay();
    
    LCD_char_Position(0, 0);
    LCD_char_PrintString(LIGHTS_BAR);
    
    uint8_t current_counter = display_counter.counter;
    uint8_t current_position = display_counter.position;
    
    for(;;)
    {      
        if (QuadDec_GetCounter() > 20)
        {
            QuadDec_SetCounter(20);
        }
        if (QuadDec_GetCounter() < 1)
        {
            QuadDec_SetCounter(1);
        }
        
        if (mode_has_changed)
        {
            LCD_char_ClearDisplay();
            switch(display_mode)
            {
                case 0:
                    LCD_char_Position(0, 0);
                    LCD_char_PrintString(LIGHTS_BAR);
                    break;
                case 1:
                    LCD_char_Position(0, 0);
                    LCD_char_PrintString(SET_RED_COLOR);
                    LCD_char_Position(1, 0);
                    LCD_char_PrintString(TIME);
                    QuadDec_SetCounter(red_color_time);
                    break;
                case 2:
                    LCD_char_Position(0, 0);
                    LCD_char_PrintString(SET_YELLOW_COLOR);
                    LCD_char_Position(1, 0);
                    LCD_char_PrintString(TIME);
                    QuadDec_SetCounter(yellow_color_time);
                    break;
                case 3:
                    LCD_char_Position(0, 0);
                    LCD_char_PrintString(SET_GREEN_COLOR);
                    LCD_char_Position(1, 0);
                    LCD_char_PrintString(TIME);
                    QuadDec_SetCounter(green_color_time);
                    break;
                default:
                    break;
            }
            
            mode_has_changed = 0;
        }
        
        if (display_mode == 0)
        {
            if (current_position != display_counter.position)
            {
                LCD_char_Position(1, 0);
                LCD_char_PrintString(EMPTY_LINE);
                current_counter = display_counter.counter;
                current_position = display_counter.position;
            }
            current_counter = display_counter.counter;
            
            LCD_char_Position(1, current_position);
            if (current_counter < 10)
            {
                LCD_char_PutChar('0');
                LCD_char_Position(1, current_position + 1);
            }
            LCD_char_PrintDecUint16(current_counter);
        }
        else if (display_mode == 1)
        {
            LCD_char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_char_PutChar('0');
                LCD_char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_char_PrintDecUint16(QuadDec_GetCounter());
            
            red_color_time = QuadDec_GetCounter();
        }
        else if (display_mode == 2)
        {
            LCD_char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_char_PutChar('0');
                LCD_char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_char_PrintDecUint16(QuadDec_GetCounter());
            
            yellow_color_time = QuadDec_GetCounter();
        }
        else if (display_mode == 3)
        {
            LCD_char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_char_PutChar('0');
                LCD_char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_char_PrintDecUint16(QuadDec_GetCounter());
            
            green_color_time = QuadDec_GetCounter();
        }
    }
}

void first_algo_green(const uint8_t* pShift)
{
    if (green_color_time > 3)
    {
        if (counter < *pShift + (green_color_time - 3))
        {
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
         else if (counter < *pShift + (green_color_time - 2)){
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
         else if (counter < *pShift + (green_color_time - 1))
        {
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (green_color_time))
        {
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
    }
    else if (green_color_time == 3)
    {
        if (counter < *pShift + (green_color_time - 1))
        {
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (green_color_time))
        {
            c_register_Write(GREEN_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
    }
}

void first_algo_red(const uint8_t* pShift)
{
    c_register_Write(RED_COLOR);
    display_counter.position = POSITION_RED_TIME;
    display_counter.counter = red_color_time - (counter - *pShift);
}

void second_algo_green(const uint8_t* pShift)
{
    c_register_Write(GREEN_COLOR);
    display_counter.position = POSITION_GREEN_TIME;
    display_counter.counter = green_color_time - (counter - *pShift);
}

void second_algo_red(const uint8_t* pShift)
{
      if (red_color_time > 3) {
        if (counter < *pShift + (red_color_time - 3))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = red_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (red_color_time - 2))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = red_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (red_color_time - 1))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = red_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (red_color_time))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = red_color_time - (counter - *pShift);
        }
    }
    else if (green_color_time > 2)
    {
        if (counter < *pShift + (green_color_time - 1))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
        else if (counter < *pShift + (green_color_time))
        {
            c_register_Write(RED_COLOR);
            display_counter.position = POSITION_GREEN_TIME;
            c_register_Write(YELLOW_COLOR);
            display_counter.position = POSITION_YELLOW_TIME;
            display_counter.counter = green_color_time - (counter - *pShift);
        }
    }
}
