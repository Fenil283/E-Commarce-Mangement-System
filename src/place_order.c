#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

void sigalrm_handler()
{
	printf("\nExiting automatically due to time out.\n");
	exit(1);
}


FILE *fp;

char *products[] = {"Smartphone ", "Smart TV   ", "Facewash   ", "Make-up kit", "Lotion     ","Soap       ","Tooth-paste" ,"Fan        "};

char *category[] = {"Electronics", "Electronics", "Cosmetics  ", "Cosmetics  ", "Cosmetics  ","House Hold ","House Hold ","House Hold "};

char price[] = {15,30,10,10,10, 5, 5,10};

int no_of_prods = 8;

void display_products()
{
	int i;
	printf("\n\t\t ---Available Products--- \n\n");
	printf("Choice \t Name \t\t Category \t\t Price\n");
	for(i=0;i<8;i++)
	{
		printf("%d \t %s \t %s \t\t %d\n", i+1, products[i], category[i], price[i]);
	}
	printf("%d Back\n", i+1);
	printf("\n");
}


int main(int argc, char *argv[])
{
	signal(SIGALRM,sigalrm_handler);
	int choice_no,flag_usr=1,qty,amt; 
	time_t t;
	
	while(flag_usr)
	{
		display_products();
		
		printf("Enter your choice: ");
		scanf("%d", &choice_no);
		
		if(choice_no >= 1 && choice_no <= no_of_prods)
		{
			char *prod_details = (char *)malloc(150*sizeof(char));
			char *statement = (char *)malloc(150*sizeof(char));
			printf("Enter quantity: ");
			scanf("%d", &qty);
			amt = price[choice_no-1]*qty;
			
			
			int l1 = (int)((ceil(log10(qty))+1)*sizeof(char)),l2 = (int)((ceil(log10(amt))+1)*sizeof(char));
			int l3 = (int)((ceil(log10(amt))+1)*sizeof(char));
			char sqty[100],samt[100],opt, sprice[100];
			sprintf(sqty, "%d", qty);
			sprintf(samt, "%d", amt);
			
			sprintf(sprice, "%d", price[choice_no-1]);
			
			char ex[100];
			char am[100];
			
			int c=0;
			char pp[100];
			char zz[100];
			
				
			if(strlen(sqty) == 1)
			{
				strcpy(zz," ");
				strcat(zz,sqty);
				strcpy(sqty,zz);
				l1++;
			}
			else
				c++;
			
			if(strlen(samt) == 2)
			{
				strcpy(am," ");
				strcat(am,samt);
				strcpy(samt,am);
				l2++;
			}
			else
				c++;
			
			
			sqty[l1]='\0';
			samt[l2]='\0';
			sprice[l3]='\0';
			
			time(&t);
			char *temp = ctime(&t);
			
			temp[strlen(temp)-1]=' ';
			strcat(prod_details, temp);
			strcat(prod_details, "      ");
			strcat(prod_details, products[choice_no-1]);
			strcat(prod_details, "          ");
			strcat(prod_details, category[choice_no-1]);
			strcat(prod_details, "         ");
			
			strcpy(statement,prod_details);
			
			
			statement[strlen(statement)]='\0';
			strcat(prod_details, sprice);
			strcat(prod_details, "        ");
			strcat(prod_details, sqty);
			strcat(prod_details, "        ");
			strcat(prod_details, samt);
			strcat(prod_details, "\n");
			prod_details[strlen(prod_details)]='\0';
			
			printf("Your order is placed: \n");
			printf("%sPrice: %d      Qty: %d      Total: %d\n\n", statement, price[choice_no-1], qty, amt);
			
			
			fp = fopen(argv[1], "a");
			fputs(prod_details, fp);
			fclose(fp);
			
			free(prod_details);
			
			while(1)
			{
				printf("Do you want to place another order?((Y/y)=yes/(N/n)=no): ");
			
				getchar();
				
				alarm(5);
				
				
				
				opt = getchar();
				
				alarm(0);
				
				if(opt=='Y' || opt == 'y')
				{
					printf("\nContinue Shopping\n");
					
					break;
				}
				else if(opt == 'N' || opt == 'n')
				{
					flag_usr=0;
					printf("Thank you for shopping with us.\n\n");
					break;
				}
				else
				{
					printf("Please give appropriate input.\n\n");	
				}
			}
			
		}
		else if(choice_no==(no_of_prods+1))
			flag_usr=0;
		else
			printf("Invalid choice. Please try again.\n\n");
	}
}
