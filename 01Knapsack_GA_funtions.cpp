#include "header.h"

// 지정된 데이터파일로부터 데이터를 입력받는 함수
void getDataFromFile(item *&arr, int &totalNum, int &capacity)
{
	ifstream fin;
	int t;

	// fin 함수를 이용하여 필요한 변수들을 test.txt에서 읽어옴(성공 여부 출력)
	fin.open("test.txt");
	if(!fin.fail())
		cout << "connection complete"<< endl;

	fin >> capacity;
	fin >> totalNum;

	arr = new item[totalNum+1]; // arr를 totalNum+1만큼 동적 할당하여 선언

	for(int i=1; i<=totalNum; i++)
	{
		fin >> t;
		arr[i].setNum(t);
		fin >> t;
		arr[i].setWeight(t);
		fin >> t;
		arr[i].setProfit(t);
	}
	
	// item의 개수와 가방의 크기를 출력
	cout << "num of item : " << totalNum << ", size of bag : " << capacity << endl;
	fin.close();

	return;
}

// GA를 가동하기 전 최초 초기화 : 랜덤으로 해를 지정한 후, 해의 품질을 반환
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

// 해의 적합성, 품질을 평가한 후 해의 품질을 반환, 부적합한 값일 경우 0을 반환
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

// 교차 함수, single crossover를 NC만큼 함. 성공, 실패 여부를 반환
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

// 룰렛 방식의 selection. 선택된 해의 번호를 반환
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

// 변이 함수. 확률에 따라 모든 값에 대해 적용
void mutation(bool *&sol, int num)
{
	sol[num] = ~sol[num];
}

// 해를 이진수로 출력해주는 함수
void showSol(bool *&sol, int totalNum)
{
	int i=0;
	for(i=1; i<=totalNum; i++)
		cout << sol[i];
	cout << endl;
}

// sol2 해의 값을 sol1으로 복사해주는 함수, size는 해의 길이.
void copySol(bool *&sol1, bool *&sol2, int size)
{
	int i=0;
	for(i=1; i<=size; i++)
		sol1[i] = sol2[i];
}

// 해의 품질 배열을 받아서 모든 품질의 평균값을 내어줌
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

// item class의 get, set 함수 정의
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