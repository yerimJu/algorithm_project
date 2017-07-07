#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define PC 0.85			// 교차 확률(percentage of crossover)
#define PM 0.0001		// 변이 확률(percentage of mutation)
#define POP 100			// 인구 수(population)
#define NC 3			// 크로스오버 포인트 수(number of crossover)
#define NR 100			// 총 라운드 수(number of round)

class item{				// 아이템의 무게, 가치를 담는 class
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