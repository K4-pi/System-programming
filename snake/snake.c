#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>

int i, j, score, height = 15, width = 30;
int fruitPos[2];
int playerPos[] = {10, 15};

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

void fruit() {
  
  srand(time(0));

  label1:
    fruitPos[0] = rand() % width;
    if (fruitPos[0] == 0 || fruitPos[0] >= width - 1) 
      goto label1;
  
  label2:
    fruitPos[1] = rand() % height;
    if (fruitPos[1] == 0 || fruitPos[1] >= height - 1)
      goto label2;
}

void player() {
  
  //player input function
  char input = getch();

  switch (input) {
    case 's':
      playerPos[0]++;
      break;

    case 'w':
      playerPos[0]--;
      break;

    case 'd':
      playerPos[1]++;
      break;

    case 'a':
      playerPos[1]--;
      break;

    case 'x':
      exit(1);

    default:
      break;
  }
}

void draw() {
  
  system("clear");
  printf("This game requires NerdFont for symbols!\n\n");

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (i == height - 1 || i == 0 || j == width - 1 || j == 0) {
        printf("#");
      }
      else if (i == playerPos[0] && j == playerPos[1]) {
        printf("󱔎");
      }
      else if (i == fruitPos[1] && j == fruitPos[0]) {
        printf("");
      }
      else {
        printf(" ");     
      }
    }
    printf("\n");
  }
  printf("\nWASD - movement\n");
  printf("\nscore: %d\n", score);
  printf("X to quit\n");
}

int main() {
  
  fruit();
  score = 0;
  
  while (1) {
    
    if (playerPos[0] >= height - 1 || playerPos[1] >= width - 1 || playerPos[0] == 0 || playerPos[1] == 0) {
      printf("\nGAME OVER \n");
      exit(1);
    }
    if (playerPos[0] == fruitPos[1] && playerPos[1] == fruitPos[0]) {
      fruit();
      score += 10;
    }
    draw();
    player();
  }
}
