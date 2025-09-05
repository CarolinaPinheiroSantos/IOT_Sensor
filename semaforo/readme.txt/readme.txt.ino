//const int ledver = 5; 
//const int ledmelha = 18; 
//const int ledama = 19; 
//const int buzzer = 21;  // Pino do buzzer
//
//void setup() {
//  pinMode(ledver, OUTPUT);
//  pinMode(ledama, OUTPUT);
//  pinMode(ledmelha, OUTPUT);
//  pinMode(buzzer, OUTPUT);  // Define o pino do buzzer como saída
//}
//
//void loop() {
//  // LED verde
//  digitalWrite(ledver, HIGH);  
//  delay(5000);                 
//  digitalWrite(ledver, LOW);  
//
//    // LED amarelo
//  digitalWrite(ledama, HIGH);  
//  delay(5000);                 
//  digitalWrite(ledama, LOW);   
//
//  // LED vermelho + buzzer
//  digitalWrite(ledmelha, HIGH);  
//  tone(buzzer, 1000);          
//  delay(5000);                  
//  digitalWrite(ledmelha, LOW);        
//  noTone(buzzer);                        
//}

const int buzzer = 21;
const int potPin = 22;  // Pino do potenciômetro (entrada analógica)

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  int potValor = analogRead(potPin);  // lê valor de 0 a 1023

  // Mapeia o valor do potenciômetro para uma frequência entre 100 e 2000 Hz
  int frequencia = map(potValor, 0, 1023, 100, 2000);

  // Mapeia o valor da frequência para um intervalo de tempo (mais rápido com maior frequência)
  int duracao = map(frequencia, 100, 2000, 1000, 100); // intervalo de 1000ms a 100ms

  // Toca o buzzer com essa frequência
  tone(buzzer, frequencia);

  delay(duracao);  // controla a duração do som (mais curta para frequências altas, mais longa para frequências baixas)

  noTone(buzzer);  // Para o som do buzzer
  delay(50);  // Pequeno delay para evitar ruídos excessivos
}
