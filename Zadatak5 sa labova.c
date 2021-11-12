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

int main() {}

//Dovrsi, mozda je dovresno?
Position CreateElement(double number) {

	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Stack));
	if (newElement == NULL) {
		perror("Memory not allocated!\n");
		return -1;
	}

	newElement->number = number;

	return newElement;
}
//Dovrsi
int InsertAfter(Position position, Position newelement) {

	newelement->next = position->next;



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
	default: printf("Operation not supported!\n"); break;
	
	}

	return EXIT_SUCCESS;
}
//Dovrsi
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
	Position head=NULL;

	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);

	buffer = (char*)calloc(fileLenght + 1, sizeof(char)); //+1 jer zavrsava sa null terminating character
	if (!buffer) {
		perror("Memory not allocated!\n");
			return -1;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLenght, file);
	printf("|%s|\n",buffer);
	fclose(file);

	while (srtlen(currentBuffer) > 0) {
	
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1) {
			
			
		}
		else {
		
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = performOperation(&head, operation);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				deleteAll(&head);
				return -4;
			}
		}
	}
	free(buffer);

	return EXIT_SUCCESS;
}

int deleteAll(Position head) {

	while (head->next != NULL) {
		deleteAfter(head);
	}
	return EXIT_SUCCESS;
}
