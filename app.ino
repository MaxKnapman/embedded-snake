#include <stdlib.h>
#include <U8g2lib.h>
#include <time.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

long previousMillis = 0;
char direction = 'r'; //r l u d character values for direction
int length = 1;
int y_segments[20] {1}; //max length based on available ram
int x_segments[20] {1};
int fruit_x_coord;
int fruit_y_coord;

void move(char direction) {
  if (x_segments[0] == fruit_x_coord && y_segments[0] == fruit_y_coord) { //increase length
    length++;
    spawn_fruit();
  }

  for (int i = length; i > 0; i--) { //shunt segments to the right
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

void spawn_fruit() { //randomly spawn fruit
  fruit_x_coord = rand() % 16;
  fruit_y_coord = rand() % 8;
  for (int i = 0; i < length; i++) { // recursion to stop fruit from spawning inside the snake
    if (fruit_x_coord == x_segments[i] && fruit_y_coord == y_segments[i]) {
      spawn_fruit();
    }
  }
}

void setup() {
  srand(time(NULL));
  u8g2.begin();
  pinMode(2, INPUT_PULLUP); //up, down, right, left
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  spawn_fruit();
}

void loop() {
  u8g2.clearBuffer();
  long currentMillis = millis();

  if (digitalRead(2) == LOW && direction != 'd') { // u turns not allowed
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
      u8g2.drawBox(((x_segments[i] * 8) + 1), ((y_segments[i] * 8) + 1), 6, 6); // cells are 8x8 pixels so coords need to be 8x
    }
    u8g2.drawBox((fruit_x_coord * 8), (fruit_y_coord * 8), 8, 8);
    u8g2.sendBuffer();
  }
}
