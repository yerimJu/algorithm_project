#include "header.h"

int main(void)
{
	int totalNum = 0;				// 해의 길이
	int capacity = 0;				// 가방의 용량
	int sumPro = 0;					// 현재 세대 해들의 모든 품질의 합
	int i, j, k;					
	item *vi = 0;					// 아이템들을 저장할 배열
	int minPro = INT_MAX;			// 모든 해들을 통틀어 가장 낮은 값의 품질을 저장(부적합한 해 제외)
	int maxPro = -1;					// 모든 해들을 통틀어 가장 높은 값의 품질을 저장
	int maxProNum = 0;				// 모든 해들을 통틀어 가장 높은 값의 품질을 가지는 해의 번호
	int maxProGen = 0;				// 모든 해들을 통틀어 가장 높은 값의 품질을 가지는 해가 생성된 세대의 번호
	int aver = 0;					// 각 세대별 품질의 평균
	int genBest = -1;				// 각 세대별 최고 품질
	bool *bestSol;					// 모든 해들을 통틀어 가장 높은 값의 품질을 가지는 해를 저장하는 배열

	srand(time(NULL));				// 랜덤을 위한 시간 함수 설정

	getDataFromFile(vi, totalNum, capacity);			// 파일로부터 데이터 가져오기

	bool **sol = new bool*[POP + 1];			// 해 배열
	bool **solMade = new bool*[POP + 1];		// 유전된 해 배열
	for(i = 0; i<=totalNum+1; i++)				// 2차원 해 배열 생성
	{
		sol[i] = new bool[totalNum+1];
		solMade[i] = new bool[totalNum+1];
	}
	int *solVal = new int[POP + 1];			// 해 품질 배열
	int *solMadeVal = new int[POP + 1];		// 유전된 해 품질 배열
	bestSol = new bool[totalNum+1];			// 가장 좋은 해 배열

	clock_t startTime=clock();

	for(i=1; i<=POP; i++)
	{
		solVal[i] = initial(vi, sol[i], totalNum, capacity);
		sumPro += solVal[i];				
	}

	int round=0;

	// NR만큼 ROUND 반복
	for(round=1; round<=NR; round++)				
	{
		genBest = -1;

		// **************  selection & crossover  *************************//

		for(i=1; i<POP; i+=2)
		{
			j = selection(solVal, sumPro);
			k = selection(solVal, sumPro);
			if(rand()%100 <= NR*100)
				k = cross(vi, sol[j], sol[k], solMade[i], solMade[i+1], solMadeVal[i], solMadeVal[i+1], totalNum, capacity);
			else
			{
				i-=2;
				continue;
			}
			if(k == 0)
				i -= 2;
		}

		// **************  mutation  *************************//

		for(i=1; i<=POP; i++)
		{
			bool *newSolMade = new bool[totalNum];

			copySol(newSolMade, solMade[i], totalNum);
			// 임의의 지점들을 선택하여 그 영역의 유전자들을 변이(mutation)시킴
			for(j=1; j<=totalNum; j++)
				if(rand()%100 <= (double)PM*100)
					mutation(newSolMade, j);
			solMadeVal[i] = evalSol(vi, newSolMade, capacity, totalNum);
			if(solMadeVal[i] == 0)
			{
				i--;
				continue;
			}
			else
				solMade[i] = newSolMade;
		}

		// **************  세대 교차 및 maxPro 찾기  **********************//
		sumPro = 0;

		for(i=1; i<=POP; i++)
		{
			copySol(sol[i], solMade[i], totalNum);
			solVal[i] = solMadeVal[i];
			sumPro += solVal[i];

			if(solVal[i] > maxPro)
			{
				maxPro = solVal[i];
				maxProNum = i;
				copySol(bestSol, sol[i], totalNum);
				maxProGen = round;
			}
			if(solVal[i] > genBest)
				genBest = solVal[i];
		}

		aver = getAver(solVal, totalNum);

		cout << round << "th generation's average profit : " << aver << ", max profit : " << genBest << endl;
	}
	

	cout << "best solution's generation : " << maxProGen << endl;
	cout << "best solution's population : " << maxProNum << endl;
	cout << "best solution's profit : " << maxPro << endl;
	cout << "best solution : " << endl;
	showSol(bestSol, totalNum);	

	clock_t finalTime=clock();
	cout << "CPU clock 수 : " << finalTime-startTime << endl;
	cout << "이상으로 12141768 주예림의 프로젝트였습니다." << endl;

	delete [] solVal;
	delete [] solMadeVal;
	delete [] bestSol;

	return 0;
}