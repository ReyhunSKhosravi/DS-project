#include <bits/stdc++.h>
using namespace std;

struct Hash {
	long long p = 31, m = 1e9 + 7;
	long long hash_value;
	Hash(const string& s)
	{
		long long hash_so_far = 0;
		long long p_pow = 1;
		const long long n = s.length();
		for (long long i = 0; i < n; ++i) {
			hash_so_far
				= (hash_so_far + (s[i] - 'a' + 1) * p_pow)
				% m;
			p_pow = (p_pow * p) % m;
		}
		hash_value = hash_so_far;
	}
	bool operator==(const Hash& other)
	{
		return (hash_value == other.hash_value);
	}
};

int main()
{
	const string s = "zeynabeslamishakib hastammmmm";
	Hash h(s);
	cout << "Hash of " << s << " is: " << h.hash_value
		<< '\n';
	return 0;
}
