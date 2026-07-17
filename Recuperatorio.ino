#define LedR 5
#define LedV 6
#define LedA 7
#define PIR 2
#define Potenciometro A0
#define SensorTemp A1
#define SensorLuz A2

int ValorPot;
int Grados;
float PorcentajeLuz;
bool Movimiento;

void setup()
{
  Serial.begin(9600);
  
    pinMode(LedR, OUTPUT);
    pinMode(LedV, OUTPUT);
    pinMode(LedA, OUTPUT);
    pinMode(PIR, INPUT);
}
void loop()
{
  Leer();
  Serial.print("Potenciometro: ");
  Serial.print(ValorPot);
  Serial.print("Temperatura: ");
  Serial.print(Grados);
  Serial.print("Luz: ");
  Serial.print(PorcentajeLuz);
  Control();
}
void Leer()
{
  int valorPotRaw = analogRead(Potenciometro);
  ValorPot = map(valorPotRaw, 0, 1023, 0, 100);

  int valorTemp = analogRead(SensorTemp);
  Grados = map(((valorTemp - 20) * 3.08), 800, 2000, 0, 100);

  int valorLuz = analogRead(SensorLuz);
  PorcentajeLuz = map(valorLuz, 460, 1017, 0, 100);

  Movimiento = digitalRead(PIR);
}

void Control()
{
  if (PorcentajeLuz >= 100)
  {
    digitalWrite(LedR, HIGH);
    digitalWrite(LedV, HIGH);
    digitalWrite(LedA, HIGH);
  }
  else if (ValorPot >= 50 && ValorPot <= 75 && Grados < 15)
  {
    if (Movimiento == HIGH)
    {
      Secuencia();
    }
    else
    {
      Apagar();
    }
  }
  else
  {
    Apagar();
  }
}

void Secuencia()
{
  digitalWrite(LedR, HIGH);
  delay(1000);
  digitalWrite(LedR, LOW);

  digitalWrite(LedV, HIGH);
  delay(1000);
  digitalWrite(LedV, LOW);

  digitalWrite(LedA, HIGH);
  delay(1000);
  digitalWrite(LedA, LOW);
}

void Apagar()
{
  digitalWrite(LedR, LOW);
  digitalWrite(LedV, LOW);
  digitalWrite(LedA, LOW);
}
  