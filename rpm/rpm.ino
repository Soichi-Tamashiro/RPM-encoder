
//Cuenta el numero de RPM

#include <LiquidCrystal.h>

double rpm, tiempo;   // variables a usar
int Interruptor = 0;  // El interruptor a utilizar sera el 0 es decir el pin digital 2 de Arduino

LiquidCrystal lcd(30,31, 32,33, 34, 35); // conexión a lcd

int pulsos=0;   // variable para contar los pulsos 
int resolucion = 100; // resolucion del encoder  ( numero de pulsos por revolución) 

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;//Esta seria nuestra funcion interrupcion exte.

void interrupcion_isr()  // se ejecuta cada interrupcion
{
  pulsos=pulsos+1;  // contador de pulsos
}

void setup() 
{ lcd.begin(16,2); 
 pinMode(Interruptor, INPUT_PULLUP);
 attachInterrupt(Interruptor, interrupcion_isr, FALLING);   // se activan interrucciones externas por detección de alto 
} 

void loop()
{
      tiempo =millis(); // mide el tiempo en microsengudos
     if(tiempo==1000){  // si el tiempo es igual a 1 seg. 
       setMillis(new_value); // reinicia el tiempo
          rpm=((double)pulsos/resolucion)*60;  // formula para calcular rpm
        lcd.clear();   
       lcd.setCursor(0,0);            
      lcd.print("rpm");
      lcd.setCursor(5,0);            
      lcd.print(rpm);
      pulsos=0;  // reinicia la cuenta de los pulsos
    }
}
 
void setMillis(unsigned long new_millis){   // función para reiniciar el tiempo a cero
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
