#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

#define mp make_pair
#define fr first
#define sc second

const int MXN = 1e5, MXM = 2e5;
const int MXN2 = 50, MXM2 = 100;
const int MXN3 = 300, MXM3 = 600;
const int MXN4 = 2e3, MXM4 = 4e3;
const int MXDEG9 = 40;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int N, M;
		vector<int> U, V;
		long long ans;

		void InputFormat()
		{
			LINE(N, M);
			LINES(U, V) % SIZE(M);
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
			CONS(0 <= M && M <= MXM);
			CONS(eachElementBetween(U, 1, N));
			CONS(eachElementBetween(V, 1, N));
			CONS(noSelfLoopMultiEdge(U, V));
		}
		void Subtask1()
		{
			Points(6);
			CONS(N == 4);
			CONS(M == 4);
			CONS(U == vector<int>({2, 3, 1, 1}));
			CONS(V == vector<int>({4, 4, 3, 4}));
		}
		void Subtask2()
		{
			Points(12);
			CONS(N <= MXN2);
			CONS(M <= MXM2);
		}
		void Subtask3()
		{
			Points(6);
			CONS(N <= MXN3);
			CONS(M <= MXM3);
		}
		void Subtask4()
		{
			Points(11);
			CONS(N <= MXN4);
			CONS(M <= MXM4);
		}
		void Subtask5()
		{
			Points(7);
			CONS(checkMaxCCSize(N, U, V, 2, N));
		}
		void Subtask6()
		{
			Points(9);
			CONS(checkMaxCCSize(N, U, V, 3, 1));
		}
		void Subtask7()
		{
			Points(8);
			CONS(checkMaxCCSize(N, U, V, 3, N));
		}
		void Subtask8()
		{
			Points(18);
			CONS(oneLeftOneRightEdge(N, U, V));
		}
		void Subtask9()
		{
			Points(11);
			CONS(checkMaxDeg(N, U, V, MXDEG9));
		}
		void Subtask10()
		{
			Points(12);
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
		bool noSelfLoopMultiEdge(vector<int> &curU, vector<int> &curV)
		{
			vector<pair<int, int>> edges;
			
			for(int i = 0; i < curU.size(); i++)
			{
				if(curU[i] >= curV[i])
				{
					return false;
				}
				edges.push_back({curU[i], curV[i]});
			}
			sort(edges.begin(), edges.end());
			for(int i = 1; i < curU.size(); i++)
			{
				if(edges[i] == edges[i - 1])
				{
					return false;
				}
			}
			return true;
		}
		int dsu[MXN + 69];
		int unionFind(int x)
		{
			if(dsu[x] != x)
			{
				dsu[x] = unionFind(dsu[x]);
			}
			return dsu[x];
		}
		bool checkMaxCCSize(int curN, vector<int> &curU, vector<int> &curV, int hi, int mxCnt)
		{
			int CCSize[curN + 69], cnt;
			
			for(int i = 1; i <= curN; i++)
			{
				dsu[i] = i;
				CCSize[i] = 1;
			}
			for(int i = 0; i < curU.size(); i++)
			{
				int k, l;
				
				k = unionFind(curU[i]);
				l = unionFind(curV[i]);
				if(k != l)
				{
					CCSize[k] += CCSize[l];
					dsu[l] = k;
				}
			}
			cnt = 0;
			for(int i = 1; i <= curN; i++)
			{
				if(unionFind(i) == i)
				{
					if(CCSize[i] > hi)
					{
						return false;
					}
					if(CCSize[i] == hi)
					{
						cnt++;
					}
				}
			}
			if(cnt > mxCnt)
			{
				return false;
			}
			return true;
		}
		bool oneLeftOneRightEdge(int curN, vector<int> &curU, vector<int> &curV)
		{
			bool hasLeft[curN + 69], hasRight[curN + 69];
			
			for(int i = 1; i <= curN; i++)
			{
				hasLeft[i] = false;
				hasRight[i] = false;
			}
			for(int i = 0; i < curU.size(); i++)
			{
				int k, l;
				
				k = curU[i];
				l = curV[i];
				if(hasRight[k])
				{
					return false;
				}
				hasRight[k] = true;
				if(hasLeft[l])
				{
					return false;
				}
				hasLeft[l] = true;
			}
			return true;
		}
		bool checkMaxDeg(int curN, vector<int> &curU, vector<int> &curV, int mxDeg)
		{
			int deg[curN + 69], mx;
			
			for(int i = 1; i <= curN; i++)
			{
				deg[i] = 0;
			}
			for(int i = 0; i < curU.size(); i++)
			{
				int k, l;
				
				k = curU[i];
				l = curV[i];
				deg[k]++;
				deg[l]++;
			}
			mx = 0;
			for(int i = 1; i <= curN; i++)
			{
				mx = max(mx, deg[i]);
			}
			if(mx > mxDeg)
			{
				return false;
			}
			return true;
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({2, 3, 4, 9, 10});
			Input
			({
				"11 14",
				"1 5",
				"1 8",
				"2 4",
				"2 5",
				"2 10",
				"3 6",
				"3 7",
				"4 8",
				"4 9",
				"5 10",
				"8 9",
				"8 11",
				"9 11",
				"10 11",
			});
			Output
			({
				"128",
			});
		}
		void SampleTestCase2()
		{
			Subtasks({2, 3, 4, 9, 10});
			Input
			({
				"4 3",
				"2 4",
				"1 2",
				"2 3",
			});
			Output
			({
				"10",
			});
		}
		void BeforeTestCase()
		{
			U.clear();
			V.clear();
		}
		void AfterTestCase()
		{
			for(int i = 0; i < M; i++)
			{
				if(U[i] > V[i])
				{
					swap(U[i], V[i]);
				}
			}
		}
		void TestGroup1()
		{
			Subtasks({1, 2, 3, 4, 9, 10});
			
			CASE(N = 4, M = 4, U = {2, 3, 1, 1}, V = {4, 4, 3, 4});
		}
		void TestGroup2()
		{
			Subtasks({2, 3, 4, 5, 6, 7, 8, 9, 10});
			
			// Case (1) M = 0
			CASE(N = MXN2, M = 0);
			
			// Case (2) all CC of size 2
			CASE(N = MXN2, M = N / 2, sameSizeCCCompleteGraph(N, 2), shuffleVertices(), shuffleEdges());
			
			// Case (3-5) small N M
			CASE(N = 1, M = 0);
			CASE(N = 2, M = 0);
			CASE(N = 2, M = 1, U = {1}, V = {2});
		}
		void TestGroup3()
		{
			Subtasks({2, 3, 4, 6, 7, 8, 9, 10});
			
			// Case (1) small N M
			CASE(N = 3, M = 2, U = {2, 1}, V = {3, 2});
		}
		void TestGroup4()
		{
			Subtasks({2, 3, 4, 6, 7, 9, 10});
			
			// Case (1) small N M
			CASE(N = 3, M = 3, U = {2, 1, 1}, V = {3, 3, 2});
		}
		void TestGroup5()
		{
			Subtasks({2, 3, 4, 9, 10});
			
			// Case (1-3) rand graph
			CASE(N = rnd.nextInt(1, MXN2), M = rnd.nextInt(0, min((long long)MXM2, (long long)N * (N - 1) / 2)), randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = MXM2, randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = MXM2, randGraph(N, M), shuffleVertices(), shuffleEdges());
			
			// Case (4-5) fixed number of CC
			CASE(N = MXN2, M = MXM2, fixedCCGraph(N, M, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = MXM2, fixedCCGraph(N, M, 2), shuffleVertices(), shuffleEdges());
			
			// Case (6) line
			CASE(N = MXN2, M = N - 1, lineGraph(N), shuffleVertices(), shuffleEdges());
			
			// Case (7-8) multiple line plus extra edges
			CASE(N = MXN2, M = MXM2, multiLinePlusGraph(N, M, 1), shuffleEdges());
			CASE(N = MXN2, M = MXM2, multiLinePlusGraph(N, M, sqrt(N)), shuffleEdges());
			
			// Case (9-10) cycle
			CASE(N = MXN2, M = N, cycleGraph(N), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = N, cycleGraph(N));
			
			// Case (11) M = 3
			CASE(N = MXN2, M = 3, starGraph(4, 1), shuffleVertices(), shuffleEdges());
			
			// Case (12-15) makes dumb DSU TLE
			CASE(N = MXN2, M = MXM2, antiHaramDSUGraph(N, M, 0));
			CASE(N = MXN2, M = MXM2, antiHaramDSUGraph(N, M, 1));
			CASE(N = MXN2, M = MXM2, antiHaramDSUGraph(N, M, 0), reverseVertices(), reverseEdges());
			CASE(N = MXN2, M = MXM2, antiHaramDSUGraph(N, M, 1), reverseVertices(), reverseEdges());
			
			// Case (16-18) all CC is complete graph same size, except 1
			CASE(N = MXN2, M = N / 2 + 2, sameSizeCCCompleteGraph(N, 2), U.push_back(1), V.push_back(3), U.push_back(2), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = N / 3 * 3 + 1, sameSizeCCCompleteGraph(N, 3), U.push_back(1), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN2, M = N / 5 * 10, sameSizeCCCompleteGraph(N, 5), shuffleVertices(), shuffleEdges());
			
			// Case (19) fibonacci graph
			CASE(N = MXN2, M = N * 2 - 3, fibonacciGraph(N));
			
			// Case (20) complete graph
			CASE(N = MXN2, M = 14*13/2, completeGraph(14), shuffleVertices(), shuffleEdges());
		}
		void TestGroup6()
		{
			Subtasks({2, 3, 4, 10});
			
			// Case (1) rand graph with some high degree vertices
			CASE(N = MXN2, M = MXM2, highDegreeGraph(N, M, N - 2, 2), shuffleVertices(), shuffleEdges());
			
			// Case (2) star
			CASE(N = MXN2, M = N - 1, starGraph(N, N / 2));
			
			// Case (3) star plus line
			CASE(N = MXN2, M = N * 2 - 4, starLineGraph(N, N / 2));
		}
		void TestGroup7()
		{
			Subtasks({3, 4, 5, 6, 7, 8, 9, 10});
			
			// Case (1) M = 0
			CASE(N = MXN3, M = 0);
			
			// Case (2) all CC of size 2
			CASE(N = MXN3, M = N / 2, sameSizeCCCompleteGraph(N, 2), shuffleVertices(), shuffleEdges());
		}
		void TestGroup8()
		{
			Subtasks({3, 4, 9, 10});
			
			// Case (1-3) rand graph
			CASE(N = rnd.nextInt(MXN2 + 1, MXN3), M = rnd.nextInt(0, min((long long)MXM3, (long long)N * (N - 1) / 2)), randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = MXM3, randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = MXM3, randGraph(N, M), shuffleVertices(), shuffleEdges());
			
			// Case (4-5) fixed number of CC
			CASE(N = MXN3, M = MXM3, fixedCCGraph(N, M, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = MXM3, fixedCCGraph(N, M, 2), shuffleVertices(), shuffleEdges());
			
			// Case (6) line
			CASE(N = MXN3, M = N - 1, lineGraph(N), shuffleVertices(), shuffleEdges());
			
			// Case (7-8) multiple line plus extra edges
			CASE(N = MXN3, M = MXM3, multiLinePlusGraph(N, M, 1), shuffleEdges());
			CASE(N = MXN3, M = MXM3, multiLinePlusGraph(N, M, sqrt(N)), shuffleEdges());
			
			// Case (9-10) cycle
			CASE(N = MXN3, M = N, cycleGraph(N), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = N, cycleGraph(N));
			
			// Case (11) M = 3
			CASE(N = MXN3, M = 3, starGraph(4, 1), shuffleVertices(), shuffleEdges());
			
			// Case (12-15) makes dumb DSU TLE
			CASE(N = MXN3, M = MXM3, antiHaramDSUGraph(N, M, 0));
			CASE(N = MXN3, M = MXM3, antiHaramDSUGraph(N, M, 1));
			CASE(N = MXN3, M = MXM3, antiHaramDSUGraph(N, M, 0), reverseVertices(), reverseEdges());
			CASE(N = MXN3, M = MXM3, antiHaramDSUGraph(N, M, 1), reverseVertices(), reverseEdges());
			
			// Case (16-18) all CC is complete graph same size, except 1
			CASE(N = MXN3, M = N / 2 + 2, sameSizeCCCompleteGraph(N, 2), U.push_back(1), V.push_back(3), U.push_back(2), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = N / 3 * 3 + 1, sameSizeCCCompleteGraph(N, 3), U.push_back(1), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN3, M = N / 5 * 10, sameSizeCCCompleteGraph(N, 5), shuffleVertices(), shuffleEdges());
			
			// Case (19) fibonacci graph
			CASE(N = MXN3, M = N * 2 - 3, fibonacciGraph(N));
			
			// Case (20) complete graph
			CASE(N = MXN3, M = 35*34/2, completeGraph(35), shuffleVertices(), shuffleEdges());
		}
		void TestGroup9()
		{
			Subtasks({3, 4, 10});
			
			// Case (1) rand graph with some high degree vertices
			CASE(N = MXN3, M = MXM3, highDegreeGraph(N, M, N - 2, 2), shuffleVertices(), shuffleEdges());
			
			// Case (2) star
			CASE(N = MXN3, M = N - 1, starGraph(N, N / 2));
			
			// Case (3) star plus line
			CASE(N = MXN3, M = N * 2 - 4, starLineGraph(N, N / 2));
		}
		void TestGroup10()
		{
			Subtasks({4, 5, 6, 7, 8, 9, 10});
			
			// Case (1) M = 0
			CASE(N = MXN4, M = 0);
			
			// Case (2) all CC of size 2
			CASE(N = MXN4, M = N / 2, sameSizeCCCompleteGraph(N, 2), shuffleVertices(), shuffleEdges());
		}
		void TestGroup11()
		{
			Subtasks({4, 9, 10});
			
			// Case (1-3) rand graph
			CASE(N = rnd.nextInt(MXN3 + 1, MXN4), M = rnd.nextInt(0, min((long long)MXM4, (long long)N * (N - 1) / 2)), randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = MXM4, randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = MXM4, randGraph(N, M), shuffleVertices(), shuffleEdges());
			
			// Case (4-5) fixed number of CC
			CASE(N = MXN4, M = MXM4, fixedCCGraph(N, M, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = MXM4, fixedCCGraph(N, M, 2), shuffleVertices(), shuffleEdges());
			
			// Case (6) line
			CASE(N = MXN4, M = N - 1, lineGraph(N), shuffleVertices(), shuffleEdges());
			
			// Case (7-8) multiple line plus extra edges
			CASE(N = MXN4, M = MXM4, multiLinePlusGraph(N, M, 1), shuffleEdges());
			CASE(N = MXN4, M = MXM4, multiLinePlusGraph(N, M, sqrt(N)), shuffleEdges());
			
			// Case (9-10) cycle
			CASE(N = MXN4, M = N, cycleGraph(N), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = N, cycleGraph(N));
			
			// Case (11) M = 3
			CASE(N = MXN4, M = 3, starGraph(4, 1), shuffleVertices(), shuffleEdges());
			
			// Case (12-15) makes dumb DSU TLE
			CASE(N = MXN4, M = MXM4, antiHaramDSUGraph(N, M, 0));
			CASE(N = MXN4, M = MXM4, antiHaramDSUGraph(N, M, 1));
			CASE(N = MXN4, M = MXM4, antiHaramDSUGraph(N, M, 0), reverseVertices(), reverseEdges());
			CASE(N = MXN4, M = MXM4, antiHaramDSUGraph(N, M, 1), reverseVertices(), reverseEdges());
			
			// Case (16-18) all CC is complete graph same size, except 1
			CASE(N = MXN4, M = N / 2 + 2, sameSizeCCCompleteGraph(N, 2), U.push_back(1), V.push_back(3), U.push_back(2), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = N / 3 * 3 + 1, sameSizeCCCompleteGraph(N, 3), U.push_back(1), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = N / 5 * 10, sameSizeCCCompleteGraph(N, 5), shuffleVertices(), shuffleEdges());
			
			// Case (19) fibonacci graph
			CASE(N = MXN4, M = N * 2 - 3, fibonacciGraph(N));
		}
		void TestGroup12()
		{
			Subtasks({4, 10});
			
			// Case (1-2) rand graph with some high degree vertices
			CASE(N = MXN4, M = MXM4, highDegreeGraph(N, M, N - 2, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN4, M = MXM4, highDegreeGraph(N, M, N / 10, 10), shuffleVertices(), shuffleEdges());
			
			// Case (3) star
			CASE(N = MXN4, M = N - 1, starGraph(N, N / 2));
			
			// Case (4) star plus line
			CASE(N = MXN4, M = N * 2 - 4, starLineGraph(N, N / 2));
			
			// Case (5) complete graph
			CASE(N = MXN4, M = 89*88/2, completeGraph(89), shuffleVertices(), shuffleEdges());
		}
		void TestGroup13()
		{
			Subtasks({5, 6, 7, 8, 9, 10});
			
			// Case (1) M = 0
			CASE(N = MXN, M = 0);
			
			// Case (2-6) all CC of size at most 2
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = rnd.nextInt(0, N / 2), sameSizeCCCompleteGraph(M * 2, 2), shuffleVertices(), shuffleEdges());
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = N / 2, sameSizeCCCompleteGraph(N, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = rnd.nextInt(0, N / 2), sameSizeCCCompleteGraph(M * 2, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 2, sameSizeCCCompleteGraph(N, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 2, sameSizeCCCompleteGraph(N, 2));
		}
		void TestGroup14()
		{
			Subtasks({6, 7, 8, 9, 10});
			
			// Case (1) one CC of size 3
			CASE(N = MXN, M = (N - 3) / 2 + 2, oneCCSize3Graph(N, M, -1, -1, -1, 3), shuffleEdges());
		}
		void TestGroup15()
		{
			Subtasks({6, 7, 9, 10});
			
			// Case (1-4) one CC of size 3
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = rnd.nextInt(3, (N - 3) / 2 + 3), oneCCSize3Graph(N, M, -1, -1, -1, 1), shuffleEdges());
			CASE(N = MXN, M = (N - 3) / 2 + 3, oneCCSize3Graph(N, M, -1, -1, -1, 1), shuffleEdges());
			CASE(N = MXN, M = (N - 3) / 2 + 2, oneCCSize3Graph(N, M, -1, -1, -1, 2), shuffleEdges());
			CASE(N = MXN, M = (N - 3) / 2 + 2, oneCCSize3Graph(N, M, -1, -1, -1, 4), shuffleEdges());
			
			// Case (5) M = 2
			CASE(N = MXN, M = 2, oneCCSize3Graph(N, M, -1, -1, -1, 2), shuffleEdges());
			
			// Case (6-7) size 3 at array endpoint
			CASE(N = MXN, M = (N - 3) / 2 + 2, oneCCSize3Graph(N, M, 1, 2, 3, 2), shuffleEdges());
			CASE(N = MXN, M = (N - 3) / 2 + 2, oneCCSize3Graph(N, M, N - 2, N - 1, N, 4), shuffleEdges());
			
			// Case (8) min ans
			CASE(N = MXN, M = (N - 3) / 2 + 3, oneCCSize3Graph(N, M, N / 2 - 1, N / 2, N / 2 + 1, 1), shuffleEdges());
		}
		void TestGroup16()
		{
			Subtasks({7, 9, 10});
			
			// Case (1-5) all CC of size at most 3
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = rnd.nextInt(0, N / 4 * 3), CCSizeAtMost3Graph(N, M, M / 6, M / 6), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 4 * 3, CCSizeAtMost3Graph(N, M, M / 6, M / 6), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 6 * 5, CCSizeAtMost3Graph(N, M, M / 5, M / 5), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 5 * 4, CCSizeAtMost3Graph(N, M, M / 4, 0), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 5 * 3, CCSizeAtMost3Graph(N, M, 0, M / 3), shuffleVertices(), shuffleEdges());
			
			// Case (6-7) all CC is complete graph size 3
			CASE(N = MXN, M = N / 3 * 3, sameSizeCCCompleteGraph(N, 3), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 3 * 3, sameSizeCCCompleteGraph(N, 3));
		}
		void TestGroup17()
		{
			Subtasks({8, 9, 10});
			
			// Case (1-2) line
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = N - 1, lineGraph(N), shuffleEdges());
			CASE(N = MXN, M = N - 1, lineGraph(N));
			
			// Case (2-7) multiple line
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = N - int(sqrt(N)), multiLineGraph(N, sqrt(N)), shuffleEdges());
			CASE(N = MXN, M = N - 2, multiLineGraph(N, 2), shuffleEdges());
			CASE(N = MXN, M = N - 10, multiLineGraph(N, 10), shuffleEdges());
			CASE(N = MXN, M = N - int(sqrt(N)), multiLineGraph(N, sqrt(N)), shuffleEdges());
			CASE(N = MXN, M = N - N / 10, multiLineGraph(N, N / 10), shuffleEdges());
		}
		void TestGroup18()
		{
			Subtasks({9, 10});
			
			// Case (1-3) rand graph
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = rnd.nextInt(0, min((long long)MXM, (long long)N * (N - 1) / 2)), randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, randGraph(N, M), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, randGraph(N, M), shuffleVertices(), shuffleEdges());
			
			// Case (4-5) fixed number of CC
			CASE(N = MXN, M = MXM, fixedCCGraph(N, M, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, fixedCCGraph(N, M, 2), shuffleVertices(), shuffleEdges());
			
			// Case (6) line
			CASE(N = MXN, M = N - 1, lineGraph(N), shuffleVertices(), shuffleEdges());
			
			// Case (7-8) multiple line plus extra edges
			CASE(N = MXN, M = MXM, multiLinePlusGraph(N, M, 1), shuffleEdges());
			CASE(N = MXN, M = MXM, multiLinePlusGraph(N, M, sqrt(N)), shuffleEdges());
			
			// Case (9-10) cycle
			CASE(N = MXN, M = N, cycleGraph(N), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N, cycleGraph(N));
			
			// Case (11) M = 3
			CASE(N = MXN, M = 3, starGraph(4, 1), shuffleVertices(), shuffleEdges());
			
			// Case (12-15) makes dumb DSU TLE
			CASE(N = MXN, M = MXM, antiHaramDSUGraph(N, M, 0));
			CASE(N = MXN, M = MXM, antiHaramDSUGraph(N, M, 1));
			CASE(N = MXN, M = MXM, antiHaramDSUGraph(N, M, 0), reverseVertices(), reverseEdges());
			CASE(N = MXN, M = MXM, antiHaramDSUGraph(N, M, 1), reverseVertices(), reverseEdges());
			
			// Case (16-18) all CC is complete graph same size, except 1
			CASE(N = MXN, M = N / 2 + 2, sameSizeCCCompleteGraph(N, 2), U.push_back(1), V.push_back(3), U.push_back(2), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 3 * 3 + 1, sameSizeCCCompleteGraph(N, 3), U.push_back(1), V.push_back(4), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = N / 5 * 10, sameSizeCCCompleteGraph(N, 5), shuffleVertices(), shuffleEdges());
			
			// Case (19) fibonacci graph
			CASE(N = MXN, M = N * 2 - 3, fibonacciGraph(N));
		}
		void TestGroup19()
		{
			Subtasks({10});
			
			// Case (1-7) rand graph with some high degree vertices
			CASE(N = rnd.nextInt(MXN4 + 1, MXN), M = rnd.nextInt(N - 1, min((long long)MXM, (long long)N * (N - 1) / 2)), highDegreeGraph(N, M, N - 1, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, N - 1, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, N / 10, 1), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, N - 2, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, N / 2, 2), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, N / 10, 10), shuffleVertices(), shuffleEdges());
			CASE(N = MXN, M = MXM, highDegreeGraph(N, M, sqrt(N), sqrt(N)), shuffleVertices(), shuffleEdges());
			
			// Case (8) star
			CASE(N = MXN, M = N - 1, starGraph(N, N / 2));
			
			// Case (9) star plus line
			CASE(N = MXN, M = N * 2 - 4, starLineGraph(N, N / 2));
			
			// Case (10) complete graph
			CASE(N = MXN, M = 632*631/2, completeGraph(632), shuffleVertices(), shuffleEdges());
		}

	private:
		vector<long long> randArray(int sz, long long lo, long long hi)
		{
			vector<long long> ret;
			
			for(int i = 0; i < sz; i++)
			{
				ret.push_back(rnd.nextLongLong(lo, hi));
			}
			return ret;
		}
		vector<long long> nonDecreasingArray(int sz, long long lo, long long hi)
		{
			vector<long long> ret = randArray(sz, lo, hi);
			
			sort(ret.begin(), ret.end());
			return ret;
		}
		vector<long long> increasingArray(int sz, long long lo, long long hi)
		{
			vector<long long> ret = nonDecreasingArray(sz, lo, hi - (sz - 1));
			
			for(int i = 0; i < sz; i++)
			{
				ret[i] += i;
			}
			return ret;
		}
		vector<long long> distinctArray(int sz, long long lo, long long hi)
		{
			vector<long long> ret = increasingArray(sz, lo, hi);
			
			rnd.shuffle(ret.begin(), ret.end());
			return ret;
		}
		void randGraph(int cntVertices, int cntEdges)
		{
			int k, l;
			long long sm;
			vector<long long> vals = increasingArray(cntEdges, 1, (long long)cntVertices * (cntVertices - 1) / 2);
			
			l = 2;
			sm = 0;
			for(int i = 0; i < vals.size(); i++)
			{
				while(sm + l - 1 < vals[i])
				{
					sm += l - 1;
					l++;
				}
				U.push_back(vals[i] - sm);
				V.push_back(l);
			}
		}
		void fixedCCGraph(int cntVertices, int cntEdges, int cntCC)
		{
			GraphRandomizer graphRand;
			
			tie(U, V) = graphRand.node_count(cntVertices).edge_count(cntEdges).component_count(cntCC).index_base(1).next().edges();
		}
		void lineGraph(int cntVertices)
		{
			for(int i = 1; i <= cntVertices - 1; i++)
			{
				U.push_back(i);
				V.push_back(i + 1);
			}
		}
		void cycleGraph(int cntVertices)
		{
			lineGraph(cntVertices);
			U.push_back(1);
			V.push_back(cntVertices);
		}
		void multiLineGraph(int cntVertices, int cntLines)
		{
			int last[cntLines + 69];
			
			for(int i = 1; i <= cntLines; i++)
			{
				last[i] = 0;
			}
			for(int i = 1; i <= cntVertices; i++)
			{
				int p = rnd.nextInt(1, cntLines);
				
				if(last[p] != 0)
				{
					U.push_back(last[p]);
					V.push_back(i);
				}
				last[p] = i;
			}
		}
		void multiLinePlusGraph(int cntVertices, int cntEdges, int cntLines)
		{
			int mxDeg[cntVertices + 69], deg[cntVertices + 69], CCIds[cntVertices + 69], perm[cntVertices + 69], carry, CCId;
			vector<long long> pos, tmp;
			bool special[cntVertices + 69];
			
			pos.push_back(0);
			tmp = increasingArray(cntLines - 1, 1, cntVertices - 1);
			pos.insert(pos.end(), tmp.begin(), tmp.end());
			pos.push_back(cntVertices);
			for(int i = 1; i <= cntVertices; i++)
			{
				special[i] = false;
			}
			for(int i = 0; i < cntLines; i++)
			{
				special[pos[i] + 1] = true;
			}
			for(int i = 1; i <= cntVertices; i++)
			{
				if(special[i])
				{
					mxDeg[i] = 0;
					deg[i] = 0;
				}
				else
				{
					mxDeg[i] = mxDeg[i - 1] + 1;
					deg[i] = 1;
				}
			}
			for(int i = 0; i < cntEdges - (cntVertices - cntLines); i++)
			{
				deg[rnd.nextInt(1, cntVertices)]++;
			}
			carry = 0;
			for(int i = 1; i <= cntVertices; i++)
			{
				deg[i] += carry;
				carry = max(deg[i] - mxDeg[i], 0);
				deg[i] = min(deg[i], mxDeg[i]);
			}
			for(int i = 1; i <= cntVertices; i++)
			{
				deg[i] += carry;
				carry = max(deg[i] - mxDeg[i], 0);
				deg[i] = min(deg[i], mxDeg[i]);
			}
			for(int i = 1; i <= cntVertices; i++)
			{
				if(deg[i] > 0)
				{
					U.push_back(i - 1);
					V.push_back(i);
					if(deg[i] > 1)
					{
						vector<long long> vals = distinctArray(deg[i] - 1, i - mxDeg[i], i - 2);
						
						for(int j = 0; j < vals.size(); j++)
						{
							U.push_back(vals[j]);
							V.push_back(i);
						}
					}
				}
			}
			CCId = 0;
			for(int i = 1; i <= cntVertices; i++)
			{
				if(special[i])
				{
					CCId++;
				}
				CCIds[i] = CCId;
			}
			rnd.shuffle(CCIds + 1, CCIds + cntVertices + 1);
			for(int i = 1; i <= cntVertices; i++)
			{
				CCId = CCIds[i];
				pos[CCId - 1]++;
				perm[pos[CCId - 1]] = i;
			}
			for(int i = 0; i < cntEdges; i++)
			{
				U[i] = perm[U[i]];
				V[i] = perm[V[i]];
			}
		}
		void antiHaramDSUGraph(int cntVertices, int cntEdges, bool rev)
		{
			int mxDeg[cntVertices + 69], deg[cntVertices + 69], carry;
			vector<int> vertices;
			
			for(int i = cntVertices / 2 + 1; i <= cntVertices; i++)
			{
				mxDeg[i] = (i - cntVertices / 2 - 1) * 2;
				deg[i] = 0;
			}
			for(int i = 0; i < cntEdges - (cntVertices - 1); i++)
			{
				deg[rnd.nextInt(cntVertices / 2 + 1, cntVertices)]++;
			}
			carry = 0;
			for(int i = cntVertices / 2 + 1; i <= cntVertices; i++)
			{
				deg[i] += carry;
				carry = max(deg[i] - mxDeg[i], 0);
				deg[i] = min(deg[i], mxDeg[i]);
			}
			for(int i = cntVertices / 2 + 1; i <= cntVertices; i++)
			{
				deg[i] += carry;
				carry = max(deg[i] - mxDeg[i], 0);
				deg[i] = min(deg[i], mxDeg[i]);
			}
			for(int i = 2; i <= cntVertices / 2; i++)
			{
				U.push_back(i - 1);
				V.push_back(i);
			}
			for(int i = cntVertices / 2 + 1; i <= cntVertices; i++)
			{
				int p;
				
				if(!rev)
				{
					p = i - cntVertices / 2;
				}
				else
				{
					p = cntVertices / 2 + 1 - (i - cntVertices / 2);
				}
				U.push_back(p);
				V.push_back(i);
				if(deg[i])
				{
					vector<long long> vals = distinctArray(deg[i], 0, vertices.size() - 1);
					
					for(int j = 0; j < vals.size(); j++)
					{
						U.push_back(vertices[vals[j]]);
						V.push_back(i);
					}
				}
				vertices.push_back(i);
				vertices.push_back(p);
			}
		}
		void sameSizeCCCompleteGraph(int cntVertices, int sz)
		{
			for(int i = sz; i <= cntVertices; i += sz)
			{
				for(int j = i - sz + 1; j <= i; j++)
				{
					for(int r = j + 1; r <= i; r++)
					{
						U.push_back(j);
						V.push_back(r);
					}
				}
			}
		}
		void fibonacciGraph(int cntVertices)
		{
			for(int i = 1; i <= cntVertices - 1; i++)
			{
				U.push_back(i);
				V.push_back(i + 1);
			}
			for(int i = 1; i <= cntVertices - 2; i++)
			{
				U.push_back(i);
				V.push_back(i + 2);
			}
		}
		void highDegreeGraph(int cntVertices, int cntEdges, int deg, int cnt)
		{
			randGraph(cntVertices - cnt, cntEdges - deg * cnt);
			for(int i = cntVertices - cnt + 1; i <= cntVertices; i++)
			{
				vector<long long> vals = distinctArray(deg, 1, i - 1);
				
				for(int j = 0; j < vals.size(); j++)
				{
					U.push_back(vals[j]);
					V.push_back(i);
				}
			}
		}
		void starGraph(int cntVertices, int pos)
		{
			for(int i = 1; i <= cntVertices; i++)
			{
				if(i != pos)
				{
					U.push_back(i);
					V.push_back(pos);
				}
			}
		}
		void starLineGraph(int cntVertices, int pos)
		{
			for(int i = 1; i <= cntVertices - 1; i++)
			{
				if(i < pos - 1 || i > pos)
				{
					U.push_back(i);
					V.push_back(i + 1);
				}
				else if(i == pos)
				{
					for(int j = 1; j <= cntVertices; j++)
					{
						if(j != i)
						{
							U.push_back(j);
							V.push_back(i);
						}
					}
				}
			}
		}
		void completeGraph(int cntVertices)
		{
			for(int i = 1; i <= cntVertices; i++)
			{
				for(int j = i + 1; j <= cntVertices; j++)
				{
					U.push_back(i);
					V.push_back(j);
				}
			}
		}
		void oneCCSize3Graph(int cntVertices, int cntEdges, int pos1, int pos2, int pos3, int type)
		{
			int p;
			vector<int> vertices;
			
			if(pos1 == -1)
			{
				vector<long long> pos = increasingArray(3, 1, cntVertices);
				
				pos1 = pos[0];
				pos2 = pos[1];
				pos3 = pos[2];
			}
			if(type == 1)
			{
				U.push_back(pos1);
				V.push_back(pos2);
				U.push_back(pos1);
				V.push_back(pos3);
				U.push_back(pos2);
				V.push_back(pos3);
			}
			else if(type == 2)
			{
				U.push_back(pos1);
				V.push_back(pos2);
				U.push_back(pos1);
				V.push_back(pos3);
			}
			else if(type == 3)
			{
				U.push_back(pos1);
				V.push_back(pos2);
				U.push_back(pos2);
				V.push_back(pos3);
			}
			else if(type == 4)
			{
				U.push_back(pos1);
				V.push_back(pos3);
				U.push_back(pos2);
				V.push_back(pos3);
			}
			for(int i = 1; i <= cntVertices; i++)
			{
				if(i != pos1 && i != pos2 && i != pos3)
				{
					vertices.push_back(i);
				}
			}
			rnd.shuffle(vertices.begin(), vertices.end());
			p = 0;
			while(U.size() < cntEdges)
			{
				U.push_back(vertices[p]);
				V.push_back(vertices[p + 1]);
				p += 2;
			}
		}
		void CCSizeAtMost3Graph(int cntVertices, int cntEdges, int cnt3Cycles, int cnt3Lines)
		{
			int cnt2Lines, p = 0;
			
			cnt2Lines = cntEdges - cnt3Cycles * 3 - cnt3Lines * 2;
			for(int i = 0; i < cnt3Cycles; i++)
			{
				U.push_back(p + 1);
				V.push_back(p + 2);
				U.push_back(p + 1);
				V.push_back(p + 3);
				U.push_back(p + 2);
				V.push_back(p + 3);
				p += 3;
			}
			for(int i = 0; i < cnt3Lines; i++)
			{
				U.push_back(p + 1);
				V.push_back(p + 2);
				U.push_back(p + 2);
				V.push_back(p + 3);
				p += 3;
			}
			for(int i = 0; i < cnt2Lines; i++)
			{
				U.push_back(p + 1);
				V.push_back(p + 2);
				p += 2;
			}
		}
		void shuffleVertices()
		{
			int perm[N + 69];
			
			for(int i = 1; i <= N; i++)
			{
				perm[i] = i;
			}
			rnd.shuffle(perm + 1, perm + N + 1);
			for(int i = 0; i < M; i++)
			{
				U[i] = perm[U[i]];
				V[i] = perm[V[i]];
			}
		}
		void reverseVertices()
		{
			for(int i = 0; i < M; i++)
			{
				U[i] = N + 1 - U[i];
				V[i] = N + 1 - V[i];
			}
		}
		void shuffleEdges()
		{
			for(int i = 0; i < M; i++)
			{
				int p = rnd.nextInt(0, i);
				
				swap(U[i], U[p]);
				swap(V[i], V[p]);
			}
		}
		void reverseEdges()
		{
			reverse(U.begin(), U.end());
			reverse(V.begin(), V.end());
		}
};
