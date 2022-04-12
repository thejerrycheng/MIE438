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


///////////////////////////////// SNAKE GAME /////////////////////////////////

////////////////////////////////////////////////////
/////////////SNAKE GAME SETUP //////////////////////
////////////////////////////////////////////////////

int fruitX, fruitY, fruitZ;
int headX, headY, headZ;
int tailX[512], tailY[512], tailZ[512];
int nTail = 0;

int score = 0;
int highestScore = 0;

const int width = 8;
const int height = 8;
const int depth = 8;


bool gameOver = false;

// define directions
enum eDIRECTION {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  STOP
};

eDIRECTION dir;

enum eINPUT {
  INLEFT,
  INRIGHT,
  INUP,
  INDOWN,
  INSTOP
};

eINPUT inputs;

#define FORWARD    0       // these values is what the "snake" looks at to decide-
#define BACKWARD   1       // the direction the snake will travel
#define LEFT       2
#define RIGHT      3
#define UP         4
#define DOWN       5


///////////////////////// setup /////////////////////////////////

const int poX = A1;
const int poY = A2;
const int poZ = A3;
const int poI = A4;
const int poPress = 7;
const int posZ = A3;
const int posI = A4;


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

  dir = STOP;

  headX = width / 2;
  headY = depth / 2;
  headZ = height / 2;

  fruitX = random(0, 8);
  fruitY = random(0, 8);
  fruitZ = random(0, 8);

  score = 0;
  //  start_animation();
  //  draw();
}


void draw() {
  clearCube();
  setVoxel(headX, headY, headZ);
  setVoxel (fruitX, fruitY, fruitZ);
  for (int i = 0; i < nTail; i++) {
    setVoxel(tailX[i], tailY[i], tailZ[i]);
  }
}



void input() {
  int xDir = analogRead(poX);
  int yDir = analogRead(poY);
  int zDir = analogRead(poZ);
  int iDir = analogRead(poI);

  if (xDir < 400) {
    inputs = INUP;
    if (dir == BACKWARD) {

    }
    else {
      dir = FORWARD;
    }
    Serial.println("up");
  }
  else if (xDir > 600) {
    inputs = INDOWN;
    if (dir == FORWARD) {

    }
    else {
      dir = BACKWARD;
    }
    Serial.println("down");
  }
  else if (yDir < 400) {
    inputs = INRIGHT;
    if (dir == LEFT) {

    }
    else {
      dir = RIGHT;
    }
    Serial.println("right");
  }
  else if (yDir > 600) {
    inputs = INLEFT;
    if (dir == RIGHT) {

    }
    else {
      dir = LEFT;
    }
    Serial.println("left");
  }
  else if (zDir > 600) {
    if (dir == UP) {

    } else {
      dir = DOWN;
    }
    Serial.println ("down");
  }
  else if (zDir < 400) {
    if (dir == DOWN) {

    }
    else {
      dir = UP;
    }
    Serial.println("up");
  }

  else if (iDir > 600) {
    if (dir == RIGHT) {

    }
    else {
      dir = LEFT;
    }
    Serial.println ("left");
  }
  else if (iDir < 400) {
    if (dir == LEFT) {

    }
    else {
      dir = RIGHT;
    }
    Serial.println("right");
  }


  //  else if (digitalRead(13) == HIGH) {
  //    if (dir == DOWN) {
  //
  //    } else {
  //      dir = UP;
  //    }
  //    Serial.println ("up");
  //  }
  //  else if (digitalRead(12) == HIGH) {
  //    if (dir == UP) {
  //
  //    }
  //    else {
  //      dir = DOWN;
  //    }
  //    Serial.println("down");
  //  }

}


void logic() {
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prevZ = tailZ[0];
  int prev2X, prev2Y, prev2Z;

  tailX[0] = headX;
  tailY[0] = headY;
  tailZ[0] = headZ;

  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    prev2Z = tailZ[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    tailZ[i] = prevZ;
    prevX = prev2X;
    prevY = prev2Y;
    prevZ = prev2Z;

  }
  /////////////// change head position based on the input commands //////////////
  if (dir == FORWARD) {
    headY ++;
    //Serial.println("moved forward");
  }

  else if (dir == BACKWARD) {
    headY --;
    //Serial.println("moved backward");
  }

  else if (dir == LEFT) {
    headX --;
    // Serial.println("moved left");
  }

  else if (dir == RIGHT) {
    headX ++;
    //  Serial.println("moved right");
  }

  else if (dir == UP) {
    headZ ++;
    // Serial.println("moved up");
  }

  else if (dir == DOWN) {
    headZ --;
    //  Serial.println("moved down");
  }

  //////////make sure head does not overflow ////////////
  if (headX > 8) {
    headX = 0;
  }
  if (headY > 8) {
    headY = 0;
  }
  if (headZ > 8) {
    headZ = 0;
  }
  if (headX < 0) {
    headX = 7;
  }
  if (headY < 0) {
    headY = 7;
  }
  if (headZ < 0) {
    headZ = 7;
  }

  if (headX == fruitX && headY == fruitY && headZ == fruitZ) {
    score ++;
    nTail ++;
    Serial.print("The score is: ");
    Serial.println (score);
    fruitX = random(0, 8);
    fruitY = random(0, 8);
    fruitZ = random(0, 8);
  }

  for (int i = 0; i < nTail; i++) {
    if (tailX[i] == headX && tailY[i] == headY && tailZ[i] == headZ ) {
      gameOver = true;
    }
  }
}

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





///////////////////////////////// /////////////////////////////////
///////////////////////////////// MAIN LOOP! /////////////////////////////////
///////////////////////////////// /////////////////////////////////
int refrsh_time = 400;

void loop() {
  //  readInputs();
  int initTime, currentTime;
  int delay_time = 100;
//  gameOver = false;
  initTime = millis();

  while (currentTime - initTime < 5000) {
    text("0123456789", 10);

    currentTime = millis();
    delay(delay_time);
    delay_time -= 1;
    //    Serial.println("Game to be Started");
  }
  initTime = millis();
  //  for (int i = 0; i < 20000; i++) {
  //    rain();
  //    renderCube();
  //    Serial.print("Rain start");
  //  }
//  clearCube();
//  renderCube();

  while (!gameOver) {

    input();

    currentTime = millis();
    if (currentTime - initTime > refrsh_time) {
      logic();
      draw();
      initTime = millis();
    }
    Serial.println("Refreshes just now");
    // else : do nothing and loop the while loop again for user inputs and logic
  }
  while (currentTime - initTime < 1000) {
    rain();
    currentTime = millis();
    delay(0.9);
    //    Serial.println("Game to be Started");
  }
  initTime = millis();

}





///////////////////////////////// PONG GAME /////////////////////////////////

enum eDir { // 1 stop state and 10 additional possible directions (5 on each side)
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





class cBall {
  private:
    int ballX, ballY, ballZ;
    int originalX, originalY, originalZ;
    eDir direction;

  public:
    cBall(int posX, int posY, int posZ) {
      originalX = posX;
      originalY = posY;
      originalZ = posZ;
      ballX = posX;
      ballY = posY;
      ballZ = posZ;
      direction = pSTOP;
    }

    void reset() {
      ballX = originalX;
      ballY = originalY;
      ballZ = originalZ;
      direction = pSTOP;
    }

    void changeDirection(eDir d) {
      direction = d;
    }

    inline int getX() {
      return ballX;
    }

    inline int getY() {
      return ballY;
    }

    inline int getZ() {
      return ballZ;
    }

    inline eDir getDirection() {
      return direction;
    }
    void randomDirection() {
      direction = (eDir)(random(1, 11)); // randomly select a direction to move to from 1-10
    }

    void Move() {
      switch (direction) {
        case pSTOP:
          break;

        case pUP:
          ballZ ++;
          break;

        case pUPLEFT:
          ballZ ++;
          ballX --;
          break;

        case pUPRIGHT:
          ballZ ++;
          ballX ++;
          break;


        case pUPIN:
          ballZ ++;
          ballY ++;
          break;

        case pUPOUT:
          ballZ ++;
          ballY --;
          break;

        case pDOWN:
          ballZ --;
          break;

        case pDOWNLEFT:
          ballZ --;
          ballX --;
          break;

        case pDOWNRIGHT:
          ballZ --;
          ballX ++;
          break;

        case pDOWNIN:
          ballZ --;
          ballY ++;
          break;

        case pDOWNOUT:
          ballZ --;
          ballY --;
          break;

        default:
          break;
      }
    }

};





////////////////////////////////////////////////////
/////////////PONG GAME SETUP //////////////////////
////////////////////////////////////////////////////
