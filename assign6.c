#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    char itemName[64];
    char simpleName[16];
    int currQ;
    int maxQ;
    char body[128];
} Item;
int ch;
void menu()
{
    FILE *file = fopen("inventory.dat", "rb+");
    if(file == NULL)
    {
        printf("test\n");
        file = fopen("inventory.dat", "wb+");
        fclose(file);
        file = fopen("inventory.dat", "rb+");
    }
    while(1)
    {
        
        char choice;
        int itemNum;
        Item item;
        printf("Enter one of the following actions or press CTRL-D to exit.\n");
        printf("C - Create\n");
        printf("R - Read\n");
        printf("U - Update\n");
        printf("D - Delete\n");
        scanf(" %c", &choice);
        if(feof(stdin))
        {
            break;
        }
        printf("Enter Item Number (1 to 9999): ");
        scanf("%d", &itemNum);
        getchar();
        
        if(fseek(file, (itemNum) * sizeof(Item), SEEK_SET) != 0)
        {
            fprintf(stderr, "Error seeking in file\n");
            exit(1);
        } 
        fread(&item, sizeof(Item), 1, file); 
        
        if(choice == 'C' || choice == 'c')
        {
            if(strcmp(item.itemName, "") != 0)
            {
                printf("ERROR: item already exists\n");
            }
            else
            {
                printf("Enter Simple Name: ");
                fgets(item.simpleName, sizeof(item.simpleName), stdin);
                item.simpleName[strcspn(item.simpleName, "\n")] = '\0';
                printf("Enter Item Name: ");
                fgets(item.itemName, sizeof(item.itemName), stdin);
                item.itemName[strcspn(item.itemName, "\n")] = '\0';
                printf("Enter Current Quantity: ");
                scanf("%d", &item.currQ);
                getchar();
                printf("Enter Maximum Quantity: ");
                scanf("%d", &item.maxQ);
                getchar();
                printf("Enter Description: ");
                fgets(item.body, sizeof(item.body), stdin);
          
                fwrite(&item, sizeof(Item), 1, file);
            }
        }
        else if(choice == 'R' || choice == 'r')
        {
            if(strcmp(item.itemName, "") == 0)
            {
                printf("ERROR: item not found\n");
            }
            else
            {
                printf("Item Name: %s\n", item.itemName);
                printf("Simple Name: %s\n", item.simpleName);
                printf("Item Number: %d\n", itemNum);
                printf("Qty: %d/%d\n", item.currQ, item.maxQ);
                printf("Description: %s\n", item.body);
            }
        }
        else if(choice == 'U' || choice == 'u')
        {
            if(strcmp(item.itemName, "") == 0)
            {
                printf("ERROR: item not found\n");
            }
            else 
            {
                char NitemName[64];
                char NsimpleName[16];
                char NcurrQ[10];
                char NmaxQ[10];
                char Nbody[128];
                
                printf("Enter Simple Name: ");
                fgets(NsimpleName, sizeof(NsimpleName), stdin);
                NsimpleName[strcspn(NsimpleName, "\n")] = '\0';
                printf("Enter Item Name: ");
                fgets(NitemName, sizeof(NitemName), stdin);
                NitemName[strcspn(NitemName, "\n")] = '\0';
                printf("Enter Current Quantity: ");
                fgets(NcurrQ, sizeof(NcurrQ), stdin);
                NcurrQ[strcspn(NcurrQ, "\n")] = '\0';
                printf("Enter Maximum Quantity: ");
                fgets(NmaxQ, sizeof(NmaxQ), stdin);
                NmaxQ[strcspn(NmaxQ, "\n")] = '\0';
                
                printf("Enter Description: ");
                fgets(Nbody, sizeof(Nbody), stdin);
                
                if (!(strlen(NitemName) == 1 && NitemName[0] == '\n'))
                {
                    strcpy(item.itemName, NitemName);
                }
                if(!(strlen(NsimpleName) == 1 && NsimpleName[0] == '\n'))
                {
                    strcpy(item.simpleName, NsimpleName);
                }
                if(!(strlen(NcurrQ) == 1 && NcurrQ[0] == '\n'))
                {
                    item.currQ = atoi(NcurrQ);
                }
                if(!(strlen(NmaxQ) == 1 && NmaxQ[0] == '\n'))
                {
                    item.maxQ = atoi(NmaxQ);
                }     
                if(!(strlen(Nbody) == 1 && Nbody[0] == '\n'))
                {
                    strcpy(item.body,Nbody);            
                }
                fseek(file, -sizeof(Item), SEEK_CUR);
                fwrite(&item, sizeof(Item), 1, file);
            }
        }
        else if(choice == 'D' || choice == 'd')
        {
            if(strcmp(item.itemName, "") == 0)
            {
                printf("ERROR: item not found\n");
            }
            else
            {
                char tempSimpleName[16];
                strcpy(tempSimpleName, item.simpleName);
                memset(item.itemName, 0, sizeof(item.itemName));
                memset(item.simpleName, 0, sizeof(item.simpleName));
                item.currQ = 0;
                item.maxQ = 0;
                memset(item.body, 0, sizeof(item.body));
                printf("%s was successfully deleted.\n", tempSimpleName);
                fseek(file, -sizeof(Item), SEEK_CUR);
                fwrite(&item, sizeof(Item), 1, file);
            }
        }
        else
        {
            printf("ERROR: invalid option\n");
        }
        memset(item.itemName, 0, sizeof(item.itemName));
        memset(item.simpleName, 0, sizeof(item.simpleName));
        item.currQ = 0;
        item.maxQ = 0;
        memset(item.body, 0, sizeof(item.body));
  }
  fclose(file);
}

int main() 
{
    menu();
    return 0;
}
