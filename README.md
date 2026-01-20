# Arduino-SHMUP
And Arduino shoot'em up using an OLED
Arduino OLED Mini Shooter

A simple shoot-'em-up game for the Arduino Nano using a SH1106-based 128×64 OLED display. This project demonstrates basic game-loop structure, sprite rendering, collision detection, and joystick/button input handling on microcontrollers.

Overview

This game uses a joystick to move a small 8×8 ship sprite around the screen. The player fires bullets at descending asteroids to gain points. Colliding with an asteroid deducts points. If the player's score drops below zero, the game ends and automatically restarts after three seconds.

This project is beginner-friendly and useful for learning Arduino graphics programming with the U8G2 library.

Features

Joystick-based ship movement
Fire button for shooting
Bullet and asteroid collision detection
Score tracking
Game Over screen with timed restart
Full 128×64 OLED rendering with the U8G2 library
Sprite stored in PROGMEM
Hardware Required

Arduino Nano (ATmega328p-based boards are compatible)
SH1106 128×64 I2C OLED display
2-axis analog joystick (X = A0, Y = A1)
Push button for firing (pin 12)
Jumper wires
Wiring

Component	Arduino Pin
Joystick X	A0
Joystick Y	A1
Fire Button	D12
OLED SDA	A4
OLED SCL	A5
OLED VCC	5V
OLED GND	GND
Libraries

Install via Arduino Library Manager:

U8g2 (by olikraus)
How to Play

Move the joystick to steer the ship.
Press the button to fire.
Hitting an asteroid adds +1 to your score.
Colliding with an asteroid subtracts -5.
If the score becomes negative, the game ends.
The game restarts automatically after three seconds.
Code Structure

The game loop handles:

Reading joystick input
Polling the fire button
Moving bullets
Moving the asteroid
Collision detection
Drawing everything to the OLED each frame
Game-over handling and timed restart
