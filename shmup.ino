#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define JOY_X A0
#define JOY_Y A1
#define FIRE_BTN 12


int shipX = 64;
int shipY = 32;

int bulletY = -10;
int bulletX = -10;

int asteroidX = 20;
int asteroidY = 12;

uint8_t asteroidSpeed = 1;
int score = 0;

char scoreText[12];
char gameOverMsg[20]; 

bool bulletActive = false;
bool gameRunning = true; 
bool isGameOver = false;

unsigned long gameOverTime = 0;

static const unsigned char ship_bits[] U8X8_PROGMEM = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b11100111,
  0b01100110,
  0b00100100,
  0b00011000
};

void setup() {
  pinMode(FIRE_BTN, INPUT_PULLUP);
  u8g2.begin();
}

void loop() {
  if (isGameOver) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_10x20_tr);
    u8g2.drawStr(20, 32, gameOverMsg);
    u8g2.sendBuffer();
    
    if (millis() - gameOverTime > 3000) {
      score = 0;
      shipX = 64;
      shipY = 32;
      asteroidX = random(0, 120);
      asteroidY = 0;
      bulletActive = false;
      isGameOver = false;
      gameRunning = true;
    }
    return;
  }

  itoa(score, scoreText, 10);

  if (gameRunning) {
    int xVal = analogRead(JOY_X);
    int yVal = analogRead(JOY_Y);

  
    if (xVal < 400) shipX -= 3;
    if (xVal > 600) shipX += 3;
    if (yVal < 400) shipY -= 3;
    if (yVal > 600) shipY += 3;

    if (shipX > 128) shipX = 0;
    if (shipX < 0)   shipX = 120;
    if (shipY > 64)  shipY = 0;
    if (shipY < 0)   shipY = 56;
  }


  if (digitalRead(FIRE_BTN) == LOW && !bulletActive) {
    bulletActive = true;
    bulletX = shipX + 2; // Center the bullet on the 8px ship
    bulletY = shipY;
  }

  if (bulletActive) {
    bulletY -= 5;
    if (bulletY < 0) bulletActive = false;
  }


  if (bulletActive && abs(bulletX - asteroidX) < 8 && abs(bulletY - asteroidY) < 8) {
    bulletActive = false;
    score++;
    asteroidX = random(0, 120);
    asteroidY = 0;
  }


  if (abs(shipX - asteroidX) < 7 && abs(shipY - asteroidY) < 7) {
    score -= 5;
    asteroidY = 0; 
    asteroidX = random(0, 120);

    if (score < 0) {
      isGameOver = true;
      gameRunning = false;
      strcpy(gameOverMsg, "Game Over");
      gameOverTime = millis();
    }
  }


  asteroidY += asteroidSpeed;
  if (asteroidY > 64) {
    asteroidY = 0;
    asteroidX = random(0, 120);
  }

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tr); 
  u8g2.drawStr(0, 10, "Score: ");
  u8g2.drawStr(40, 10, scoreText);

  u8g2.drawXBMP(shipX, shipY, 8, 8, ship_bits);

  if (bulletActive) {
    u8g2.drawBox(bulletX, bulletY, 3, 3);
  }

  u8g2.drawDisc(asteroidX, asteroidY, 3);
  u8g2.sendBuffer();

  delay(10);
}
