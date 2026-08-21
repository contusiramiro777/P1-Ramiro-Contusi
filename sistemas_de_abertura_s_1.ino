#include <Servo.h>

#define PIR_ENTRADA 8
#define PIR_SALIDA 9
#define BUZZER 11

#define SERVO_1 5
#define SERVO_2 6

#define FOCO 13
#define LDR A0


Servo servo1;
Servo servo2;

int limiteLuz = 400;
int puertasAbiertas = 0;

void detectarMovimiento(int pin, int &movimiento)
{
  movimiento = digitalRead(pin);
}

void detectarLuz(int pin, int limite, int &oscuro)
{
  int valor = analogRead(pin);

  if(valor < limite)
  {
    oscuro = HIGH;
  }
  else
  {
    oscuro = LOW;
  }
}

void controlarLuminaria(int pin, int estado)
{
  digitalWrite(pin, estado);
}

void abrirPuertas(int pos1, int pos2)
{
  servo1.write(pos1);
  servo2.write(pos2);

  puertasAbiertas = 1;
}

void cerrarPuertas(int pos1, int pos2)
{
  servo1.write(pos1);
  servo2.write(pos2);

  puertasAbiertas = 0;
}

void cancionAbrir(int pin)
{
  tone(pin,262,200);
  delay(250);

  tone(pin,294,200);
  delay(250);

  tone(pin,330,200);
  delay(250);

  tone(pin,349,200);
  delay(250);

  tone(pin,392,300);
  delay(350);

  noTone(pin);
}

void cancionCerrar(int pin)
{
  tone(pin,392,200);
  delay(250);

  tone(pin,349,200);
  delay(250);

  tone(pin,330,200);
  delay(250);

  tone(pin,294,200);
  delay(250);

  tone(pin,262,300);
  delay(350);

  noTone(pin);
}

void cambiarPuerta()
{
  if(puertasAbiertas == 0)
  {
    abrirPuertas(0,180);
    cancionAbrir(BUZZER);
  }
  else
  {
    cerrarPuertas(90,90);
    cancionCerrar(BUZZER);
  }
}


void setup()
{
  pinMode(PIR_ENTRADA, INPUT);
  pinMode(PIR_SALIDA, INPUT);

  pinMode(FOCO, OUTPUT);
  pinMode(BUZZER, OUTPUT);


  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);


  cerrarPuertas(90,90);


  delay(30000); // calibración PIR
}


void loop()
{

  int movimientoEntrada;
  int movimientoSalida;
  int oscuro;


  detectarMovimiento(PIR_ENTRADA,movimientoEntrada);
  detectarMovimiento(PIR_SALIDA,movimientoSalida);


  detectarLuz(LDR,limiteLuz,oscuro);


  controlarLuminaria(FOCO,oscuro);



  if(movimientoEntrada == HIGH)
  {
    cambiarPuerta();
    delay(1000);
  }


  if(movimientoSalida == HIGH)
  {
    cambiarPuerta();
    delay(1000);
  }

}
