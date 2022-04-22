int pins[] = {3, 6, 7, 8, 9, 10, 11, 12};
const int pins_len = sizeof(pins)/sizeof(pins[0]);
int option = 2;
const int LEFT = 1;
const int RIGHT = 2;

void turnOn(int pin) {
  for (int i = 0; i < pins_len; i++) {
    if (pins[i] == pin) {
      digitalWrite(pins[i], HIGH);
    } else {
      digitalWrite(pins[i], LOW);
    }
  }
}

void allTurnOn() {
  for (int i = 0; i < pins_len; i++) {
    digitalWrite(pins[i], HIGH);
  }
  tone(A0, 500);
}

void decToBin(int dec) {
  int stack[pins_len];
  for (int i = 0; i < pins_len; i++) {
    stack[i] = 0;
  }
  int cindx = pins_len;
  while (dec != 0) {
    stack[cindx-1] = dec % 2;
    dec = dec / 2;
    cindx--;
  }
  for (int i = 0; i < pins_len; i++) {
    if (stack[i] == 1) {
      digitalWrite(pins[pins_len-i-1], HIGH);
    } else {
      digitalWrite(pins[pins_len-i-1], LOW);
    }
  }
}

void countNumbers(int interval){
  for(int i = 0; i <= 255; i++) {
    if (i % 2 == 0) {
      tone(A0, 1800);
    }
    decToBin(i);
    delay(interval);
    noTone(A0);
  }
}

void anim(int interval, int dir) {
  tone(A0, 2000);
  delay(100);
  noTone(A0);
  delay(100);
  if (dir == LEFT) {
    for (int i = 0; i < pins_len; i++) {
      turnOn(pins[i]);
      delay(interval);
    }
  } else if (dir == RIGHT) {
    for (int i = pins_len-1; i >= 0; i--) {
      turnOn(pins[i]);
      delay(interval);
    }
  }
}

void setup () {
  Serial.begin(9600);
  for (int i = 0; i < pins_len; i++) {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
}

void loop () {
  while (Serial.available() > 0) {
    byte data = Serial.read();
    Serial.write(1);
    digitalWrite(13, HIGH);
    delay(4);
    digitalWrite(13, LOW);
    delay(4);
    if (data == 0x01) {
      option = 1;
    } else if (data == 0x02) {
      option = 2;
    } else if (data == 0x03) {
      option = 3;
    }
  }
  if (option == 1) {
    countNumbers(80);
  } else if (option == 2) {
    anim(100, LEFT);
    anim(100, RIGHT);
  } else if (option == 3) {
    allTurnOn();
  }
}
