#include <stdio.h>

int main() {
	printf(“\033[0;33m”);

	int n;

	printf("n = ");
	scanf("%d", &n);
	printf("\n");

	int canvas[n][n];

	int center, c1, c2, c3;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			canvas[i][j] = 0;
		}
	}

	center = n / 2 - 1;
        c1 = n; c2 = 0;

        while(c1 > 0) {
                for(int i = c2; i < n - c2; i++) {
                        canvas[center][i] = 1;
                }

                center++;
		if(center % 2 == 0) {
			c2 += 2;
			c1 -= 4;
		} else {
			c2 += 1;
			c1 -= 2;
		}
        }

	center = n / 2;

	c1 = 1;

	for(int i = 0; i < center; i++) {
		c2 = center - c1 / 2;

		for(int j = 0; j < c1; j++) {
			canvas[i][c2 + j] = 1;
		}

		if((i % 2 == 0) && (i > 0)) {
			c1 += 2;
		}
	}

	int row = n - 1;
        c1 = n; c2 = 0;

        while(c1 > 0) {
                for(int i = c2; i < n - c2; i++) {
                        canvas[row][i] = 1;
                }

                row--;

		// if(row % 2 == 0) {
			c2 += 1;
		// }

                c1 -= 2;
        }

	row = n - 1;
        c1 = n - 2; c2 = 0;

        while(c1 > 0) {
                for(int i = c2; i < n - c2; i++) {
                        canvas[row][i] = 0;
                }

                row--;
                c1 -= 2;
                c2 += 2;
        }

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(canvas[i][j] == 1) {
				printf("*");
			} else {
				printf(" ");
			}
		}

		printf("\n");
	}

    	return 0;
}
