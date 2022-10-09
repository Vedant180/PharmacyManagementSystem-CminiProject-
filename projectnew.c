#include "projectnew.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void init(heap *h)
{
  h->arr=(node *)malloc(sizeof(node)*5000);
  h->size=5000;
  h->rear=-1;
  return;
}

void heapify(heap *h)
{
    int i=h->rear,p=(i-1)/2;
    while(p>=0)
    {
        if(h->arr[i].stock < h->arr[p].stock)
        {
            node temp=h->arr[i];
            h->arr[i]=h->arr[p];
            h->arr[p]=temp;
        }
        else
            return ;
        i=p;
        p=(i-1)/2;
    }
    return ;
}


void insertnn(node n, heap *h)
{
	if(h->rear>=h->size)
		return ;
	h->rear++;
	h->arr[h->rear]=n;
	heapify(h);
	return;
}

void Order_List(node n){
        FILE *fp;
        fp=fopen("order.txt","a+");
        if(fp==NULL){
            printf("Cannot open file");
            return;
        }
        fprintf(fp,"%s ",n.name);
        fprintf(fp,"%d",n.stock);
        fprintf(fp,"\n");
        fclose(fp);
}

void td_heapify(heap *h) 
{ 
    int i=0; 
    while(i<=h->rear) 
    { 
        int c1=2*i+1, c2=2*i+2; 
        if(c1<=h->rear && c2<=h->rear) 
        { 
            if(h->arr[i].stock > h->arr[c1].stock && h->arr[i].stock > h->arr[c2].stock) 
            { 
                if(h->arr[c1].stock < h->arr[c2].stock) 
                { 
                    node temp=h->arr[c1]; 
                    h->arr[c1]=h->arr[i]; 
                    h->arr[i]=temp; 
                    i=c1; 
                } 
                else 
                { 
                    node temp=h->arr[c2]; 
                    h->arr[c2]=h->arr[i]; 
                    h->arr[i]=temp; 
                    i=c2; 
                } 
            } 
            else if(h->arr[i].stock > h->arr[c1].stock) 
            { 
                node temp=h->arr[c1]; 
                h->arr[c1]=h->arr[i]; 
                h->arr[i]=temp; 
                i=c1; 
            } 
            else if(h->arr[i].stock > h->arr[c2].stock) 
            { 
                node temp=h->arr[c2]; 
                h->arr[c2]=h->arr[i]; 
                h->arr[i]=temp; 
                i=c2; 
            } 
            else 
                return ; 
        } 
        else if(c1<=h->rear) 
        { 
            if(h->arr[i].stock > h->arr[c1].stock) 
            { 
                node temp=h->arr[c1]; 
                h->arr[c1]=h->arr[i]; 
                h->arr[i]=temp; 
                i=c1; 
            } 
            else  
                return ; 
        } 
        else if(c2<=h->rear) 
        { 
            if(h->arr[i].stock > h->arr[c2].stock) 
            { 
                node temp=h->arr[c2]; 
                h->arr[c2]=h->arr[i]; 
                h->arr[i]=temp; 
                i=c2; 
            } 
            else 
                return ; 
        } 
        else  
            return; 
    } 
    return ; 
}



node delete_elmt(heap *h) 
{ 
    node g;
    if(h->rear==-1) 
        return g; 
    node temp=h->arr[h->rear], ele=h->arr[0]; 
    h->arr[h->rear]=h->arr[0]; 
    h->arr[0]=temp; 
    h->rear--; 
    td_heapify(h); 
    return ele; 
} 
 

void check(heap *h)
{
 while(h->arr[0].stock < 20)
 {
  node deleted = delete_elmt(h);
  Order_List(deleted);
 }
}



void GetInNode(heap *h){
   FILE *fp;  
   char c;
   c='a';
   fp=fopen("list.txt","r+");  
   if(fgetc(fp)==EOF){
        fseek(fp,-1,SEEK_CUR);
        fclose(fp);
        return ;
    }
   while(c!=EOF){
        node NewNode1;
        fscanf(fp,"%s",NewNode1.name);
        fscanf(fp,"%d",&NewNode1.stock);
        fscanf(fp,"%lf",&NewNode1.price);
        insertnn(NewNode1, h);
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
        }

    fclose(fp);
    return ;
}

void Inorder_Traversal(heap h){
	int i;
	for(i=0;i<=h.rear;i++)
	{
		printf("%d\t%lf\t%s\n",h.arr[i].stock, h.arr[i].price, h.arr[i].name);
	}
    return ;
}

void Display_ALL(){
    system("clear");
    FILE*fp;;
    fp=fopen("list.txt","r");
    char c='a';
    while(c!=EOF){
        node*NewNode1=malloc(sizeof(node));
        fscanf(fp,"%s",NewNode1->name);
        fscanf(fp,"%d",&NewNode1->stock);
        fscanf(fp,"%lf",&NewNode1->price);
        printf("%-15s\t",NewNode1->name);
        printf("%-15d\t",NewNode1->stock);
        printf("%-15lf\n",NewNode1->price);
        free(NewNode1);
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
        
    }

    fclose(fp);

    printf("\n");
    printf("\n");
    printf("Press[ENTER] Key to continue:");
    while(getchar()!='\n');{
        getchar();
    }
    system("clear");
}

void Display_Order_List(){
    FILE *fp;
    char c='a';
    fp=fopen("order.txt","r");
    while(c!=EOF){
        node*Newnode=malloc(sizeof(node));
        fscanf(fp,"%s",Newnode->name);
        fscanf(fp,"%d",&Newnode->stock);
        printf("%s",Newnode->name);
        free(Newnode);
        printf("\n");
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
    }
    fclose(fp);
}

void Fill_Stock(){
    int f=0;
    char name[20];
    int s;
    double price;
    FILE*fp,*fp1;
    fp=fopen("list.txt","r+");
    fp1=fopen("order.txt","r+");
    printf("Enter Medicine Name: ");
    scanf("%s",name);
    printf("Enter the quantity of stock:");
    scanf("%d",&s);
    printf("Enter the price per unit:");
    scanf("%lf",&price);
    char c='a';
    while(c!=EOF){
        node*Newnode=malloc(sizeof(node));
        
        fscanf(fp,"%s",Newnode->name);
        fscanf(fp,"%d",&Newnode->stock);
        fscanf(fp,"%lf",&Newnode->price);
        if(strcmp(Newnode->name,name)==0){
            fseek(fp,(sizeof(Newnode->price)+sizeof(Newnode->stock)+2*sizeof("\t"))*-1,SEEK_CUR);
            f=1;
            fprintf(fp,"%d\t\t",s);
            fprintf(fp,"%lf",price);
            fclose(fp);
            break;
        }
        free(Newnode);
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
    }
    if(f==0){
        fp=fopen("list.txt","a+");
        fprintf(fp,"\n");
        fprintf(fp,"%s\t\t",name);
        fprintf(fp,"%d\t\t",s);
        fprintf(fp,"%lf",price);
        fclose(fp);
    }
}






int main(){
    FILE *fp;
    int choice;
    fp=fopen("list.txt","r");
    if(fp==NULL){
        printf("Cannnot Open file!");
        return 0;
    }

    heap h;
    init(&h);
    while(1){
        system("clear");
        printf("\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        printf("\t\t\t\t **Medicine Stock Management**");
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        printf("\n");

        while(1){
        printf("1.Display All Medicines\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("2.Order Depleted Stocks of Medicine\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("3.Display Order List\n\n");
        printf("-------------------------------------------------------\n\n");
        printf("4.Add New Stock\n\n");
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
            GetInNode(&h);
            check(&h);
            printf("Medicines Ordered Successfully\n\n");
            printf("Press[ENTER] Key to continue:");
            while(getchar()!='\n');{
                getchar();
            }
            system("clear");
        }
        if(choice==3){
            Display_Order_List();
        }
        if(choice==4){
            Fill_Stock();
        }
        // if(choice==5){
        //     head=GetInList(&head);
        //     head=sort_list(&head);
        //     create_minHeap(&(head),&(root));
        //     Bill(&head,&root);
        // }
        // if(choice==6){
        //     head=GetInList(&head);
        //     head=sort_list(&head);
        //     create_minHeap(&(head),&(root));
        //     Inorder_Traversal(root);
        // }
        if(choice==7){
            break;
        }
        }

    }

return 0;
}
 