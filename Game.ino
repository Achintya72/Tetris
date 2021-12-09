#include <TFT.h>
#include <SPI.h>

TFT TFTscreen = TFT(10, 9, 8);
int board[16][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
// int colors[7][3] = ;
int allShapes[7][4][4][4] = 
{
  {
    {
      {0, 1}, 
      {0, 1}, 
      {1, 1}
    }, 
    {
      {1, 0, 0}, 
      {1, 1, 1}
    },
    {
      {1, 1},
      {1, 0},
      {1, 0}
    },
    {
      {1, 1, 1}, 
      {0, 0, 1}
    }
 },
 {
    {
      {1, 0}, 
      {1, 0}, 
      {1, 1}
    }, 
    {
      {1, 1, 1}, 
      {1, 0, 0}
    },
    {
      {1, 1},
      {0, 1},
      {0, 1}
    },
    {
      {0, 0, 1},  
      {1, 1, 1}
    }
 },
 {
  {
    {0, 1, 1},
    {1, 1, 0}
  },
  {
    {1, 0},
    {1, 1},
    {0, 1}
  },
  {
    {0, 1, 1},
    {1, 1, 0}
  },
  {
    {1, 0},
    {1, 1},
    {0, 1}
  }
 },
 {
  {
    {1, 1, 0},
    {0, 1, 1}
  },
  {
    {0, 1},
    {1, 1},
    {1, 0}
  },
  {
    {1, 1, 0},
    {0, 1, 1}
  },
  {
    {0, 1},
    {1, 1},
    {1, 0}
  }
 },
 {
  {
    {1, 1},
    {1, 1}
  },
  {
    {1, 1},
    {1, 1}
  },
  {
    {1, 1},
    {1, 1}
  },
  {
    {1, 1},
    {1, 1}
  }
 },
 {
  {
    {1},
    {1},
    {1},
    {1}
  },
  {
    {1, 1, 1, 1}
  },
  {
    {1},
    {1},
    {1},
    {1}
  },
  {
    {1,1,1,1}
  }
 },
 {
  {
    {0,1,0},
    {1,1,1}
  },
  {
    {1,0},
    {1,1},
    {1,0}
  },
  {
    {1, 1, 1},
    {0, 1, 0}
  },
  {
    {0, 1},
    {1, 1},
    {0, 1}
  }
 }
};
int allHeights[7][4] = {
  {3, 2, 3, 2},
  {3, 2, 3, 2},
  {2, 3, 2, 3},
  {2, 3, 2, 3},
  {2, 2, 2, 2},
  {4, 1, 4, 1},
  {2, 3, 2, 3}
};
int allWidths[7][4] = {
  {2, 3, 2, 3},
  {2, 3, 2, 3},
  {3, 2, 3, 2},
  {3, 2, 3, 2},
  {2, 2, 2, 2},
  {1, 4, 1, 4},
  {3, 2, 3, 2}
};
int currShape;
int currRotation; 
int x;
int y;
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
  currShape = 0;
  currRotation = 0;
  x = 4;
  y = 0;
}
int checkFreeze() {
  if(y + allHeights[currShape][currRotation]+1 > 20) {
    return 1;
  }
  for(int i = 0; i < allHeights[currShape][currRotation]; i++) {
    for(int j = 0; j < allWidths[currShape][currRotation]; j++) {
      if(board[y+1+i][x+j] != 0 && allShapes[currShape][currRotation][i][j] == 1) {
        if(allShapes[currShape][currRotation][i+1][j] != 1 || i == 3 || j == 3) {
          return 1;
        }
      }
    }
  }
  return -1;
}
int change = 1;
int increment = 0;
void loop() {
  // put your main code here, to run repeatedly:
  TFTscreen.background(0,0,0);
  if(change == 2) {
    change = 1;
    if(checkFreeze() == -1) {
      for(int i = allHeights[currShape][currRotation] - 1; i >= 0; i--) {
        for(int j = 0; j < allWidths[currShape][currRotation]; j++) {
          if(allShapes[currShape][currRotation][i][j] == 1) {
            board[y+i+1][x+j] = currShape;
            board[y+i][x+j] = 0;
          }
        }
      }
      y += 1;
    }
  }
  if(analogRead(A0) < 520) {
    increment = -1;
  }
  else if(analogRead(A0) > 524) {
    increment = 1;
  }
  if(x+allWidths[currShape][currRotation]+increment <= 10 && x+increment >= 0) {
    int canMove = 1;
    for(int i = 0; i < allHeights[currShape][currRotation]; i++) {
      for(int j = 0; j < allWidths[currShape][currRotation]; j++) {
        if(board[y+i][x+increment+j] != 0 && allShapes[currShape][currRotation][i][j] == 1) {
          if(allShapes[currShape][currRotation][i][j+increment] != 1) {
            canMove = -1;
          }
        }
      }
    }
    if(canMove == 1) {
      for(int i = 0; i < allHeights[currShape][currRotation]; i++) {
        for(int j = 0; j < allWidths[currShape][currRotation]; j++) {
          board[y+i][x+j] = 0;
        }
      }
      x += increment;
      for(int i = 0; i < allHeights[currShape][currRotation]; i++) {
        for(int j = 0; j < allWidths[currShape][currRotation]; j++) {
          if(allShapes[currShape][currRotation][i][j] == 1){
            board[y+i][x+j] = 1; 
          }
        }
      }
    }
  }
  
  if(checkFreeze() == 1) {
    currShape = random(0, 7);
    y = 0;
    x = 4;
    currRotation = 0;
    for(int i = 0; i < 15; i++) {
      
    }
  } 
  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < 10; j++) {
      if(board[i][j] > 0) {
          // {{0,255,255}, {255, 165, 0}, {0, 255, 0}, {128, 0, 128}, {255, 0, 255}, {255, 0, 0}, {0, 0, 255}}
          TFTscreen.fill(255, 255, 255);
          TFTscreen.rect(i*10, 114 - (j*10), 10, 10);
      }
    }
  }
  change++;
  delay(64);
}
