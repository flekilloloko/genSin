int W_CLK = 2;
int FQ_UP = 3;
int RESET = 4;
int D0 = 12, D1 = 11, D2 = 10, D3 = 9, D4 = 8, D5 = 7, D6 = 6, D7 = 5;
int palabra, resto, leer, i;
double frec;
long lectura;
int SW = 13, POTE = 2;
int retardo = 10 ;


void setup() {
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UP, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(D0, OUTPUT); pinMode(D1, OUTPUT); pinMode(D2, OUTPUT); pinMode(D3, OUTPUT); pinMode(D4, OUTPUT); pinMode(D5, OUTPUT); pinMode(D6, OUTPUT); pinMode(D7, OUTPUT);
  pinMode(POTE1, OUTPUT); pinMode(POTE2, OUTPUT); pinMode(POTE3, OUTPUT); pinMode(POTE4, OUTPUT); pinMode(POTE5, OUTPUT); 
  //      x00K                     x0K                    xK                       x00			           xx
  pinMode(SW, INPUT);
  digitalWrite(W_CLK, LOW);
  digitalWrite(FQ_UP, LOW);
  digitalWrite(RESET, LOW);
  digitalWrite(POTE1, LOW); digitalWrite(POTE2, LOW); digitalWrite(POTE3, LOW); digitalWrite(POTE4, LOW); digitalWrite(POTE5, LOW); 
}

void loop() {
  //1.073.883 = 1M(999.999,8496)		107388 = 100k(99.999,7056)		10739 = 10k(10.000,1568)		1074 = 1k (1.000,1088)	107 = 100 (99,6384)
  digitalWrite(POTE1, HIGH); digitalWrite(POTE5, LOW);	//cientos
  delay(retardo);
  lectura = analogRead(POTE);
  if (lectura>969) lectura = 1023;
  for (i=0;i<10;i++) 
	  if((lectura>=102*i)&&(lectura<102*(i+1))) 
		  lectura = 102*i;
  frec = lectura * 107;
  
  digitalWrite(POTE2, HIGH); digitalWrite(POTE1, LOW);	//miles
  delay(retardo);
  lectura = analogRead(POTE);
  if (lectura>969) lectura = 1023;
  for (i=0;i<20;i++) 
	  if((lectura>=102*i)&&(lectura<102*(i+1))) 
		  lectura = 102*i;
  frec += lectura * 1074;
  
  digitalWrite(POTE1, HIGH); digitalWrite(POTE5, LOW);	//decenas de miles
  delay(retardo);
  lectura = analogRead(POTE);
  if (lectura>969) lectura = 1023;
  for (i=0;i<20;i++) 
	  if((lectura>=102*i)&&(lectura<102*(i+1))) 
		  lectura = 102*i;
  frec += lectura * 10739;
  
  digitalWrite(POTE1, HIGH); digitalWrite(POTE5, LOW); //cientos de miles
  delay(retardo);
  lectura = analogRead(POTE);
  if (lectura>969) lectura = 1023;
  for (i=0;i<20;i++) 
	  if((lectura>=102*i)&&(lectura<102*(i+1))) 
		  lectura = 102*i;
  frec += lectura * 107388;
  
  frecuency(frec);
  delay(100);
}

void frecuency(long freq){
  palabra = 0;
  digitalWrite(RESET, HIGH); delay(1); digitalWrite(RESET, LOW);
  cargarDatos(palabra); //word 0    =   Fase y control
  palabra = freq / 524288;
  cargarDatos(palabra); //word 1	=	Frec-b31 / Frec-b24
  palabra = (freq & 524287 ) / 2048;		
  cargarDatos(palabra); //word 2	= 	Frec-b23 / Frec-b16
  palabra = (freq & 2047 ) / 8;      								
  cargarDatos(palabra); //word 3	=	Frec-b15 / Frec-b8
  palabra = (freq & 7    ) * 32;									// b5 = 0.9312 Hz
  cargarDatos(palabra); //word 4	=	Frec-b7  / Frec-b0      // LSB = 0.0291 Hz
  digitalWrite(FQ_UP, HIGH); digitalWrite(FQ_UP, LOW);
  
}

void cargarDatos(int data){
  digitalWrite(D0, bitRead(data,0));
  digitalWrite(D1, bitRead(data,1));
  digitalWrite(D2, bitRead(data,2));
  digitalWrite(D3, bitRead(data,3));
  digitalWrite(D4, bitRead(data,4));
  digitalWrite(D5, bitRead(data,5));
  digitalWrite(D6, bitRead(data,6));
  digitalWrite(D7, bitRead(data,7));
  digitalWrite(W_CLK, HIGH);
  digitalWrite(W_CLK, LOW);
}



