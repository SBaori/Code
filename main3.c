#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Timestamp
// manipulate other data in delete trainer/member
// print grouped program-wise in hour_list
// Add descriptive messages/prompts
struct trainer
{
	int trainer_id;
	char name[50];
	char programs[4][15];
	int remun[4];
	int tot_remun;
	struct trainer *next;
};

struct member
{
	int member_id, age, fees[4];
	char name[50];
	char gender[7];
	char enroll_prog[4][15];
	int alot, slot_hr,happy;
	struct member *next;
};
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
struct time *initialize_time(int first_hour_start, int last_hour_start, struct available_trainer_ptr *available_head)
{
	struct time *head = NULL, *t, *tail;
	struct available_trainer_ptr *temp;
	struct allots *t_allots, *tail_allots;
	while (first_hour_start <= last_hour_start)
	{
		t = malloc(sizeof(struct time));
		t->next = NULL;
		t->allot_node = NULL;

		temp = available_head;
		while ((temp != NULL))
		{
			t_allots = malloc(sizeof(struct allots));
			t_allots->m_ptr = NULL;
			if (t->allot_node == NULL)
			{
				t->allot_node = t_allots;
			}
			else
			{
				tail_allots->next = t_allots;
			}

			tail_allots = t_allots;
			temp = temp->next;
		}
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

void *sortedMerge(void *a, void *b, int flag, int remun)
{
	void *res;
	if (flag == 1)
	{
		if (remun == 0)
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
					result->next = (struct trainer *)sortedMerge((void *)(t_a->next), (void *)t_b, flag, remun);
				}
				else
				{
					result = t_b;
					result->next = (struct trainer *)sortedMerge((void *)t_a, (void *)(t_b->next), flag, remun);
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
					result->next = (struct trainer *)sortedMerge((void *)(t_a->next), (void *)t_b, flag, remun);
				}
				else
				{
					result = t_b;
					result->next = (struct trainer *)sortedMerge((void *)t_a, (void *)(t_b->next), flag, remun);
				}
				res = (void *)result;
			}
		}
	}
	else
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
				result->next = (struct member *)sortedMerge((void *)(m_a->next), (void *)m_b, flag, remun);
			}
			else
			{
				result = m_b;
				result->next = (struct member *)sortedMerge((void *)m_a, (void *)(m_b->next), flag, remun);
			}
			res = (void *)result;
		}
	}
	return res;
}
void *middle(void *head1, int flag)
{
	struct member *m_new_list = NULL;
	struct trainer *t_new_list = NULL;
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
	return result;
}
void *mergesort(void *head, int flag, int remun)
{
	void *v_head;
	if (flag == 1)
	{
		struct trainer *t_head = (struct trainer *)head;
		if (t_head != NULL && t_head->next != NULL)
		{
			struct trainer *back1 = NULL;

			back1 = middle((void *)t_head, flag);
			head = mergesort((void *)t_head, flag, remun);

			back1 = mergesort((void *)back1, flag, remun);

			head = sortedMerge(head, back1, flag, remun);
		}
		v_head = (void *)head;
	}
	else
	{
		struct member *m_head = (struct member *)head;
		if (m_head != NULL && m_head->next != NULL)
		{
			struct member *back1 = NULL;

			back1 = middle((void *)m_head, flag);
			head = mergesort((void *)m_head, flag, remun);

			back1 = mergesort((void *)back1, flag, remun);

			head = sortedMerge(head, back1, flag, remun);
		}
		v_head = (void *)head;
	}
	return v_head;
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
			printf("Total remuneration earned today: %d\n",head->tot_remun);
			i++;
		}
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

struct trainer *Add_trainer(struct trainer *t_head, struct available_trainer_ptr **avail_t_head)
{
	char name[50] = {0};
	int name_comp, flag = 1;
	struct trainer *input_head = NULL, *input_tail;
	char programs[4][15] = {0};
	int remn[4];
	struct available_trainer_ptr *train_tail_ptr = NULL, *temp_ptr = (*avail_t_head), *t_ptr;

	while (flag)
	{
		printf("-----Enter trainer details! (enter x when done)-----\n");
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
					}
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
			}
			flag = 1;
		}
	}
	input_head = (struct trainer *)mergesort((void *)input_head, 1, 0);
	t_head = (struct trainer *)sortedMerge((void *)t_head, (void *)input_head, 1, 0);
	printf("---------------Trainers added successfully!----------\n\n");
	return t_head;
}
struct trainer *delete_trainer(struct trainer *head)
{
	int trainer_id = 1;
	struct trainer *ahead, *temp = head;
	while (trainer_id)
	{
		printf("Enter trainer ID to remove (enter 0 when done)");
		scanf("%d", &trainer_id);
		getchar();
		if (trainer_id)
		{
			if (head->trainer_id == trainer_id)
			{
				ahead = head->next;
				free(head);
				head = ahead;
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
					free(ahead);
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

			printf("\n\n------Enter Programs to enroll! (enter x when done)-----\n\n");
			char enroll_inp[15] = {0};
			int i = 0;
			int comp = strcmp(enroll_inp, "x");
			while (comp && (i < 4))
			{
				printf("Enter program %d: \n",i+1);
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
struct member *delete_member(struct member *head)
{
	int member_id = 1;
	struct member *ahead, *temp = head;
	while (member_id)
	{
		printf("-------Enter member ID to remove (enter 0 when done)--------\n\n");
		printf("Enter member ID: \n");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			if (head->member_id == member_id)
			{
				ahead = head->next;
				free(head);
				head = ahead;
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
					free(ahead);
				}
			}
		}
	}
	return head;
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
// struct allot* find_free_slot(struct time* time_temp,struct trainer* available_trainers,char progs[])
// {
// 	struct trainer* trainer_temp = available_trainers,
// 	while ((trainer_temp != NULL) && (trainer_temp->trainer_id != trainer_id))
// 	{
// 		if (match_trainer_member_progs(progs, trainer_temp))
// 		{
// 			if (allot_time_temp->m_ptr != NULL)
// 			{
// 				other_matching_trainer = trainer_temp;
// 				other_matching_allot = allot_time_temp;
// 			}
// 		}
// 		// printf("exec\n");
// 		trainer_temp = trainer_temp->next;
// 		allot_time_temp = allot_time_temp->next;
// 	}
// }
void schedule_slot(struct member *m_head, struct time *h_head, struct available_trainer_ptr *available_head)
{
	int member_id = 1;
	while (member_id)
	{

		printf("Enter member ID: (enter 0 to exit)");
		scanf("%d", &member_id);
		getchar();
		if (member_id)
		{
			struct member *member_temp = m_head;
			while ((member_temp != NULL) && (member_temp->member_id != member_id))
			{
				member_temp = member_temp->next;
			}
			if (member_temp == NULL)
			{
				printf("Member not found!\n");
			}
			else if (member_temp->alot == 1)
				printf("Alotted slot for today!\n");
			else
			{
				int slot_hour;
				printf("Enter start of preffered 1 hr slot:\n------(if preffered slot is 6:00 to 7:00, then enter 6; Time taken in 24hr format)------\n");
				scanf("%d", &slot_hour);
				getchar();
				if ((slot_hour > 20) || (slot_hour < 6))
					printf("Enter time slot between 6:00 and 21:00!\n\n");
				else
				{
					int trainer_id;
					printf("List of available trainer!\n");
					// Print_trainer_list(available_head);
					printf("\nEnter preffered trainer_ID:\n");
					scanf("%d", &trainer_id);
					getchar();
					printf("Programs enrolled by member: ");
					fputs(member_temp->name, stdout);
					printf("\n");
					int i = 0;
					while ((i < 4) && (member_temp->enroll_prog[i][0] != '\0'))
					{
						printf("%d - ", i);
						fputs(member_temp->enroll_prog[i], stdout);
						printf("\n");
						i++;
					}
					char progs[15];
					printf("Enter program to book slot!(only 1 accepted)\n");
					gets(progs);
					int j = 0;
					while ((j < 4) && (member_temp->enroll_prog[j][0] != '\0') && (strcmpi(member_temp->enroll_prog[j], progs)))
						j++;
					if ((j == 4) || (member_temp->enroll_prog[j][0] == '\0'))
					{
						printf("Program not enrolled!\n\n");
					}
					else
					{
						int start_hour = 6;
						struct time *time_temp = h_head;

						while (start_hour < slot_hour)
						{
							time_temp = time_temp->next;

							start_hour++;
						}
						struct available_trainer_ptr *trainer_temp = available_head, *other_matching_trainer = NULL,*found_trainer=NULL;
						struct allots *allot_time_temp = time_temp->allot_node, *other_matching_allot,*found_trainer_allot;
						if (time_temp->tot_persons == 10)
							printf("Total members exceeding the limit given in covid guidline! Choose different time slot\n\n");
						else
						{
							while ((trainer_temp != NULL))
							{

								if (match_trainer_member_progs(progs, trainer_temp) != -1)
								{
									if(trainer_temp->ptr->trainer_id==trainer_id)
									{
										found_trainer=trainer_temp;
										found_trainer_allot=allot_time_temp;
										//f=0;
									}
									else if (allot_time_temp->m_ptr==NULL)
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
								printf("Trainer does not exit or does not specialise in the entered program!\n\n");
							// else if (match_trainer_member_progs(progs, trainer_temp) == -1)
							// 	printf("Trainer does not specialise in the given program\n\n");
							else
							{
								if (found_trainer_allot->m_ptr != NULL)
								{
									printf("-----Trainer not free-----\n");
									if (other_matching_trainer != NULL)
									{
										printf("Alloting to other free trainers in the same time slot for the entered program!\n");
										other_matching_allot->m_ptr = member_temp;
										time_temp->tot_persons++;
										printf("Slot booked for the member ");
										fputs(member_temp->name,stdout);
										printf("from %d:00-%d:00 with trainer ",start_hour,start_hour+1);
										fputs(other_matching_trainer->ptr->name,stdout);
										printf("\n");
										other_matching_trainer->ptr->tot_remun += other_matching_trainer->ptr->remun[match_trainer_member_progs(progs, other_matching_trainer)];
										// printf("---------%d:%d--------\n",other_matching_trainer->tot_remun,match_trainer_member_progs(progs,other_matching_trainer));
										member_temp->alot = 1;
										member_temp->slot_hr = start_hour;
										member_temp->happy=0;
									}
									else
									{
										// trainer_temp = trainer_temp->next;
										// while (trainer_temp != NULL)
										// {
										// 	if (match_trainer_member_progs(progs, trainer_temp) != -1)
										// 	{
										// 		if (allot_time_temp->m_ptr != NULL)
										// 		{
										// 			other_matching_trainer = trainer_temp;
										// 			other_matching_allot = allot_time_temp;
										// 		}
										// 	}
										// 	trainer_temp = trainer_temp->next;
										// 	allot_time_temp = allot_time_temp->next;
										// }
										// if (other_matching_trainer != NULL)
										// {
										// 	other_matching_allot->m_ptr = member_temp;
										// 	time_temp->tot_persons++;
										// 	other_matching_allot->happy = 0;
										// 	printf("Slot booked for the member ID %s for the time %d-%d\n", m_head->name, slot_hour, slot_hour + 1);
										// 	printf("Slot booked for the member ");
										// 	fputs(member_temp->name,stdout);
										// 	printf("from %d:00-%d:00 with trainer ");
										// 	fputs(other_matching_trainer->ptr->name,stdout);
										// 	other_matching_trainer->ptr->tot_remun += other_matching_trainer->ptr->remun[match_trainer_member_progs(progs, other_matching_trainer)];
										// 	// printf("---------%d:%d--------\n",other_matching_trainer->tot_remun,match_trainer_member_progs(progs,other_matching_trainer));
										// 	member_temp->alot = 1;
										// }
										//else
										//{
											time_temp = time_temp->next;
											start_hour++;
											int found = 0;
											while (!found && (time_temp != NULL))
											{
												allot_time_temp = time_temp->allot_node;
												other_matching_trainer = NULL;
												trainer_temp = available_head;
												found_trainer=NULL;
												while ((trainer_temp != NULL) && (!found))
												{
													if (match_trainer_member_progs(progs, trainer_temp) != -1)
													{
														if(trainer_temp->ptr->trainer_id==trainer_id && allot_time_temp->m_ptr==NULL)
														{
															found_trainer=trainer_temp;
															found_trainer_allot=allot_time_temp;
															found=1;
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
												if (found_trainer != NULL)
												{

													found_trainer_allot->m_ptr = member_temp;
													time_temp->tot_persons++;
													// printf("Slot booked for the member ID %s for the time %d-%d\nwith trainer ID %d\n\n", member_temp->name, start_hour, start_hour + 1, trainer_temp->ptr->trainer_id);
													printf("Slot booked for the member ");
													fputs(member_temp->name,stdout);
													printf("from %d:00-%d:00 with trainer ",start_hour,start_hour+1);
													fputs(found_trainer->ptr->name,stdout);
													printf("\n");
													member_temp->alot = 1;
													found_trainer->ptr->tot_remun += found_trainer->ptr->remun[match_trainer_member_progs(progs, found_trainer)];
													// printf("---------%d:%d--------",trainer_temp->tot_remun,match_trainer_member_progs(progs,trainer_temp));
													//found = 1;
													member_temp->slot_hr = start_hour;
													member_temp->happy=1;
												}
												else if (other_matching_trainer != NULL)
												{
													other_matching_allot->m_ptr = member_temp;
													time_temp->tot_persons++;
													// printf("Slot booked for the member ID %s for the time %d-%d\nwith trainer ID: %d\n\n", member_temp->name, start_hour, start_hour + 1, trainer_temp->ptr->trainer_id);
													printf("Slot booked for the member ");
													fputs(member_temp->name,stdout);
													printf("from %d:00-%d:00 with trainer ",start_hour,start_hour+1);
													fputs(other_matching_trainer->ptr->name,stdout);
													printf("\n");
													member_temp->alot = 1;
													other_matching_trainer->ptr->tot_remun += other_matching_trainer->ptr->remun[match_trainer_member_progs(progs, other_matching_trainer)];
													// printf("---------%d:%d--------",other_matching_trainer->tot_remun,match_trainer_member_progs(progs,other_matching_trainer));
													found = 1;
													member_temp->slot_hr = start_hour;
													member_temp->happy=0;
												}
												else
													time_temp = time_temp->next;
											}
											if (time_temp == NULL)
											{
												printf("No available slots today!\n Slot booked for the same preffered time for the next day!\n");
											}
										//}
									}
								}
								else
								{

									found_trainer_allot->m_ptr = member_temp;
									time_temp->tot_persons++;
									// printf("Slot booked for the member ID %s for the time %d-%d\nwith trainer ID: %d\n\n", member_temp->name, slot_hour, slot_hour + 1, trainer_temp->ptr->trainer_id);
									printf("Slot booked for the member ");
									fputs(member_temp->name,stdout);
									printf("from %d:00-%d:00 with trainer ",start_hour,start_hour+1);
									fputs(found_trainer->ptr->name,stdout);
									printf("\n");
									found_trainer->ptr->tot_remun += found_trainer->ptr->remun[match_trainer_member_progs(progs, found_trainer)];
									// printf("---------%d:%d--------",trainer_temp->tot_remun,match_trainer_member_progs(progs,trainer_temp));
									member_temp->alot = 1;
									member_temp->slot_hr = start_hour;
									member_temp->happy=1;
								}
							}
						}
					}
				}
			}
		}
	}
}
void print_sorted_remuneration_list(struct trainer *t_head)
{
	t_head = mergesort((void *)t_head, 1, 1);
	Print_trainer_list(t_head);
	t_head = mergesort((void *)t_head, 1, 0);
}
void print_intersection_list(struct time *time_head)
{
	while (time_head != NULL)
	{
		if (time_head->tot_persons > 0)
		{
			while (time_head->allot_node != NULL)
			{
				if (time_head->allot_node->m_ptr != NULL && time_head->allot_node->happy == 1)
				{
					struct member *store_next = time_head->allot_node->m_ptr->next;
					time_head->allot_node->m_ptr->next = NULL;
					Print_member_list(time_head->allot_node->m_ptr);
					time_head->allot_node->m_ptr->next = store_next;
				}
				time_head->allot_node = time_head->allot_node->next;
			}
		}
		time_head = time_head->next;
	}
}
void print_hour_wise_list(struct time *time_head, struct available_trainer_ptr *available_head)
{
	struct allots *allot_node;
	struct available_trainer_ptr *temp;
	while (time_head != NULL)
	{
		temp = available_head;
		allot_node = time_head->allot_node;
		while (allot_node != NULL)
		{
			if (allot_node->m_ptr != NULL)
			{
				printf("Member Name :");
				fputs(allot_node->m_ptr->name, stdout);
				printf("Member ID: %d\n", allot_node->m_ptr->member_id);
				printf("-----\nTrainer Name: ");
				fputs(temp->ptr->name, stdout);
				printf("Trainer ID: %d\n", temp->ptr->trainer_id);
			}
			temp = temp->next;
			allot_node = allot_node->next;
		}
	}
	time_head = time_head->next;
}
int main()
{
	struct available_trainer_ptr *available_head = NULL;
	struct trainer *t_head = Add_trainer(NULL, &available_head);

	// struct trainer *available_head = available_trainers(t_head);
	//  Print_trainer_list(available_head);
	struct time *time_head = initialize_time(6, 12 + 8, available_head);
	// while(time_head!=NULL)
	// {
	// 	printf("")
	// 	while(time_head->allot_node!=NULL)
	// 	{
	// 		printf("NULL\n");
	// 		time_head->allot_node=time_head->allot_node->next;
	// 	}

	// 	time_head=time_head->next;
	// }
	struct member *m_head = Add_member(NULL);
	// while(time_head)
	//  printf("-----------SECOND TIME-------\n");
	//  head = Add_member(head);
	//  search_member(head);
	schedule_slot(m_head, time_head, available_head);

	print_sorted_remuneration_list(t_head);
	print_intersection_list(time_head);
	return 0;
}
