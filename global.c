#include<stdlib.h>
#include "structures.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

Invoice invoices[MAX_INVOICES];
int invoiceCount = 0;

void clearScreen()
{
    system("cls");
}
