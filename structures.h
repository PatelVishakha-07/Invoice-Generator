
#ifndef STRUCTURES_H
#define STRUCTURES_H


#define MAX_ITEMS_PER_INVOICE 20  //an invoice can have upto 20 products
#define MAX_PRODUCTS 200  //Maximum number of products can be store is 200
#define MAX_INVOICES 200  //Maximum number of invoices can be store is 200

#define PRODUCT_FILE "products.dat"  //stores products information
#define INVOICE_FILE "invoices.dat"  //stores invoices

typedef struct
{
    int code, price, stock;
    char prdName[50];
}Product;

typedef struct
{
   int prdCode,qty, total_amount;
   char prdName[50];
}InvoiceItem;

typedef struct
{
    int billNo, itemCount, bill_amount;
    char custName[50], billDate[20];
    InvoiceItem items[MAX_ITEMS_PER_INVOICE];  //Array of InvoiceItem, max 20 items in a single invoice
}Invoice;

void clearScreen();

//extern is used to declare global variables
extern Product products[MAX_PRODUCTS];
extern int productCount;

extern Invoice invoices[MAX_INVOICES];
extern int invoiceCount;

#endif
