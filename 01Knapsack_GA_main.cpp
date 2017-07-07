#include "header.h"

int main(void)
{
	int totalNum = 0;				// ���� ����
	int capacity = 0;				// ������ �뷮
	int sumPro = 0;					// ���� ���� �ص��� ��� ǰ���� ��
	int i, j, k;					
	item *vi = 0;					// �����۵��� ������ �迭
	int minPro = INT_MAX;			// ��� �ص��� ��Ʋ�� ���� ���� ���� ǰ���� ����(�������� �� ����)
	int maxPro = -1;					// ��� �ص��� ��Ʋ�� ���� ���� ���� ǰ���� ����
	int maxProNum = 0;				// ��� �ص��� ��Ʋ�� ���� ���� ���� ǰ���� ������ ���� ��ȣ
	int maxProGen = 0;				// ��� �ص��� ��Ʋ�� ���� ���� ���� ǰ���� ������ �ذ� ������ ������ ��ȣ
	int aver = 0;					// �� ���뺰 ǰ���� ���
	int genBest = -1;				// �� ���뺰 �ְ� ǰ��
	bool *bestSol;					// ��� �ص��� ��Ʋ�� ���� ���� ���� ǰ���� ������ �ظ� �����ϴ� �迭

	srand(time(NULL));				// ������ ���� �ð� �Լ� ����

	getDataFromFile(vi, totalNum, capacity);			// ���Ϸκ��� ������ ��������

	bool **sol = new bool*[POP + 1];			// �� �迭
	bool **solMade = new bool*[POP + 1];		// ������ �� �迭
	for(i = 0; i<=totalNum+1; i++)				// 2���� �� �迭 ����
	{
		sol[i] = new bool[totalNum+1];
		solMade[i] = new bool[totalNum+1];
	}
	int *solVal = new int[POP + 1];			// �� ǰ�� �迭
	int *solMadeVal = new int[POP + 1];		// ������ �� ǰ�� �迭
	bestSol = new bool[totalNum+1];			// ���� ���� �� �迭

	clock_t startTime=clock();

	for(i=1; i<=POP; i++)
	{
		solVal[i] = initial(vi, sol[i], totalNum, capacity);
		sumPro += solVal[i];				
	}

	int round=0;

	// NR��ŭ ROUND �ݺ�
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
			// ������ �������� �����Ͽ� �� ������ �����ڵ��� ����(mutation)��Ŵ
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

		// **************  ���� ���� �� maxPro ã��  **********************//
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
	cout << "CPU clock �� : " << finalTime-startTime << endl;
	cout << "�̻����� 12141768 �ֿ����� ������Ʈ�����ϴ�." << endl;

	delete [] solVal;
	delete [] solMadeVal;
	delete [] bestSol;

	return 0;
}