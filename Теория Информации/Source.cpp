#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(int mn, char* nm[])
{
	int i, j, k, l, row, max, C, N, t, K, Col, ms, s, *col;
	double q, x, Q_, X_, Q, X;
	char c, * p, * d, * b;
	if (mn != 5) cerr << "gen in.txt out.ext K N" << endl, exit(1);
	ifstream in(nm[1], ios::binary);//��������� ���������� ����� � �������� �������
	if (!in) cerr << "File\"." << nm[1] << "\"not open" << endl, exit(1);//���� ����� �� �������� ���������� ������ � �������
	in.seekg(0, ios::end);//������������� ������� ����� �����
	//ios -����� �������������� � �������� ��������
	s = in.tellg();//�������� ������� ������� ��������� ������ ������ � �����,��� ����� ������ ����� �����
	in.seekg(0, ios::beg);//������������� ������� � ������ �����
	p = new char[s + 2];//������� ������ �� 2 ������� ������ ����� 
	in.read((char*)p, s);//��������� ���� �� ����� � ���� ������
	in.close();//��������� �������� �����
	for (p[s++] = 0x0A, p[s++] = 0, i = -1;++i, p[i] += 23 * !(p[i] - '\t'););//��������� ������ 0x0A. ������� ���������
	//������������ ������������� ������ ������ ������� �������� ������
	//��������� ������ ���������� ����� ������
	//�������� ����� ���������(ascii ���==9) �� ����� �������(���=32)
	for (i = -1;++i, p[i] += 2 * !(p[i] - ','););//�������� ������� �� �����, ���������� ���� ��� � ����������
	for (k = i = 0;(p[k] = p[i]);i++) 
		k += (p[i] == '.' || (p[i] | 7) == '7' || (p[i] | 1) == '9' || p[i] == ' ' || p[i] == 0x0A);///&//&///&///////////////
	//�������� ����� ������� ������� 0x0A � ����� �� 0 �� 9
	for (ms = k = 0, i = -1;p[++i];k += !(p[i] - '.')) 
		if (p[i] == ' ' || p[i] == 0x0A)
			(ms < k) ? ms = k, k = 0 : k = 0;
	// ������� ������������� ���������� ���������� ����� � ����� ����� (�����)
	if (ms > 1) cerr << "� ��������� �������� ��������� ����� ����� ���������� �����\n", exit(1);//��� �������� ������ ����� ���������� ������ � �������
	for (i = 1;p[++i];)
		if (p[i - 1] == '.') if (p[i - 2] == ' ') if (p[i] == ' ') p[i - 1] = ' ';// ������ ��������� ����� �� ������
	for (c = ' ', k = i = 0;(p[k] = p[i]);c = p[i++]) if (!(c ^ p[i]) && c == ' ');else p[k++] = p[i];
	//�������� 2 � ����� �������� �� 1 ������
	for (i = -1;p[++i];) if ((p[i + 1] == 0x0A && p[i] == ' ') || (p[i + 1] == ' ' && p[i] == 0x0A)) p[i] = p[i + 1] = 0x0A;
	//������ �������� � ������ � ����� ����� �� ������ 0x0A
	for (c = 0x0A, k = i = 0;(p[k] = p[i]);c = p[i++]) if (!(c ^ p[i]) && (c == 0x0A));else p[k++] = p[i];
	//�������� 2 � ����� �������� 0x0A �� 1 ������ 0x0A
	for (row = i = 0;p[i];row += (p[i++] == 0x0A));//������� ������ � ���������� � ���������� row
	cout << "row=" << row << endl;
	{
		ofstream o("1.fb", ios::binary);//�������� �������� �����, ��������
		for (i = -1; ++i < s; o.put(p[i]));
		o.close();
	}//�������� ����������� �������� �������
	col = new int[row];//������� ������ �����
	for (i = row;--i >= 0;col[i] = 0);//������� � �������� �������, ��������� ������ ������
	// ������ ��� ���������� �������� � ������ ������ (�� 1 ������, ��� �����)
	for (k = i = 0;p[i];col[k] += (p[i] == 0x20), k += (p[i++] == 0x0A));// ������� ����� �������� � ������� � ������ �� � ������
	for (s = i + 1, k = i = -1;++i < row;k &= !(col[0] ^ col[i]),i+=!k*row);// �������� ������������ ���������� ��������
	if (!k) //�������� �� ������ ���������� ��������� � ������ ������
		cerr << "� ������� ������ ���������� ������!\n", exit(3);
	for (Col = col[0] - (i = -1); ++i < s - 2; p[i] += 22 * !(p[i] - 0x0A));
		if (!col[0])col[0] = row - 1, row = 1;//������ �������� 0x09 �� ������ ����������� �������� � ������
	cout << "s=" << s << "\nCol=" << Col << endl; 
	if (row - 1) if (row != Col)cerr << "������� �� ����������!\n", exit(4);
	{ofstream o("2.fb", ios::binary);for (i = -1;++i < s;o.put(p[i]));o.close();}//�������� ����������� �������� �������
	{ cout << p;} //�������� ����������� �������� �������
	d = new char[s * 10];b = new char[s * 10];//�������� ���������� ������������ �������
	for (c = j = i = -1;p[++i];d[++j] = p[i], c = p[i]) if (p[i] == '.' && c == ' ') d[++j] = 0x30;
	d[++j] = 0;// ���������� ���� ����� ���������� ������, ���� ��� ��� ������
	{ cout << d << endl;} //�������� ����������� �������� �������
	for (k = 0, j = i = -1;d[++i];b[++j] = d[i]) if (k += (d[i] == '.'), d[i] == ' ') k ? k = 0 : b[++j] = '.';
	// ���������� ���������� ����� � ����� �����, ���� �� ��� ���
	if (!k) b[j] = '.', b[j + 1] = 0x0A, b[j + 2] = 0;// ���������� ���������� ����� � ����� ���������� ����� � ����������� 0x0A
	{ cout << endl << b << endl;} //�������� ����������� �������� �������
	for (max = k = 0, i = -1;b[++i];)if (k *= (b[i] != '.'), b[i] == 0x20 || b[i] == 0x0A) { if (max < k) max = k;k = 0;}
	else k++;
	// ������� ������������� ����� ������ ����� ������� (��������� �� 1)
	cout << "max=" << max - 1 << endl;
	for (l = i = -1, k = 0;b[++i];d[++l] = b[i], k *= !!j)
		if (k *= (b[i] != '.'), j = (b[i] != 0x20 && b[i] != 0x0A), k += j, !j) for (;k++ < max;d[++l] = 48);
	d[++l] = 0;
	{ cout << d << endl;} //�������� ����������� �������� �������
	for (j = i = -1;d[++i];) if (d[i] == '.');else d[++j] = d[i];
	d[++j] = 0;
	//�������� o����������� �������� �������
	{ cout << d << endl;} //�������� ����������� �������� �������
	int* g = new int[row * (col[0] + 1)];int** G = new int* [row];for (i = -1;++i < row;) G[i] = &g[(col[0] + 1) * i];
	for (g[k = i = 0] = atoi(&d[0]);++k < row * Col;)for (;d[++i] != ' ';) g[k] = atoi(&d[i + 1]);
	for (k = -1;d[++k] != ' ';);
	for (i = l = 1;++i <= k;l *= 10);
	cout << "l=" << l << endl;
	for (i = -1;++i < row;cout << endl) for (cout << i << ": ", j = -1;++j < Col;) cout << G[i][j] / float(l) << '\t';
	for (k = i = -1;++i < row;s != l ? cerr << "����� ������������ � ������ " << i + (k = 0) << " �� ����� 1 " << endl : cerr)
		for (s = j = 0;j < Col;) s += G[i][j++];
	if (!k)exit(6);
	float* f = new float[row * Col];float** F = new float* [row];for (i = -1;++i < row;) F[i] = &f[Col * i];
	for (i = -1;++i < row * Col;f[i] = g[i] / float(l));
	for (i = -1;++i < row;cout << endl) for (k = -1;++k <= col[i];) cout << F[i][k] << '\t';
	for (K = 2;K < l;K *= 2);
	cout << "K=" << K << endl;
	for (i = -1;++i < row;)for (j = 0;++j <= col[0];)G[i][j] += G[i][j - 1];
	for (i = -1;++i < row;cout << endl) for (j = -1;++j < (col[0] + 1);) cout << G[i][j] << '\t';
	C = atoi(nm[3]);if (C < 0 || C - row>255)cerr << " ������ ���������\n", exit(7);
	N = atoi(nm[4]);if (N < 1)cerr << "������ N<1\n", exit(8);
	srand(time(NULL));
	if (row == 1) // ��������� �� ������
	{
		ofstream ou(nm[2], ios::binary);
		for (i = 0;i < N;)for (t = rand() % K, j = 0;j <= col[0];j++)if (t < G[0][j])ou.put(C + j), j = col[0], i++;// ��������� ��������
		ou.close();
		for (q = i = 0;i <= col[0];i++) if (F[0][i] > 1e-9) q -= F[0][i] * log(F[0][i]) / log(2.);//������� ����������� ��������
		x = 1 - q / (log(float(col[0] + 1)) / log(2.));//������� ����������� ������������
		//����� ��������(������� ���� ��������� �� ����������� ������ �����)
		cout << "H(A)=" << q << "\nx=" << x << endl;
		cout << "n/n0=" << 1 / (1 - x) << endl;//����� ������������ ������ ��� ����������� ��������
	}
	else //��������� �� �������
	{
		int rw = row - 1, idx;float w, mx, sm, ml;float* R = new float[row];float* B = new float[rw];float* P = new float[row + 1];
		float* u = new float[rw * rw];float** U = new float* [rw];for (i = -1;++i < rw;)U[i] = &u[rw * i];
		float* e = new float[rw * rw];float** E = new float* [rw];for (i = -1;++i < rw;)E[i] = &e[rw * i];
		for (i = -1;++i < rw;B[i] = F[rw][i], cout << F[rw][i] << endl) // ������������ ��������� �������
			for (j = 0;j < rw;j++) U[i][j] = (i == j) + F[rw][i] - F[j][i], cout << (i == j) << "+" << F[rw][i] << "-" << F[j][i] << " ";
		// ������� ������� ���������
		for (i = 0;i < rw;i++) for (j = 0;j < rw;j++) E[i][j] = (i == j);
		for (k = 0;k < rw;k++)
		{
			for (mx = U[k][k], idx = k, i = k + 1;i < rw;i++)
				if (fabs(U[i][k]) > fabs(mx))mx = U[idx = i][k];
			for (i = k + 1;i < rw;i++)
				if (U[k][k])
					for (ml = U[i][k] / U[k][k], j = 0;j < rw;j++)U[i][j] -= ml * U[k][j], E[i][j] -= ml * E[k][j];
				else cerr << "Err", exit(8);
		}
		for (k = rw - 1;k >= 0;k--)
			for (i = k - 1;i >= 0;i--)
				if (U[k][k]) for (ml = U[i][k] / U[k][k], j = 0;j < rw;j++)E[i][j] -= ml * E[k][j];else cerr << "Err", exit(8);
		for (k = 0;k < rw;k++) for (i = 0;i < rw;i++) E[k][i] /= U[k][k];
		for (sm = i = 0;i < rw;sm += (P[i] = R[i]), i++) // ��������� ����������� ������������
			for (R[i] = j = 0;j < rw;j++)
				R[i] += E[i][j] * B[j];
		P[rw] = R[rw] = 1 - sm;// ������ ��������� ����������� �����������
		for (i = 0;i <= rw;i++) cout << "P(" << i << ")=" << P[i] << endl;// ����� ������������ ������������
		for (i = 1;i <= rw;i++) R[i] += R[i - 1];// ������ ������� ��� ��������� �������� (��������� ����� = 1 - �� �����)
		ofstream ou(nm[2], ios::binary);
		for (t = rand(), i = -1;++i < rw;) if (t < RAND_MAX * R[i]) ou.put(C + (k = i)), i = row;// ��������� ������� �������
		if (i <= row) k = rw, ou.put(c + k);
		for (i = 1;i < N;) for (t = rand() % K, j = 0;j <= rw;j++) if (t < G[k][j]) ou.put(C + (k = j)), j = row, i++;
		// ��������� ��������� ��������
		for (Q = i = 0;i <= row;i++) if (P[i] > 1e-9)Q -= P[i] * log(P[i]) / log(2.);//������� ����������� ��������
		X = 1 - Q / (log(float(row)) / log(2.));//������� ����������� ������������
		ou.close();
		for (Q_ = i = 0;i < row;Q_ -= P[i++] * q) //������� �������� ��������
			for (q = j = 0;j < row;j++)if (F[i][j])
				q += F[i][j] * log(F[i][j]) / log(2.);
		X_ = 1 - Q_ / (log(float(row)) / log(2.));//������� �������� ������������
		cout << "H(A)= " << Q << "\n x(A)=" << X << "\nn/n0=" << 1 / (1 - X) << endl;
		//����� ����������� ��������, ����������� ������������, ������������ ������ ��� ����������� ��������
		cout << "H(A|A^)=" << Q_ << "\nx(A|A^)=" << X_ << "\nn_/n0=" << 1 / (1 - X_) << endl;
		//����� �������� ��������, �������� ������������, ������������ ������ ��� ��������� ��������
		delete[]R;delete[]B;delete[]U;delete[]E;delete[]u;delete[]e;delete[]P;
	}
	delete[]g;delete[]G;delete[]d;delete[]p;
	return 0;
}