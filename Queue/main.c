#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node  {
	int content;
	struct Node *next;
} Node;

typedef struct Queue {
	bool pQ;
	bool cQ;
	Node *head, *tail;
	int len;
} Queue;

int input();
int printQueue();
int deallocateMemory();
int saveToFile();
int enq();
int deq();
int search();
int sort();
int reverse();
int serveElementWithHPriority();
int fixCircQ();

int main() {
	int option;
	int val;
	int c;
	int prevVal;
	Queue q;
	q.head = NULL; q.tail = NULL; q.len = 0;
	q.pQ = false; q.cQ = false;


	while(1) {
		printf("===================\n");
		printf("Pick a procedure from the list below:\n");

		printf("'1' - Create a new queue and enter some values;\n");
		printf("'2' - Print all the values from the queue;\n");
		printf("'3' - Clear the queue;\n");
		printf("'4' - Save the queue to a file;\n");
		printf("'5' - Add a value to an existing queue;\n");
		printf("'6' - Dequeue element;\n");
		printf("'7' - Search;\n");
		printf("'8' - Sort;\n");
		printf("'9' - Reverse the queue;\n");
		printf("'10' - Make the queue to be a priority queue;\n");
		printf("'11' - Make the queue to be a circular queue;\n");
		printf("'12' - Remove specification flags;\n");
		printf("'-1' - Clear the terminal;\n");
		printf("'0' - Quit without saving (the memory will be automatically deallocated)\n");

		printf("OPTION: ");
		scanf("%i", &option);

		switch(option) {
			case -1: system("clear"); break;
			case 1: q.len = input(&q.head, &q.tail, q.len); break;
			case 2: printQueue(q.head, q.tail, q.len); break;
			case 3:
				deallocateMemory(q.head, q.tail, q.len);
				q.head = NULL; q.tail = NULL;
				q.len = 0; q.pQ = false;
				break;
			case 4: saveToFile(q.head, q.tail, q.len);
			case 5: q.len = enq(&q.tail, q.len);
				if(q.pQ) { sort(q.tail, q.len, 2); }
				if(q.cQ) { fixCircQ(q.head, q.tail, q.len); }
				break;
			case 6: if(q.len == 1) {
					deallocateMemory(q.head, q.tail, q.len);
	                                q.head = NULL; q.tail = NULL;
					q.len = 0; q.pQ = false;

					printf("SUCCESS: The queue consisted of only one element, so it was completely destroyed!\n");
				} else if (!q.pQ){
					val = q.head->content;
					q.len = deq(q.tail, &q.head, q.len); q.head->next = NULL;

					printf("SUCCESS: Heading element with value: %i - was successfully dequeued!\n", val);
				} else {
					val = q.head->content;
					c = 0; prevVal = val;

					while(q.head->content == prevVal) {
						prevVal = q.head->content;

						c++;
						q.len = deq(q.tail, &q.head, q.len); q.head->next = NULL;
					}

					printf("SUCCESS: %i element/-s with highest priority - %i was/were served ...\n", c, val);
				}

				if(q.cQ) { fixCircQ(q.head, q.tail, q.len); }
				break;
			case 7: search(q.head, q.tail, q.len); break;
			case 8:
				if(q.pQ) {
					printf("ABORT: This operation may not be performed on a priority queue!\n");
					break;
				}

				printf("'1' - ASC;\n");
        			printf("'2' - DESC;\n");
        			printf("'0' - Abort this operation\n");

        			printf("OPTION: ");
        			scanf("%i", &option);

				if(option == 0) {
					break;
				} else if((option == 1) || (option == 2)) {
					sort(q.tail, q.len, option); break;
				} else { break; }
			case 9:
				if(q.pQ) {
                                        printf("ABORT: This operation may not be performed on a priority queue!\n");
                                        break;
                                }

				reverse(q.tail, q.len); break;
			case 10:
				q.pQ = true;
				if(q.pQ) { sort(q.tail, q.len, 2); }
				break;
			case 11:
				q.cQ = true;
				fixCircQ(q.head, q.tail, q.len);
				break;
			case 12:
				if(q.len == 0) {
					printf("ABORT: Queue is empty and don't have any specification flags!");
					break;
				}

				printf("Specification flags:\n");
				printf("Priority queue - %b,\n", q.pQ);
				printf("Circular queue - %b\n", q.cQ);

				printf("--------------------\n");

				if(q.pQ) { printf("'1' - Remove the priority queue flag;\n"); }
				if(q.cQ) { printf("'2' - Remove the circular queue flag;\n"); }
				printf("'0' - Abort this operation\n");

				printf("OPTION: ");
			        scanf("%i", &option);

				switch(option) {
					case 1:
						if(!q.pQ) {
							printf("ABORT: Unable to perform this operation on this queue :(\n");
						} else {
							q.pQ = false;
						}
						break;
					case 2:
						if(!q.cQ) {
                                                        printf("ABORT: Unable to perform this operation on this queue :(\n");
                                                } else {
                                                        q.cQ = false;
							q.head->next = NULL;
                                                }
                                                break;
					case 0: break;
					default: printf("ERROR: This option is probably not in the list ...\n"); break;
				}
				break;
			case 0: deallocateMemory(q.head, q.tail, q.len);
                                q.head = NULL; q.tail = NULL;
				q.len = 0; q.pQ = false;
                                return 0;
			default: printf("ERROR: This option is probably not in the list ...\n"); break;
		}
	}
};

int input(Node **h, Node **t, int l) {
	if(l > 0) {
		printf("ABORT: You've already created a queue, dellocatre memory in order to create a new one ...\n");
		return l;
	}

	int option = 0; int n = 0;
	Node *newNode;

	printf("'1' - Manual input;\n");
        printf("'2' - Input from a file\n");
        printf("? - ");

	printf("OPTION: ");
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
		printf("%i elements will be read ...\n", n);

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
		printf("ABORT: Queue is empty - unable to print!\n");
		return 0;
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
                printf("ABORT: Queue is empty - unable to deallocate memory!\n");
                return 0;
        }

	Node *nodeToDeallocate;

	for(int i = 0; i < n; i++) {
		nodeToDeallocate = t;
		t = t->next;

		free(nodeToDeallocate);
	}

	return 0;
};


int saveToFile(Node *h, Node *t, int n) {
	if(n == 0) {
		printf("ABORT: Queue is empty - unable to save it in a file!\n");
		return 0;
	}

	int values[n], i;
	char nameOfFile[256];
	Node *currentNode;

	FILE *output;

       	printf("Enter the name of file (OR 'ABORT' to abort input procedure): ");
        scanf("%s", &nameOfFile);

        if(!strcmp(nameOfFile, "ABORT")) {
        	return 0;
        } else {
                output = fopen(nameOfFile, "w");
	}

	fprintf(output, "%i\n", n);

	for(i = 0; i < n; i++) {
		currentNode = t;
		t = t->next;

		values[i] = currentNode->content;
	}

	for(i = n-1; i > 0; i--) {
		fprintf(output, "%i ", values[i]);
	}

	fprintf(output, "%i", values[i]);

	printf("The queue is saved in the 'queue_out.txt' ...\n");

	fclose(output);

	return 0;
};

int enq(Node **t, int n) {
	if(n == 0) {
		printf("ABORT: First of all you have to create a new queue!\n");
		return 0;
	}

	char input[256];

	Node *newNode = (Node*)malloc(sizeof(Node));

	printf("Print a value to add in the queue (OR 'A' to abort this operation): ");
	scanf("%s", &input);

	if(!strcmp(input, "A")) {
		return n;
	}

	newNode->content = atoi(input);
	newNode->next = *t;
	*t = newNode;

	return n+1;
};

int deq(Node *t, Node **h, int n) {
	if(n == 0) {
                printf("ABORT: Queue is empty!\n");
                return 0;
        }

	Node *currentNode;
	currentNode = t;

	while(1) {
		if(currentNode->next == *h) {
			*h = currentNode;
			currentNode = currentNode->next;

			free(currentNode);

			return n-1;
		} else {
			currentNode = currentNode->next;
		}
	}
};

int search(Node *h, Node *t, int n) {
	if(n == 0) {
                printf("ABORT: Queue is empty!\n");
                return 0;
        }

	Node *currentNode;
	currentNode = t;

	int index = 0;
	int indexes[n]; int indLen = 0;
	int val = 0;

	int opt;

	printf("'1' - Find a value by index;\n");
	printf("'2' - Find indexes by value;\n");
	printf("'0' - Abort this operation\n");

	printf("OPTION: ");
	scanf("%i", &opt);

	switch(opt) {
		case 1:
			printf("Enter the index (from 0 to n-1, from HEAD to TAIL): ");
			scanf("%i", &index);

			index = n-1 - index;

			for(int i = 0; i < n; i++) {
				if(index == i) {
					printf("Value sub this index is: %i ...\n", currentNode->content);
					return 0;
				}

				currentNode = currentNode->next;
			}

			printf("Unable to find a value sub this index :( - aborting this operation...\n");
			return 0;
		case 2:
			printf("Enter a value we are searching for: ");
			scanf("%i", &val);

			for(int i = 0; i < n; i++) {
				if(currentNode->content == val) {
					indexes[indLen] = i;
					indLen++;
				}

				currentNode = currentNode->next;
			}

			if(indLen == 0) {
				printf("We were unable to find a single element with this value :(\n");
				return 0;
			} else {
				printf("We've found %i elements with this value on these positions (from 0 to n-1, from HEAD to TAIL):\n", indLen);

				for(int i = 0; i < indLen; i++) {
					printf("%i ", n-1 - indexes[i]);
				}

				printf("\n");
				return 0;
			}
		case 0:
			return 0;
		default:
			printf("This option is probably not in the list ...\n"); return 0;
	}
};

int sort(Node *t, int n, int opt) {
	if(n == 0) {
                printf("ABORT: Queue is empty!\n");
                return 0;
        }

	int res;
	Node *currentNode;

	switch(opt) {
		case 1:
			for(int i = 0; i < n-1; i++) {
				currentNode = t;

				for(int j = 0; j < n-i-1; j++) {
					if(currentNode->content < currentNode->next->content) {
						res = currentNode->content + 0;
						currentNode->content = currentNode->next->content + 0;
						currentNode->next->content = res + 0;
					}

					currentNode = currentNode->next;
				}
			}

			return 0;
		case 2:
			for(int i = 0; i < n-1; i++) {
				currentNode = t;

                                for(int j = 0; j < n-i-1; j++) {
                                        if(currentNode->content > currentNode->next->content) {
                                                res = currentNode->content + 0;
                                                currentNode->content = currentNode->next->content + 0;
                                                currentNode->next->content = res + 0;
                                        }

					currentNode = currentNode->next;
                                }
                        }

                        return 0;
		case 3: return 0;
		default:
			printf("This option is probably not in the list ...\n"); return 0;
	}
};

int reverse(Node *t, int n) {
	if(n == 0) {
		printf("ABORT: Queue is empty!\n"); return 0;
	} else if(n == 1) {
		printf("ABORT: Queue contains only one element - the operation won't change anything!\n");
		return 0;
	}

	Node *rearNode, *frontNode;
	int res;
	int frontI, rearI;
	frontI = n - 1; rearI = 0;

	while(rearI < frontI) {
		rearNode = t; frontNode = t;

		for(int i = 0; i < rearI; i++) {
			rearNode = rearNode->next;
		}

		for(int i = 0; i < frontI; i++) {
			frontNode = frontNode->next;
		}

		res = rearNode->content;
		rearNode->content = frontNode->content;
		frontNode->content = res;

		rearI++; frontI--;
	}

	return 0;
};

int fixCircQ(Node *h, Node *t, int n) {
	if(n == 0) {
		printf("ABORT: Queue is empty!\n"); return 0;
	} else if(n == 1) {
		h->next = t;
		t->next = h;

		return 0;
	} else {
		h->next = t; return 0;
	}
};
