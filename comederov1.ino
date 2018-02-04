  // put your setup code here, to run once:



//  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define SERVO_PIN 0
#define SERVO_COMER 5
#define SERVO_STOP 83
#define SERVO_REVERSA 180
#define TIEMPO_COMIDA 10000
//#define TIEMPO_REVERSA 500
//#define TIEMPO_FOWARD 1500
#define TIEMPO_REVERSA 250
#define TIEMPO_FOWARD 750
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "4e40c05ed07b40558c5daafb574f8fe7";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "softronica_01";
//char pass[] = "el_perro_de_san_roque";
char ssid[] = "Guaynet";
char pass[] = "raqueleslamejor";
int dardecomer=0;
unsigned long timer_millis_1_inicio=0;
unsigned long timer_millis_1_fin=0;
unsigned long timer_millis_1_curent=0;
unsigned long timer_real =0;
unsigned long resta_timer = 0;

unsigned long intervalo_motor = 0;
int rotacion=0;

Servo servo;
BLYNK_WRITE(V3)
{
  dardecomer=param.asInt();
  timer_millis_1_inicio=millis()+TIEMPO_COMIDA;
  resta_timer = millis();
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
   alimentar();
   
   if (timer_millis_1_curent>=timer_millis_1_inicio)
    {
    dardecomer=0;
    intervalo_motor=0;
    rotacion=0;
    }
  }

  if(dardecomer==0)
  {
  servo.detach();
  delay(500);
  Serial.print("NOCOMER");
  }  
}



void alimentar()
{
timer_real = timer_millis_1_curent-resta_timer;

if (timer_real>=intervalo_motor)
  {
  if(rotacion == 1)
    {
    intervalo_motor = intervalo_motor + TIEMPO_FOWARD; 
    servo.write(SERVO_COMER); 
    rotacion = 0;
    Serial.println (" SERVO ADELANTE ");
    }
    else if (rotacion == 0)
    {
    servo.write(SERVO_REVERSA);
    Serial.println (" SERVO ATRAS ");
    intervalo_motor = intervalo_motor + TIEMPO_REVERSA;  
    rotacion = 1;
    }
  }
  // AQUI EN ESTE PUNTO PODEMOS INTRODUCIR EL TEMA DE LOS ATASCOS EN EL MOTOR Y SU ANALISIS.
  Serial.println("");
  Serial.print("Timer real: ");
  Serial.print(timer_real);
  Serial.print(" proximo cambio: ");
  Serial.print(intervalo_motor);
  if (rotacion==0)
  {
    Serial.print (" SERVO ADELANTE ");
  }else{
    Serial.print (" SERVO ATRAS ");
  }  
  Serial.print(" rotacion: ");
  Serial.println(rotacion);
  Serial.println("----------------------");
}

void atranco_alimentar()
{
timer_real = timer_millis_1_curent-resta_timer;

if (timer_real>=intervalo_motor)
  {
  if(rotacion == 1)
    {
    intervalo_motor = intervalo_motor + 150; 
    servo.write(SERVO_COMER); 
    rotacion = 0;
    Serial.println (" SERVO ADELANTE ");
    }
    else if (rotacion == 0)
    {
    servo.write(SERVO_REVERSA);
    Serial.println (" SERVO ATRAS ");
    intervalo_motor = intervalo_motor + 150;  
    rotacion = 1;
    }
  }

}

  


