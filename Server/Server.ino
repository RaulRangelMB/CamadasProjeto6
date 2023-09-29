const int rxPin = 3; // Pino digital usado para a recepção (exemplo: pino 3)
const int baudRate = 9600; // Taxa de transmissão em bps

byte receivedByte = 0;
int bitCount = 0;
boolean receiving = false;

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(baudRate);
  // Configurar a interrupção para o timer2
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 208; // Valor para a interrupção a cada 104 µs para 9600 bps
  TCCR2A |= (1 << WGM21); // Modo CTC
  TCCR2B |= (1 << CS21); // Prescaler de 8
  TIMSK2 |= (1 << OCIE2A); // Habilitar interrupção
}

void loop() {
  if (bitCount == 0) {
    receiving = false;
  }
  
  if (bitCount == 0 && digitalRead(rxPin) == LOW) {
    receiving = true;
  }
  
  if (receiving && bitCount < 10) {
    receivedByte |= (digitalRead(rxPin) << bitCount);
    bitCount++;
  } else if (bitCount == 10 && receiving) {
    char characterReceived = removeParityBit(receivedByte);
    Serial.println(characterReceived);
    bitCount = 0;
    receivedByte = 0;
  }
}

char removeParityBit(byte data) {
  // Implemente aqui sua lógica para remover o bit de paridade (par ou ímpar)
  // Neste exemplo, usamos paridade ímpar
  int count = 0;
  byte temp = data;
  while (temp) {
    count += temp & 1;
    temp >>= 1;
  }
  if (count % 2 == 0) {
    // Erro de paridade
    // Implemente aqui a lógica de tratamento de erro, se necessário
    // Por padrão, retornamos um caractere nulo em caso de erro
    return '\0';
  } else {
    // Paridade ímpar: Remova o bit de paridade
    data &= ~(1 << 7);
    return (char)data;
  }
}

// Função de interrupção do timer2
ISR(TIMER2_COMPA_vect) {
  if (bitCount < 10) {
    bitCount++;
  } else {
    bitCount = 0;
  }
}