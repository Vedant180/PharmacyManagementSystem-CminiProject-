#include "project.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void heapify(heap*root);
heap Find_last(ll*head,heap*root);

queue*front=NULL;
queue*rear=NULL;

node*last=NULL;
int NUM=-1;
int find;
char delete[30]="";


void Save_To_File(ll*head){
      remove("list.txt");
      FILE*fp;
      fp=fopen("list.txt","w+");
      list*ptr=*head;
      while(ptr!=NULL){
          if(strcmp(delete, ptr->name)!=0)
          {
           fprintf(fp,"%s\t",ptr->name);
           fprintf(fp,"%d\t",ptr->stock );
           fprintf(fp,"%lf\n",ptr->price);
          }
           ptr=ptr->next;
      }
      fclose(fp);
      return;
}


void init(heap*root){
    *root=NULL;
    return;
}

ll GetInList(ll*head){
   FILE *fp;  
   fp=fopen("list.txt","r+");  
   list*ptr1=NULL;
   *head=malloc(sizeof(list));
   fscanf(fp,"%s",(*head)->name);
   fscanf(fp,"%d",&(*head)->stock);
   fscanf(fp,"%lf",&(*head)->price);
   ptr1=(*head);
   (*head)->next=NULL;
   char c='a';
   while(c!=EOF){
        list*NewNode1=malloc(sizeof(list));
        fscanf(fp,"%s",NewNode1->name);
        fscanf(fp,"%d",&NewNode1->stock);
        fscanf(fp,"%lf",&NewNode1->price);
        ptr1->next=NewNode1;
        ptr1=ptr1->next;
        ptr1->next=NULL;
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
        
    }

    fclose(fp);
    return *head;
}

void swapListNodes(list*A,list*B){
    char str1[40];
    int temp1=A->stock;
    A->stock=B->stock;
    B->stock=temp1;
    double temp2=A->price;
    A->price=B->price;
    B->price=temp2;
    strcpy(str1,A->name);
    strcpy(A->name,B->name);
    strcpy(B->name,str1);
}

void swapheapNodes(heap*A,heap*B){
    char str1[40];
    int temp1=(*A)->stock;
    (*A)->stock=(*B)->stock;
    (*B)->stock=temp1;
    double temp2=(*A)->price;
    (*A)->price=(*B)->price;
    (*B)->price=temp2;
    strcpy(str1,(*A)->name);
    strcpy((*A)->name,(*B)->name);
    strcpy((*B)->name,str1);
}

ll sort_des(ll*head){
    list*temp1;
    list*temp2=NULL;
    list*temp3=*head;
    int done;

    if((*head)==NULL){
        return NULL;
    }
    do
    {
    done=0;
    temp1=(*head);
    while (temp1->next != temp2){
        if(temp1->stock < temp1->next->stock){
            swapListNodes(temp1,temp1->next);
            done=1;
        }
        temp1=temp1->next;
    }
    temp2=temp1;
    }
    while(done);
    return *head;
}

ll sort_list(ll*head){
    int done;
    list*temp1;
    list*temp2=NULL;

    if((*head)==NULL){
        return NULL;
    }
    do
    {
        done=0;
        temp1=(*head);
        while (temp1->next != temp2){
            if(temp1->stock > temp1->next->stock){
                swapListNodes(temp1,temp1->next);
                done=1;
            }
            temp1=temp1->next;
        }
        temp2=temp1;
    }
    while(done);

    return *head;


}

heap Search(heap*root,int value){
    node*ptr=*root;
    if(ptr->left==NULL && ptr->right==NULL)
        return NULL;
    if(ptr->left->stock==value || ptr->right->stock==value)
        return ptr;
    node * temp = Search(&(ptr->left), value);
    if(temp)
        return temp;
    return Search(&(ptr->right), value);
}



void Order_List(heap*root, ll * head){
    last=Find_last(&(*head),&(*root));
    node*ptr;
    if(*root==NULL){
        return;
    }
    if((*root)->stock < 20){
        FILE *fp;
        strcpy(delete, (*root)->name);
        fp=fopen("order.txt","a+");
        fprintf(fp,"%s ",(*root)->name);
        fprintf(fp,"%d",(*root)->stock);
        fprintf(fp,"\n");
        if(last->left!=NULL){
           if(last->left->stock == find )
           {
              (*root)->stock=last->left->stock;
              strcpy((*root)->name,last->left->name);
              (*root)->price=last->left->price;
              free(last->left);
              last->left=NULL;
           }
        else  if(last->right!=NULL )
        {    
            if(last->right->stock == find){
               (*root)->stock=last->right->stock;
               strcpy((*root)->name,last->right->name);
               (*root)->price=last->right->price;
               free(last->right);
               last->right=NULL;
            }
        }
        heapify(root);
        Save_To_File(&(*head));
        fclose(fp);
        }
}
}



heap Find_last(ll*head,heap*root){
    node*ptr;
    *head=GetInList(head);
    *head=sort_des(head);
    list*temp3=*head;
    find=temp3->stock;

    ptr=Search(root,find);

    return ptr;
    
}


void heapify(heap*root){
    int r=0;
    int l=0;
    node*temp=*root;
    while(temp->left!=NULL || temp->right!=NULL){
        if(temp->left!=NULL && temp->right!=NULL){
            if((temp)->left->stock < (temp)->stock && (temp)->left->stock < (temp)->right->stock ){
              l=1;  
              swapheapNodes(&(temp)->left,&(temp));
            }
            else{
               r=1;
               swapheapNodes(&(temp)->right,&(temp));
            }
        }
        else if(temp->left!=NULL && temp->right==NULL){
            swapheapNodes(&(temp)->left,&(temp));
        }
        if(l==1){
            temp=temp->left;
        }
        if(r==1){
            temp=temp->right;
        }


}
}


void enque(heap*root){
    queue*newnode=malloc(sizeof(queue));
    newnode->root=*root;
    newnode->next=NULL;
    if(front==NULL && rear==NULL){
        front=newnode;
        rear=newnode;
    }
    else{
        rear->next=newnode;
        rear=newnode;
    }
}

void deque(){
    queue*temp;
    temp=front;
    if(front==NULL && rear==NULL){
        return;
    }
    if(front==rear){
        front=NULL;
        rear=NULL;
    }
    else{
        front=front->next;
    }
    free(temp);
}

heap init_heap(heap*root,int stock,char*name,double price){
    int i=0;
    node*temp=malloc(sizeof(node));
    temp->stock=stock;
    temp->price=price;
    strcpy(temp->name,name);
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

heap create_minHeap(ll*head,heap*root){
    if(*head==NULL){
        *root==NULL;
        return NULL;
    }
    list*point=*head;
    (*root)=init_heap(&(*root),(point)->stock,(point)->name,(point)->price);
    enque(&(*root));
    (point)=(point)->next;
    while(point){
        node*parent=front->root;    
        deque();   
        node*lastNode=NULL;
        node*leftChild=NULL;
        node*rightChild=NULL;
        leftChild=init_heap(&(*root),(point)->stock,(point)->name,(point)->price);
        enque((&leftChild));
        (point)=(point)->next;
        if(point){
            rightChild=init_heap(&(*root),(point)->stock,(point)->name,(point)->price);
            enque(&rightChild);
            (point)=(point)->next;
            if((point)==NULL){
                lastNode=rightChild;
            }
        }
        else{
            lastNode=leftChild;
        }
        parent->left=leftChild;
        parent->right=rightChild;      
}

    return (*root);

    
}

void Inorder_Traversal(heap root){
    if(root==NULL){
        return;
    }
    Inorder_Traversal(root->left);
    printf("%d\t",root->stock);
    printf("%s",root->name);
    printf("\n");
    Inorder_Traversal(root->right);

}





void Bill(ll*head,heap*root){
    int choice;
    int quantity;
    int total=0;
    double amount;
    int v=0;
    if((*head)==NULL){
        return;
    }
    while(1){
        char medicine[10];
        list*med=*head;
        node*ptr;
        printf("1.Continue with Billing\n");
        printf("0.Exit\n");
        scanf("%d",&choice);
        if(choice==1){
            printf("Enter medicine Name: ");
            scanf("%s",medicine);
            while(med!=NULL){
                if(strcmp(med->name,medicine)==0){
                    v=1;
                    find=med->stock;
                    printf("Enter the quantity");
                    scanf("%d",&quantity);
                    if(quantity > med->stock){
                        printf("Insufficient stock");
                        return;
                    }
                    else{
                        ptr=Search(&(*root),find);
                        if(ptr->left!=NULL){
                           if(ptr->left->stock==find){
                               ptr=ptr->left;
                        }
                        }
                        if(ptr->right!=NULL){
                            if(ptr->right->stock==find){
                                ptr=ptr->right;
                            }

                        }
                        FILE*fp;
                        fp=fopen("bill.txt","a");
                        ptr->stock=ptr->stock-quantity;
                        amount=(ptr->price)*quantity;
                        total=total+ (ptr->price)*(quantity);
                       // med->stock=med->stock-quantity;
                        fprintf(fp,"%s\t",ptr->name);
                        fprintf(fp,"%d\t",quantity);
                        fprintf(fp,"%lf\n",amount);
                        fclose(fp);

                    }
                }
                else{
                    if(v==1){
                        v=1;
                    }
                    else{
                        v=0;
                    }
                }
                med=med->next;
            }
        }

        if(v==0){
            printf("Medicine Not Available");
            return;
        }
        if (choice==0)
        {
            return;
        }

        
    }
    //Save_To_File(&(*head));
}

void Update(bl*newnode,ll*head){
    remove("list.txt");
    FILE*fp1;
    fp1=fopen("list.txt","w+");
    list*ptr=*head;
    while(ptr!=NULL){
        if(strcmp((*newnode)->name, ptr->name)==0)
        {   
            int avail=ptr->stock - (*newnode)->quantity;
            fprintf(fp1,"%s\t",ptr->name);
            fprintf(fp1,"%d\t",avail);
            fprintf(fp1,"%lf\n",ptr->price);
            }
            fprintf(fp1,"%s\t",ptr->name);
            fprintf(fp1,"%d\t",ptr->stock );
            fprintf(fp1,"%lf\n",ptr->price);
            ptr=ptr->next;
        }
    fclose(fp1);
}
void BILL_Amount(ll*head){
    int choice;
    int quantity;
    double total=0;
    double amount;
    int v=0;
    if((*head)==NULL){
        return;
    }
    list*head1=NULL;
    while(1){
        bill*newnode=malloc(sizeof(bill));
        list*med=*head;
        printf("1.Continue with Billing\n");
        printf("0.Exit\n");
        scanf("%d",&choice);
        if(choice==1){
            printf("Enter medicine Name: ");
            scanf("%s",newnode->name);
            while(med!=NULL){
                if(strcmp(med->name,newnode->name)==0){
                    printf("Enter the quantity: ");
                    scanf("%d",&newnode->quantity);
                    if(newnode->quantity > med->stock){
                        printf("Stock is insufficient");
                        return;
                    }
                    amount=newnode->quantity * med->price;
                    total=total+amount;
                    FILE*fp2;
                    fp2=fopen("bill.txt","a");
                    fprintf(fp2,"%s",newnode->name);
                    fprintf(fp2,"%d",newnode->quantity);
                    fprintf(fp2,"%lf",amount);
                    fclose(fp2);
                    Update(&newnode,&(*head));
                }
                else{
                 v=0;
                }
                med=med->next;
            }
            if(v==0){
                printf("Medicine Not Available");
                return;
            }

        }
        if(choice==0){
            return;
        }
    }
}


void Display_Order_List(){
    FILE *fp;
    char*name;
    fp=fopen("order.txt","r");
    while(fscanf(fp,"%s",name)!=EOF){
        printf("%s",name);
        printf("\n");
    }
    fclose(fp);
}

void Fill_Stock(){
    char name[20];
    int s;
    double price;
    FILE*fp;
    fp=fopen("list.txt","a+");
    printf("Enter Medicine Name: ");
    scanf("%s",name);
    printf("Enter the quantity of stock:");
    scanf("%d",&s);
    printf("Enter the price per unit:");
    scanf("%lf",&price);
    fprintf(fp,"%s","\n");
    fprintf(fp,"%s\t",name);
    fprintf(fp,"%d\t",s);
    fprintf(fp,"%lf",price);
    fclose(fp);
}

void Display_ALL(){
    system("clear");
    FILE*fp;;
    fp=fopen("list.txt","r");
    char c='a';
    while(c!=EOF){
        list*NewNode1=malloc(sizeof(list));
        fscanf(fp,"%s",NewNode1->name);
        fscanf(fp,"%d",&NewNode1->stock);
        fscanf(fp,"%lf",&NewNode1->price);
        printf("%-15s\t",NewNode1->name);
        printf("%-15d\t",NewNode1->stock);
        printf("%-15lf\n",NewNode1->price);
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

    


 
 



 
 




 /* list*ptr8=head;
while(ptr8!=NULL){
        printf("%s\t",ptr8->name);
        printf("%d\t",ptr8->stock);
        printf("%lf\n",ptr8->price);

    //     // printf("%s\n",ptr8->expiry);
        ptr8=ptr8->next;
    }*/
