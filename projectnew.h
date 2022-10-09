typedef struct node{
    int stock;
    double price;
    char name[40];
}node;

typedef struct heap{
    node*arr;
    int rear;
    int size;
}heap;


typedef node*t;



