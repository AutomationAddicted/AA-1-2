// --- Automation Addicted #1-2 ---
/*
  Kalman Filter: implementation on Arduino UNO board
  Author: Alessandro D'Alio
  YouTube: Automation Addicted
  "Follow me and subscribe to my channel for more videos!"
*/

int v   = 0;                // valore misura sensore LM35DZ [0-1023]
float T = 0;                // valore temperatura [°C]

float R   = 0.026971021;    //varianza del rumore sulla misura
float Q   = 1e-05;          // varianza del disturbo sul processo
float Pp  = 0.0;            // P(t|t-1) varianza dell'errore di predizione
float K   = 0.0;            // Kalman gain
float e   = 0.0;            // epsilon, termine di innovazione
float P   = 1.0;            // P(t|t) varianza dell'errore di filtraggio
float Xp  = 0.0;            // x_^(t|t-1) predizione dello stato precedente
float X   = 0.0;            // x_^(t|t) stato filtrato

// System model
//  int A = 1;
//  int B = 0;
//  int C = 1;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Sensor_measurement,Kalman_estimate");
}

void loop() {
  v = analogRead(A0);     // lettura output del sensore LM35DZ         
  T = v * 0.48875;        // temperatura: conversione [V] - [°C]
  
  // --- Kalman process ---
  Pp = P + Q;             // (PREDICTION) predizione della varianza dell'errore al prossimo step
  Xp = X;                 // (PREDICTION) predizione dello stato al prossimo step
  K = Pp/(Pp + R);        // (CORRECTION) Kalman gain
  e = T-Xp;               // (CORRECTION) aggiornamento innovazione
  P = (1-K)*Pp;           // (CORRECTION) aggiornamento della varianza dell'errore di filtraggio
  X = Xp + K*e;           // (CORRECTION) stima di Kalman dell'output del sensore

  Serial.print(T);
  Serial.print(" ");
  Serial.println(X); 
    
  delay(30);      
}
