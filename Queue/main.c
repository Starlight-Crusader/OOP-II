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
	int option;
	Queue q;
	q.head = NULL; q.tail = NULL; q.len = 0;


	while(1) {
		printf("===================\n");
		printf("Pick a procedure from the list below:\n");

		printf("'1' - Create a new queue and enter some values;\n");
		printf("'2' - Print all the values from the queue;\n");
		printf("'3' - Clear the queue;\n");
		printf("'4' - Stop the program (the memory will be automatically deallocated)\n");

		scanf("%i", &option);

		switch(option) {
			case 1: q.len = input(&q.head, &q.tail); break;
			case 2: printQueue(q.head, q.tail, q.len); break;
			case 3:
				deallocateMemory(q.head, q.tail, q.len);
				q.head = NULL; q.tail = NULL; q.len = 0;
				break; 
			case 4: deallocateMemory(q.head, q.tail, q.len);
                                q.head = NULL; q.tail = NULL; q.len = 0;
                                return 0;
			default: printf("This option is probably not in the list ..."); break;
		}
	}
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
				return n;
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

		while(1) {
			printf("Enter the name of file (OR 'ABORT' to abort input procedure): ");
                	scanf("%s", &nameOfFile);

			if(!strcmp(nameOfFile, "ABORT")) {
				return 0;
			} else {
				input = fopen(nameOfFile, "r");

                        	if(input == NULL) {
                                	printf("Unable to find a file with such a name :( ...\n");
                        	} else {
                                	break;
                        	}
			}
		}

		fscanf(input, "%i", &n);
		printf("%i\n", n);

		for(int i = 0; i < n; i++) {
			if(i == 0) {
                        	newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  &newNode->content);

                                *h = newNode;
                                *t  = newNode;
                        } else {
                                newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  &newNode->content);

                                newNode->next = *t;
                                *t = newNode;
                        }
		}

		fclose(input);

		return n;
	}
};

int printQueue(Node *h, Node *t, int n) {
	if(n == 0) {
		printf("Queue is empty!\n");
		return -1;
	}

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
	if(n == 0) {
                printf("Queue is empty!\n");
                return -1;
        }

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
