#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BOARDSIZE 64

int get_neighbors(int x, int y, int world[BOARDSIZE][BOARDSIZE]);
void gameloop(int steps, int world[BOARDSIZE][BOARDSIZE]);
void draw(int world[BOARDSIZE][BOARDSIZE]);
void step(int world[BOARDSIZE][BOARDSIZE]);

int main(void) {
	int world[BOARDSIZE][BOARDSIZE];
	int y = BOARDSIZE / 2;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			world[i][j] = 0;
		}
	}
	world[y-8][y-8] = 1;
	world[y-9][y-8] = 1; world[y-9][y-9] = 1;
	world[y-10][y-8] = 1;  world[y-10][y-10] = 1;
	world[y-11][y-7] = 1; 
	world[y-12][y-6] = 1;

	gameloop(100, world);
}

void step(int world[BOARDSIZE][BOARDSIZE]) {
    int nworld[BOARDSIZE][BOARDSIZE];
    int n;
    for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			n = get_neighbors(i, j, world);
            if (world[i][j] == 1) {
                if (n == 2 || n == 3) {
                    nworld[i][j] = 1;
                } else if (n < 2) {
                    nworld[i][j] = 0;
                } else if (n > 3) {
                    nworld[i][j] = 0;
                }
            }
            else {
                if (n == 3) {
                    nworld[i][j] = 1;
                } else {
                    nworld[i][j] = 0;
                }
            }
		}
	}
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
		    world[i][j] = nworld[i][j];
		}
	}
}

int get_neighbors(int x, int y, int world[BOARDSIZE][BOARDSIZE]) {
	int n = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int sx = x + i;
			int sy = y + j;
			if ( !((sy < 0) || (sx < 0) || (sy > (BOARDSIZE - 1)) || (sx > (BOARDSIZE - 1)) || ((i == 0) && (j == 0)) ) ) {
				n += world[sx][sy];
			}
		}
	}
	return n;
	
}

void gameloop(int steps, int world[BOARDSIZE][BOARDSIZE]) {
	for (int i = 0; i < steps; i++) {
		draw(world);
		step(world);
		usleep(150000);
		system("clear");
	}
}

void draw(int world[BOARDSIZE][BOARDSIZE]) {
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (world[i][j] == 0) {
				printf(" ");
			} else {
				printf("#");
			} if (j == BOARDSIZE - 1) printf("\n");
		}
	}
}
