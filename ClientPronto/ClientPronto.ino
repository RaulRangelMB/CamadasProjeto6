#include <Arduino.h>
int tx = 7;
float baudrate = 9600; //Baudrate fixo em 9600

char Caractere = 'P';
int valorAscii = int(Caractere);



void setup() {
  pinMode(tx, OUTPUT);
  Serial.begin(9600);
  digitalWrite(tx, HIGH);
}

void meioT(void){
  for(int i =0; i< 500;i++) { asm("NOP");}
}

void T(void){
  meioT();
  meioT();
 }


void loop() {
  
  Serial.println("Enviando ");
  Serial.println(Caractere);
  Serial.println("\n");
  Serial.println("Hexadecimal: ");
  Serial.println(valorAscii, HEX);

  digitalWrite(tx, 0); //bit de inicialização
  T();

  int um_qnt = 0;
  for(int i = 0; i < 8; i++){
    int bitEnvio = 1 & (valorAscii >> i);
    digitalWrite(tx, bitEnvio);
    if (bitEnvio == 1){
      um_qnt++;
    }
    T();
  }
  

  int bitParidade = um_qnt % 2;
  digitalWrite(tx, bitParidade);
  T();

  digitalWrite(tx, 1); //bit de parada
  T();

  
  delay(2000);
 }
