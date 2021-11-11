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

int dodajPocetak(Position);
int ispisListe(Position);
int dodajKraj(Position);
int findPerson(Position);
int delete(Position);
int dodajNakon(Position, Position);
Position justfind(Position, char*);
Position findbefore(Position, Position);
int dodajPrije(Position, Position);
int Sort(Position);
int uDatoteku(Position);
int izDatoteke(Position);

int main(int argc, char** argv) {
	student head = { .next = NULL, .ime = {0}, .prezime = {0}, .god = 0 };

	Position p = &head;

	char izbor;

	Position studentNakon = NULL;
	studentNakon = (Position)malloc(sizeof(student));
	char temp_nakon[64];

	Position studentPrije = NULL;
	studentPrije = (Position)malloc(sizeof(student));
	char temp_prije[64];

	student ucitano = { .next = NULL, .ime = {0}, .prezime = {0}, .god = 0 };

	//Kopiran izbornik :D
	while (1) {
		printf("\nIZBORNIK:\n");
		printf("P - unos na pocetak liste\nK - unos na kraj liste\nT - trazi po prezimenu\nD - ukloni po prezimenu\nI - ispis liste\nL - izlaz iz programa\nA - unos nakon odredenog prezimena\nB - unos prije odredenog prezimena\n E - unos u datoteku\n H - ispis iz datoteke\n");
		printf("Unesite naredbu:");
		scanf(" %c", &izbor);

		switch (toupper(izbor)) {
		case 'P': dodajPocetak(&head); break;
		case 'K': dodajKraj(&head); break;
		case 'T': findPerson(head.next); break;
		case 'D': delete(&head); break;
		case 'I': ispisListe(head.next); break;
		case 'L': return 1; break;
		case 'A': printf("Nakon kojeg prezimena zelite dodati novog studenta?\n");
			scanf("%s", temp_nakon);
			studentNakon = justfind(head.next, temp_nakon);
			dodajNakon(&head, studentNakon);
			break;

		case 'B': printf("Prije kojeg prezimena zelite dodati novog studenta?\n");
			scanf("%s", temp_prije);
			studentPrije = justfind(head.next, temp_prije);
			dodajPrije(&head, studentPrije);
			break;

		case 'S': Sort(&head); break;
		case 'E': uDatoteku(head.next); break;
		case 'H': izDatoteke(&ucitano); break;

		default: printf("Wrong command!\n"); break;

		}

	}

	return EXIT_SUCCESS;

}

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

	return 0;

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
int dodajNakon(Position head, Position nakon) {

	if (nakon == NULL) {
		return -1;
	}

	Position newStudent = (Position)malloc(sizeof(student));

	printf("Unesite ime studenta: ");
	scanf("%s", newStudent->ime);
	printf("Unesite prezime studenta: ");
	scanf("%s", newStudent->prezime);
	printf("Unesite godinu rodenja studenta: ");
	scanf("%d", &newStudent->god);

	newStudent->next = nakon->next;
	nakon->next = newStudent;

	return 0;
}
Position justfind(Position head, char* prezime) {

	Position temp = head->next;

	while (temp != NULL && strcmp(temp->prezime, prezime))
		temp = temp->next;

	if (temp == NULL) {
		printf("Prezime not found!");
		return NULL;

	}

	return temp;

}
Position findbefore(Position head, Position before)
{
	Position temp;
	temp = head;

	while (temp != NULL && temp->next != before)
		temp = temp->next;

	return temp;
}
int dodajPrije(Position head, Position prije) {

	if (prije == NULL) {
		return -1;
	}

	Position newStudent = (Position)malloc(sizeof(student));
	Position prethodni = (Position)malloc(sizeof(student));

	prethodni = findbefore(head, prije);

	prethodni->next = newStudent;
	newStudent->next = prije;

	printf("Unesite ime studenta: ");
	scanf("%s", newStudent->ime);
	printf("Unesite prezime studenta: ");
	scanf("%s", newStudent->prezime);
	printf("Unesite godinu rodenja studenta: ");
	scanf("%d", &newStudent->god);

	return 0;
}
int Sort(Position head)
{
	Position p = head;
	Position q = NULL;
	Position pret_q = NULL;
	Position zadnji = NULL;

	while (p->next != zadnji)
	{
		pret_q = p;
		q = pret_q->next;

		while (q->next != zadnji)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
			{
				pret_q->next = q->next;
				q->next = q->next->next;
				pret_q->next->next = q;
				q = pret_q->next;
			}
			pret_q = q;
			q = q->next;
		}
		zadnji = q;
	}

	return 0;
}
int uDatoteku(Position p)
{
	FILE* fp = NULL;

	fp = fopen("osobe.txt", "w");

	if (fp == NULL) {
		puts("GRESKA!!! Datoteka nije otvorena!");
		return -1;
	}

	while (p != NULL) {
		if (p->next == NULL) {
			fprintf(fp, "%s\t%s\t%d", p->ime, p->prezime, p->god);
			break;
		}
		fprintf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, p->god);

		p = p->next;
	}

	puts("Upis u datoteku je zavrsen\n");
	fclose(fp);
	return 0;
}
int izDatoteke(Position p)
{
	Position novi, temp;
	FILE* fp = NULL;

	fp = fopen("osobe.txt", "r");

	if (fp == NULL) {
		puts("GRESKA!!! Datoteka nije otvorena!");
		return -1;
	}

	temp = p;

	while (!feof(fp)) {

		novi = (Position)malloc(sizeof(student));
		if (novi == NULL) {
			perror("Memorija nije alocirana!!");
			return -1;
		}

		fscanf(fp, "%s %s %d", novi->ime, novi->prezime, &novi->god);

		novi->next = temp->next;    //unos na kraj liste
		temp->next = novi;
		temp = novi;
	}

	puts("Unos iz datoteke je zavrsen\n");
	fclose(fp);
	return 0;
}


