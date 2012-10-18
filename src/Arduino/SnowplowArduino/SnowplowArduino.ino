#include "commands.h"

void setup(){
    int baud = 9600;
    Serial.begin(baud);
}

void loop(){
char cmd = Serial.read();
    switch (cmd){
        case CODE_SET_PIN_MODE:{           //sets the pin to input or output
            char pin = Serial.read();
            char inout = Serial.read();
            pinMode(pin, inout);
        }
        case CODE_SET_PWM:{                 //sets the PWM of the pin selected
            char pin = Serial.read(); 
            char val = Serial.read(); 
            analogWrite(pin, val); 
            break; 
        }
        case CODE_SET_DIGITAL:{             //sets the pin to on or off
            char pin = Serial.read();
            char b = Serial.read();
            digitalWrite(pin, b);
            break;
        }
        case CODE_READ_DIGITAL:{            //returns a char of pin on or off
            char pin = Serial.read();
            char dig_rd = digitalRead(pin);
            Serial.write(dig_rd);
            break;
        }
        case CODE_READ_ANALOG:{              //returns a short 0-1023
            char pin = Serial.read();
            short ana_rd = analogRead(pin);
            Serial.write(ana_rd);
            break;
        }
    }
}

