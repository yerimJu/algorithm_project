#include <iostream>
#include <ctime>
#include <cstdio>
using namespace std;

int print_Karray(int* price, int* weight, int** K, int N, int W);
int main(void) {
	int i, w, selected, unselected;
	int W, N, temp;
	int **K; // K�� ���߹迭�̹Ƿ� ���� �Ҵ� ����� ���� double pointer ����
	int *price, *weight; // price, weight�� ���� �Ҵ��� ���� pointer�� ����

	//test.txt���� freopen�Լ��� �̿��Ͽ� �ʿ��� ������ ����
	freopen("test.txt","r",stdin);
	cin >> W >> N;
	K=new int*[N+1];
	price=new int[N+1];
	weight=new int[W+1];

	for (i=0;i<=N;i++) {
		K[i]=new int[W+1];
	}
	for (i=1;i<=N;i++) {
		cin >> temp >> weight[i] >> price[i];
	}

	// ������ ���� clock ����
	clock_t startTime=clock();

	// 0��° ��� 0��° ���� 0���� ä����(�ʱⰪ ����)
	for (i = 0; i <= N; i++)
		K[i][0] = 0;
	for (w = 0; w <= W; w++)
		K[0][w] = 0;

	// K�迭�� ���ϴ� 2�� for loop ����.
	for (i = 1; i <= N; i++) {
		for (w = 1; w <= W; w++) {
			// i��° item�� ���濡 ���� �� ���� ��
			if (weight[i]<=w) {
				selected = K[i - 1][w - weight[i]] + price[i]; // i��° item�� �������� ���� ��ġ
				unselected = K[i - 1][w]; // i��° item�� �������� �ʾ��� ���� ��ġ
				K[i][w] = (selected > unselected ? selected : unselected); // �� ��ġ �߿� ū ���� �����Ͽ� K��Ŀ� ����
				// i��° item�� ���濡 ���� �� ���� ��
			} else K[i][w] = K[i - 1][w];
		}
	}

	cout << "N is " << N << ", W is " << W << endl;
	// K array�� recursion�� �̿��Ͽ� ����ϴ� �Լ� ����
	print_Karray(price,weight,K,N,W);
	
	// �Լ� ������ ������ ���� clock ����
	clock_t finalTime=clock();

	cout << "The best price is " << K[N][W] << endl;
	cout << "CPU clock �� : " << finalTime-startTime << endl;
	cout << "�̻� 12141768 �ֿ����� ������Ʈ�����ϴ�. " << endl;

	return 0;
}

int print_Karray(int* price, int* weight, int** K, int N, int W) {
	// item������ 0�̰ų� ������ ���԰� 0�����̸� recursion �ߴ�
	if (N==0 || W<=0) return 0;
	// item������ 1���̸� �� �迭�� ���� ����ϰ� recursion �ߴ�
	if (N==1) { 
		cout <<  "K[" << N << "][" << W << "] = " <<  K[N][W] << endl;
		return 0;
	}

	// ��ȭ�� ���
	cout << "K[" << N << "][" << W << "] = max(" << "K[" << N-1 << "][" << W << "], ";
	cout << price[N] << "+K[" << N-1 << "][" << W-weight[N-1] << "]) = ";
	cout << "max(" << K[N-1][W] << "," << price[N] << "+" << K[N-1][W-weight[N-1]] << ")=" << K[N][W] << endl;
	
	// ���� K�迭�� ���� ���� ���� ������ recursion�� �ش�.
	if (weight[N-1]>W) return print_Karray(price,weight,K,N-1,W);
	else {
		if (price[N-1]+K[N-1][W-weight[N-1]] > K[N-1][W])
			return print_Karray(price,weight,K,N-1,W-weight[N-1]);
		else return print_Karray(price,weight,K,N-1,W);
	}
}
