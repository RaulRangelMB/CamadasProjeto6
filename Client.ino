const int pino_timer_5 = 47;

int contador = 0;
void setup() {

  pinMode(pino_timer_5, INPUT);
  Serial.begin(9600);

  TCCR5A= 0b00000000;
  TCCR5B= 0b00000111;
}

void loop() {
 
    delay(1000);
    TCCR5B= 0b00000000;
    contador = TCNT5;
    TCNT5=0b00000000;
    TCCR5B= 0b00000111;
    Serial.println(contador);
    
}
