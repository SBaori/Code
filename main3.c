#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// TODO: Programs[4][15] in sorted order
// TODO: remun search field
// TODO: multiple program search field
// TODO: Narrow down search
struct trainer
{
	int trainer_id;
	char name[50];
	char programs[4][15];
	int remun[4];
	struct trainer *next;
};

struct member
{
	int member_id, age, fees[4];
	char name[50];
	char gender[7];
	char enroll_prog[4][15];
	struct member *next;
};
struct allots
{
	struct trainer* t_ptr;
	struct member* m_ptr;
	struct allots* next;
};

struct time
{
	int hr,tot_persons;
	struct allots* allot_node;
	struct time* next;
};
struct time* initialize_time(int first_hour_start,int last_hour_start)
{
	struct time* head = NULL,*t,*tail;
	while(first_hour_start<=last_hour_start)
	{
		t=malloc(sizeof(struct time));
		t->next=NULL;
		if(head == NULL)
		{
			
			head = t;
			tail = head;
		}
		else
		{
			tail->next = t;
		}
		first_hour_start++;
	}
}
void *sortedMerge(void *a, void *b, int flag)
{
	void *res;
	if (flag == 1)
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
				result->next = (struct trainer *)sortedMerge((void *)(t_a->next), (void *)t_b, flag);
			}
			else
			{
				result = t_b;
				result->next = (struct trainer *)sortedMerge((void *)t_a, (void *)(t_b->next), flag);
			}
			res = (void *)result;
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
				result->next = (struct member *)sortedMerge((void *)(m_a->next), (void *)m_b, flag);
			}
			else
			{
				result = m_b;
				result->next = (struct member *)sortedMerge((void *)m_a, (void *)(m_b->next), flag);
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
void *mergesort(void *head, int flag)
{
	void *v_head;
	if (flag == 1)
	{
		struct trainer *t_head = (struct trainer *)head;
		if (t_head != NULL && t_head->next != NULL)
		{
			struct trainer *back1 = NULL;

			back1 = middle((void *)t_head, flag);
			head = mergesort((void *)t_head, flag);

			back1 = mergesort((void *)back1, flag);

			head = sortedMerge(head, back1, flag);
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
			head = mergesort((void *)m_head, flag);

			back1 = mergesort((void *)back1, flag);

			head = sortedMerge(head, back1, flag);
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
struct trainer *Add_trainer(struct trainer *t_head)
{
	char name[50] = {0};
	int name_comp, flag = 1;
	struct trainer *input_head = NULL, *input_tail;
	char programs[4][15] = {0};
	int remn[4];
	printf("---Enter trainer details! (enter x when done)---\n");
	while (flag)
	{

		printf("enter name!:\n");
		flag = 0;
		int i = 0;
		gets(name);
		name_comp = strcmp(name, "x");

		if (name_comp)
		{
			char prog_inp[15] = {0};
			printf("\n---enter list of activities of the trainer! (enter x when done!)---\n");
			int comp = strcmp(prog_inp, "x");

			for (int i = 0; i < 4; i++)
			{
				programs[i][0] = '\0';
				remn[i] = 0;
			}

			while (comp && (i < 4))
			{
				printf("Enter activity:\n");
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

			flag = 1;
		}
	}
	input_head = (struct trainer *)mergesort((void *)input_head, 1);
	t_head = (struct trainer *)sortedMerge((void *)t_head, (void *)input_head, 1);
	printf("---------------Trainers added successfully!----------\n");
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
	printf("Enter Member details! (enter x when done)\n");
	int flag = 1;
	struct member *inp_head = NULL, *tail;

	while (flag)
	{
		flag = 0;
		printf("Enter Name!\n");
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

			printf("Enter Programs to enroll! (enter x when done)\n");
			char enroll_inp[15] = {0};
			int i = 0;
			int comp = strcmp(enroll_inp, "x");
			while (comp && (i < 4))
			{
				printf("Enter program!\n");
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
	inp_head = (struct member *)mergesort((void *)inp_head, 0);
	m_head = (struct member *)sortedMerge((void *)m_head, inp_head, 0);
	printf("---------------Members added successfully!----------\n");
	return m_head;
}
struct member *delete_member(struct member *head)
{
	int member_id = 1;
	struct member *ahead, *temp = head;
	while (member_id)
	{
		printf("Enter member ID to remove (enter 0 when done)");
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
int main()
{
	initialize_time(6,12+8);
	struct member *head = Add_member(NULL);
	printf("-----------SECOND TIME-------\n");
	head = Add_member(head);
	search_member(head);

	return 0;
}
