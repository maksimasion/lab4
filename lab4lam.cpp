#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

void matrix_enter(double **x, int n)
{
	double *f;
	f = new double[n];
	

	for (int i = 0; i < n; i++) {
		x[i] = new double[n];
		for (int j = 0; j < n; j++) {
			x[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				x[i][j] = 10;
			if (i < n - 2) {
				if (j == i + 2)
					x[i][j] = 0.1;
			}
			if (i < n - 1) {
				if (j == i + 1)
					x[i][j] = 1;
			}
			if (i > 0) {
				if (j == i - 1)
					x[i][j] = 1;
			}
			if (i > 1) {
				if (j == i - 2)
					x[i][j] = 0.1;
			}
		}

	}
}

void matrix_show(double **matrix, int n)
{
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << "\n";
		for (int j = 0; j < n; j++)
			printf("  %.5f ", matrix[i][j]);
	}

}
void new_matrix(double** &matrix, int n)
{
	matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
}

void pr_matrix(double **A, double **B, double **C, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
}

void calc_U(double **A, double **B, int n)
{
	double max_elem = A[0][1];
	int h = 1;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (fabs(A[i][j]) > max_elem)
			{
				max_elem = fabs(A[i][j]);
				k = i;
				h = j;
			}
	}
	double fi = 0.5*atan((2 * max_elem) / (A[k][k] - A[h][h]));

	if (A[k][k] == A[h][h]) {
		fi = 0.785;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				B[i][j] = 1;
			}
			else
				B[i][j] = 0;

			B[k][h] = -sin(fi);
			B[h][k] = sin(fi);
			B[h][h] = cos(fi);
			B[k][k] = cos(fi);

		}

}

double elem_sum(double **A, int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			sum += (A[i][j])*(A[i][j]);

	return sum;
}
void trans_matrix(double **A, double **B, double **T, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			T[i][j] = A[j][i];
			B[i][j] = A[j][i];
			B[i][j] = T[i][j];
		}

}

void prir_matrix(double **A, double **B, double **T, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			T[i][j] = A[i][j];
			B[i][j] = A[i][j];
			B[i][j] = T[i][j];
		}

}

void calc_max_elem(double **A, int n)
{
	double max_elem = A[0][1];
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
			if (A[i][j] > max_elem)
			{
				max_elem = A[i][j];
			}
	}
	cout << max_elem;
}

int control(double **A, int n)
{
	double s = 0;
	s = elem_sum(A, n);
	if (s == 0) {
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (A[i][j] != A[j][i]) {
					cout << " \nmatrix is not symmetric \n";
					return 0;
				}
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	double Eps = 0.001;
	int n = 20;
	double **A;
	double **U;
	double **UT;
	double **E;
	double **C;
	double **T1;
	double **T2;
	new_matrix(A, n);
	new_matrix(U, n);
	new_matrix(UT, n);
	new_matrix(E, n);
	new_matrix(C, n);
	new_matrix(T1, n);
	new_matrix(T2, n);

	matrix_enter(A, n);
	control(A, n);

	double s = elem_sum(A, n);

	cout << "\n please waiting... \n";
	for (int i = 0; sqrt(s) > Eps; i++) {
		calc_U(A, U, n);
		trans_matrix(U, UT, T1, n);
		pr_matrix(UT, A, E, n);
		pr_matrix(E, U, C, n);
		prir_matrix(C, A, T2, n);

		s = elem_sum(A, n);
	}
	double min = 100;
	double max = 0;
	//matrix_show(A,n);
	//Все лямбда находятся на главной диагонали, осуществляем поиск максимальных и минимальных их значений \|/
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == j) {
				if (A[i][j] > max) {
					max = A[i][j];
				}
				if (A[i][j] < min) {
					min = A[i][j];
				}
			}
		}
	}
	//Выводим максимальные и минимальные значения
	cout << "Max: " << max << ", Min: " << min << endl;

	system("PAUSE");
	return EXIT_SUCCESS;
}
