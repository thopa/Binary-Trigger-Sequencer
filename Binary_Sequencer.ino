//Binary Gate Sequencer by Thopa
// A Eurorack Binary trigger Sequencer, based on Sebastian Tomasck code and Module
// 8 Triggers Channels
//Clock In And Reset



const int interrupt_pin = 2;
const int clock_out = 11;

const int rstClkIn = 12;

const int gate_1 = 3;
const int gate_2 = 4;
const int gate_3 = 5;
const int gate_4 = 6;

const int gate_5 = 7;
const int gate_6 = 8;
const int gate_7 = 9;
const int gate_8 = 10;

byte clock_count = 0;
byte value_1 = 0;
byte value_2 = 0;
byte value_3 = 0;
byte value_4 = 0;

byte value_5 = 0;
byte value_6 = 0;
byte value_7 = 0;
byte value_8 = 0;

volatile byte interrupt_flag = LOW;

byte reset_current;
byte reset_previous;



void setup() {

  pinMode(gate_1, OUTPUT);
  digitalWrite(gate_1, HIGH);

  pinMode(gate_2, OUTPUT);
  digitalWrite(gate_2, HIGH);

  pinMode(gate_3, OUTPUT);
  digitalWrite(gate_3, HIGH);

  pinMode(gate_4, OUTPUT);
  digitalWrite(gate_4, HIGH);

  pinMode(gate_5, OUTPUT);
  digitalWrite(gate_5, HIGH);

  pinMode(gate_6, OUTPUT);
  digitalWrite(gate_6, HIGH);

  pinMode(gate_7, OUTPUT);
  digitalWrite(gate_7, HIGH);

  pinMode(gate_8, OUTPUT);
  digitalWrite(gate_8, HIGH);

  pinMode(clock_out, OUTPUT);
  digitalWrite(clock_out, HIGH);

  pinMode(rstClkIn, INPUT_PULLUP);

  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), changing, CHANGE);
}

void loop() {
  value_1 = analogRead(0) >> 2;
  value_2 = analogRead(1) >> 2;
  value_3 = analogRead(2) >> 2;
  value_4 = analogRead(3) >> 2;

  value_5 = analogRead(4) >> 2;
  value_6 = analogRead(5) >> 2;
  value_7 = analogRead(6) >> 2;
  value_8 = analogRead(7) >> 2;

  if (interrupt_flag == HIGH) {
    interrupt_flag = LOW;

    if (digitalRead(interrupt_pin) == HIGH) {
      digitalWrite(clock_out, HIGH);

      digitalWrite(gate_1, bitRead(value_1, clock_count));
      digitalWrite(gate_2, bitRead(value_2, clock_count));
      digitalWrite(gate_3, bitRead(value_3, clock_count));
      digitalWrite(gate_4, bitRead(value_4, clock_count));

      digitalWrite(gate_5, bitRead(value_5, clock_count));
      digitalWrite(gate_6, bitRead(value_6, clock_count));
      digitalWrite(gate_7, bitRead(value_7, clock_count));
      digitalWrite(gate_8, bitRead(value_8, clock_count));

      clock_count ++;

      if (clock_count == 8) {
        clock_count = 0;


      }
    }

    else {
      digitalWrite(gate_1, LOW);
      digitalWrite(gate_2, LOW);
      digitalWrite(gate_3, LOW);
      digitalWrite(gate_4, LOW);

      digitalWrite(gate_5, LOW);
      digitalWrite(gate_6, LOW);
      digitalWrite(gate_7, LOW);
      digitalWrite(gate_8, LOW);

      digitalWrite(clock_out, LOW);



    }
    reset_current = digitalRead(rstClkIn);

    if (reset_current != reset_previous) {
      reset_previous = reset_current;

      if (reset_current == 1) {
        clock_count = 0;
      }
    }
  }
}

void changing() {
  interrupt_flag = HIGH;
}
