// Librerías
////*Definición de pindes de McU para control de registros*///
int pinData  = 2;
int pinLatch = 3;
int pinClock = 4;

// Variables Globales
//Variables de la máquina de estado
int Estado = 0;
int flag = 0;
int modo = 2;
//Variable de control del Timer (millis)
unsigned long previousTime = 0;
unsigned long te = 1000;
unsigned long t = te;
//////////////*Void Setup*/////////////
void setup() {
  //Inicialización del puerto serial del mCU

  //Designación de  pines del mCU como entrada y salida
  ////////////*Definición de pines como salida*////////////
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  /////////////////////////////////////////////////////////

  // Apagado de todas las fases
}
/////////////*Void Loop*/////////////
void loop() {
  // Declaración de variables locales
  //Variable de tiempo actual del timer
  unsigned long currentTime = millis();

  //Revisión de tiempo cumplido
  if ( (currentTime - previousTime >= t) ){
    previousTime = currentTime;
    flag = 1;
    Serial.print("Estado: ");
    Serial.println(Estado);
  }
  
  // Función de tiempo real
  tiempoReal();
  
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
//////////////////////*Funciones*/////////////////////////
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
// Función de tiempo real
void tiempoReal(){

}
// Función de modo manual
void manual(){

}
// Función de modo aislado
void aislado(){
	
}
// Función de destello
void destello(){
    switch (edoDes){
    case 0: //
        ledWrite(B01001001,B00100100,B10010010); delay(375);
        if (flag == 1){
            edoDes = 1;
            flag = 0;
            t = 375;
        }
        break;
    case 1: //
        ledWrite(B00000000,B00000000,B00000000); delay(375);
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

}
////*Función de interface de Registros de Desplazamiento*////
void ledWrite(int Reg1, int Reg2, int Reg3){
   shiftOut(pinData, pinClock, LSBFIRST, Reg3);
   shiftOut(pinData, pinClock, LSBFIRST, Reg2);
   shiftOut(pinData, pinClock, LSBFIRST, Reg1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}