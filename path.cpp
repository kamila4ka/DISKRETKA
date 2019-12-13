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


int main() {

	int flow = 0, output = 0;
	string idx[] = { "1","2","3","4","5","6", "7", "8" };
	string in, out;
	for (int l = 0; l < 8; l++) {
		in = "C:\\tests\\test" + idx[l] + ".in";
		out = "C:\\tests\\test" + idx[l] + ".out";
		cout << endl << endl;
		cout << "file no. " << l + 1 << endl;

		ifstream fin(in);
		int n;
		fin >> n;
		ifstream fout(out);
		fout >> output;

		vector <vector <int>> c(n, vector <int>(n, 0));

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				fin >> c[i][j];
			}
		}

		vector <int> p;
		int w;
		int maxpath = 0;
		while (w = bfs(p, n, c)) {
			if (w > maxpath) maxpath = w;
			for (int i = 0; i < p.size() - 1; i++) {
				int a = p[i + 1];
				int b = p[i];
				if (c[a][b] <= w)
					c[a][b] = 0;
			}
		}


		cout << "correct: " << output << endl;
		cout << "result: " << maxpath << endl;
		fin.close();
		fout.close();
	}

	return 0;

}
