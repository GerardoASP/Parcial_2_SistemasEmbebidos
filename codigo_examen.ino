// C++ code
//Librerias
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

//Declaración de Variables/Constantes
#define trig 0
#define echo 1
int cont = 0;
const byte rowsCount = 4;
const byte columnsCount = 4;
char keys [rowsCount][columnsCount] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
int valor_opcion = 0;
//Pines
byte rowsPins[rowsCount] = {13,12,11,10};
byte columnsPins[columnsCount] = {9,8,7,6};
byte pin_servo_motor = 3;
byte pin_led = 2;

//Instancia Libreria Keypad
Keypad teclado = Keypad(makeKeymap(keys),rowsPins,columnsPins,rowsCount,columnsCount);
//Instancia Libreria Servo.h
Servo myservo;

//Control del tiempo
unsigned long tiempoInicio = 0;
unsigned long tiempoActual = millis();

//Control de Acceso
//Contraseñas permitidas
char pass[] = "1234";
char pass_2[] = "1112";
char pass_3[] = "4444";
char pass_4[] = "2346";
char leave_pass[]="7777";
char entry_pass[4];

//Control de Acceso 2
//Variables de acceso
bool acceso_1 = true;
bool acceso_2 = true;
bool acceso_3 = true;
bool acceso_4 = true;
bool tiquete_entrada = false;

void setup()
{
  Serial.begin(9600);
  myservo.attach(pin_servo_motor); //Mandar datos
  myservo.write(0);
  pinMode(pin_led, OUTPUT);
}

void loop()
{
  char dato = teclado.getKey();
  if (dato != NO_KEY)
  {
    entry_pass[cont]=dato;
    Serial.print(entry_pass[cont]);
    cont=cont+1;
    if(cont==4)
    {
      for ( int i = 0 ; i<4 ; i++) {
        if ( entry_pass[i]!=pass[i] || !acceso_1 ) { acceso_1 = false ; }
        if ( entry_pass[i]!=pass_2[i] || !acceso_2 ) { acceso_2 = false ; }
        if ( entry_pass[i]!=pass_3[i] || !acceso_3 ) { acceso_3 = false ; }
        if ( entry_pass[i]!=pass_4[i] || !acceso_4 ) { acceso_4 = false ; }
      }
      if (acceso_1){
          Serial.println("Contraseña 1 correcta");
          tiquete_entrada = true ;
      }else if (acceso_2){
          Serial.println("Contraseña 2 correcta");
          tiquete_entrada = true ;
      }else if (acceso_3){
          Serial.println("Contraseña 3 correcta");
          tiquete_entrada = true ;
      }else if (acceso_4){
          Serial.println("Contraseña 4 correcta");
          tiquete_entrada = true ;
      }
      
      if(acceso_1 == true && tiquete_entrada==true){
        Serial.println("Mueva servomotor");
        for(int grado=0;grado<=179;grado++){
    		myservo.write(grado);
    		Serial.println(grado);
    		if (tiempoActual - tiempoInicio >= 50){
      			tiempoInicio = millis();
      		}
  		}
  		for(int grado=179;grado>=0;grado--){
    		myservo.write(grado);
    		Serial.println(grado);
    		if (tiempoActual - tiempoInicio >= 50){
      			tiempoInicio = millis();
      		}
  		}
      }else if (acceso_2 == true && tiquete_entrada==true){
        Serial.println("Capturando valor sensor ultrasonico");
        //Generacion echo
  		digitalWrite(trig, HIGH);
  		if (tiempoActual - tiempoInicio >= 1){
      			tiempoInicio = millis();
      	}
  		digitalWrite(trig, LOW);
  
  		float duracion = pulseIn(echo, HIGH);
  		float distancia = duracion/ 58.2;
  		if (tiempoActual - tiempoInicio >= 50){
      			tiempoInicio = millis();
      	}
  		Serial.println("distancia (cm): ");
  		Serial.println(distancia);
      }else if(acceso_3 == true && tiquete_entrada==true){
        Serial.println("Prendiendo Led");
        digitalWrite(pin_led, HIGH);
        tiempoInicio = millis();
        tiempoActual = millis();
        while (tiempoActual - tiempoInicio <= 5000){
      			tiempoActual = millis();
          		digitalWrite(pin_led, HIGH);
      	}
        digitalWrite(pin_led, LOW);
        
      }else if(acceso_4 == true && tiquete_entrada==true){
      	Serial.println("Blue Lock te espera");
      }
      cont = 0;
    }
  }
}