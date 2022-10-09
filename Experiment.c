#include "projectnew.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void initBST(t *root)
{
  *root = NULL;
  return;
}
void preorderTraversal(node* root)
{
    if (!root)
        return;
 
    // first print the root's data
    printf("%d\t",root->stock);
 
    // then recur on left subtree
    preorderTraversal(root->left);
 
    // now recur on right subtree
    preorderTraversal(root->right);
}



t insertNode(t*root,node*Newnode1){
    if((*root)==NULL){
		Newnode1 -> left = Newnode1 -> right = NULL;
        Newnode1->parent=(*root);
		return Newnode1; 
    }
    if((*root) -> stock >= Newnode1->stock){
        (*root) -> left = insertNode(&(*root)->left, Newnode1);
    }

    else if((*root) -> price < Newnode1->price){
        (*root) -> right = insertNode(&(*root)->right,Newnode1);
    }
    return *root;
}


t GetInNode(t*root){
   FILE *fp;  
   char c;
   c='a';
   fp=fopen("list.txt","r+");  
   node*ptr1=NULL;
   if(*root==NULL){
    if(fgetc(fp)==EOF){
        fseek(fp,-1,SEEK_CUR);
        fclose(fp);
        return *root;
    }
    fseek(fp,-1,SEEK_CUR);
    node*NewNode1=malloc(sizeof(node));
    fscanf(fp,"%s",NewNode1->name);
    fscanf(fp,"%d",&NewNode1->stock);
    fscanf(fp,"%lf",&NewNode1->price);
    *root=insertNode(&(*root),NewNode1);

    }
   ptr1=(*root);
   c='a';
   while(c!=EOF){
        node*NewNode1=malloc(sizeof(node));
        fscanf(fp,"%s",NewNode1->name);
        fscanf(fp,"%d",&NewNode1->stock);
        fscanf(fp,"%lf",&NewNode1->price);
        *root=insertNode(&(*root),NewNode1);
        if(fgetc(fp)==EOF){
           break;
        } 
        c=fgetc(fp);
        fseek(fp,-1,SEEK_CUR);
        
    }

    fclose(fp);
    return *root;
}

void Inorder_Traversal(t root,int*arr,int * i){
    if(root==NULL){
        return;
    }
    Inorder_Traversal(root->left,arr,i);
    arr[*i]=root->stock;
    (*i)++;
    Inorder_Traversal(root->right,arr,i);
}

int* minheap(t root,int count){
    int* arr;
    arr=malloc(sizeof(int)*count);
    int i=0;
    Inorder_Traversal(root,arr,&i);
    return arr;
}

node* insertLevelOrder(int arr[],
                       int i, int n)
{
      node *root = NULL;
    // Base case for recursion
    if (i < n)
    {
        root = newNode(arr[i]);
          
        // insert left child
        root->left = insertLevelOrder(arr,
                   2 * i + 1, n);
  
        // insert right child
        root->right = insertLevelOrder(arr,
                  2 * i + 2, n);
    }
    return root;
}