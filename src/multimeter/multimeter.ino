// Pin assignment - Common cathode for the 3 individual digits on 
3*seven-segment display 
const int DIGIT1 = 11; 
const int DIGIT2 = 12; 
const int DIGIT3 = 13; 
 
// Pin assignment - decimal point 
const int DM_POINT = 6; 
 
// Pin assignment - binary values for digital output to BCD-encoder 
const int BCD_A = 2; 
const int BCD_B = 3; 
const int BCD_C = 4; 
const int BCD_D = 5; 
 
// Pin assignment - function selection 
const int FUNCTION_1 = 7; 
const int FUNCTION_2 = 8; 
const int FUNCTION_3 = 9; 
const int FUNCTION_4 = 10; 
 
// Pin assignment - LEDs 
const int YELLOW_LED = 0; // Pin connected to Yellow LED 
const int RED_LED = 1;    // Pin connected to Red LED 
 
const int WAIT_TIME_MS = 2; // Fine-tuned delay for display multiplexing 
 
const float U_REF = 5.0; // Reference voltage for ADC 
 
// Real resistor values for calculations 
const int R1_LOW = 100; 
const int R1_HIGH = 15000; 
 
// High voltage scaling resistors 
const float R_HIGH = 67600.0; // 67.6k ohms 
const float R_LOW = 11760.0;  // 11.76k ohms 
const float SCALING_FACTOR = (R_HIGH + R_LOW) / R_LOW; 
 
// Battery check resistor values  
 
const float R4_BATT = 46450.0; // 46.45k ohms 
const float R6_BATT = 32600.0; // 32.60k ohms 
 
// Battery thresholds 
const float BATTERY_LOW_THRESHOLD = 6.5; 
const float HYSTERESIS_OFFSET = 0.5; 
const float NO_BATTERY_THRESHOLD = 1.0; 
 
// Global variables 
bool batteryCheckActive = true; 
bool batteryLow = false; 
int hundratal = 0, tiotal = 0, ental = 0; 
unsigned int counter = 0; 
int dp1 = 0, dp2 = 0, dp3 = 0; 
float U_in = 0; 
long int r2 = 0; 
bool continuityDetected = false; 
 
// Function prototypes 
void displayDigits(); 
float readBatteryVoltage(); 
 
void setup() { 
    // Configure pins 
    pinMode(DIGIT1, OUTPUT); 
    pinMode(DIGIT2, OUTPUT); 
    pinMode(DIGIT3, OUTPUT); 
    pinMode(DM_POINT, OUTPUT); 
    pinMode(A5, OUTPUT); // Buzzer 
 
    pinMode(BCD_A, OUTPUT); 
    pinMode(BCD_B, OUTPUT); 
    pinMode(BCD_C, OUTPUT); 
    pinMode(BCD_D, OUTPUT); 
 
    pinMode(FUNCTION_1, INPUT); 
    pinMode(FUNCTION_2, INPUT); 
    pinMode(FUNCTION_3, INPUT); 
    pinMode(FUNCTION_4, INPUT); 
 
    pinMode(YELLOW_LED, OUTPUT); 
    pinMode(RED_LED, OUTPUT); 
 
    // Turn off all indicators at startup 
    digitalWrite(DIGIT1, HIGH); 
    digitalWrite(DIGIT2, HIGH); 
    digitalWrite(DIGIT3, HIGH); 
    digitalWrite(DM_POINT, HIGH); 
    digitalWrite(A5, LOW); // Beeper off 
    digitalWrite(YELLOW_LED, LOW); 
    digitalWrite(RED_LED, LOW); 
} 
 
void loop() { 
    // Continuously update the display 
    displayDigits(); 
 
    // Turn off LEDs by default 
    digitalWrite(RED_LED, LOW); 
    digitalWrite(YELLOW_LED, LOW); 
 
    // Check battery status 
    if (batteryCheckActive) { 
        float batteryVoltage = readBatteryVoltage(); 
        if (batteryVoltage < NO_BATTERY_THRESHOLD) { 
            // No battery detected 
            batteryCheckActive = false; 
            digitalWrite(A5, LOW); // Buzzer off 
        } else if (batteryVoltage < BATTERY_LOW_THRESHOLD) { 
            // Battery low 
            if (!batteryLow) { 
                batteryLow = true; 
                digitalWrite(A5, HIGH); // Buzzer on 
            } 
        } else if (batteryVoltage > BATTERY_LOW_THRESHOLD + HYSTERESIS_OFFSET) 
{ 
            // Battery level normal 
            batteryLow = false; 
            digitalWrite(A5, LOW); // Buzzer off 
        } 
    } 

    // Perform measurements and other logic 
    int fkn1 = digitalRead(FUNCTION_1); 
    int fkn2 = digitalRead(FUNCTION_2); 
    int fkn3 = digitalRead(FUNCTION_3); 
    int fkn4 = digitalRead(FUNCTION_4); 
 
    int function_select = ((fkn4 << 3) | (fkn3 << 2) | (fkn2 << 1) | (fkn1 << 
0)); 
 
    switch (function_select) { 
        case 0b0001: // Low Voltage 
            U_in = analogRead(A0) * (U_REF / 1023.0); 
            if (U_in > U_REF) U_in = U_REF; 
            counter = (unsigned int)(U_in * 10); // Convert to 3-digit format 
            dp1 = LOW; dp2 = HIGH; dp3 = LOW; // Decimal after tens place 
            digitalWrite(YELLOW_LED, HIGH); 
            break; 
 
        case 0b0010: // High Voltage 
            U_in = analogRead(A1) * (U_REF / 1023.0) * SCALING_FACTOR; 
            counter = (unsigned int)(U_in * 10); 
            dp1 = LOW; dp2 = HIGH; dp3 = LOW; 
            digitalWrite(RED_LED, HIGH); 
            break; 
 
        case 0b0100: // Low Resistance 
            U_in = analogRead(A2) * (U_REF / 1023.0); 
            if (U_in < 0.01) { 
                r2 = -1; 
            } else { 
                r2 = (long int)(U_in * R1_LOW) / (U_REF - U_in); 
            } 
            if (r2 >= 0 && r2 < 10) digitalWrite(A5, HIGH); 
            else digitalWrite(A5, LOW); 
            counter = (r2 >= 0) ? r2 : 0; 
            dp1 = LOW; dp2 = LOW; dp3 = LOW; 
            digitalWrite(YELLOW_LED, HIGH); 
            break; 
 
        case 0b1000: // High Resistance 
            U_in = analogRead(A3) * (U_REF / 1023.0); 
            r2 = (long int)(U_in * R1_HIGH) / (U_REF - U_in); 
            if (r2 < 10000) { 
                counter = r2 / 100; 
                dp1 = LOW; dp2 = HIGH; dp3 = LOW; 
            } else { 
                counter = r2 / 1000; 
                dp1 = LOW; dp2 = LOW; dp3 = HIGH; 
            } 
            digitalWrite(YELLOW_LED, HIGH); 
            break; 
 
        default: 
            counter = 0; 
            dp1 = LOW; dp2 = LOW; dp3 = LOW; 
            digitalWrite(YELLOW_LED, HIGH); 
            break; 
    } 
} 
 
 
float readBatteryVoltage() { 
    float rawReading = analogRead(A4); 
    return rawReading * (U_REF / 1023.0) * ((R4_BATT + R6_BATT) / R6_BATT); 
} 
 
void displayDigits() { 
    // Hundreds digit 
    hundratal = (counter / 100) % 10; 
    digitalWrite(BCD_A, hundratal & 1); 
    digitalWrite(BCD_B, (hundratal >> 1) & 1); 
    digitalWrite(BCD_C, (hundratal >> 2) & 1); 
    digitalWrite(BCD_D, (hundratal >> 3) & 1); 
    digitalWrite(DM_POINT, dp1); 
    digitalWrite(DIGIT1, LOW); 
    delay(WAIT_TIME_MS); 
    digitalWrite(DIGIT1, HIGH); 
 
    // Tens digit 
    tiotal = (counter / 10) % 10; 
    digitalWrite(BCD_A, tiotal & 1); 
    digitalWrite(BCD_B, (tiotal >> 1) & 1); 
    digitalWrite(BCD_C, (tiotal >> 2) & 1); 
    digitalWrite(BCD_D, (tiotal >> 3) & 1); 
    digitalWrite(DM_POINT, dp2); 
    digitalWrite(DIGIT2, LOW); 
    delay(WAIT_TIME_MS); 
    digitalWrite(DIGIT2, HIGH); 
 
    // Units digit 
    ental = counter % 10; 
    digitalWrite(BCD_A, ental & 1); 
    digitalWrite(BCD_B, (ental >> 1) & 1); 
    digitalWrite(BCD_C, (ental >> 2) & 1); 
    digitalWrite(BCD_D, (ental >> 3) & 1); 
    digitalWrite(DM_POINT, dp3); 
    digitalWrite(DIGIT3, LOW); 
    delay(WAIT_TIME_MS); 
    digitalWrite(DIGIT3, HIGH); 
} 
 
 
 
32 