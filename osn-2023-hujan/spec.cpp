#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define ll long long
const int MXN = 1000;
const int MXA = 1000000000;

vector<vector<int> > open_sub = {{-1, 6}, {9, -1}};
vector<vector<int> > handle_inf_corner1 = {{-1, -1, -1}, {0, 1, 2}, {3, 4, 1}};
vector<vector<int> > handle_inf_corner2 = {{-1, -1, -1}, {0, 5, -1}, {-1, 2, -1}};

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector<vector<int> > A;

	ll ans;

	void InputFormat() {
		LINE(N);
		GRID(A) % SIZE(N, N);
	}
	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(512);
	}

	void Constraints() {
		CONS(2 <= N && N <= MXN);
		CONS(eachElementBetween(A, -1, MXA));
	}

	void Subtask1() {
		Points(5);
		CONS(N == 2);
		CONS(A == open_sub);
	}
	void Subtask2() {
		Points(4);
		CONS(N == 2);
	}
	void Subtask3() {
		Points(7);
		CONS(eachElementBetween(A, -1, 0));
	}
	void Subtask4() {
		Points(7);
		CONS(N <= 8);
		CONS(eachElementBetween(A, 0, MXA));
	}
	void Subtask5() {
		Points(7);
		CONS(N <= 80);
		CONS(eachElementBetween(A, 0, MXA));
	}
	void Subtask6() {
		Points(8);
		CONS(eachElementBetween(A, 0, MXA));
	}
	void Subtask7() {
		Points(12);
		CONS(emptyNonDiagonal(N, A));
		CONS(A[0][0] == 0);
	}
	void Subtask8() {
		Points(14);
		CONS(emptyNonDiagonal(N, A));
	}
	void Subtask9() {
		Points(8);
		CONS(N <= 5);
		CONS(eachElementBetween(A, -1, 7));
		CONS(hasZeroElement(A));
	}
	void Subtask10() {
		Points(10);
		CONS(N <= 100);
		CONS(eachElementBetween(A, -1, 100));
		CONS(hasZeroElement(A));
	}
	void Subtask11() {
		Points(12);
		CONS(hasZeroElement(A));
	}
	void Subtask12() {
		Points(6);
	}

private:
	bool eachElementBetween(vector<vector<int> > V, int lf, int rg) {
		for(auto i : V) for(auto j : i)
			if(j < lf || rg < j) return 0;
		return 1;
	}

	bool emptyNonDiagonal(int N, vector<vector<int> > V) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (i != j && V[i][j] != -1)
					return 0;
				if (i == j && V[i][j] == -1)
					return 0;
			}
		return 1;
	}

	bool hasZeroElement(vector<vector<int> > V) {
		for (auto i : V) for (auto j : i)
			if (j == 0) return 1;
		return 0;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1() {
		Subtasks({9, 10, 11, 12});
		Input({
			"3",
			"-1 0 -1",
			"4 -1 7",
			"3 -1 -1",
		});
		Output({
			"4",
		});
	}
	void SampleTestCase2() {
		Subtasks({2, 12});
		Input({
			"2",
			"-1 1",
			"2 -1",
		});
		Output({
			"4",
		});
	}
	void SampleTestCase3() {
		Subtasks({2, 3, 12});
		Input({
			"2",
			"-1 -1",
			"-1 -1",
		});
		Output({
			"-1",
		});
	}
	void SampleTestCase4() {
		Subtasks({2, 4, 5, 6, 12});
		Input({
			"2",
			"2 6",
			"5 265",
		});
		Output({
			"0",
		});
	}

	void BeforeTestCase(){
		A.clear();
	}

	void TestGroup1(){
		Subtasks({1, 2, 12});
		CASE(N = 2, A = {{-1, 6}, {9, -1}});
	}

	void TestGroup2() {
		Subtasks({2, 4, 5, 6, 12});
		CASE(N = 2, A = {{52342, 6462345}, {452366, 6862369}});
		CASE(N = 2, A = {{52342, 6462345}, {452366, 6862368}});
	}

	void TestGroup3(){
		Subtasks({2, 3, 9, 10, 11, 12});
		CASE(N = 2, A = {{-1, 0}, {0, 0}});
		CASE(N = 2, A = {{-1, 0}, {-1, -1}});
		CASE(N = 2, A = {{0, -1}, {0, -1}});
	}

	void TestGroup4() {
		Subtasks({2, 8, 12});
		CASE(N = 2, A = {{MXA, -1}, {-1, MXA}});
		CASE(N = 2, A = {{998244353, -1}, {-1, 420691273}});
	}

	void TestGroup5() {
		Subtasks({2, 12});
		CASE(N = 2, A = {{3452432, 2}, {-1, -1}});
		CASE(N = 2, A = {{234342, 123413}, {364633, -1}});
		CASE(N = 2, A = {{-1, 3413}, {12431, 46346523}});
		CASE(N = 2, A = {{-1, 436324523}, {234234165, -1}});
	}

	void TestGroup6() {
		Subtasks({3, 5, 6, 10, 11, 12});
		CASE(N = 67, A = vector<vector<int> >(67, vector<int>(67, 0)));
		CASE(N = 80, A = vector<vector<int> >(80, vector<int>(80, 0)));
	}

	void TestGroup7() {
		Subtasks({3, 6, 11, 12});
		CASE(N = 727, A = vector<vector<int> >(727, vector<int>(727, 0)));
		CASE(N = MXN, A = vector<vector<int> >(MXN, vector<int>(MXN, 0)));
	}

	void TestGroup8() {
		Subtasks({3, 7, 8, 11, 12});
		CASE(N = 727, A = generateDiag(727, 0, 1, 1));
		CASE(N = MXN, A = generateDiag(MXN, 0, 1, 1));
	}

	void TestGroup9() {
		Subtasks({3, 11, 12});
		CASE(N = rnd.nextInt(105, MXN), A = generateSub3(N, 0));
		CASE(N = rnd.nextInt(105, MXN), A = generateSub3(N, 1));
		CASE(N = rnd.nextInt(105, MXN), A = generateSub3(N, 1));
		CASE(N = rnd.nextInt(105, MXN), A = generateSub3(N, 0));
		CASE(N = MXN - 2, A = generateSub3(MXN - 2, 0));
		CASE(N = MXN, A = generateSub3(MXN, 1));
	}

	void TestGroup10() {
		Subtasks({4, 5, 6, 11, 12}); // A > 100
		CASE(N = 3, A = generateValid(N, 1));
		CASE(N = 8, A = generateInvalid(N, 1, 1));
		CASE(N = 6, A = generateInvalid(N, 3, 1));
		CASE(N = 8, A = generateValid(N, 1));
		CASE(N = 8, A = generateValid(N, 1));
		CASE(N = 8, A = generateInvalid(N, 1, 1));
		CASE(N = 8, A = generateValid(N, 1));
	}

	void TestGroup11() {
		Subtasks({4, 5, 6, 12});
		CASE(N = 3, A = generateInvalid(N, 1, 0));
		CASE(N = 5, A = generateValid(N, 0));
		CASE(N = 8, A = generateValid(N, 0));
		CASE(N = 8, A = generateInvalid(N, 4, 0));
		CASE(N = 8, A = generateInvalid(N, 1, 0));
		CASE(N = 8, A = generateInvalid(N, 1, 0));
		CASE(N = 8, A = generateValid(N, 0));
	}

	void TestGroup12() {
		Subtasks({5, 6, 11, 12});
		CASE(N = 27, A = generateInvalid(N, 1, 1));
		CASE(N = 52, A = generateValid(N, 1));
		CASE(N = 80, A = generateValid(N, 1));
		CASE(N = 80, A = generateValid(N, 1));
		CASE(N = 80, A = generateInvalid(N, 1, 1));
		CASE(N = 80, A = generateInvalid(N, 1, 1));
	}

	void TestGroup13() {
		Subtasks({5, 6, 12});
		CASE(N = 42, A = generateInvalid(N, 1, 0));
		CASE(N = 69, A = generateValid(N, 0));
		CASE(N = 69, A = generateInvalid(N, 5, 0));
		CASE(N = 80, A = generateValid(N, 0));
		CASE(N = 80, A = generateInvalid(N, 1, 0));
		CASE(N = 80, A = generateInvalid(N, 17, 0));
		CASE(N = 80, A = generateValid(N, 0));
		CASE(N = 80, A = generateInvalid(N, 1, 0));
		CASE(N = 80, A = generateValid(N, 0));
	}

	void TestGroup14() {
		Subtasks({6, 11, 12});
		CASE(N = 265, A = generateInvalid(N, 1, 1));
		CASE(N = 666, A = generateValid(N, 1));
		CASE(N = MXN - 3, A = generateInvalid(N, 5, 1));
		CASE(N = MXN, A = generateInvalid(N, 1, 1));
		CASE(N = MXN, A = generateValid(N, 1));
		CASE(N = MXN, A = generateInvalid(N, 1, 1));
		CASE(N = MXN, A = generateValid(N, 1));
		CASE(N = MXN, A = generateInvalid(N, 1, 1));
		CASE(N = MXN, A = generateValid(N, 1));
	}

	void TestGroup15() {
		Subtasks({6, 12});
		CASE(N = 420, A = generateValid(N, 0));
		CASE(N = 727, A = generateInvalid(N, 1, 0));
		CASE(N = MXN - 3, A = generateValid(N, 0));
		CASE(N = MXN, A = generateInvalid(N, 42, 0));
		CASE(N = MXN, A = generateInvalid(N, 1, 0));
		CASE(N = MXN, A = generateValid(N, 0));
		CASE(N = MXN, A = generateInvalid(N, 1, 0));
		CASE(N = MXN, A = generateValid(N, 0));
		CASE(N = MXN, A = generateInvalid(N, 1, 0));
		CASE(N = MXN, A = generateValid(N, 0));
	}

	void TestGroup16() {
		Subtasks({7, 8, 10, 11, 12});
		CASE(N = 5, A = generateDiag(N, 17, 1, 1));
		CASE(N = 8, A = generateDiag(N, 3, 1, 1));
		CASE(N = 26, A = generateDiag(N, 69, 1, 1));
		CASE(N = 100, A = generateDiag(N, 100, 1, 1));
	}

	void TestGroup17() {
		Subtasks({7, 8, 11, 12});
		CASE(N = 177, A = generateDiag(N, 3423561, 1, 1));
		CASE(N = 265, A = generateDiag(N, 123123123, 1, 1));
		CASE(N = 642, A = generateDiag(N, 420691273, 1, 1));
		CASE(N = 727, A = generateDiag(N, MXA, 1, 1));
		CASE(N = MXN, A = generateDiag(N, MXA, 1, 1));
	}

	void TestGroup18() {
		Subtasks({8, 10, 11, 12});
		CASE(N = 26, A = generateDiag(N, 99, 0, 1));
	}

	void TestGroup19() {
		Subtasks({8, 11, 12});
		CASE(N = 972, A = generateDiag(N, MXA, 0, 1));
		CASE(N = 525, A = generateDiag(N, 3423561, 0, 1));
	}

	void TestGroup20() {
		Subtasks({8, 12});
		CASE(N = 4, A = generateDiag(N, 17, 0, 0));
		CASE(N = 8, A = generateDiag(N, 3, 0, 0));
		CASE(N = 100, A = generateDiag(N, 100, 0, 0));
		CASE(N = 666, A = generateDiag(N, 123123123, 0, 0));
		CASE(N = 883, A = generateDiag(N, 420691273, 0, 0));
		CASE(N = MXN, A = generateDiag(N, MXA, 0, 0));
	}

	void TestGroup21() {
		Subtasks({9, 10, 11, 12});
		CASE(N = 3, A = handle_inf_corner1);
		CASE(N = 3, A = handle_inf_corner2);
		CASE(N = 4, A = generateGeneral(N, 7, 2, 0, 0, 0, 1));
		CASE(N = 4, A = generateGeneral(N, 7, 2, 0, 1, 0, 1));
		CASE(N = 5, A = generateGeneral(N, 7, 2, 0, 0, 0, 1));
		CASE(N = 5, A = generateGeneral(N, 7, 2, 0, 0, 1, 1));
		CASE(N = 5, A = generateGeneral(N, 7, 3, 1, 0, 0, 1));
		CASE(N = 5, A = generateGeneral(N, 7, 4, 0, 0, 0, 1));
		CASE(N = 5, A = generateGeneral(N, 7, 1, 1, 0, 0, 1));
	}

	void TestGroup22() {
		Subtasks({10, 11, 12});
		CASE(N = 100, A = generateGeneral(N, 100, 1, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(50, 100), A = generateGeneral(N, 100, 2, 1, 0, 0, 1));
		CASE(N = rnd.nextInt(50, 100), A = generateGeneral(N, 100, 7, 0, 0, 1, 1));
		CASE(N = rnd.nextInt(50, 100), A = generateGeneral(N, 100, 9, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(70, 100), A = generateGeneral(N, 100, 13, 0, 1, 0, 1));
		CASE(N = rnd.nextInt(70, 100), A = generateGeneral(N, 100, 20, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(70, 100), A = generateGeneral(N, 100, 26, 1, 1, 0, 1));
		CASE(N = rnd.nextInt(90, 100), A = generateGeneral(N, 100, 28, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(90, 100), A = generateGeneral(N, 100, 37, 0, 1, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 44, 0, 1, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 50, 0, 0, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 69, 0, 0, 1, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 72, 0, 0, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 85, 1, 1, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 99, 1, 0, 0, 1));
		CASE(N = 100, A = generateGeneral(N, 100, 100, 0, 0, 0, 1));
	}

	void TestGroup23() {
		Subtasks({11, 12});
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 1, 1, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 1, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 2, 0, 1, 0, 1));
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 5, 0, 0, 1, 1));
		CASE(N = rnd.nextInt(700, MXN), A = generateGeneral(N, MXA, 9, 1, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 16, 0, 0, 0, 1));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 27, 1, 0, 0, 1));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 28, 0, 1, 0, 1));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 29, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 47, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 51, 0, 0, 1, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 57, 1, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 69, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 70, 0, 1, 0, 1));
		CASE(N = MXN - 1, A = generateGeneral(N, MXA, 99, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 169, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 217, 0, 1, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 219, 1, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 265, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 500, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 666, 0, 1, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, 727, 1, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, MXN - 1, 0, 0, 0, 1));
		CASE(N = MXN, A = generateGeneral(N, MXA, MXN, 0, 0, 0, 1));
	}

	void TestGroup24() {
		Subtasks({12});
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 1, 1, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 1, 0, 0, 0, 0));
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 2, 0, 1, 0, 0));
		CASE(N = rnd.nextInt(MXN / 2, MXN), A = generateGeneral(N, MXA, 5, 0, 0, 1, 0));
		CASE(N = rnd.nextInt(700, MXN), A = generateGeneral(N, MXA, 9, 1, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 16, 0, 0, 0, 0));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 27, 1, 0, 0, 0));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 28, 0, 1, 0, 0));
		CASE(N = rnd.nextInt(800, MXN), A = generateGeneral(N, MXA, 29, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 47, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 51, 0, 0, 1, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 57, 1, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 69, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 70, 0, 1, 0, 0));
		CASE(N = MXN - 1, A = generateGeneral(N, MXA, 99, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 169, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 217, 0, 1, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 219, 1, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 265, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 500, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 666, 0, 1, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, 727, 1, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, MXN - 1, 0, 0, 0, 0));
		CASE(N = MXN, A = generateGeneral(N, MXA, MXN, 0, 0, 0, 0));
	}

private:
	vector<vector<int> > generateSub3(int n, int tp) {
		vector<vector<int> > v = vector<vector<int> >(n, vector<int>(n, 0));
		vector<int> cnti, cntj;
		cnti.assign(n, 0); cntj.assign(n, 0);
		vector<pair<int, int> > pp;
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) pp.push_back({i, j});
		rnd.shuffle(pp.begin(), pp.end());

		int xx = -1, bts;
		for (int i = 0; i < pp.size(); i++) {
			cnti[pp[i].first]++;
			cntj[pp[i].second]++;
			if (cnti[pp[i].first] == n || cntj[pp[i].second] == n) {
				xx = i; break;
			}
		}

		if (tp)	bts = rnd.nextInt(max(xx - 2 * n, 0), xx);
		else bts = rnd.nextInt(xx, min(xx + 2 * n, n * n - 1));
		for (int i = 0; i < bts; i++) v[pp[i].first][pp[i].second] = -1;
		return v;
	}

	vector<vector<int> > generateDiag(int n, int rg, int isSub7, int isSub11) {
		if (isSub7) isSub11 = 1;
		vector<vector<int> > v = vector<vector<int> >(n, vector<int>(n, -1));
		bool has0 = 0;
		for (int i = 0; i < n; i++) {
			int rd = rnd.nextInt(1 - isSub11, rg);
			if (isSub7 && i == 0) rd = 0;
			v[i][i] = rd;
			if (rd == 0) has0 = 1;
		}
		if (isSub11 && !has0) {
			int t = rnd.nextInt(1, n - 1);
			v[t][t] = 0;
		}
		return v;
	}

	vector<vector<int> > generateValid(int n, int isSub11) {
		vector<vector<int> > v = vector<vector<int> >(n, vector<int>(n, -1));
		vector<int> rw(n), cl(n);
		for (int i = 0; i < n; i++) {
			rw[i] = rnd.nextInt(0, MXA / 2);
			while (rw[i] == 0 && !isSub11) rw[i] = rnd.nextInt(0, MXA / 2);
			if (i == n / 2 && isSub11) rw[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			cl[i] = rnd.nextInt(0, MXA / 2);
			while (cl[i] == 0 && !isSub11) cl[i] = rnd.nextInt(0, MXA / 2);
			if (i == n / 2 && isSub11) cl[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[i][j] = rw[i] + cl[j];
			}
		}
		return v;
	}

	vector<vector<int> > generateInvalid(int n, int pt, int isSub11) {
		vector<vector<int> > v = generateValid(n, isSub11);
		for (int tp = 0; tp < pt; tp ++) {
			int i = rnd.nextInt(0, n - 1);
			int j = rnd.nextInt(0, n - 1);
			if (v[i][j] == 0 && isSub11) {
				tp --;
				continue;
			}
			int ww = rnd.nextInt(0, MXA);
			for (; v[i][j] == ww; ww = rnd.nextInt(1 - isSub11, MXA));
			v[i][j] = ww; 
		}
		return v;
	}

	vector<vector<int> > generateGeneral(int n, int maxa, int cc_count, bool faulty_sum, bool faulty_range, bool faulty_inf, bool isSub11) {
		vector<int> rw, cl, fs, fr, fi, f0;
		for (int i = 0; i < cc_count; i++) {
			cl.push_back(i);
			rw.push_back(i);

			if (!faulty_sum) fs.push_back(0);
			else if (i == 0) fs.push_back(1);
			else {
				if (rnd.nextInt(0, 9) < 7) fs.push_back(0);
				else fs.push_back(1);
			}

			if (!faulty_range) fr.push_back(0);
			else if (i == 0) fr.push_back(1);
			else {
				if (rnd.nextInt(0, 9) < 7) fr.push_back(0);
				else fr.push_back(1);
			}

			if (!faulty_inf) fi.push_back(0);
			else if (i == 0) fi.push_back(1);
			else {
				if (rnd.nextInt(0, 9) < 7) fi.push_back(0);
				else fi.push_back(1);
			}

			if (!isSub11) f0.push_back(0);
			else if (i == 0) f0.push_back(1);
			else {
				if (rnd.nextInt(0, 9) < 7) f0.push_back(0);
				else f0.push_back(1);
			}
		}
		rnd.shuffle(fs.begin(), fs.end());
		rnd.shuffle(fr.begin(), fr.end());
		rnd.shuffle(fi.begin(), fi.end());
		rnd.shuffle(f0.begin(), f0.end());
		int tmp = n - cc_count;
		for (int i = 0; i < tmp; i++) {
			cl.push_back(rnd.nextInt(0, cc_count - 1));
			rw.push_back(rnd.nextInt(0, cc_count - 1));
		}
		rnd.shuffle(cl.begin(), cl.end());
		rnd.shuffle(rw.begin(), rw.end());

		vector<vector<int> > res(n, vector<int>(n, -1));
		for (int tp = 0; tp < cc_count; tp++) {
			vector<int> row, col;
			vector<pair<int, int> > edges;
			for (int i = 0; i < n; i++) {
				if (rw[i] == tp) row.push_back(i);
				if (cl[i] == tp) col.push_back(i);
			}
			for (int i = 0; i < row.size(); i++) {
				for (int j = 0; j < col.size(); j++)
					edges.push_back({i, j});
			}
			rnd.shuffle(edges.begin(), edges.end());
			vector<int> par(row.size() + col.size());
			for (int i = 0; i < row.size() + col.size(); i++)
				par[i] = i;
			function<int(int)> findpar = [&](int x) {
				if (par[x] == x) return x;
				return par[x] = findpar(par[x]);
			};

			bool ccfaultyinf = fi[tp]; // definitely gives -1
			bool ccfaultysum = fs[tp]; // has a chance to give 0
			bool ccfaultyrange = fr[tp]; // has a chance to give 0
			bool cchas0 = f0[tp]; // has value 0

			vector<int> rowvalues, colvalues;
			if (!ccfaultyrange) {
				int minvalrow = -rnd.nextInt(0, maxa);
				int minvalcol = rnd.nextInt(-minvalrow, maxa);
				int maxvalcol = rnd.nextInt(minvalcol, maxa);
				int maxvalrow = rnd.nextInt(0, maxa - maxvalcol);

				if (cchas0) colvalues.push_back(0);
				else colvalues.push_back(maxvalcol);
				if (col.size() > 1) colvalues.push_back(minvalcol);
				for (int i = 2; i < col.size(); i++) colvalues.push_back(rnd.nextInt(minvalcol, maxvalcol));
				rowvalues.push_back(0);
				if (row.size() > 1) rowvalues.push_back(minvalrow);
				if (row.size() > 2) rowvalues.push_back(maxvalrow);
				for (int i = 3; i < row.size(); i++) rowvalues.push_back(rnd.nextInt(minvalrow, maxvalrow));
			} else {
				int minvalrow = -rnd.nextInt(0, maxa);
				int minvalcol = rnd.nextInt(0, max(0, -minvalrow - 1));
				int maxvalcol = rnd.nextInt(minvalcol, maxa);
				int maxvalrow = rnd.nextInt(0, maxa - maxvalcol);

				if (cchas0) colvalues.push_back(0);
				else colvalues.push_back(maxvalcol);
				if (col.size() > 1) colvalues.push_back(minvalcol);
				for (int i = 2; i < col.size(); i++) colvalues.push_back(rnd.nextInt(minvalcol, maxvalcol));
				rowvalues.push_back(0);
				if (row.size() > 1) rowvalues.push_back(minvalrow);
				if (row.size() > 2) rowvalues.push_back(maxvalrow);
				for (int i = 3; i < row.size(); i++) rowvalues.push_back(rnd.nextInt(minvalrow, maxvalrow));
			}

			rnd.shuffle(colvalues.begin(), colvalues.end());
			rnd.shuffle(rowvalues.begin(), rowvalues.end());

			// (row[i], col[j]) has value rowvalues[i] + colvalues[j]
			int ccnow = row.size() + col.size();
			vector<int> edges_used;
			int edge_limit = rnd.nextInt(ccnow - 1, max(ccnow - 1, min((int)edges.size() - 1, 5 * ccnow)));
			

			if (cchas0) {
				int banu = -1, banv = -1;
				for (int i = 0; i < rowvalues.size(); i++)
					if (rowvalues[i] == 0) banu = i;
				for (int j = 0; j < colvalues.size(); j++)
					if (colvalues[j] == 0) banv = j;
				if (banu != -1 && banv != -1) {
					vector<pair<int, int> > tped;
					tped.push_back({banu, banv});
					for (auto i : edges) if (!(i.first == banu && i.second == banv)) tped.push_back(i);
					edges = tped;
				}
			}

			for (int i = 0; edge_limit > 0 && i < edges.size(); i ++) {
				int ru = edges[i].first;
				int cv = edges[i].second;

				int fu = findpar(ru), fv = findpar(cv + (int)row.size());
				if (fu != fv) {
					if (ccnow == 2 && ccfaultyinf) continue;

					ccnow --;
					par[fu] = fv;
				}
				if (fu == fv && ccnow - 1 == edge_limit && !ccfaultyinf) continue;
				if (rowvalues[ru] + colvalues[cv] < 0) continue;
				int u = row[ru], v = col[cv];
				res[u][v] = rowvalues[ru] + colvalues[cv];
				edges_used.push_back(i);
				edge_limit --;
			}

			if (ccfaultysum) {
				if (edges_used.size() == 1 && cchas0);
				else {
					int idx = rnd.nextInt((cchas0 ? 1 : 0), edges_used.size() - 1);
					int i = edges[edges_used[idx]].first, j = edges[edges_used[idx]].second;
					res[row[i]][col[j]] = maxa;
					while (res[row[i]][col[j]] == rowvalues[i] + colvalues[j])
						res[row[i]][col[j]] --;
				}
			}
		}

		return res;
	}
};
