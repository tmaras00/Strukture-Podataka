#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define Max_Bodovi 9
#define Max_Size 1024


struct Student;
typedef struct Student std;
struct Student{
	char ime[32];
	char prezime[64];
	int bodovi;
};
int main()
{	
	int br_std=0;
	char buffer[Max_Size] = {0};
	FILE* fp = fopen("popis.txt", "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return -1;
	}
	//Brojac studenata
	while (fgets(buffer, Max_Size, fp) != NULL) {
		br_std++;
	}

	//BITNO!	
	rewind(fp);

	std* niz = (std*)malloc(sizeof(std) * br_std);
	if (niz == NULL) {
		printf("Memorija nije alocirana!\n");
		return -2;
	}
	int i = 0;
	//Redak mora izgledat ovako: Ime Prezime BrBodova
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", niz[i].ime, niz[i].prezime, &niz[i].bodovi);
		i++;
	}

	for (int i = 0; i < br_std; i++) {
		printf("%s %s %d %.2f\n", niz[i].ime, niz[i].prezime, niz[i].bodovi, (float)niz[i].bodovi / Max_Bodovi * 100);
	}

	fclose(fp);
	return 0;
}
