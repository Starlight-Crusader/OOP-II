#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node  {
        int content;
        struct Node *prev;
} Node;

typedef struct Tower {
        Node *top;
        int len;
} Tower;

int addElem();
int rmElem();
int checkMv();
int drawState();

int main() {
	Tower towers[3];
	int from, to;
	int dim;
	int val;
	int moves = 0;

	printf("Input the number of rings: ");
	scanf("%i", &dim);

	towers[0].top = (Node*)malloc(sizeof(Node));
	towers[1].top = (Node*)malloc(sizeof(Node));
	towers[2].top = (Node*)malloc(sizeof(Node));

	towers[0].top->content = 0; towers[0].top->prev = NULL; towers[0].len = 0;
	towers[1].top->content = 0; towers[1].top->prev = NULL; towers[1].len = 0;
	towers[2].top->content = 0; towers[2].top->prev = NULL; towers[2].len = 0;

	for(int i = dim; i > 0; i--) {
		towers[0].len = addElem(&towers[0].top, towers[0].len, i);
	}

	while(1) {
		printf("====================\n");

		if(towers[2].len == dim) {
			system("clear");

                        printf("Congrats - You've won, after %i moves!\n", moves);
			printf("Final state of the game:\n");

			printf("====================\n");
			drawState(towers[0].top, towers[1].top, towers[2].top, towers[0].len, towers[1].len, towers[2].len, dim);

                        break;
                }

		drawState(towers[0].top, towers[1].top, towers[2].top, towers[0].len, towers[1].len, towers[2].len, dim);

		printf("Input a move in the following form: SOURCE (INT) > TARGET (INT) (example: '1 > 2');\n");
		printf("OR input: '0 > 0' to stop the game\n");
		printf("MOVE: ");
		scanf("%i > %i", &from, &to);

		if((from == 0) && (to == 0)) {
			system("clear");
                        printf("Game has been finished without achieveng the goal :(\n");
			printf("Final state of the game after %i moves:\n", moves);
			drawState(towers[0].top, towers[1].top, towers[2].top, towers[0].len, towers[1].len, towers[2].len, dim);

                        break;
               	}

		if(from == to) {
			printf("This move is illegal!\n");
			continue;
		} else if(checkMv(towers[from-1].top, towers[to-1].top, towers[from-1].len, towers[to-1].len)) {
			continue;
		}

		val = rmElem(&towers[from-1].top, &towers[from-1].len);
		towers[to-1].len = addElem(&towers[to-1].top, towers[to-1].len, val);

		moves++;
	}

	return 0;
};

int addElem(Node **t, int l, int v) {
	Node *tempNode;

	if(l == 0) {
		tempNode = *t;
		tempNode->content = v;
	} else {
		tempNode = (Node*)malloc(sizeof(Node));

		tempNode->content = v;
		tempNode->prev = *t;

		*t = tempNode;
	}

	return l + 1;
};

int rmElem(Node **t, int *l) {
	int val;
	Node *tempPntr;

	if(*l == 1) {
		tempPntr = *t;
		val = tempPntr->content;
		tempPntr->content = 0;

		*l = *l - 1;

		return val;
	} else {
		Node *nodeToFree = *t;

		val = nodeToFree->content;
		*t = nodeToFree->prev;

		free(nodeToFree);
		*l = *l - 1;

		return val;
	}
};

int checkMv(Node *source, Node *target, int sLen, int tLen) {
	if((sLen == 0) || ((source->content > target->content) && (target->content != 0))) {
		printf("This move is illegal!\n"); return 1;
	}

	return 0;
};

int drawState(Node *t1, Node *t2, Node *t3, int l1, int l2, int l3, int n) {
	int canvas[n][7];
	int start;

	for(int i = 0; i < n; i++) {
                for(int j = 0; j < 7; j++) {
                        canvas[i][j] = 0;
                }
        }

	Node *currentNode = NULL;

	start = n - l1;
        currentNode = t1;

        for(int i = 0; i < l1; i++) {
                canvas[start][1] = currentNode->content;
                currentNode = currentNode->prev;

		start++;
        }

	start = n - l2;
        currentNode = t2;

        for(int i = 0; i < l2; i++) {
                canvas[start][3] = currentNode->content;
                currentNode = currentNode->prev;

		start++;
        }

	start = n - l3;
        currentNode = t3;

        for(int i = 0; i < l3; i++) {
                canvas[start][5] = currentNode->content;
                currentNode = currentNode->prev;

		start++;
        }

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 7; j++) {
			if(canvas[i][j] == 0) {
				printf(" ");
			} else {
				printf("%i", canvas[i][j]);
			}
		}

		printf("\n");
	}

	printf(" | | | \n");
	printf("-------\n");
	printf(" T T T \n");
	printf(" 1 2 3 \n");
	printf("====================\n");
};
