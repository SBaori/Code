#include <stdio.h>
#include <stdlib.h>
#define heap_ptr_size 500
//#define header_size 2
#define null -2
char heap_ptr[heap_ptr_size]; // heap
							  //  start pointer of the free list (points at the start of the memory by default).

// allocated blocks have the head pointer pointing to 0 by default.

struct header
{
	short int size;
	void *h_ptr;
	char ref_count;
	char alloc;
	struct header *next;
	struct header *next_free;
};

struct allocs
{
	char tag;
	char* ptr[3];
};
int header_size = sizeof(struct header);
struct header *free_list_start;
struct header *first_head;

// initialize the memory(heap)
void initialize_mem(int size, int next_ptr, struct header *head)
{
	if (size && next_ptr)
	{
		head->size = size;
		head->ref_count = 0;
		head->next = NULL;
		head->next_free = NULL;
		head->h_ptr = heap_ptr;
		head->alloc = 0;
	}
}

struct header *update_offsets_alloc(struct header *addr_curr, struct header *addr_prev, short int size, struct header *head_prev)
{
	struct header *alloced;
	// if we have found a block of exact size
	if (addr_curr->size == size)
	{
		// if this block comes before the start of free list, then update the start free list pointer.
		if (addr_prev == NULL)
			free_list_start = addr_curr->next_free;
		// otherwise, change the pointer of previous free block to point to next to next free block.
		else
			addr_prev->next_free = addr_curr->next_free;
		// mark the block as allocated.
		addr_curr->alloc = 1;
		addr_curr->next_free = NULL;
		alloced = addr_curr;
	}
	else
	{
		alloced = malloc(sizeof(struct header));
		alloced->size = size;
		alloced->h_ptr = addr_curr->h_ptr;
		// head_prev->next=alloced;
		alloced->next = addr_curr;

		addr_curr->size = addr_curr->size - size;
		addr_curr->h_ptr = addr_curr->h_ptr + alloced->size;
		if (head_prev == NULL)
			first_head = alloced;
		else
			head_prev->next = alloced;
		alloced->alloc = 1;
		alloced->next_free = NULL;
	}
	return alloced;
}

// merge the block if possible and add to the free list.
void merge(struct header *prev_ptr, struct header *next_ptr, struct header *target_block)
{

	/* Here we are first merging the current block to the next free block(or adding to the free list) then we merge(or add) the newly added (or merged)
	   block with the previous free block

	*/
	// head pointer of current block will need to be pointed to the next free block no matter what.
	target_block->next_free = next_ptr;
	target_block->alloc = 0;
	// heap_ptr[ptr+1] = next_ptr;

	// check if the nearest right free block is adjacent
	if (target_block->next == next_ptr)
	{
		target_block->size += next_ptr->size;
		struct header *temp = target_block->next;
		target_block->next = target_block->next->next;
		target_block->next_free = next_ptr->next_free;
		free(temp);
		// heap_ptr[ptr] += heap_ptr[next_ptr];
		// heap_ptr[ptr+1] = heap_ptr[next_ptr+1];
	}

	// if there is no previous free block, update the free list pointer to point to the current block
	if (prev_ptr == NULL)
	{
		free_list_start = target_block;
	}
	else
	{
		prev_ptr->next_free = target_block;

		if (prev_ptr->next == target_block)
		{
			prev_ptr->size += target_block->size;
			struct header *temp = prev_ptr->next;
			prev_ptr->next = prev_ptr->next->next;
			prev_ptr->next_free = target_block->next_free;
			free(temp);
		}
	}
}
void free_mem_alloc(void *ptr)
{
	// change the address to point to the start of head.
	ptr -= header_size;
	struct header *i = free_list_start, *prev_free_ptr = NULL, *next_free_ptr = NULL, *temp = first_head;
	void *temp_ptr = ptr;
	// locate the nearest free blocks of the block to be freed.
	while (i->h_ptr < ptr)
	{
		prev_free_ptr = i;
		i = i->next_free;
	}
	if (i == ptr)
		printf("Invalid pointer\n");
	else
	{
		next_free_ptr = i;
		while (temp != NULL && temp->h_ptr != ptr)
		{
			temp = temp->next;
		}
		merge(prev_free_ptr, next_free_ptr, temp);
	}
}

void *mem_alloc(short int size)
{
	// change requested size to include header size
	size += header_size;
	struct header *i = free_list_start, *addr_min = NULL, *addr_min_prev = NULL, *addr_prev = NULL;
	struct header *temp = first_head;
	short int min_size_alloced = heap_ptr_size + 1;
	if (free_list_start != NULL)
	{
		// find the smallest free block to be allocated for the request.
		do
		{
			if (i->size > size)
			{
				if (i->size < min_size_alloced)
				{
					min_size_alloced = i->size;
					addr_min_prev = addr_prev;
					addr_min = i;
				}
			}
			else if (i->size == size)
			{
				min_size_alloced = i->size;
				addr_min_prev = addr_prev;
				addr_min = i;
				break;
			}
			addr_prev = i;
			i = i->next_free;
		} while (i != NULL);
		// if we have found one, update the free list.
		if (addr_min != NULL)
		{
			if (temp->next == NULL)
				temp = NULL;
			else
			{
				while (temp != NULL && temp->next != addr_min)
					temp = temp->next;
			}
			addr_min = update_offsets_alloc(addr_min, addr_min_prev, size, temp);
		}
	}
	void *addr = addr_min->h_ptr;
	return (addr + header_size);
}

void populate_matrix(int adj_matrix[][11],char *root,struct allocs chunks[])
{
	char i=*root;
	int k=0;
	while(chunks[i].ptr[k]!=NULL)
	{
		adj_matrix[i][*(chunks[i].ptr[k])] = 1;
		display_matrix(adj_matrix,chunks[i].ptr[k],chunks);
		k++;
	}

}

int main()
{
	int adj_matrix[11][11];
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
			adj_matrix[i][j] = 0;
	}
	// int root_set[4];
	// int sim_struct_size[3] = {2,3,4};
	// struct header* free_start = malloc(sizeof(struct header));
	free_list_start = malloc(sizeof(struct header));
	first_head = malloc(sizeof(struct header));
	initialize_mem(heap_ptr_size, null, free_list_start);
	first_head->h_ptr = heap_ptr;
	first_head->next = NULL;
	first_head->size = free_list_start->size;
	struct allocs chunks[10];

	for(int i=0;i<10;i++)
	{
		//chunks[i].tag=0;
		chunks[i].ptr[0]=NULL;
		chunks[i].ptr[1]=NULL;
		chunks[i].ptr[3]=NULL;
	}
	char *root1 = mem_alloc(sizeof(struct allocs));
	char *root2 = mem_alloc(sizeof(struct allocs));
	*root1 = 5;
	*root2 = 1;
	char *two = mem_alloc(sizeof(struct allocs));
	*two = 2;
	
	
	char *nine = mem_alloc(sizeof(struct allocs));
	*nine = 9;
	

	char* ten = mem_alloc(sizeof(struct allocs));
	*ten = 10;
	

	char *eight = mem_alloc(sizeof(struct allocs));
	*eight = 8;
	

	char *seven = mem_alloc(sizeof(struct allocs));
	*seven = 7;

	char *three = mem_alloc(sizeof(struct allocs));
	*three = 3;
	
	chunks[5].ptr[0] = root2;
	chunks[1].ptr[0] = two;
	chunks[1].ptr[1] = nine;
	chunks[1].ptr[2] = ten;
	
	chunks[8].ptr[0] = nine;
	
	chunks[7].ptr[0] = root2;
	chunks[7].ptr[1] = eight;

	chunks[3].ptr[0] = eight;
	chunks[3].ptr[1] = ten;
	two = nine = eight = seven = three = ten = NULL;

	populate_matrix(adj_matrix,root2,chunks);
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			printf("%d,(%d,%d) |",adj_matrix[i][j],i,j);
		}
		printf("\n");
	}
	// printf("%d",adj_matrix[5][1]);
	//gc_collect();
	// struct header *temp_head = first_head;
	// while (temp_head != NULL)
	// {
	// 	printf("size: %d\nptr: %d\nheap: %d\nalloc: %d\n\n", temp_head->size, temp_head->h_ptr, heap_ptr, temp_head->alloc);
	// 	temp_head = temp_head->next;
	// }
	// printf("%d", free_list_start->h_ptr);
	
	return 0;
}
