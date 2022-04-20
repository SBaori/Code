// #include <stdio.h>
// #include <stdlib.h>
// #define order 3
// #define max_key order-1
// #define min_key order/2

// struct node
// {
//     int vals[max_key+1];
//     struct node* children[max_key+2];
//     int vals_count;
// };
// struct root
// {
//     int vals[max_key+1];
//     struct node* n[max_key+2];
//     int vals_count;
// };

// void merge(int arr[], int l, int m, int r)
// {
//     int i, j, k;
//     int n1 = m - l + 1;
//     int n2 = r - m;

//     /* create temp arrays */
//     int L[n1], R[n2];

//     /* Copy data to temp arrays L[] and R[] */
//     for (i = 0; i < n1; i++)
//         L[i] = arr[l + i];
//     for (j = 0; j < n2; j++)
//         R[j] = arr[m + 1 + j];

//     /* Merge the temp arrays back into arr[l..r]*/
//     i = 0; // Initial index of first subarray
//     j = 0; // Initial index of second subarray
//     k = l; // Initial index of merged subarray
//     while (i < n1 && j < n2) {
//         if (L[i] <= R[j]) {
//             arr[k] = L[i];
//             i++;
//         }
//         else {
//             arr[k] = R[j];
//             j++;
//         }
//         k++;
//     }

//     /* Copy the remaining elements of L[], if there
//     are any */
//     while (i < n1) {
//         arr[k] = L[i];
//         i++;
//         k++;
//     }

//     /* Copy the remaining elements of R[], if there
//     are any */
//     while (j < n2) {
//         arr[k] = R[j];
//         j++;
//         k++;
//     }
// }

// /* l is for left index and r is right index of the
// sub-array of arr to be sorted */
// void mergesort(int arr[], int l, int r)
// {
//     if (l < r) {
//         // Same as (l+r)/2, but avoids overflow for
//         // large l and h
//         int m = l + (r - l) / 2;

//         // Sort first and second halves
//         mergesort(arr, l, m);
//         mergesort(arr, m + 1, r);

//         merge(arr, l, m, r);
//     }
// }
// struct node* getnode()
// {
//     struct node* n = malloc(sizeof(struct node));
//     n->vals_count=0;
//     for(int i=0;i<max_key+1;i++)
//     {
//         n->children[i]=NULL;
//         n->vals[i]=10;
//     }

//     return n;
// }
// void splitnode_helper(struct node **left,struct node* child)
// {
//     struct node* new_left = getnode();
//     int i=0,j=0;
//     while(i<child->vals_count/2)
//     {
//         new_left->vals[i] = child->vals[i];
//         new_left->vals_count++;
//         new_left->children[i] = child->children[i];
//         i++;
//         j++;
//     }
//     new_left->children[i] = child->children[i];
//     (*left) = new_left;
//     struct node* new_right = getnode();
//     i++;
//     j=0;
//     while(i<child->vals_count)
//     {
//         new_right->vals[j] = child->vals[i];
//         new_right->vals_count++;
//         new_right->children[j] = child->children[i];
//         i++;
//         j++;
//     }
//     new_right->children[j] = child->children[i];
//     struct node **right = left+1;
//     (*right) = new_right;

// }
// struct node* splitnode(struct node* parent,struct node* child)
// {
//     struct node* new_parent = getnode();
//     if(parent!=NULL)
//     {
//         //parent->vals[parent->vals_count] = child->vals[(child->vals_count)/2];

//         for(int i=0;i<parent->vals_count;i++)
//         {
//             new_parent->vals[i] = parent->vals[i];

//         }
//         new_parent->vals[parent->vals_count] = child->vals[(child->vals_count)/2];
//         new_parent->vals_count=parent->vals_count+1;

//     }
//     else
//     {
//         new_parent->vals[0]=child->vals[(child->vals_count)/2];
//         new_parent->vals_count=1;
//     }

//     mergesort(new_parent->vals,0,new_parent->vals_count-1);
//     int i=0,j=0;
//     //printf("--%d--",new_parent->vals[0]);
//     while(new_parent->vals[i]!=child->vals[(child->vals_count)/2])
//     {
//         new_parent->children[i] = parent->children[i];
//         i++;
//         j++;
//     }
//         //printf("--%d--\n",new_parent->vals_count);
//     splitnode_helper(new_parent->children+i,child);
//     i+=2;
//     j++;

//     if(parent!=NULL && i<max_key+2)
//     {

//         while(j<parent->vals_count)
//         {
//             new_parent->children[i] = parent->children[j];
//             i++;
//             j++;
//         }
//         //printf("%d:%d\n",parent->children[j]->vals[0],j);
//         new_parent->children[i] = parent->children[j];

//     }

//     return new_parent;

// }
// struct node* mergenode(struct node* parent,int i)
// {
//     struct node* new_parent = getnode();
//     int n_parent=0,o_parent=0;
//     new_parent->vals_count=parent->vals_count-1;
//     while(o_parent<parent->vals_count && o_parent!=i)
//     {
//         new_parent->vals[o_parent] = parent->vals[o_parent];
//         new_parent->children[o_parent]=parent->children[o_parent];

//         o_parent++;
//         n_parent++;
//     }
//     struct node* mergedchild = getnode();
//     int merge_child = 0;
//     mergedchild->vals_count = parent->children[i]->vals_count+parent->children[i+1]->vals_count+1;
//     while(merge_child<mergedchild->vals_count)
//     {
//         if(merge_child<parent->children[i]->vals_count)
//         {
//             mergedchild->vals[merge_child] = parent->children[i]->vals[merge_child];
//             mergedchild->children[merge_child] = parent->children[i]->children[merge_child];
//         }
//         else if(merge_child==parent->children[i]->vals_count)
//         {
//             mergedchild->vals[merge_child] = parent->vals[i];
//             mergedchild->children[merge_child] = parent->children[i]->children[merge_child];
//         }
//         else
//         {
//             mergedchild->vals[merge_child] = parent->children[i+1]->vals[merge_child - (parent->children[i]->vals_count+1)];
//             mergedchild->children[merge_child] = parent->children[i+1]->children[merge_child - (parent->children[i]->vals_count+1)];
//         }
//         merge_child++;
//     }
//     //mergedchild->vals[merge_child] = parent->children[i]->vals[merge_child - parent->children[i]->vals_count];
//     mergedchild->children[merge_child] = parent->children[i+1]->children[merge_child - (parent->children[i]->vals_count+1)];

//     //free

//     new_parent->children[o_parent] = mergedchild;
//     new_parent->vals[o_parent] = parent->vals[o_parent+1];
//     o_parent+=2;
//     n_parent++;

//     while(o_parent<parent->vals_count)
//     {
//         new_parent->vals[n_parent] = parent->vals[o_parent];
//         new_parent->children[n_parent] = parent->children[o_parent];
//         n_parent++;
//         o_parent++;
//     }
//     new_parent->children[n_parent]=parent->children[o_parent];
//     return new_parent;

// }
// struct node* balancenode(struct node* parent,struct node* child,int i)
// {
//     int done=0;
//     if(child->children[0]==NULL)
//     {
//             if(i!=parent->vals_count && parent->children[i+1]->vals_count>min_key)
//             {
//                 parent->children[i]->vals[parent->children[i]->vals_count] = parent->vals[i];
//                 parent->vals[i] = parent->children[i+1]->vals[0];
//                 parent->children[i+1]->vals[0]=10;

//                 mergesort(parent->children[i+1]->vals,0,parent->children[i+1]->vals_count-1);
//                 parent->children[i+1]->vals_count--;
//                 done=1;

//             }
//             if(i!=0 && parent->children[i-1]->vals_count>min_key)
//             {
//                 parent->children[i]->vals[parent->children[i]->vals_count] = parent->vals[i-1];
//                 parent->vals[i-1] = parent->children[i-1]->vals[parent->children[i-1]->vals_count-1];
//                 parent->children[i-1]->vals[parent->children[i-1]->vals_count-1]=10;

//                 mergesort(parent->children[i-1]->vals,0,parent->children[i-1]->vals_count-1);
//                 parent->children[i-1]->vals_count--;
//                 done=1;
//             }
//             if(!done && i!=0)
//             {
//                 parent = mergenode(parent,i-1);
//             }
//             else if(!done)
//             {
//                 parent = mergenode(parent,i);
//             }

//     }
//     return parent;
// }
// struct node* delete(struct node* parent,struct node* child,int data)
// {
//     int i=0;
//     while(child->vals[i]<data && i<child->vals_count)
//     {
//         i++;
//     }
//     if(child->children[0]!=NULL && child->vals[i]!=data)
//     {
//         child->children[i] = delete(child,child->children[i],data);
//     }
//     else if(child->vals[i]==data)
//     {
//         if(child->children[i]==NULL)
//         {
//             child->vals[i]=10;
//             mergesort(child->vals,0,child->vals_count-1);
//             child->vals_count--;
//         }
//         // else
//         // {
//         //     struct node* replacer = replace();
//         // }
//     }
//     if(child->children[i]!=NULL)
//     {
//         if(child->children[i]->vals_count<min_key);
//             child = balancenode(child,child->children[i],i);

//     }
//     return child;
// }
// struct node* insert(struct node* parent,struct node* child,int data)
// {
//     // int i=search(data,child->vals);
//     int i=0;
//     while(child->vals[i]<data && i<child->vals_count)
//     {
//         i++;
//     }
//     if(child->children[i]!=NULL)
//         child->children[i] = insert(child,child->children[i],data);
//     else
//     {
//         child->vals[child->vals_count] = data;
//         child->vals_count++;
//         mergesort(child->vals,0,child->vals_count-1);
//     }
//     if(child->children[i]!=NULL)
//     {
//         int j=0,found=0;
//         while((j<child->vals_count+1) && !found)
//         {
//             if(child->children[j]->vals_count>max_key)
//             {
//                 child = splitnode(child,child->children[j]);
//                 found=1;
//             }
//             j++;
//         }
//     }
//     if(parent==NULL)
//     {
//         if(child->vals_count>max_key)
//             child = splitnode(NULL,child);
//     }
//     return child;
// }
#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// Node creation
void *createNode(void *ptr, void *child, int flag)
{
  void *newnode;
  if (flag)
  {
    struct BTreeNode_trainer *newNode;
    newNode = (struct BTreeNode_trainer *)malloc(sizeof(struct BTreeNode_trainer));
    // newNode = (struct BtreeNode_member *)malloc(sizeof(struct BtreeNode_member));
    newNode->ptrs[1] = ptr;
    newNode->count = 1;
    newNode->linker[0] = trainer_root;
    newNode->linker[1] = child;
    newnode = newNode;
  }
  else
  {
    struct BTreeNode_member *newNode = malloc(sizeof(struct BTreeNode_member));
    newNode->ptrs[1] = ptr;
    newNode->count = 1;
    newNode->linker[0] = member_root;
    newNode->linker[1] = child;
    newnode = newNode;
  }
  return newnode;
}

// Add value to the node
void addValToNode(void *ptr, int pos, void *node, void *child, int flag)
{
  if (flag)
  {
    int j = ((struct BTreeNode_member *)node)->count;
    while (j > pos)
    {
      ((struct BTreeNode_member *)node)->ptrs[j + 1] = ((struct BTreeNode_member *)node)->ptrs[j];
      ((struct BTreeNode_member *)node)->linker[j + 1] = ((struct BTreeNode_member *)node)->linker[j];
      j--;
    }
    ((struct BTreeNode_member *)node)->ptrs[j + 1] = ptr;
    ((struct BTreeNode_member *)node)->linker[j + 1] = child;
    ((struct BTreeNode_member *)node)->count++;
  }
  else
  {
    int j = ((struct BTreeNode_trainer *)node)->count;
    while (j > pos)
    {
      ((struct BTreeNode_trainer *)node)->ptrs[j + 1] = ((struct BTreeNode_trainer *)node)->ptrs[j];
      ((struct BTreeNode_trainer *)node)->linker[j + 1] = ((struct BTreeNode_trainer *)node)->linker[j];
      j--;
    }
    ((struct BTreeNode_trainer *)node)->ptrs[j + 1] = ptr;
    ((struct BTreeNode_trainer *)node)->linker[j + 1] = child;
    ((struct BTreeNode_trainer *)node)->count++;
  }
}

// Split the node
void splitNode(void *ptr, void **pval, int pos, void *node, void *child, void **newNode, int flag)
{
  if (flag)
  {
    int median, j;

    if (pos > MIN)
      median = MIN + 1;
    else
      median = MIN;

    // struct BTreeNode_trainer **node_tr = newNode;
    // struct trainer **pval_mr = pval;
    *((struct BTreeNode_trainer **)newNode) = (struct BTreeNode_trainer *)malloc(sizeof(struct BTreeNode_trainer));
    j = median + 1;
    while (j <= MAX)
    {
      (*((struct BTreeNode_trainer **)newNode))->ptrs[j - median] = ((struct BTreeNode_trainer *)node)->ptrs[j];
      (*((struct BTreeNode_trainer **)newNode))->linker[j - median] = ((struct BTreeNode_trainer *)node)->linker[j];
      j++;
    }
    ((struct BTreeNode_trainer *)node)->count = median;
    (*((struct BTreeNode_trainer **)newNode))->count = MAX - median;

    if (pos <= MIN)
    {
      addValToNode(ptr, pos, node, child, flag);
    }
    else
    {
      addValToNode(ptr, pos - median, (*((struct BTreeNode_trainer **)newNode)), child, flag);
    }
    *((struct trainer **)pval) = ((struct BTreeNode_trainer *)node)->ptrs[((struct BTreeNode_trainer *)node)->count]; //---------------------
    (*((struct BTreeNode_trainer **)newNode))->linker[0] = ((struct BTreeNode_trainer *)node)->linker[((struct BTreeNode_trainer *)node)->count];
    ((struct BTreeNode_trainer *)node)->count--;
  }
  else
  {
    int median, j;

    if (pos > MIN)
      median = MIN + 1;
    else
      median = MIN;

    // struct BTreeNode_member **node_mr = newNode;
    // struct member **pval_tr = pval;
    (*((struct BTreeNode_member **)newNode)) = (struct BTreeNode_member *)malloc(sizeof(struct BTreeNode_member));
    j = median + 1;
    while (j <= MAX)
    {
      (*((struct BTreeNode_member **)newNode))->ptrs[j - median] = ((struct BTreeNode_member *)node)->ptrs[j];
      (*((struct BTreeNode_member **)newNode))->linker[j - median] = ((struct BTreeNode_member *)node)->linker[j];
      j++;
    }
    ((struct BTreeNode_member *)node)->count = median;
    (*((struct BTreeNode_trainer **)newNode))->count = MAX - median;

    if (pos <= MIN)
    {
      addValToNode(ptr, pos, node, child, flag);
    }
    else
    {
      addValToNode(ptr, pos - median, (*((struct BTreeNode_trainer **)newNode)), child, flag);
    }
    *((struct member **)pval) = ((struct BTreeNode_member *)node)->ptrs[((struct BTreeNode_member *)node)->count]; //---------------------
    (*((struct BTreeNode_member **)newNode))->linker[0] = ((struct BTreeNode_member *)node)->linker[((struct BTreeNode_member *)node)->count];
    ((struct BTreeNode_member *)node)->count--;
  }
}

// Set the value in the node
int setValueInNode(void *ptr, void **pval, void *node, void **child, int flag)
{
  int res = 0;
  int d = 0;
  if (flag)
  {
    int pos;
    if (!node)
    {
      *((struct trainer **)pval) = ptr;
      *((struct BTreeNode_trainer **)child) = NULL;
      res = 1;
    }
    else if (((struct trainer *)ptr)->trainer_id < ((struct BTreeNode_trainer *)node)->ptrs[1]->trainer_id)
    {
      pos = 0;
    }
    else
    {
      for (pos = ((struct BTreeNode_trainer *)node)->count;
           (((struct trainer *)ptr)->trainer_id < ((struct BTreeNode_trainer *)node)->ptrs[pos]->trainer_id && pos > 1); pos--)
        ;
      if (((struct trainer *)ptr)->trainer_id == ((struct BTreeNode_trainer *)node)->ptrs[pos]->trainer_id)
      {
        printf("Duplicates not allowed\n");
        d = 1;
        res = 0;
      }
    }
    if (!d && !res && setValueInNode(ptr, pval, ((struct BTreeNode_trainer *)node)->linker[pos], child, flag))
    {
      if (((struct BTreeNode_trainer *)node)->count < MAX)
      {
        addValToNode(*pval, pos, node, *child, flag);
      }
      else
      {
        splitNode(*pval, pval, pos, node, *child, child, flag);
        res = 1;
      }
    }
  }
  else
  {
    int pos;
    if (!node)
    {
      *((struct member **)pval) = ptr;
      *((struct BTreeNode_member **)child) = NULL;
      res = 1;
    }
    else if (((struct member *)ptr)->member_id < ((struct BTreeNode_member *)node)->ptrs[1]->member_id)
    {
      pos = 0;
    }
    else
    {
      for (pos = ((struct BTreeNode_member *)node)->count;
           (((struct member *)ptr)->member_id < ((struct BTreeNode_member *)node)->ptrs[pos]->member_id && pos > 1); pos--)
        ;
      if (((struct member *)ptr)->member_id == ((struct BTreeNode_member *)node)->ptrs[pos]->member_id)
      {
        printf("Duplicates not allowed\n");
        res = 0;
        d = 1;
      }
    }
    if (!d && !res && setValueInNode(ptr, pval, ((struct BTreeNode_member *)node)->linker[pos], child, flag))
    {
      if (((struct BTreeNode_member *)node)->count < MAX)
      {
        addValToNode(*pval, pos, node, *child, flag);
      }
      else
      {
        splitNode(*pval, pval, pos, node, *child, child, flag);
        res = 1;
      }
    }
  }
  return res;
}

// Insertion operation
void insertion(void *ptr, int flag)
{
  if (flag)
  {
    int flag1;
    struct trainer *i;
    struct BTreeNode_trainer *child;
    flag1 = setValueInNode(ptr, (void **)&i, trainer_root, (void **)&child, flag);
    if (flag1)
      trainer_root = createNode(i, child, flag);
  }
  else
  {
    int flag1;
    struct member *i;
    struct BTreeNode_member *child;
    flag1 = setValueInNode(ptr, (void **)&i, member_root, (void **)&child, flag);
    if (flag1)
      member_root = createNode(i, child, flag);
  }
}

// Copy the successor
void copySuccessor(void *myNode, int pos, int flag)
{
  if (flag)
  {
    struct BTreeNode_trainer *dummy;
    dummy = ((struct BTreeNode_trainer *)myNode)->linker[pos];

    for (; dummy->linker[0] != NULL;)
      dummy = dummy->linker[0];
    ((struct BTreeNode_trainer *)myNode)->ptrs[pos] = dummy->ptrs[1];
  }
  else
  {
    struct BTreeNode_member *dummy;
    dummy = ((struct BTreeNode_member *)myNode)->linker[pos];

    for (; dummy->linker[0] != NULL;)
      dummy = dummy->linker[0];
    ((struct BTreeNode_member *)myNode)->ptrs[pos] = dummy->ptrs[1];
  }
}

// Remove the value
void removeVal(void *myNode, int pos, int flag)
{
  if (flag)
  {
    int i = pos + 1;
    while (i <= ((struct BTreeNode_trainer *)myNode)->count)
    {
      ((struct BTreeNode_trainer *)myNode)->ptrs[i - 1] = ((struct BTreeNode_trainer *)myNode)->ptrs[i];
      ((struct BTreeNode_trainer *)myNode)->linker[i - 1] = ((struct BTreeNode_trainer *)myNode)->linker[i];
      i++;
    }
    ((struct BTreeNode_trainer *)myNode)->count--;
  }
  else
  {
    int i = pos + 1;
    while (i <= ((struct BTreeNode_member *)myNode)->count)
    {
      ((struct BTreeNode_member *)myNode)->ptrs[i - 1] = ((struct BTreeNode_member *)myNode)->ptrs[i];
      ((struct BTreeNode_member *)myNode)->linker[i - 1] = ((struct BTreeNode_member *)myNode)->linker[i];
      i++;
    }
    ((struct BTreeNode_member *)myNode)->count--;
  }
}

// Do right shift
void rightShift(void *myNode, int pos, int flag)
{
  if (flag)
  {
    struct BTreeNode_trainer *x = ((struct BTreeNode_trainer *)myNode)->linker[pos];
    int j = x->count;

    while (j > 0)
    {
      x->ptrs[j + 1] = x->ptrs[j];
      x->linker[j + 1] = x->linker[j];
    }
    x->ptrs[1] = ((struct BTreeNode_trainer *)myNode)->ptrs[pos];
    x->linker[1] = x->linker[0];
    x->count++;

    x = ((struct BTreeNode_trainer *)myNode)->linker[pos - 1];
    ((struct BTreeNode_trainer *)myNode)->ptrs[pos] = x->ptrs[x->count];
    ((struct BTreeNode_trainer *)myNode)->linker[pos] = x->linker[x->count];
    x->count--;
  }
  else
  {
    struct BTreeNode_member *x = ((struct BTreeNode_member *)myNode)->linker[pos];
    int j = x->count;

    while (j > 0)
    {
      x->ptrs[j + 1] = x->ptrs[j];
      x->linker[j + 1] = x->linker[j];
    }
    x->ptrs[1] = ((struct BTreeNode_member *)myNode)->ptrs[pos];
    x->linker[1] = x->linker[0];
    x->count++;

    x = ((struct BTreeNode_member *)myNode)->linker[pos - 1];
    ((struct BTreeNode_member *)myNode)->ptrs[pos] = x->ptrs[x->count];
    ((struct BTreeNode_member *)myNode)->linker[pos] = x->linker[x->count];
    x->count--;
  }
  return;
}

// Do left shift
void leftShift(void *myNode, int pos, int flag)
{
  if (flag)
  {
    int j = 1;
    struct BTreeNode_trainer *x = ((struct BTreeNode_trainer *)myNode)->linker[pos - 1];

    x->count++;
    x->ptrs[x->count] = ((struct BTreeNode_trainer *)myNode)->ptrs[pos];
    x->linker[x->count] = ((struct BTreeNode_trainer *)myNode)->linker[pos]->linker[0];

    x = ((struct BTreeNode_trainer *)myNode)->linker[pos];
    ((struct BTreeNode_trainer *)myNode)->ptrs[pos] = x->ptrs[1];
    x->linker[0] = x->linker[1];
    x->count--;

    while (j <= x->count)
    {
      x->ptrs[j] = x->ptrs[j + 1];
      x->linker[j] = x->linker[j + 1];
      j++;
    }
  }
  else
  {
    int j = 1;
    struct BTreeNode_member *x = ((struct BTreeNode_member *)myNode)->linker[pos - 1];

    x->count++;
    x->ptrs[x->count] = ((struct BTreeNode_member *)myNode)->ptrs[pos];
    x->linker[x->count] = ((struct BTreeNode_member *)myNode)->linker[pos]->linker[0];

    x = ((struct BTreeNode_member *)myNode)->linker[pos];
    ((struct BTreeNode_member *)myNode)->ptrs[pos] = x->ptrs[1];
    x->linker[0] = x->linker[1];
    x->count--;

    while (j <= x->count)
    {
      x->ptrs[j] = x->ptrs[j + 1];
      x->linker[j] = x->linker[j + 1];
      j++;
    }
  }
  return;
}

// Merge the nodes
void mergeNodes(void *myNode, int pos, int flag)
{
  if (flag)
  {
    int j = 1;
    struct BTreeNode_trainer *x1 = ((struct BTreeNode_trainer *)myNode)->linker[pos], *x2 = ((struct BTreeNode_trainer *)myNode)->linker[pos - 1];

    x2->count++;
    x2->ptrs[x2->count] = ((struct BTreeNode_trainer *)myNode)->ptrs[pos];
    x2->linker[x2->count] = ((struct BTreeNode_trainer *)myNode)->linker[0];

    while (j <= x1->count)
    {
      x2->count++;
      x2->ptrs[x2->count] = x1->ptrs[j];
      x2->linker[x2->count] = x1->linker[j];
      j++;
    }

    j = pos;
    while (j < ((struct BTreeNode_trainer *)myNode)->count)
    {
      ((struct BTreeNode_trainer *)myNode)->ptrs[j] = ((struct BTreeNode_trainer *)myNode)->ptrs[j + 1];
      ((struct BTreeNode_trainer *)myNode)->linker[j] = ((struct BTreeNode_trainer *)myNode)->linker[j + 1];
      j++;
    }
    ((struct BTreeNode_trainer *)myNode)->count--;
    free(x1);
  }
  else
  {
    int j = 1;
    struct BTreeNode_member *x1 = ((struct BTreeNode_member *)myNode)->linker[pos], *x2 = ((struct BTreeNode_member *)myNode)->linker[pos - 1];

    x2->count++;
    x2->ptrs[x2->count] = ((struct BTreeNode_member *)myNode)->ptrs[pos];
    x2->linker[x2->count] = ((struct BTreeNode_member *)myNode)->linker[0];

    while (j <= x1->count)
    {
      x2->count++;
      x2->ptrs[x2->count] = x1->ptrs[j];
      x2->linker[x2->count] = x1->linker[j];
      j++;
    }

    j = pos;
    while (j < ((struct BTreeNode_member *)myNode)->count)
    {
      ((struct BTreeNode_member *)myNode)->ptrs[j] = ((struct BTreeNode_member *)myNode)->ptrs[j + 1];
      ((struct BTreeNode_member *)myNode)->linker[j] = ((struct BTreeNode_member *)myNode)->linker[j + 1];
      j++;
    }
    ((struct BTreeNode_member *)myNode)->count--;
    free(x1);
  }
}

// Adjust the node
void adjustNode(void *myNode, int pos, int flag)
{
  if (flag)
  {
    if (!pos)
    {
      if (((struct BTreeNode_trainer *)myNode)->linker[1]->count > MIN)
      {
        leftShift(myNode, 1, flag);
      }
      else
      {
        mergeNodes(myNode, 1, flag);
      }
    }
    else
    {
      if (((struct BTreeNode_trainer *)myNode)->count != pos)
      {
        if (((struct BTreeNode_trainer *)myNode)->linker[pos - 1]->count > MIN)
        {
          rightShift(((struct BTreeNode_trainer *)myNode), pos, flag);
        }
        else
        {
          if (((struct BTreeNode_trainer *)myNode)->linker[pos + 1]->count > MIN)
          {
            leftShift(((struct BTreeNode_trainer *)myNode), pos + 1, flag);
          }
          else
          {
            mergeNodes(((struct BTreeNode_trainer *)myNode), pos, flag);
          }
        }
      }
      else
      {
        if (((struct BTreeNode_trainer *)myNode)->linker[pos - 1]->count > MIN)
          rightShift(((struct BTreeNode_trainer *)myNode), pos, flag);
        else
          mergeNodes(((struct BTreeNode_trainer *)myNode), pos, flag);
      }
    }
  }
  else
  {
    if (!pos)
    {
      if (((struct BTreeNode_member *)myNode)->linker[1]->count > MIN)
      {
        leftShift(myNode, 1, flag);
      }
      else
      {
        mergeNodes(myNode, 1, flag);
      }
    }
    else
    {
      if (((struct BTreeNode_member *)myNode)->count != pos)
      {
        if (((struct BTreeNode_member *)myNode)->linker[pos - 1]->count > MIN)
        {
          rightShift(((struct BTreeNode_member *)myNode), pos, flag);
        }
        else
        {
          if (((struct BTreeNode_member *)myNode)->linker[pos + 1]->count > MIN)
          {
            leftShift(((struct BTreeNode_member *)myNode), pos + 1, flag);
          }
          else
          {
            mergeNodes(((struct BTreeNode_member *)myNode), pos, flag);
          }
        }
      }
      else
      {
        if (((struct BTreeNode_member *)myNode)->linker[pos - 1]->count > MIN)
          rightShift(((struct BTreeNode_member *)myNode), pos, flag);
        else
          mergeNodes(((struct BTreeNode_member *)myNode), pos, flag);
      }
    }
  }
}

// Delete a value from the node
int delValFromNode(int id, void *myNode, int flag)
{
  int pos, flag1 = 0;
  if (flag)
  {
    if (myNode)
    {
      if (id < ((struct BTreeNode_trainer *)myNode)->ptrs[1]->trainer_id)
      {
        pos = 0;
        flag1 = 0;
      }
      else
      {
        for (pos = ((struct BTreeNode_trainer *)myNode)->count; (id < ((struct BTreeNode_trainer *)myNode)->ptrs[pos]->trainer_id && pos > 1); pos--)
          ;
        if (id == ((struct BTreeNode_trainer *)myNode)->ptrs[pos]->trainer_id)
        {
          flag1 = 1;
        }
        else
        {
          flag1 = 0;
        }
      }
      if (flag1)
      {
        if (((struct BTreeNode_trainer *)myNode)->linker[pos - 1])
        {
          copySuccessor(myNode, pos, flag);
          flag1 = delValFromNode(((struct BTreeNode_trainer *)myNode)->ptrs[pos]->trainer_id, ((struct BTreeNode_trainer *)myNode)->linker[pos], flag);
          if (flag1 == 0)
          {
            printf("Given data is not present in B-Tree\n");
          }
        }
        else
        {
          removeVal(myNode, pos, flag);
        }
      }
      else
      {
        flag1 = delValFromNode(id, ((struct BTreeNode_trainer *)myNode)->linker[pos], flag);
      }
      if (((struct BTreeNode_trainer *)myNode)->linker[pos])
      {
        if (((struct BTreeNode_trainer *)myNode)->linker[pos]->count < MIN)
          adjustNode(myNode, pos, flag);
      }
    }
  }
  else
  {
    if (myNode)
    {
      if (id < ((struct BTreeNode_member *)myNode)->ptrs[1]->member_id)
      {
        pos = 0;
        flag1 = 0;
      }
      else
      {
        for (pos = ((struct BTreeNode_member *)myNode)->count; (id < ((struct BTreeNode_member *)myNode)->ptrs[pos]->member_id && pos > 1); pos--)
          ;
        if (id == ((struct BTreeNode_member *)myNode)->ptrs[pos]->member_id)
        {
          flag1 = 1;
        }
        else
        {
          flag1 = 0;
        }
      }
      if (flag1)
      {
        if (((struct BTreeNode_member *)myNode)->linker[pos - 1])
        {
          copySuccessor(myNode, pos, flag);
          flag1 = delValFromNode(((struct BTreeNode_member *)myNode)->ptrs[pos]->member_id, ((struct BTreeNode_member *)myNode)->linker[pos], flag);
          if (flag1 == 0)
          {
            printf("Given data is not present in B-Tree\n");
          }
        }
        else
        {
          removeVal(myNode, pos, flag);
        }
      }
      else
      {
        flag1 = delValFromNode(id, ((struct BTreeNode_member *)myNode)->linker[pos], flag);
      }
      if (((struct BTreeNode_member *)myNode)->linker[pos])
      {
        if (((struct BTreeNode_member *)myNode)->linker[pos]->count < MIN)
          adjustNode(myNode, pos, flag);
      }
    }
  }

  return flag1;
}

// Delete operaiton
void deletenode(int id, void *myNode, int flag)
{
  int t = 0;
  if (flag)
  {
    struct BTreeNode_trainer *tmp;
    if (!delValFromNode(id, myNode, flag))
    {
      printf("Trainer %d not found!\n", id);
      t = 1;
    }
    else
    {
      if (((struct BTreeNode_trainer *)myNode)->count == 0)
      {
        tmp = myNode;
        myNode = ((struct BTreeNode_trainer *)myNode)->linker[0];
        free(tmp);
      }
    }
    if (!t)
      trainer_root = myNode;
  }
  else
  {
    struct BTreeNode_member *tmp;
    if (!delValFromNode(id, myNode, flag))
    {
      printf("Member %d not found\n", id);
      t = 1;
    }
    else
    {
      if (((struct BTreeNode_member *)myNode)->count == 0)
      {
        tmp = myNode;
        myNode = ((struct BTreeNode_member *)myNode)->linker[0];
        free(tmp);
      }
    }
    if (!t)
      member_root = myNode;
  }
  return;
}

void *searching_tree(int id, int *pos, void *myNode, int flag)
{
  if (flag)
  {
    if (myNode)
    {
      if (id < ((struct BTreeNode_trainer *)myNode)->ptrs[1]->trainer_id)
      {
        *pos = 0;
      }
      else
      {
        for (*pos = ((struct BTreeNode_trainer *)myNode)->count;
             (id<((struct BTreeNode_trainer *)myNode)->ptrs[*pos]->trainer_id && * pos> 1); (*pos)--)
          ;
        if (id == ((struct BTreeNode_trainer *)myNode)->ptrs[*pos]->trainer_id)
        {
          return ((struct BTreeNode_trainer *)myNode)->ptrs[*pos];
        }
      }
    }
    else
      return NULL;
    return searching_tree(id, pos, ((struct BTreeNode_trainer *)myNode)->linker[*pos], flag);
  }
  else
  {
    if (myNode)
    {
      if (id < ((struct BTreeNode_member *)myNode)->ptrs[1]->member_id)
      {
        *pos = 0;
      }
      else
      {
        for (*pos = ((struct BTreeNode_member *)myNode)->count;
             (id<((struct BTreeNode_member *)myNode)->ptrs[*pos]->member_id && * pos> 1); (*pos)--)
          ;
        if (id == ((struct BTreeNode_member *)myNode)->ptrs[*pos]->member_id)
        {
          return ((struct BTreeNode_member *)myNode)->ptrs[*pos];
        }
      }
    }
    else
      return NULL;
    return searching_tree(id, pos, ((struct BTreeNode_member *)myNode)->linker[*pos], flag);
  }
}

// void traversal(void *myNode,int flag) {
//   if(flag)
//   {
//     int i;
//     if (myNode) {
//       for (i = 0; i < ((struct BTreeNode_trainer*)myNode)->count; i++) {
//         traversal(((struct BTreeNode_trainer*)myNode)->linker[i],flag);
//         printf("%d ", ((struct BTreeNode_trainer*)myNode)->ptrs[i + 1]->trainer_id);
//       }
//       traversal(((struct BTreeNode_trainer*)myNode)->linker[i],flag);
//     }
//   }
//   else
//   {
//     int i;
//     if (myNode) {
//       for (i = 0; i < ((struct BTreeNode_member*)myNode)->count; i++) {
//         traversal(((struct BTreeNode_member*)myNode)->linker[i],flag);
//         printf("%d ", ((struct BTreeNode_member*)myNode)->ptrs[i + 1]->member_id);
//       }
//       traversal(((struct BTreeNode_member*)myNode)->linker[i],flag);
//     }
//   }
// }