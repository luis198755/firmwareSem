// Librerías
////*Definición de pines de McU para control de registros*///
int pinData  = 2;
int pinLatch = 3;
int pinClock = 4;
int pinOE = 5;
////*Definición de pines de McU de entrada para pruebas*///
#define CantidadBotonEntrada 4
int botonEntrada[CantidadBotonEntrada] = {6, 7, 8, 9};
int estadoBoton[CantidadBotonEntrada] = {LOW, LOW, LOW, LOW};

int estadoBoton1 = LOW;    // Estado actual del primer botón
int estadoBoton2 = LOW;    // Estado actual del segundo botón

// Variables Globales
//Variables de la máquina de estado
int Estado = 0;
int edoDes = 0;
int flag = 1;
int modo = 0;
//Variable de control del Timer (millis)
unsigned long previousTime = 0;
unsigned long te = 375;
unsigned long t = 10000;
// Arreglos de programación
unsigned long prog0[31] = {
                            0b00000000000000000000000000000000, // ***Escenario 1***
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b01001001010000100100000000000000, // Tiempo de ambar  

                            0b00100100110000110000000000000000, // ***Escenario 2***
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100101000101000000000000000, // Tiempo de ambar  

                            0b00100110000110000100000000000000, // ***Escenario 3***
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000101000100000000000000  // Tiempo de ambar  
};     

int longitud = sizeof(prog0) / sizeof(prog0[0]);

unsigned long time0[31] = {  
                            0,

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

                            12000,
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

unsigned long prog1[3] = {
                            0b00000000000000000000000000000000,
                            0b00000000000000000000000000000000,
                            0b00100100100100100100000000000000 
};    

unsigned long time1[3] = {
                            0,
                            375,
                            375 
};     

int longitud1 = sizeof(prog1) / sizeof(prog1[0]);

// Variables de Programación
unsigned long EscOn   = 0b11111111111111111111111111111111; // Todo Apagado
unsigned long EscOff  = 0b00000000000000000000000000000000; // Todo Encendido
///////////////////////////////////*FIN Programación*//////////////////////////////////////////

// Declarar una variable para almacenar el tiempo actual
unsigned long tiempo;

unsigned seg = 1;

// Declarar una variable para almacenar el índice del arreglo
int indice = 0;

//////////////*Void Setup*/////////////
void setup() {
  //Inicialización del puerto serial del mCU
  Serial.begin(9600);

  //Designación de  pines del mCU como entrada y salida
  ////////////*Definición de pines como salida*////////////
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinOE, OUTPUT);

  ////////////*Desactivar Registros*////////////////////////
  digitalWrite(pinOE, HIGH);
  ////////////*Activar Registros*////////////////////////
  digitalWrite(pinOE, LOW);
  // Apagado de todas las fases
  ledWrite(0xff,0xff,0xff,0xff);
  //interfaceProg(EscOff); 
  delay(2000);
  
  ////////////*Definición de pines como entrada*////////////
  for (int i=0; i<CantidadBotonEntrada; i++){
    pinMode(botonEntrada[i], INPUT_PULLUP);
  }
  /////////////////////////////////////////////////////////

  // Obtener el tiempo actual en milisegundos
  //tiempo = millis();
}
/////////////*Void Loop*/////////////
void loop() {
  // Declaración de variables locales
  ////////////*Activar Registros*////////////////////////
  digitalWrite(pinOE, LOW);
  // Función de tiempo real
  //tiempoReal();
  // Lectura de Modo
  modofunc();

}
//////////////////////*Funciones*/////////////////////////
// Función de interface 32 a 8 bits - en base a variables
void interfaceProg(unsigned long var32Bits) {
    unsigned char var1 = (var32Bits & 0xFF);// ^ 0xFF;
    unsigned char var2 = ((var32Bits >> 8) & 0xFF);// ^ 0xFF;
    unsigned char var3 = ((var32Bits >> 16) & 0xFF);// ^ 0xFF;
    unsigned char var4 = ((var32Bits >> 24) & 0xFF);// ^ 0xFF;

    ledWrite(var1,var2,var3,var4);
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
  int lecturaBoton[CantidadBotonEntrada];
  for (int i=0; i<CantidadBotonEntrada; i++){
    lecturaBoton[i] = digitalRead(botonEntrada[i]);

    if (lecturaBoton[i]==LOW && i==0 && estadoBoton[i] == LOW){
      modo = 0; // Aislado
      indice = 0;
      Serial.println("Modo: Aislado");
      estadoBoton[i] = HIGH;
      previousTime = millis();
    }
    else if (lecturaBoton[i]==HIGH && i==0){
      estadoBoton[i] = LOW;
    }

    if (lecturaBoton[i]==LOW && i==1 && estadoBoton[i] == LOW){
      modo = 1; // Manual
      indice++;
      Serial.println("Modo: Manual");
      Serial.print("Indice: ");
      Serial.print(indice);
      Serial.println("");
      estadoBoton[i] = HIGH;
      previousTime = millis();
    }
    else if (lecturaBoton[i]==HIGH && i==1){
      estadoBoton[i] = LOW;
    }

    if (lecturaBoton[i]==LOW && i==2 && estadoBoton[i] == LOW){
      modo = 2; // Destello
      indice = 0;
      Serial.println("Modo: Destello");
      estadoBoton[i] = HIGH;
      previousTime = millis();
    }
    else if (lecturaBoton[i]==HIGH && i==2){
      estadoBoton[i] = LOW;
    }

    if (lecturaBoton[i]==LOW && i==3 && estadoBoton[i] == LOW){
      modo = 3; // Sicronizado
      indice = 0;
      Serial.println("Modo: Sicronizado");
      estadoBoton[i] = HIGH;
      previousTime = millis();
    }
    else if (lecturaBoton[i]==HIGH && i==3){
      estadoBoton[i] = LOW;
    }
    
    
  }
  // Modos de funcionamiento
  switch (modo){
    case 0: //Aislado
        //Actualiza la máquina de estados
        aislado();
        break;
    case 1: //Manual
        aislado();
        break;
    case 2: //Destello
        destello();
        break;
    case 3: //Sincronizado
        sincronizado();
        break;
  } 
}

// Función de modo aislado
void aislado(){
  tiempoReal(time0, prog0, longitud);
}
// Función de modo manual
void manual(){
  tiempoReal(time0, prog0, longitud);
}
// Función de destello
void destello(){
  tiempoReal(time1, prog1, longitud1);
}
// Función de sincronización
void sincronizado(){
  
}
// Función de tiempo real
unsigned long tiempoReal(unsigned long* time, unsigned long* prog, int longitud){
  //Variable de tiempo actual del timer
  //Revisión de tiempo cumplido
  if ( (millis() - previousTime >= *(time + indice)) ){
    previousTime = millis();

    // Incrementar el índice en uno
    indice++;
    // Si el índice llega al final del arreglo, reiniciarlo a cero
    if (indice != longitud) {
        // Ejecución de la Programación
        interfaceProg(*(prog + indice));
    }
    else {
        indice = 0;
    }
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