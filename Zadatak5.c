#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StogElement;
typedef struct StogElement* Position;
typedef struct StogElement {
	double number;
	Position next;
}Stack;

Position CreateElement(double number);
int InsertAfter(Position position, Position newelement);
int push(Position head, double number);
int deleteAfter(Position position);
int pop(double* destinationOfResult, Position head);
int performOperation(Position head, char operation);
int calculatePostfixFromFile(double* destinationOfResult, char* fileName);
int deleteAll(Position head);

int main() {

	char fileName[64] = { 0 };
	double result = 0;
	printf("Unesite naziv datoteke gdje se nalazi postfix: ");
	scanf("%s", fileName);

	calculatePostfixFromFile(&result, fileName);
	printf("Rezultat je %lf", result);
	

	return EXIT_SUCCESS;
}

Position CreateElement(double number) {

	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Stack));
	if (newElement == NULL) {
		perror("Memory not allocated!\n");
		return -1;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}
int InsertAfter(Position position, Position newelement) {

	newelement->next = position->next;
	position->next = newelement;

	return EXIT_SUCCESS;

}
int push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);
	if (!newElement)
	{
		return -1;
	}

	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}
int deleteAfter(Position position) {

	Position temp = position->next;
	if (!temp) {
		return EXIT_SUCCESS;
	}

	position->next = temp->next;
	free(temp);
	return EXIT_SUCCESS;

}
int pop(double* destinationOfResult, Position head) {

	Position first = head->next;
	if (!first) {
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}
	*destinationOfResult = first->number;

	deleteAfter(head);

	return EXIT_SUCCESS;
}
int performOperation(Position head, char operation) {

	double result = 0;
	double operand1 = 0;
	double operand2 = 0;
	int status1 = 0;
	int status2 = 0;

	status2 = pop(&operand2, head);
	if (status2 != EXIT_SUCCESS) {
		return -1;
	}

	status1 = pop(&operand1, head);
	if (status1 != EXIT_SUCCESS) {
		return -2;
	}

	switch (operation) {

	case '+':
		result = operand1 + operand2; break;
	case '-':
		result = operand1 - operand2; break;
	case '*':
		result = operand1 * operand2; break;
	case '/':
		if (operand2 == 0) {
			printf("Cannot divide with 0! Check your postfix!\n");
			return -1;
		}
		result = operand1 / operand2; break;
	default: printf("Operation not supported!\n"); return -1;

	}

	return push(head,result);
}
int calculatePostfixFromFile(double* destinationOfResult, char* fileName) {

	FILE* file = NULL;
	file = fopen(fileName, "rb"); //otvori file za read i u binary modu!
	if (!file) {
		perror("Cannot open file!\n");
		return -1;
	}

	int fileLenght = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	char operation;
	double number = 0;
	int numBytes = 0;
	int status = 0;
	Stack head = { .next = NULL,.number = 0 };

	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);

	buffer = (char*)calloc(fileLenght + 1, sizeof(char)); //+1 jer zavrsava sa null terminating character
	if (!buffer) {
		perror("Memory not allocated!\n");
		return -1;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLenght, file);
	printf("|%s|\n", buffer);
	fclose(file);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0) {
	
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1) {
			status = push(&head, number);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				deleteAll(&head);
				return -1;
			}
			currentBuffer += numBytes;
		}
		else{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = performOperation(&head, operation);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				deleteAll(&head);
				return -1;
			}
			currentBuffer += numBytes;
		}
	
	}


	free(buffer);

	status = pop(destinationOfResult, &head);
	if (status != EXIT_SUCCESS) {
		deleteAll(&head);
		return -1;
	}

	
	if (head.next) {
		printf("Postfix not valid!\n");
		deleteAll(&head);
		return -1;
	}

	return EXIT_SUCCESS;
}
int deleteAll(Position head) {

	while (head->next != NULL) {
		deleteAfter(head);
	}
	return EXIT_SUCCESS;
}
