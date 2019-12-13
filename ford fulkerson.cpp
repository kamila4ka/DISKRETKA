
#include <iostream> 
#include <string.h> 
#include <queue> 
#include <fstream>


using namespace std;

int n;

int c[1000][1000];
int f[1000][1000];

bool bfs(vector<int>& used)
{
	vector<bool> visited(n,false);

	queue<int> q;
	q.push(0);
	visited[0] = true;
	used[0] = 0;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int b = 0; b < n; b++)
		{
			if (visited[b] == false && c[now][b] > 0)
			{
				q.push(b);
				used[b] = now;
				visited[b] = true;
			}
		}
	}

	return (visited[1] == true);
}




int main()
{

	std::ifstream in("D:\\tests\\test3.in");
	in >> n;

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			in >> c[i][j];
			cout << c[i][j] << " ";
			f[i][j] = c[i][j];
		}
		cout << endl;
	}




	vector<int> used(n,-1);

	int max_flow = 0;
	int a, b;
	while (bfs(used))
	{

		int w = 10000;
		for (b = 1; b != 0; b = used[b])
		{
			a = used[b];
			w = min(w, c[a][b]);
                }

                for (b = 1; b != 0; b = used[b])
		{
			a = used[b];
	
			c[a][b] -= w;
			c[b][a] += w;
		}

		max_flow += w;
	}

	int output;
	std::ifstream test("D:\\tests\\test3.out");
	test >> output;

	cout << "maximum flow: " << max_flow << endl;
	cout << "correct: " << output << endl;

	return 0;
}

