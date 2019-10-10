#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
int n;
char c[100][100] = { 0 };
int kolvo; // kolichestvo bukv v slove w
string w;

bool bfs(string& used) {
	vector<bool> visited(100, false);

	for (int i = 0; i < kolvo; ++i)
		for (int k = 0; k < n; ++k) 
			for (int j = 0; j < 6; ++j)
				if (!visited[k] && c[k][j] == w[i]) {
					visited[k] = true;
					used.push_back(w[i]);
					if (k != n - 1)
						++i;
				}
		
	return (used == w);
}

int main()
{
	std::ifstream in("D:\\tests\\test4.in");
	in >> n;
	in >> w;
	kolvo = w.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 6; ++j) {
			in >> c[i][j];
		}
	} // chtenie iz faila

	string used;
	bool search = bfs(used);
	if (search)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}
