# Interfacing_GSM_module_with_Dot_matrix_display_Arudino_code
>In this project we can send sms to the gsm module and this message is displayed on dot matrix display(max 7219) in return when the message is received by the module it sends back the conformation message to the specific number


## connetion for the project follows:
**********************************************************************************************************************
>Connection for the GSM Module

>connect the RX pin of the GSM module to the TX pin of arduino
connect the TX pin of the GSM module to the RX pin of arduino

>Now connect the vcc of the GSM module to the 5V power and GND pin to the ground.
**********************************************************************************************************************
## Connection for Dot Matrix Display Max7219

>Connect CLK_Pin of the dot matrix display to the pin 13 of the arduino.
Connect Data_Pin of the dot matrix display to the pin 11 of the arduino.
Connect the Cs_Pin of the dot matrix display to the pin 10 of the arduino.

>Finally connect the VCC to the 5V and GND to the ground.

Now we are done with the connections.
**********************************************************************************************************************
## Now upload the code Arduino UNO 
### Note:

> Before you upload the sketch to the Arduino make sure that you disconnect the RX and TX pins(0 and 1 pins) of the Arduino.
    When you are done uploading the sketch you can reconnect the pins.
    Now you are ready to go.
**********************************************************************************************************************
## Working of the project:
>  When you start the project the GSM Module and dot matrix get initialised.
  After getting intilised the dot matrix displays the defaut text.
  The GSM module is set to the messages reciving mode now you can send the message to the number which is you've given.
  When the message is received starting with # and ending with the * it stores in an array and message stored in array is display on   the dot matrix.
  The old message gets displayed until the new  message is received.
**********************************************************************************************************************

