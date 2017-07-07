#include "header.h"

// ������ ���������Ϸκ��� �����͸� �Է¹޴� �Լ�
void getDataFromFile(item *&arr, int &totalNum, int &capacity)
{
	ifstream fin;
	int t;

	// fin �Լ��� �̿��Ͽ� �ʿ��� �������� test.txt���� �о��(���� ���� ���)
	fin.open("test.txt");
	if(!fin.fail())
		cout << "connection complete"<< endl;

	fin >> capacity;
	fin >> totalNum;

	arr = new item[totalNum+1]; // arr�� totalNum+1��ŭ ���� �Ҵ��Ͽ� ����

	for(int i=1; i<=totalNum; i++)
	{
		fin >> t;
		arr[i].setNum(t);
		fin >> t;
		arr[i].setWeight(t);
		fin >> t;
		arr[i].setProfit(t);
	}
	
	// item�� ������ ������ ũ�⸦ ���
	cout << "num of item : " << totalNum << ", size of bag : " << capacity << endl;
	fin.close();

	return;
}

// GA�� �����ϱ� �� ���� �ʱ�ȭ : �������� �ظ� ������ ��, ���� ǰ���� ��ȯ
int initial(item *&vi, bool *&sol, int totalNum, int capacity)
{
	int i = 0;
	int cap = 0;
	int prof = 0;
	
	while(1)
	{
		cap = 0;
		prof = 0;
		for(i=1; i<=totalNum; i++)
		{
			sol[i] = rand() % 2;
			if(sol[i])
			{
				cap += vi[i].getWeight();
				prof += vi[i].getProfit();
				if(cap>capacity)
				{
					i--;
					break;
				}
			}
		}
		if(i >= totalNum)
			break;
	}

	return prof;
}

// ���� ���ռ�, ǰ���� ���� �� ���� ǰ���� ��ȯ, �������� ���� ��� 0�� ��ȯ
int evalSol(item *&vi, bool *&sol, int capacity, int totalNum)	
{
	int i=0;
	int prof = 0;
	int cap = 0;
	for(i=1; i<=totalNum; i++)
		if(sol[i])
		{
			cap += vi[i].getWeight();
			prof += vi[i].getProfit();
			if(cap>capacity)
				return 0;
		}
	return prof;
}

// ���� �Լ�, single crossover�� NC��ŭ ��. ����, ���� ���θ� ��ȯ
int cross(item *&vi, bool *&sol1, bool *&sol2, bool *&newSol1, bool *&newSol2, int newSolVal1, int newSolVal2, int totalNum, int capacity)		
{
	int *cut = new int[NC+1];;
	int i=0, j=0, k=0;
	int cap1 = 0, cap2 = 0;
	int prof1 = 0, prof2 = 0;

	for(i=0; i<=NC; i++)
	{
		cut[i] = rand()%totalNum+1;
		for(j=0; j<i; j++)
			if(cut[i] == cut[j])
			{
				i--;
				break;
			}
	}

	for(i=1; i<=totalNum; i++)
	{
		if(k%2)
		{
			newSol1[i] = sol2[i];
			newSol2[i] = sol1[i];
		}
		else
		{
			newSol1[i] = sol1[i];
			newSol2[i] = sol2[i];
		}
		if(cut[k] == i)
			k++;
		prof1 += newSol1[i] * vi[i].getProfit();
		prof2 += newSol2[i] * vi[i].getProfit();
		cap1 += newSol1[i] * vi[i].getWeight();
		cap2 += newSol2[i] * vi[i].getWeight();
		
		if(cap1 > capacity || cap2 > capacity)
			return 0;
	}
	newSolVal1 = prof1;
	newSolVal2 = prof2;
	return 1;
}

// �귿 ����� selection. ���õ� ���� ��ȣ�� ��ȯ
int selection(int *&solVal, int sumPro)				
{
	int i=0, j=1;
	double ranNum = 0;

	double prob = 0;

	while(j)
	{
		ranNum = (double)((double)(rand()%100) / 100);
		for(i=1; i<=POP; i++)
		{
			prob = (double)((double)solVal[i] / (double)sumPro);
			ranNum -= prob;
			if(ranNum <= 0)
			{
				j=0;
				break;
			}
		}
	}

	return i;
}

// ���� �Լ�. Ȯ���� ���� ��� ���� ���� ����
void mutation(bool *&sol, int num)
{
	sol[num] = ~sol[num];
}

// �ظ� �������� ������ִ� �Լ�
void showSol(bool *&sol, int totalNum)
{
	int i=0;
	for(i=1; i<=totalNum; i++)
		cout << sol[i];
	cout << endl;
}

// sol2 ���� ���� sol1���� �������ִ� �Լ�, size�� ���� ����.
void copySol(bool *&sol1, bool *&sol2, int size)
{
	int i=0;
	for(i=1; i<=size; i++)
		sol1[i] = sol2[i];
}

// ���� ǰ�� �迭�� �޾Ƽ� ��� ǰ���� ��հ��� ������
double getAver(int *&solVal, int totalNum)
{
	int i=0;
	int sum = 0;
	double aver = 0;
	for(i=1; i<=POP; i++)
	{
		sum += solVal[i];
	}
	aver = (double)sum / POP;

	return aver;
}

// item class�� get, set �Լ� ����
int item::getNum()
{
	return num;
}
int item::getProfit()
{
	return profit;
}
int item::getWeight()
{
	return weight;
}
void item::setNum(int newNum)
{
	num = newNum;
}
void item::setProfit(int newProfit)
{
	profit = newProfit;
}
void item::setWeight(int newWeight)
{
	weight = newWeight;
}