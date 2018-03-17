#include "stdio.h"
#include "stdlib.h"
#define MAX 100

typedef struct btree_node {
    struct btree_node *parent, *left, *right;
    int key;
} node;

typedef struct queue {
    node *mass[MAX];
    int lvl[MAX];
    int front, last;
} que;

node* search_btree(node *root, int user_key);
void pre_order(node* node);
void in_order(node* node);
void post_order(node* node);
que *init_que();
void add_to_que(que* q, node* n, int lvl);
void del_from_que(que* q);
int isempty_que(que* q);
void level_order(node* root);
void del_node(node* root, int user_key);
void add_node(node* root, int user_key);
node* smallest_right(node *root);
node* init_btree(int user_key);
void del_tree(node** n);
void my_cp1_func(node* root);////My own function

int main() {
    int i;
    FILE* f;
    if((f = fopen("tree.txt", "r")) == NULL) {
        fprintf(stderr, "Error reading file");
        return (0);
    }
    fscanf(f, "%d", &i);
    node * n = init_btree(i);
    
    while(!feof(f)) {
        fscanf(f, "%d", &i);
        add_node(n, i);
    }
    fclose(f);

    printf("\n");
    my_cp1_func(n);
        printf("\n");
    pre_order(n);
    printf("\n");
    in_order(n);
        printf("\n");
    post_order(n);
        printf("\n");
    level_order(n);
    del_tree(&n);
    in_order(n);

    return (0);
}
node* init_btree(int user_key) {
    node* root = (node *) malloc(sizeof(node));
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
    root->key = user_key;

    return (root);
}
que* init_que() {
    que* temp = (que *) malloc(sizeof(que));
    temp->front = 1;
    temp->last = 0;

    return(temp);
}
void add_to_que(que* q, node* n, int lvl) {
    if(q->last < MAX - 1) {
        q->last++;
        q->mass[q->last] = n;
        q->lvl[q->last] = lvl;
    }
    else printf("Too big tree, i`m sorry\n");
}
int isempty_que(que* q) {
    if(q->last < q->front) return (1);
    else return (0);
}
void del_from_que(que* q) {
    if(isempty_que(q)) {
        printf("Queue is empty!\n");
        return;
    }
    for(int h = q->front; h < q->last; h++) {
        q->mass[h] = q->mass[h+1];
        q->lvl[h] = q->lvl[h+1];
    }
    q->last--;
}
node* search_btree(node *root, int user_key) {
    node* temp = root;
    while(temp->key != user_key) {
        if(temp == NULL) {printf("The node with %d value doesn`t exists", user_key); return(NULL);}
        if(user_key >= temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }

    return (temp);
}
node* smallest_right(node *root) {
    node *temp = root->right;
    while(temp->left != NULL) {
        temp = temp->left;
    }
    return (temp);
}
void del_node(node *root, int user_key) {
    node *t = search_btree(root, user_key);
    if(!t) return;
    node *p = t->parent;

    if(t->right && t->left) {
        node *smr = smallest_right(t);
        if(p) {
            if(p->key >= t->key) p->left = smr;
            else p->right = smr;
        }
       if(t->right != smr) {
           (smr->parent)->left = smr->right;
           if(smr->right)
           (smr->right)->parent = smr->parent;
           smr->right = t->right;
       }
        (t->left)->parent = smr;
        smr->parent = p;
        smr->left = t->left;
    } else if(!(t->right) && (t->left)) {
        if(p) {
            if(p->key >= t->key) p->left = t->left;
            else p->right = t->left;
        }
        (t->left)->parent = p;
    } else if((t->right) && !(t->left)) {
        if(p) {
            if(p->key >= t->key) p->left = t->right;
            else p->right = t->right;
        }
        (t->right)->parent = p;
    } else if(!(t->right) && !(t->left)){
        if(p) {
            if(p->key >= t->key) p->left = NULL;
            else p->right = NULL;
        }
    }
    free(t);
}
void add_node(node* root, int user_key) {
    node* n = (node *) malloc(sizeof(node));
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->key = user_key;
    node *temp1, *temp2 = root;

    while(temp2 != NULL) {
        temp1 = temp2;
        if(user_key >= temp2->key)
            temp2 = temp2->right;
        else
            temp2 = temp2->left;
    }
    n->parent = temp1;
    if(user_key >= temp1->key)
        temp1->right = n;
    else temp1->left = n;
}
void pre_order(node* node) {
    if(node == NULL) return;
    printf("%d, ", node->key);
    pre_order(node->left);        //left-parent-right
    pre_order(node->right);
}
void in_order(node* node) {
    if(node == NULL) return;
    in_order(node->left);
    printf("%d, ", node->key);    //sorted order
    in_order(node->right);
}
void post_order(node* node) {
    if(node == NULL) return;
    post_order(node->left);
    post_order(node->right);    //left-right-parent
    printf("%d, ", node->key);
}
void level_order(node* root) {
    if(root == NULL) return;
    que *q;
    q = init_que();
    add_to_que(q, root, 0);

    while(!isempty_que(q)) {
        node *temp = q->mass[q->front];
        del_from_que(q);
        printf("%d ", temp->key);

        if(temp->left != NULL) {
            add_to_que(q, temp->left, 0);
          }
        if(temp->right != NULL)
            add_to_que(q, temp->right, 0);
    }
    free(q);
}
void my_cp1_func(node* root) {
    if(root == NULL) return;
    que *q = init_que();
    int sum = 0, level = 0;

    add_to_que(q, root, level);
    printf("%d  ", root->key);
    sum += root->key;

    while(!isempty_que(q)) {
        node *temp = q->mass[q->front];
        int fr = q->front;

        if(q->lvl[fr] > level) {
          printf("%d  ", temp->key);
          sum += temp->key;
          level++;
        }

        if(temp->left != NULL)
            add_to_que(q, temp->left, q->lvl[fr] + 1);
        if(temp->right != NULL)
            add_to_que(q, temp->right, q->lvl[fr] + 1);
        del_from_que(q);
    }
    printf("Sum is: %d", sum);
    free(q);
}
void del_tree(node** n) {
    while((*n)->left)
        del_node((*n)->left, ((*n)->left)->key);
    while((*n)->right)
        del_node((*n)->right, ((*n)->right)->key);
    free(*n);
    *n = NULL;
}
