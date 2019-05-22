#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 20


typedef struct car{
    char id[MAX_SIZE];
    char color[MAX_SIZE];
    double engine_volume;
    char brand[MAX_SIZE];
    double price;
}sCar_t;

struct sList_t{
    sCar_t payload;
    struct sList_t *next;
};
typedef struct sList_t sList_t;

//prototypes
sList_t *new_car(sList_t *,sList_t *);
sList_t *stack_sList_t(sList_t *,sList_t *);
void print_entered_cars();
void brand_search(sList_t *,sList_t *);
sList_t *delete_by_id(sList_t *,sList_t *);
void free_sList_t(sList_t *,sList_t *);
void price_brand_search(sList_t *,sList_t *);
void write_to_file(FILE *,sList_t *,sList_t *);


int main()
{
    int choice;

    FILE *fp=NULL;

    sList_t *head=NULL;
    sList_t *node=NULL;

//    head = (sList_t*)malloc(sizeof(sList_t));
    //node = (sList_t*)malloc(sizeof(sList_t));

    if((fp=fopen("car.data", "ab"))==NULL){
        perror(NULL);
        exit(10);
    }

    do{
        printf("Menu:");
        printf("\n1. Add a car;");
        printf("\n2. Search for brand;");
        printf("\n3. Delete by ID;");
        printf("\n4. Search for expensive cars from a brand;");
        printf("\n5. Exit.");


        do{
            printf("\n\nEnter your choice: ");
            scanf("%d",&choice);
            while(getchar()!='\n');
        }while(choice<1 || choice>5);

        if(choice == 1){
            head = stack_sList_t(head,node);
        }
        if(choice == 2){
            if(head == NULL)
                printf("\nNo entered cars.\n");
            else
                brand_search(head,node);
        }
        if(choice == 3){
            if(head !=NULL)
                head = delete_by_id(head,node);
            else printf("\nNo entered cars.\n");
        }
        if(choice == 4)
            price_brand_search(head,node);

        printf("\n");
    }while(choice != 5);

    if(head != NULL){
        write_to_file(fp,head,node);
    }
    fclose(fp);

    print_entered_cars(head, node);

    return 0;
}

sList_t *new_car(sList_t *head,sList_t *node){
    sList_t *result = NULL;

    result = (sList_t*)malloc(sizeof(sList_t));

    fflush(stdin);
    printf("\nID: ");
    scanf("%s",result->payload.id);

    //printf("node = %p\nhead = %p\nresu = %p",node, head, result);


        for(node = head; node!=NULL; node=node->next){

            //printf("node = %p\nhead = %p\nresu = %p",node, head, result);

            if(strcmp(node->payload.id,result->payload.id)==0){
                printf("\nThere is already a car with this ID.");

                printf("\nID: \t\t  %s\n",node->payload.id);
                printf("Color: \t\t  %s",node->payload.color);
                printf("Engine's Volume:  %lf\n",node->payload.engine_volume);
                printf("Brand: \t\t  %s",node->payload.brand);
                printf("Price: \t\t  %lf\n",node->payload.price);

                return NULL;
            }
        }



    fflush(stdin);
    printf("\nColor: ");
    fgets(result->payload.color,MAX_SIZE,stdin);

    printf("\nEngine's volume: ");
    scanf("%lf",&result->payload.engine_volume);

    fflush(stdin);
    printf("\nBrand: ");
    fgets(result->payload.brand,MAX_SIZE,stdin);

    printf("\nPrice: ");
    scanf("%lf",&result->payload.price);

    fflush(stdin);
    result->next = NULL;

    return result;
}
sList_t *stack_sList_t(sList_t *head,sList_t *node)
{

    if(head != NULL){
        //temp = head;
        node = new_car(head, node);
        if(node != NULL){
            node->next = head;
            head = node;
        }
    }
    else{
        head = new_car(head, node);
    }

    return head;
}

void brand_search(sList_t *head,sList_t *node)
{
    char search_for_brand[MAX_SIZE];

    printf("\nEnter the brand you are searching for: ");
    fgets(search_for_brand,MAX_SIZE,stdin);

    for(node = head; node!=NULL; node = node->next){
        if(strcmp(search_for_brand,node->payload.brand)==0){
            printf("\nID: \t\t  %s\n",node->payload.id);
            printf("Color: \t\t  %s",node->payload.color);
            printf("Engine's Volume:  %lf\n",node->payload.engine_volume);
            printf("Brand: \t\t  %s",node->payload.brand);
            printf("Price: \t\t  %lf\n",node->payload.price);
        }
        else{
            printf("\nNot found.\n");
        }
    }

}

sList_t *delete_by_id(sList_t *head,sList_t *node)
{
    sList_t *temp = NULL;
    sList_t *temp2 = NULL;
    node = head;
    temp = node->next;
    char id_to_delete[MAX_SIZE];

    printf("\nEnter the ID of the car you want to delete: ");
    scanf("%s",id_to_delete);

    for(;temp!=NULL;temp=temp->next){
        if(!strcmp(temp->payload.id,id_to_delete)){
            //working
            if(head->next == NULL){
                free(head);
                return NULL;
            }

           temp2 = temp->next;
           free(temp);
           node->next = temp2;

        }
        if(!strcmp(head->payload.id,id_to_delete)){
            temp = head->next;
            free(head);
            head = temp;
        }

        node = node->next;
    }

    return head;

}

void price_brand_search(sList_t *head,sList_t *node)
{
    char price_brand[MAX_SIZE];
    double average = 0 ;
    int counter = 0;

    if(head!=NULL){
        printf("\nEnter the brand you are looking for: ");
        fgets(price_brand,MAX_SIZE,stdin);


        for(node = head; node != NULL; node = node->next){

            if(!strcmp(node->payload.brand,price_brand)){
                average+=node->payload.price;
                counter ++;
            }
        }
        for(node = head; node!=NULL; node = node->next){
            if(!strcmp(node->payload.brand,price_brand)){
                if(node->payload.price>=(average/counter)){
                    printf("\nID: \t\t  %s\n",node->payload.id);
                    printf("Color: \t\t  %s",node->payload.color);
                    printf("Engine's Volume:  %lf\n",node->payload.engine_volume);
                    printf("Brand: \t\t  %s",node->payload.brand);
                    printf("Price: \t\t  %lf\n",node->payload.price);
                }

            }
            else{
                printf("\nNot found.\n");
            }
        }
    }
    else{
        printf("\nNo entered cars.\n");
    }
}

void free_sList_t(sList_t *head,sList_t *node)
{
    for(node=head;node->next!=NULL;node=node->next){
        free(node);
    }
}

void write_to_file(FILE *fp,sList_t *head, sList_t *node)
{
    for(node = head; node!=NULL; node = node->next){
        if(fwrite(&node->payload,sizeof(sCar_t),1,fp)!= 1){
            perror(NULL);
            fclose(fp);
            exit(444);
        }
    }
}
void print_entered_cars(sList_t *head, sList_t *node)
{
    for(node=head;node!=NULL;node=node->next){

        printf("\nID: \t\t  %s\n",node->payload.id);
        printf("Color: \t\t  %s",node->payload.color);
        printf("Engine's Volume:  %lf\n",node->payload.engine_volume);
        printf("Brand: \t\t  %s",node->payload.brand);
        printf("Price: \t\t  %lf\n",node->payload.price);

    }
}
