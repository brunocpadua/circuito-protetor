#include "EmonLib.h" //usa pra ler a corrente do medidor
#include <LiquidCrystal.h>

//inicializar lcd e medidor
EnergyMonitor medCorrente;
LiquidCrystal lcd(43,41,39,37,35,33);

int pinMedCorrente = 11; //pino do medidor
int rele = 53;  //pino do rele
long tempoRestante = 0; //variavel para armazenar o tempo restante ao original

void setup() 
{
  //inicialização do lcd
  lcd.begin(16, 2);

  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  medCorrente.current(pinMedCorrente, 29);
 
  //Define pinos para o rele como saida
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW); 
} 
 
void loop() 
{ 
  //Calcula a corrente  
  double corrente = medCorrente.calcIrms(1480); //calculando a corrente atual
  imprime(corrente, tempoRestante); //imprimindo as informacoes de tempo e corrente
}

void imprime(float corrente, long tempo){
  //convertendo o valor em segundos para horas, minutos e segundos
  int segundos = tempo % 60;
  int minutos = ((tempo-segundos)/60) % 60;  
  int horas = (tempo-minutos)/(60*60);
  
  //Informacoes iniciais display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Corrente:");
  lcd.setCursor(10,0); // imprime no lcd a corrente
  lcd.print(corrente);
  lcd.setCursor(15,0);
  lcd.print("A");
  lcd.setCursor(0,1);
  lcd.print("Tempo:");
  lcd.setCursor(7,1); // imprime no lcd a corrente
  if(horas >= 10)
    lcd.print(horas);
  else{
    lcd.print("0");
    lcd.print(horas);
  }
  lcd.print(":");
  if(minutos >= 10)
    lcd.print(minutos);
  else{
    lcd.print("0");
    lcd.print(minutos);
  }  
  lcd.print(":");
  if(segundos >= 10)
    lcd.print(segundos);
  else{
    lcd.print("0");
    lcd.print(segundos);
  } 
}
