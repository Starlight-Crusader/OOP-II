#include <stdio.h>
#include <stdlib.h>

typedef struct Node  {
	int content;
	struct Node *next;
} Node;

int input(Node *h, Node *t, int *n) {
	int option = 0;
	Node *newNode;

	printf("1. Manual input;\n");
        printf("2. Input from a file\n");
        printf("? - ");

        scanf("%i", &option);

        if(option == 1) {
		char input[256];

                while(1) {
                        printf("Type a number to be enqueued (OR 'S' to stop): ");
                        scanf("%s", &input);

                        if(strcmp(input, "S")) {
				if(*n == 0) {
					printf("Input at leat 1 number...\n");
					continue;
				} else { break; }
                        } else {
                                if(*n == 0) {
                                        newNode = (Node*)malloc(sizeof(Node));
                                        newNode->content = input + 0;

                                        h = newNode;
                                        t  = newNode;

					*n++;
                                } else {
                                        newNode = (Node*)malloc(sizeof(Node));
                                        newNode->content = input + 0;

                                        newNode->next = t;
                                        t = newNode;

					*n++;
                                }
                        }
                }
        } else {
		FILE *input;
		char nameOfFile[256];

		input = fopen(nameOfFile, "r");

		fscanf(input, "%i", *n);

		for(int i = 0; i < *n; i++) {
			if(i == 0) {
                        	newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  newNode->content);

                                h = newNode;
                                t  = newNode;
                        } else {
                                newNode = (Node*)malloc(sizeof(Node));
                                fscanf(input, "%i",  newNode->content);

                                newNode->next = t;
                                t = newNode;
                        }
		}

		fclose(nameOfFile);
	}

	return 0;
};

int printQueue(Node *h, Node *t, int *n) {
	printf("TAIL -> ");

	Node *currentNode; currentNode = t;

	for(int i = 1; i < *n; i++) {
		printf("%i - ", currentNode->content);
		currentNode = currentNode->next;
	}

	printf("%i <-", currentNode->content);
	printf("HEAD\n");

	return 0;
};

int deallocateMemory(Node *h, Node *t, int *n) {
	Node *nodeToDeallocate;
	nodeToDeallocate = t;

	for(int i = 1; i < *n; i++) {
		nodeToDeallocate = t;
		t = t->next;

		free(nodeToDeallocate);
	}

	free(h);

	return 0;
};

int main() {
	int *n; *n = 0;
        Node *head, *tail;

	input(head, tail, n);
	printQueue(head, tail, n);
	deallocateMemory(head, tail, n);

	return 0;
}
