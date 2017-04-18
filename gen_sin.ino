int W_CLK = 2;
int FQ_UP = 3;
int RESET = 4;
int D0 = 5, D1 = 6, D2 = 7, D3 = 8, D4 = 9, D5 = 10, D6 = 11, D7 = 12;
int palabra, resto, leer, i;
long frec;
int SW = 13, POTE = 2;


void setup() {
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UP, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(D0, OUTPUT); pinMode(D1, OUTPUT); pinMode(D2, OUTPUT); pinMode(D3, OUTPUT); pinMode(D4, OUTPUT); pinMode(D5, OUTPUT); pinMode(D6, OUTPUT); pinMode(D7, OUTPUT);
  pinMode(SW, INPUT);
  digitalWrite(W_CLK, LOW);
  digitalWrite(FQ_UP, LOW);
  digitalWrite(RESET, LOW);
  
}

void loop() {
  //frecuency(8393); delay(5000); frecuency (168036); delay(5000);
	//		   1M							  20M
  frec = analogRead(POTE);
  if (frec>969) frec = 1023;
  for (i=0;i<20;i++) 
	  if((frec>=51*i)&&(frec<51*(i+1))) 
		  frec = 51*i;
  frec = frec * 156 + 8393;
  frecuency(frec);
  delay(100);
}

void frecuency(long freq){
  palabra = 0;
  digitalWrite(RESET, HIGH); delay(1); digitalWrite(RESET, LOW);
  cargarDatos(palabra); //word 0    =   Fase y control
  palabra = freq / 4096;
  cargarDatos(palabra); //word 1	=	Frec-b31 / Frec-b24
  palabra = (freq & 4095)/16;		
  cargarDatos(palabra); //word 2	= 	Frec-b23 / Frec-b16
  palabra = (freq & 15) * 16;      								// elevo al bit 12 (= * 4096)
  cargarDatos(palabra); //word 3	=	Frec-b15 / Frec-b8
  palabra = 0;
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



