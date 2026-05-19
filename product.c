#include<stdio.h>
#include<conio.h>
#include<string.h>
#include "product_n.h"
#include "structures.h"

//add new product
void add_product() {
    clearScreen();
    int i, n, j, exist, a= 0, f=0;
    FILE *fp;

    fp = fopen(PRODUCT_FILE, "rb");
    if(fp != NULL){
        productCount = 0;
        while(productCount < MAX_PRODUCTS && fread(&products[productCount], sizeof(Product), 1, fp) == 1){
            productCount++;
        }
        fclose(fp);
    }

    printf("\n\t\t\t\t\t\t\t\tHow Many Products You Want To Add: ");
    scanf("%d", &n);


    fp = fopen(PRODUCT_FILE, "ab");
    if(fp == NULL){
        printf("\n\t\t\t\t\t\t\t\tFile Not Found!!\n");
        return;
    }
    while(a < n) {
        f=0;
        clearScreen();
        do {
            exist = 0;
            printf("\n\t\t\t\t\t\t\t\tEnter Product Code: ");
            scanf("%d", &products[productCount].code);

            for(j = 0; j < productCount; j++) {
                if(products[j].code == products[productCount].code) {
                    printf("\n\t\t\t\t\t\t\tThis code already exists! Enter a unique code.\n");
                    exist = 1;
                    break;
                }
            }
        } while(exist);

        printf("\n\t\t\t\t\t\t\t\tEnter Product Name: ");
        while(getchar()!='\n');
        gets(products[productCount].prdName);

        for(j=0;j<productCount;j++){
            if(stricmp(products[j].prdName,products[productCount].prdName)==0){
                int choice;
                printf("\n\t\t\t\t\t\t\tThis product name already exists!\n");
                printf("\t\t\t\t\t\t\t1. Update stock\n");
                printf("\t\t\t\t\t\t\t2. Exit\n");
                printf("\t\t\t\t\t\t\tEnter your choice: ");
                scanf("%d", &choice);

                if(choice==1){
                    f=1;
                    int add_stock;
                    printf("\n\t\t\t\t\t\t\tEnter stock to add: ");
                    scanf("%d", &add_stock);

                    products[j].stock+=add_stock;

                    fp = fopen(PRODUCT_FILE, "wb");
                    fwrite(products, sizeof(Product), productCount, fp);
                    fclose(fp);

                    printf("\n\t\t\t\t\t\t\tupdated successfully!\n");
                    break;
                }
                else{
                    printf("\n\t\t\t\t\t\t\tstock not updated exit..\n");
                    return;
                }
            }
        }

        if(f==0){
            printf("\n\t\t\t\t\t\t\t\tEnter Product Stock: ");
            scanf("%d", &products[productCount].stock);
        }

        printf("\n\t\t\t\t\t\t\t\tEnter Product Price: ");
        scanf("%d", &products[productCount].price);

        fwrite(&products[productCount], sizeof(Product), 1, fp);

        productCount++;
        a++;
    }

    fclose(fp);
    printf("\n\t\t\t\t\t\t\t\tProduct Added Successfully!\n");

}

void search_product() {
    clearScreen();
    int choice, i, found = 0, f=0;
    char s_name[50];
    int s_code;

    FILE *fp;



    printf("\n\t\t\t\t\t\t\t\tSearch Product Through: \n");
    printf("\t\t\t\t\t\t\t\t1. Name");
    printf("\n\t\t\t\t\t\t\t\t2. ID");
    printf("\n\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);


    fp = fopen(PRODUCT_FILE, "rb");
    if (fp == NULL) {
        printf("\n\t\t\t\t\t\t\t\tNo product data found...\n");
        return;
    }

    Product temp;

    switch(choice) {
        case 1:
            clearScreen();
            printf("\t\t\t\t\t\t\t\tEnter product name to search: ");
            fflush(stdin);
            gets(s_name);

            printf("\n\n\n\t\t\t\t\t\t\t\t   ****** %s Product Details ******\n",s_name);

            while(fread(&temp, sizeof(Product), 1, fp) == 1) {
                if(stricmp(temp.prdName, s_name) == 0) {
                    if(f==0){
                        printf("\n\n\n\t\t\t\t\t\t\t\tCode\t      Name      Stock   Price\n");
                        printf("\n\t\t\t\t\t\t\t    --------------------------------------------\n");
                        f=1;
                    }
                    printf("\n\t\t\t\t\t\t\t\t%d\t%10s\t%d\t%d\t", temp.code, temp.prdName, temp.stock, temp.price);
                    found = 1;
                }
            }

            if(found==0)
                printf("\n\t\t\t\t\t\t\t\tNot found.\n");
            break;

        case 2:
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tEnter product ID to search: ");
            scanf("%d", &s_code);

            printf("\n\n\n\t\t\t\t\t\t\t\t ****** %d ID Product Details ******\n",s_code);
            while(fread(&temp, sizeof(Product), 1, fp) == 1) {

                if(temp.code == s_code) {
                    if(f==0){
                        printf("\n\n\n\t\t\t\t\t\t\t\tCode\t      Name      Stock   Price\n");
                        printf("\n\t\t\t\t\t\t\t    --------------------------------------------\n");
                        f=1;
                    }
                    printf("\n\t\t\t\t\t\t\t\t%d\t%10s\t%d\t%d\t", temp.code, temp.prdName, temp.stock, temp.price);
                    found = 1;
                    break;
                }
            }

            if(found==0)
                printf("\n\t\t\t\t\t\t\t\tNot found.\n");
            break;

        default:
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tInvalid choice...\n");
    }
}



void delete_product(){
    clearScreen();
	int s_code,i,j,f=0,choice;
	char s_nm[50];

	FILE *fp;

	printf("\n\t\t\t\t\t\t\t\t1.Name \n\t\t\t\t\t\t\t\t2.ID \n\t\t\t\t\t\t\tEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if(choice==1){
        clearScreen();
        printf("\n\t\t\t\t\t\t\t\tEnter product name to delete: ");
        gets(s_nm);

        for(i=0;i<productCount;i++){
		if(stricmp(products[i].prdName,s_nm)==0){
			f=1;

			for(j=i;j<productCount-1;j++){
				products[j]=products[j+1];
			}

			productCount--;
			break;
		}
	}

}

    else if(choice==2){
        clearScreen();
        printf("\n\t\t\t\t\t\t\t\tEnter product code to delete: ");
        scanf("%d", &s_code);
        fflush(stdin);


        for(i = 0; i < productCount; i++) {
            if(products[i].code == s_code) {
                f = 1;
                for(j = i; j < productCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                productCount--;
                break;
            }
        }

    }

    else {
        clearScreen();
        printf("\n\t\t\t\t\t\t\t\tInvalid choice...\n");
        return;
    }


	if(f==0){
        clearScreen();
		printf("\n\t\t\t\t\t\t\tThis product is not found....");
	}

	else{

	fp = fopen(PRODUCT_FILE,"wb");
    if(fp != NULL){
        for(i=0; i<productCount; i++){
            fwrite(&products[i],sizeof(Product),1,fp);
        }
        fclose(fp);
    }

    printf("\n\t\t\t\t\t\t\t\tProduct deleted successfully.\n");

}
}




void update_product(){
    clearScreen();
	int i,c,j,s_code,choice;
	char s_nm[50];

	FILE *fp;

    printf("\n\t\t\t\t\t\t\t\t----- Update Menu -----\n");
    printf("\t\t\t\t\t\t\t\t1. Update Name\n");
    printf("\t\t\t\t\t\t\t\t2. Update Stock\n");
    printf("\t\t\t\t\t\t\t\t3. Update Price\n");
    printf("\t\t\t\t\t\t\t\t0. Exit Update\n");
    printf("\t\t\t\t\t\t\t\tEnter choice:");
    scanf("%d",&c);

    if(c == 0) {
        clearScreen();
        printf("\n\t\t\t\t\t\t\t\tExit update...\n");
        return;
    }
    clearScreen();
    printf("\n\t\t\t\t\t\t\t\t1.By name...");
    printf("\n\t\t\t\t\t\t\t\t2.By id...");
    printf("\n\t\t\t\t\t\t\t\tYou want to update using which column:");
    scanf("%d",&choice);
    while (getchar() != '\n');
        if(choice==1){
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tEnter product name:");
            gets(s_nm);

            for(i=0;i<productCount;i++){
                if(stricmp(products[i].prdName,s_nm)==0){
                    switch(c){
                            case 1:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tEnter product name:");
                                gets(products[i].prdName);
                                break;
                            case 2:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tEnter product stock:");
                                scanf("%d",&products[i].stock);
                                fflush(stdin);
                                break;
                            case 3:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tEnter product price:");
                                scanf("%d",&products[i].price);
                                fflush(stdin);
                                break;
                            case 0:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tExit update...");
                                break;
                            default:
                                clearScreen();
                                printf("\n\t\t\t\t\t\t\t\tInvalid choice...");
                    }

                    fp=fopen(PRODUCT_FILE,"wb");
                    if(fp != NULL){
                        for(j=0;j<productCount;j++){
                            fwrite(&products[j], sizeof(Product), 1, fp);
                        }
                    }
                    fclose(fp);
                    printf("\n\t\t\t\t\t\t\t\tUpdate successfull...\n");
                    return;
                }
            }
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tProduct not found.");
        }
        else if(choice==2){
            clearScreen();
            printf("\t\t\t\t\t\t\t\tEnter code:");
            scanf("%d",&s_code);
            fflush(stdin);

            for(i=0;i<productCount;i++){
                if(products[i].code==s_code){
                        switch(c){
                            case 1:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tEnter product name:");
                                gets(products[i].prdName);
                                break;
                            case 2:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tEnter product stock:");
                                scanf("%d",&products[i].stock);
                                fflush(stdin);
                                break;
                            case 3:
                                clearScreen();
                                printf("\t\t\t\t\t\t\tEnter product price:");
                                scanf("%d",&products[i].price);
                                fflush(stdin);
                                break;
                            case 0:
                                clearScreen();
                                printf("\t\t\t\t\t\t\t\tExit update...");
                                break;
                            default:
                                clearScreen();
                                printf("\t\n\t\t\t\t\t\t\tInvalid choice...");
                        }
                        fp=fopen(PRODUCT_FILE,"wb");
                        if(fp != NULL){
                            for(j=0;j<productCount;j++){
                                fwrite(&products[j], sizeof(Product), 1, fp);
                            }
                        }
                        fclose(fp);
                        printf("\n\t\t\t\t\t\t\t\tUpdate successfully...");
                        return;
                }
            }
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tProduct not found.");
        }
        else{
            clearScreen();
            printf("\n\t\t\t\t\t\t\t\tInvalid search choice...\n");
        }
}




void show_product(){
    clearScreen();
    int i=0;
    FILE *fp;

    fp=fopen(PRODUCT_FILE,"rb");

    if (fp == NULL) {
        printf("\n\t\t\t\t\t\t\t\tNo product data found...\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\t********** Product Details **********\n");
    printf("\n\n\n\t\t\t\t\t\t\t\tCode\t      Name      Stock   Price\n");
    printf("\n\t\t\t\t\t\t\t    --------------------------------------------\n");

    while(fread(&products[i], sizeof(Product), 1, fp) == 1){
       printf("\n\t\t\t\t\t\t\t\t%d\t%10s\t%d\t%d\t ", products[i].code, products[i].prdName,
              products[i].stock, products[i].price);
       i++;
    }
    printf("\n\t\t\t\t\t\t\t    --------------------------------------------");

    fclose(fp);
}
