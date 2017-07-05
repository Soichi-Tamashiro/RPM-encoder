
#include <LiquidCrystal.h>
LiquidCrystal lcd(30, 31, 32, 33, 34, 35); 

const int pwm = 3; // volviendo el pin 2 como pwm
const int in1 = 8;
const int in2 = 9;

float     i=80;
float     t=0;
float     l;

double rpm, tiempo;   // variables a usar
int Interruptor = 0;  // El interruptor a utilizar sera el 0 es decir el pin digital 2 de Arduino

int pulsos=0;   // variable para contar los pulsos 
int resolucion = 100; // resolucion del encoder  ( numero de pulsos por revolución) 

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;//Esta seria nuestra funcion interrupcion exte.

void setup()
{     pinMode(pwm,OUTPUT); // ponemos el pin pwm como salida
      pinMode(in1,OUTPUT); //ponemos como salida el pin in1
      pinMode(in2,OUTPUT); //ponemos como salida el pin in2
      // pinMode(bot,INPUT); // ponemos como entrada el pin bot
  
      lcd.begin(16,2);
      lcd.clear();   
      lcd.setCursor(0,0);            
      lcd.print("rpm");
      lcd.setCursor(5,0);            
      lcd.print(rpm);
      pinMode(Interruptor, INPUT_PULLUP);
      attachInterrupt(Interruptor, cachete_1, FALLING);  // se activan interrucciones externas por detección de alto 
      attachInterrupt(Interruptor, interrupcion_isr, FALLING);
  }
  
      void interrupcion_isr()  // se ejecuta cada interrupcion
      { pulsos=pulsos+1;  // contador de pulsos
      }

        void cachete_1(){
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
        } }
      
      void setMillis(unsigned long new_millis)
      {   // función para reiniciar el tiempo a cero
      uint8_t oldSREG = SREG;
      cli();
      timer0_millis = new_millis;
      SREG = oldSREG;
      }

void loop()
{     for(i;i<=255;i++)            
      { digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);           
        analogWrite(pwm,i); 
        delay(80);               
       }
       delay(3000);
       //analogWrite(pwm,0);
       digitalWrite(in1,HIGH);
       digitalWrite(in2,HIGH);
       delay(1000) ;
}


