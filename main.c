#include "project.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
    FILE *fp;
    int count=1;
    char c;
    int size;
    int choice;
    fp=fopen("list.txt","r");
    if(fp==NULL){
        printf("Cannnot Open file!");
        return 0;
    }
    while(1){
        c=getc(fp);
        if(c=='\n'){
            count+=1;
        }
        if(c==EOF){
            break;
        }
        c=getc(fp);
    }
    fclose(fp);
    node*root=NULL;
    list*head=NULL;
    node*LastchildParent;
    while(1){
        system("clear");
        printf("\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        printf("\t\t\t\t **PHARMACY MANAGEMENT SYSTEM**");
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        printf("\n");

        while(){
        printf("1.Display All Medicines\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("2.Order Depleted Stocks of Medicine\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("3.Display Order List\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("4.Add New Stock\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("5.Bill\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("6.Create Heap\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("7.Exit\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("Enter the choice:" );
        scanf("%d",&choice);
        system("clear");
        if(choice==1){
            printf("List of all medicines available currently.\n");
            Display_ALL();
        }
        if(choice==2){
            head=GetInList(&head);
            head=sort_list(&head);
            list*del=head;
            FILE*fp;
            fp=fopen("order.txt","a+");
            fprintf(fp,"%s ",(head)->name);
            fprintf(fp,"%d",(head)->stock);
            fprintf(fp,"\n");
            fclose(fp);
            head=head->next;
            del->next=NULL; 
            free(del);
            Save_To_File(&head);
            fp=fopen("order.txt","a+");
            
            
        }
        if(choice==3){
            Display_Order_List();
        }
        if(choice==4){
            Fill_Stock();
        }
        if(choice==5){
            head=GetInList(&head);
            head=sort_list(&head);
            create_minHeap(&(head),&(root));
            Bill(&head,&root);
        }
        if(choice==6){
            head=GetInList(&head);
            head=sort_list(&head);
            create_minHeap(&(head),&(root));
            Inorder_Traversal(root);
        }
        if(choice==7){
            break;
        }
        }

    }

return 0;
}
 
