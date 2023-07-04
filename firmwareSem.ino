// Librerías
////*Definición de pines de McU para control de registros*///
int pinData  = 2;
int pinLatch = 3;
int pinClock = 4;
////*Definición de pines de McU de entrada para pruebas*///
#define CantidadBotonEntrada 4
int botonEntrada[CantidadBotonEntrada] = {5, 6, 7, 8};

// Variables Globales
//Variables de la máquina de estado
int Estado = 0;
int edoDes = 0;
int flag = 0;
int modo = 0;
//Variable de control del Timer (millis)
unsigned long previousTime = 0;
unsigned long te = 375;
unsigned long t = te;
// Variables de Programación
unsigned long EscOff = 0b00000000000000000000000000000000;
unsigned long Esc1   = 0b10000000100000001000000010000000;
unsigned long Esc2   = 0b00000000000011000000000000011000;
unsigned long Esc3   = 0b00000000000000000000000000000000;

unsigned long EscOn  = 0b11111111111111111111111111111111;



//////////////*Void Setup*/////////////
void setup() {
  //Inicialización del puerto serial del mCU
  Serial.begin(9600);

  //Designación de  pines del mCU como entrada y salida
  ////////////*Definición de pines como salida*////////////
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  ////////////*Definición de pines como entrada*////////////
  for (int i=0; i<CantidadBotonEntrada; i++){
    pinMode(botonEntrada[i], INPUT);
  }
  /////////////////////////////////////////////////////////

  // Apagado de todas las fases
  fasesOff(); delay(2000);
}
/////////////*Void Loop*/////////////
void loop() {
  // Declaración de variables locales
  // Función de tiempo real
  tiempoReal();
  
  interfaceProg(EscOff);

  // Lectura de Modo
  modofunc();
}
//////////////////////*Funciones*/////////////////////////
// Función de interface 32 a 8 bits
void interfaceProg(unsigned long escenario){
  unsigned long aux1 = 0b00000000000000000000000011111111;
  unsigned long aux2 = 0b00000000000000001111111100000000;
  unsigned long aux3 = 0b00000000111111110000000000000000;
  unsigned long aux4 = 0b11111111000000000000000000000000;

  unsigned bit, bitAux1, bitAux2, bitAux3, bitAux4, bitEsc;
  int arrayAux1[8];
  int arrayAux2[8];
  int arrayAux3[8];
  int arrayAux4[8];
  int arrayAux5[8];

  double array1 = 0;
  double array2 = 0;
  double array3 = 0;

  for (int i=0; i<32; i++){
    bitAux1 = bitRead(aux1, i);
    bitAux2 = bitRead(aux2, i);
    bitAux3 = bitRead(aux3, i);
    bitAux4 = bitRead(aux4, i);
    bitEsc = bitRead(escenario, i);
    //Serial.print("Array 1");
    if (i < 8){
      arrayAux1[i] = (bitEsc && bitAux1);
    }else if((i >= 8) && (i < 16)){
      arrayAux2[i-8] = (bitEsc && bitAux2 );
    }else if((i >= 16) && (i < 24)){
      arrayAux3[i-16] = (bitEsc && bitAux3 );
    }else if((i >= 24) && (i < 32)){
      arrayAux4[i-24] = (bitEsc && bitAux4 );
    }
  }

  /*
  Serial.println("Array 1");
  for (int i=0; i<8; i++){
    Serial.print(arrayAux1[i]);
  }
  Serial.println("");
  Serial.println("Array 2");
  for (int i=0; i<8; i++){
    Serial.print(arrayAux2[i]);
  }
  Serial.println("");
  Serial.println("Array 3");
  for (int i=0; i<8; i++){
    Serial.print(arrayAux3[i]);
  }
  Serial.println("");
  Serial.println("Array 4");
  for (int i=0; i<8; i++){
    Serial.print(arrayAux4[i]);
  }*/

  for (int i=0; i<8; i++){
    array1 = (arrayAux1[i]*(pow(2,i))) + array1;
    array2 = (arrayAux2[i]*(pow(2,i))) + array2;
    array3 = (arrayAux3[i]*(pow(2,i))) + array3;
  }
  
  int arrayInt1 = int(round(array1));
  int arrayInt2 = int(round(array2));
  int arrayInt3 = int(round(array3));
  /*
  Serial.println("Array 1");
  Serial.print(array1); Serial.println(arrayInt1);
  Serial.println("Array 2");
  Serial.print(array2); Serial.println(arrayInt2);
  Serial.println("Array 3");
  Serial.print(array3); Serial.println(arrayInt3);*/
  
  

  ledWrite(arrayInt3,arrayInt2,arrayInt1);
  //delay(5000);
}
//Función de Estados
void ActualizarSemaforo() {
  //Estados
  switch (Estado){
    //Estado Inicial
    case 0:
      edo0();
      break;
    //Estado 1
    case 1:
      edo1();
      break;
    //Estado 2
    case 2:
      edo2();
      break;
    //Estado 3
    case 3:
      edo3();
      break;
    //Estado 4
    case 4:
      edo4();
      break;
    //Estado 5
    case 5:
      edo5();
      break;
    //Estado 6
    case 6:
      edo6();
      break;
    default:
      Estado = 0;
  }
}
// Apagar todas las fases
void fasesOff(){
    interfaceProg(EscOff); 
}
// Estado 0
void edo0(){
  
}
// Estado 1
void edo1(){
  
}
// Estado 2
void edo2(){
  
}
// Estado 3
void edo3(){
  
}
// Estado 4
void edo4(){
  
}
// Estado 5
void edo5(){
  
}
// Estado 6
void edo6(){
  
}
// Función de Modo
void modofunc(){
  int buttonState[CantidadBotonEntrada];
  for (int i=0; i<CantidadBotonEntrada; i++){
    buttonState[i] = digitalRead(botonEntrada[i]);
    if (buttonState[i]==HIGH && i==0){
      modo = 0;
    }
    else if (buttonState[i]==HIGH && i==1){
      modo = 1;
    }else if (buttonState[i]==HIGH && i==2){
      modo = 2;
    }else if (buttonState[i]==HIGH && i==3){
      modo = 3;
    }
  }
  // Modos de funcionamiento
  switch (modo){
    case 0: //Aislado
        //Actualiza la máquina de estados
        aislado();
        break;
    case 1: //Manual
        manual();
        break;
    case 2: //Destello
        destello();
        break;
    case 3: //Sincronizado
        sincronizado();
        break;
  } 
}
// Función de tiempo real
void tiempoReal(){
  //Variable de tiempo actual del timer
  unsigned long currentTime = millis();
  //Revisión de tiempo cumplido
  if ( (currentTime - previousTime >= t) ){
    previousTime = currentTime;
    flag = 1;
    /*Serial.print("Estado: ");
    Serial.println(Estado);*/
  }
}
// Función de modo manual
void manual(){
  switch (edoDes){
    case 0: //
        interfaceProg(Esc1);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 2000;
        }
        break;
    case 1: //
        interfaceProg(Esc2);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 2000;
        }
        break;
  } 
}
// Función de modo aislado
void aislado(){
    interfaceProg(EscOn);
}
// Función de destello
void destello(){
  switch (edoDes){
    case 0: //
        interfaceProg(EscOff); //delay(375);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        interfaceProg(EscOn);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 375;
        }
        break;
  } 
}
// Función de sincronización
void sincronizado(){
  switch (edoDes){
    case 0: //
        interfaceProg(EscOff); //delay(375);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 200;
        }
        break;
    case 1: //
        interfaceProg(EscOn); //delay(375);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 200;
        }
        break;
  }
}
////*Función de interface de Registros de Desplazamiento*////
void ledWrite(int Reg1, int Reg2, int Reg3){
   shiftOut(pinData, pinClock, LSBFIRST, Reg3);
   shiftOut(pinData, pinClock, LSBFIRST, Reg2);
   shiftOut(pinData, pinClock, LSBFIRST, Reg1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}