#include <TFT.h>
#include <SPI.h>

TFT TFTscreen = TFT(10, 9, 8);
int x = 4;
int y = 0;

int currPiece[5][5];
int board[17][12] = {
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int allShapes[7][5][5] = {
  // L
  {
    {0, 0, 0, 0, 0}, 
    {0, 0, 1, 0, 0}, 
    {0, 0, 1, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
  },
  // J
  {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0}, 
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
  },
  // S
  {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
  }, 
  // Z
  {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
  },
  // O
  {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
  },
  // I
  {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
  },
  // T
  {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
  }
};
int currShape;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  randomSeed(analogRead(A5));
  TFTscreen.begin();
  TFTscreen.background(0,0,0);
  TFTscreen.stroke(255,255,255);
  currShape = random(0, 7);
  Serial.begin(9600);
}
int checkFreeze(int shape[5][5]) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(board[y+1+i][x+j] != 0 && shape[i][j] == 1) {
        if(shape[i+1][j] != 1 || i == 4 || j == 4) {
          return -1;
        }
      }
    }
  }
  return 1;
}
void updatePos(int shape[5][5]) {
  if(checkFreeze(currPiece) == 1) {
    for(int i = 4; i >= 0; i--) {
      for(int j = 0; j < 5; j++) {
        if(shape[i][j] == 1) {
          board[y+i+1][x+j] = currShape + 1;
          board[y+i][x+j] = 0;
        }
      }
    }
    y++;
  }
}
void rotate90Clockwise(int arr[5][5])
{
 
    // Traverse each cycle
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4 - i; j++) {
        int temp = arr[i][j];
        arr[i][j] = arr[4 - j][4 - i];
        arr[4 - j][4 - i] = temp;
      }
    }
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 5; j++) {
        int temp = arr[i][j];
        arr[i][j] = arr[4 - i][j];
        arr[4 - i][j] = temp;
      }
    }
}
void defineShape(int arr[5][5]) {
  for(int i = 0; i < 5; i++) {
    arr[i][0] = allShapes[currShape][i][0];
    arr[i][1] = allShapes[currShape][i][1];
    arr[i][2] = allShapes[currShape][i][2];
    arr[i][3] = allShapes[currShape][i][3];
    arr[i][4] = allShapes[currShape][i][4];
  }
}
void movePiece(int increment, int arr[5][5]) {
  int canMove = 1;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(board[y+i][x+j+increment] != 0 && arr[i][j] == 1) {
        if(arr[i][j+increment] != 1 || (j+increment) == 5 || (j+increment) == -1) {
          canMove = -1;
        }
      }
    }
  }
  /*
  if(canMove == 1) {
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        if(arr[i][j] == 1) {
          board[y+i][x+j+increment] = currShape+1;
          board[y+i][x+j] = 0;
        }
      }
    }
  }
  */
  if(canMove == 1) {
      for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
          if(arr[i][j] == 1) {
            board[y+i][x+j] = 0;
          }
        }
      }
      x += increment;
      for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
          if(arr[i][j] == 1){
            board[y+i][x+j] = 1; 
          }
        }
      }
    }
}

int change = 1;
void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(A0) < 500) {
    movePiece(-1, currPiece);
  }
  else if(analogRead(A0) > 540) {
    movePiece(1, currPiece);
  }
  if(checkFreeze(currPiece) == -1) {
    currShape = random(0, 7);
    x = 4; 
    y = 0;
  }
  if(change == 1) {
    rotate90Clockwise(currPiece);
    change = 0;
  }
  
  TFTscreen.background(255, 0, 0);
  defineShape(currPiece);
  Serial.println(checkFreeze(currPiece));
  updatePos(currPiece);
  for(int i = 0; i < 16; i++) {
    for(int j = 1; j < 11; j++) {
      if(board[i][j] > 0) {
        TFTscreen.fill(255, 255, 255);
        TFTscreen.rect(i*10, 114-(j*10), 10, 10);
      }
    }
  }
  delay(64);
}
