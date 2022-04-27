#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define start_time 6
#define end_time 8
// Trainer data list
struct trainer
{
	int trainer_id;
	char name[50];
	char programs[4][15];
	int remun[4];
	int tot_remun;
	int available;
	struct trainer *next;
};

// Member Data list
struct member
{
	int member_id, age, fees[4];
	char name[50];
	char gender[7];
	char enroll_prog[4][15], booked_prog[15];
	int alot, slot_hr, happy;
	struct member *next;
};

// Member - Trainer allotment node for every hour and allots nodes are in sync with the available_trainer_ptr nodes
struct allots
{
	struct member *m_ptr;
	struct allots *next;
};

// Time(per hour) data list
struct time
{
	int tot_persons;
	struct allots *allot_node;
	struct time *next;
};

// Available trainer list(kind of a hash table structure so that we dont't have to traverse everytime the entire trainer list)
struct available_trainer_ptr
{
	struct trainer *ptr;
	struct available_trainer_ptr *next;
};

// A node created for slot request per member(Hash table structure of members)
struct member_allot_request
{
	struct member *m_ptr;
	int timestamp, slot_hr, trainer_id;
	char request_prog[15];
	struct member_allot_request *next;
};
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
void *sortedMerge(void *a, void *b, int flag, int flag2)
{
	void *res;
	if (flag == 1)
	{
		if (flag2 == 0)
		{
			struct trainer *t_a = (struct trainer *)a, *t_b = (struct trainer *)b;
			if ((t_a == NULL))
				res = t_b;
			else if (t_b == NULL)
				res = t_a;
			else
			{
				struct trainer *result = NULL;

				// pick either `a` or `b`, and recur
				if (t_a->trainer_id <= t_b->trainer_id)
				{
					result = t_a;
					result->next = (struct trainer *)sortedMerge((void *)(t_a->next), (void *)t_b, flag, flag2);
				}
				else
				{
					result = t_b;
					result->next = (struct trainer *)sortedMerge((void *)t_a, (void *)(t_b->next), flag, flag2);
				}
				res = (void *)result;
			}
		}
		else
		{
			struct trainer *t_a = (struct trainer *)a, *t_b = (struct trainer *)b;
			if ((t_a == NULL))
				res = t_b;
			else if (t_b == NULL)
				res = t_a;
			else
			{
				struct trainer *result = NULL;

				// pick either `a` or `b`, and recur
				if (t_a->tot_remun >= t_b->tot_remun)
				{
					result = t_a;
					result->next = (struct trainer *)sortedMerge((void *)(t_a->next), (void *)t_b, flag, flag2);
				}
				else
				{
					result = t_b;
					result->next = (struct trainer *)sortedMerge((void *)t_a, (void *)(t_b->next), flag, flag2);
				}
				res = (void *)result;
			}
		}
	}
	else
	{
		if (flag2 == 0)
		{
			struct member *m_a = (struct member *)a, *m_b = (struct member *)b;
			if ((m_a == NULL))
				res = m_b;
			else if (m_b == NULL)
				res = m_a;
			else
			{
				struct member *result = NULL;

				// pick either `a` or `b`, and recur
				if (m_a->member_id <= m_b->member_id)
				{
					result = m_a;
					result->next = (struct member *)sortedMerge((void *)(m_a->next), (void *)m_b, flag, flag2);
				}
				else
				{
					result = m_b;
					result->next = (struct member *)sortedMerge((void *)m_a, (void *)(m_b->next), flag, flag2);
				}
				res = (void *)result;
			}
		}
		else
		{
			struct member_allot_request *m_a = (struct member_allot_request *)a, *m_b = (struct member_allot_request *)b;
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
					result->next = (struct member_allot_request *)sortedMerge((void *)(m_a->next), (void *)m_b, flag, flag2);
				}
				else
				{
					result = m_b;
					result->next = (struct member_allot_request *)sortedMerge((void *)m_a, (void *)(m_b->next), flag, flag2);
				}
				res = (void *)result;
			}
		}
	}
	return res;
}
void *middle(void *head1, int flag, int flag2)
{
	struct member *m_new_list = NULL;
	struct trainer *t_new_list = NULL;
	struct member_allot_request *allot_m_new_list = NULL;
	void *result;
	if (flag == 1)
	{
		struct trainer *slow = (struct trainer *)head1, *fast = ((struct trainer *)head1)->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		t_new_list = slow->next;
		slow->next = NULL;
		result = (void *)t_new_list;
	}
	else
	{
		if (flag2 == 0)
		{
			struct member *slow = (struct member *)head1, *fast = ((struct member *)head1)->next;
			while (fast != NULL)
			{
				fast = fast->next;
				if (fast != NULL)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}
			m_new_list = slow->next;
			slow->next = NULL;
			result = (void *)m_new_list;
		}
		else
		{
			struct member_allot_request *slow = (struct member_allot_request *)head1, *fast = ((struct member_allot_request *)head1)->next;
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
			result = (void *)allot_m_new_list;
		}
	}
	return result;
}
void *mergesort(void *head, int flag, int flag2)
{
	void *v_head;
	if (flag == 1)
	{
		struct trainer *t_head = (struct trainer *)head;
		if (t_head != NULL && t_head->next != NULL)
		{
			struct trainer *back1 = NULL;

			back1 = middle((void *)t_head, flag, flag2);
			head = mergesort((void *)t_head, flag, flag2);

			back1 = mergesort((void *)back1, flag, flag2);

			head = sortedMerge(head, back1, flag, flag2);
		}
		v_head = (void *)head;
	}
	else
	{
		if (flag2 == 0)
		{
			struct member *m_head = (struct member *)head;
			if (m_head != NULL && m_head->next != NULL)
			{
				struct member *back1 = NULL;

				back1 = middle((void *)m_head, flag, flag2);
				head = mergesort((void *)m_head, flag, flag2);

				back1 = mergesort((void *)back1, flag, flag2);

				head = sortedMerge(head, back1, flag, flag2);
			}
			v_head = (void *)head;
		}
		else
		{
			struct member_allot_request *request_m_head = (struct member_allot_request *)head;
			if (request_m_head != NULL && request_m_head->next != NULL)
			{
				struct member_allot_request *back1 = NULL;

				back1 = middle((void *)request_m_head, flag, flag2);
				head = mergesort((void *)request_m_head, flag, flag2);

				back1 = mergesort((void *)back1, flag, flag2);

				head = sortedMerge(head, back1, flag, flag2);
			}
			v_head = (void *)head;
		}
	}
	return v_head;
}
int match_trainer_member_progs(char progs[], struct available_trainer_ptr *trainer)
{
	int i = 0, res = 1;
	while ((i < 4) && (trainer->ptr->programs[i][0] != '\0') && strcmpi(trainer->ptr->programs[i], progs))
		i++;
	if ((i == 4) || (trainer->ptr->programs[i][0] == '\0'))
		i = -1;
	return i;
}
void Print_trainer_list(struct trainer *head)
{
	while (head != NULL)
	{
		printf("Name: %s\nTrainer Id: %d\n", head->name, head->trainer_id);
		int i = 0;
		while (i < 4 && head->programs[i][0] != '\0')
		{
			printf("Program %d: ", i + 1);
			fputs(head->programs[i], stdout);
			printf(", Remuneration: %d\n", head->remun[i]);

			i++;
		}
		printf("Total remuneration earned today: %d\n", head->tot_remun);
		head = head->next;
		printf("\n");
	}
}
void Print_member_list(struct member *head)
{
	while (head != NULL)
	{
		printf("Name: %s\nmember Id: %d\n", head->name, head->member_id);
		int i = 0;
		while (i < 4 && head->enroll_prog[i][0] != '\0')
		{
			printf("Enrolled Program %d: ", i + 1);
			fputs(head->enroll_prog[i], stdout);
			printf(", Fees paid: %d\n", head->fees[i]);
			i++;
		}
		head = head->next;
		printf("\n");
	}
}
void search_trainer(struct trainer *head)
{
	printf("---------------Enter number to search the field---------------\n");
	int num = 4;
	struct trainer *temp = head;

	while (num)
	{
		printf("1: Name\n2: Trainer Id\n3: Programs\n0: To exit searching\n");
		scanf("%d", &num);
		getchar();
		if (num == 1)
		{
			char name[50];
			printf("Enter name: \n");
			gets(name);
			while ((temp != NULL))
			{
				if (!strcmpi(temp->name, name))
				{
					struct trainer *temp_next = temp->next;
					temp->next = NULL;
					Print_trainer_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Trainer not found!\n");
			}
			num = 1;
		}
		else if (num == 2)
		{
			int t_id;
			printf("Enter trainer ID:\n");
			scanf("%d", &t_id);
			getchar();
			while ((temp != NULL) && (t_id != temp->trainer_id))
				temp = temp->next;
			if (temp != NULL)
			{
				struct trainer *temp_next = temp->next;
				temp->next = NULL;
				Print_trainer_list(temp);
				temp->next = temp_next;
			}
			else
			{
				printf("Trainer not found!\n");
			}
		}
		else if (num == 3)
		{
			char program[15];
			printf("Enter program:\n");
			gets(program);
			while ((temp != NULL))
			{
				int i = 0;
				while ((i < 4) && (temp->programs[i][0] != '\0') && strcmpi(temp->programs[i], program))
				{
					i++;
				}
				if ((i < 4) && (temp->programs[i][0] != '\0'))
				{
					struct trainer *temp_next = temp->next;
					temp->next = NULL;
					Print_trainer_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
				printf("Trainer not found!\n");
			num = 3;
		}
		temp = head;
	}
}

void search_member(struct member *head)
{
	printf("---------------Enter number to search the field---------------\n");
	int num = 1;
	struct member *temp = head;
	while (num)
	{
		printf("1: Name\n2: Member Id\n3: Program Enrolled(searches for a single program input)\n4: Gender\n5: Age\n6: Fees Paid (for any program)\n7: Total Fees paid\n0: To exit searching\n");
		scanf("%d", &num);
		getchar();
		if (num == 1)
		{
			char name[50];
			printf("Enter name: \n");
			gets(name);
			while ((temp != NULL))
			{
				if (!strcmpi(temp->name, name))
				{
					struct member *temp_next = temp->next;
					temp->next = NULL;
					Print_member_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 1;
		}
		else if (num == 2)
		{
			int t_id;
			printf("Enter member ID:\n");
			scanf("%d", &t_id);
			getchar();
			struct member *prev = NULL;
			while ((temp != NULL) && (t_id != temp->member_id))
			{
				temp = temp->next;
			}

			if (temp != NULL)
			{
				struct member *temp_next = temp->next;
				temp->next = NULL;
				Print_member_list(temp);
				temp->next = temp_next;
			}
			else
			{
				printf("Member not found!\n");
			}
		}
		else if (num == 3)
		{
			char program[15];
			printf("Enter program:\n");
			gets(program);
			while ((temp != NULL))
			{
				int i = 0;
				while ((i < 4) && (temp->enroll_prog[i][0] != '\0') && strcmpi(temp->enroll_prog[i], program))
				{
					i++;
				}
				if ((i < 4) && (temp->enroll_prog[i][0] != '\0'))
				{
					struct member *temp_next = temp->next;
					temp->next = NULL;
					Print_member_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 3;
		}
		else if (num == 4)
		{
			printf("Enter gender!\n");
			char gender[7];
			gets(gender);
			while (temp != NULL)
			{
				if (!strcmpi(temp->gender, gender))
				{
					struct member *temp_next = temp->next;
					temp->next = NULL;
					Print_member_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 4;
		}
		else if (num == 5)
		{
			printf("Enter Age:\n");
			int age;
			scanf("%d", &age);
			getchar();
			while (temp != NULL)
			{
				if (age == temp->age)
				{
					struct member *temp_next = temp->next;
					temp->next = NULL;
					Print_member_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 5;
		}
		else if (num == 6)
		{
			printf("Enter fees paid(for a program):\n");
			int fees;
			scanf("%d", &fees);
			getchar();
			int i;
			while (temp != NULL)
			{
				i = 0;
				while ((i < 4) && (temp->fees[i] != 0))
				{
					if (temp->fees[i] == fees)
					{
						struct member *temp_next = temp->next;
						temp->next = NULL;
						Print_member_list(temp);
						temp->next = temp_next;
						num = 0;
						i = 4;
					}
					i++;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 6;
		}
		else if (num == 7)
		{
			printf("Enter total fees paid\n");
			int tot_fees;
			scanf("%d", &tot_fees);
			int i;
			int sum;
			while (temp != NULL)
			{
				i = sum = 0;
				while ((i < 4) && (temp->fees[i] != 0))
				{
					sum += temp->fees[i];
					i++;
				}
				if (sum == tot_fees)
				{
					struct member *temp_next = temp->next;
					temp->next = NULL;
					Print_member_list(temp);
					temp->next = temp_next;
					num = 0;
				}
				temp = temp->next;
			}
			if (num != 0)
			{
				printf("Member not found!\n");
			}
			num = 7;
		}
		temp = head;
	}
}

struct trainer *Add_trainer(struct trainer *t_head, struct available_trainer_ptr **avail_t_head,struct time* time_head)
{
	char name[50] = {0};
	int name_comp, flag = 1;
	struct trainer *input_head = NULL, *input_tail;
	char programs[4][15] = {0};
	int remn[4];
	struct available_trainer_ptr *train_tail_ptr = NULL, *temp_ptr = (*avail_t_head), *t_ptr;

	while (flag)
	{
		printf("\n-----Enter trainer details! (enter x when done)-----\n");
		printf("Enter Trainer name!:\n");
		flag = 0;
		int i = 0;
		gets(name);
		name_comp = strcmp(name, "x");

		if (name_comp)
		{
			char prog_inp[15] = {0};
			printf("\n---Enter list of activities of the trainer! (enter x when done!)---\n");
			int comp = strcmp(prog_inp, "x");

			for (int i = 0; i < 4; i++)
			{
				programs[i][0] = '\0';
				remn[i] = 0;
			}

			while (comp && (i < 4))
			{
				printf("Enter activity %d:\n", i + 1);
				gets(prog_inp);
				comp = strcmp(prog_inp, "x");
				if (comp)
				{
					printf("Enter remuneration!:\n");
					strcpy(programs[i], prog_inp);
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
						train_tail_ptr=t_ptr; 						//<-------------------- INSERTED LINE!
					}
					add_trainer_slots(time_head,(*avail_t_head));
				}
				t->available=available;
				t->tot_remun = 0;
				t->next = NULL;
				Print_trainer_list(t);
				if (input_head == NULL)
				{
					input_head = t;
				}

				else
				{
					input_tail->next = t;
				}
				input_tail = t;
			}
			flag = 1;
		}
	}
	input_head = (struct trainer *)mergesort((void *)input_head, 1, 0);
	t_head = (struct trainer *)sortedMerge((void *)t_head, (void *)input_head, 1, 0);
	printf("---------------Trainers added successfully!----------\n\n");
	return t_head;
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
struct trainer *delete_trainer(struct trainer *head, struct available_trainer_ptr **available_head, struct time *time_head)
{
	int trainer_id = 1;
	struct trainer *ahead, *temp = head;
	while (trainer_id)
	{
		printf("Enter trainer ID to remove (enter 0 when done)\n");
		scanf("%d", &trainer_id);
		getchar();
		if (trainer_id)
		{
			if (head->trainer_id == trainer_id)
			{
				ahead = head->next;
				if(head->available==1)
					remove_trainer_slots(head,available_head,time_head);
				free(head);
				head = ahead;
				printf("--------Trainer deleted successfully------\n\n");
			}
			else
			{
				while ((temp->next != NULL) && (temp->next->trainer_id != trainer_id))
					temp = temp->next;
				if (temp->next == NULL)
					printf("No trainer found!");
				else
				{
					ahead = temp->next;
					temp->next = ahead->next;
					if(ahead->available==1)
						remove_trainer_slots(ahead,available_head,time_head);
					free(ahead);
					printf("--------Trainer deleted successfully------\n\n");
				}
			}
		}
	}
	return head;
}
struct member *Add_member(struct member *m_head)
{
	char name[50];

	int flag = 1;
	struct member *inp_head = NULL, *tail;

	while (flag)
	{
		printf("--------Enter Member details! (enter x when done)--------\n");
		flag = 0;
		printf("Enter Member Name: \n");
		gets(name);
		int comp = strcmp(name, "x");
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
			gets(gender);

			printf("\n\n------Enter Programs to enroll! (enter x when done)-----\n");
			char enroll_inp[15] = {0};
			int i = 0;
			int comp = strcmp(enroll_inp, "x");
			while (comp && (i < 4))
			{
				printf("Enter program %d: \n", i + 1);
				gets(enroll_inp);
				comp = strcmp(enroll_inp, "x");
				if (comp)
				{
					strcpy(enroll_progs[i], enroll_inp);
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
			m->next = NULL;
			Print_member_list(m);
			if (inp_head == NULL)
			{
				inp_head = m;
			}
			else
			{
				tail->next = m;
			}
			tail = m;
			flag = 1;
		}
	}
	inp_head = (struct member *)mergesort((void *)inp_head, 0, 0);
	m_head = (struct member *)sortedMerge((void *)m_head, inp_head, 0, 0);
	printf("---------------Members added successfully!----------\n\n");
	return m_head;
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
struct member *delete_member(struct member *head, struct time *time_head, struct available_trainer_ptr *available_head)
{
	int member_id = 1;
	struct member *ahead, *temp = head;
	while (member_id)
	{
		printf("\n-------Enter member ID to remove (enter 0 when done)--------\n");
		printf("Enter member ID: \n");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			if (head->member_id == member_id)
			{
				ahead = head->next;
				if (head->alot == 1)
					remove_member_bookings(head, time_head, available_head);
				free(head);
				head = ahead;
				printf("--------Member deleted successfully------\n\n");
			}
			else
			{
				while ((temp->next != NULL) && (temp->next->member_id != member_id))
					temp = temp->next;
				if (temp->next == NULL)
					printf("No member found!");
				else
				{
					ahead = temp->next;
					temp->next = ahead->next;
					if (ahead->alot == 1)
						remove_member_bookings(ahead, time_head, available_head);
					free(ahead);
					printf("--------Member deleted successfully------\n\n");
				}
			}
		}
		
	}
	return head;
}
void schedule_slot(struct member *m_head, struct time *h_head, struct available_trainer_ptr *available_head)
{
	int member_id = 1;
	struct member *member_temp;
	struct member_allot_request *allot_head = NULL, *t, *allot_tail;
	while (member_id)
	{
		member_temp = m_head;
		printf("\nEnter member ID: (enter 0 to start booking)\n");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			while ((member_temp != NULL) && (member_temp->member_id != member_id))
			{
				member_temp = member_temp->next;
			}
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
				gets(progs);
				i = 0;
				while ((i < 4) && (member_temp->enroll_prog[i][0] != '\0') && (strcmpi(member_temp->enroll_prog[i], progs)))
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
	allot_head = mergesort((void *)allot_head, 0, 1);
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

void print_sorted_remuneration_list(struct trainer *t_head)
{
	t_head = mergesort((void *)t_head, 1, 1);
	Print_trainer_list(t_head);
	t_head = mergesort((void *)t_head, 1, 0);
}
void print_intersection_list(struct member *m_head)
{
	printf("------Members who were assigned preffered trainers!-------\n");
	struct member *temp = m_head;
	while (m_head != NULL)
	{
		if (m_head->alot == 1 && m_head->happy == 1)
		{
			temp = m_head->next;
			m_head->next = NULL;
			Print_member_list(m_head);
			m_head->next = temp;
		}
		m_head = m_head->next;
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
				if(allot_node->m_ptr!=NULL && !strcmpi(allot_node->m_ptr->booked_prog,progs[i]))
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
int main()
{
	struct available_trainer_ptr *available_head = NULL,*temp;
	struct member *m_head = NULL;
	struct trainer *t_head = NULL;
	struct time *time_head = NULL;
	int key = 1;
	time_head = initialize_time(6, 20);
	printf("\nEnter the key for the corresponding operations!\n");
	while (key)
	{
		printf("----------------------\n1. Add Member\n2. Delete Member\n3. Add Trainer\n4. Delete Trainer\n5. Print Members\n6. Print Trainers\n7. Schedule Slot\n8. Print Trainers Remuneration wise\n9. Print Intersection List\n10. Print Hour Wise List\n11. Search Member\n12. Search Trainer\n0. To exit\n-----------------------\nkey: ");
		scanf("%d", &key);
		getchar();
		if (key == 1)
			m_head = Add_member(m_head);
		else if (key == 2)
		{
			if (m_head != NULL)
				m_head = delete_member(m_head, time_head, available_head);
			else
				printf("No members present!\n");

		}

		else if (key == 3)
		{
			t_head = Add_trainer(t_head, &available_head,time_head);
			
		}
		else if (key == 4)
		{
			if (t_head != NULL)
				t_head = delete_trainer(t_head, &available_head, time_head);
			else
				printf("No trainers present!\n");
		}

		else if (key == 5)
			Print_member_list(m_head);
		else if (key == 6)
			Print_trainer_list(t_head);
		else if (key == 7)
		{
			if (available_head != NULL)
				schedule_slot(m_head, time_head, available_head);
			else
				printf("No free trainers present!\n");
		}

		else if (key == 8)
			print_sorted_remuneration_list(t_head);
		else if (key == 9)
			print_intersection_list(m_head);
		else if (key == 10)
			print_hour_wise_list(time_head, available_head);
		else if (key == 11)
			search_member(m_head);
		else if (key == 12)
			search_trainer(t_head);
	}
	return 0;
}
