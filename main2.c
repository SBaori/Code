#include <stdio.h>
#define heap_ptr_size 52
#define header_size 2
#define null -2
int heap_ptr[heap_ptr_size]; //heap
int free_list_start=0;       // start pointer of the free list (points at the start of the memory by default).

// allocated blocks have the head pointer pointing to 0 by default.


// initialize the memory(heap)
void initialize_mem(int ptr,int size,int next_ptr)
{
	for(int i=ptr+header_size;i<ptr+size;i++)
		heap_ptr[i]=-1;
	if(size && next_ptr)
	{
		heap_ptr[ptr]=size;
		heap_ptr[ptr+1]=next_ptr;
	}
}

int update_offsets_alloc(int addr_curr,int addr_prev,int size)
{
    // if we have found a block of exact size
	if(heap_ptr[addr_curr] == size)
	{
        // if this block comes before the start of free list, then update the start free list pointer.
		if(addr_prev==-1)
			free_list_start= heap_ptr[addr_curr+1];
        // otherwise, change the pointer of previous free block to point to next to next free block.
		else
			heap_ptr[addr_prev+1] = heap_ptr[addr_curr+1];
        // mark the block as allocated.
		heap_ptr[addr_curr+1]=0;
	}
	else
	{
		int orig_size = heap_ptr[addr_curr];
		int orig_ptr = heap_ptr[addr_curr+1];

		heap_ptr[addr_curr]=size;
		heap_ptr[addr_curr+1] = 0;

		// change current pointer to the next remaining block.
		addr_curr+=size;

		// update free list pointer if current pointer is equal to it.
		if(free_list_start == (addr_curr-size))
			free_list_start+=size;
		// if current pointer and free list pointer are not equal, then there is a previous address. change it to point to new free block.
		else
			heap_ptr[addr_prev+1] = addr_curr;

		heap_ptr[addr_curr] = orig_size-size;
		heap_ptr[addr_curr+1] = orig_ptr;
		/*if(addr_prev!=-1)
			heap_ptr[addr_prev+1] = addr_curr;*/
		addr_curr-=size;

	}
	return addr_curr;
}

// merge the block if possible and add to the free list.
void merge(int prev_ptr,int next_ptr,int ptr)
{

    /* Here we are first merging the current block to the next free block(or adding to the free list) then we merge(or add) the newly added (or merged)
       block with the previous free block

    */
    // head pointer of current block will need to be pointed to the next free block no matter what.
	heap_ptr[ptr+1] = next_ptr;

    // check if the nearest right free block is adjacent
	if(ptr+heap_ptr[ptr] == next_ptr)
	{
		heap_ptr[ptr] += heap_ptr[next_ptr];
		heap_ptr[ptr+1] = heap_ptr[next_ptr+1];
	}

    // if there is no previous free block, update the free list pointer to point to the current block
	if(prev_ptr == null)
	{
		free_list_start = ptr;
	}
	else
	{
		heap_ptr[prev_ptr+1] = ptr;

		if(prev_ptr + heap_ptr[prev_ptr] == ptr)
		{
			heap_ptr[prev_ptr]+= heap_ptr[ptr];
			heap_ptr[prev_ptr+1] = heap_ptr[ptr+1];
            ptr = prev_ptr;
		}
	}
	initialize_mem(ptr,heap_ptr[ptr],0);
}
void free_mem_alloc(int ptr)
{
    //change the address to point to the start of head.
	ptr-=2;
	int i=free_list_start,temp_ptr=ptr,prev_free_ptr=null,next_free_ptr=null;

    // locate the nearest free blocks of the block to be freed.
	while( i < ptr && i!=null)
	{
		prev_free_ptr = i;
		i = heap_ptr[i+1];
	}
	if( i == ptr )
		printf("Invalid pointer\n");
	next_free_ptr=i;

	merge(prev_free_ptr,next_free_ptr,ptr);

}

int mem_alloc(int size)
{
	// change requested size to include header size
	size+=header_size;

	int i=free_list_start,min_size_alloced=heap_ptr_size+1,addr_min=-3,addr_prev=-1;
	int addr_min_prev=-1;
	if(free_list_start!=null)
	{
        // find the smallest free block to be allocated for the request.
		do
		{
			if(heap_ptr[(i)]>size)
			{
				if(heap_ptr[(i)]<min_size_alloced)
				{
					min_size_alloced = heap_ptr[i];
					addr_min_prev = addr_prev;
					addr_min = i;
				}
			}
			else if(heap_ptr[i] == size)
			{
				min_size_alloced = heap_ptr[i];
				addr_min_prev = addr_prev;
				addr_min=i;
				break;
			}
			addr_prev=i;
			i = heap_ptr[i+1];
		}while(i!=null);
    //if we have found one, update the free list.
    if(addr_min!=-3)
		addr_min = update_offsets_alloc(addr_min,addr_min_prev,size);
	}
	return (addr_min+header_size);
}

void display_heap_layout()
{
	//int start = free_list_start;
	int i=0,j=0;
	do
	{
		if(heap_ptr[i] != -1)
		{
			printf("|%d|",heap_ptr[i]);
            //j=1;
		}
		else
        {
            // printf("(%d)",j);
            // j++;
            printf("-");
        }
		i++;
	}while(i<heap_ptr_size);
	printf("\n");

}
void display_matrix(int adj_matrix[][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
			printf(" %d :(%d,%d)|",adj_matrix[i][j],i,j);
		printf("\n");
	}
}
int main()
{
	int adj_matrix[10][10];
	int root_set[4];
	int sim_struct_size[3] = {2,3,4};
	initialize_mem(free_list_start,heap_ptr_size,null);
     	int alloc[11];
	alloc[5] = mem_alloc(sim_struct_size[0]);
      	alloc[1] = mem_alloc(sim_struct_size[2]);
	heap_ptr[alloc[5]+1] = alloc[1];
       	alloc[2] = mem_alloc(sim_struct_size[0]);
	heap_ptr[alloc[1]+1] = alloc[2];
	heap_ptr[alloc[2]+1] = -3;
      	alloc[7] = mem_alloc(sim_struct_size[1]);
	heap_ptr[alloc[7]+1] = alloc[1];
	alloc[3] = mem_alloc(sim_struct_size[1]);
	alloc[8] = mem_alloc(sim_struct_size[0]);
	heap_ptr[alloc[3]+1] = alloc[8];
	heap_ptr[alloc[7]+2] = alloc[8];
	alloc[9] = mem_alloc(sim_struct_size[0]);
	heap_ptr[alloc[8]+1] = alloc[9];
	alloc[10] = mem_alloc(sim_struct_size[0]);
	heap_ptr[alloc[1]+2] = alloc[9];
	heap_ptr[alloc[1]+3] = alloc[10];
	heap_ptr[alloc[3]+2] = alloc[10];
/*     	free_mem_alloc(c);
      	int e = mem_alloc(1);
       	free_mem_alloc(d);
      	free_mem_alloc(e);
       	free_mem_alloc(b);*/
	display_heap_layout();
return 0;
}
