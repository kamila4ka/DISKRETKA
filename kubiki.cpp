#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

int bfs(vector <int>& p, int n, vector <vector <int>> c)
{
	p.clear();
	vector <int> used(n, -1);
	queue <int> q;
	used[0] = 0; q.push(0);
	int now;

	while (!q.empty()) {
		now = q.front();
		q.pop();
		if (now == 1) { break; }

		for (int i = 0; i < n; ++i) {
			if ((used[i] == -1) && (c[now][i] > 0)) {
				q.push(i);
				used[i] = now;
				if (i == 1) { break; }
			}
		}
	}

	if (used[1] == -1) {
		return 0;
	}
	int i = 1;
	int w = c[used[1]][1];
	while (i != 0) {
		w = min(w, c[used[i]][i]);
		p.push_back(i);
		i = used[i];
	}
	p.push_back(0);

	return w;
}

void capacity(vector <vector <int>>& c, vector <string> matrix, int size, int n, string word)
{
	c[0][1] = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j || ((j == 0) || (i == 1))) {
				c[i][j] = 0;
				continue;
			}

			if (((i == 0) && (j > 1) && (j < (n + 2)))
				|| ((j == 1) && (i > 1) && (i > (n + 1)))) {
				c[i][j] = 1;
				continue;
			}
		}
	}

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < word.size(); j++) {
			if(matrix[i].find(word[j]) != std::string::npos)
				c[i + 2][j + n + 2] = 1;
		}
	}
	/*
	for (int i = 0; i < buf.size(); i++)
	{
		for (int j = 0; j < word.size(); j++)
		{
			k = buf[i].find(word[j]);
			if (k >= 0)
			{
				c[i+2][j+n+2] = 1;
			}
		}
	}
	*/
}
int main()
{
	int flow = 0;
	string output;
	string idx[] = { "1","2","3","4","5","6", "7", "8"};
	string in, out;
	for (int l = 0; l < 8; l++) {
		in = "C:\\kubiki\\test" + idx[l] + ".in";
		out = "C:\\kubiki\\test" + idx[l] + ".out";
		cout << endl << endl;
		cout << "file no. " << l + 1 << endl;

		ifstream fin(in);
		int n;
		string word;
		fin >> n >> word;
		ifstream fout(out);
		fout >> output;
		int size = n + word.size() + 2;
		vector <string> matrix;

		string buf;
		for (int i = 0; i < n; ++i) {
				fin >> buf;
				matrix.push_back(buf);
		}

		vector <vector <int>> c(size, vector<int>(size, 0));
		vector <vector <int>> f(size, vector<int>(size, 0));
		capacity(c, matrix, size, n, word);
		/*for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << c[i][j] << " ";
			}
			cout << endl;
		}*/
		vector <int> p;
		int w;

		while (w = bfs(p, size, c)) {
			for (int i = 0; i < p.size() - 1; i++) {
				int a = p[i + 1];
				int b = p[i];
				f[a][b] += w;
				f[b][a] -= w;
				c[a][b] -= w;
				c[b][a] += w;
			}
		}
		flow = 0;
		for (int i = 0; i < size; i++) {
			flow += f[0][i];
		}
		cout << "res: ";
		if (flow == word.size())
			cout << "YES" << endl;
		else cout << "NO" << endl;
		cout << "correct: " << output << endl;
		fin.close();
		fout.close();
	}

	return 0;
}

