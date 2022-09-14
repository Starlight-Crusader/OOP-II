#include <stdio.h>int *n; *n = 0;
                char input[256];
                Node *head, *tail, *newNode;

typedef struct {
	int content;
	Node *next;
} Node;

int input(Node *h, Node *t, int *n) {
	int option = 0;
	int newNode = 0;
	char input[256];

	printf("1. Manual input;\n");
        printf("2. Input from a file\n");
        printf("? - ");

        scanf("%i", &option);

        if(option == 1) {
                while(1) {
                        printf("Type a number to be enqueued (OR 'S' to stop): ");
                        scanf("%s", &input);

                        if(strcmp(input, "S")) {
                                break;
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

	}
}

int main() {
	int *n; *n = 0;
        Node *head, *tail;

	input(head, tail, n);

	return 0;
}
