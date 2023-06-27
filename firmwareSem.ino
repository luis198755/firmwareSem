// Librerías

// Variables Globales

//////////////*Void Setup*/////////////
void setup() {
  //Inicialización del puerto serial del mCU
  
  //Designación de  pines del mCU como entrada y salida

  // Apagado de todas las fases
}
/////////////*Void Loop*/////////////
void loop() {
  // Declaración de variables locales
  
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
tiempoReal(){

}
// Función de modo manual
void manual(){

}
// Función de destello
void destello(){
// Función de sincronización
}
void sincronizado(){

}