#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h> //nema bool u C-u


//dsenta00 na Gitu
//spoji Git sa VS2019
//koristi headere tj. .h

struct Article;
typedef struct Article* PositionArt;

typedef struct Article {

	char name;
	int count;
	float price;
	PositionArt next;

}article;

