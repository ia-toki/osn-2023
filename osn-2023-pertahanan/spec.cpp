#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define mp make_pair
#define fr first
#define sc second

const int MXN = 2e5;
const int MXN2 = 8;
const int MXN3 = 17;
const int MXN6 = 200;
const int MXN7 = 3e3;
const int MXA8 = 200;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int N, ans;
		vector<int> A;

		void InputFormat()
		{
			LINE(N);
			LINE(A % SIZE(N));
		}
		void OutputFormat()
		{
			LINE(ans);
		}
		void GradingConfig()
		{
			TimeLimit(2);
			MemoryLimit(512);
		}
		void Constraints()
		{
			CONS(1 <= N && N <= MXN);
			CONS(eachElementBetween(A, 1, N));
		}
		void Subtask1()
		{
			Points(5);
			CONS(N == 10);
			CONS(A == vector<int>({2, 1, 2, 3, 2, 3, 4, 3, 4, 5}));
		}
		void Subtask2()
		{
			Points(8);
			CONS(N <= MXN2);
		}
		void Subtask3()
		{
			Points(7);
			CONS(N <= MXN3);
		}
		void Subtask4()
		{
			Points(7);
			CONS(eachElementSame(A));
		}
		void Subtask5()
		{
			Points(11);
			CONS(eachElementBetween(A, 1, 2));
		}
		void Subtask6()
		{
			Points(21);
			CONS(N <= MXN6);
		}
		void Subtask7()
		{
			Points(11);
			CONS(N <= MXN7);
		}
		void Subtask8()
		{
			Points(10);
			CONS(eachElementBetween(A, 1, MXA8));
		}
		void Subtask9()
		{
			Points(20);
		}

	private:
		bool eachElementBetween(vector<int> &curV, int lo, int hi)
		{
			for(int i = 0; i < curV.size(); i++)
			{
				if(!(lo <= curV[i] && curV[i] <= hi))
				{
					return false;
				}
			}
			return true;
		}
		bool eachElementSame(vector<int> &curV)
		{
			for(int i = 0; i < curV.size() - 1; i++)
			{
				if(curV[i] != curV[i + 1])
				{
					return false;
				}
			}
			return true;
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({2, 3, 6, 7, 8, 9});
			Input
			({
				"7",
				"2 2 3 2 1 4 2",
			});
			Output
			({
				"3",
			});
		}
		void BeforeTestCase()
		{
			A.clear();
		}
		void TestGroup1()
		{
			Subtasks({1, 3, 6, 7, 8, 9});
			
			// Case (1)
			CASE(N = 10, A = {2, 1, 2, 3, 2, 3, 4, 3, 4, 5});
		}
		void TestGroup2()
		{
			Subtasks({2, 3, 4, 5, 6, 7, 8, 9});
			
			// Case (1-4)
			CASE(N = 1, A = {1});
			CASE(N = 2, A = {1, 1});
			CASE(N = 2, A = {2, 2});
			CASE(N = 3, A = {2, 2, 2});
		}
		void TestGroup3()
		{
			Subtasks({2, 3, 4, 6, 7, 8, 9});
			
			// Case (1)
			CASE(N = 3, A = {3, 3, 3});
		}
		void TestGroup4()
		{
			Subtasks({2, 3, 5, 6, 7, 8, 9});
			
			// Case (1-3)
			CASE(N = 2, A = {1, 2});
			CASE(N = 2, A = {2, 1});
			CASE(N = 3, A = {1, 2, 2});
		}
		void TestGroup5()
		{
			Subtasks({2, 3, 6, 7, 8, 9});
			
			// Case (1-2) rand
			CASE(N = rnd.nextInt(3, MXN2), A = randArray(N, 1, N));
			CASE(N = MXN2, A = randArray(N, 1, N));
			
			// Case (3-4) generate from perfect array
			CASE(N = MXN2, A = perfectArray(N, N, 1));
			CASE(N = MXN2, A = perfectArray(N, N, 2), addExtra(sqrt(N), 1, N));
			
			// Case (5) sorted
			CASE(N = MXN2, A = decreasingArray(N, 1, N));
			
			// Case (6) almost all same
			CASE(N = MXN2, A = sameArray(N, N), A[N - 1]--);
			
			// Case (7-9) same, then A[i]=i
			CASE(N = MXN2, A = sameThenConsecutiveArray(N, N / 2, 1, 0));
			CASE(N = MXN2, A = sameThenConsecutiveArray(N, N * 2 / 3, 2, 0));
			CASE(N = MXN2, A = sameThenConsecutiveArray(N, (N + 1) / 2 + 1, 1, 0));
			
			// Case (10) almost reachable
			CASE(N = MXN2, A = almostReachableArray(N, N));
			
			// Case (11) two mixed perfect arrays
			CASE(N = MXN2, A = twoMixedPerfectArrays(N, N, 2, 2));
		}
		void TestGroup6()
		{
			Subtasks({3, 6, 7, 8, 9});
			
			// Case (1-2) rand
			CASE(N = rnd.nextInt(MXN2 + 1, MXN3), A = randArray(N, 1, N));
			CASE(N = MXN3, A = randArray(N, 1, N));
			
			// Case (3-5) generate from perfect array
			CASE(N = MXN3, A = perfectArray(N, N, 1));
			CASE(N = MXN3, A = perfectArray(N, N, 2), addExtra(sqrt(N), 1, N));
			CASE(N = MXN3, A = perfectArray(N, N, 3), addExtra(sqrt(N), 1, N));
			
			// Case (6) sorted
			CASE(N = MXN3, A = decreasingArray(N, 1, N));
			
			// Case (7) almost all same
			CASE(N = MXN3, A = sameArray(N, N), A[N - 1]--);
			
			// Case (8-10) same, then A[i]=i
			CASE(N = MXN3, A = sameThenConsecutiveArray(N, N / 2, 1, 0));
			CASE(N = MXN3, A = sameThenConsecutiveArray(N, N * 2 / 3, 2, 0));
			CASE(N = MXN3, A = sameThenConsecutiveArray(N, (N + 1) / 2 + 1, 1, 0));
			
			// Case (11) almost reachable
			CASE(N = MXN3, A = almostReachableArray(N, N));
			
			// Case (12) two mixed perfect arrays
			CASE(N = MXN3, A = twoMixedPerfectArrays(N, N, 3, 3));
		}
		void TestGroup7()
		{
			Subtasks({4, 5, 8, 9});
			
			// Case (1-4)
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = sameArray(N, 1));
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = sameArray(N, 2));
			CASE(N = MXN, A = sameArray(N, 1));
			CASE(N = MXN, A = sameArray(N, 2));
		}
		void TestGroup8()
		{
			Subtasks({4, 8, 9});
			
			// Case (1-2)
			CASE(N = MXN, A = sameArray(N, 3));
			CASE(N = MXN, A = sameArray(N, 10));
		}
		void TestGroup9()
		{
			Subtasks({4, 9});
			
			// Case (1-8)
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = sameArray(N, sqrt(N) + rnd.nextInt(-10, 10)));
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = sameArray(N, N));
			CASE(N = MXN, A = sameArray(N, sqrt(N) + rnd.nextInt(-10, 10)));
			CASE(N = MXN / (int)sqrt(MXN) * (int)sqrt(MXN), A = sameArray(N, sqrt(N)));
			CASE(N = MXN, A = sameArray(N, N / 2));
			CASE(N = MXN - 1, A = sameArray(N, N / 2));
			CASE(N = MXN, A = sameArray(N, N));
			CASE(N = MXN, A = sameArray(N, N - 1));
		}
		void TestGroup10()
		{
			Subtasks({5, 8, 9});
			
			// Case (1-2) rand
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = randArray(N, 1, 2));
			CASE(N = MXN, A = randArray(N, 1, 2));
			
			// Case (3-4) fixed number of cc
			CASE(N = MXN, A = fixedCCArray(N, sqrt(N)));
			CASE(N = MXN, A = fixedCCArray(N, 10));
			
			// Case (5) every cc has odd size
			CASE(N = MXN, A = oddCCArray(N, sqrt(N)));
			
			// Case (6) alternating
			CASE(N = MXN, A = alternatingArray(N));
			
			// Case (7-12) almost all same
			CASE(N = MXN, A = sameArray(N, 1), A[0] = 2);
			CASE(N = MXN, A = sameArray(N, 1), A[N - 1] = 2);
			CASE(N = MXN, A = sameArray(N, 2), A[0] = 1);
			CASE(N = MXN, A = sameArray(N, 2), A[N - 1] = 1);
			CASE(N = MXN, A = sameArray(N, 2), A[N / 2 - 1] = 1);
			CASE(N = MXN, A = sameArray(N, 2), A[N / 2] = 1);
		}
		void TestGroup11()
		{
			Subtasks({6, 7, 8, 9});
			
			// Case (1-3) rand
			CASE(N = rnd.nextInt(MXN3 + 1, MXN6), A = randArray(N, 1, N));
			CASE(N = MXN6, A = randArray(N, 1, N));
			CASE(N = MXN6, A = wrandArray(N, 1, N, -10));
			
			// Case (4-5) many same value of A[i]-i
			CASE(N = MXN6, A = manySameArray(N, 1, N, sqrt(N), sqrt(N)), addExtra(sqrt(N), 1, N));
			CASE(N = MXN6, A = manySameArray(N, 1, N, sqrt(N), 2), addExtra(sqrt(N), 1, N));
			
			// Case (6-9) generate from perfect array
			CASE(N = MXN6, A = perfectArray(N, N, 1));
			CASE(N = MXN6, A = perfectArray(N, N, 2), addExtra(sqrt(N), 1, N));
			CASE(N = MXN6, A = perfectArray(N, N, 3), addExtra(sqrt(N), 1, N));
			CASE(N = MXN6, A = perfectArray(N, N, sqrt(N)));
			
			// Case (10-12) sorted
			CASE(N = MXN6, A = decreasingArray(N, 1, N));
			CASE(N = MXN6, A = nonDecreasingArray(N, 1, N));
			CASE(N = MXN6, A = nonIncreasingArray(N, 1, N));
			
			// Case (13-14) almost all same
			CASE(N = MXN6, A = sameArray(N, 1), A[rnd.nextInt(2, N - 1)] = 3);
			CASE(N = MXN6, A = sameArray(N, N), A[N - 1]--);
			
			// Case (15-17) same, then A[i]=i
			CASE(N = MXN6, A = sameThenConsecutiveArray(N, N / 2, 1, 0));
			CASE(N = MXN6, A = sameThenConsecutiveArray(N, N * 2 / 3, 2, 0));
			CASE(N = MXN6, A = sameThenConsecutiveArray(N, (N + 1) / 2 + 1, 1, 0));
			
			// Case (18) almost reachable
			CASE(N = MXN6, A = almostReachableArray(N, N));
			
			// Case (19-20) two mixed perfect arrays
			CASE(N = MXN6, A = twoMixedPerfectArrays(N, N, 3, 3));
			CASE(N = MXN6, A = twoMixedPerfectArrays(N, N, 10, 10));
		}
		void TestGroup12()
		{
			Subtasks({7, 9});
			
			// Case (1-3) rand
			CASE(N = rnd.nextInt(MXN6 + 1, MXN7), A = randArray(N, 1, N));
			CASE(N = MXN7, A = randArray(N, 1, N));
			CASE(N = MXN7, A = wrandArray(N, 1, N, -10));
			
			// Case (4-5) many same value of A[i]-i
			CASE(N = MXN7, A = manySameArray(N, 1, N, sqrt(N), sqrt(N)), addExtra(sqrt(N), 1, N));
			CASE(N = MXN7, A = manySameArray(N, 1, N, sqrt(N), 2), addExtra(sqrt(N), 1, N));
			
			// Case (6-9) generate from perfect array
			CASE(N = MXN7, A = perfectArray(N, N, 1));
			CASE(N = MXN7, A = perfectArray(N, N, 2), addExtra(sqrt(N), 1, N));
			CASE(N = MXN7, A = perfectArray(N, N, 3), addExtra(sqrt(N), 1, N));
			CASE(N = MXN7, A = perfectArray(N, N, sqrt(N)), addExtra(sqrt(N), 1, N));
			
			// Case (10-12) sorted
			CASE(N = MXN7, A = decreasingArray(N, 1, N));
			CASE(N = MXN7, A = nonDecreasingArray(N, 1, N));
			CASE(N = MXN7, A = nonIncreasingArray(N, 1, N));
			
			// Case (13-14) almost all same
			CASE(N = MXN7, A = sameArray(N, 1), A[rnd.nextInt(MXA8, N - 1)] = MXA8 + 1);
			CASE(N = MXN7, A = sameArray(N, N), A[N - 1]--);
			
			// Case (15-17) same, then A[i]=i
			CASE(N = MXN7, A = sameThenConsecutiveArray(N, N / 2, 1, 0));
			CASE(N = MXN7, A = sameThenConsecutiveArray(N, N * 2 / 3, 2, 0));
			CASE(N = MXN7, A = sameThenConsecutiveArray(N, (N + 1) / 2 + 1, 1, 0));
			
			// Case (18) almost reachable
			CASE(N = MXN7, A = almostReachableArray(N, N));
			
			// Case (19-20) two mixed perfect arrays
			CASE(N = MXN7, A = twoMixedPerfectArrays(N, N, 3, 3));
			CASE(N = MXN7, A = twoMixedPerfectArrays(N, N, 10, 10));
		}
		void TestGroup13()
		{
			Subtasks({8, 9});
			
			// Case (1-3) rand
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = randArray(N, 1, MXA8));
			CASE(N = MXN, A = randArray(N, 1, MXA8));
			CASE(N = MXN, A = wrandArray(N, 1, MXA8, -10));
			
			// Case (4-5) many same value of A[i]-i
			CASE(N = MXN, A = manySameArray(N, 1, MXA8, N / MXA8, N / MXA8), addExtra(sqrt(N), 1, MXA8));
			CASE(N = MXN, A = manySameArray(N, 1, MXA8, N / MXA8, 2), addExtra(sqrt(N), 1, MXA8));
			
			// Case (6-7) generate from perfect array
			CASE(N = MXN, A = perfectArray(N, MXA8, N / MXA8));
			CASE(N = MXN, A = perfectArray(N, MXA8, N / MXA8), addExtra(sqrt(N), 1, MXA8));
			
			// Case (8) sorted
			CASE(N = MXN, A = nonIncreasingArray(N, 1, MXA8));
			
			// Case (9-10) almost all same
			CASE(N = MXN, A = sameArray(N, 1), A[rnd.nextInt(2, N - 1)] = 3);
			CASE(N = MXN, A = sameArray(N, MXA8), A[N - 1]--);
			
			// Case (11-13) same, then A[i]=i
			CASE(N = MXN, A = sameThenConsecutiveArray(N, N - MXA8 + MXA8 / 2, 1, N - MXA8));
			CASE(N = MXN, A = sameThenConsecutiveArray(N, N - MXA8 + MXA8 * 2 / 3, 2, N - MXA8));
			CASE(N = MXN, A = sameThenConsecutiveArray(N, N - MXA8 + (MXA8 + 1) / 2 + 1, 1, N - MXA8));
			
			// Case (14) almost reachable
			CASE(N = MXN, A = almostReachableArray(N, MXA8));
			
			// Case (15) two mixed perfect arrays
			CASE(N = MXN, A = twoMixedPerfectArrays(N, MXA8, N / MXA8, N / MXA8));
		}
		void TestGroup14()
		{
			Subtasks({9});
			
			// Case (1-4) rand
			CASE(N = rnd.nextInt(MXN7 + 1, MXN), A = randArray(N, 1, N));
			CASE(N = MXN, A = randArray(N, 1, N));
			CASE(N = MXN, A = wrandArray(N, 1, N, -10));
			CASE(N = MXN, A = wrandArray(N, 1, N, -100));
			
			// Case (5-7) many same value of A[i]-i
			CASE(N = MXN, A = manySameArray(N, 1, N, sqrt(N), sqrt(N)), addExtra(sqrt(N), 1, N));
			CASE(N = MXN, A = manySameArray(N, 1, N, sqrt(N), 2), addExtra(sqrt(N), 1, N));
			CASE(N = MXN, A = manySameArray(N, 1, N, 10, 2), addExtra(sqrt(N), 1, N));
			
			// Case (8-11) generate from perfect array
			CASE(N = MXN, A = perfectArray(N, N, 1));
			CASE(N = MXN, A = perfectArray(N, N, 2), addExtra(sqrt(N), 1, N));
			CASE(N = MXN, A = perfectArray(N, N, 3), addExtra(sqrt(N), 1, N));
			CASE(N = MXN, A = perfectArray(N, N, sqrt(N)));
			
			// Case (12-14) sorted
			CASE(N = MXN, A = decreasingArray(N, 1, N));
			CASE(N = MXN, A = nonDecreasingArray(N, 1, N));
			CASE(N = MXN, A = nonIncreasingArray(N, 1, N));
			
			// Case (15-16) almost all same
			CASE(N = MXN, A = sameArray(N, 1), A[rnd.nextInt(MXA8, N - 1)] = MXA8 + 1);
			CASE(N = MXN, A = sameArray(N, N), A[N - 1]--);
			
			// Case (17-19) same, then A[i]=i
			CASE(N = MXN, A = sameThenConsecutiveArray(N, N / 2, 1, 0));
			CASE(N = MXN, A = sameThenConsecutiveArray(N, N * 2 / 3, 2, 0));
			CASE(N = MXN, A = sameThenConsecutiveArray(N, (N + 1) / 2 + 1, 1, 0));
			
			// Case (20) almost reachable
			CASE(N = MXN, A = almostReachableArray(N, N));
			
			// Case (21-22) two mixed perfect arrays
			CASE(N = MXN, A = twoMixedPerfectArrays(N, N, 3, 3));
			CASE(N = MXN, A = twoMixedPerfectArrays(N, N, 10, 10));
		}

	private:
		int wrand(int lo, int hi, int deg)
		{
			int ret = rnd.nextInt(lo, hi);
			
			if(deg > 0)
			{
				for(int i = 0; i < deg; i++)
				{
					ret = max(ret, rnd.nextInt(lo, hi));
				}
			}
			else if(deg < 0)
			{
				for (int i = 0; i < -deg; i++)
				{
					ret = min(ret, rnd.nextInt(lo, hi));
				}
			}
			return ret;
		}
		vector<int> randArray(int sz, int lo, int hi)
		{
			vector<int> ret;
			
			for(int i = 0; i < sz; i++)
			{
				ret.push_back(rnd.nextInt(lo, hi));
			}
			return ret;
		}
		vector<int> nonDecreasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = randArray(sz, lo, hi);
			
			sort(ret.begin(), ret.end());
			return ret;
		}
		vector<int> nonIncreasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = randArray(sz, lo, hi);
			
			sort(ret.begin(), ret.end(), greater<int>());
			return ret;
		}
		vector<int> increasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = nonDecreasingArray(sz, lo, hi - (sz - 1));
			
			for(int i = 0; i < sz; i++)
			{
				ret[i] += i;
			}
			return ret;
		}
		vector<int> decreasingArray(int sz, int lo, int hi)
		{
			vector<int> ret = increasingArray(sz, lo, hi);
			
			reverse(ret.begin(), ret.end());
			return ret;
		}
		vector<int> distinctArray(int sz, int lo, int hi)
		{
			vector<int> ret = increasingArray(sz, lo, hi);
			
			rnd.shuffle(ret.begin(), ret.end());
			return ret;
		}
		vector<int> sameArray(int sz, int val)
		{
			vector<int> ret(sz, val);
			
			return ret;
		}
		vector<int> wrandArray(int sz, int lo, int hi, int deg)
		{
			vector<int> ret;
			
			for(int i = 0; i < sz; i++)
			{
				ret.push_back(wrand(lo, hi, deg));
			}
			return ret;
		}
		vector<int> manySameArray(int sz, int lo, int hi, int cnt, int mxDis)
		{
			vector<int> vals, ret;
			
			vals =  increasingArray(cnt, 0, sz - 1);
			for(int i = 1; i <= sz; i++)
			{
				int p, p2;
				
				p = lower_bound(vals.begin(), vals.end(), i - hi) - vals.begin();
				p2 = upper_bound(vals.begin(), vals.end(), i - lo) - vals.begin() - 1;
				if(p <= p2)
				{
					int k;
					
					p = max(p, p2 - mxDis + 1);
					k = rnd.nextInt(p, p2);
					ret.push_back(i - vals[k]);
				}
				else
				{
					ret.push_back(rnd.nextInt(lo, hi));
				}
			}
			return ret;
		}
		vector<int> perfectArray(int sz, int hi, int cnt)
		{
			int val;
			bool special[sz + 69];
			vector<int> pos, ret;
			
			for(int i = 0; i < sz; i++)
			{
				special[i] = false;
			}
			special[0] = true;
			pos = increasingArray(cnt - 1, 1, sz - 1);
			for(int i = 0; i < pos.size(); i++)
			{
				special[pos[i]] = true;
			}
			for(int i = 0; i < sz; i++)
			{
				if(special[i])
				{
					val = 1;
				}
				else
				{
					val++;
				}
				ret.push_back(val);
			}
			for(int i = sz - 1; i >= 0; i--)
			{
				ret[i] = min(ret[i], hi);
				if(!special[i])
				{
					ret[i - 1] = max(ret[i] - 1, 1);
				}
			}
			return ret;
		}
		vector<int> sameThenConsecutiveArray(int sz, int cnt, int val, int offset)
		{
			vector<int> ret;
			
			for(int i = 1; i <= sz; i++)
			{
				if(i <= cnt)
				{
					ret.push_back(val);
				}
				else
				{
					ret.push_back(i - offset);
				}
			}
			return ret;
		}
		vector<int> almostReachableArray(int sz, int hi)
		{
			vector<int> ret;
			
			for(int i = 1; i <= sz; i++)
			{
				ret.push_back(min(i + 1, hi));
			}
			return ret;
		}
		vector<int> twoMixedPerfectArrays(int sz, int hi, int cnt, int cnt2)
		{
			vector<int> tmp, ret;
			
			ret = perfectArray(sz, hi, cnt);
			tmp = perfectArray(sz, hi, cnt2);
			for(int i = 0; i < sz; i++)
			{
				if(rnd.nextInt(0, 1))
				{
					ret[i] = tmp[i];
				}
			}
			return ret;
		}
		vector<int> fixedCCArray(int sz, int cnt)
		{
			int p, val;
			vector<int> pos, ret;
			
			pos = increasingArray(cnt * 2, 1, sz + 1);
			p = 0;
			val = 1;
			for(int i = 1; i <= sz; i++)
			{
				if(p < pos.size() && pos[p] == i)
				{
					val = val % 2 + 1;
					p++;
				}
				ret.push_back(val);
			}
			return ret;
		}
		vector<int> oddCCArray(int sz, int cnt)
		{
			int p, val;
			vector<int> pos, ret;
			
			pos = increasingArray(cnt * 2, 1, sz + 1);
			for(int i = 0; i < cnt * 2; i += 2)
			{
				if((pos[i + 1] - pos[i]) % 2 == 0)
				{
					pos[i]++;
				}
			}
			p = 0;
			val = 1;
			for(int i = 1; i <= sz; i++)
			{
				if(p < pos.size() && pos[p] == i)
				{
					val = val % 2 + 1;
					p++;
				}
				ret.push_back(val);
			}
			return ret;
		}
		vector<int> alternatingArray(int sz)
		{
			vector<int> ret;
			
			for(int i = 1; i <= sz; i++)
			{
				ret.push_back((i - 1) % 2 + 1);
			}
			return ret;
		}
		void addExtra(int cnt, int lo, int hi)
		{
			for(int i = 0; i < cnt; i++)
			{
				int p = rnd.nextInt(0, N - 1);
				
				A[p] = rnd.nextInt(lo, hi);
			}
		}
};
