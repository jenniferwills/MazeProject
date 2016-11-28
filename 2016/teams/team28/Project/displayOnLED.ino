#include "displayOnLED.h"

void setupLED() {
  OrbitOledInit();
  OrbitOledClearBuffer();
}

void showStartInstruction(){
  //display is 16 chars horizontally and four lines vertically
  OrbitOledSetCursor(3, 0);
  OrbitOledPutString("WELCOME TO");
  OrbitOledSetCursor(4, 1);
  OrbitOledPutString("The Maze");
  OrbitOledSetCursor(1, 3);
  OrbitOledPutString("shake to start");
}

void showSelectDifficultyInstruction(){
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString("difficulty:");
  OrbitOledSetCursor(7, 1);
  char temp = 48 + viewNum;
  OrbitOledPutChar(temp);
  OrbitOledSetCursor(0, 2);
  OrbitOledPutString("Right BTN:+");
  OrbitOledSetCursor(0, 3);
  OrbitOledPutString("Left BTN: OK");
}

void showResult(){
  OrbitOledClearBuffer();
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString("CONGRATULATIONS!");
  OrbitOledSetCursor(4, 1);
  OrbitOledPutString("YOU WIN!");
  OrbitOledSetCursor(0, 2);
  OrbitOledPutString("up BTN: new game");
  OrbitOledSetCursor(0, 3);
  OrbitOledPutString("Time to exit: ");
  OrbitOledSetCursor(15, 3);
  char temp = 49 + (5000 - millis() + t) / 1000;
  OrbitOledPutChar(temp);
  OrbitOledUpdate();
  //could add the time left to start new game
}

void drawBall(int ballPos[]){
  //128 columns, 32 rows
  OrbitOledMoveTo(ballPos[0], ballPos[1]);
  OrbitOledDrawPixel();
  OrbitOledUpdate();
  OrbitOledUpdate();
}

void drawMaze(int mazeArray[128][32]){
  
  for(int i = 0; i<128;i++){
    for(int j=0;j<32;j++){
      OrbitOledMoveTo(i, j);
      if(mazeArray[i][j] == 1){
        OrbitOledDrawPixel();
      }
    }
  }
  
  OrbitOledSetDrawColor(0);  //change the colour to the same as the background to erase
  for(int i=finishX;i<127;i++){
    mazeArray[i][finishY] = 0;
    OrbitOledMoveTo(i, finishY);
    OrbitOledDrawPixel();
  }
  OrbitOledSetDrawColor(0x01);  //return to white to be able see the next drawn things
}

void pathBlock(){
  blockedPath = random(pathNum);
  
  for(int i = 0; i<pathWidth+1; i++){
    
    for(int j = 0; j<pathWidth+1; j++){
      mazeArray[(pathArray[blockedPath*4]*(pathWidth+1))+(i)*pathArray[blockedPath*4+2]][(pathArray[blockedPath*4+1]*(pathWidth+1))+(j)*pathArray[blockedPath*4+3]]=1;
    }
  }  
}

void pathUnblock(){
  for(int i = 1; i<pathWidth+1; i++){
    
    for(int j = 1; j<pathWidth+1; j++){
      mazeArray[(pathArray[blockedPath*4]*(pathWidth+1))+(i)*pathArray[blockedPath*4+2]][(pathArray[blockedPath*4+1]*(pathWidth+1))+(j)*pathArray[blockedPath*4+3]]=0;
    }
  } 
}

void drawPortal(){
  for (int i = 0; i < 2; i++){
    OrbitOledMoveTo(portalPos[i][0], portalPos[i][1]);
    OrbitOledDrawPixel();
    OrbitOledMoveTo(portalPos[i][0] - 1, portalPos[i][1]);
    OrbitOledDrawPixel();
    OrbitOledMoveTo(portalPos[i][0] + 1, portalPos[i][1]);
    OrbitOledDrawPixel();
    OrbitOledMoveTo(portalPos[i][0], portalPos[i][1] - 1);
    OrbitOledDrawPixel();
    OrbitOledMoveTo(portalPos[i][0], portalPos[i][1] + 1);
    OrbitOledDrawPixel();
  }
}

