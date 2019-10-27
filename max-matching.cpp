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

	while (!q.empty()){
		now = q.front();
		q.pop();
		if (now == 1) { break; }

		for (int i = 0; i < n; ++i){
			if ((used[i] == -1) && (c[now][i] > 0)){
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
	while (i!= 0){
		w = min(w, c[used[i]][i]);
		p.push_back(i);
		i = used[i];
	}
	p.push_back(0);

	return w;
}
void capacity(vector <vector <int>>& c, vector <vector <int>> matrix, int size, int n)
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
		if (matrix[i][0] != 0)
			for (int j = 1; j < matrix[i][0] + 1; j++) {
				c[i + 2][matrix[i][j] + n + 2] = 1;
			}
	}
}
int main()
{
	int flow = 0, output = 0;
	string idx[]={"1","2","3","4","5","6"};
	string in, out;
	for (int l = 0; l < 6; l++){
		in = "D:\\max_matching\\test" + idx[l] + ".in"; 
		out = "D:\\max_matching\\test" + idx[l] + ".out";
		cout << endl << endl;
		cout << "file no. " << l+1 << endl;

		ifstream fin(in);
		int n, m;
		fin >> n >> m;
		ifstream fout(out);
		fout >> output;
	
		vector <vector <int>> matrix(n, vector <int>());
		
		int k = 0, buf=0;
		for (int i = 0; i < n; ++i) {
			fin >> k;
			matrix[i].push_back(k);
			for (int j = 0; j < k; ++j) {
				fin >> buf;
				matrix[i].push_back(buf);
			}
		}
		int size = n + m + 2;

		vector <vector <int>> c(size, vector<int>(size, 0));
		vector <vector <int>> f(size, vector<int>(size, 0));
		capacity(c, matrix, size, n);
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

		while (w = bfs(p, size, c)){		
			for (int i = 0; i < p.size() - 1; i++){
				int a = p[i + 1];
				int b = p[i];
				f[a][b] += w;
				f[b][a] -= w;
				c[a][b] -= w;
				c[b][a] += w;
			}
		}
		flow = 0;
		for (int i = 0; i < size; i++){
			flow += f[0][i];
		}

		cout << "correct: " << output << endl;
		cout << "result: " << flow << endl;
		fin.close();
		fout.close();
	}
	
	return 0;
}

