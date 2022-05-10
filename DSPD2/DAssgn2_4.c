#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "btree.h"


struct allots
{
	struct member *m_ptr;
	struct allots *next;
};

struct time
{
	int tot_persons;
	struct allots *allot_node;
	struct time *next;
};

struct available_trainer_ptr
{
	struct trainer *ptr;
	struct available_trainer_ptr *next;
};

struct member_allot_request
{
	struct member *m_ptr;
	int timestamp, slot_hr, trainer_id;
	char request_prog[15];
	struct member_allot_request *next;
};
char avail_progs[4][15] = {"Yoga","Zumba","Cardio","Weight Lifting"};
struct time *initialize_time(int first_hour_start, int last_hour_start)
{
	struct time *head = NULL, *t, *tail;
	struct available_trainer_ptr *temp;
	struct allots *t_allots, *tail_allots;
	while (first_hour_start <= last_hour_start)
	{
		t = malloc(sizeof(struct time));
		t->next = NULL;
		t->allot_node = NULL;

		// temp = available_head;
		// while ((temp != NULL))
		// {
		// 	t_allots = malloc(sizeof(struct allots));
		// 	t_allots->m_ptr = NULL;
		// 	if (t->allot_node == NULL)
		// 	{
		// 		t->allot_node = t_allots;
		// 	}
		// 	else
		// 	{
		// 		tail_allots->next = t_allots;
		// 	}

		// 	tail_allots = t_allots;
		// 	temp = temp->next;
		// }
		t->tot_persons = 0;
		if (head == NULL)
		{

			head = t;
		}
		else
		{
			tail->next = t;
		}
		tail = t;
		first_hour_start++;
	}
	return head;
}

void add_trainer_slots(struct time* time_head,struct available_trainer_ptr* available_head)
{
	struct allots* allot_node,*allot_node_tail,*t;
	struct available_trainer_ptr* temp;
	while(time_head!=NULL)
	{
		allot_node=time_head->allot_node;
		temp = available_head;
		while(temp!=NULL)
		{
			if(time_head->allot_node==NULL)
			{
				t = malloc(sizeof(struct allots));
				t->m_ptr=NULL;
				t->next=NULL;
				time_head->allot_node=t;
				allot_node=t;
			}
			else
			{
				if((allot_node->next==NULL) && (temp->next!=NULL))
				{
					t = malloc(sizeof(struct allots));
					t->m_ptr=NULL;
					t->next=NULL;
					allot_node->next=t;
				}
				allot_node=allot_node->next;
				temp=temp->next;
			}
			

		}
		time_head=time_head->next;
	}
}
void print_trainer_data(struct trainer *ptr)
{
	printf("Name: %s\nTrainer Id: %d\n", ptr->name, ptr->trainer_id);
	int i = 0;
	while (i < 4 && ptr->programs[i][0] != '\0')
	{
		printf("Program %d: ", i + 1);
		fputs(ptr->programs[i], stdout);
		printf(", Remuneration: %d\n", ptr->remun[i]);

		i++;
	}
	printf("Total remuneration earned today: %d\n\n", ptr->tot_remun);
}

void print_member_data(struct member *ptr)
{
	printf("Name: %s\nmember Id: %d\n", ptr->name, ptr->member_id);
	int i = 0;
	while (i < 4 && ptr->enroll_prog[i][0] != '\0')
	{
		printf("Enrolled Program %d: ", i + 1);
		fputs(ptr->enroll_prog[i], stdout);
		printf(", Fees paid: %d\n", ptr->fees[i]);
		i++;
	}
	printf("\n");
}


int match_trainer_member_progs(char progs[], struct available_trainer_ptr *trainer)
{
	int i = 0, res = 1;
	while ((i < 4) && (trainer->ptr->programs[i][0] != '\0') && strcasecmp(trainer->ptr->programs[i], progs))
		i++;
	if ((i == 4) || (trainer->ptr->programs[i][0] == '\0'))
		i = -1;
	return i;
}
void Add_trainer(struct available_trainer_ptr** avail_t_head,struct time* time_head)
{
	char name[50] = {0};
	int name_comp, flag = 1;
	// struct trainer *input_head = NULL, *input_tail;
	char programs[4][15] = {0};
	int remn[4];
	 struct available_trainer_ptr *train_tail_ptr = NULL, *temp_ptr = (*avail_t_head), *t_ptr;

	while (flag)
	{
		printf("\n-----Enter trainer details! (enter x when done)-----\n");
		printf("Enter Trainer name!:\n");
		flag = 0;
		int i = 0;
		fgets(name,sizeof(name),stdin);
		name_comp = strcmp(name, "x\n");

		if (name_comp)
		{
			//char prog_inp[15] = {0};
			printf("\n---Enter list of activities of the trainer! (enter 0 when done!)---\n");
			int inp=1;

			for (int i = 0; i < 4; i++)
			{
				programs[i][0] = '\0';
				remn[i] = 0;
			}

			while (inp && (i < 4))
			{
				printf("1. Yoga\n2. Zumba\n3. Cardio\n4. Weight Lifting\nEnter key: ");
				scanf("%d",&inp);
				getchar();
				//comp = strcmp(prog_inp, "x");
				if (inp)
				{
					printf("Enter remuneration!:\n");
					strcpy(programs[i], avail_progs[inp-1]);
					scanf("%d", &remn[i]);
					getchar();
					i++;
				}
			}
			if (i == 0)
				printf("\nActivities cannot be emtpy!\n\n");
			else
			{
				int available;
				printf("---Enter key for availability for the day---\n1. Available\n0. Not Available\n");
				scanf("%d", &available);
				getchar();
				struct trainer *t = malloc(sizeof(struct trainer));
				strcpy(t->name, name);
				i = 0;
				while ((i < 4))
				{
					strcpy(t->programs[i], programs[i]);
					t->remun[i] = remn[i];
					i++;
				}
				srand(time(0));
				t->trainer_id = 1000 + ((rand()) % (9999 - 1000 + 1));
				if (available)
				{
					t_ptr = malloc(sizeof(struct available_trainer_ptr));
					t_ptr->ptr = t;
					t_ptr->next = NULL;
					if (train_tail_ptr == NULL)
					{
						if ((*avail_t_head) == NULL)
						{
							(*avail_t_head) = t_ptr;
							train_tail_ptr = (*avail_t_head);
							temp_ptr = (*avail_t_head);
						}
						else
						{
							while (temp_ptr->next != NULL)
								temp_ptr = temp_ptr->next;
							train_tail_ptr = temp_ptr;
							train_tail_ptr->next = t_ptr;
						}
					}
					else
					{
						train_tail_ptr->next = t_ptr;
						train_tail_ptr=train_tail_ptr->next;
					}
					add_trainer_slots(time_head,(*avail_t_head));
				}
				t->available = available;
				t->tot_remun = 0;
				print_trainer_data(t);
				insertion(t, 1);
				// Print_trainer_list(t);
			}
			flag = 1;
		}
	}
	printf("---------------Trainers added successfully!----------\n\n");
}
void Add_member()
{
	char name[50];

	int flag = 1;
	// struct member *inp_head = NULL, *tail;

	while (flag)
	{
		printf("--------Enter Member details! (enter x when done)--------\n");
		flag = 0;
		printf("Enter Member Name: \n");
		fgets(name,sizeof(name),stdin);
		int comp = strcmp(name, "x\n");
		if (comp)
		{
			char enroll_progs[4][15];
			
			int fees[4];
			for (int i = 0; i < 4; i++)
			{
				enroll_progs[i][0] = '\0';
				fees[i] = 0;
			}

			printf("Enter age: ");
			int age;
			scanf("%d", &age);
			getchar();
			printf("Enter gender: ");
			char gender[7];
			fgets(gender,sizeof(gender),stdin);

			printf("\n\n------Enter Programs to enroll! (enter 0 when done)-----\n");
			int enroll_inp=1;
			int i = 0;
			//int comp = strcmp(enroll_inp, "x");
			while (enroll_inp && (i < 4))
			{
				printf("---Enter key for program!---\n1. Yoga\n2. Zumba\n3. Cardio\n4. Weight Lifting\nEnter Key: ");
				scanf("%d",&enroll_inp);
				getchar();
				//gets(enroll_inp);
				//comp = strcmp(enroll_inp, "x");
				if (enroll_inp)
				{
					strcpy(enroll_progs[i], avail_progs[enroll_inp-1]);
					printf("Enter Fees\n");
					scanf("%d", &fees[i]);
					getchar();
					i++;
				}
			}
			struct member *m = malloc(sizeof(struct member));
			strcpy(m->name, name);
			m->alot = 0;
			m->age = age;
			strcpy(m->gender, gender);
			i = 0;

			while ((i < 4))
			{
				strcpy(m->enroll_prog[i], enroll_progs[i]);
				m->fees[i] = fees[i];
				i++;
			}
			srand(time(0));
			m->member_id = 1000 + ((rand()) % (9999 - 1000 + 1));
			// m->next = NULL;
			// Print_member_list(m);
			//  if (inp_head == NULL)
			//  {
			//  	inp_head = m;
			//  }
			//  else
			//  {
			//  	tail->next = m;
			//  }
			//  tail = m;
			print_member_data(m);
			insertion(m, 0);
			flag = 1;
		}
	}
	printf("---------------Members added successfully!----------\n\n");
}

void remove_trainer_slots(struct trainer *trainr, struct available_trainer_ptr **available_head, struct time *time_head)
{
	struct available_trainer_ptr *available_temp = *(available_head);

	int node_no = 0, node_no_itr;
	if (available_temp->ptr == trainr)
	{
		struct available_trainer_ptr *next_node_ptr = ((*available_head)->next);
		free(*(available_head));
		*available_head = next_node_ptr;
		while (time_head != NULL)
		{
			struct allots *allot_node_next = time_head->allot_node->next;
			if (time_head->allot_node->m_ptr != NULL)
			{
				time_head->allot_node->m_ptr->alot = 0;
				time_head->tot_persons--;
			}
			free(time_head->allot_node);
			time_head->allot_node = allot_node_next;
			time_head = time_head->next;
		}
	}
	else
	{
		struct allots *allot_node;
		while (time_head != NULL)
		{
			available_temp = *available_head;
			allot_node = time_head->allot_node;
			while (available_temp->next != NULL && available_temp->next->ptr != trainr)
			{
				available_temp = available_temp->next;
				allot_node = allot_node->next;
			}
			struct allots *allot_node_next = allot_node->next;
			allot_node->next = allot_node_next->next;
			if (allot_node_next->m_ptr != NULL)
			{
				allot_node_next->m_ptr->alot = 0;
				time_head->tot_persons--;
			}
			free(allot_node_next);
			time_head = time_head->next;
		}
		struct available_trainer_ptr *next_node_ptr = available_temp->next;
		available_temp->next = next_node_ptr->next;
		free(next_node_ptr);
	}
}
void delete_trainer(struct time* time_head,struct available_trainer_ptr** available_head)
{
	int trainer_id = 1;
	// struct trainer *ahead, *temp = head;
	while (trainer_id)
	{
		printf("Enter trainer ID to remove (enter 0 when done)\n");
		printf("Enter trainer ID: \n");
		scanf("%d", &trainer_id);
		getchar();
		if (trainer_id)
		{
			int i;
			struct trainer* temp = searching_tree(trainer_id,&i,trainer_root,1);
			if(temp)
			{
				if(temp->available==1)
					remove_trainer_slots(temp,available_head,time_head);
				deletenode(trainer_id, trainer_root, 1);
			}
			
		}
	}
	printf("---------All trainers deleted successfully!--------\n");
}

void remove_member_bookings(struct member *member, struct time *time_head, struct available_trainer_ptr *available_head)
{
	int hr = member->slot_hr;
	int start_hour = 6;
	while (start_hour < hr)
	{
		start_hour++;
		time_head = time_head->next;
	}
	struct allots *allot = time_head->allot_node;
	int done = 0;
	while (allot != NULL && !done)
	{
		if (allot->m_ptr == member)
		{
			time_head->tot_persons--;
			available_head->ptr->tot_remun -= available_head->ptr->remun[match_trainer_member_progs(allot->m_ptr->booked_prog, available_head)];
			allot->m_ptr = NULL;
			done = 1;
		}
		available_head = available_head->next;
		allot = allot->next;
	}
}
void delete_member(struct time* time_head,struct available_trainer_ptr* available_head)
{
	int member_id = 1;
	// struct member *ahead, *temp = head;
	while (member_id)
	{
		printf("\n-------Enter member ID to remove (enter 0 when done)--------\n");
		printf("Enter member ID: \n");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			int i;
			struct member* temp = searching_tree(member_id,&i,member_root,0);
			if(temp)
			{
				if(temp->alot==1)
					remove_member_bookings(temp, time_head, available_head);
				deletenode(member_id,member_root,0);
			}
			else
				printf("--------Member not found!-------\n");
		}
	}
	printf("-------All Members deleted successfully!-------\n");
}

void Print_trainer_list(struct BTreeNode_trainer *myNode)
{
	int i;
	if (myNode)
	{
		for (i = 0; i < (myNode)->count; i++)
		{
			Print_trainer_list((myNode)->linker[i]);
			print_trainer_data(myNode->ptrs[i + 1]);
		}
		Print_trainer_list((myNode)->linker[i]);
	}
}

void Print_member_list(struct BTreeNode_member *myNode)
{
	int i;
	if (myNode)
	{
		for (i = 0; i < (myNode)->count; i++)
		{
			Print_member_list((myNode)->linker[i]);
			print_member_data(myNode->ptrs[i + 1]);
		}
		Print_member_list((myNode)->linker[i]);
	}
}

void search_trainer_helper(int id, char char_field[], struct BTreeNode_trainer *r_trainer, int flag)
{
	if (flag == 1)
	{
		if (r_trainer)
		{
			for (int j = 1; j <= r_trainer->count; j++)
			{
				if (!strcasecmp(char_field, r_trainer->ptrs[j]->name))
					print_trainer_data(r_trainer->ptrs[j]);
			}
			for (int i = 0; i <= r_trainer->count; i++)
				search_trainer_helper(id,char_field, r_trainer->linker[i], flag);
		}
	}
	else
	{
		if (r_trainer)
		{
			for (int j = 1; j <= r_trainer->count; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (!strcasecmp(char_field, r_trainer->ptrs[j]->programs[k]))
					{
						print_trainer_data(r_trainer->ptrs[j]);
						k=4;
					}
						
				}
			}
			for (int i = 0; i <= r_trainer->count; i++)
				search_trainer_helper(id,char_field, r_trainer->linker[i], flag);
		}
	}
}
void search_trainer()
{
	printf("---------------Enter number to search the field---------------\n");
	int num = 4;
	// struct trainer *temp = head;

	while (num)
	{
		printf("1: Name\n2: Trainer Id\n3: Programs\n0: To exit searching\n");
		scanf("%d", &num);
		getchar();
		if (num == 1)
		{
			char name[50];
			printf("Enter name: \n");
			fgets(name,sizeof(name),stdin);
			search_trainer_helper(0,name,trainer_root,num);
		}
		else if (num == 2)
		{
			int t_id;
			printf("Enter trainer ID:\n");
			scanf("%d", &t_id);
			getchar();
			int i;
			struct trainer* res = searching_tree(t_id,&i,trainer_root,1);
			if(res!=NULL)
				print_trainer_data(res);
		}
		else if (num == 3)
		{
			char program[15];
			printf("Enter program:\n");
			fgets(program,sizeof(program),stdin);
			search_trainer_helper(0,program,trainer_root,num);
		}
	}
}
void search_member_helper(int id,char char_field[],struct BTreeNode_member* r_member,int flag)
{
	if(flag==1)
	{
		if (r_member)
		{
			for (int j = 1; j <= r_member->count; j++)
			{
				if (!strcasecmp(char_field, r_member->ptrs[j]->name))
					print_member_data(r_member->ptrs[j]);
			}
			for (int i = 0; i <= r_member->count; i++)
				search_member_helper(id,char_field, r_member->linker[i], flag);
		}
	}
	else if(flag==3)
	{
		if (r_member)
		{
			for (int j = 1; j <= r_member->count; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (!strcasecmp(char_field, r_member->ptrs[j]->enroll_prog[k]))
						print_member_data(r_member->ptrs[j]);
				}
			}
			for (int i = 0; i <= r_member->count; i++)
				search_member_helper(id,char_field, r_member->linker[i], flag);
		}
	}
	else if(flag==4)
	{
		if (r_member)
		{
			for (int j = 1; j <= r_member->count; j++)
			{
				if (!strcasecmp(char_field, r_member->ptrs[j]->gender))
					print_member_data(r_member->ptrs[j]);
			}
			for (int i = 0; i <= r_member->count; i++)
				search_member_helper(id,char_field, r_member->linker[i], flag);
		}
	}
	else if(flag==5)
	{
		if (r_member)
		{
			for (int j = 1; j <= r_member->count; j++)
			{
				if (id == r_member->ptrs[j]->age)
					print_member_data(r_member->ptrs[j]);
			}
			for (int i = 0; i <= r_member->count; i++)
				search_member_helper(id,char_field, r_member->linker[i], flag);
		}
	}
	else if(flag==6)
	{
		if (r_member)
		{
			for (int j = 1; j <= r_member->count; j++)
			{
				if (id == r_member->ptrs[j]->tot_fees)
					print_member_data(r_member->ptrs[j]);
			}
			for (int i = 0; i <= r_member->count; i++)
				search_member_helper(id,char_field, r_member->linker[i], flag);
		}
	}
}
void search_member()
{
	printf("---------------Enter number to search the field---------------\n");
	int num = 1;
	//struct member *temp = head;
	while (num)
	{
		printf("1: Name\n2: Member Id\n3: Program Enrolled(searches for a single program input)\n4: Gender\n5: Age\n6: Total Fees paid\n0: To exit searching\n");
		scanf("%d", &num);
		getchar();
		if (num == 1)
		{
			char name[50];
			printf("Enter name: \n");
			fgets(name,sizeof(name),stdin);
			search_member_helper(0,name,member_root,num);
		}
		else if (num == 2)
		{
			int m_id;
			printf("Enter member ID:\n");
			scanf("%d", &m_id);
			getchar();
			int i;
			struct member* res =searching_tree(m_id,&i,member_root,0);
			if(res!=NULL)
				print_member_data(res);
		}
		else if (num == 3)
		{
			char program[15];
			printf("Enter program:\n");
			fgets(program,sizeof(program),stdin);
			search_member_helper(0,program,member_root,num);
		}
		else if (num == 4)
		{
			printf("Enter gender!\n");
			char gender[7];
			fgets(gender,sizeof(gender),stdin);
			search_member_helper(0,gender,member_root,num);
		}
		else if (num == 5)
		{
			printf("Enter Age:\n");
			int age;
			scanf("%d", &age);
			getchar();
			search_member_helper(age,'\0',member_root,num);
		}
		else if (num == 6)
		{
			printf("Enter total fees paid\n");
			int tot_fees;
			scanf("%d", &tot_fees);
			search_member_helper(tot_fees,'\0',member_root,num);
		}
	}
}
void range_search(int low,int high,struct BTreeNode_member* m_root)
{
	if (m_root)
	{
		for (int j = 1; j <= m_root->count; j++)
		{
			if (m_root->ptrs[j]->member_id<=high && m_root->ptrs[j]->member_id>=low)
				print_member_data(m_root->ptrs[j]);
		}
		for (int i = 0; i <= m_root->count; i++)
			range_search(low,high,m_root->linker[i]);
	}
}
struct member_allot_request* sortedMerge(struct member_allot_request* a,struct member_allot_request* b)
{
	struct member_allot_request* res;
	struct member_allot_request *m_a = a, *m_b = b;
	if ((m_a == NULL))
		res = m_b;
	else if (m_b == NULL)
		res = m_a;
	else
	{
		struct member_allot_request *result = NULL;

		// pick either `a` or `b`, and recur
		if (m_a->timestamp <= m_b->timestamp)
		{
			result = m_a;
			result->next = (struct member_allot_request *)sortedMerge((m_a->next), m_b);
		}
		else
		{
			result = m_b;
			result->next = (struct member_allot_request *)sortedMerge(m_a, (m_b->next));
		}
	}
	return res;
}
struct member_allot_request* middle(struct member_allot_request* head)
{
	struct member_allot_request *slow = head, *fast = head->next,*allot_m_new_list=NULL;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	allot_m_new_list = slow->next;
	slow->next = NULL;
	return allot_m_new_list;
}
struct member_allot_request* mergesort(struct member_allot_request* head)
{
	struct member_allot_request *request_m_head = head;
	if (request_m_head != NULL && request_m_head->next != NULL)
	{
		struct member_allot_request *back1 = NULL;

		back1 = middle(request_m_head);
		head = mergesort(request_m_head);

		back1 = mergesort(back1);

		head = sortedMerge(head, back1);
	}
	return head;
}

void schedule_slot(struct time *h_head, struct available_trainer_ptr *available_head)
{
	int member_id = 1;
	struct member *member_temp;
	struct member_allot_request *allot_head = NULL, *t, *allot_tail;
	while (member_id)
	{
		//member_temp = m_head;
		printf("\nEnter member ID: (enter 0 to start booking)\n");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			int i;
			member_temp = searching_tree(member_id,&i,member_root,0);
			if (member_temp == NULL)
				printf("Member not found!\n");
			else if (member_temp->alot == 1)
				printf("Already alloted today!\n");
			else
			{
				t = malloc(sizeof(struct member_allot_request));
				t->next = NULL;
				t->m_ptr=member_temp;
				int tp;
				printf("Enter timestamp (Any number!)");
				scanf("%d", &tp);
				getchar();
				t->timestamp = tp;
				int t_id;
				printf("\n-----List of available trainer!----\n");
				struct available_trainer_ptr *itr = available_head;
				while (itr != NULL)
				{
					printf("Trainer ID: %d\n", itr->ptr->trainer_id);
					printf("Name: ");
					fputs(itr->ptr->name, stdout);
					printf("\n");
					int i = 0;
					while ((i < 4) && itr->ptr->programs[i][0] != '\0')
					{
						printf("Program %d: ", i + 1);
						fputs(itr->ptr->programs[i], stdout);
						printf("\n");
						i++;
					}
					itr = itr->next;
					printf("\n");
				}
				printf("Enter trainer ID: ");
				scanf("%d", &t_id);
				getchar();
				t->trainer_id = t_id;
				
				printf("Programs enrolled by member ");
				fputs(member_temp->name, stdout);
				printf("\n");
				printf("\n");
				int i = 0;
				while ((i < 4) && (member_temp->enroll_prog[i][0] != '\0'))
				{
					printf("%d - ", i + 1);
					fputs(member_temp->enroll_prog[i], stdout);
					printf("\n");
					i++;
				}
				char progs[15];
				printf("Enter program to book slot!(only 1 accepted)\n");
				fgets(progs,sizeof(progs),stdin);
				i = 0;
				while ((i < 4) && (member_temp->enroll_prog[i][0] != '\0') && (strcasecmp(member_temp->enroll_prog[i], progs)))
					i++;
				if ((i == 4) || (member_temp->enroll_prog[i][0] == '\0'))
				{
					printf("Program not enrolled in by the member, slot booking failed!\n\n");
				}
				else
				{
					strcpy(t->request_prog, progs);
					int slot_hour = 0;
					
					while (slot_hour > 20 || slot_hour < 6)
					{
						printf("Enter start of preffered 1 hr slot:\n------(if preffered slot is 6:00 to 7:00, then enter 6; Time taken in 24hr format)------\n");
						scanf("%d", &slot_hour);
						getchar();
						if ((slot_hour > 20) || (slot_hour < 6))
							printf("Enter time slot between 6:00 and 21:00!\n\n");
					}
					t->slot_hr = slot_hour;
					if (allot_head == NULL)
					{
						allot_head = t;
					}
					else
					{
						allot_tail->next = t;
					}
					allot_tail = t;
				}
			}
		}
	}
	allot_head = mergesort(allot_head);
	struct member_allot_request* itr = allot_head;
	while (allot_head != NULL)
	{
		int start_hour = 6;
		struct time *time_temp = h_head;

		while (start_hour < allot_head->slot_hr)
		{
			time_temp = time_temp->next;

			start_hour++;
		}
		struct available_trainer_ptr *trainer_temp = available_head, *other_matching_trainer = NULL, *found_trainer = NULL;
		struct allots *allot_time_temp = time_temp->allot_node, *other_matching_allot, *found_trainer_allot;
		if (time_temp->tot_persons == 10)
			printf("Total members exceeding the limit given in covid guidline! Choose different time slot\n\n");
		else
		{
			while ((trainer_temp != NULL))
			{

				if (match_trainer_member_progs(allot_head->request_prog, trainer_temp) != -1)
				{
					if (trainer_temp->ptr->trainer_id == allot_head->trainer_id)
					{
						found_trainer = trainer_temp;
						found_trainer_allot = allot_time_temp;
						// f=0;
					}
					else if (allot_time_temp->m_ptr == NULL)
					{
						other_matching_trainer = trainer_temp;
						other_matching_allot = allot_time_temp;
					}
				}
				// printf("exec\n");
				trainer_temp = trainer_temp->next;
				allot_time_temp = allot_time_temp->next;
			}
			if (found_trainer == NULL)
			{
				printf("Trainer does not exist or does not specialise in the entered program! \nSlot booking failed for member ");
				fputs(allot_head->m_ptr->name, stdout);
				printf("\n\n");
			}

			else
			{
				int found = 1, found_other = 0;
				if (found_trainer_allot->m_ptr != NULL)
				{
					printf("Trainer not free, Checking for other trainers in the same slot\n");
					if (other_matching_trainer != NULL)
					{
						printf("Alloting to other free trainers in the same time slot for the entered program!\n");
						other_matching_allot->m_ptr = allot_head->m_ptr;
						time_temp->tot_persons++;
						printf("Slot booked for the member ");
						fputs(allot_head->m_ptr->name, stdout);
						printf(" from %d:00-%d:00 with trainer ", start_hour, start_hour + 1);
						fputs(other_matching_trainer->ptr->name, stdout);
						printf("\n\n");
						other_matching_trainer->ptr->tot_remun += other_matching_trainer->ptr->remun[match_trainer_member_progs(allot_head->request_prog, other_matching_trainer)];
						found_other=1;
						allot_head->m_ptr->alot = 1;
						allot_head->m_ptr->slot_hr = start_hour;
						allot_head->m_ptr->happy = 0;
						strcpy(allot_head->m_ptr->booked_prog, allot_head->request_prog);

					}
					else
					{
						printf("No trainers free for the entered program in the given slot, checking for slots ahead of given time!\n");
						time_temp = time_temp->next;
						
						found = 0;
						while (!(found || found_other) && (time_temp != NULL))
						{
							start_hour++;
							allot_time_temp = time_temp->allot_node;
							other_matching_trainer = NULL;
							trainer_temp = available_head;
							found_trainer = NULL;
							while ((trainer_temp != NULL) && (!found))
							{
								if (match_trainer_member_progs(allot_head->request_prog, trainer_temp) != -1)
								{
									if (trainer_temp->ptr->trainer_id == allot_head->trainer_id && allot_time_temp->m_ptr == NULL)
									{
										found_trainer = trainer_temp;
										found_trainer_allot = allot_time_temp;
										found = 1;
									}
									else if (allot_time_temp->m_ptr == NULL)
									{
										other_matching_trainer = trainer_temp;
										other_matching_allot = allot_time_temp;
									}
								}
								trainer_temp = trainer_temp->next;
								allot_time_temp = allot_time_temp->next;
							}
							if ((!found) && other_matching_trainer != NULL)
							{
								other_matching_allot->m_ptr = allot_head->m_ptr;
								time_temp->tot_persons++;
								
								printf("Slot booked for the member ");
								fputs(allot_head->m_ptr->name, stdout);
								printf(" from %d:00-%d:00 with trainer ", start_hour, start_hour + 1);
								fputs(other_matching_trainer->ptr->name, stdout);
								printf("\n\n");
								allot_head->m_ptr->alot = 1;
								other_matching_trainer->ptr->tot_remun += other_matching_trainer->ptr->remun[match_trainer_member_progs(allot_head->request_prog, other_matching_trainer)];
								
								found_other = 1;
								allot_head->m_ptr->slot_hr = start_hour;
								allot_head->m_ptr->happy = 0;
								strcpy(allot_head->m_ptr->booked_prog, allot_head->request_prog);

							}
							else
								time_temp = time_temp->next;
						}
						if (time_temp == NULL)
						{
							printf("No slots available today!\n Slot booked for the same preffered time for the next working day!\nMember ");
							fputs(allot_head->m_ptr->name, stdout);
							printf(" can book for any other enrolled program today given the slots are free!\n\n");

						}
						//}
					}
				}
				if (found && !found_other)
				{

					found_trainer_allot->m_ptr = allot_head->m_ptr;
					time_temp->tot_persons++;
					printf("Slot booked for the member ");
					fputs(allot_head->m_ptr->name, stdout);
					printf(" from %d:00-%d:00 with trainer ", start_hour, start_hour + 1);
					fputs(found_trainer->ptr->name, stdout);
					printf("\n\n");
					found_trainer->ptr->tot_remun += found_trainer->ptr->remun[match_trainer_member_progs(allot_head->request_prog, found_trainer)];
					allot_head->m_ptr->alot = 1;
					allot_head->m_ptr->slot_hr = start_hour;
					allot_head->m_ptr->happy = 1;
					strcpy(allot_head->m_ptr->booked_prog, allot_head->request_prog);

				}
			}
		}
		struct member_allot_request *next = allot_head->next;
		free(allot_head);
		allot_head = next;
	}
}
void Print_intersection_list(struct BTreeNode_member* r_member)
{
	if (r_member)
	{
		for (int j = 1; j <= r_member->count; j++)
		{
			if (r_member->ptrs[j]->happy==1)
				print_member_data(r_member->ptrs[j]);
		}
		for (int i = 0; i <= r_member->count; i++)
			Print_intersection_list(r_member->linker[i]);
	}
}

void print_hour_wise_list(struct time *time_head, struct available_trainer_ptr *available_head)
{
	struct allots *allot_node;
	struct time *time_itr;
	struct available_trainer_ptr* temp;
	char progs[4][15] = {"Yoga","Zumba","Cardio","Weigth Lifting"};
	int i=0;
	while(i<4)
	{
		printf("\n---");
		fputs(progs[i],stdout);
		printf("---\n");
		time_itr = time_head;
		while(time_itr!=NULL)
		{
			allot_node=time_itr->allot_node;
			temp = available_head;
			while(allot_node!=NULL)
			{
				if(allot_node->m_ptr!=NULL && !strcasecmp(allot_node->m_ptr->booked_prog,progs[i]))
				{

					printf("Member ");
					fputs(allot_node->m_ptr->name,stdout);
					printf(" - Trainer ");
					fputs(temp->ptr->name,stdout);
					printf("\n");
					printf("Time Slot: %d:00-%d:00",allot_node->m_ptr->slot_hr,allot_node->m_ptr->slot_hr+1);
					printf("\n");
				}
				allot_node=allot_node->next;
				temp=temp->next;
			}
			time_itr=time_itr->next;
		}
		i++;
	}

}
void fetchTrainers()
{
	FILE *f;
	f = fopen("trainers.txt","r");
	struct trainer* t = malloc(sizeof(struct trainer));

	while(fread(t,sizeof(struct trainer),1,f))
	{
		insertion(t,1);
		t = malloc(sizeof(struct trainer));
	}

	fclose(f);
}
void fetchMembers()
{
	FILE *f;
	f = fopen("members.txt","r");

	struct member* m = malloc(sizeof(struct member));
	while(fread(m,sizeof(struct member),1,f))
	{
		insertion(m,0);
		m = malloc(sizeof(struct member));
	}

	fclose(f);
}
void traversal(void *myNode,int flag,FILE **f) {
   if(flag)
   {
     int i;
     if (myNode) {
       for (i = 0; i < ((struct BTreeNode_trainer*)myNode)->count; i++) {
         traversal(((struct BTreeNode_trainer*)myNode)->linker[i],flag,f);
        fwrite(myNode,sizeof(struct BTreeNode_trainer),1,*f);
       }
       traversal(((struct BTreeNode_trainer*)myNode)->linker[i],flag,f);
     }
   }
   else
   {
     int i;
     if (myNode) {
       for (i = 0; i < ((struct BTreeNode_member*)myNode)->count; i++) {
         traversal(((struct BTreeNode_member*)myNode)->linker[i],flag,f);
	fwrite(myNode,sizeof(struct BTreeNode_member),1,*f);
       }
       traversal(((struct BTreeNode_member*)myNode)->linker[i],flag,f);
     }
   }
 }

void writeToTrainerFile()
{
	FILE *f;
	f = fopen("trainers.txt","w");
	traversal(trainer_root,1,&f);

	fclose(f);
}
void writeToMemberFile()
{
	FILE *f;
	f = fopen("members.txt","w");
	traversal(member_root,0,&f);
	fclose(f);
}
int main()
{
	int key = 1;
	struct time *time_head = NULL;
	struct available_trainer_ptr *available_head = NULL,*temp;
	time_head = initialize_time(6, 20);
	fetchTrainers();
	fetchMembers();
	printf("\nEnter the key for the corresponding operations!\n");
	while (key)
	{
		printf("----------------------\n1. Add Member\n2. Delete Member\n3. Add Trainer\n4. Delete Trainer\n5. Print Members\n6. Print Trainers\n7. Schedule Slot\n8. Print Trainers Remuneration wise\n9. Print Intersection List\n10. Print Hour Wise List\n11. Search Member\n12. Search Trainer\n13. Range Search\n0. To exit\n-----------------------\nkey: ");
		scanf("%d", &key);
		getchar();
		if (key == 1)
		{
			Add_member();
			writeToMemberFile();
		}
		else if (key == 2)
		{
			if (member_root != NULL)
			{
				delete_member(time_head,available_head);
				writeToMemberFile();
			}
			else
				printf("No members present!\n");
		}

		else if (key == 3)
		{
			Add_trainer(&available_head,time_head);
			writeToTrainerFile();
		}
		else if (key == 4)
		{
			if (trainer_root != NULL)
			{
				delete_trainer(time_head,&available_head);
				writeToTrainerFile();
			}
			else
				printf("No trainers present!\n");
		}

		else if (key == 5)
			// Print_member_list(m_head);
			Print_member_list(member_root);
		else if (key == 6)
			// Print_trainer_list(t_head);
			Print_trainer_list(trainer_root);
		else if (key == 7)
		{
			if (available_head != NULL)
				schedule_slot(time_head, available_head);
			else
				printf("No free trainers present!\n");
			//printf("Not implemented\n\n");
		}

		else if (key == 8)
			// print_sorted_remuneration_list(t_head);
			printf("Not implemented\n\n");
		else if (key == 9)
		{
			printf("Members who were assigned their preffered trainers!\n\n");
			Print_intersection_list(member_root);
		}
			
			//printf("Not implemented\n\n");
		else if (key == 10)
		//	printf("Not implemented\n\n");
		 print_hour_wise_list(time_head, available_head);
		else if (key == 11)
			search_member();
		else if (key == 12)
			search_trainer();
		else if(key==13)
		{
			printf("\n------Enter range to search!-----\n");
			printf("Enter lower bound(inclusive!)\n");
			int low;
			scanf("%d",&low);
			getchar();
			printf("Enter upper bound(inclusive!)\n");
			int high;
			scanf("%d",&high);
			getchar();
			range_search(low,high,member_root);
		}
			
	}
}
