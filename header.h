#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define PC 0.85			// ���� Ȯ��(percentage of crossover)
#define PM 0.0001		// ���� Ȯ��(percentage of mutation)
#define POP 100			// �α� ��(population)
#define NC 3			// ũ�ν����� ����Ʈ ��(number of crossover)
#define NR 100			// �� ���� ��(number of round)

class item{				// �������� ����, ��ġ�� ��� class
private:
	int num;
	int weight;
	int profit;

public:
	int getNum();
	int getWeight();
	int getProfit();
	void setNum(int newNum);
	void setWeight(int newWeight);
	void setProfit(int newProfit);
};	

void getDataFromFile(item *&arr, int &totalNum, int &capacity);	
int initial(item *&vi, bool *&sol, int totalNum, int capacity);		
int evalSol(item *&vi, bool *&sol, int capacity, int totalNum);		
int cross(item *&vi, bool *&sol1, bool *&sol2, bool *&newSol1, bool *&newSol2, int newSolVal1, int newSolVal2, int totalNum, int capacity);		
int selection(int *&solVal, int sumPro);								
void mutation(bool *&sol, int num);									
void showSol(bool *&sol, int totalNum);								
void copySol(bool *&sol1, bool *&sol2, int size);					
double getAver(int *&solVal, int totalNum);							