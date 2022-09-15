#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node  {
	int content;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *head, *tail;
	int len;
} Queue;

int input();
int printQueue();
int deallocateMemory();

int main() {
	Queue q;
	q.head = NULL; q.tail = NULL; q.len = 0;

	q.len = input(&q.head, &q.tail);
	printQueue(q.head, q.tail, q.len);
	return 0;
};

int input(Node **h, Node **t) {
	int option = 0; int n = 0;
	Node *newNode;

	printf("1. Manual input;\n");
        printf("2. Input from a file\n");
        printf("? - ");

        scanf("%i", &option);

        if(option == 1) {
		char input[256];

                while(1) {
                        printf("Type a number to be enqueued (OR 'S' to stop) (TOTAL = %i): ", n);
                        scanf("%s", &input);

                        if(!strcmp(input, "S")) {
				if(n == 0) {
					printf("Input at leat 1 number...\n");
					continue;
				} else {
					return n;
				}
                        } else {
                                if(n == 0) {
                                        newNode = (Node*)malloc(sizeof(Node));
                                        newNode->content = atoi(input);

                                        *h = newNode;
                                        *t  = newNode;

					n++;
                                } else {
                                        newNode = (Node*)malloc(sizeof(Node));
                                        newNode->content = atoi(input);

                                        newNode->next = *t;
                                        *t = newNode;

					n++;
                                }
                        }
                }
        } else {
		FILE *input;
		char nameOfFile[256];

		input = fopen(nameOfFile, "r");

		fscanf(input, "%i", &n);

		for(int i = 0; i < n; i++) {
			if(i == 0) {
                        	newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  &newNode->content);

                                h = newNode;
                                t  = newNode;
                        } else {
                                newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  &newNode->content);

                                newNode->next = t;
                                t = newNode;
                        }
		}

		fclose(nameOfFile);

		return n;
	}

	return -1;
};

int printQueue(Node *h, Node *t, int n) {
	printf("%i: ", n);
	printf("TAIL -> ");

	Node *currentNode; currentNode = t;

	for(int i = 1; i < n; i++) {
		printf("%i - ", currentNode->content);
		currentNode = currentNode->next;
	}

	printf("%i <-", currentNode->content);
	printf("HEAD\n");

	return 0;
};

int deallocateMemory(Node *h, Node *t, int n) {
	Node *nodeToDeallocate;
	nodeToDeallocate = t;

	for(int i = 1; i < n; i++) {
		nodeToDeallocate = t;
		t = t->next;

		free(nodeToDeallocate);
	}

	free(t);

	return 0;
};
