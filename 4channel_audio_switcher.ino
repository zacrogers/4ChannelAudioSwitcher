/*
    4 Channel Stereo Audio Switcher

    Multiplexer pins connected to 3 separate muxes
    MUX 1 = Audio left
    MUX 2 = Audio right
    MUX 3 = Led display
*/

#define NUM_CHANNELS 4

/* Mux select pin indexes */
enum class Select
{
    A = 0,
    B = 1
};

/* Button pin define indexes */
enum class BtnInd
{
    INCR = 0,
    DECR = 1
};

/* Pin defines */
const uint8_t MUX_PINS[2]    = {3, 4};
const uint8_t BUTTON_PINS[2] = {0, 2};

/* Channel States */
uint8_t current_channel = 0;
uint8_t prev_channel    = 0;

void setup() 
{
    for(uint8_t i = 0; i < 2; i++)
    {
        pinMode(MUX_PINS[i], OUTPUT);
        pinMode(BUTTON_PINS[i], INPUT);
    }
}

void loop() 
{
    read_buttons();

    if(prev_channel != current_channel)
    {
        channel_set();
    }
}

/* Increment or decrement current channel */
void read_buttons()
{
    if(digitalRead(BUTTON_PINS[(uint8_t)BtnInd::INCR]) == HIGH)
    {
        prev_channel = current_channel;

        if(current_channel < (NUM_CHANNELS - 1))
        {
            current_channel++;
        }    
        delay(250); /* debounce */
    }    

    if(digitalRead(BUTTON_PINS[(uint8_t)BtnInd::DECR]) == HIGH)
    {
        prev_channel = current_channel;

        if(current_channel > 0)
        {
            current_channel--;
        }
        delay(250); /* debounce */
    }     
}

void channel_set(void)
{
    digitalWrite(MUX_PINS[(uint8_t)SELECT::A], (current_channel & (0x1 << 0)));  
    digitalWrite(MUX_PINS[(uint8_t)SELECT::B], (current_channel & (0x1 << 1)));      
/*    
    switch(current_channel)
    {
        case 0:
            digitalWrite(MUX_PINS[0], LOW);
            digitalWrite(MUX_PINS[1], LOW);
            break;   
            
        case 1:
            digitalWrite(MUX_PINS[0], HIGH);
            digitalWrite(MUX_PINS[1], LOW);
            break;   
            
        case 2:
            digitalWrite(MUX_PINS[0], LOW);
            digitalWrite(MUX_PINS[1], HIGH);
            break;  
             
        case 3:
            digitalWrite(MUX_PINS[0], HIGH);
            digitalWrite(MUX_PINS[1], HIGH);
            break;    
    }    
*/
}
