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
unsigned long t = 10000;
// Variables de Programación
int escOff[24] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0}; // Todo Apagado
int escOn[24] =   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0}; // Todo Encendido
//////////////////////////////////////*Programación*//////////////////////////////////////////
int esc1[24] =    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // ***Escenario 1***
int esc1_1[24] =  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_2[24] =  {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_3[24] =  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_4[24] =  {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_5[24] =  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_6[24] =  {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_7[24] =  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_8[24] =  {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc1_9[24] =  {0,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
//////////////////////////////////////////////////////////////////////////////////////////////
int esc2[24] =    {0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0, 0,0,0,0,0,0}; // ***Escenario 2***
int esc2_1[24] =  {0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_2[24] =  {0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_3[24] =  {0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_4[24] =  {0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_5[24] =  {0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_6[24] =  {0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_7[24] =  {0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_8[24] =  {0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0, 0,0,0,0,0,0}; // Transisción de Verde
int esc2_9[24] =  {0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0, 0,0,0,0,0,0}; // Tiempo de ambar
//////////////////////////////////////////////////////////////////////////////////////////////
int esc3[24] =    {0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_1[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_2[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_3[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_4[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_5[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_6[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_7[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_8[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1, 0,0,0,0,0,0}; // Transisción de Verde
int esc3_9[24] =  {0,0,1,0,0,1,1,0,0,0,0,1,0,1,0,0,0,1, 0,0,0,0,0,0}; // Tiempo de ambar
//////////////////////////////////////////////////////////////////////////////////////////////
int outputArray1[8];
int outputArray2[8];
int outputArray3[8];
int outputArray4[8];
int size = sizeof(outputArray1) / sizeof(outputArray1[0]);

///////////////////////////////////*FIN Programación*//////////////////////////////////////////

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

  // Lectura de Modo
  modofunc();
}
//////////////////////*Funciones*/////////////////////////
// Función de interface 32 a 8 bits
void interfaceProg2(int* inputArray, int* outputArray1, int* outputArray2, int* outputArray3, int size) {
    for (int i = 0; i < 8; i++) {
        outputArray1[i] = inputArray[i];
        outputArray2[i] = inputArray[i + 8];
        outputArray3[i] = inputArray[i + 16];
    }
    /*
  	Serial.println(size);
  	Serial.println("");
    Serial.println(binaryArrayToInt(outputArray1,size));
  	Serial.println(binaryArrayToInt(outputArray2,size));
  	Serial.println(binaryArrayToInt(outputArray3,size));*/
  	// Escritura de los arreglos de 8 bits a Salida
  	int dig0 = binaryArrayToInt(outputArray1,size);
  	int dig1 = binaryArrayToInt(outputArray2,size);
    int dig2 = binaryArrayToInt(outputArray3,size);
  	
    ledWrite(dig0,dig1,dig2);
    
}

unsigned long int binaryArrayToInt(int* binaryArray, int size) {
  unsigned long int result = 0;
  for (int i = 0; i < size; i++) {
    result = result * 2 + binaryArray[i];
  }
  return result;
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
    interfaceProg2(escOff,outputArray1,outputArray2,outputArray3,size); 
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
      edoDes = 0;
      t = 100;
    }
    else if (buttonState[i]==HIGH && i==1){
      modo = 1;
      edoDes = 0;
      t = 100;
    }else if (buttonState[i]==HIGH && i==2){
      modo = 2;
      edoDes = 0;
      t = 100;
    }else if (buttonState[i]==HIGH && i==3){
      modo = 3;
      edoDes = 0;
      t = 100;
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
        interfaceProg2(escOff,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 1000;
        }
        break;
    case 1: //
        interfaceProg2(escOn,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 1000;
        }
        break;
  
  } 
}
// Función de modo aislado
void aislado(){
  switch (edoDes){
    case 0: //
        interfaceProg2(esc1,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        interfaceProg2(esc1_1,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 2;
            flag = 0;
            t = 375;
        }
        break;
    case 2: //
        interfaceProg2(esc1_2,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 3;
            flag = 0;
            t = 375;
        }
        break;
    case 3: //
        interfaceProg2(esc1_3,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 4;
            flag = 0;
            t = 375;
        }
        break;
    case 4: //
        interfaceProg2(esc1_4,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 5;
            flag = 0;
            t = 375;
        }
        break;
    case 5: //
        interfaceProg2(esc1_5,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 6;
            flag = 0;
            t = 375;
        }
        break;
    case 6: //
        interfaceProg2(esc1_6,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 7;
            flag = 0;
            t = 375;
        }
        break;
    case 7: //
        interfaceProg2(esc1_7,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 8;
            flag = 0;
            t = 375;
        }
        break;
    case 8: //
        interfaceProg2(esc1_8,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 9;
            flag = 0;
            t = 3000;
        }
        break;
    case 9: //
        interfaceProg2(esc1_9,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 10;
            flag = 0;
            t = 10000;
        }
        break;
    case 10: //
        interfaceProg2(esc2,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 11;
            flag = 0;
            t = 375;
        }
        break;
    case 11: //
        interfaceProg2(esc2_1,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 12;
            flag = 0;
            t = 375;
        }
        break;
    case 12: //
        interfaceProg2(esc2_2,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 13;
            flag = 0;
            t = 375;
        }
        break;
    case 13: //
        interfaceProg2(esc2_3,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 14;
            flag = 0;
            t = 375;
        }
        break;
    case 14: //
        interfaceProg2(esc2_4,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 15;
            flag = 0;
            t = 375;
        }
        break;
    case 15: //
        interfaceProg2(esc2_5,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 16;
            flag = 0;
            t = 375;
        }
        break;
    case 16: //
        interfaceProg2(esc2_6,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 17;
            flag = 0;
            t = 375;
        }
        break;
    case 17: //
        interfaceProg2(esc2_7,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 18;
            flag = 0;
            t = 375;
        }
        break;
    case 18: //
        interfaceProg2(esc2_8,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 19;
            flag = 0;
            t = 3000;
        }
        break;
    case 19: //
        interfaceProg2(esc2_9,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 20;
            flag = 0;
            t = 10000;
        }
        break;
    case 20: //
        interfaceProg2(esc3,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 21;
            flag = 0;
            t = 375;
        }
        break;
    case 21: //
        interfaceProg2(esc3_1,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 22;
            flag = 0;
            t = 375;
        }
        break;
    case 22: //
        interfaceProg2(esc3_2,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 23;
            flag = 0;
            t = 375;
        }
        break;
    case 23: //
        interfaceProg2(esc3_3,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 24;
            flag = 0;
            t = 375;
        }
        break;
    case 24: //
        interfaceProg2(esc3_4,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 25;
            flag = 0;
            t = 375;
        }
        break;
    case 25: //
        interfaceProg2(esc3_5,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 26;
            flag = 0;
            t = 375;
        }
        break;
    case 26: //
        interfaceProg2(esc3_6,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 27;
            flag = 0;
            t = 375;
        }
        break;
    case 27: //
        interfaceProg2(esc3_7,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 28;
            flag = 0;
            t = 375;
        }
        break;
    case 28: //
        interfaceProg2(esc3_8,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 29;
            flag = 0;
            t = 3000;
        }
        break;
    case 29: //
        interfaceProg2(esc3_9,outputArray1,outputArray2,outputArray3,size);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 10000;
        }
        break;
  } 
}
// Función de destello
void destello(){
  switch (edoDes){
    case 0: //
        interfaceProg2(escOff,outputArray1,outputArray2,outputArray3,size); //delay(375);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        interfaceProg2(escOn,outputArray1,outputArray2,outputArray3,size);
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
        interfaceProg2(escOff,outputArray1,outputArray2,outputArray3,size); //delay(375);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 200;
        }
        break;
    case 1: //
        interfaceProg2(escOn,outputArray1,outputArray2,outputArray3,size); //delay(375);
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