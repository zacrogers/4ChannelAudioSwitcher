/*
    4 Channel Stereo Audio Switcher

    Multiplexer pins connected to 3 separate muxes
    MUX 1 = Audio left
    MUX 2 = Audio right
    MUX 3 = Led display
*/

/* Pin defines */
const uint8_t MUX_PINS[]    = {3, 4};
const uint8_t BUTTON_PINS[] = {0, 2};

/* States */
uint8_t current_state = 0;
uint8_t prev_state    = 0;

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
    read_button();

    if(prev_state != current_state)
    {
        channel_set();
    }
}


void read_button()
{
    if(digitalRead(BUTTON_PINS[0]) == HIGH)
    {
        prev_state = current_state;
        
        if(current_state < 4)
        {
            current_state++;
        }    
        delay(250);
    }    
    
    if(digitalRead(BUTTON_PINS[1]) == HIGH)
    {
        prev_state = current_state;
        
        if(current_state > 0)
        {
            current_state--;
        }
        delay(250);
    }     
}

void channel_set()
{
    switch(current_state)
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
}
