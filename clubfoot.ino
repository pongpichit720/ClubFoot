#include <CapacitiveSensor.h>
//In order to run this program, you much have imported capacitive library to your arduino library.

// variable for capacitive sensor
CapacitiveSensor   cs_1_0 = CapacitiveSensor(1,0);

// variables required
int use = 0;
int unuse = 0;
float percentage = 0;
int percentage1 = 0;
char command;
String message;
char m[30];
boolean printCommand = true;
boolean connected = false;
//String rawData[90];

// user variables
String name = "";
String idNumber = "";
int age = 0;
String date;
int interval = 1200000;
void setup() {
  cs_1_0.set_CS_AutocaL_Millis(0xFFFFFFFF); // set up sensor 
  
  Bean.setBeanName("ClubFoot1"); // set name on device
  Serial.begin(9600); // bandwidth for console (may not be necessary)
  Bean.setLed(0,0,0); // set LED to off initially
  Bean.enableWakeOnConnect(true); // enable to detect connection

 // for(int i = 0; i < 90; i++) rawData[i] = "000000000000000000000000000000000000000000000000000000000000000000000000";
}

void loop() {
  connected = Bean.getConnectionState(); // detect connection state
  if(connected){  // when connected
    //Bean.setLed(0,0,127); // turn on LED to blue
    if(printCommand){ // when command menu have not yet printed
      Bean.sleep(10000); // delay for console setup
      Serial.print("Please give me a command");
      Serial.print("'E' for Edit user information");
      Serial.print("'D' for input start date");
      Serial.print("'P' for Print data");
      Serial.print("'R' for Reset user data");
      printCommand = false;
      }

     // for testing sensor  
//    long start = millis();
//    cs_1_0 = CapacitiveSensor(1,0);
      cs_1_0.set_CS_AutocaL_Millis(0xFFFFFFFF);
      cs_1_0.set_CS_Timeout_Millis(2000);
    cs_1_0.lastCal = millis();
    long wear =  cs_1_0.capacitiveSensor(30);
    Serial.print(wear);
    Serial.print(" ");
    if(wear >= 0){ // check for error
        if(wear < 4100) unuse += 1; // increment unuse count
        else use += 1; // increment use count
        
        Bean.sleep(interval); // time waiting for next count check up
    }
   
    
    command = Serial.read(); // detect user command
    if(command == 'P'){ // command for print
      if((unuse+use) <= 0) percentage = 0;
      else percentage = ((float)use/(use+unuse))*100; 
      percentage1 = (percentage - (int)percentage)*100;
      
      message = "Name: ";
      message += name;
      Serial.print(message);
      message = "ID number: ";
      message += idNumber;
      Serial.print(message);
      message = "Age: ";
      message += age;
      Serial.print(message);
      message = "Start date: ";
      message += date;
      Serial.print(message);
      message = "Use = ";
      message += use*20; // use count
      message += " minutes";
      Serial.print(message);
      message = "Unuse = ";
      message += unuse*20; // unuse count
      message += " minutes";
      Serial.print(message);
      sprintf(m,"Percentage = %0d.%d percent",(int)percentage,percentage1);
      Serial.print(m);
      
      //printCommand = true;
    }else if(command == 'E'){
      name = "";
      idNumber = "";
      age = 0;
      Serial.print("User information has been reseted\nPlease input the name");
      while(name.length() <= 1) name = Serial.readString();
      Serial.print("Please input the ID number");
      while(idNumber.length() <= 1) idNumber = Serial.readString();
      Serial.print("Please input the age");
      age = 0;
      while(age == 0) age = Serial.parseInt();
      Serial.print("User edit complete");
      //printCommand = true;
    }else if(command == 'D'){
      date = "";
      Serial.print("Please input start date");
      while(date.length() <= 1) date = Serial.readString();
      Serial.print("Start date edit complete");
    }else if(command == 'R'){
      Serial.print("Reset user data");
      date = "";
      use = unuse = 0; // command for reset
      //printCommand = true;
    }
     
    }else{
      //Bean.setLed(0,0,0); // turn off LED and in collecting data mode(safe power)
      printCommand = true;
      
//      long start = millis();
//      cs_1_0 = CapacitiveSensor(1,0);
      cs_1_0.set_CS_AutocaL_Millis(0xFFFFFFFF);
      cs_1_0.set_CS_Timeout_Millis(2000);
      cs_1_0.lastCal = millis();
      long wear =  cs_1_0.capacitiveSensor(30);
      if(wear >= 0){ // check for error
        if(wear < 4100) unuse += 1; // increment unuse count
        else use += 1; // increment use count
        
       Bean.sleep(interval); // time waiting for next count check up
        }
      }
}

