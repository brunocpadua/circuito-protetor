#include "EmonLib.h" //usa pra ler a corrente do medidor
#include <LiquidCrystal.h>
#define botRight  1
#define botUp     2
#define botDown   3
#define botLeft   4
#define botSelect 5

//inicializar lcd e medidor
EnergyMonitor medCorrente;
LiquidCrystal lcd(43,41,39,37,35,33);

int pinMedCorrente = 11; //pino do medidor
int rele = 53;  //pino do rele
long tempoRestante = 0; //variavel para armazenar o tempo restante ao original
long tempoInicio; //guarda informação da millis() de quando o tempo foi setado
long tempo; //tempo setado
int botao = 8; //pino de leitura dos botoes

void setup() {
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
  if(leituraBotao(botao) == botSelect){
      tempo = setTempo(botao,tempoRestante); //seta tempo
      tempoInicio = millis();
      tempoRestante = tempo*60;
      digitalWrite(rele, LOW); //liga rele caso setado tempo
  }

  if(tempoRestante != 0){//subtraindo o tempo atual do restante - se acabou o tempo nao subtrai
     tempoRestante = tempo*60*1000 - (millis() - tempoInicio);
     Serial.println(tempoInicio);
     tempoRestante = floor(tempoRestante/1000.0);
  }
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

int setTempo(int botao, long tempo){
    delay(500);
    lcd.clear(); //limpa o lcd
    //convertendo o valor em segundos para horas, minutos e segundos
    int segundos = tempo % 60;
    int minutos = ((tempo-segundos)/60) % 60;  
    int horas = (tempo-minutos)/(60*60);
    int incremento = 3;
    
    while(leituraBotao(botao) != botSelect){
      switch(leituraBotao(botao)){
          case botLeft: { //botao da esquerda
              incremento++;
              if(incremento == 4)
                  incremento = 3;
              break;              
          }
          case botRight: { //botao da direita
              incremento--;
              if(incremento == 0)
                  incremento = 1;
              break;
          }
          case botUp: { //botao da cima
              switch(incremento){
                  case 1: minutos++; break;
                  case 2: minutos = minutos + 10; break;
                  case 3: horas++; break;              
              }
              if(minutos >= 60){
                minutos = minutos - 60;
                horas++;
              }
              if(horas > 23){
                    horas = 24;
                    minutos = 0;
                    lcd.setCursor(0,1);
                    lcd.print("Limite Excedido!!!");
                    delay(1000);
                    lcd.clear();
              }
              break;
          }
          case botDown: { //botao da baixo
              switch(incremento){
                  case 1: minutos--; break;
                  case 2: minutos = minutos - 10; break;
                  case 3: horas--; break;              
              }
              if(minutos < 0){//se os minutos forem negativos, tem que descontar da hora
                minutos = 60 + minutos;
                horas--;
                if(horas < 0) //caso a hora fosse 0, ela ia passar a ser negativa
                  minutos = 0; //logo se os minutos forem negativos e nao tiver onde descontar, coloca em zero
              }
              if(horas < 0){ //se as horas forem negativas, temos que avisar e coloca-la em zero
                    horas = 0;
                    lcd.setCursor(0,1);
                    lcd.print("Limite Excedido!!!");
                    delay(1000);
                    lcd.clear();
              }
              break;
          }
      } 
      lcd.setCursor(0,0); //imprime no lcd a corrente maxima
      lcd.print("Tempo: ");
      lcd.setCursor(0,1); //imprime a corrente setada
      
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
      switch(incremento){
         case 1: lcd.setCursor(4,1); break;
         case 2: lcd.setCursor(3,1); break;
         case 3: lcd.setCursor(1,1); break;
      } //colocando o cursor nas respectivas casas
      lcd.cursor(); 
      delay(200);      
    }  
    lcd.noCursor();
    return (horas*60 + minutos); //retorna os minutos
}

int leituraBotao(int botao){
  int bot = analogRead(botao);
  if (bot < 50)   return botRight; 
  if (bot < 195)  return botUp;
  if (bot < 380)  return botDown;
  if (bot < 555)  return botLeft;
  if (bot < 790)  return botSelect;  
  return 0; //quando nenhum botao eh precionado
}
