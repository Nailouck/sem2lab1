#ifndef MENU_H
#define MENU_H

#include <stdio.h>
void type_choice(unsigned int &choice) {
	printf(" акой тип данных должна иметь матрица?\n 0 - int\n 1 - complex\n");
	do { scanf("%d", &choice); } while (choice != 1 && choice != 0);
	return;
}

#endif