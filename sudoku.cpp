#include <iostream>
#include <cstdlib>

using namespace std;

bool f_row(int **a, int **b, int **e, int j);
bool f_col(int **c, int **d, int **e, int j);
bool f_box(int **e);
bool checkSudoku(int **a[]);

int main()
{
	int **a[9];
	int b[9] = {2,4,8,   3,9,5,   7,1,6};
	int c[9] = {5,0,1,   6,2,8,   3,4,9};
	int d[9] = {9,3,6,   7,4,1,   5,8,2};
	
	int e[9] = {6,8,2,   5,3,9,   1,7,4};
	int f[9] = {3,5,9,   0,7,0,   0,2,8};
	int g[9] = {7,0,4,   8,6,2,   9,5,3};
	
	int h[9] = {8,6,3,   4,1,7,   2,9,5};
	int i[9] = {1,9,5,   2,0,6,   4,3,7};
	int j[9] = {4,2,7,   9,5,3,   8,6,1};

	int *block[9] = {&b[0], &c[0], &d[0], &e[0], &f[0], &g[0], &h[0], &i[0], &j[0]};

	int *box0[9] = {&b[0], &b[1], &b[2], &c[0], &c[1], &c[2], &d[0], &d[1], &d[2]};
	int *box1[9] = {&b[3], &b[4], &b[5], &c[3], &c[4], &c[5], &d[3], &d[4], &d[5]};
	int *box2[9] = {&b[6], &b[7], &b[8], &c[6], &c[7], &c[8], &d[6], &d[7], &d[8]};

	int *box3[9] = {&e[0], &e[1], &e[2], &f[0], &f[1], &f[2], &g[0], &g[1], &g[2]};
	int *box4[9] = {&e[3], &e[4], &e[5], &f[3], &f[4], &f[5], &g[3], &g[4], &g[5]};
	int *box5[9] = {&e[6], &e[7], &e[8], &f[6], &f[7], &f[8], &g[6], &g[7], &g[8]};

	int *box6[9] = {&h[0], &h[1], &h[2], &i[0], &i[1], &i[2], &j[0], &j[1], &j[2]};
	int *box7[9] = {&h[3], &h[4], &h[5], &i[3], &i[4], &i[5], &j[3], &j[4], &j[5]};
	int *box8[9] = {&h[6], &h[7], &h[8], &i[6], &i[7], &i[8], &j[6], &j[7], &j[8]};

	a[0] = &box0[0];
	a[1] = &box1[0];
	a[2] = &box2[0];
	a[3] = &box3[0];
	a[4] = &box4[0];
	a[5] = &box5[0];
	a[6] = &box6[0];
	a[7] = &box7[0];
	a[8] = &box8[0];

	//find number of 0s
	int length = 0;
	for(int t = 0; t < 9; t++)
	{
		for(int u = 0; u < 9; u++)
		{
			if(*a[t][u] == 0)
			{
				length++;  
			}
		}
	}

	//track where there are 0s
	int *xcoord = new int[length];
	int *ycoord = new int[length];
	int count = 0;
	for(int t = 0; t < 9; t++)
	{
		for(int u = 0; u < 9; u++)
		{
			if(*a[t][u] == 0)
			{
				xcoord[count] = t;
				ycoord[count] = u;
				count++;
			}
		}
	}

	//generate random numbers
	int xaxis = 0;
	int yaxis = 0;
	for(int w = 0; w < length; w++)
	{
		xaxis = xcoord[w];
		yaxis = ycoord[w];
		*a[xaxis][yaxis] = (rand() % 9) + 1;
	}

	while(checkSudoku(a) != 1)
	{
		for(int w = 0; w < length; w++)
		{
			xaxis = xcoord[w];
			yaxis = ycoord[w];
			*a[xaxis][yaxis] = (rand() % 9) + 1;
		}
	}

	//print solution
	for(int n = 0; n < 9; n++)
	{
		if(n%3 == 0 && n != 0)
		{
			cout << endl;
		}		
		for(int t = 0; t < 9; t++)
		{
			if(t%3 == 0 && t != 0)
			{
				cout << "   ";
			}
			cout << *(block[n] + t) << " ";
		}
		cout << endl;
	}

	delete [] xcoord;
	delete [] ycoord;

	return 0;
}

bool f_row(int **a, int **b, int **e, int j)
{
	bool row = 1;
	int arr[9];
	int temp = j;
	for (int i = 0; i < 3; i++)
	{
		arr[i] = *a[j];
		j++;
	}

	j = temp;
	for(int i = 3; i < 6; i++)
	{
		arr[i] = *b[j];
		j++;
	}
	j = temp;
	for(int i = 6; i < 9; i++)
	{
		arr[i] = *e[j];
		j++;
	}

	int tem;
	for(int i = 0; i < 9; i++)
	{
		tem = arr[i];
		for(int k = 0; k < 9; k++)
		{
			if(k != i)
			{
				if(tem == arr[k])
				{
					row = 0;
				}
			}
		}
	}

	return row;
}

bool f_col(int **c, int **d, int **e, int j)
{
	bool col = 1;
	int arr[9];
	int temp = j;
	for(int i = 0; i < 3; i++)
	{
		arr[i] = *c[j];
		j = j + 3;
	}
	j = temp;
	for(int i = 3; i < 6; i++)
	{
		arr[i] = *d[j];
		j = j + 3;
	}
	j = temp;
	for(int i = 6; i < 9; i++)
	{
		arr[i] = *e[j];
		j = j + 3;
	}

	int tem;
	for(int i = 0; i < 9; i++)
	{
		tem = arr[i];
		for(int k = 0; k < 9; k++)
		{
			if(k != i)
			{
				if(tem == arr[k])
				{
					col = 0;
				}
			}
		}
	}

 	return col;
}

bool f_box(int **e)
{
	bool box = 1;
	int arr[9];
	for(int i = 0; i < 9; i++)
	{
		arr[i] = *e[i];
	}

	int tem;
	for(int i = 0; i < 9; i++)
	{
		tem = arr[i];
		for(int k = 0; k < 9; k++)
		{
			if(k != i)
			{
				if(tem == arr[k])
				{
					box = 0;
				}
			}
		}
	}

	return box;
}

bool checkSudoku(int **a[])
{
	bool check = 1;

	bool array_row[9];
	int p = 0; int k = 0;
	for (int count = 0; count < 9; count++)
	{
		if(count%3 == 0 && count != 0)
		{
			p = p + 3;
			k = 0;
		}
		array_row[count] = f_row(a[p], a[p+1], a[p+2], k*3);
		
		k++;
	}

	bool array_col[9];
	p = 0; k = 0;
	for(int count = 0; count < 9; count++)
	{
		if(count%3 == 0 && count != 0)
		{
			p++;
			k = 0;
		}
		array_col[count] = f_col(a[p], a[p+3], a[p+6], k);
		k++;
	}

	bool array_box[9];
	for(int count = 0; count < 9; count++)
	{
		array_box[count] = f_box(a[count]);
	}

	for(int count = 0; count < 9; count++)
	{
		if((array_row[count] && array_col[count] && array_box[count]) == 0)
		{
			check = 0;
		}	
	}

	return check;
}