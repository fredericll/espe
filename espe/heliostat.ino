#include <Servo.h> 

//Servo moteur horizontal
Servo servo_H;  // servo mouvement horizontal
Servo servo_V;  // servo mouvement vertical

int posH = 90, posV = 90;    // variable pour stocker la position courante du servo

const int pr_drt = A0;
const int pr_gch = A1;
const int pr_ht = A2;

int lum_drt;
int lum_gch;
int lum_ht;
int lum_bas;

void setup() 
{ 
  servo_H.attach(9);  // attacher notre objet myservo au servomoteur branché sur la broche 9 
  servo_V.attach(8);
  servo_H.write(posH); // initialisation au centre
  servo_V.write(posV); //initialisation au centre
  Serial.begin(9600);

  pinMode(pr_drt, INPUT); //photoresistance droite
  
  
  pinMode(pr_gch, INPUT); //photoresistance gauche
} 


void loop() 
{ 
   lum_drt = analogRead(pr_drt) ;
   lum_gch = analogRead(pr_gch) ;
   lum_bas = (lum_drt+lum_gch)/2;
   lum_ht  = analogRead(pr_ht) ;

/*   Serial.print("Drt : ");
   Serial.print(lum_drt);
   Serial.print("- Gch : ");
   Serial.print(lum_gch);
   Serial.print("- Bas : ");
   Serial.print(lum_bas);
   Serial.print(" - Haut : ");
   Serial.println(lum_ht);        */
   
   if (lum_drt > lum_gch*1.05) {
//    Serial.print(" - pos : ");
//    Serial.println(posH);
      if (posH > 1) {
        posH -= 1;
        servo_H.write(posH);
        delay(20);
      }
   }
   else if (lum_gch > lum_drt*1.05) {
           Serial.print(" - pos : ");
           Serial.println(posH);
           if (posH < 180) {
                posH += 1;
                servo_H.write(posH);
                delay(20); 
        }
   }
   
//   Serial.print("posV = ");
//   Serial.println(posV) ;
   
   if (lum_ht > lum_bas*1.05) {
      if (posV < 135) {
        posV += 1;
        servo_V.write(posV);
        delay(20);
        }
   }
   else if (lum_bas > lum_ht*1.05) {
//           Serial.print("posV = ");
//           Serial.println(posV) ; 
           if (posV > 45) {
              posV -= 1;
              servo_V.write(posV);
              delay(20);
              }
            }
   
}
