
/*
 * UNIVERSIDAD TECNICA DEL NORTE
 * FACULTAD DE INGENIERIA EN CIENCIAS APLICADAS
 * SISTEMAS EMBEBIDOS
 * STEVEN FLORES
 * 5to Nivel;
 * CAP IV: 
 * Deber 5: Juego con motor
 *          attachInterrupt(0,metodo,activacion )    Funcion para interrupcion por boton
 *          variable.servo(pin)              Seleccion pin para servo motor
 *          Serial.begin(9600)              Inicia la terminal
 *                .println(mensaje/vasriable) Imprime mensaje en teminal
 *                .available              Verifica que haya mensaje en la terminal               
 *          variable.readString             Lee el mensaje de terminal 
 */
 
#include<Servo.h>
Servo servo1;   //Objeto para servo 1
int conversor1;             //variable servo
String dato;                //variable auxiliar servo
int lim;                    //variable auxiliar servo
int aux = 0;                //variable activacion serial
 int on=0;                  //variable para interrupcion
 
void setup() {
      Serial.begin(9600);       //Inicializar para comunicacion serial
      servo1.attach(6);         //Inicializar servo
      attachInterrupt(0,activacion,LOW);      //Evento de activación
}

void loop() {
      if(aux==1){             //Condicion de activacion
        if(Serial.available()>0){         //Condicion de ingreso serial
          dato=Serial.readString();       //Lectura de dato por serial
          lim=dato.toInt();               //Conversion dato leido
          Serial.println("");             //Espacio en blanco
          Serial.println(String("El motor se movera: ")+String(lim)+String(" grados"));     //Mensaje
          Serial.println("Presione el boton para mover el motor ");     //Mensaje 
          aux++;          //Incremento para salir de la condición de activación
        }   
     }
}    
void activacion(){                    //Se activa Interrupción 1 mediante botón
  // NO FUNCIONA DELAY
  switch(on){                         //Número de veces de activación
    case 0: 
      Serial.println("INICIO DEL SISTEMA");     //Mensajes
      Serial.println("Ingrese el angulo a mover el motor"); //Mensajes
      aux=1; //Inicio de condicion para comunicacion serial
      on++;  //Aumento condicion de interrupcion
    break;
    case 1:
      Serial.println("Accion Iniciada");
      conversor1=lim;        // Obtencion del dato de giro 
      conversor1=map(lim,0,1023,0,180);   //Funcion de cambio de rango
      servo1.write(lim);              //Funcion para mover el servo motor
      delay(20); //estabilizar al servo
      Serial.println(String("El motor ha girado ")+String(lim)+String(" grados")); //Mensaje
      Serial.println("Presione para finalizar");      //Mensaje
      on++;                                     //Aumento condicion de interrupcion
    break;
    case 2:
      Serial.println("Accion Finalizada"); //Mensaje
      aux=0;                //Reinicio variables;
      on=0;                 //Reinicio variables;
      Serial.println("Presione  el boton para iniciar nuevamente"); //Mensaje
    break;
  }
}
