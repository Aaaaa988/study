#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const double Pi = 3.14159265359;

int SumC = 0;
int MultC = 0;


struct Complex
{
	double Re;
	double Im;	
};


void ComplexMult(Complex *a, int k, Complex *b, int k1,  Complex *rez)
{
	rez->Re = ((a+k)->Re * (b+k1)->Re) - ((a+k)->Im * (b+k1)->Im);
	rez->Im = ((a+k)->Re * (b+k1)->Im) + ((a+k)->Im * (b+k1)->Re);
}

void ComplexExp(double arg, Complex *rez)
{
	if(arg < 0)
	{
		rez->Re = cos( -1 * arg );
		rez->Im = -1 * sin( -1 * arg );
	}
	else
	{
		rez->Re = cos( arg );
		rez->Im = sin( arg );
	}
}

void ComplexDivide(Complex *a, int k, int p)
{
	Complex Temp;
	Temp.Re = 0;
	Temp.Im = 0;
	Complex n;
	n.Re = p;
	n.Im = 0;
	
	Temp.Re = ((a+k)->Re * n.Re + (a+k)->Im * n.Im) / (n.Re * n.Re + n.Im  * n.Im);
	Temp.Im = ((a+k)->Im * n.Re - (a+k)->Re * n.Im) / (n.Re * n.Re + n.Im * n.Im);
	
	(a+k)->Re = Temp.Re;
	(a+k)->Im = Temp.Im;	
}

void PrintF(Complex *a, int N)
{
	for(int i = 0; i < N; i++)
	{
		cout << " ( " << (a+i)->Re << " ; " << (a+i)->Im << " ) " << endl;
	}
}

int GetP(int N)
{
	int p = (int)sqrt(N);
	while(true)
	{
		if(N % p == 0)
		{
			break;
		}
		else
		{
			p++;
		}
	}
	return p;
}

void SFFT(Complex *A, Complex *f, int N)
{
	Complex Mult;
	Mult.Im = 0;
	Mult.Re = 0;
	
	//Временная переменная для експоненты
	Complex Exp;
	Exp.Re = 0;
	Exp.Im = 0;
	
	
	int p1 = GetP(N);
	int p2 = N / p1;

	Complex A1[N];
	for(int i = 0; i < N; i++)
	{
		A1[i].Re = 0;
		A1[i].Im = 0;
	}
	
	for(int k1 = 0; k1 < p1; k1++)
	{
		for(int j2 = 0; j2 < p2; j2++)
		{
			for(int j1 = 0; j1 < p1; j1++)
			{
				double z = (-1 * 2 * Pi * j1 * k1) / p1;
				ComplexExp( z, &Exp );
				ComplexMult(f, j2 + p2 * j1, &Exp, 0, &Mult);
				
				A1[k1 + p1 * j2].Re += Mult.Re;
				A1[k1 + p1 * j2].Im += Mult.Im;
				
				Mult.Im = 0;
				Mult.Re = 0;
				
				SumC++;
				MultC++;
				
				Exp.Im = 0;
				Exp.Re = 0;	
			}
			ComplexDivide(A1, k1 + p1 * j2, p1);
		}
	}
	
	Mult.Im = 0;
	Mult.Re = 0;
			
	Exp.Im = 0;
	Exp.Re = 0;	
	
	Complex A2[N];
	for(int i = 0; i < N; i++)
	{
		A2[i].Re = 0;
		A2[i].Im = 0;
	}
	
	for(int k1 = 0; k1 < p1; k1++)
	{
		for(int k2 = 0; k2 < p2; k2++)
		{
			for(int j2 = 0; j2 < p2; j2++)
			{
				double z = -1 * 2 * Pi * j2 * (k1 + p1 * k2) / (p1 * p2);
				ComplexExp(   z, &Exp);
				ComplexMult(A1, k1 + p1 * j2, &Exp, 0, &Mult);
				
				A2[k1 + p1 * k2].Re += Mult.Re;
				A2[k1 + p1 * k2].Im += Mult.Im;
				
				Mult.Im = 0;
				Mult.Re = 0;
				
				SumC++;
				MultC++;
				
				Exp.Im = 0;
				Exp.Re = 0;	
			}
			ComplexDivide(A2, k1 + p1 * k2, p2);
		}
	}
	
	for(int i = 0; i < N; i++)
	{
		A[i].Re = A2[i].Re ;
		A[i].Im = A2[i].Im ;
	}
}

void SFFTO(Complex *A, Complex *f, int N)
{
	Complex Mult;
	Mult.Im = 0;
	Mult.Re = 0;
	
	//Временная переменная для експоненты
	Complex Exp;
	Exp.Re = 0;
	Exp.Im = 0;
	
	
	int p1 = GetP(N);
	int p2 = N / p1;

	Complex f1[N];
	for(int i = 0; i < N; i++)
	{
		f1[i].Re = 0;
		f1[i].Im = 0;
	}
	
	for(int k1 = 0; k1 < p1; k1++)
	{
		for(int j2 = 0; j2 < p2; j2++)
		{
			for(int j1 = 0; j1 < p1; j1++)
			{
				double z = (1 * 2 * Pi * j1 * k1) / p1;
				ComplexExp( z, &Exp );
				ComplexMult(A, j2 + p2 * j1, &Exp, 0, &Mult);
				
				f1[k1 + p1 * j2].Re += Mult.Re;
				f1[k1 + p1 * j2].Im += Mult.Im;
				
				Mult.Im = 0;
				Mult.Re = 0;
				
				SumC++;
				MultC++;
				
				Exp.Im = 0;
				Exp.Re = 0;	
			}
			//ComplexDivide(A1, k1 + p1 * j2, p1);
		}
	}
	
	Mult.Im = 0;
	Mult.Re = 0;
			
	Exp.Im = 0;
	Exp.Re = 0;	
	
	Complex f2[N];
	for(int i = 0; i < N; i++)
	{
		f2[i].Re = 0;
		f2[i].Im = 0;
	}
	
	for(int k1 = 0; k1 < p1; k1++)
	{
		for(int k2 = 0; k2 < p2; k2++)
		{
			for(int j2 = 0; j2 < p2; j2++)
			{
				double z = 1 * 2 * Pi * j2 * (k1 + p1 * k2) / (p1 * p2);
				ComplexExp(   z, &Exp);
				ComplexMult(f1, k1 + p1 * j2, &Exp, 0, &Mult);
				
				f2[k1 + p1 * k2].Re += Mult.Re;
				f2[k1 + p1 * k2].Im += Mult.Im;
				
				Mult.Im = 0;
				Mult.Re = 0;
				
				SumC++;
				MultC++;
				
				Exp.Im = 0;
				Exp.Re = 0;	
			}
			//ComplexDivide(A2, k1 + p1 * k2, p2);
		}
	}
	
	for(int i = 0; i < N; i++)
	{
		f[i].Re = f2[i].Re ;
		f[i].Im = f2[i].Im ;
	}
}

int main()
{
	string a;
	string b;
	//cin >> a;
	//cin >> b;
	
	int N1 = 10 * 10; //a.size();
	int N2 = 10 * 10; //b.size();


	int A[N1];
	int B[N2];
	
	
	/*for(int i = N1 - 1; i >= 0; i--)
	{
		A[i] = a[i] - '0';
	}
	
	for(int i = N2 - 1; i >= 0; i--)
	{
		B[i] = b[i] - '0';
	}*/
	
	for(int i = 0; i < N1; i++)
	{
		A[i] = i + 1;
	}
	for(int i = 0; i < N2; i++)
	{
		B[i] = i + 1;
	}
	
	int Kmax = (N1 - 1) + (N2 - 1);


	int C[Kmax + 1];
	for(int i = 0; i < Kmax+1; i++)
	{
		C[i] = 0;
	}
	
	cout << "A:  ";
	for(int i = 0; i < N1; i++)
	{
		cout << A[i] << " ";
	}
	
	cout << endl;
	cout << "B:  ";
	for(int i = 0; i < N2; i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;
	for(int i = 0; i < Kmax + 1; i++)
	{
		for(int j = 0; j < N1; j++)
		{
			for(int z = 0; z < N2; z++)
			{
				if( (j + z) == i)
				{
					C[i] += A[j] * B[z];
				}
			}
		}
	}
	cout << "Obychnya Sve`rtka:\n";
	for(int i = 0; i < Kmax+1; i++)
	{
		cout << C[i] << " " << endl;	
	}
	cout << endl;
	
	//Алгоритм быстрой свёртки
	int N = 0;
	if(N1 > N2)
	{
		N = 2 * N1;
		//N = Kmax + 1;
	}
	else
	{
		N = 2 * N2;
		//N = Kmax + 1;
	}
	
	Complex A1[N];
	Complex B1[N];
	
	/*for(int i = N - 1; i>= 0; i--)
	{
		if(i <= N1 - 1)
		{
			A1[i].Re = a[i] - '0';
			A1[i].Im = 0;
		}
		else
		{
			A1[i].Re = 0;
			A1[i].Im = 0;
		}
	}*/
	for(int i = 0; i < N; i++)
	{
		if(i <= N1 - 1)
		{
			A1[i].Re = A[i];
			A1[i].Im = 0;
		}
		else
		{
			A1[i].Re = 0;
			A1[i].Im = 0;
		}
	}
	//cout << "A1 :\n";
	//PrintF(A1, N);
	
	/*for(int i = N - 1; i>= 0; i--)
	{
		if(i <= N2 - 1)
		{
			B1[i].Re = b[i] - '0';
			B1[i].Im = 0;
		}
		else
		{
			B1[i].Re = 0;
			B1[i].Im = 0;
		}
	}*/
	for(int i = 0; i < N; i++)
	{
		if(i <= N2 - 1)
		{
			B1[i].Re = B[i];
			B1[i].Im = 0;
		}
		else
		{
			B1[i].Re = 0;
			B1[i].Im = 0;
		}
	}
	//cout << "B1 : \n";
	//PrintF(B1, N);
	
	Complex RA[N];
	for(int i = 0; i < N; i++)
	{
		RA[i].Re = 0;
		RA[i].Im = 0;
	}
	
	Complex RB[N];
	for(int i = 0; i < N; i++)
	{
		RB[i].Re = 0;
		RB[i].Im = 0;
	}
	
	SFFT(RA, A1, N);
	SFFT(RB, B1, N);
	
	//cout << "RA: \n";
	//PrintF(RA, N);
	//cout << "RB: \n";
	//PrintF(RB, N);
	
	Complex C1[N];
	for(int i = 0; i < N; i++)
	{
		C1[i].Re = 0;
		C1[i].Im = 0;
	}
	
	
	Complex Mult;
	Mult.Im = 0.0;
	Mult.Re = 0.0;
	
	for(int i = 0; i < N; i++)
	{
		ComplexMult(RA, i, RB, i, &Mult);
		C1[i].Re = Mult.Re;
		C1[i].Im = Mult.Im;
		Mult.Im = 0.0;
		Mult.Re = 0.0;
		MultC++;
	}
	
	//cout <<"\n";
	//PrintF(C1, N);
	
	Complex n2;
	n2.Re = N;
	n2.Im = 0;
	
	
	Mult.Im = 0.0;
	Mult.Re = 0.0;
	for(int i = 0; i < N; i++)
	{
		ComplexMult(C1, i, &n2, 0, &Mult);
		C1[i].Re = Mult.Re;
		C1[i].Im = Mult.Im;
		Mult.Im = 0.0;
		Mult.Re = 0.0;
		//MultC++;
	}
	//cout << "\n";
	//PrintF(C1, N);
	
	Complex f[N];
	for(int i = 0; i < N; i++)
	{
		f[i].Re = 0;
		f[i].Im = 0;
	}
	
	SFFTO(C1, f, N);
	cout << "Sve`rtka Cherez SFFT:\n";
	PrintF(f, N);
	cout << "\n\n";
	cout << "Mult =" << MultC << "  Summ" << SumC << " Rez = " << MultC + SumC << endl;
}
