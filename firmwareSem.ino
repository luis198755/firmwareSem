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
// Arreglos de programación
unsigned long prog[30] = {
                            0b10010010010000100100000000000000, 
                            0b00000000010000100100000000000000,
                            0b10010010010000100100000000000000, 
                            0b00000000010000100100000000000000, 
                            0b10010010010000100100000000000000, 
                            0b00000000010000100100000000000000, 
                            0b10010010010000100100000000000000, 
                            0b00000000010000100100000000000000, 
                            0b10010010010000100100000000000000,
                            0b01001001010000100100000000000000,

                            0b00100100110000110000000000000000,
                            0b00100100100000100000000000000000,
                            0b00100100110000110000000000000000,
                            0b00100100100000100000000000000000,
                            0b00100100110000110000000000000000,
                            0b00100100100000100000000000000000,
                            0b00100100110000110000000000000000,
                            0b00100100100000100000000000000000,
                            0b00100100110000110000000000000000,
                            0b00100100101000101000000000000000,

                            0b00100110000110000100000000000000,
                            0b00100110000100000100000000000000,
                            0b00100110000110000100000000000000,
                            0b00100110000100000100000000000000,
                            0b00100110000110000100000000000000,
                            0b00100110000100000100000000000000,
                            0b00100110000110000100000000000000,
                            0b00100110000100000100000000000000,
                            0b00100110000110000100000000000000,
                            0b00100110000101000100000000000000
};
unsigned long time[30] = {
                            10000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000,
                            10000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000,
                            10000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000
};

// Declarar una variable para almacenar el tiempo actual
unsigned long tiempo;

unsigned seg = 1;

// Declarar una variable para almacenar el índice del arreglo
int indice = 0;

// Variables de Programación
unsigned long EscOn   = 0b11111111111111111111111111111111; // Todo Apagado
unsigned long EscOff  = 0b00000000000000000000000000000000; // Todo Encendido
//////////////////////////////////////*Programación*//////////////////////////////////////////
unsigned long esce1   = 0b10010010010000100100000000000000; // ***Escenario 1***
unsigned long esce1_1 = 0b00000000010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_2 = 0b10010010010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_3 = 0b00000000010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_4 = 0b10010010010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_5 = 0b00000000010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_6 = 0b10010010010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_7 = 0b00000000010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_8 = 0b10010010010000100100000000000000; // Transición de Verde a Ambar
unsigned long esce1_9 = 0b01001001010000100100000000000000; // Tiempo de ambar
//////////////////////////////////////////////////////////////////////////////////////////////
unsigned long esce2   = 0b00100100110000110000000000000000; // ***Escenario 2***
unsigned long esce2_1 = 0b00100100100000100000000000000000; // Transición de Verde a Ambar
unsigned long esce2_2 = 0b00100100110000110000000000000000; // Transición de Verde a Ambar
unsigned long esce2_3 = 0b00100100100000100000000000000000; // Transición de Verde a Ambar
unsigned long esce2_4 = 0b00100100110000110000000000000000; // Transición de Verde a Ambar
unsigned long esce2_5 = 0b00100100100000100000000000000000; // Transición de Verde a Ambar
unsigned long esce2_6 = 0b00100100110000110000000000000000; // Transición de Verde a Ambar
unsigned long esce2_7 = 0b00100100100000100000000000000000; // Transición de Verde a Ambar
unsigned long esce2_8 = 0b00100100110000110000000000000000; // Transición de Verde a Ambar
unsigned long esce2_9 = 0b00100100101000101000000000000000; // Tiempo de ambar
//////////////////////////////////////////////////////////////////////////////////////////////
unsigned long esce3   = 0b00100110000110000100000000000000; // ***Escenario 3***
unsigned long esce3_1 = 0b00100110000100000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_2 = 0b00100110000110000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_3 = 0b00100110000100000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_4 = 0b00100110000110000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_5 = 0b00100110000100000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_6 = 0b00100110000110000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_7 = 0b00100110000100000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_8 = 0b00100110000110000100000000000000; // Transición de Verde a Ambar
unsigned long esce3_9 = 0b00100110000101000100000000000000; // Tiempo de ambar

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

  Serial.println(prog[0]);
  // Obtener el tiempo actual en milisegundos
  tiempo = millis();
}
/////////////*Void Loop*/////////////
void loop() {
  // Declaración de variables locales
  // Función de tiempo real
  //tiempoReal();
  // Lectura de Modo
  //modofunc();
  
  // Si han pasado más de 1000 milisegundos desde el último tiempo
  if (millis() - tiempo > (time[indice])) {
    // Imprimir el elemento del arreglo correspondiente al índice
    Serial.println(prog[indice+1]);

    // Incrementar el índice en uno
    indice++;

    // Si el índice llega al final del arreglo, reiniciarlo a cero
    if (indice == 30) {
      indice = 0;
    }

    // Actualizar el tiempo actual
    tiempo = millis();
  }
}
//////////////////////*Funciones*/////////////////////////
// Función de interface 32 a 8 bits - en base a variables
void interfaceProg(unsigned long var32Bits) {
    unsigned char var1 = (var32Bits & 0xFF);
    unsigned char var2 = ((var32Bits >> 8) & 0xFF);
    unsigned char var3 = ((var32Bits >> 16) & 0xFF);
    unsigned char var4 = ((var32Bits >> 24) & 0xFF);

    ledWrite(var1,var2,var3,var4);
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
        interfaceProg(EscOff);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 1000;
        }
        break;
    case 1: //
        interfaceProg(EscOn);
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
        interfaceProg(esce1);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        interfaceProg(esce1_1);
        if (flag == 1){
            edoDes = 2;
            flag = 0;
            t = 375;
        }
        break;
    case 2: //
        interfaceProg(esce1_2);
        if (flag == 1){
            edoDes = 3;
            flag = 0;
            t = 375;
        }
        break;
    case 3: //
        interfaceProg(esce1_3);
        if (flag == 1){
            edoDes = 4;
            flag = 0;
            t = 375;
        }
        break;
    case 4: //
        interfaceProg(esce1_4);
        if (flag == 1){
            edoDes = 5;
            flag = 0;
            t = 375;
        }
        break;
    case 5: //
        interfaceProg(esce1_5);
        if (flag == 1){
            edoDes = 6;
            flag = 0;
            t = 375;
        }
        break;
    case 6: //
        interfaceProg(esce1_6);
        if (flag == 1){
            edoDes = 7;
            flag = 0;
            t = 375;
        }
        break;
    case 7: //
        interfaceProg(esce1_7);
        if (flag == 1){
            edoDes = 8;
            flag = 0;
            t = 375;
        }
        break;
    case 8: //
        interfaceProg(esce1_8);
        if (flag == 1){
            edoDes = 9;
            flag = 0;
            t = 3000;
        }
        break;
    case 9: //
        interfaceProg(esce1_9);
        if (flag == 1){
            edoDes = 10;
            flag = 0;
            t = 10000;
        }
        break;
    case 10: //
        interfaceProg(esce2);
        if (flag == 1){
            edoDes = 11;
            flag = 0;
            t = 375;
        }
        break;
    case 11: //
        interfaceProg(esce2_1);
        if (flag == 1){
            edoDes = 12;
            flag = 0;
            t = 375;
        }
        break;
    case 12: //
        interfaceProg(esce2_2);
        if (flag == 1){
            edoDes = 13;
            flag = 0;
            t = 375;
        }
        break;
    case 13: //
        interfaceProg(esce2_3);
        if (flag == 1){
            edoDes = 14;
            flag = 0;
            t = 375;
        }
        break;
    case 14: //
        interfaceProg(esce2_4);
        if (flag == 1){
            edoDes = 15;
            flag = 0;
            t = 375;
        }
        break;
    case 15: //
        interfaceProg(esce2_5);
        if (flag == 1){
            edoDes = 16;
            flag = 0;
            t = 375;
        }
        break;
    case 16: //
        interfaceProg(esce2_6);
        if (flag == 1){
            edoDes = 17;
            flag = 0;
            t = 375;
        }
        break;
    case 17: //
        interfaceProg(esce2_7);
        if (flag == 1){
            edoDes = 18;
            flag = 0;
            t = 375;
        }
        break;
    case 18: //
        interfaceProg(esce2_8);
        if (flag == 1){
            edoDes = 19;
            flag = 0;
            t = 3000;
        }
        break;
    case 19: //
        interfaceProg(esce2_9);
        if (flag == 1){
            edoDes = 20;
            flag = 0;
            t = 10000;
        }
        break;
    case 20: //
        interfaceProg(esce3);
        if (flag == 1){
            edoDes = 21;
            flag = 0;
            t = 375;
        }
        break;
    case 21: //
        interfaceProg(esce3_1);
        if (flag == 1){
            edoDes = 22;
            flag = 0;
            t = 375;
        }
        break;
    case 22: //
        interfaceProg(esce3_2);
        if (flag == 1){
            edoDes = 23;
            flag = 0;
            t = 375;
        }
        break;
    case 23: //
        interfaceProg(esce3_3);
        if (flag == 1){
            edoDes = 24;
            flag = 0;
            t = 375;
        }
        break;
    case 24: //
        interfaceProg(esce3_4);
        if (flag == 1){
            edoDes = 25;
            flag = 0;
            t = 375;
        }
        break;
    case 25: //
        interfaceProg(esce3_5);
        if (flag == 1){
            edoDes = 26;
            flag = 0;
            t = 375;
        }
        break;
    case 26: //
        interfaceProg(esce3_6);
        if (flag == 1){
            edoDes = 27;
            flag = 0;
            t = 375;
        }
        break;
    case 27: //
        interfaceProg(esce3_7);
        if (flag == 1){
            edoDes = 28;
            flag = 0;
            t = 375;
        }
        break;
    case 28: //
        interfaceProg(esce3_8);
        if (flag == 1){
            edoDes = 29;
            flag = 0;
            t = 3000;
        }
        break;
    case 29: //
        interfaceProg(esce3_9);
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
void ledWrite(char Reg4, char Reg3, char Reg2, char Reg1){
   shiftOut(pinData, pinClock, LSBFIRST, Reg4);
   shiftOut(pinData, pinClock, LSBFIRST, Reg3);
   shiftOut(pinData, pinClock, LSBFIRST, Reg2);
   shiftOut(pinData, pinClock, LSBFIRST, Reg1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}