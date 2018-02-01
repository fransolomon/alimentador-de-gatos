  // put your setup code here, to run once:



//  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

/*************************************************************

  Download latest Blynk library here:

    https://github.com/blynkkk/blynk-library/releases/latest



  Blynk is a platform with iOS and Android apps to control

  Arduino, Raspberry Pi and the likes over the Internet.

  You can easily build graphic interfaces for all your

  projects by simply dragging and dropping widgets.



    Downloads, docs, tutorials: http://www.blynk.cc

    Sketch generator:           http://examples.blynk.cc

    Blynk community:            http://community.blynk.cc

    Follow us:                  http://www.fb.com/blynkapp

                                http://twitter.com/blynk_app



  Blynk library is licensed under MIT license

  This example code is in public domain.



 *************************************************************



  Rotate a servo using a slider!



  App project setup:

    Slider widget (0...180) on V3

 *************************************************************/



/* Comment this out to disable prints and save space */

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define SERVO_PIN 0
#define SERVO_COMER 5
#define SERVO_STOP 5
#define TIEMPO_COMIDA 5
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "4e40c05ed07b40558c5daafb574f8fe7";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "softronica_01";
char pass[] = "el_perro_de_san_roque";
int dardecomer=0;
unsigned long timer_millis_1_inicio=0;
unsigned long timer_millis_1_fin=0;
unsigned long timer_millis_1_curent=0;

Servo servo;
BLYNK_WRITE(V3)
{
  dardecomer=param.asInt();
  timer_millis_1_inicio=millis()+TIEMPO_COMIDA;
  
}

BLYNK_APP_CONNECTED() {
  Serial.println("App Connected.");
}

// This is called when Smartphone App is closed
BLYNK_APP_DISCONNECTED() {
  Serial.println("App Disconnected.");
}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, IPAddress(213,98,53,186), 8442); //213.98.53.186
  servo.attach(SERVO_PIN);
}



void loop()
{
  Blynk.run();

  timer_millis_1_curent=millis();
  
  if(dardecomer==1)
  {
   servo.attach(SERVO_PIN);
   servo.write(SERVO_COMER);
   Serial.print("COMER");
   if (timer_millis_1_curent>=timer_millis_1_inicio)
    {
    dardecomer=0;
    }
  }

  if(dardecomer==0)
  {
  servo.detach();
  delay(500);
  Serial.print("NOCOMER");
  }  

 

}
