#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include "login.h"
#include "product_n.h"
#include "structures.h"
#include "generateInvoice.h"

int menu();

int main()
{
    int ch;
    char choice,u_name[50],d_name[50];

    int i=0;
    FILE *fp;
    productCount=0;
    fp=fopen(PRODUCT_FILE,"rb");

    if (fp != NULL) {
        productCount = 0;
        while (productCount < MAX_PRODUCTS && fread(&products[productCount], sizeof(Product), 1, fp) == 1) {
            productCount++;
        }
        fclose(fp);
    }


    if(login())
    {
        do
        {
            ch=menu();

            switch (ch)
            {
                case 0:
                exit(0);

                case 1:
                    add_product();
                    break;

                case 2:
                    update_product();
                    break;

                case 3:
                    delete_product();
                    break;

                case 4:
                    show_product();
                    break;

                case 5:
                    search_product();
                    break;

                case 6:
                    GenerateInvoice();
                    break;

                case 7:
                    SearchInvoice();
                    break;

                case 8:
                    ViewInvoice();
                    break;

                default:
                    printf("\n\t\t\t\t\t\tInvalid Choice....\n");
        }

        getch();
        clearScreen();
        printf("\n\n\t\t\t\t\t\t\tDo you want to continue? [Y/N]");
            scanf(" %c",&choice);

        }while(choice=='Y'||choice=='y' );
    }

    getch();
    return 0;
}

int menu()
{
    clearScreen();
    int ch;

    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t*************** Invoice Menu ***************\n");
    printf("\t\t\t\t\t\t\t*\t\t\t\t\t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t0. Exit \t\t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t1. Add Product \t\t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t2. Update Product \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t3. Delete Product \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t4. View Products \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t5. Search Product \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t6. Generate Invoice \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t7. Search Invoice \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t8. View Invoice \t   *\n");
    printf("\t\t\t\t\t\t\t*\t\t\t\t\t   *\n");
    printf("\t\t\t\t\t\t\t********************************************\n");
    printf("\n\t\t\t\t\t\t\t\t   Please Enter your Choice: ");
    scanf("%d",&ch);

    return ch;
}
