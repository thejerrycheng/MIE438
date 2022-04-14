#include <TimerOne.h>

#include <SPI.h>

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define POS_X 0
#define NEG_X 1
#define POS_Z 2
#define NEG_Z 3
#define POS_Y 4
#define NEG_Y 5

#define BUTTON_PIN 8
#define RED_LED 5
#define GREEN_LED 7

#define TOTAL_EFFECTS 7
#define RAIN 0
#define PLANE_BOING 1
#define SEND_VOXELS 2
#define WOOP_WOOP 3
#define CUBE_JUMP 4
#define GLOW 5
#define TEXT 6
//#define LIT 7

#define RAIN_TIME 260
#define PLANE_BOING_TIME 220
#define SEND_VOXELS_TIME 140
#define WOOP_WOOP_TIME 350
#define CUBE_JUMP_TIME 200
#define GLOW_TIME 8
#define TEXT_TIME 300
#define CLOCK_TIME 500

uint8_t characters[10][8] = {
  {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C}, //0
  {0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x3C}, //1
  {0x3C, 0x42, 0x40, 0x40, 0x3C, 0x02, 0x02, 0x7E}, //2
  {0x3C, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x42, 0x3C}, //3
  {0x22, 0x22, 0x22, 0x22, 0x7E, 0x20, 0x20, 0x20}, //4
  {0x7E, 0x02, 0x02, 0x3E, 0x40, 0x40, 0x42, 0x3C}, //5
  {0x3C, 0x02, 0x02, 0x3E, 0x42, 0x42, 0x42, 0x3C}, //6
  {0x3C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40}, //7
  {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C}, //8
  {0x3C, 0x42, 0x42, 0x42, 0x3C, 0x40, 0x40, 0x3C}, //9
};

uint8_t cube[8][8];
uint8_t currentEffect;
uint16_t timer;
uint64_t randomTimer;
bool loading;

int slaveSelectPin = 52;

int refresh_time = 0.1;
int layer_time = 0.01;

///////////////////////////////// global function to set the state of a voxel /////////////////////////////////
void writeVoxel(uint8_t x, uint8_t y, uint8_t z, bool state) {
  if (state == 0) {
    clearVoxel(x, y, z);
  }
  else {
    setVoxel(x, y, z);
  }
}

///////////////////////////////// set a voxel /////////////////////////////////
void setVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] |= (0x01 << x);
}
///////////////////////////////// clear a voxel /////////////////////////////////
void clearVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[y][z] &= ~(1 << x);
}
///////////////////////////////// flip a voxel /////////////////////////////////
void flipVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] ^= (0x01 << x);
}
///////////////////////////////// get the state of the voxel /////////////////////////////////
bool getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  return (cube[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

///////////////////////////////// set a plane to be lit up/////////////////////////////////
void setPlane(uint8_t axis, uint8_t i) {
  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t k = 0; k < 8; k++) {
      if (axis == XAXIS) {
        setVoxel(i, j, k);
      } else if (axis == YAXIS) {
        setVoxel(j, i, k);
      } else if (axis == ZAXIS) {
        setVoxel(j, k, i);
      }
    }
  }
}

///////////////////////////////// shift a plane to the direction given; dir can be: POS_X; POS_Y; POS_Z; NEG_X; NEG_Y; NEG_Z /////////////////////////////////
void shift(uint8_t dir) {

  if (dir == POS_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y][z] << 1;
      }
    }
  } else if (dir == NEG_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y][z] >> 1;
      }
    }
  } else if (dir == POS_Y) {
    for (uint8_t y = 1; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y - 1][z] = cube[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[7][i] = 0;
    }
  } else if (dir == NEG_Y) {
    for (uint8_t y = 7; y > 0; y--) {
      for (uint8_t z = 0; z < 8; z++) {
        cube[y][z] = cube[y - 1][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[0][i] = 0;
    }
  } else if (dir == POS_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 1; z < 8; z++) {
        cube[y][z - 1] = cube[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[i][7] = 0;
    }
  } else if (dir == NEG_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 7; z > 0; z--) {
        cube[y][z] = cube[y][z - 1];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      cube[i][0] = 0;
    }
  }
}

///////////////////////////////// Draw a hallow cube /////////////////////////////////
void drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s) {
  for (uint8_t i = 0; i < s; i++) {
    setVoxel(x, y + i, z);
    setVoxel(x + i, y, z);
    setVoxel(x, y, z + i);
    setVoxel(x + s - 1, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z + s - 1);
    setVoxel(x + s - 1, y + s - 1, z + i);
    setVoxel(x + s - 1, y + i, z);
    setVoxel(x, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z);
    setVoxel(x + i, y, z + s - 1);
    setVoxel(x + s - 1, y, z + i);
    setVoxel(x, y + s - 1, z + i);
  }
}
///////////////////////////////// set the buffer to ON for the entire cube /////////////////////////////////
void lightCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
}

///////////////////////////////// clear up all the buffer to OFF for enture cube /////////////////////////////////
void clearCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
}


///////////////////////////////// Send the buffer data to the LED Cube! equvlent to display.display() function from the OLED display  /////////////////////////////////
//void renderCube() {
//  for (uint8_t i = 0; i < 8; i++) {
//    digitalWrite(slaveSelectPin, LOW);
//    SPI.transfer(0x01 << i);
//    //   SPI.transfer(0xFF);
//    for (uint8_t j = 0; j < 8; j++) {
//      SPI.transfer(cube[i][j]);
//      //SPI.transfer(0x11);
//      //delay(layer_time);
//    }
//    digitalWrite(slaveSelectPin, HIGH);
//  }
//  //delay(layer_time * 5);
//  for (uint8_t k = 0; k < 8; k++) {
//    digitalWrite(slaveSelectPin, LOW);
//    SPI.transfer(0x01 << k);
//    //    SPI.transfer(0xFF);
//    for (uint8_t j = 0; j < 8; j++) {
//      //      SPI.transfer(cube[k][j]);
//      SPI.transfer(0x00);
//    }
//    digitalWrite(slaveSelectPin, HIGH);
//  }
//  //delay(refresh_time);
//}



void renderCube() {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(SS, LOW);

    SPI.transfer(0x01 << i);
    for (uint8_t j = 0; j < 8; j++) {
      SPI.transfer(cube[i][j]);
    }
    digitalWrite(SS, HIGH);
  }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////// Effects /////////////////////////////////
///////////////////////////////////////////////////////////////////////////


///////////////////////////////// Rain Effects /////////////////////////////////
void rain() {
  if (loading) {
    clearCube();
    loading = false;
  }
  timer++;
  if (timer > RAIN_TIME) {
    timer = 0;
    shift(NEG_Y);
    uint8_t numDrops = random(0, 5);
    for (uint8_t i = 0; i < numDrops; i++) {
      setVoxel(random(0, 8), 7, random(0, 8));
    }
  }
}
///////////////////////////////// Plane Boing Effects /////////////////////////////////

uint8_t planePosition = 0;
uint8_t planeDirection = 0;
bool looped = false;


void planeBoing() {
  if (loading) {
    clearCube();
    uint8_t axis = random(0, 3);
    planePosition = random(0, 2) * 7;
    setPlane(axis, planePosition);
    if (axis == XAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_X;
      } else {
        planeDirection = NEG_X;
      }
    } else if (axis == YAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Y;
      } else {
        planeDirection = NEG_Y;
      }
    } else if (axis == ZAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Z;
      } else {
        planeDirection = NEG_Z;
      }
    }
    timer = 0;
    looped = false;
    loading = false;
  }

  timer++;
  if (timer > PLANE_BOING_TIME) {
    timer = 0;
    shift(planeDirection);
    if (planeDirection % 2 == 0) {
      planePosition++;
      if (planePosition == 7) {
        if (looped) {
          loading = true;
        } else {
          planeDirection++;
          looped = true;
        }
      }
    } else {
      planePosition--;
      if (planePosition == 0) {
        if (looped) {
          loading = true;
        } else {
          planeDirection--;
          looped = true;
        }
      }
    }
  }
}


///////////////////////////////// Send Voxel Effects /////////////////////////////////
uint8_t selX = 0;
uint8_t selY = 0;
uint8_t selZ = 0;
uint8_t sendDirection = 0;
bool sending = false;

void sendVoxels() {
  if (loading) {
    clearCube();
    for (uint8_t x = 0; x < 8; x++) {
      for (uint8_t z = 0; z < 8; z++) {
        setVoxel(x, random(0, 2) * 7, z);
      }
    }
    loading = false;
  }

  timer++;
  if (timer > SEND_VOXELS_TIME) {
    timer = 0;
    if (!sending) {
      selX = random(0, 8);
      selZ = random(0, 8);
      if (getVoxel(selX, 0, selZ)) {
        selY = 0;
        sendDirection = POS_Y;
      } else if (getVoxel(selX, 7, selZ)) {
        selY = 7;
        sendDirection = NEG_Y;
      }
      sending = true;
    } else {
      if (sendDirection == POS_Y) {
        selY++;
        setVoxel(selX, selY, selZ);
        clearVoxel(selX, selY - 1, selZ);
        if (selY == 7) {
          sending = false;
        }
      } else {
        selY--;
        setVoxel(selX, selY, selZ);
        clearVoxel(selX, selY + 1, selZ);
        if (selY == 0) {
          sending = false;
        }
      }
    }
  }
}




///////////////////////////////// Woop woop Effects /////////////////////////////////
uint8_t cubeSize = 0;
bool cubeExpanding = true;

void woopWoop() {
  if (loading) {
    clearCube();
    cubeSize = 2;
    cubeExpanding = true;
    loading = false;
  }

  timer++;
  if (timer > WOOP_WOOP_TIME) {
    timer = 0;
    if (cubeExpanding) {
      cubeSize += 2;
      if (cubeSize == 8) {
        cubeExpanding = false;
      }
    } else {
      cubeSize -= 2;
      if (cubeSize == 2) {
        cubeExpanding = true;
      }
    }
    clearCube();
    drawCube(4 - cubeSize / 2, 4 - cubeSize / 2, 4 - cubeSize / 2, cubeSize);
  }
}

///////////////////////////////// Cube Jump Effects /////////////////////////////////

uint8_t xPos;
uint8_t yPos;
uint8_t zPos;

void cubeJump() {
  if (loading) {
    clearCube();
    xPos = random(0, 2) * 7;
    yPos = random(0, 2) * 7;
    zPos = random(0, 2) * 7;
    cubeSize = 8;
    cubeExpanding = false;
    loading = false;
  }

  timer++;
  if (timer > CUBE_JUMP_TIME) {
    timer = 0;
    clearCube();
    if (xPos == 0 && yPos == 0 && zPos == 0) {
      drawCube(xPos, yPos, zPos, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 0) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 0 && zPos == 7) {
      drawCube(xPos, yPos, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 7) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos + 1 - cubeSize, cubeSize);
    }
    if (cubeExpanding) {
      cubeSize++;
      if (cubeSize == 8) {
        cubeExpanding = false;
        xPos = random(0, 2) * 7;
        yPos = random(0, 2) * 7;
        zPos = random(0, 2) * 7;
      }
    } else {
      cubeSize--;
      if (cubeSize == 1) {
        cubeExpanding = true;
      }
    }
  }
}


///////////////////////////////// Glowing Effects /////////////////////////////////

bool glowing;
uint16_t glowCount = 0;

void glow() {
  if (loading) {
    clearCube();
    glowCount = 0;
    glowing = true;
    loading = false;
  }

  timer++;
  if (timer > GLOW_TIME) {
    timer = 0;
    if (glowing) {
      if (glowCount < 448) {
        do {
          selX = random(0, 8);
          selY = random(0, 8);
          selZ = random(0, 8);
        } while (getVoxel(selX, selY, selZ));
        setVoxel(selX, selY, selZ);
        glowCount++;
      } else if (glowCount < 512) {
        lightCube();
        glowCount++;
      } else {
        glowing = false;
        glowCount = 0;
      }
    } else {
      if (glowCount < 448) {
        do {
          selX = random(0, 8);
          selY = random(0, 8);
          selZ = random(0, 8);
        } while (!getVoxel(selX, selY, selZ));
        clearVoxel(selX, selY, selZ);
        glowCount++;
      } else {
        clearCube();
        glowing = true;
        glowCount = 0;
      }
    }
  }
}


///////////////////////////////// Display Numbers from 0-9 Effects /////////////////////////////////

uint8_t charCounter = 0;
uint8_t charPosition = 0;

void text(char string[], uint8_t len) {
  if (loading) {
    clearCube();
    charPosition = -1;
    charCounter = 0;
    loading = false;
  }


  shift(NEG_Z);
  charPosition++;

  if (charPosition == 7) {
    charCounter++;
    if (charCounter > len - 1) {
      charCounter = 0;
    }
    charPosition = 0;
  }

  if (charPosition == 0) {
    for (uint8_t i = 0; i < 8; i++) {
      cube[i][0] = characters[string[charCounter] - '0'][i];
    }
  }

}

///////////////////////////////// Lit up Effects /////////////////////////////////

void lit() {
  if (loading) {
    clearCube();
    for (uint8_t i = 0; i < 8; i++) {
      for (uint8_t j = 0; j < 8; j++) {
        cube[i][j] = 0xFF;
      }
    }
    loading = false;
  }
}




///////////////////////////////// Automatically Rendered Effects //////////////////////////////////

void effect_text() {

  for (int i = 0; i < 20000; i++) {
    text("0123456789", 10);
    renderCube();

  }
  //  clearCube();
  //  renderCube();
  currentEffect ++;

}

void effect_planeBoing() {

  for (int i = 0; i < 20000; i++) {
    planeBoing();
    renderCube();

  }
  clearCube();
  renderCube();
  currentEffect ++;

}

void effect_rain() {

  for (int i = 0; i < 20000; i++) {
    rain();
    renderCube();

  }
  clearCube();
  renderCube();
  currentEffect ++;

}


void effect_sendVoxels() {

  for (int i = 0; i < 20000; i++) {
    sendVoxels();
    renderCube();

  }
  clearCube();
  renderCube();
  currentEffect ++;

}

void effect_cubeJump() {

  for (int i = 0; i < 20000; i++) {
    cubeJump();
    renderCube();

  }
  clearCube();
  renderCube();
  currentEffect ++;

}

void effect_woopWoop() {

  for (int i = 0; i < 20000; i++) {
    cubeJump();
    renderCube();

  }
  woopWoop();
  renderCube();
  currentEffect ++;

}

void effect_glow() {

  for (int i = 0; i < 20000; i++) {
    glow();
    renderCube();

  }
  woopWoop();
  renderCube();
  currentEffect ++;

}




///////////////////////// setup /////////////////////////////////

const int poX = A1;
const int poY = A2;
const int poZ = A3;
const int poI = A4;
const int poPress = 7;
const int posZ = A3;
const int posI = A4;

/////////////////////////////////Effect Animation Showcase: /////////////////////////////////

void start_animation() {
  for (int i = 0; i < 20000; i++) {
    rain();
    renderCube();

  }
  clearCube();
  //renderCube();

  for (int i = 0; i < 20000; i++) {
    planeBoing();
    // renderCube();

  }
  clearCube();
  renderCube();
  ///////////////////////////////// /////////////////////////////////
  for (int i = 0; i < 20000; i++) {
    woopWoop();
    renderCube();

  }
  clearCube();
  renderCube();
  ///////////////////////////////// /////////////////////////////////

  ///////////////////////////////// /////////////////////////////////
  for (int i = 0; i < 20000; i++) {
    cubeJump();
    renderCube();

  }
  clearCube();
  renderCube();

}




////////////////////////////////////////////////////
/////////////PONG GAME SETUP //////////////////////
////////////////////////////////////////////////////



///////////////////////////////// PONG GAME /////////////////////////////////
//
//
//class cBall {
//  private:
//    int ballX, ballY, ballZ;
//    int originalX, originalY, originalZ;
//    eDir direction;
//
//  public:
//    cBall(int posX, int posY, int posZ) {
//      originalX = posX;
//      originalY = posY;
//      originalZ = posZ;
//      ballX = posX;
//      ballY = posY;
//      ballZ = posZ;
//      direction = pSTOP;
//    }
//
//    void Reset() {
//      ballX = originalX;
//      ballY = originalY;
//      ballZ = originalZ;
//      direction = pSTOP;
//    }
//
//    void changeDirection(eDir d) {
//      direction = d;
//    }
//
//    inline int getX() {
//      return ballX;
//    }
//
//    inline int getY() {
//      return ballY;
//    }
//
//    inline int getZ() {
//      return ballZ;
//    }
//
//    inline eDir getDirection() {
//      return direction;
//    }
//    void randomDirection() {
//      direction = (eDir)(random(1, 11)); // randomly select a direction to move to from 1-10
//    }
//
//    void Move() {
//      switch (direction) {
//        case pSTOP:
//          break;
//
//        case pUP:
//          ballZ ++;
//          break;
//
//        case pUPLEFT:
//          ballZ ++;
//          ballX --;
//          break;
//
//        case pUPRIGHT:
//          ballZ ++;
//          ballX ++;
//          break;
//
//
//        case pUPIN:
//          ballZ ++;
//          ballY ++;
//          break;
//
//        case pUPOUT:
//          ballZ ++;
//          ballY --;
//          break;
//
//        case pDOWN:
//          ballZ --;
//          break;
//
//        case pDOWNLEFT:
//          ballZ --;
//          ballX --;
//          break;
//
//        case pDOWNRIGHT:
//          ballZ --;
//          ballX ++;
//          break;
//
//        case pDOWNIN:
//          ballZ --;
//          ballY ++;
//          break;
//
//        case pDOWNOUT:
//          ballZ --;
//          ballY --;
//          break;
//
//        default:
//          break;
//      }
//    }
//
//};
//
//class cPaddle {
//  private:
//    int x, y, z;
//    int originalX, originalY, originalZ;
//
//  public:
//    cPaddle() {
//      x = y = z = 0;
//    }
//
//    cPaddle(int posX, int posY, int posZ) {
//      originalX = posX;
//      originalY = posY;
//      originalZ = posZ;
//      x = posX;
//      y = posY;
//      z = posZ;
//    }
//
//    inline void Reset() {
//      x = originalX;
//      y = originalY;
//      z = originalZ;
//    }
//
//    inline void getX() {
//      return x;
//    }
//
//    inline void getY() {
//      return y;
//    }
//
//    inline void getZ() {
//      return z;
//    }
//
//    inline void moveForward() {
//      y++;
//    }
//
//    inline void moveBackward() {
//      y--;
//    }
//
//    inline void moveLeft() {
//      x++;
//    }
//
//    inline void moveRight() {
//      x--;
//    }
//};
//
//class cGameManager {
//  private:
//    int width = 7;
//    int height = 7;
//    int depth = 7;
//    int score1, score2;
//    char forward1, backward1, left1, right1, forward2, backward2, left2, right2;
//    bool quit;
//    cBall*ball;
//    cPaddle *player1;
//    cPaddle *player2;
//
//  public:
//    cGameManager() {
//      quit = false;
//      //      if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//      //
//      //
//      //      if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//      //      else if () {
//      //
//      //      }
//
//      score1 = score2 = 0;
//      ball = new cBall(4, 4, 4);
//      player1 = new cPaddle(4, 4, 0);
//      player2 = new cPaddle(4, 4, 7);
//    }
//
//    ~cGameManager() {
//      delete ball, player1, player2;
//    }
//
//    void ScoreUp(cPaddle *player) {
//      if (player == player1) {
//        score1++;
//      }
//      else if (player == player2) {
//        score2++;
//      }
//
//      ball -> Reset();
//      player1 -> Reset();
//      player2 -> Reset();
//    }
//
//
//    void Draw() {
//
//    }
//
//};





int score = 0;
bool gameOver = false;
int ballX, ballY, ballZ;
int player1X, player1Y, player1Z;
int player2X, player2Y, player2Z;


int ballInitX = 4;
int ballInitY = 4;
int ballInitZ = 4;

int player1InitX = 4;
int player1InitY = 4;
int player1InitZ = 0;

int player2InitX = 4;
int player2InitY = 4;
int player2InitZ = 7;

enum ePLAYER {
  LEFT1 = 0,
  RIGHT1 = 1,
  UP1 = 2,
  DOWN1 = 3,
  STOP1 = 4,

  LEFT2 = 5,
  RIGHT2 = 6,
  UP2 = 7,
  DOWN2 = 8,
  STOP2 = 9
};

enum eBall { // 1 stop state and 10 additional possible directions (5 on each side)
  pSTOP = 0,
  
  pUP = 1,
  pUPLEFT = 2,
  pUPRIGHT = 3,
  pUPIN = 4,
  pUPOUT = 5,
  
  pDOWN = 6,
  pDOWNLEFT = 7,
  pDOWNRIGHT = 8,
  pDOWNIN = 9,
  pDOWNOUT = 10
};

ePLAYER player1Dir;
ePLAYER player2Dir;
eBall ballDir;

void setup() {

  Serial.begin(57600);
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  pinMode (poX, INPUT);
  pinMode (poY, INPUT);
  pinMode (poPress, INPUT);
  pinMode (posZ, INPUT);
  pinMode (posI, INPUT);
  pinMode (13, INPUT);
  pinMode (12, INPUT);

  digitalWrite(poPress, HIGH);

  Timer1.initialize(300); // 520 is the most ideal value as refresh rate! 550 will be really fast but can be acceptable for the game. 515 is really slow
  Timer1.attachInterrupt(renderCube);

  //  cBall ball(4, 4, 4);
  //  cPaddle p1(0, 0, 0);
  //  cPaddle p2(0, 0, 7);

  ballX = ballInitX;
  ballY = ballInitY;
  ballZ = ballInitZ;

  player2X = player2InitX;
  player2Y = player2InitY;
  player2Z = player2InitZ;

  player1X = player1InitX;
  player1Y = player1InitY;
  player1Z = player1InitZ;

 
ballDir = pUPIN;
 // ballDir = random(1, 11);
}


void Input() {
  int xDir = analogRead(poX);
  int yDir = analogRead(poY);
  int zDir = analogRead(poZ);
  int iDir = analogRead(poI);

  if (xDir < 400) {
    player1Dir = LEFT1;

  }
  else if (xDir > 600) {
    player1Dir = RIGHT1;

  }
  else if (yDir < 400) {
    player1Dir = DOWN1;

  }
  else if (yDir > 600) {
    player1Dir = UP1;

  }
  if (zDir < 400) {
    player2Dir = LEFT2;

  }
  else if (zDir > 600) {
    player2Dir = RIGHT2;

  }
  else if (iDir < 400) {
    player2Dir = DOWN2;

  }
  else if (iDir > 600) {
    player2Dir = UP2;

  }
}


void bounce() {
 
  if (ballDir == pUPLEFT){
    ballDir = pUPRIGHT;
  }
  else if (ballDir == pUPRIGHT){
    ballDir = pUPLEFT;
  }
  else if (ballDir == pUPIN){
    ballDir = pUPOUT;
  }
  else if (ballDir == pUPOUT){
    ballDir = pUPIN;
  }
  
  else if (ballDir == pDOWNLEFT){
    ballDir = pDOWNRIGHT;
  }
  else if (ballDir == pDOWNRIGHT){
    ballDir = pDOWNLEFT;
  }
  else if (ballDir == pDOWNIN){
    ballDir = pDOWNOUT;
  }
  else if (ballDir == pDOWNOUT){
    ballDir = pDOWNIN;
  }


}

void Logic() {

  // logic for ball moving
  if (ballDir == pSTOP) {
  }

  else if (ballDir == pUP) {
    ballZ ++;
  }

  else if (ballDir == pUPLEFT) {
    ballZ ++;
    ballX --;
  }

  else if (ballDir == pUPRIGHT) {
    ballZ ++;
    ballX ++;
  }

  else if (ballDir == pUPIN) {
    ballZ ++;
    ballY ++;
  }
  else if (ballDir == pUPOUT) {
    ballZ ++;
    ballY --;
  }

  else if (ballDir == pDOWN) {
    ballZ --;
  }

  else if (ballDir == pDOWNLEFT) {
    ballZ --;
    ballX --;
  }
  else if (ballDir == pDOWNRIGHT) {
    ballZ --;
    ballX ++;
  }

  else if (ballDir == pDOWNIN) {
    ballZ --;
    ballY ++;
  }

  else if (ballDir == pDOWNOUT) {
    ballZ --;
    ballY --;
  }

////////////check for collision and change directions ////////////////////

  if (ballZ == 7 && ballX < (player2X+1) && ballX > (player2X-1) && ballY < (player2Y+1) && ballY > (player2Y-1)) {
    ballDir = random(6,11);
  }
  else if (ballZ == 0 && ballX < (player1X+1) && ballX > (player1X-1) && ballY < (player1Y+1) && ballY > (player1Y-1)) {
    ballDir = random(1,6);
  }

  if (ballX == 7 || ballX == 0 || ballY == 7 || ballY == 0) {
  bounce();
  }
////////check for ball values /////////////////
if (ballX > 7){
  ballX = 7;
  
}
else if (ballY > 7){
  ballY = 7;
}
else if (ballZ > 7){
  ballZ = 7;
  ballDir = random(6,11);
}

if (ballX < 0){
  ballX = 0;
}
else if (ballY < 0){
  ballY = 0;
}
else if (ballZ < 0){
  ballZ = 0;
  ballDir = random(1,6);
}
  

  // control for the first player ////////////////////

  if (player1Dir == LEFT1) {
    player1X ++;
    if (player1X > 6) {
      player1X = 6;
    }
    Serial.println("Left1");
  }

  else if (player1Dir == RIGHT1) {
    player1X --;
    if (player1X < 1) {
      player1X = 1;
    }
    Serial.println("Right1");
  }

  else if (player1Dir == UP1) {
    player1Y++;
    if (player1Y > 6) {
      player1Y = 6;
    }
    Serial.println("Up1");
  }

  else if (player1Dir == DOWN1) {
    player1Y --;
    if (player1Y < 1) {
      player1Y = 1;
    }
    Serial.println("Down1");
  }

  // control for the second player ////////////////

  if (player2Dir == LEFT2) {
    player2X ++;
    if (player2X > 6) {
      player2X = 6;
    }
    Serial.println("Left2");
  }

  else if (player2Dir == RIGHT2) {
    player2X--;
    if (player2X < 1) {
      player2X = 1;
    }
    Serial.println("RIGHT2");
  }

  else if (player2Dir == UP2) {
    player2Y++;
    if (player2Y > 6) {
      player2Y = 6;
    }
    Serial.println("Up2");
  }

  else if (player2Dir == DOWN2) {
    player2Y--;
    if (player2Y < 1) {
      player2Y = 1;
    }
    Serial.println("Down2");
  }

}

void Restart() {
  ballDir = pSTOP;

  ballX = ballInitX;
  ballY = ballInitY;
  ballZ = ballInitZ;

  player2X = player2InitX;
  player2Y = player2InitY;
  player2Z = player2InitZ;

  player1X = player1InitX;
  player1Y = player1InitY;
  player1Z = player1InitZ;
}


void Draw() {
  clearCube();

  setVoxel(ballX, ballY, ballZ);

  setVoxel (player1X - 1, player1Y - 1, 0);
  setVoxel (player1X - 1, player1Y, 0);
  setVoxel (player1X - 1, player1Y + 1, 0);
  setVoxel (player1X, player1Y - 1, 0);
  setVoxel (player1X, player1Y, 0);
  setVoxel (player1X, player1Y + 1, 0);
  setVoxel (player1X + 1, player1Y - 1, 0);
  setVoxel (player1X + 1, player1Y, 0);
  setVoxel (player1X + 1, player1Y + 1, 0);


  setVoxel (player2X - 1, player2Y - 1, 7);
  setVoxel (player2X - 1, player2Y, 7);
  setVoxel (player2X - 1, player2Y + 1, 7);
  setVoxel (player2X, player2Y - 1, 7);
  setVoxel (player2X, player2Y, 7);
  setVoxel (player2X, player2Y + 1, 7);
  setVoxel (player2X + 1, player2Y - 1, 7);
  setVoxel (player2X + 1, player2Y, 7);
  setVoxel (player2X + 1, player2Y + 1, 7);

  Serial.println(player1X);
  Serial.println(player1Y);

  Serial.println(player2X);
  Serial.println(player2Y);



}


///////////////////////////////// /////////////////////////////////
///////////////////////////////// MAIN LOOP! /////////////////////////////////
///////////////////////////////// /////////////////////////////////
int refrsh_time = 300;
bool snake = false;
bool pong = false;

void loop() {
  //  readInputs();
  int initTime, currentTime;
  int delay_time = 100;

  initTime = millis();

  bool gameOver = false;
  while (!gameOver) {
    Input();


    currentTime = millis();
    if (currentTime - initTime > refrsh_time) {
      Logic();
      Draw();
      initTime = millis();
    }

    //Serial.println("Refreshes just now");
  }
}
