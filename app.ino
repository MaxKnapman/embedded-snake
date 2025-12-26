#include <stdlib.h>
#include <U8g2lib.h>
#include <time.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

long previousMillis = 0;
char direction = 'r'; //r l u d character values for direction
int length = 1;
int y_segments[10] {1}; //max length 10 for now
int x_segments[10] {1};
int fruit_x_coord;
int fruit_y_coord;

void move(char direction) {
  if (x_segments[0] == fruit_x_coord && y_segments[0] == fruit_y_coord) { //increase length
    length++;
    fruit();
  }

  for (int i = 9; i > 0; i--) { //shunt segments to the right
    x_segments[i] = x_segments[i - 1];
    y_segments[i] = y_segments[i - 1];
  }

  switch (direction) { //reposition head of snake
    case 'l':
      x_segments[0] -= 1;
      break;
    case 'r':
      x_segments[0] += 1;
      break;
    case 'u':
      y_segments[0] -= 1;
      break;
    case 'd':
      y_segments[0] += 1;
      break;
  }
}

void fruit() { //randomly spawn fruit
  fruit_x_coord = rand() % 32;
  fruit_y_coord = rand() % 16;
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
    for (int i = 0; i < length; i++) {
      u8g2.drawBox((x_segments[i] * 4), (y_segments[i] * 4), 4, 4);
    }
    u8g2.drawBox((fruit_x_coord * 4), (fruit_y_coord * 4), 4, 4);
    u8g2.sendBuffer();
  }
}
