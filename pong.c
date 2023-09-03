#include <stdio.h>

void render();
void playerLeftMover(int direction);
void playerRightMover(int direction);
void control();
void ballMover();
void scoreHandler();

int playerRight1 = 11;
int playerRight2 = 12;
int playerRight3 = 13;

int playerLeft1 = 11;
int playerLeft2 = 12;
int playerLeft3 = 13;

int playerLeftScore = 0;
int playerRightScore = 0;

int ballX;
int ballY;
int ballDirectionX = 1;  // 1 or -1
int ballDirectionY = 0;  // 1 or 0 or -1
int gameOver = 1;

const int ballStartX = 39;
const int ballStartY = 12;

int main() {
    ballX = ballStartX;
    ballY = ballStartY;
    render();
    while (gameOver) {
        control();
        ballMover();
        scoreHandler();
        render();
    }
    if (!gameOver) {
        printf("GAME OVER\n");
    }
    return 0;
}

void render() {
    printf("\033[?25l\033[?2j\033[0;0H");
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            if (y == 0) {
                if (x == 3) {
                    printf("left player: %.2d", playerLeftScore);
                } else if (x == 62) {
                    printf("right player: %.2d", playerRightScore);
                } else if ((x < 3) || (17 < x && x < 61) || (77 <= x)) {
                    printf("=");
                }
            } else if (y == 24) {
                printf("=");
            } else {
                if (x == 0 || x == 79) {
                    printf("|");
                } else if (x == 2) {
                    if (y == playerLeft1) {
                        printf("\\");
                    } else if (y == playerLeft2) {
                        printf("|");
                    } else if (y == playerLeft3) {
                        printf("/");
                    } else
                        printf(" ");
                } else if (x == 77) {
                    if (y == playerRight1) {
                        printf("/");
                    } else if (y == playerRight2) {
                        printf("|");
                    } else if (y == playerRight3) {
                        printf("\\");
                    } else
                        printf(" ");
                } else if (y == ballY && x == ballX) {
                    printf("0");
                } else if (x == 39) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void scoreHandler(){
  if(ballX <= 1) {
    playerRightScore++;
    ballX = ballStartX;
    ballY = ballStartY;
    ballDirectionY = 0;
    ballDirectionX = -1;
  } else if (ballX >= 78){
    playerLeftScore++;
    ballX = ballStartX;
    ballY = ballStartY;
    ballDirectionY = 0;
    ballDirectionX = 1;
  }

}

void ballMover() {
    if (ballDirectionX == 1) {
        if (ballX + 1 == 77) {
            if (ballY != playerRight1 && ballY != playerRight2 && ballY != playerRight3) {
                ballX++;
            } else if (ballY == playerRight1) {
                if (ballDirectionY == 0) {
                    ballDirectionY = -1;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = 0;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = -1;
                }
                ballDirectionX = -1;
            } else if (ballY == playerRight2) {
                if (ballDirectionY == 0) {
                    ballDirectionY = 0;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = -1;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = 1;
                }
                ballDirectionX = -1;
            } else if (ballY == playerRight3) {
                if (ballDirectionY == 0) {
                    ballDirectionY = 1;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = 1;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = 0;
                }
                ballDirectionX = -1;
            }
        } else if (ballX + 1 != 79) {
            ballX++;
        }
    }

    if (ballDirectionX == -1) {
        if (ballX - 1 == 2) {
            if (ballY != playerLeft1 && ballY != playerLeft2 && ballY != playerLeft3) {
                ballX--;
            } else if (ballY == playerLeft1) {
                if (ballDirectionY == 0) {
                    ballDirectionY = -1;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = 0;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = -1;
                }
                ballDirectionX = 1;
            } else if (ballY == playerLeft2) {
                if (ballDirectionY == 0) {
                    ballDirectionY = 0;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = -1;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = 1;
                }
                ballDirectionX = 1;
            } else if (ballY == playerLeft3) {
                if (ballDirectionY == 0) {
                    ballDirectionY = 1;
                } else if (ballDirectionY == 1) {
                    ballDirectionY = 1;
                } else if (ballDirectionY == -1) {
                    ballDirectionY = 0;
                }
                ballDirectionX = 1;
            }
        } else if (ballX - 1 != 0) {
            ballX--;
        }
    }

    if (ballY - 1 == 0) {
        ballDirectionY = 1;
    } else if (ballY + 1 == 24) {
        ballDirectionY = -1;
    }

    if (ballDirectionY == 1) {
        ballY++;
    } else if (ballDirectionY == -1) {
        ballY--;
    }
}

void control() {
    char direction = getchar();
    switch (direction) {
        case 'a':
            if (playerLeft1 != 1) {
                int dir = 1;
                playerLeftMover(-1);
            }
            break;
        case 'z':
            if (playerLeft3 != 23) {
                int dir = 1;
                playerLeftMover(1);
            }
            break;
        case 'k':
            if (playerRight1 != 1) {
                int dir = 1;
                playerRightMover(-1);
            }
            break;
        case 'm':
            if (playerRight3 != 23) {
                int dir = 1;
                playerRightMover(dir);
            }
            break;
        case ' ':
            break;
        default:
            break;
    }
}

void playerLeftMover(int direction) {
    playerLeft1 = playerLeft1 + (1 * direction);
    playerLeft2 = playerLeft2 + (1 * direction);
    playerLeft3 = playerLeft3 + (1 * direction);
}

void playerRightMover(int direction) {
    playerRight1 = playerRight1 + (1 * direction);
    playerRight2 = playerRight2 + (1 * direction);
    playerRight3 = playerRight3 + (1 * direction);
}
