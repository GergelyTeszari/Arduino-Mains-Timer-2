int LEDs[3] = {12, 11, 10};
int button1 = 4;
int button2 = 5;
int button3 = 6;
int relay1= 2;
int relay2 = 3;
long timeUnit = 1800000;
long relay1Time = 0;
long relay2Time = 0;
bool isStarted = false;
bool nightMode = false;
bool isSecondDifferent = false;
bool isEnded = false;

void setup(){
    for (int i=0; i<3; i++){
        pinMode(LEDs[i], OUTPUT);
        digitalWrite(LEDs[i], HIGH);
    }
    pinMode(button1, INPUT);
    digitalWrite(button1, LOW);
    pinMode(button2, INPUT);
    digitalWrite(button2, LOW);
    pinMode(button3, INPUT);
    digitalWrite(button3, LOW);
    pinMode(relay1, OUTPUT);
    digitalWrite(relay1, LOW);
    pinMode(relay2, OUTPUT);
    digitalWrite(relay2, LOW);
}

void loop(){
    if(isStarted){
        isEnded = wait1Sec();
        if (isEnded){
            reset();
            return;
        }
        if (relay1Time >= 1000){
            LEDshow(relay1Time, false);
        }
        else{
            LEDshow(relay2Time, false);
        }       
    }
    //Button1
    if (digitalRead(button1) == HIGH){
        if (!isStarted){
            if (!isSecondDifferent){
                relay1Time += timeUnit;
                if (relay1Time / timeUnit > 7){
                    relay1Time = 0;
                }
                LEDshow(relay1Time, true);
            }
            if (isSecondDifferent){
                relay2Time += timeUnit;
                if (relay2Time / timeUnit > 7){
                    relay2Time = 0;
                }
                LEDshow(relay2Time, true);
            }
        }
        if (isStarted){
            blink(2);
            clrLED();
            nightMode = true;
        }
    }
    //Button2
    if (digitalRead(button2) == HIGH){
        if (!isStarted){
            isSecondDifferent = true;
            blink(3);
        }
        if (isStarted){
            blink(3);
            relay1Time += timeUnit;
            if (relay1Time / timeUnit > 7){
                relay1Time = 0;
            }
            relay2Time += timeUnit;
            if (relay1Time / timeUnit > 7){
                relay2Time = 0;
            }
            Serial.println(relay1Time);
            Serial.println(relay2Time);
        }
    }
    //Button3
    if (digitalRead(button3) == HIGH){
        if (!isStarted){
            isStarted = true;
            blink(5);
            Serial.println("Start");
            if (!isSecondDifferent){
                relay2Time = relay1Time;
            }
            Serial.println(relay1Time);
            Serial.println(relay2Time);
            digitalWrite(relay1, HIGH);
            digitalWrite(relay2, HIGH);
            return;
        }
        if (isStarted){
            reset();
        }
    }
    delay(50);
}

void reset(){
    isSecondDifferent = false;
    nightMode = false;
    isStarted = false;
    relay1Time = 0;
    relay2Time = 0;
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    blink(5);
}

bool wait1Sec(){
    delay(1000);
    relay1Time -= 1000;
    if (relay1Time <= 0){
        relay1Time = 0;
        digitalWrite(relay1, LOW);
        if (!isSecondDifferent){
            relay2Time = 0;
            digitalWrite(relay2, LOW);
            return true;
        }
    }
    relay2Time -= 1000;
    if (relay2Time <= 0){
        relay2Time = 0;
        digitalWrite(relay2, LOW);
    }
    if (relay1Time <= 0 && relay2Time <= 0){
        relay1Time = 0;
        relay2Time = 0;
        digitalWrite(relay1, LOW);
        digitalWrite(relay2, LOW);
        return true;
    }
    return false;
}

void blink(int times){
    for(int i=0; i<times; i++){
        digitalWrite(LEDs[0], LOW);
        digitalWrite(LEDs[1], LOW);
        digitalWrite(LEDs[2], LOW);
        delay(100);
        digitalWrite(LEDs[0], HIGH);
        digitalWrite(LEDs[1], HIGH);
        digitalWrite(LEDs[2], HIGH);
        delay(100);
    }
}

void LEDshow(long time, bool hold){
    clrLED();
    time /= timeUnit;
    if (not nightMode){
        for(int i=0; i<3; i++){
            int pin = LEDs[i];
            int pinState = (time >> i) & 1;
            digitalWrite(pin, 1-pinState);
        }
        if (hold) {
            delay(1000);
            clrLED();
        }
    }
}

void clrLED(){
    for(int i=0; i<3; i++){
        digitalWrite(LEDs[i], HIGH);
    }
}
