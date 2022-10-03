typedef struct node{
    int stock;
    double price;
    char name[40];
    struct node*left;
    struct node*right;
}node;

typedef struct list{
    int stock;
    double price;
    char name[40];
    struct list*next;
}list;

typedef struct  queue{
    node*root;
    struct queue*next;
}queue;

typedef struct bill
{
    char name[40];
    int quantity;
    double amount;
}bill;



typedef queue*q;
typedef list*ll;
typedef node*heap;
typedef bill*bl;

void init(heap*root);
void Order_List(heap*root, ll * head);
void heapify(heap*root);
heap create_minHeap(ll*head,heap*root);
void Bill(ll*head,heap*root);
void Fill_Stock();
