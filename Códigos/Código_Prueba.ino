#include <DEF_PP.h>

/* PROGRAMA PARA LA PLACA DE PRUEBA */
/* Segun el pulsador presionado, se elige uno de 3 modos:
/* 1) Controlar el brillo de 2 LEDs con el potenciometro.
/* 2) Encender un LED o su complementario segun lo que mida el LDR.
/* 3) Encender un LED o su complementario segun se interrumpa el haz del fototransistor o no.

/* VARIABLES */
int v_anterior = 0;
int v_estado = 0;
int v_pot;
int v_ldr;
int v_ft;


/* SETUP */
void setup(){
              pinMode(SW1, INPUT_PULLUP);     // Se configuran como entradas con pullup.
              pinMode(SW2, INPUT_PULLUP);
              pinMode(SW3, INPUT_PULLUP);
              pinMode(POT, INPUT);            // Se configuran como entradas.
              pinMode(LDR, INPUT);
              pinMode(FT, INPUT);
              pinMode(LED1,OUTPUT);
              pinMode(LED2,OUTPUT);
              pinMode(LED3,OUTPUT);            // Se configuran como salidas.
              pinMode(LED4,OUTPUT);

}
/* Loop */
void loop(){
  
  
  v_estado = Detectar_Estado();               
  
  switch (v_estado) {
    case 1: digitalWrite(LED3,LOW);            // Apago los LEDs no utilizados.
            digitalWrite(LED4,LOW);
            
            v_pot= analogRead(POT);            // Mido el potenciometro y guardo el valor en v_pot.
            v_pot= map(v_pot,0,1023,0,255);    // Traslado los valores [0 1023] a [0 255]
                                               // http://arduino.cc/en/Reference/Map
            if (v_pot >= 230) v_pot= 255;      // Si mido mas de 230, asigno a v_pote = 255.
            if (v_pot <= 5) v_pot= 0;          // Si mido menos de 5, asigno a v_pote = 0.
            
            analogWrite(LED1,v_pot);           // Uso el PWM con ciclo de trabajo igual a v_ote para prender un LED.
            analogWrite(LED2,255-v_pot);       // El otro LED se comporta complementario.

            v_anterior= 1;
            break;
           
           
    case 2: digitalWrite(LED1,LOW);            // Apago los LEDs no utilizados.
            digitalWrite(LED2,LOW);
            v_ldr=analogRead(LDR);             // Mido el LDR y guardo el valor en Luz.

            if (v_ldr >= 850) {                // Si mido mas de 850, prendo uno de los LEDs. Si no, prendo el otro.
              digitalWrite(LED4,HIGH);
              digitalWrite(LED3,LOW);
            } else{
              digitalWrite(LED4,LOW);
              digitalWrite(LED3,HIGH);
            }
            v_anterior= 2;
            break;
          
    case 3: digitalWrite(LED1,LOW);           // Apago los LEDs no utilizados.
            digitalWrite(LED2,LOW);
            v_ft=analogRead(FT);              // Mido el fototransistor y guardo el valor en v_ft.
            if (v_ft <= 200){
              digitalWrite(LED3,HIGH);  
              digitalWrite(LED4,LOW);
            } else{
               digitalWrite(LED3,LOW);  
               digitalWrite(LED4,HIGH);
            }
            v_anterior= 3;
            break;
  }

}

/* Funciones */


/* Esta funcion permite detectar que boton se presiono y   *
 * devolver el resultado en la variable v_est. En caso     *
 * de no detectarse ningun boton, la funcion retorna el    *
 * valor del estado anterior.                              */
 
int Detectar_Estado(){
  
  byte v_est;
  
  if (digitalRead(SW1) == 0){ 
    v_est= 1; 
  } else if (digitalRead(SW2) == 0){
    v_est= 2; 
  } else if (digitalRead(SW3) == 0){ 
    v_est= 3; 
  } else {
    return v_anterior;
  }
  
  delay(500);  
  return v_est;
  
}

