#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student;
typedef struct Student student;
typedef struct Student* Position;

struct Student {
	char ime[32];
	char prezime[64];
	int god;
	Position next;
};

int dodajPocetak(Position head) {
	Position newStudent = NULL;
	newStudent = (Position)malloc(sizeof(student));

	if (newStudent == NULL) {
		perror("Greska! Memorija nije alocirana\n"); //puts ili perror ili printf
		return -1;
	}

	printf("Unesite ime studenta: ");
	scanf("%s", newStudent->ime);
	printf("Unesite prezime studenta: ");
	scanf("%s", newStudent->prezime);
	printf("Unesite godinu rodenja studenta: ");
	scanf("%d", &newStudent->god);
	newStudent->next = NULL;

	newStudent->next = head->next;
	head->next = newStudent;
	return 0;
}
int ispisListe(Position first) {

	Position temp = first;

	//for(Position temp=first; temp!=NULL; temp=temp->next){}
	while (temp) {
		printf("Name: %s, Surname: %s, DoB: %d\n", temp->ime, temp->prezime, temp->god);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}
int dodajKraj(Position head) {
	Position newStudent = NULL;
	newStudent = (Position)malloc(sizeof(student));

	if (newStudent == NULL) {
		perror("Greska! Memorija nije alocirana\n"); //puts ili perror ili printf
		return -1;
	}

	printf("Unesite ime studenta: ");
	scanf("%s", newStudent->ime);
	printf("Unesite prezime studenta: ");
	scanf("%s", newStudent->prezime);
	printf("Unesite godinu rodenja studenta: ");
	scanf("%d", &newStudent->god);
	newStudent->next = NULL;

	while (head->next) {
		head = head->next;
	}

	newStudent->next = head->next;
	head->next = newStudent;

}
int findPerson(Position first)
{
	char prezime[64];

	printf("Upisi prezime koje trazite: ");
	scanf("%s", prezime);

	while (first->next != NULL && strcmp(prezime, first->prezime) != 0)
	{
		first = first->next;
	}

	if (strcmp(prezime, first->prezime) == 0) {

		printf("User found.\n");
		printf("Name: %s, Surname: %s, DoB: %d\n", first->ime, first->prezime, first->god);

	}
	else if (strcmp(prezime, first->prezime) != 0)
		printf("Can't find user!\n");

	return 0;
}
int delete(Position head) {

	char prezime[20];
	Position temp = (Position)malloc(sizeof(student));

	if (temp == NULL) {
		perror("GREŠKA! Memorija nije alocirana");
		return -1;
	}

	printf("Upisite prezime koje zelite izbrisati:");
	scanf("%s", prezime);

	while (head->next != NULL && strcmp(prezime, head->prezime) != 0)
	{
		temp = head;
		head = head->next;
	}

	if (strcmp(prezime, head->prezime) == 0) {
		temp->next = head->next;
		free(head);
	}

	else if (strcmp(prezime, head->prezime) != 0)
		printf("Trazeno prezime ne postoji u listi");

	return 0;
	

}
int main(int argc, char** argv) {
	student head = { .next = NULL, .ime = {0}, .prezime = {0}, .god = 0 };
	
	Position p = &head;

	char izbor;

	//Kopiran izbornik :D
	while (1) {
		printf("\nIZBORNIK:\n");
		printf("P - unos na pocetak liste\nK - unos na kraj liste\nT - trazi po prezimenu\nD - ukloni po prezimenu\nI - ispis liste\nL - izlaz iz programa\n");
		printf("Unesite naredbu:");
		scanf(" %c", &izbor);

		switch (toupper(izbor)) {
		case 'P': dodajPocetak(&head); break;
		case 'K': dodajKraj(&head); break;
		case 'T': findPerson(head.next); break;
		case 'D': delete(&head); break;
		case 'I': ispisListe(head.next); break;
		case 'L': return 1; break;
		default: printf("Wrong command!\n"); break;

		}

	}

	return EXIT_SUCCESS;

}
