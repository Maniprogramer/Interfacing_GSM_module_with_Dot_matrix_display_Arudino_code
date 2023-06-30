 
int led=13;

int temp=0,i=0,x=0,k=0,sent=0,first=0;
char str[100],msg[32];


#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define BUF_SIZE 75

char message[BUF_SIZE] = { "" };                                 //This is the variable that is used store and to display the message on the display.
char startup[] = "Starting GSM Module";                         //This is variable used to initialise the starting message.
//char 

#define MAX_DEVICES 4                      //Max devices of dot matrix boards
#define CLK_PIN 13                         // CLK or SCK
#define DATA_PIN                           // DATA or MOSI
#define CS_PIN 10                         // CS or SS

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);    //setting hardware type

void setup() {
  Serial.begin(9600);   //serial monitor baud rate
  myDisplay.begin();            //initialising the display
  myDisplay.setIntensity(1);                                          //This value can be change within (1-15)as it increases or decreases the brightness of the display
  myDisplay.displayClear();                                            //This is used to clear the display
  myDisplay.displayScroll(message, PA_CENTER, PA_SCROLL_LEFT, 200);   //This is responsible to display the message

//Initialising the gsm module
  Serial.println("GSM Initilizing...");
  matrix_display();                     //calling the matrix_display funtion
  gsm_init();                           //calling the gsm_initialising funtion
  Serial.println("Wireless Notice");
  delay(200);
  Serial.println("    Board      ");
  delay(200);
  Serial.println("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");    //Gsm module is set to receiving mode
  delay(500);
  Serial.println("AT+CMGF=1");            //Gsm module is set to the text mode
  delay(500);
}

void loop() {

    for(unsigned int t=0;t<60000;t++)
  {
    serialEvent();                    //calling serial event funtion
  if(temp==1)
  {
    x=0,k=0,temp=0;
    while(x<i)
    {
      while(str[x]=='#')            //checks for #(hash) in the message if it is present its start storing the message
      {
        x++;
        while(str[x]!='*')          //checks for *(astrix) in the message if it is present it stops storing the message
        {
          msg[k++]=str[x++];
        }
      }
      x++;
    }
    msg[k]='\0';
    Serial.println(msg);      //print the received message in serial monitor
    matrix_display();         // Call the display function to show the message
    delay(1000);
    temp=0;
    i=0;
    x=0;
    k=0;

   if(sent==1){
      sent=0;
      SendMessage();    //calling the send message funtion to sending msg when message is received from the receiver || someone
          
      }
    }
  }
  
  
  if (myDisplay.displayAnimate()) {     //this line checks wheater display is animating any message if yes, it returns true if no it returns false----
                                        //----if the condition is true the display continues animating if condition is false it enters the loop and resets the display to display new message
    myDisplay.displayReset();
  }
}

void matrix_display() {                                                         //This is code for the dot matrix 
    
    if(first==0){     //This condition is to display startup message
      
      myDisplay.displayClear();     //before displaying something we need to clear something
      String myString =String(startup);       //we concat starup message to a string
      myString.toCharArray(message, sizeof(message));   //here string is converted to the char array 

    }

     if(first==1){      //This condition is to display received messages from the gsm module
      
      if (myDisplay.displayAnimate()) {     //This loop will  not to interupt the animating message,wait for it complete and then passed the next new message to display
        myDisplay.displayReset();
      }
      String myString = String(msg);                                         //In this msg char is converted to the string and concated to the mystring

    if(myString.length() == 0){
      String myString = "Try to Send a Message";
     }
    
    myString.toCharArray(message, sizeof(message));                        //This line is used to store the mystring variable to the message variable
   
   }
}



void serialEvent()      //This funtion checks *(astrix) if it is present it declares as message received
{
  while(Serial.available())
  {
    char ch=(char)Serial.read();
    str[i++]=ch;
    if(ch == '*')
    {
      temp=1;
      sent=1;
      first=1;
      Serial.println("Message Received");     //This message is printed in serial monitor
      delay(500);                             //waits for a half second
    }
  }
}

void gsm_init()               //This funtion is to initialise the gsm module
{
  Serial.println("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    while(Serial.available()>0)     //if gsm connected and availabe it enters the loop
    {
      if(Serial.find("OK"))         //finds for ok message if true continues the next commands
      at_flag=0;
    }
    delay(1000);
  }

  Serial.println("Module Connected..");
  delay(1000);
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))     //again checks for ok message
      echo_flag=0;
    }
    delay(2000);
  }

  delay(2000);
  Serial.println("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");     
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))       //trying to find the signal 
      net_flag=0;
    }
    delay(1000);
  }
  Serial.println("Network Found..");
  delay(1000);
  
}

 void SendMessage()
{
  Serial.println ("Sending Message");
  Serial.println("AT+CMGF=1");        //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  Serial.println("AT+CMGS=\"+918686873899\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println("Message Received :");   // Messsage content
  Serial.print(msg);   // Messsage content
  delay(100);

  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
