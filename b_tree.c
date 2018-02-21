#include "stdio.h"
#include "stdlib.h"
#define MAX 100

typedef struct btree_node {
  struct btree_node *parent, *left, *right;
  int key;
} node;

typedef struct queue {
  node *mass[MAX];
  int front, last;
} que;

node* search_btree(node *root, int user_key);
void pre_order(node* node);
void in_order(node* node);
void post_order(node* node);
que *init_que();
void add_to_que(que* q, node* n);
void del_from_que(que* q);
int isempty_que(que* q);
void level_order(node* root);
void del_node(node* root, int user_key);
void add_node(int user_key, node* root);
node* smallest_right(node *root);
node* init_btree(int user_key);

int main() {
  int i;
  scanf("%d", &i);
  node * test = init_btree(i);
  while(i != -1) {
    scanf("%d", &i);
    add_node(i, test);
  }
  pre_order(test);
  printf("\n");
  in_order(test);
  printf("\n");
  post_order(test);
  printf("\n");
  level_order(test);
  printf("\n");
  scanf("%d", &i);
  printf("\n");
  del_node(test, i);
    level_order(test);
  return(0);
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
void add_to_que(que* q, node* n) {
  if(q->last < MAX - 1) {
    q->last++;
    q->mass[q->last] = n;
  }
  else printf("Too big tree, i`m sorry\n");
}
int isempty_que(que* q) {
  if(q->last < q->front) return (1);
  else return (0);
}
void del_from_que(que* q) {
  if(isempty_que(q)) return;
  for(int i = q->last; i > q->front; i--)
    q->mass[i - 1] = q->mass[i];
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
  node *temp = search_btree(root, user_key);
  node *par = temp->parent;

  if(temp == NULL) return;

  if((!temp->right) && (!temp->left)) {
    if(par) {
      if(par->key <= user_key) par->right = NULL;
      else par->left = NULL;
    }
  }

  else if((!temp->right) && (temp->left)) {
    if(par) {
      if(par->key <= user_key) par->right = temp->left;
      else par->left = temp->left;
    }
    (temp->left)->parent = par;
  }

  else if((temp->right) && (!temp->left)) {
    if(par) {
      if(par->key <= user_key) par->right = temp->right;
      else par->left = temp->right;
    }
    (temp->right)->parent = par;
  }

  else {
    node *sm_r = smallest_right(temp);
    if(par) {
      if(par->key <= user_key) par->right = sm_r;
      else par->left = sm_r;
      }

    if(sm_r->parent == temp) sm_r->parent = par;
    else {
      (sm_r->parent)->left = sm_r->right;
      (sm_r->right)->parent = sm_r->parent;
    }
    sm_r->left = temp->left;
  }
  free(temp);
  return;
}
void add_node(int user_key, node* root) {
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

  add_to_que(q, root);

  while(!isempty_que(q)) {
    node *temp = q->mass[q->front];
    del_from_que(q);
    printf("%d ", temp->key);

    if(temp->left != NULL)
      add_to_que(q, temp->left);

    if(temp->right != NULL)
      add_to_que(q, temp->right);
  }
}
