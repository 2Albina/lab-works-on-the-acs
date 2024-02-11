#include <iostream>
#include <omp.h>

using namespace std;
using std::cout;

double func(double x)
{
	return x*x + x - 3.2;
}

int main() {
	double time_start, time_finish, S, T1, Tp, Q;
	int num_proc = omp_get_num_procs();
	cout << "Number of processors = " << num_proc << std::endl << std::endl;
	cout << "Number of threads, T, S, Q" << std::endl;

	double a = 1, b = 20;
	int n = 100000000;
	double h = (b - a) / n;
	double I;
	int i = 0;
	for (int p = 1; p <= 2 * num_proc; ++p)
	{
		I = 0;
		double ai = 0;
		double bi = 0;
		omp_set_num_threads(p); 
		time_start = omp_get_wtime();

		#pragma omp parallel for private(i) shared(n) reduction(+:I)
		for (int i = 0; i < n-1; i++) {
			ai = a + i*h;
			bi = a + (i+1)*h;
			I += h / 6 * (func(ai) + func(bi) + 4 * func((ai + bi) / 2));
		}

		time_finish = omp_get_wtime();
		Tp = time_finish - time_start;
		if (p == 1)
			T1 = Tp;
		S = T1 / Tp;
		Q = S / p;
		cout << p << ", " << Tp << ", " << S << ", " << Q << std::endl; // ", " << I <<
	}

	return 0;
}