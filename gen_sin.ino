#include "AD9850.h"

int W_CLK = 2;
int FQ_UP = 3;
int RESET = 4;

int Dout = 5;
int palabra, resto, leer, i;
double frec;
int lectura;
int POTE1 = A1, POTE2 = A2, POTE3 = A3, POTE4 = A4, POTE5 = A5, POTE6 = A6;
int retardo = 8 ;
const float resolucion = 0.0291;


void setup() {
  Serial.begin(9800);
  DDS.begin(W_CLK,FQ_UP,Dout,RESET);
  DDS.calibrate(124500000);
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UP, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(Dout, OUTPUT);// pinMode(D1, OUTPUT); pinMode(D2, OUTPUT); pinMode(D3, OUTPUT); pinMode(D4, OUTPUT); pinMode(D5, OUTPUT); pinMode(D6, OUTPUT); pinMode(D7, OUTPUT);
 // pinMode(POTE1, OUTPUT); pinMode(POTE2, OUTPUT); pinMode(POTE3, OUTPUT); pinMode(POTE4, OUTPUT); pinMode(POTE5, OUTPUT); 
  //      x00K                     x0K                    xK                       x00			           xx
 // pinMode(SW, INPUT);
  digitalWrite(W_CLK, LOW);
  digitalWrite(FQ_UP, LOW);
  digitalWrite(RESET, LOW);
//  digitalWrite(POTE1, LOW); digitalWrite(POTE2, LOW); digitalWrite(POTE3, LOW); digitalWrite(POTE4, LOW); digitalWrite(POTE5, LOW); 
}

void loop() {
  //1.073.883 = 1M(999.999,8496)		107388 = 100k(99.999,7056)		10739 = 10k(10.000,1568)		1074 = 1k (1.000,1088)	107 = 100 (99,6384)
//  digitalWrite(POTE1, HIGH); digitalWrite(POTE5, LOW);	//cientos
  delay(retardo);
  lectura = analogRead(POTE1);
  //lectura = constrain(lectura, 10, 1010);
  frec = lectura*10/1024;
  Serial.print("U: ");Serial.print(lectura); Serial.print("\t");
  
  
  delay(retardo);
  lectura = analogRead(POTE2);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
      frec += 10*i;
  Serial.print("D: ");Serial.print(lectura); Serial.print("\t");
  
  delay(retardo);
  lectura = analogRead(POTE3);
  for (i=0;i<10;i++) 
	  if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += 100*i;
  Serial.print("C: ");Serial.print(lectura); Serial.print("\t");
  
  delay(retardo);
  lectura = analogRead(POTE6);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += 1000*i;
  Serial.print("UM: ");Serial.print(lectura); Serial.print("\t");
  
  delay(retardo);
  lectura = analogRead(POTE5);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += 10000*i;
  Serial.print("DM: ");Serial.print(lectura); Serial.print("\t");
  
  delay(retardo);
  lectura = analogRead(POTE4);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += 100000*i;
  Serial.print("CM: ");Serial.print(lectura); Serial.println("\t");
  
  DDS.setfreq(frec,0);
  delay(80);
}



