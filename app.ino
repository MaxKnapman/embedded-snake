#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

int xCoord = 0;
int yCoord = 0;
int up = 2;
int down = 3;
int left = 4;
int right = 5;
int direction = 4;
long movementInterval = 500;
long previousMillis = 0;

void changeDirection(int newDirection) {
  direction = newDirection;
  delay(100);
}

void setup() {
  u8g2.begin();
  Serial.begin(9600);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
}

void loop() {

  long currentMillis = millis();

  // get button inputs
  if (digitalRead(up) == LOW)
  }
  if (digitalRead(down) == LOW) {
    changeDirection(2);
  }
  if (digitalRead(left) == LOW) {
    changeDirection(3);
  }
  if (digitalRead(right) == LOW) {
    changeDirection(4);
  }

  //movement
  if (currentMillis - previousMillis >= movementInterval) {
    previousMillis = currentMillis;
    switch(direction) {
      case 1:
        yCoord--;
        break;
      case 2:
        yCoord++;
        break;
      case 3:
        xCoord--;
        break;
      case 4:
        xCoord++;
        break;
    }
    u8g2.drawPixel(xCoord, yCoord);
    u8g2.sendBuffer();
    Serial.println(xCoord + yCoord);
  }
}
