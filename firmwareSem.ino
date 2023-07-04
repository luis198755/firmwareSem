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
unsigned long t = 5000;
// Variables de Programación
unsigned long EscOff  = 0b00000000000000000000000000000000;

unsigned long Esc1    = 0b00000000000000100100100100001001; // Escenario 1

unsigned long Esc1_1  = 0b00000000000000000000000100001001;
unsigned long Esc1_2  = 0b00000000000000100100100100001001;
unsigned long Esc1_3  = 0b00000000000000000000000100001001;
unsigned long Esc1_4  = 0b00000000000000100100100100001001;
unsigned long Esc1_5  = 0b00000000000000010010010100001001;

unsigned long Esc2    = 0b00000000000000001001001100001100; // Escenario 2

unsigned long Esc2_1  = 0b00000000000000001001001000001000;
unsigned long Esc2_2  = 0b00000000000000001001001100001100;
unsigned long Esc2_3  = 0b00000000000000001001001000001000;
unsigned long Esc2_4  = 0b00000000000000001001001100001100;
unsigned long Esc2_5  = 0b00000000000000001001001010001010;

unsigned long Esc3    = 0b00000000000000001001100001100001; // Escenario 3

unsigned long Esc3_1  = 0b00000000000000001001100001000001;
unsigned long Esc3_2  = 0b00000000000000001001100001100001;
unsigned long Esc3_3  = 0b00000000000000001001100001000001;
unsigned long Esc3_4  = 0b00000000000000001001100001100001;
unsigned long Esc3_5  = 0b00000000000000001001100001010001;

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
  
  //interfaceProg(EscOff);

  // Lectura de Modo
  modofunc();
}
//////////////////////*Funciones*/////////////////////////
// Función de interface 32 a 8 bits
void interfaceProg(unsigned long escenario){
  // Variables para separar los 32 bits de entrada en grupos de 8 bits
  unsigned long aux1 = 0b00000000000000000000000011111111;
  unsigned long aux2 = 0b00000000000000001111111100000000;
  unsigned long aux3 = 0b00000000111111110000000000000000;
  unsigned long aux4 = 0b11111111000000000000000000000000;
  // Arreglos para cada grupo de 8 bits
  int arrayAux1[8];
  int arrayAux2[8];
  int arrayAux3[8];
  int arrayAux4[8];
  // Variables para conversión de bits a decimal
  double array1 = 0;
  double array2 = 0;
  double array3 = 0;
  // Conversión de la variable de 32 bits a arreglos de 8 bits
  for (int i=0; i<32; i++){
    if (i < 8){
      arrayAux1[i] = ((bitRead(escenario, i)) && (bitRead(aux1, i)));
    }else if((i >= 8) && (i < 16)){
      arrayAux2[i-8] = ((bitRead(escenario, i)) && (bitRead(aux2, i)) );
    }else if((i >= 16) && (i < 24)){
      arrayAux3[i-16] = ((bitRead(escenario, i)) && (bitRead(aux3, i)) );
    }else if((i >= 24) && (i < 32)){
      arrayAux4[i-24] = ((bitRead(escenario, i)) && (bitRead(aux4, i)) );
    }
  }
  // Arreglos de 8 bits a decimal double
  for (int i=0; i<8; i++){
    array1 = (arrayAux1[i]*(pow(2,i))) + array1;
    array2 = (arrayAux2[i]*(pow(2,i))) + array2;
    array3 = (arrayAux3[i]*(pow(2,i))) + array3;
  }
  // Conversión de decimal double a entero
  int arrayInt1 = int(round(array1));
  int arrayInt2 = int(round(array2));
  int arrayInt3 = int(round(array3));
  // Escritura de los arreglos de 8 bits a Salida
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
            t = 1000;
        }
        break;
  
  } 
}
// Función de modo aislado
void aislado(){
  switch (edoDes){
    case 0: //
        interfaceProg(Esc1);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        interfaceProg(Esc1_1);
        if (flag == 1){
            edoDes = 2;
            flag = 0;
            t = 375;
        }
        break;
    case 2: //
        interfaceProg(Esc1_2);
        if (flag == 1){
            edoDes = 3;
            flag = 0;
            t = 375;
        }
        break;
    case 3: //
        interfaceProg(Esc1_3);
        if (flag == 1){
            edoDes = 4;
            flag = 0;
            t = 375;
        }
        break;
    case 4: //
        interfaceProg(Esc1_4);
        if (flag == 1){
            edoDes = 5;
            flag = 0;
            t = 3000;
        }
        break;
    case 5: //
        interfaceProg(Esc1_5);
        if (flag == 1){
            edoDes = 6;
            flag = 0;
            t = 2000;
        }
        break;
    case 6: //
        interfaceProg(Esc2);
        if (flag == 1){
            edoDes = 7;
            flag = 0;
            t = 375;
        }
        break;
    case 7: //
        interfaceProg(Esc2_1);
        if (flag == 1){
            edoDes = 8;
            flag = 0;
            t = 375;
        }
        break;
    case 8: //
        interfaceProg(Esc2_2);
        if (flag == 1){
            edoDes = 9;
            flag = 0;
            t = 375;
        }
        break;
    case 9: //
        interfaceProg(Esc2_3);
        if (flag == 1){
            edoDes = 10;
            flag = 0;
            t = 375;
        }
        break;
    case 10: //
        interfaceProg(Esc2_4);
        if (flag == 1){
            edoDes = 11;
            flag = 0;
            t = 3000;
        }
        break;
    case 11: //
        interfaceProg(Esc2_5);
        if (flag == 1){
            edoDes = 12;
            flag = 0;
            t = 2000;
        }
        break;
    case 12: //
        interfaceProg(Esc3);
        if (flag == 1){
            edoDes = 13;
            flag = 0;
            t = 375;
        }
        break;
    case 13: //
        interfaceProg(Esc3_1);
        if (flag == 1){
            edoDes = 14;
            flag = 0;
            t = 375;
        }
        break;
    case 14: //
        interfaceProg(Esc3_2);
        if (flag == 1){
            edoDes = 15;
            flag = 0;
            t = 375;
        }
        break;
    case 15: //
        interfaceProg(Esc3_3);
        if (flag == 1){
            edoDes = 16;
            flag = 0;
            t = 375;
        }
        break;
    case 16: //
        interfaceProg(Esc3_4);
        if (flag == 1){
            edoDes = 17;
            flag = 0;
            t = 3000;
        }
        break;
    case 17: //
        interfaceProg(Esc3_5);
        if (flag == 1){
            edoDes = 0;
            flag = 0;
            t = 5000;
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
void ledWrite(int Reg1, int Reg2, int Reg3){
   shiftOut(pinData, pinClock, LSBFIRST, Reg3);
   shiftOut(pinData, pinClock, LSBFIRST, Reg2);
   shiftOut(pinData, pinClock, LSBFIRST, Reg1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}