#define MAX 3
#define MIN 2

struct BTreeNode_trainer {
  int count;
  struct trainer* ptrs[MAX+1];
  struct BTreeNode_trainer *linker[MAX + 1];
};

struct BTreeNode_member
{
  int count;
  struct member* ptrs[MAX+1];
  struct BTreeNode_member* linker[MAX+1];
};

struct trainer
{
	int trainer_id;
	char name[50];
	char programs[4][15];
	int remun[4];
	int tot_remun;
	int available;
};

// Member Data list
struct member
{
	int member_id, age, fees[4];
	char name[50];
	char gender[7];
	char enroll_prog[4][15], booked_prog[15];
	int alot, slot_hr, happy,tot_fees;
};

struct BTreeNode_trainer* trainer_root;
struct BTreeNode_member* member_root;
void *createNode(void* ptr, void *child,int flag);
void addValToNode(void* ptr, int pos, void *node,void *child,int flag);
void splitNode(void* ptr, void** pval, int pos, void *node,void *child, void **newNode,int flag);
int setValueInNode(void* ptr, void** pval,void *node, void **child,int flag);
void insertion(void* ptr,int flag);
void copySuccessor(void *myNode, int pos,int flag);
void removeVal(void *myNode, int pos,int flag);
void rightShift(void *myNode, int pos,int flag);
void leftShift(void *myNode, int pos,int flag);
void mergeNodes(void *myNode, int pos,int flag);
void adjustNode(void *myNode, int pos,int flag);
int delValFromNode(int id, void *myNode,int flag);
void deletenode(int id, void *myNode,int flag);
void* searching_tree(int id, int *pos, void *myNode,int flag);
void traversal(void *myNode,int flag);
