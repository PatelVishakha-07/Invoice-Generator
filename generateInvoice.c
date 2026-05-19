#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "generateInvoice.h"

void GenerateInvoice() {
    clearScreen();
    Invoice inv;
    int i,total = 0,found;
    FILE *fp, *pf;
    Product p;
    char p_nm[50];

    fp = fopen(INVOICE_FILE, "rb");
    if(fp != NULL) {
        invoiceCount = 0;
        while(invoiceCount < MAX_INVOICES && fread(&invoices[invoiceCount], sizeof(Invoice), 1, fp) == 1){
            invoiceCount++;
        }
        fclose(fp);
    }


    time_t t;
    struct tm *dt;
    time(&t);
    dt = localtime(&t);
    sprintf(inv.billDate, "%02d/%02d/%04d", dt->tm_mday, dt->tm_mon + 1, dt->tm_year + 1900);

    printf("\n\t\t\t\t\t\t\t\t********** Generate Invoice **********\n");

    int unique;
    do {
        unique = 1;
        printf("\t\t\t\t\t\t\t\tEnter Bill No: ");
        scanf("%d", &inv.billNo);
        while(getchar() != '\n');

            for(i = 0; i < invoiceCount; i++) {
                if(invoices[i].billNo == inv.billNo) {
                printf("\t\t\t\t\t\tThis Bill No already exists! Enter a unique Bill No.\n");
                unique = 0;
                break;
            }
        }
    } while(!unique);

        printf("\n\t\t\t\t\t\t\t\tEnter Customer Name: ");
        gets(inv.custName);
        printf("\t\t\t\t\t\t\t\tSystem Date: %s\n", inv.billDate);

        printf("\t\t\t\t\t\t\t\tHow many items: ");
        scanf("%d", &inv.itemCount);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
            total = 0;
            for(i = 0; i < inv.itemCount; i++) {
                found = 0;
                do {
                    printf("\n\t\t\t\t\t\t\t\tEnter Product Name: ");
                    gets(p_nm);
                    pf = fopen(PRODUCT_FILE, "rb");
                    if(pf == NULL) {
                        printf("\n\t\t\t\t\t\t\t\tProduct file missing...\n");
                        return;
                    }

                while(fread(&p, sizeof(Product), 1, pf) == 1) {
                    if(strcmp(p.prdName,p_nm)==0) {
                        found = 1;
                        inv.items[i].prdCode = p.code;
                        strcpy(inv.items[i].prdName, p.prdName);

                        printf("\t\t\t\t\t\t\t\tname: %s | price: %d\n", p.prdName, p.price);

                        printf("\n\t\t\t\t\t\t\t\tEnter Quantity: ");
                        scanf("%d", &inv.items[i].qty);

                        while ((ch = getchar()) != '\n' && ch != EOF);

                    inv.items[i].total_amount = p.price * inv.items[i].qty;
                        total += inv.items[i].total_amount;
                        break;
                    }
                }

                fclose(pf);

                if(!found) {
                    printf("\n\t\t\t\t\t\t\t\tProduct is out of stock! .\n");
                }
            } while(!found);
        }

        inv.bill_amount = total;
        invoices[invoiceCount++] = inv;

        fp = fopen(INVOICE_FILE, "ab");
        if(fp == NULL) {
            printf("\n\t\t\t\t\t\t\t\tFile Does Not Exist\n");
            return;
        }

        fwrite(&inv, sizeof(Invoice), 1, fp);
        fclose(fp);

        printf("\n\t\t\t\t\t\t\t\t====== INVOICE DETAILS ======\n");
        printf("\t\t\t\t\t\t\t\tBill No: %d\n\t\t\t\t\t\t\t\tCustomer: %s\n\t\t\t\t\t\t\t\tDate: %s\n", inv.billNo, inv.custName, inv.billDate);
        printf("\n\t\t\t\t\t\t\t\tCode\tName\tQty\tAmount");
        for(i = 0; i < inv.itemCount; i++) {
            printf("\n\t\t\t\t\t\t\t\t%d\t%s\t%d\t%d", inv.items[i].prdCode, inv.items[i].prdName, inv.items[i].qty, inv.items[i].total_amount);
        }
        printf("\n\t\t\t\t\t\t\t\t------------------------------\n");
        printf("\n\t\t\t\t\t\t\t\tTotal Amount: %d\n", inv.bill_amount);
}

void updateStock(int code, int qty)
{
    clearScreen();
    FILE *fp;
    int i, count=0;
    Product temp[MAX_PRODUCTS];

    fp=fopen(PRODUCT_FILE,"rb");
    if(fp==NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tProduct File Missing\n");
        return;
    }

    while(fread(&temp[count],sizeof(Product),1,fp)==1)
    {
        count++;
    }
    fclose(fp);

    for(i=0; i<count; i++)
    {
        if(temp[i].code == code)
        {
            if(temp[i].stock < qty)
            {
                printf("\n\t\t\t\t\t\tStock for particular product is less than specified quantity...\n");
                printf("\n\t\t\t\t\t\t\t\tPlease update the stock first....\n");
                return;
            }
            temp[i].stock -= qty;
            break;
        }
    }

    fp=fopen(PRODUCT_FILE,"wb");
    for(i=0; i<count; i++)
    {
        fwrite(&temp[i],sizeof(Product),1,fp);
    }
    fclose(fp);
}

void ViewInvoice()
{
    clearScreen();
    int i, j;
    FILE *fp;
    Invoice inv;

    fp = fopen(INVOICE_FILE,"rb");

        if(fp == NULL){
            printf("\n\t\t\t\t\t\t\t\tFile does not exist!\n");
            return;
        }
    printf("\n\n\t\t\t\t\t\t********** All Invoices **********\n");

        while(fread(&inv,sizeof(Invoice),1,fp) == 1)
        {
            printf("\n\t\t\t\t\t==================================================\n");
            printf("\t\t\t\t\t||\t\t\t\t\t\t||");
            printf("\n\t\t\t\t\t||\tBill No: %d \t\t\t\t||",inv.billNo);
            printf("\n\t\t\t\t\t||\tCustomer Name: %s\t\t\t||",inv.custName);
            printf("\n\t\t\t\t\t||\tPurchase Date: %s\t\t||",inv.billDate);
            printf("\n\t\t\t\t\t||\t\t\t\t\t\t||");
            printf("\n\t\t\t\t\t||\tItems:\t\t\t\t\t||\n\t\t\t\t\t||\tCode\tName\tQty\tAmount\t\t||");
            for(j=0; j<inv.itemCount; j++)
            {
                printf("\n\t\t\t\t\t||\t%d\t%s\t%d\t%d\t\t||", inv.items[j].prdCode,inv.items[j].prdName,
                       inv.items[j].qty, inv.items[j].total_amount);
            }
            printf("\n\t\t\t\t\t||----------------------------------------------||\n");
            printf("\t\t\t\t\t||\t\t\t\t\t\t||");
            printf("\n\t\t\t\t\t||\tTotal Bill Amount: %10d\t\t||\n", inv.bill_amount);
            printf("\t\t\t\t\t||\t\t\t\t\t\t||");
            printf("\n\t\t\t\t\t==================================================\n");
        }
}

void SearchInvoice()
{
    clearScreen();
    int ch = SearchMenu();

    switch(ch)
    {
        case 1:
            SearchBillNo();
            break;
        case 2:
            SearchCustName();
            break;
        case 3:
            SearchDate();
            break;
        default:
            printf("\n\t\t\t\t\t\t\t\tInvalid Choice...\n");
    }
}

int SearchMenu()
{
    clearScreen();
    int ch;
    printf("\n\t\t\t\t\t\t\tSearch Through: ");
    printf("\n\t\t\t\t\t\t\t1. Bill Number");
    printf("\n\t\t\t\t\t\t\t2. Customer Name");
    printf("\n\t\t\t\t\t\t\t3. Purchase Date");
    printf("\n\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%d",&ch);

    return ch;
}

void SearchBillNo()
{
    clearScreen();
    int i,j, f=0, billno;
    FILE *fp;

    printf("\n\t\t\t\t\t\t\t\tEnter Bill No: ");
    scanf("%d",&billno);

    fp=fopen(INVOICE_FILE,"rb");
    if(fp==NULL){
        printf("no invoice found\n");
    }

    Invoice temp;
    while(fread(&temp,sizeof(Invoice),1,fp)==1){
        if(temp.billNo == billno)
        {
            f=1;
            printf("\n\t\t\t\t\t\t\t\t****** Invoice Found ******\n");
            printf("\n\t\t\t\t\t\t\t\tBill No: %d",temp.billNo);
            printf("\n\t\t\t\t\t\t\t\tCustomer Name: %s",temp.custName);
            printf("\n\t\t\t\t\t\t\t\tPurchase Date: %s",temp.billDate);
            printf("\n\t\t\t\t\t\t\t\tItems:\n\t\t\t\t\t\t\t\tCode\tName\tQty\tAmount");
            for(j=0; j<temp.itemCount; j++)
            {
                printf("\n\t\t\t\t\t\t\t\t%d\t%s\t%d\t%d", temp.items[j].prdCode,temp.items[j].prdName,
                       temp.items[j].qty, temp.items[j].total_amount);
            }
            printf("\n\t\t\t\t\t\t\t\t---------------------------------------");
            printf("\n\t\t\t\t\t\t\t\tTotal Bill Amount: %d\n", temp.bill_amount);
        }
    }
    fclose(fp);
    if(f == 0)
        printf("\n\t\t\t\t\t\t\t\tNo Invoices Available...\n");
}


void SearchDate()
{
    clearScreen();
    int i,j, f=0;
    char bdate[50];
    FILE *fp;

    printf("\n\t\t\t\t\t\t\t\tEnter Purchase Date[DD/MM/YYYY]: ");
    fflush(stdin);
    gets(bdate);

    fp=fopen(INVOICE_FILE,"rb");
    if(fp==NULL){
        printf("no invoice found\n");
    }

    Invoice temp;
    while(fread(&temp,sizeof(Invoice),1,fp)==1){
        if(strcmp(temp.billDate,bdate)==0)
        {
            f=1;
            printf("\n\t\t\t\t\t\t\t\t****** Invoice Found *******");
            printf("\n\t\t\t\t\t\t\t\tBill No: %d",temp.billNo);
            printf("\n\t\t\t\t\t\t\t\tCustomer Name: %s",temp.custName);
            printf("\n\t\t\t\t\t\t\t\tPurchase Date: %s",temp.billDate);
            printf("\n\t\t\t\t\t\t\t\tItems:\n\t\t\t\t\t\t\t\tCode\tName\tQty\tAmount");
            for(j=0; j<temp.itemCount; j++)
            {
                printf("\n\t\t\t\t\t\t\t\t%d\t%s\t%d\t%d", temp.items[j].prdCode,temp.items[j].prdName,
                        temp.items[j].qty, temp.items[j].total_amount);
            }
            printf("\n\t\t\t\t\t\t\t\t---------------------------------------");
            printf("\n\t\t\t\t\t\t\t\tTotal Bill Amount: %d\n", temp.bill_amount);
            printf("\n\t\t\t\t\t\t\t\t---------------------------------------\n");
        }
    }
    fclose(fp);
    if(f == 0)
        printf("\n\t\t\t\t\t\t\t\tNo Invoices Available...\n");
}

void SearchCustName()
{
    clearScreen();
    int i,j, f=0;
    char cname[50];
    FILE *fp;

    printf("\n\t\t\t\t\t\t\t\tEnter Customer Name: ");
    fflush(stdin); gets(cname);

    fp=fopen(INVOICE_FILE,"rb");
    if(fp==NULL){
        printf("no invoice found\n");
    }

    Invoice temp;
    while(fread(&temp,sizeof(Invoice),1,fp)==1){
        if(stricmp(temp.custName,cname) == 0)
        {
            f=1;
            printf("\n\t\t\t\t\t\t\t\t****** Invoice Found ******\n");
            printf("\n\t\t\t\t\t\t\t\tBill No: %d",temp.billNo);
            printf("\n\t\t\t\t\t\t\t\tCustomer Name: %s",temp.custName);
            printf("\n\t\t\t\t\t\t\t\tPurchase Date: %s",temp.billDate);
            printf("\n\t\t\t\t\t\t\t\tItems:\n\t\t\t\t\t\t\t\tCode\tName\tQty\tAmount");
            for(j=0; j<temp.itemCount; j++)
            {
                printf("\n\t\t\t\t\t\t\t\t%d\t%s\t%d\t%d", temp.items[j].prdCode,temp.items[j].prdName,
                       temp.items[j].qty, temp.items[j].total_amount);
            }
            printf("\n\t\t\t\t\t\t\t\t---------------------------------------");
            printf("\n\t\t\t\t\t\t\t\tTotal Bill Amount: %d\n", temp.bill_amount);
            printf("\n\t\t\t\t\t\t\t\t---------------------------------------\n");
        }
    }
    if(f == 0)
        printf("\n\t\t\t\t\t\t\t\tNo Invoices Available...\n");
}

