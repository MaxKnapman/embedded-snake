#include <stdlib.h>
#include <U8g2lib.h>
#include <time.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

long previousMillis = 0;
char direction = 'r'; //r l u d character values for direction
int ycoord = 1;
int xcoord = 1;
int length = 0;
int ysegments[10];
int xsegments[10];
int fruitx;
int fruity;

void move(char direction) {
  switch (direction) {
    case 'l':
      xcoord -= 1;
      break;
    case 'r':
      xcoord += 1;
      break;
    case 'u':
      ycoord -= 1;
      break;
    case 'd':
      ycoord += 1;
      break;
  }
  if (xcoord == fruitx && ycoord == fruity) {
    length++;
    fruit();
  }
}

void fruit() {
  fruitx = rand() % 32;
  fruity = rand() % 16;
}

void setup() {
  srand(time(NULL));
  u8g2.begin();
  pinMode(2, INPUT_PULLUP); //up, down, right, left
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  fruit();
}

void loop() {
  u8g2.clearBuffer();
  long currentMillis = millis();

  if (digitalRead(2) == LOW && direction != 'd') {
    direction = 'u';
  }
  if (digitalRead(3) == LOW && direction != 'u') {
    direction = 'd';
  }
  if (digitalRead(4) == LOW && direction != 'l') {
    direction = 'r';
  }
  if (digitalRead(5) == LOW && direction != 'r') {
    direction = 'l';
  }

  if (currentMillis - previousMillis >= 500) {
    previousMillis = currentMillis;
    move(direction);
    u8g2.drawBox((xcoord * 4), (ycoord * 4), 4, 4);
    u8g2.drawBox((fruitx * 4), (fruity * 4), 4, 4);
    u8g2.sendBuffer();
  }
}
