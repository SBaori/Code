#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ctzns_tot 100
#define vc_tot 100
#define curr_year 2021

struct citizens
{
	int beneficiary_id;
	char name[50];
	char gender[10];
	int YOB;
	int num_doses;
};

struct vaccine_centers
{
	int center_id;
	char center_address[50];
	char district[15];
	int pin_code;
	char center_type[15];
	char vacc_type[6][11];
	int qty[6];
	int price[6];
};
void initialize(struct citizens ctzns[], struct vaccine_centers vc[])
{
	for (int i = 0; i < ctzns_tot; i++)
	{
		ctzns[i].YOB = -1;
		ctzns[i].num_doses = -1;
		ctzns[i].beneficiary_id = 0;
		ctzns[i].name[0] = '\0';
		ctzns[i].gender[0] = '\0';

		vc[i].center_id = 0;
		vc[i].district[0] = '\0';
		vc[i].pin_code = -1;

		for (int j = 0; j < 6; j++)
		{
			vc[i].price[j] = -1;
			vc[i].qty[j] = -1;
			vc[i].vacc_type[j][0] = '\0';
		}
	}
}
void print_ctzn_rec(struct citizens ctzns[], int i)
{
	printf("name: %s\ngender: %s\nbeneficiary_id: %d\nYOB: %d\nNumber of doses: %d\n", ctzns[i].name, ctzns[i].gender, ctzns[i].beneficiary_id, ctzns[i].YOB, ctzns[i].num_doses);
}

void print_vc_rec(struct vaccine_centers vc[], int i)
{
	int j = 0,k=0;
	while(vc[i].center_address[k]!='\0')
	{
		printf("%c",vc[i].center_address[k]);
		k++;
	}
	printf("\ncenter_id: %d\ncenter_type: %s\ndistrict: %s\npin code: %d\n", vc[i].center_id, vc[i].center_type, vc[i].district, vc[i].pin_code);

	while (vc[i].vacc_type[j][0] != '\0' && j < 6)
	{
		printf("vaccine %d: %s, ", j + 1, vc[i].vacc_type[j]);
		printf("quantity : %d, ", vc[i].qty[j]);
		printf("price: %d \n", vc[i].price[j]);
		j++;
	}
}
void sortBeneficiaryid(struct citizens ctzn[],int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		sortBeneficiaryid(ctzn,l,mid);
		sortBeneficiaryid(ctzn,mid+1,r);
		int i1=mid+1-l,i2=r-mid;
		struct citizens a[i1],b[i2]; 
		for(int i=0;i<i1;i++)
			a[i]=ctzn[i+l];
		for(int i=0;i<i2;i++)
			b[i]=ctzn[i+mid+1];
		int i=0,j=0,k=l;
		while(i<i1 && j<i2)
		{
			if(a[i].beneficiary_id<b[j].beneficiary_id)
			{
				ctzn[k]=a[i];
				i++;
				k++;
			}
			else
			{
				ctzn[k]=b[j];
				j++;
				k++;
			}
		}
		while(i<i1)
		{
			ctzn[k]=a[i];
				i++;
				k++;
		}
		while(j<i2)
		{
			ctzn[k]=b[j];
				j++;
				k++;
		}
	}
}
void sortDistrict(struct vaccine_centers vc[], int l, int r, int income[])
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		sortDistrict(vc, l, mid, income);
		sortDistrict(vc, mid + 1, r, income);
		int i1 = mid + 1 - l, i2 = r - mid;
		struct vaccine_centers a[i1], b[i2];
		int income_temp1[i1], income_temp2[i2];
		for (int i = 0; i < i1; i++)
		{
			a[i] = vc[i + l];
			income_temp1[i] = income[i + l];
		}
		for (int i = 0; i < i2; i++)
		{
			b[i] = vc[i + mid + 1];
			income_temp2[i] = income[mid + 1 + i];
		}
		int i = 0, j = 0, k = l;
		while (i < i1 && j < i2)
		{
			if (strcmp(a[i].district, b[j].district) < 0)
			{
				vc[k] = a[i];
				income[k] = income_temp1[i];
				i++;
				k++;
			}
			else
			{
				vc[k] = b[j];
				income[k] = income_temp2[i];
				j++;
				k++;
			}
		}
		while (i < i1)
		{
			vc[k] = a[i];
			income[k] = income_temp1[i];
			i++;
			k++;
		}
		while (j < i2)
		{
			vc[k] = b[j];
			income[k] = income_temp2[i];
			j++;
			k++;
		}
	}
}
void sortPinCode(struct vaccine_centers vc[], int l, int r, int income[])
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		sortPinCode(vc, l, mid, income);
		sortPinCode(vc, mid + 1, r, income);
		int i1 = mid + 1 - l, i2 = r - mid;
		struct vaccine_centers a[i1], b[i2];
		int income_temp1[i1], income_temp2[i2];
		for (int i = 0; i < i1; i++)
		{
			a[i] = vc[i + l];
			income_temp1[i] = income[i + l];
		}

		for (int i = 0; i < i2; i++)
		{
			b[i] = vc[i + mid + 1];
			income_temp2[i] = income[mid + 1 + i];
		}

		int i = 0, j = 0, k = l;
		while (i < i1 && j < i2)
		{
			if (a[i].pin_code < b[j].pin_code)
			{
				vc[k] = a[i];
				income[k] = income_temp1[i];
				i++;
				k++;
			}
			else
			{
				vc[k] = b[j];
				income[k] = income_temp2[i];
				j++;
				k++;
			}
		}
		while (i < i1)
		{
			vc[k] = a[i];
			income[k] = income_temp1[i];
			i++;
			k++;
		}
		while (j < i2)
		{
			vc[k] = b[j];
			income[k] = income_temp2[i];
			j++;
			k++;
		}
	}
}
void sortCenterid(struct vaccine_centers vc[], int l, int r, int income[])
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		sortCenterid(vc, l, mid, income);
		sortCenterid(vc, mid + 1, r, income);
		int i1 = mid + 1 - l, i2 = r - mid;
		struct vaccine_centers a[i1], b[i2];
		int income_temp1[i1], income_temp2[i2];
		for (int i = 0; i < i1; i++)
		{
			a[i] = vc[i + l];
			income_temp1[i] = income[i + l];
		}

		for (int i = 0; i < i2; i++)
		{
			b[i] = vc[i + mid + 1];
			income_temp2[i] = income[i + mid + 1];
		}

		int i = 0, j = 0, k = l;
		while (i < i1 && j < i2)
		{
			if (a[i].center_id < b[j].center_id)
			{
				vc[k] = a[i];
				income[k] = income_temp1[i];
				i++;
				k++;
			}
			else
			{
				vc[k] = b[j];
				income[k] = income_temp2[j];
				j++;
				k++;
			}
		}
		while (i < i1)
		{
			vc[k] = a[i];
			income[k] = income_temp1[i];
			i++;
			k++;
		}
		while (j < i2)
		{
			vc[k] = b[j];
			income[k] = income_temp2[j];
			j++;
			k++;
		}
	}
}
int addNewBeneficiary(struct citizens ctzns[])
{
	printf("enter name: ");
	char name[50];
	scanf("%s", name);
	printf("enter gender: ");
	char gender[10];
	scanf("%s", gender);
	printf("enter year of birth: ");
	int YOB;
	scanf("%d", &YOB);
	if (curr_year - YOB < 18)
	{
		printf("Minimum age must be 18!\n");
		return -1;
	}
	printf("enter number of dose taken: ");
	int doses_ta;
	scanf("%d", &doses_ta);
	if (doses_ta > 2)
	{
		printf("enter 0-2 only!\n");
		return -1;
	}
	int i = 0;
	while (ctzns[i].name[0] != '\0' && i < ctzns_tot)
	{
		i++;
	}
	if (i == ctzns_tot)
	{
		return -1;
	}
	else
	{
		strcpy(ctzns[i].name, name);
		//ctzns[i].name=name;
		strcpy(ctzns[i].gender, gender);
		//ctzns[i].gender=gender;
		ctzns[i].num_doses = doses_ta;
		ctzns[i].YOB = YOB;
		srand(time(0));
		ctzns[i].beneficiary_id = (rand()%(99999-10000+1))+10000;
	}
	return i;
}

int addNewCenter(struct vaccine_centers vc[])
{
	printf("enter center id: \n");
	int center_id;
	scanf("%d", &center_id);
	printf("enter center type: \n");
	char cent_type[15];
	scanf("%s", cent_type);
	printf("enter address: \n");
	char address[50];
	//scanf("%s", address);
	getchar();
	gets(address);
	printf("enter district: \n");
	char district[15];
	scanf("%s", district);
	printf("enter pin code: \n");
	int pin_code;
	scanf("%d", &pin_code);

	char vacc_type[6][11];
	int qty[6];
	int price[6];
	for (int i = 0; i < 6; i++)
	{
		vacc_type[i][0] = '\0';
		qty[i] = -1;
		price[i] = 0;
	}
	for (int j = 0; j < 6; j++)
	{
		printf("enter vaccine type (enter x when done)%d: ", j + 1);
		scanf("%s", vacc_type[j]);
		if (vacc_type[j][0] != 'x')
		{
			printf("enter quantity: ");
			scanf("%d", &qty[j]);
			if (!strcmpi(cent_type, "private"))
			{
				printf("enter price: ");
				scanf("%d", &price[j]);
			}
			else
			{
				price[j] = 0;
				printf("price is 0!\n");
			}
		}
		else
		{
			vacc_type[j][0] = '\0';
			break;
		}
	}

	int i = 0;
	while (vc[i].center_id != 0 && i < vc_tot)
		i++;
	if (i == vc_tot)
		return -1;
	else
	{
		strcpy(vc[i].center_address, address);
		strcpy(vc[i].center_type, cent_type);
		strcpy(vc[i].district, district);
		vc[i].center_id = center_id;
		vc[i].pin_code = pin_code;
		for (int j = 0; vacc_type[j][0] != '\0' && j < 6; j++)
		{
			strcpy(vc[i].vacc_type[j], vacc_type[j]);
			vc[i].price[j] = price[j];
			vc[i].qty[j] = qty[j];
		}
	}
	return i;
}

void EnlistSortedCenters(struct vaccine_centers vc[], int index, int income[])
{
	int key_field, i = 0;
	printf("enter code for key field:\n1: Center Id\n2: District: \n3: PIN Code\n");
	scanf("%d", &key_field);
	if (key_field == 1)
	{
		sortCenterid(vc, 0, index, income);
		while (vc[i].center_id != 0)
		{
			print_vc_rec(vc, i);
			i++;
		}
	}
	else if (key_field == 2)
	{
		sortDistrict(vc, 0, index, income);
		while (vc[i].center_id != 0)
		{
			print_vc_rec(vc, i);
			i++;
		}
	}
	else if (key_field == 3)
	{
		sortPinCode(vc, 0, index, income);
		while (vc[i].center_id != 0)
		{
			print_vc_rec(vc, i);
			i++;
		}
	}
}
void getCenter(struct vaccine_centers vc[])
{
	int x;
	printf("enter code for key field:\n 1: Center Id\n 2: PIN Code: \n3: District\n4: center type\n5: vaccine type\n");
	scanf("%d", &x);

	if (x == 1)
	{
		printf("enter center ID: ");
		int cid;
		scanf("%d", &cid);
		int i = 0;
		while (vc[i].center_id != cid && i < vc_tot && vc[i].center_id != 0)
		{
			i++;
		}
		if (i == vc_tot || vc[i].center_id == 0)
			printf("center not found!\n");
		else
			print_vc_rec(vc, i);
	}
	else if (x == 2)
	{
		printf("enter PIN Code: ");
		int pid;
		scanf("%d", &pid);
		int i = 0;
		while (vc[i].pin_code != pid && i < vc_tot && vc[i].pin_code != -1)
		{
			i++;
		}
		if (vc[i].pin_code == -1 || i == vc_tot)
			printf("center not found!\n");
		else
			print_vc_rec(vc, i);
	}
	else if (x == 3)
	{
		printf("enter district: ");
		char dist[15];
		scanf("%s", dist);
		int i = 0;
		while (vc[i].center_id != 0 && i < ctzns_tot && vc[i].center_id != 0)
		{
			if (!strcmpi(vc[i].district, dist))
				print_vc_rec(vc, i);
			i++;
		}
		printf("done!\n");
	}
	else if (x == 4)
	{
		printf("enter center type: ");
		char ctype[15];
		scanf("%s", ctype);
		int i = 0;
		while (vc[i].center_id != 0 && i < ctzns_tot && vc[i].center_id != 0)
		{
			if (strcmpi(vc[i].center_type, ctype))
				print_vc_rec(vc, i);
			i++;
		}
		printf("done!\n");
	}
	else if (x == 5)
	{
		printf("enter vaccine type: ");
		char vtype[10];
		scanf("%s", vtype);
		int i = 0;
		while (vc[i].center_id != 0)
		{
			int j = 0;
			while (j < 6 && strcmpi(vc[i].vacc_type[j], vtype))
			{
				j++;
			}
			if (j != 6)
				print_vc_rec(vc, i);
			i++;
		}
		printf("done!\n");
	}
}
void BookAppointment(struct citizens ctzns[], struct vaccine_centers vc[], char bookngs[][10], int income[], int cent[])
{
	int bid, cid, i = 0, k = 0, j = 0, l = 0;

	char vtype[15];
	printf("enter beneficiary id: ");
	scanf("%d", &bid);
	while (ctzns[k].beneficiary_id != bid && k < ctzns_tot && ctzns[k].beneficiary_id != 0)
		k++;
	if (bookngs[k][0] == '\0' && k < ctzns_tot && ctzns[k].num_doses < 2 && ctzns[k].beneficiary_id != 0)
	{
		while (vc[l].center_id != 0)
		{
			print_vc_rec(vc, l);
			l++;
		}
		printf("enter center id: ");
		scanf("%d", &cid);
		printf("enter vaccine type: ");
		scanf("%s", vtype);
		while (vc[i].center_id != cid && i < vc_tot && vc[i].center_id != 0)
			i++;
		if (i < vc_tot && vc[i].center_id != 0)
		{
			while (vc[i].vacc_type[j][0] != '\0' && j < 6 && strcmpi(vc[i].vacc_type[j], vtype) && vc[i].qty[j] != -1)
			{
				j++;
			}

			if (j != 6 && vc[i].qty[j] != -1)
			{

				vc[i].qty[j]--;
				print_vc_rec(vc, i);
				income[i] =income[i] + vc[i].price[j];
				strcpy(bookngs[k], vtype);
				cent[k] = cid;
				printf("slot booked!\n");
			}
			else
				printf("booking unsuccessful\n");
		}
		else
			printf("center not found!\n");
	}
	else if (ctzns[k].num_doses == 2)
		printf("2 doses already taken\n");
	else if (ctzns[k].beneficiary_id == 0)
		printf("beneficiary not found!\n");
	else
		printf("Already booked!\n");
}
void CancelAppointment(struct vaccine_centers vc[], struct citizens ctzns[], char bookngs[][10], int cent[], int income[])
{
	int bid, i = 0, k = 0, j = 0;
	printf("enter beneficiary id: ");
	scanf("%d", &bid);
	while (ctzns[k].beneficiary_id != bid && k < ctzns_tot)
		k++;
	if (bookngs[k][0] != '\0' && k < ctzns_tot)
	{
		while (vc[i].center_id != cent[k])
			i++;
		while (strcmpi(vc[i].vacc_type[j], bookngs[k]))
			j++;
		vc[i].qty[j]++;
		income[i] -= vc[i].price[j];
		bookngs[k][0] = '\0';
		cent[k]=0;
		printf("appointment cancelled success!\n");
	}

	else
		printf("No bookings found!\n");
}
void removeBeneficiary(struct citizens ctzns[], struct vaccine_centers vc[], char bookngs[][10], int income[], int cent[], int *ctzns_num)
{
	int bid, i = 0, k = 0, j = 0;
	printf("enter beneficiary id: ");
	scanf("%d", &bid);
	while (ctzns[k].beneficiary_id != bid && k < ctzns_tot)
		k++;
	while (cent[k] != vc[i].center_id && i < vc_tot)
		i++;
	while (strcmp(vc[i].vacc_type[j], bookngs[k]))
		j++;
	income[i] -= vc[i].price[j];
	vc[i].qty[j]++;
	if (k < ctzns_tot)
	{
		ctzns[k].YOB = -1;
		ctzns[k].num_doses = -1;
		ctzns[k].beneficiary_id = 0;
		ctzns[k].name[0] = '\0';
		ctzns[k].gender[0] = '\0';
		bookngs[k][0] = '\0';
		cent[k]=0;

		int l = k + 1;
		while (ctzns[l].beneficiary_id != 0 && l < ctzns_tot)
		{
			struct citizens temp = ctzns[l - 1];
			ctzns[l - 1] = ctzns[l];
			ctzns[l] = temp;
			char temp1[10];
			strcpy(temp1, bookngs[l - 1]);
			strcpy(bookngs[l - 1], bookngs[l]);
			strcpy(bookngs[l], temp1);
			int temp3 = cent[l - 1];
			cent[l - 1] = cent[l];
			cent[l] = temp3;
			l++;
		}
		(*ctzns_num)--;
		printf("beneficiary removed success!\n");
		if (vc[i].center_id != 0)
			printf("Appointment booked at center ID %d has been cancelled!\n", vc[i].center_id);
	}
	else
		printf("No beneficiary found!\n");
}
void removeCenter(struct vaccine_centers vc[], struct citizens ctzn[], int income[], int cent[], char bookngs[][10], int *index)
{
	int cid, i = 0, j = 0;
	printf("enter center ID: ");
	scanf("%d", &cid);
	while (vc[i].center_id != cid && i < vc_tot && vc[i].center_id != 0)
		i++;

	if (i < vc_tot)
	{
		vc[i].center_id = 0;
		vc[i].district[0] = '\0';
		vc[i].pin_code = -1;

		for (int l = 0; l < 6; l++)
		{
			vc[i].price[l] = -1;
			vc[i].qty[l] = -1;
			vc[i].vacc_type[l][0] = '\0';
		}
		income[i] = 0;
		int k = i + 1;
		while (vc[k].center_id != 0 && k < vc_tot)
		{
			struct vaccine_centers temp = vc[k - 1];
			vc[k - 1] = vc[k];
			vc[k] = temp;
			int temp1 = income[k - 1];
			income[k - 1] = income[k];
			income[k] = temp1;
			k++;
		}
		(*index)--;
		printf("center removed!\n");
		while (j < ctzns_tot && cent[j] != 0)
		{
			if (cent[j] == cid)
			{
				bookngs[j][0] = '\0';
				cent[j] = 0;

				printf("appointment cancelled for beneficiary ID: %d\n", ctzn[j].beneficiary_id);
			}
			j++;
		}
	}
	else
	{
		printf("no center found!\n");
	}
}
void updateBeneficiaryInfo(struct citizens ctzn[], struct vaccine_centers vc[],int cent[], char bookngs[][10],int income[])
{
	int bid, i = 0, j = 0;
	printf("enter beneficiary ID: ");
	scanf("%d", &bid);
	while (ctzn[i].beneficiary_id != bid && i < ctzns_tot && ctzn[i].beneficiary_id!=0)
		i++;
	if (i < ctzns_tot && ctzn[i].beneficiary_id!=0)
	{
		int key;
		
		while (key != 0)
		{
			printf("enter code for the field to update\n1 - name\n2 - gender\n3 - YOB\n4 - Number of doses\n0: done\n");
			scanf("%d", &key);
			if (key == 1)
			{
				printf("enter name: ");
				char name[50];
				scanf("%s", name);
				strcpy(ctzn[i].name, name);
				printf("updated!\n");
			}
			else if (key == 2)
			{
				printf("enter gender: ");
				char gender[15];
				scanf("%s", gender);
				strcpy(ctzn[i].gender, gender);
				printf("updated!\n");
			}
			else if (key == 3)
			{
				printf("enter YOB: ");
				int YOB;
				scanf("%d", &YOB);
				ctzn[i].YOB = YOB;
				printf("updated!\n");
			}
			else if (key == 4)
			{
				printf("enter number of doses taken: ");
				int doses;
				scanf("%d", &doses);
				if (doses == 2 && bookngs[i][0] != '\0')
				{
					printf("appointment booked at center ID %d will be cancelled since 2 doses taken! Confirm? enter y or n: ", cent[i]);
					getchar();
					char conf;
					scanf("%c", &conf);
					if (conf=='y')
					{
						int l=0;
						while(vc[l].center_id!=cent[i])
							l++;
						
						while (strcmpi(vc[l].vacc_type[j], bookngs[i]))
							j++;
						vc[i].qty[j]++;
						income[l] -= vc[l].price[j];
						bookngs[i][0] = '\0';
						ctzn[i].num_doses = doses;
						//printf("%d\n",ctzn[i].num_doses);
						printf("appointment cancelled success!\n");
						printf("updated!\n");
					}
					else
					{
						printf("No updation made!\n");
					}
				}
				else
				{
					ctzn[i].num_doses = doses;
					printf("updated!\n");
				}
			}
		}
		printf("info updated on beneficiary ID %d\n",ctzn[i].beneficiary_id);
	}
	else
		printf("No beneficiary found\n");
}
void updateCenterInfo(struct vaccine_centers vc[])
{
	int cid, i = 0, j = 0;
	printf("enter center ID: ");
	scanf("%d", &cid);
	while (vc[i].center_id != cid && i < vc_tot)
		i++;

	if (i < vc_tot)
	{
		int key;
		while (key != 0)
		{
			printf("enter code for the field to update\n1 - Address\n2 - District\n3 - PIN Code\n4 - vaccine type\n5 - center type\n0 - done\n");
			scanf("%d", &key);
			if (key == 1)
			{
				printf("enter Address: ");
				char address[50];
				scanf("%s", address);
				strcpy(vc[i].center_address, address);
				printf("updated!");
			}
			else if (key == 2)
			{
				printf("enter district: ");
				char district[15];
				scanf("%s", district);
				strcpy(vc[i].district, district);
				printf("updated!");
			}
			else if (key == 3)
			{
				printf("enter PIN Code: ");
				int pin;
				scanf("%d", &pin);
				vc[i].pin_code = pin;
				printf("updated!");
			}
			else if (key == 5)
			{
				printf("enter center type: ");
				char ctype[15];
				scanf("%s", ctype);
				strcpy(vc[i].center_type, ctype);
				printf("updated!");
			}
			else if (key == 4)
			{
				int k = 0;
				char v_key[10];
				v_key[0] = '\0';
				while (vc[i].vacc_type[k][0] != '\0' && k < 6)
				{
					printf("vaccine %d: %s, ", k + 1, vc[i].vacc_type[k]);
					printf("quantity : %d, ", vc[i].qty[k]);
					printf("price: %d \n", vc[i].price[k]);
					k++;
				}
				while (v_key[0] != 'x')
				{
					printf("enter vaccine type(enter x when done): ");
					scanf("%s", v_key);
					int l = 0;
					while (strcmpi(vc[i].vacc_type[l], v_key) && l < 6 && vc[i].vacc_type[l][0]!='\0')
						l++;
					if (l != 6 && vc[i].vacc_type[l][0]!='\0')
					{
						if (!strcmpi(vc[i].center_type, "private"))
						{
							printf("enter price: ");
							scanf("%d", &vc[i].price[l]);
						}
						printf("enter quantity: ");
						scanf("%d", &vc[i].qty[l]);
					}
				}
				printf("updated!\n");
			}
			printf("Info updated on Center ID %d\n", cid);
		}
	}
	else
		printf("No Center found\n");
}
void MaxIncomeCenter(struct vaccine_centers vc[], int income[])
{
	int i = 0, max = 0, index[vc_tot], k = 0;
	for (int j = 0; j < vc_tot; j++)
		index[j] = -1;
	while (vc[i].center_id != 0)
	{
		if (income[i] > max)
		{
			for (int j = 0; j < vc_tot && index[j] != -1; j++)
				index[j] = -1;
			max = income[i];
			k = 0;
			index[k] = i;
		}
		else if (income[i] == max && max!=0)
		{
			k++;
			index[k] = i;
		}
		i++;
	}
	if (max == 0)
		printf("no bookings made yet in private centers!\n");
	else
	{
		int i = 0;
		while (index[i] != -1)
		{
			print_vc_rec(vc, index[i]);
			printf("%d\n",income[index[i]]);
			i++;
		}
	}
}
void VaccinceAvailabilityReport(struct vaccine_centers vc[])
{
	//sortDistrict(vc);
	int i = 0;
	while (vc[i].center_id != 0)
	{
		int j = 0;
		printf("center ID: %d\n",vc[i].center_id);
		while (vc[i].vacc_type[j][0] != '\0' && j < 6)
		{
			printf("vaccine %d: %s, ", j + 1, vc[i].vacc_type[j]);
			printf("quantity : %d, \n", vc[i].qty[j]);
			j++;
		}
		i++;
	}
}
void DistrictReport(struct vaccine_centers vc[], char bookngs[][10], int income[],int dist_bookngs,int vacc_cent_num,int cent[])
{
	int i = 1;
	char district[15];
	sortDistrict(vc,0,vacc_cent_num,income);
	strcpy(district, vc[0].district);
	while (vc[i].center_id != 0)
	{
		int j=0;
		while(j<vc_tot && vc[i].center_id!=0)
		{
			if(vc[i].center_id==cent[j])
				dist_bookngs++;
			j++;
		}
		if (strcmpi(vc[i].district, district))
		{
			printf("number of vaccines booked in %s is : %d\n", vc[i - 1].district, dist_bookngs);
			strcpy(district, vc[i].district);
			dist_bookngs=0;
		}
		i++;
	}
	printf("number of vaccines booked in %s is : %d", vc[i - 1].district, dist_bookngs);
		
}
void SeniorCitizenIntersection(struct vaccine_centers vc[],struct citizens ctzns[],int cent[], char boonkgs[][10])
{
	printf("enter people greater that 60 who booked first dose(enter x when done!)\n");
	int list1[ctzns_tot],list2[ctzns_tot],i=0,j=0,l1=0,l=0,c_list[ctzns_tot];
	for(int k=0;k<ctzns_tot;k++)
	{
		list1[k]=-1;
		list2[k]=-1;
		c_list[k]=-1;
	}
	while(list1[i]!=0)
	{
		scanf("%d",&list1[i]);
		while(ctzns[l1].beneficiary_id!=list1[i] && ctzns[l1].beneficiary_id!=0 && l1<ctzns_tot)
			l1++;
		if((curr_year- ctzns[l1].YOB>60) && l1<ctzns_tot && ctzns[l1].beneficiary_id!=0 && boonkgs[l1][0]!='\0' && list1[i]!=0)
		{
			i++;
			
		}
		else if(ctzns[l1].beneficiary_id==0 && l1>ctzns_tot && list1[i]!=0)
		{
			printf("beneficiary not found!\n");
		}
		else if((curr_year-ctzns[l1].YOB)<60 && list1[i]!=0)
			printf("beneficiary under 60\nenter another!\n");
		else if(boonkgs[l1][0]=='\0' && list1[i]!=0)
			printf("noo bookings found!\nenter another!\n");
		l1=0;
			
	}
	printf("enter list of people greater than 60 who booked second dose(enter 0 when done!)\n");
	l1=0;
	while(list2[j]!=0)
	{
		scanf("%d",&list2[j]);
		while(ctzns[l1].beneficiary_id!=list2[j] && ctzns[l1].beneficiary_id!=0 && l1<ctzns_tot && list1[j]!=0)
			l1++;
		if((curr_year- ctzns[l1].YOB>60) && l1<ctzns_tot && ctzns[l1].beneficiary_id!=0 && boonkgs[l1][0]!='\0')
		{
			j++;
			
		}
		else if(ctzns[l1].beneficiary_id==0 && l1>ctzns_tot && list1[j]!=0)
		{
			printf("beneficiary not found!\n");
		}
		else if((curr_year-ctzns[l1].YOB)<60 && list1[j]!=0)
			printf("beneficiary under 60\nenter another!\n");
		else if(boonkgs[l1][0]=='\0' && list1[j]!=0)
			printf("noo bookings found!\nenter another!\n");
			
		l1=0;
	}
	int a=0,b=0,c=0;
	while(list1[a]!=0)
	{
		while(list2[b]!=0)
		{
			if(list2[a]==list1[b])
			{
				if(cent[a]==cent[b])
				{
					c_list[c]= list2[b];
					c++;
				}
					
			}
			b++;
		}
		a++;
	}
	if(c==0)
		printf("No beneficiary found!\n");
	else
	{
		for(int i=0;i<c;i++)
			printf("%d",c_list[i]);
	}

}
int main()
{
	int ctzns_num = 0, vacc_cent_num = 0, income[vc_tot], dist_bookngs = 0, cent[ctzns_tot];
	char bookngs[ctzns_tot][10];
	for (int i = 0; i < ctzns_tot; i++)
	{
		bookngs[i][0] = '\0';
		income[i] = 0;
	}

	struct citizens ctzns[ctzns_tot];
	struct vaccine_centers vc[vc_tot];
	initialize(ctzns, vc);
	int key = -1;
	printf("enter key for following functions: \n");
	printf("1 - add beneficiary\n2 - add center\n3 - list sorted centers\n4 - get center\n5 - Book Appointment\n6 - Cancel Appointment\n7 - remove beneficiary\n8 - remove center\n9 - update beneficiary info\n10 - update center info\n11 - max income center\n12 - Vaccine availability\n13 - District report\n14: senior citizen intersection\n0 - exit\n");

	while (key != 0)
	{
		scanf("%d", &key);
		if (key == 1)
		{
			ctzns_num = addNewBeneficiary(ctzns);
			if (ctzns_num + 1)
			{
				printf("beneficiary added successfully!\n Beneficiary ID: %d\n", ctzns[ctzns_num].beneficiary_id);
				sortBeneficiaryid(ctzns,0,ctzns_num);
			}
				
			else
				printf("booking unsuccessfull!\n");
		}
		if (key == 2)
		{
			vacc_cent_num = addNewCenter(vc);
			if (vacc_cent_num + 1)
			{
				printf("center added succesfully!\n");
				sortCenterid(vc,0,vacc_cent_num,income);
			}
				
			else
				printf("unsuccesfull!\n");
		}

		if (key == 3)
			EnlistSortedCenters(vc, vacc_cent_num, income);
		if (key == 4)
			getCenter(vc);
		if (key == 5)
			BookAppointment(ctzns, vc, bookngs, income, cent);
		if (key == 6)
			CancelAppointment(vc, ctzns, bookngs, cent, income);
		if (key == 8)
			removeCenter(vc, ctzns, income, cent, bookngs, &vacc_cent_num);
		else if (key == 7)
			removeBeneficiary(ctzns, vc, bookngs, income, cent, &ctzns_num);
		else if (key == 9)
			updateBeneficiaryInfo(ctzns,vc, cent, bookngs,income);
		else if (key == 10)
			updateCenterInfo(vc);
		else if (key == 11)
			MaxIncomeCenter(vc, income);
		else if (key == 12)
			VaccinceAvailabilityReport(vc);
		else if (key == 13)
			DistrictReport(vc, bookngs, income,dist_bookngs,vacc_cent_num,cent);
		else if(key==14)
			SeniorCitizenIntersection(vc,ctzns,cent,bookngs);
	}
	return 0;
}