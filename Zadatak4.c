#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Polinom;
typedef struct Polinom polinom;
typedef struct Polinom* ppol;

struct Polinom {
	int koef;
	int eksp;
	ppol next;
};

int unosFILE(ppol, ppol);
ppol noviPol(int, int);
int sortUnos(ppol, int, int);
int brisi(ppol);
int brisiSve(ppol);
int zbrajanje(ppol, ppol, ppol);
int mnozenje(ppol, ppol, ppol);
int ispis(ppol);

int main() {

    polinom prvipolinom, drugipolinom, suma, produkt;
    prvipolinom.next = NULL;
    drugipolinom.next = NULL;
    suma.next = NULL;
    produkt.next = NULL;

    unosFILE(&prvipolinom, &drugipolinom);
    puts("Prvi polinom: ");
    ispis(&prvipolinom);
    puts("\nDrugi polinom: ");
    ispis(&drugipolinom);
    puts("\nZbroj: ");
    zbrajanje(prvipolinom.next, drugipolinom.next, &suma);
    ispis(&suma);
    puts("\nProdukt: ");
    mnozenje(prvipolinom.next, drugipolinom.next, &produkt);
    ispis(&produkt);

    brisiSve(&prvipolinom);
    brisiSve(&drugipolinom);
    brisiSve(&suma);
    brisiSve(&produkt);

    return EXIT_SUCCESS;
}

int unosFILE(ppol prvi, ppol drugi) {

	FILE* fp;
	char datoteka[64];
	int tempkoef, tempeksp;
	char poli1[1024];
	char poli2[1024];
	char* ptr1 = NULL;
    char* ptr2 = NULL;
	int check = 0;

	printf("Unesite naziv datoteke odakle zelite uniti polinome (ime_datoteke.txt) : \n");
	scanf("%s", datoteka);

	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		perror("Datoteka se nije otvorila!\n");
		return -1;
	}

	rewind(fp);
	fgets(poli1, 1024, fp);
	fgets(poli2, 1024, fp);

	ptr1 = poli1;
    while (strlen(ptr1) > 0) {
		
		sscanf(ptr1, " %d %d %n", &tempkoef, &tempeksp, &check);
		//printf("%d %d pomak %d", tempkoef, tempeksp, check);
        sortUnos(prvi, tempkoef, tempeksp);
		ptr1 += check;
	}

    check = 0;
    ptr2 = poli2;
    while (strlen(ptr2) > 0) {

        sscanf(ptr2, " %d %d %n", &tempkoef, &tempeksp, &check);
        //printf("%d %d pomak %d", tempkoef, tempeksp, check);
        sortUnos(drugi, tempkoef, tempeksp);
        ptr2 += check;
        tempeksp = 0;
    }
    return 0;
}
ppol noviPol(int koef, int eksp){

    ppol novi = (ppol)malloc(sizeof(polinom));
    if(novi==NULL){
        perror("Memorija nije alocirana!\n");
        return -1;
    }

    novi->koef = koef;
    novi->eksp = eksp;
    novi->next = NULL;

    return novi;
}
int sortUnos(ppol head, int koef, int exp)
{
    ppol novi = NULL;
    ppol h = head;
    ppol prev = head;

    novi = noviPol(koef, exp);

    if (h->next == NULL)
    {
        novi->next = h->next;
        h->next = novi;
    }

    else
    {
        h = h->next;

        while (h->next != NULL && h->eksp > exp)
        {
            prev = h;
            h = h->next;
        }

        if (h->eksp < novi->eksp)
        {
            novi->next = h;
            prev->next = novi;
        }

        else if (h->eksp == novi->eksp)
        {
            h->koef = h->koef + novi->koef;
            if (h->koef == 0)
            {
                brisi(prev);
            }
        }

        else
        {
            novi->next = h->next;
            h->next = novi;
        }
    }

    return 0;
}
int brisi(ppol p) {

    ppol temp = NULL;

    temp = p->next;

    p->next = temp->next;
    free(temp);

    return 0;
}
int brisiSve(ppol head){
    
    ppol temp = NULL;
    
    while (head->next != NULL) {

        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 0;
}
int zbrajanje(ppol prvi, ppol drugi, ppol suma) {

    ppol temp = NULL;

    while (prvi != NULL && drugi != NULL)
    {
        if (prvi->eksp == drugi->eksp)
        {
            sortUnos(suma, prvi->koef + drugi->koef, prvi->eksp);
            prvi = prvi->next;
            drugi = drugi->next;
        }
        else if (prvi->eksp > drugi->eksp)
        {
            sortUnos(suma, prvi->koef, prvi->eksp);
            prvi = prvi->next;
        }
        else
        {
            sortUnos(suma, drugi->koef, drugi->eksp);
            drugi = drugi->next;
        }
    }
    if (prvi != NULL)
    {
        temp = prvi;
    }
    else
    {
        temp = drugi;
    }
    while (temp != NULL)
    {
        sortUnos(suma, temp->koef, temp->eksp);
        temp = temp->next;
    }
    return 0;

}
int mnozenje(ppol prvi, ppol drugi, ppol produkt) {

    ppol temp = drugi;

    while (prvi != NULL)
    {
        drugi = temp;
        while (drugi != NULL)
        {
            sortUnos(produkt, prvi->koef * drugi->koef, prvi->eksp + drugi->eksp);
            drugi = drugi->next;
        }
        prvi = prvi->next;
    }
    return 0;

}
int ispis(ppol head) {

    ppol temp = head;

    temp = temp->next;

    while (temp != NULL) {
        printf("%dx^%d\t", temp->koef, temp->eksp);
        temp = temp->next;

    }
    return 0;
}


