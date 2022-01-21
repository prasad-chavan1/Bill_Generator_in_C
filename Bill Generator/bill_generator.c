#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[40];
    char date[23];
    int no_ofItems;
    struct items itm[20];
};
void gnt_bill_header(char name[50], char date[30])
{
    printf("\n\n");
    printf("\n========================================\n");
    printf("||           ADV MEGA SHOP            ||\n");
    printf("========================================\n");
    printf(" DATE: %s \n", date);
    printf(" INVOICE TO: %s \n", name);
    printf("========================================\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t");
    printf("\n========================================\n\n");
}
void gnt_bill_body(char name[30], int qty, float price)
{
    printf("%s\t\t", name);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}
void gnt_bill_foot(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst; //remaining
    printf("========================================\n");
    printf("\nSub Total:\t\t%.2f", total);
    printf("\nDiscount @10:\t\t%.2f\n", dis);
    printf("\t\t    ===========");
    printf("\nNet Total:\t\t%.2f", netTotal);
    printf("\nCGST @9:\t\t%.2f", cgst);
    printf("\nSGST @9:\t\t%.2f", cgst);
    printf("\n========================================\n");
    printf("\nGrand Total:\t\t%.2f", grandTotal);
    printf("\n========================================\n");
    printf("\n========THANK YOU VISIT US AGAIN========\n");
}

int main()
{
    int ch, n;
    struct orders ord, order;
    char savebill = 'y', flag = 'y';
    FILE *fp;
    char name[50];
    while (flag == 'y' || flag == 'Y')
    {
        float total; int invFound=0;
        printf("\n========================================\n");
        printf("||           ADV MEGA SHOP            ||\n");
        printf("========================================\n");
        printf("\n1. GENERATE NEW INVOICE");
        printf("\n2. SHOW ALL INVOICES");
        printf("\n3. SEARCH AN INVOICE");
        printf("\n4. EXIT MENU");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &ch);
        fflush(stdin);
        switch (ch)
        {
        case 1:

            printf("\nPlease Enter Name Of Customer:\t");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            printf("\nPlease Enter The Number Of items:    ");
            scanf("%d", &n);
            ord.no_ofItems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\nPlease Enter Item Number %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("Please Enter The quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please Enter The Unit Price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            gnt_bill_header(ord.customer, ord.date);
            for (int i = 0; i < ord.no_ofItems; i++)
            {
                gnt_bill_body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            gnt_bill_foot(total);

            printf("\nDo You want to Save Bill (y/n):\t");
            scanf("%s", &savebill);
            if (savebill == 'y' || savebill == 'Y')
            {
                fp = fopen("savedBills.dat", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                {
                    printf("\nSuccesfully Saved!!");
                }
                else
                    printf("\nError In Saving!!");
                fclose(fp);
            }
            break;
        case 2:
        {
            fp = fopen("savedBills.dat", "r");
            printf("\n========PREVIOUSLY SAVED BILLS========\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                gnt_bill_header(order.customer, order.date);
                for (int i = 0; i < order.no_ofItems; i++)
                {
                    gnt_bill_body(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                gnt_bill_foot(tot);
            }
            fclose(fp);
        }
        break;
        case 3:
        {
            printf("\nPlease Enter Name You want To Search:\t");
            //fgetc(stdin);
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            fp = fopen("savedBills.dat", "r");
            printf("\n========INVOICE OF %s========\n", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    gnt_bill_header(order.customer, order.date);
                    for (int i = 0; i < order.no_ofItems; i++)
                    {
                        gnt_bill_body(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    gnt_bill_foot(tot);
                    invFound = 1;
                }
            }
            if (!invFound)
            {
                printf("\nSorry!! Invoice Not Found!!");
            }

            fclose(fp);
        }
        break;
        case 4:
            printf("\n\tBYE BYE :)\n\n");
        default:
            printf("\nSorry Invalid Option!!");
            break;
        }
        printf("\nDo You Want To Continue Operation [y/n]:\t");
        scanf("%s", &flag);
        printf("\n\tBYE BYE :)\n\n");
    }
    return 0;
}