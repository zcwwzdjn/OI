/*
 * $File: naj.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given alphabet with k letters, and each letter
 *   has a cost, we say the cost of a word is the
 *   sum of cost of the letters in it. Find a set
 *   of words consist of exactly n words, and no two
 *   words (u, v) and u is prefix of v, with minimal
 *   sum of cost.
 *
 * Solution:
 *   Greedy. In each move we expand out set of words by
 *   this way: choose the word with minimal cost, erase it
 *   and append letters to it and add them into the set.
 *   When the size of set reaches n, we update our answer.
 *   Once the sum of cost of words in set is more than
 *   current answer, we can stop the expansion.
 *   I use a BST to implement.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;
int n, k, w[26], res;
multiset<int> s;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; ++ i) scanf("%d", &w[i]);
	sort(w, w + k);
	if (k >= n) {
		res = 0;
		for (int i = 0; i < n; ++ i) res += w[i];
		printf("%d\n", res);
		return 0;
	}
	res = 0x3f3f3f3f;
	int tmp = 0;
	for (int i = 0; i < k; ++ i) s.insert(w[i]), tmp += w[i];
	while (true) {
		while ((int)s.size() > n) {
			multiset<int>::iterator it = s.end();
			-- it;
			tmp -= *it;
			s.erase(it);
		}
		if ((int)s.size() == n) {
			if (tmp >= res) break;
			res = tmp;
			int u = *s.begin();
			s.erase(s.begin()), tmp -= u;
			for (int i = 0; i < k; ++ i)
				s.insert(u + w[i]), tmp += u + w[i];
		}
		else {
			int u = *s.begin();
			s.erase(s.begin()), tmp -= u;
			for (int i = 0; i < k; ++ i)
				s.insert(u + w[i]), tmp += u + w[i];
		}
	}
	printf("%d\n", res);
	return 0;
}
