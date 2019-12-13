#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

unsigned long long int fib(unsigned long long int n, unsigned long long int p) {
	unsigned long long int a = 1, ta,
		b = 1, tb,
		c = 1, rc = 0, tc,
		d = 0, rd = 1;

	while (n)
	{
		if (n & 1)
		{
			tc = rc;
			rc = (rc * a + rd * c); 
			rd = (tc * b + rd * d);
			
		}

		ta = a; tb = b; tc = c;
		a = (a * a + b * c);
		b = ((ta * b) + b * d);
		c = ((c * ta) + (d * c));
		d = ((tc * tb) + (d * d));
		if (a > p&& b > p&& c > p && d > p)
		{
			a %= p;
			b %= p;
			c %= p;
			d %= p;

		}
		if (rc > p&& rd > p) {
			rc %= p;
			rd %= p;
		}
		n >>= 1;
	}

	return rc%p;
}

int main() 
{
	string in, out;
	for (int l = 400; l < 405; l++) {
		in = "C:\\fib\\test" + std::to_string(l+1) + ".in";
		out = "C:\\fib\\test" + std::to_string(l + 1) + ".out";
		ifstream fin(in);
		ifstream fout(out);
		unsigned long long int n, p, output;
		fin >> n >> p;
		fout >> output;
		int res = fib(n, p);
		//if (res != output) {
			cout << "file no." << l + 1 << endl << "res: " << res << endl;
			cout << "correct: " << output << endl << endl;
		}
	//}

	return 0;
}
