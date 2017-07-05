/* A través del presente software, se pretende controlar un oscilador digital, con frecuencias del rango 
 * de 0 a 25MHz, construido para utilizarse en el Laboratorio de Electrónica, de la facultad UTN de Bahía Blanca.
 * 
 * Su realización fue parte de la materia Medidas Electrónicas II, a cargo del profesor Miguel Banchieri y 
 * Oscar Rodriguez
 * 
 * Autor: Trapaglia Mansilla Matías Daniel
 */

#include "AD9850.h"     //librería de manejo del sintetizador digital (DDS), disponible en https://github.com/F4GOJ/AD9850

int W_CLK = 2;          //coneccionado de pines de control del DDS
int FQ_UP = 3;
int RESET = 4;
int Dout = 5;

double frec;
int lectura;
int POTE1 = A1, POTE2 = A2, POTE3 = A3, POTE4 = A4, POTE5 = A5, POTE6 = A6;  //puerto analógico para cada uno de los Potenciometros perilla
int retardo = 8 ;
const float resolucion = 0.0291;
bool millon;

enum Posicion { Unidad, Decena, Centena, UMil, DMil, CMil, UMillon, DMillon };

void setup() {
  //Serial.begin(9800);                     // a modo de debug
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UP, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(Dout, OUTPUT);
  pinMode(SW, INPUT);
  pinMode(LED_M, OUTPUT);
  DDS.begin(W_CLK,FQ_UP,Dout,RESET);        // inicializamos el hardware DDS
  DDS.calibrate(124500000);                 // calibración fina del cristal del DDS
  digitalWrite(W_CLK, LOW);
  digitalWrite(FQ_UP, LOW);
  digitalWrite(RESET, LOW);
}

int convertirValor(Posicion perilla, int valor) {
    switch (perilla) {
        case Unidad:
            valor = valor*10/1024; break;
        case Decena:
            if (valor<7) valor=0;
            else if (valor<125) valor = 10;
            else if (valor<234) valor = 20;
            else if (valor<352) valor = 30;
            else if (valor<463) valor = 40;
            else if (valor<578) valor = 50;
            else if (valor<696) valor = 60;
            else if (valor<812) valor = 70;
            else if (valor<925) valor = 80;
            else valor = 90; break;
        case Centena:
            if (valor<4) valor=0;
            else if (valor<103) valor = 100;
            else if (valor<215) valor = 200;
            else if (valor<336) valor = 300;
            else if (valor<462) valor = 400;
            else if (valor<598) valor = 500;
            else if (valor<724) valor = 600;
            else if (valor<842) valor = 700;
            else if (valor<942) valor = 800;
            else valor = 900; break;
        case UMil:
            if (valor<2) valor=0;
            else if (valor<85) valor = 1000;
            else if (valor<212) valor = 2000;
            else if (valor<342) valor = 3000;
            else if (valor<459) valor = 4000;
            else if (valor<571) valor = 5000;
            else if (valor<692) valor = 6000;
            else if (valor<811) valor = 7000;
            else if (valor<933) valor = 8000;
            else valor = 9000; break;
        case DMil:
            if (valor<10) valor=0;
            else if (valor<132) valor = 10000;
            else if (valor<251) valor = 20000;
            else if (valor<377) valor = 30000;
            else if (valor<485) valor = 40000;
            else if (valor<607) valor = 50000;
            else if (valor<731) valor = 60000;
            else if (valor<845) valor = 70000;
            else if (valor<969) valor = 80000;
            else valor = 90000; break;
        case CMil:
            if (valor<2) valor=0;
            else if (valor<98) valor = 100000;
            else if (valor<209) valor = 200000;
            else if (valor<331) valor = 300000;
            else if (valor<449) valor = 400000;
            else if (valor<586) valor = 500000;
            else if (valor<705) valor = 600000;
            else if (valor<818) valor = 700000;
            else if (valor<934) valor = 800000;
            else valor = 900000; break;
        case UMillon:
            if (valor<3) valor=0;
            else if (valor<96) valor = 1000000;
            else if (valor<209) valor = 2000000;
            else if (valor<322) valor = 3000000;
            else if (valor<440) valor = 4000000;
            else if (valor<566) valor = 5000000;
            else if (valor<692) valor = 6000000;
            else if (valor<805) valor = 7000000;
            else if (valor<928) valor = 8000000;
            else valor = 9000000; break;
        case DMillon:
            if (valor<7) valor=0;
            else if (valor<125) valor = 10000000;
            else if (valor<234) valor = 20000000;
            else if (valor<352) valor = 30000000;
            else if (valor<463) valor = 40000000;
            else if (valor<578) valor = 50000000;
            else if (valor<696) valor = 60000000;
            else if (valor<812) valor = 70000000;
            else if (valor<925) valor = 80000000;
            else valor = 90000000; break;
    }
    return (valor);
}


void loop() {
    
  millon = digitalRead(SW);                 // leo el estado del interruptor frontal de Millones
  digitalWrite(LED_M, millon);              // paso dicho parámetro al led y a los relays 

  delay(retardo);
  lectura = analogRead(POTE1);
  //lectura = constrain(lectura, 10, 1010);
  if(millon == HIGH)
    frec = convertirValor(UMillon, valor);
  else frec = convertirValor(Unidad, valor);
  //Serial.print("U: ");Serial.print(lectura); Serial.print("\t");      //salidas para debug
  
  
  delay(retardo);
  lectura = analogRead(POTE2);
  if(millon == HIGH)
    frec = convertirValor(DMillon, valor);
  else frec = convertirValor(Decena, valor);
  //Serial.print("D: ");Serial.print(lectura); Serial.print("\t");      //salidas para debug
  
  delay(retardo);
  lectura = analogRead(POTE3);
  frec += convertirValor(Centena, lectura);
  //Serial.print("C: ");Serial.print(lectura); Serial.print("\t");      //salidas para debug
  
  delay(retardo);
  lectura = analogRead(POTE6);
  frec += convertirValor(UMil, lectura);
  //Serial.print("UM: ");Serial.print(lectura); Serial.print("\t");     //salidas para debug
  
  delay(retardo);
  lectura = analogRead(POTE5);
  frec += convertirValor(DMil, lectura);
  //Serial.print("DM: ");Serial.print(lectura); Serial.print("\t");     //salidas para debug
  
  delay(retardo);
  lectura = analogRead(POTE4);
  frec += convertirValor(CMil, lectura);
  //Serial.print("CM: ");Serial.print(lectura); Serial.println("\t");   //salidas para debug
  
  DDS.setfreq(frec,0);              // paso al DDS el valor acumulado de frecuencia.
  delay(80);
}



