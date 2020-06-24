// 8_Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include<cstdlib>
using namespace std;

#define n 3
#define m 3

void Taomang(int Start[][m]);
void Xuatmang(int Start[][m]);
int checkpoint1(int Start[][n]);
int checkpoint2(int Start[][m]);
int toppoint(int Goal[][m], int Start[][m], int a, int b);
int leftpoint(int Goal[][m], int Start[][m], int a, int b);
int rightpoint(int Goal[][m], int Start[][m], int a, int b);
int downpoint(int Goal[][m], int Start[][m], int a, int b);
void Hillclimbing(int Goal[][m], int Start[][m], int t, int l, int r, int d, int a, int b, int& Cg, int c, int A[], int& check1, int& Step);
void Swap(int &x, int &y);
void MangGoal(int Goal[][m]);
int checkGoal(int Start[][m], int Goal[][m]);
void Savestart(int Start[][m], int Save[][m]);
void Randomrestarthillclimbing(int Goal[][m], int Start[][m], int t, int l, int r, int d, int a, int b, int &Cg, int c, int Save[][m], int A[], int B[], int u, int check1, int& Step);
void Kq(int Start[][m], int Goal[][m], int Cg, int Step,int &Giaiduoc);
void Startchange(int Start[][m], int Save[][m]);
void docfile(int Start[][m]);
void RandomMove(int Start[][m], int a, int b, int t, int l, int r, int d);
int Zeropoint(int Start[][m], int Goal[][m], int a, int b);
void Simulatedannealing(int Start[][m], int Goal[][m], int a, int b, int t, int l, int r, int d, int z, int& rd, int& Cg, int& Step, int checkStep, double& tam,int &check2);
void itMove(int Start[][m], int rd, int a, int b, int t, int l, int r, int d,int &checkStep);
int check(int x, int b[]);
void RandomMang(int Start[][m], int Goal[][m], int &t, int &l, int &r, int &d, int &a, int &b);
//void NewforStart(int New[][m], int Start[][m], int Goal[][m], int &a, int &b, int &t, int &l, int &r, int &d);
void Status(int Start[][m], int Goal[][m], int Cg, int& Giaiduoc);
void GoalForStart(int Start[][m]);


void main()
{

	int Start[n][m];
	int New[n][m];
	int Save[n][m];
	unsigned long numberArray = 0;
	int A[5000], B[99];
	int Savehill[n][m], Saverandomhill[n][m], Savesimulatedannealing[n][m];
	int u = 0; int k = 0; int Giaiduoc = 0; int countH = 0; int countRH = 0; int countSA = 0;
	int check1 = 0, checkstate = 1;
	int Step = 0;
	int checkStep = 0;
	double tam = 0; int check2 = 0;	// cho ham Simulated
		/*int A[30];*/
	//tao mang goal
	int Goal[n][m] =
	{ {1, 2, 3}, // hang 1
		{4, 5, 6}, // hang 2
		{7, 8, 0}  // hang 3
	};
	MangGoal(Goal);
	/*Taomang(Start);*/
	docfile(Start);
	Savestart(Start, Save);
	
	//RandomMang(Start);
	
	int Cg = checkGoal(Start, Goal);
	//int cost = 0;
	//int Cl = Checklap(A);
	//HillClimbing
	int c = 9;
	int a = checkpoint1(Start);
	int b = checkpoint2(Start);
	//Chi phí
	int t = toppoint(Goal, Start, a, b);
	int d = downpoint(Goal, Start, a, b);
	int l = leftpoint(Goal, Start, a, b);
	int r = rightpoint(Goal, Start, a, b);
	int z = Zeropoint(Start, Goal, a, b);
	int rd=1;
	//int Cg = checkGoal(Start, Goal);
	//int cost = 0;
	//int Cl = Checklap(A);

	//HillClimbing

	int choose;
	printf("1.Hillclimbing\n");
	printf("2.Random restart hill climbing\n");
	printf("3.Simulated annealing\n");
	printf("4.So sanh 3 thuat toan\n");
	scanf_s("%d", &choose);
	while (choose < 1 && choose>4)
	{
		scanf_s("%d", &choose);
		printf("Vui chon lai");
	}
	switch (choose)
	{
		case 1:
			
				srand(time(NULL));
				while (numberArray <=0)
				{
					printf("\nNhap so luong Array dau vao: ");
					scanf_s("%d", &numberArray);
				}
				printf("Array                      Step                      Result\n");
				printf("--------------------------------------------------------------\n");
				Xuatmang(Start);
				for (int i = 0; i < numberArray; i++)
				{
					
					Step = 0;
					
					Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1, Step);
					Kq(Start, Goal, Cg, Step,Giaiduoc);
					printf("\n------------|-|--------------------------|-|---------------------\n");

					Cg = 0;
					if (i < numberArray-1)
					{
						//printf("\nkhac");
						RandomMang(Start,Goal,t,l,r,d,a,b);
						Xuatmang(Start);
						//NewforStart(New, Start, Goal, a, b, t, l, r, d);
					}
				}
				printf("So ket qua giai duoc -------------------------> ");
				printf("%d", Giaiduoc);
				
			break;
		case 2:
			srand(time(NULL));
			while (numberArray <= 0)
			{
				printf("\nNhap so luong Array dau vao: ");
				scanf_s("%d", &numberArray);
			}
			printf("Array                      Step                      Result\n");
			printf("--------------------------------------------------------------\n");
			Xuatmang(Start);
			for (int i = 0; i < numberArray; i++)
			{
				Step = 0;
				Randomrestarthillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, Save, A, B, u, check1, Step);
				Kq(Start, Goal, Cg, Step, Giaiduoc);
				printf("\n------------|-|--------------------------|-|---------------------\n");

				if (i < numberArray -1)
				{
					//printf("\nkhac");
					RandomMang(Start, Goal, t, l, r, d, a, b);
					Xuatmang(Start);
					//NewforStart(New, Start, Goal, a, b, t, l, r, d);
					Savestart(Start, Save);
				}
				
			}
			printf("So ket qua giai duoc -------------------------> ");
			printf(" %d", Giaiduoc);
			break;
		case 3:
			srand(time(NULL));
			while (numberArray <= 0)
			{
				printf("\nNhap so luong Array dau vao: ");
				scanf_s("%d", &numberArray);
			}
			printf("Array                      Step                      Result\n");
			printf("--------------------------------------------------------------\n");
			Xuatmang(Start);
			for (int i = 0; i < numberArray; i++)
			{
				Step = 0;
				Simulatedannealing(Start, Goal, a, b, t, l, r, d, z, rd, Cg, Step,checkStep,tam,check2);
				Kq(Start, Goal, Cg, Step, Giaiduoc);
				printf("\n------------|-|--------------------------|-|---------------------\n");

				if (i < numberArray - 1)
				{
					//printf("\nkhac");
					RandomMang(Start, Goal, t, l, r, d, a, b);
					Xuatmang(Start);
					//NewforStart(New, Start, Goal, a, b, t, l, r, d);
				}
			}
			printf("\nSo ket qua giai duoc -------------------------> ");
			printf("%d", Giaiduoc);
			break;
		case 4:
			srand(time(NULL));
			while (numberArray <= 0)
			{
				printf("\nNhap so luong Array dau vao: ");
				scanf_s("%d", &numberArray);
			}
			printf("Array          Hillclimbing          Random restart hill climbing          Simulated annealing\n");
			printf("--------------------------------------------------------------------------------------------------\n");
			Xuatmang(Start);
			for (int i = 0; i < numberArray; i++)
			{
				Step = 0;
				Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1, Step);
				Status(Start, Goal, Cg, Giaiduoc);
				countH = countH + Giaiduoc;
				Giaiduoc = 0;
				

				Startchange(Start, Save);
				Randomrestarthillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, Save, A, B, u, check1, Step);
				Status(Start, Goal, Cg, Giaiduoc);
				countRH = countRH + Giaiduoc;
				Giaiduoc = 0;
				
				Startchange(Start, Save);
				Simulatedannealing(Start, Goal, a, b, t, l, r, d, z, rd, Cg, Step, checkStep,tam,check2);
				Status(Start, Goal, Cg, Giaiduoc);
				countSA = countSA + Giaiduoc;
				Giaiduoc = 0;

				printf("\n--------------------------------------------------------------------------------------------------\n");
				if (i < numberArray - 1)
				{
					//printf("\nkhac");
					RandomMang(Start, Goal, t, l, r, d, a, b);
					Xuatmang(Start);
					//NewforStart(New, Start, Goal, a, b, t, l, r, d);
					Savestart(Start, Save);
				}
			}
			printf("So ket qua giai duoc cua Hillclimbing: %d\n", countH);
			printf("So ket qua giai duoc cua Random restart hill climbing: %d\n", countRH);
			printf("So ket qua giai duoc cua Simulated annealing: %d\n", countSA);
			if (countH > countRH && countH> countSA)
			{
				printf("So sanh thuat toan: Hillclimbing tot nhat");
			}
			else if (countRH > countSA && countRH >= countH)
			{
				if (countRH == countH)
				{
					printf("So sanh thuat toan: Hillclimbing = Random restart hill climbing > Simulated annealing\n");
				}
				else
				{
					printf("So sanh thuat toan:  Random restart hill climbing tot nhat\n");
				}
				
			}
			else if (countSA >= countRH && countSA >= countH)
			{
				if (countSA != countRH)
				{
					if (countSA == countRH)
					{
						printf("So sanh thuat toan: Simulated annealing =  Hillclimbing > Random restart hill climbing\n");
					}
					else
					{
						printf("So sanh thuat toan:  Simulated annealing  tot nhat\n");
					}
				}
				else
				{
					if (countSA == countRH && countSA >countH)
					{
						printf("So sanh thuat toan: Simulated annealing =  Random restart hill climbing > Hillclimbing\n");
					}
					else
					{
						printf("So sanh thuat toan: Simulated annealing =  Random restart hill climbing = Hillclimbing\n");
					}
				}
			}



	default:
		break;
	}
}
void Taomang(int Start[][m])
{
	printf("Nhap so tuy y tu 0-8:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			scanf_s("%d", &Start[i][j]);
		}
}
void Xuatmang(int Start[][m])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", Start[i][j]);
		}
		printf("\n");
	}
}
int checkpoint1(int Start[][n])
{
	int point1=0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (Start[i][j] == 0)
			{
				point1 = i;
			}
		}
	return point1;
}
int checkpoint2(int Start[][m])
{
	int point2=0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (Start[i][j] == 0)
			{
				point2 = j;
			}
		}
	return point2;
}
int toppoint(int Goal[][m],int Start[][m],int a,int b)
{
	int top;
	if (a > 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Goal[i][j] == Start[a - 1][b])
				{
					top = abs(i - (a - 1)) + abs(b - j);
				}
			}
		}
		if (top == 0)
		{
			return 5;
		}
		else
		{
			return top;
		}
	}
	else
		return 199;
}
int downpoint(int Goal[][m], int Start[][m], int a, int b)
{
	int down;
	if (a < 2)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Goal[i][j] == Start[a + 1][b])
				{
					down = abs(i - (a + 1)) + abs(b - j);
				}
			}
		}
		if (down == 0)
		{
			return 5;
		}
		else
		{
			return down;
		}
	}
	else
		return 199;
}

int leftpoint(int Goal[][m], int Start[][m], int a,int b)
{
	int left;
	if (b > 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Goal[i][j] == Start[a][b - 1])
				{
					left = abs(i - a) + abs((b - 1) - j);
				}
			}
		}
		if (left == 0)
		{
			return 5;
		}
		else
		{
			return left;
		}
		
	}
	else
		return 199;
}
int rightpoint(int Goal[][m], int Start[][m], int a, int b)
{
	int right;
	if (b < 2)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Goal[i][j] == Start[a][b + 1])
				{
					right = abs(i - a) + abs((b + 1) - j);
				}
			}
		}
		if (right == 0)
		{
			return 5;
		}
		else
		{
			return right;
		}
	}
	else
		return 199;
}
void Swap(int &x, int &y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void Hillclimbing(int Goal[][m], int Start[][m], int t, int l, int r, int d, int a, int b, int& Cg, int c, int A[], int& check1, int& Step)
{
	int k = 0;
	int i = 0;
	int count = 0;
	clock_t start = clock();
	while (Cg < 8)
	{
		count++;
		// Kiem tra vitri 0
		a = checkpoint1(Start);
		b = checkpoint2(Start);
		//Chi phí
		t = toppoint(Goal, Start, a, b);
		d = downpoint(Goal, Start, a, b);
		l = leftpoint(Goal, Start, a, b);
		r = rightpoint(Goal, Start, a, b);

		Cg = checkGoal(Start, Goal);
		// Cl = Checklap(A);
		if (t < l && t < r && t < d && t != 5 && t != 199 && c != Start[a - 1][b]) // top nho nhat
		{
			if (k < 2)
			{
				A[k++] = 1;
			}

			c = Start[a - 1][b];
			Swap(Start[a][b], Start[a - 1][b]);
			//Xuatmang(Start);

		}
		else if (l < r && l < d && l != 5 && l != 199 && c != Start[a][b - 1]) // left nho nhat
		{
			if (k < 2)
			{
				A[k++] = 2;
			}
			c = Start[a][b - 1];
			Swap(Start[a][b], Start[a][b - 1]);
			//Xuatmang(Start);

		}
		else if (r < d && r != 5 && r != 199 && c != Start[a][b + 1]) // right nho nhat
		{
			if (k < 2)
			{
				A[k++] = 3;
			}

			c = Start[a][b + 1];
			Swap(Start[a][b], Start[a][b + 1]);
			//Xuatmang(Start);

		}
		else if (d != 5 && d != 199 && c != Start[a + 1][b]) // down nho nhat
		{
			/*if (d != r || d != l || d != t)
			{*/
				if (k < 2)
				{
					A[k++] = 4;
				}

				c = Start[a + 1][b];
				Swap(Start[a][b], Start[a + 1][b]);
				//Xuatmang(Start);
			/*}
			else
				break;*/
		}
		else
		{

			break;
		}
		check1 = A[0];
		/*printf("\n");*/

		Step++;
		if (count == 50)
		{
			break;
		}
	}

	//checkstate = 1;
}
void MangGoal(int Goal[][m])
{
	printf("Mang Goal\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ",Goal[i][j]);
		}
		printf("\n");
	}
}
int checkGoal(int Start[][m], int Goal[][m])
{
	int x=0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Goal[i][j] == Start[i][j])
			{
				x++;
			}
		}
	}
	return x;
}
void Savestart(int Start[][m],int Save[][m])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n;j++)
		{
			Save[i][j] = Start[i][j];
		}
}
void Randomrestarthillclimbing(int Goal[][m], int Start[][m], int t, int l, int r, int d, int a, int b, int &Cg, int c,int Save[][m],int A[],int B[],int u,int check1,int &Step)
{
	int k = 0;
	while (k >= 0 && k <= 4)
	{
		a = checkpoint1(Start);
		b = checkpoint2(Start);
		//Chi phí
		t = toppoint(Goal, Start, a, b);
		d = downpoint(Goal, Start, a, b);
		l = leftpoint(Goal, Start, a, b);
		r = rightpoint(Goal, Start, a, b);
		Cg = checkGoal(Start, Goal);
		if (k == 0)
		{
			Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1,Step);
			k++;
			if (Cg < 8)
			{
				Startchange(Start, Save);
				a = checkpoint1(Start);
				b = checkpoint2(Start);
				//Chi phí
				t = toppoint(Goal, Start, a, b);
				d = downpoint(Goal, Start, a, b);
				l = leftpoint(Goal, Start, a, b);
				r = rightpoint(Goal, Start, a, b);
				Cg = checkGoal(Start, Goal);
			}
		}
		else if (k == 1 && t != 199 && Cg < 8 &&check1!=1)
		{
			//printf("Restart\n");
			Step = Step + 2;
			//Xuatmang(Start);
			//printf("\n");
			c = Start[a - 1][b];
			Swap(Start[a][b], Start[a - 1][b]);
			//Xuatmang(Start);

			Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1, Step);
			k++;
			if (Cg < 8)
			{
				Startchange(Start, Save);
				a = checkpoint1(Start);
				b = checkpoint2(Start);
				//Chi phí
				t = toppoint(Goal, Start, a, b);
				d = downpoint(Goal, Start, a, b);
				l = leftpoint(Goal, Start, a, b);
				r = rightpoint(Goal, Start, a, b);
				Cg = checkGoal(Start, Goal);
			}
		}
		else if (k == 2 && l!=199 && Cg < 8 && check1 != 2)
		{
			//printf("Restart\n");
			Step = Step + 2;
			//Xuatmang(Start);
			//printf("\n");
			c = Start[a][b - 1];
			Swap(Start[a][b], Start[a][b - 1]);
			//Xuatmang(Start);
			Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1,Step);
			k++;
			if (Cg < 8)
			{
				Startchange(Start, Save);
				a = checkpoint1(Start);
				b = checkpoint2(Start);
				//Chi phí
				t = toppoint(Goal, Start, a, b);
				d = downpoint(Goal, Start, a, b);
				l = leftpoint(Goal, Start, a, b);
				r = rightpoint(Goal, Start, a, b);
				Cg = checkGoal(Start, Goal);
			}
		}
		else if (k == 3 && r!=199 && Cg < 8 && check1 != 3)
		{
			//printf("Restart\n");
			Step = Step + 2;
			//Xuatmang(Start);
			//printf("\n");
			c = Start[a][b + 1];
			Swap(Start[a][b], Start[a][b + 1]);
			//Xuatmang(Start);
			Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1,Step);
			k++;
			if (Cg < 8)
			{
				Startchange(Start, Save);
				a = checkpoint1(Start);
				b = checkpoint2(Start);
				//Chi phí
				t = toppoint(Goal, Start, a, b);
				d = downpoint(Goal, Start, a, b);
				l = leftpoint(Goal, Start, a, b);
				r = rightpoint(Goal, Start, a, b);
				Cg = checkGoal(Start, Goal);
			}
		}
		else if (k == 4 && d!=199 && Cg <8 && check1 != 4)
		{
			//printf("Restart\n");
			Step = Step + 2;
			//Xuatmang(Start);
			//printf("\n");
			c = Start[a + 1][b];
			Swap(Start[a][b], Start[a + 1][b]);
			//Xuatmang(Start);
			Hillclimbing(Goal, Start, t, l, r, d, a, b, Cg, c, A, check1,Step);
			k++;
			if (Cg < 8)
			{
				Startchange(Start, Save);
				a = checkpoint1(Start);
				b = checkpoint2(Start);
				//Chi phí
				t = toppoint(Goal, Start, a, b);
				d = downpoint(Goal, Start, a, b);
				l = leftpoint(Goal, Start, a, b);
				r = rightpoint(Goal, Start, a, b);
				Cg = checkGoal(Start, Goal);
			}
		}
		else
		{
			k++;
		}
	}
}
void Kq(int Start[][m],int Goal[][m],int Cg,int Step,int &Giaiduoc)
{
	Cg = checkGoal(Start, Goal);
	printf("                             %d", Step);

	if (Cg >= 8)
	{
		/*cost = 0;
		printf("Cost: %d\n", cost);*/
		printf("                           1\n");
		Giaiduoc++;
	}
	if (Cg < 8)
	{
		/*printf("Cost: %d\n", cost);*/
		printf("                          0\n");
	}
}
void Startchange(int Start[][m], int Save[][m])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			Start[i][j] = Save[i][j];
		}
}
void docfile(int Start[][m])
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "Start.txt", "rt");
	if (fp == NULL)
	{
		printf("Error!");
		exit(1);
	}

	for(int i=0;i<n;i++)
		for (int j = 0; j < m; j++)
		{
			fscanf_s(fp, "%d", &Start[i][j]);
		}
	fclose(fp);
}
void RandomMove(int Start[][m],int a,int b,int t,int l,int r,int d)
{
	srand(time(NULL));
	int rd = 1 + rand() % 4;
	if (rd == 1 && t!=199)
	{
		Swap(Start[a][b], Start[a - 1][b]);
	}
	else if (rd == 2 && l!=199)
	{
		Swap(Start[a][b], Start[a][b - 1]);

	}
	else if (rd == 3 && r!=199)
	{
		Swap(Start[a][b], Start[a][b + 1]);

	}
	else if (rd == 4 && d!=199)
	{
		Swap(Start[a][b], Start[a + 1][b]);
	}
	//else
	//{
	//	Swap(Start[a][b], Start[a + 1][b]);
	//}
	
}
void Simulatedannealing(int Start[][m],int Goal[][m],int a,int b,int t,int l,int r,int d,int z,int &rd,int &Cg,int &Step,int checkStep,double &tam,int &check2)
{
	int i = 0;
	double f = 0;
	double denta = 0;
	double p = 0;
	double T = 100;
	double scale = 0;
	//f= scale * 1;
	
	while (i < 100)
	{
		tam = 0;
		a = checkpoint1(Start);
		b = checkpoint2(Start);
		t = toppoint(Goal, Start, a, b);
		l = leftpoint(Goal, Start, a, b);
		r = rightpoint(Goal, Start, a, b);
		d = downpoint(Goal, Start, a, b);
		Cg = checkGoal(Start, Goal);
		if (Cg >= 8)
		{
			break;
		}
		rd = 1 + rand() % 4;
		scale = rand() / (double)RAND_MAX;
		//printf("%d", rd);
		if (rd == 1)
		{
			denta = t - z;
			tam = t;
			check2 = 1;
		}
		else if (rd == 2)
		{
			denta = l - z;
			tam = l;
			check2 = 2;

		}
		else if (rd == 3)
		{
			denta = r - z;
			tam = r;
			check2 = 3;

		}
		else if (rd == 4)
		{
			denta = d - z;
			tam = d;
			check2 = 4;
		}
		if (denta < 0)
		{
			p = 1;
		}
		else
		{
			
			p = exp(-denta / T);
		}
		if (scale < p)
		{
			itMove(Start, rd, a, b, t, l, r, d,checkStep);
			//Xuatmang(Start);
			//printf("\n");
			if (checkStep == 2)
			{
				Step++;
				checkStep = 0;
			}
			//printf("\n");
			//Xuatmang(Start);
		}
		T = T - 1;
		i++;
	
	
	}
}
int Zeropoint(int Start[][m],int Goal[][m],int a,int b)
{
	int zero;
	if (a < 2)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Goal[i][j] == Start[a][b])
				{
					zero = abs(i - a) + abs(b - j);
				}
			}
		}
		if (zero == 0)
		{
			return 5;
		}
		else
		{
			return zero;
		}
	}
}
void itMove(int Start[][m],int rd,int a,int b,int t,int l,int r,int d,int &checkStep )
{
	//srand(time(NULL));
	if (rd == 1 && t != 199)
	{
		if (t <= l && t <= r &&t <= d)
		{
			Swap(Start[a][b], Start[a - 1][b]);
			checkStep = 2;
		}
		//break;
	}
	else if (rd == 2 && l != 199)
	{
		if (l <= t && l <= r && l <= d)
		{
			Swap(Start[a][b], Start[a][b - 1]);
			checkStep = 2;
		}
		//break;
	}
	else if (rd == 3 && r != 199)
	{
		if (r <= t &&r <= l && r <= d)
		{
			Swap(Start[a][b], Start[a][b + 1]);
			checkStep = 2;
		}
	}
	else if (rd == 4 && d != 199)
	{
		if (d <= t && d <= l && d <= r)
		{
			Swap(Start[a][b], Start[a + 1][b]);
			checkStep = 2;
		}
	}
	else
	{
			//rd++;
		checkStep = 1;
	}
}

void RandomMang(int Start[][m],int Goal[][m],int &t,int &l,int &r,int &d,int &a,int &b)
{
		//int z, x, k = 0;
		////moi lan chay se cho so khac nhau theo thoi gian
		//
		//int b[9];

		//for (int i = 0; i < 9; i++) b[i] = -1;
		//for (int i = 0; i < 3; i++)
		//	for (int j = 0; j < 3; j++)
		//	{
		//		New[i][j] = -1;
		//	}


		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		do
		//		{
		//			x = rand() % 9;
		//		} while (check(x, b) == 0);
		//		b[k] = x;
		//		New[i][j] = x;
		//		k++;
		//	}
		//}

		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		printf("%d ", New[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");
	int check = 1;
	int rd = 0;
	GoalForStart(Start);
	int rdStep = 1 + rand() % 99;
	while (rdStep > 0)
	{
		a = checkpoint1(Start);
		b = checkpoint2(Start);
		t = toppoint(Goal, Start, a, b);
		l = leftpoint(Goal, Start, a, b);
		r = rightpoint(Goal, Start, a, b);
		d = downpoint(Goal, Start, a, b);
		check = 1;
		while (check == 1)
		{
			rd = 1 + rand() % 4;
			if (rd == 1)
			{
				if (t != 199)
				{
					Swap(Start[a][b], Start[a - 1][b]);
					check = 0;
				}
			}
			if (rd == 2)
			{
				if (l != 199)
				{
					Swap(Start[a][b], Start[a][b-1]);
				}
			}
			if (rd == 3)
			{
				if (r != 199)
				{
					Swap(Start[a][b], Start[a][b+1]);
					check = 0;
				}
			}
			if (rd == 4)
			{
				if (d != 199)
				{
					Swap(Start[a][b], Start[a + 1][b]);
					check = 0;
				}
			}
			rdStep--;
		}
		
	}
	a = checkpoint1(Start);
	b = checkpoint2(Start);
	t = toppoint(Goal, Start, a, b);
	l = leftpoint(Goal, Start, a, b);
	r = rightpoint(Goal, Start, a, b);
	d = downpoint(Goal, Start, a, b);

}
int check(int x, int b[])
{
	for (int i = 0; i < 9; i++)
	{
		if (b[i] > -1)
			if (b[i] == x)
				return 0;
	}
	return 1;
}
void NewforStart(int New[][m], int Start[][m],int Goal[][m],int &a,int &b,int &t,int &l,int &r,int &d)
{
	
	for(int i=0;i<n;i++)
		for (int j = 0; j < m; j++)
		{
			Start[i][j] = New[i][j];
		}
	a = checkpoint1(Start);
	b = checkpoint2(Start);
	t = toppoint(Goal, Start, a, b);
	d = downpoint(Goal, Start, a, b);
	l = leftpoint(Goal, Start, a, b);
	r = rightpoint(Goal, Start, a, b);
}
void Status(int Start[][m], int Goal[][m], int Cg, int& Giaiduoc)
{
	Cg = checkGoal(Start, Goal);
	if (Cg >= 8)
	{
		/*cost = 0;
		printf("Cost: %d\n", cost);*/
		printf("                           1");
		Giaiduoc++;
	}
	if (Cg < 8)
	{
		/*printf("Cost: %d\n", cost);*/
		printf("                          0");
	}
}
void GoalForStart(int Start[][m])
{
	int Goal1[n][m] =
	{ {1, 2, 3}, // hang 1
		{4, 5, 6}, // hang 2
		{7, 8, 0}  // hang 3
	};
	for(int i=0;i<n;i++)
		for (int j = 0; j < m; j++)
		{
			Start[i][j] = Goal1[i][j];
		}

}



