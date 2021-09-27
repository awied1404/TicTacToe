#include "Game.h"
Game game;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting the game");
  // put your setup code here, to run once:
  game.startGame();
}

void loop() {
  // put your main code here, to run repeatedly:

}
