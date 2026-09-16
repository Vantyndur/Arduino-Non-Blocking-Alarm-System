// GLOBAL 
// pins aliases definitions
const int workLedPin = 8; 
const int alarmLedPin = 7;
const int buzzerPin = 12;
const int buttonPin = 4;
const int sensorPin = A0;
// Alarm messages  
const String ErrorMessage1 = "ERR_CODE_1: HIGH TEMP!";
const String ErrorMessage2 = "ERR_CODE_2: EMERGENCY BUTON PUSHED!";
// variables definitions
bool isAlarmOn, alarmState;
int sensorValue, buttonValue;
// delay variables definitions
unsigned long stoper1;
unsigned int stoper1Interval; 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Fuctions

// This function takes provided message and sends it through the serial port without stoping the program.
// It sends part after part until whole message is sent.
// Must be left without parameter in void loop function to continously send messages.
// Add optional message parameter to add message to be sent to the buffer.
// Function returns false when Serial is not open for transmission. 
bool BufferedSerialWrite(String message = ""){
  // initialize the static messageBuffer variable.
  static String messageBuffer = "";
  if(!Serial) return false;
  if(message.length() > 0){
    // add message to the buffer.
    messageBuffer += message;
    // seperate messages with new line.
    messageBuffer += "\n";
  }
  // send message:
  // Check if there is any message to send.
  if(messageBuffer.length()>0){
    // Check serial buffer available space.
    int serialBufforSize = Serial.availableForWrite();
    // Check if whole messageBuffer can be sent at once.
    if(serialBufforSize > messageBuffer.length()){
      Serial.print(messageBuffer);
      // Clear message buffer
      messageBuffer = "";
    }
    // Send first part of message
    else {
      // Chose piece of message
      String transmision = messageBuffer.substring(0, serialBufforSize);
      // Write piece of message to serial port.
      Serial.print(transmision);
      // Remove sent part of message.
      messageBuffer = messageBuffer.substring(serialBufforSize);
    }
  }
  return true;
}

void turnAlarmOn(){
  //Turn off the green LED indicating proper work of system.
    digitalWrite(workLedPin, LOW);
    // Turn on the alarm sequence.
    isAlarmOn = true;
    alarmState = HIGH;
    digitalWrite(alarmLedPin, alarmState);
    digitalWrite(buzzerPin, alarmState);
    stoper1 = millis();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>

// PROGRAM LOGIC
void setup()
{

  // variables initialization
  isAlarmOn = false;
  sensorValue = 0;
  buttonValue = 1;
  alarmState = LOW;
  // delay variables initialization
  stoper1 = 0;
  stoper1Interval = 500;
  // setup pins modes
  pinMode(workLedPin, OUTPUT);
  pinMode(alarmLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  // setup serial communication
  Serial.begin(9600);
  // check if the serial connection is open for transmition in case of danger.
  while(!Serial) {
    ; // wait for serial port to connect.
  }
  // Light green LED indicating proper work of system.
  digitalWrite(workLedPin, HIGH);
}

void loop()
{
  // Write to Serial port from program buffer.
  BufferedSerialWrite();
  // Read analog sensor value.
  sensorValue = analogRead(sensorPin);
  // Check if analog sensor value is out of proper work scope.
  if (sensorValue > 1000 && !isAlarmOn)
  {
    turnAlarmOn();
    // Send alarm information to remote devices.
    BufferedSerialWrite(ErrorMessage1);
    BufferedSerialWrite("Temperature sensor value: "+String(sensorValue));
  }
  // Read button value.
  buttonValue = digitalRead(buttonPin);
  // Check if the button was pressed.
  if (buttonValue == 0 && !isAlarmOn)
  {
    turnAlarmOn();
    // Send alarm information to remote devices.
    BufferedSerialWrite(ErrorMessage2);
  }
  // check if the Alarm is currently on
  if (isAlarmOn)
  {
    // get current time
    unsigned long currentTime = millis();
    // Check if enough time had passed since last state change
    if(stoper1 + stoper1Interval <= currentTime){
      // change alarm state
      alarmState = !alarmState;
      // write appropriate state on the alarm pins
      digitalWrite(alarmLedPin, alarmState);
      digitalWrite(buzzerPin, alarmState);
      // set last state change time to current time
      stoper1 = currentTime;
    }

  }
}