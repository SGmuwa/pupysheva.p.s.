#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h>
#include<time.h>

struct Data
{
	double value;
	unsigned long int time;
};

//�������� �������, ������� ��������� ������ � ������ ����� � ��������� �� � ������������ ������. ������������ malloc. 
struct Data * GetFileData(FILE * fp, size_t * count);

// ������� ���������� �������� ��������� search � ����� fp � ������. ����� ������������� fseek � ������ �����. fp - ��������� �� ����, � ������� ������ �����, search - ������� ������ � �����.
size_t SearchInFile(FILE * fp, char search);

//�������� ������� ��� ������������ ��������
void SWAP(struct Data *a, struct Data *b);

//�������� ������� ������� ����������
void QuickSort(struct Data * SFF, int left, int right);

int main(void) {
	double T;//float
	unsigned int i, imin, imax;
	double number;
	struct tm m_time;
	unsigned long int datemin, datemax;
	size_t count = 0;
	FILE *fp = NULL;
	fp = fopen("laba1_1.csv", "r");
	struct Data * SFF = GetFileData(fp, &count);// ������������� ��������� ���� � ������ �������, ��������� ��� ���������� � ���������, scan from file=SFF 

	T = clock();
	QuickSort(SFF, 0, count-1);
	T = (clock()-T)/ CLOCKS_PER_SEC;//T = (clock()-T)/ (double)CLOCKS_PER_SEC;

	//���� ����������� �� ���������� ����� �� ����� 0, ������� ���, � ���� �����, �������, ��� ��� - ����� 0.001 �������
	if (T != 0) printf("Estimated time to quicksort:  %.3f sec\n", T);//%lf
	else printf("Estimated time to quicksort: <0.001 sec\n");
							
							 
	//����� ���������������� �������
	for (i = 0; i < count; i++) 
		printf("%lu %.9lf\n", SFF[i].time, SFF[i].value);
	
	//������� ���� 1 ������ 1980 ���� � ������ unix timestamp
	m_time.tm_sec = 0; m_time.tm_min = 0; m_time.tm_hour = 0;
	m_time.tm_mday = 1; m_time.tm_mon = 0; m_time.tm_year = 80;
	datemin = mktime(&m_time);

	//������� ���� 31 ������� 1984 ���� � ������ unix timestamp
	m_time.tm_sec = 0; m_time.tm_min = 0; m_time.tm_hour = 0;
	m_time.tm_mday = 31; m_time.tm_mon = 11; m_time.tm_year = 84;
	datemax = mktime(&m_time);

	printf("%lu, %lu\n", datemin, datemax);

	//����� ������������ �������� ���������� �������� �� ������ � 1 ������ 1980 ���� �� 31 ������� 1984 ����.
	for (i = 0; i < count; i++) {
		if (SFF[i].time > datemin) {
			imin = i;
			number = SFF[imin].value;
			break;
		}
	}
	for (i = 0; i < count; i++) 
		if (SFF[i].time<datemax)
			imax = i;
		else break;
	
	for (i = imin; i<=imax; i++) 
		if (SFF[i].value<=number) number = SFF[i].value;
	printf("The smallest number between 1 Jan 1980 and 31 Dec 1984 is %.9lf\n", number);


	fclose(fp);
	getch();
}


//����������� �������, ������� ��������� ������ � ������ ����� � ��������� �� � ������������ ������. ������������ malloc. 
struct Data * GetFileData(FILE * fp, size_t * count)
{
	unsigned int i = 0;
	struct Data * output = NULL;
	*count = SearchInFile(fp, '\n');
	output = (struct Data *) malloc(*count * sizeof(struct Data));
	for (i = 0; i < *count; i++)
	{
		fscanf(fp,"%lf,%lu", &output[i].value, &output[i].time);
	}
	return output;
}


//����������� �������, ������� ������� ���������� �������� ��������� search � ����� fp.
size_t SearchInFile(FILE * fp, char search)
{
	size_t count;
	fseek(fp, 0l, SEEK_SET); //������������ � ������ �����. 0l=(long int)0. 0 ��������, ��� �� �� ������. 
	count = 0;
	while (!feof(fp))
	{
		if (fgetc(fp) == search)
			count++;
	}
	fseek(fp, 0l, SEEK_SET);//������������ � ������ ����� 
	return count;
}


//����������� ������� ��� ������������ ��������
void SWAP(struct Data *a, struct Data *b) {
	struct Data tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


//����������� ������� ������� ����������
void QuickSort(struct Data * SFF, int left, int right) {
	
	int i, last;
	if (left >= right)//���� ������ ���� ��������� ����������� �� �����
		return;
	SWAP(&SFF[left], &SFF[(left + right) / 2]);//������� ������� ��������������� ��������
	last = left;
	for (i = left + 1; i <= right; i++)
		if (SFF[i].time < SFF[left].time) {
			SWAP(&SFF[++last], &SFF[i]);
		}
	SWAP(&SFF[left], &SFF[last]);
	QuickSort(SFF, left, last - 1);
	QuickSort(SFF, last + 1, right);
	return;
}
