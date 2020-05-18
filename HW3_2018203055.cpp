// 김진구 2018203055

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void rotated_form(vector<string> v, int n, int space);
void not_rotated_form(vector<string> v);
void H_tree_form(vector<string> v, string** H_tree, int node, int i, int j, int d, int U, int D, int R, int L, int n);
int center(int n); // H_tree 에서 정 가운데의 값을 알려주는 함수
int depth(int n); // H_tree 에서 depth 를 반환하는 함수

int main(void) {
	vector<string> v;
	string str;
	stringstream ss;

	while (cin >> str) {
		if (str == "EOI") { // EOI라면 입력 끝
			break;
		}
		else if (str == "INS") { // 다음에 오는 문자열을 입력
			cin >> str;
			v.push_back(str);
			push_heap(v.begin(), v.end());
		}
		else if (str == "DEL") { // 루트노드 삭제
			pop_heap(v.begin(), v.end()); // 루트 노드와 마지막 노드를 바꿈
			v.pop_back(); // 맨 마지막 노드를 삭제
		}
	}

	cout << "1. rotated form" << endl;
	rotated_form(v, 0, 0); // rotated form 출력
	
	cout << endl << endl << "2. non rotated form" << endl;
	not_rotated_form(v); // not rotated form 출력
	cout << endl << endl;

	int pow = 0;
	int tmp = v.size();
	int size = 2;

	while (tmp > 0) {
		pow++;
		tmp /= 2;
	}

	for (int i = 0; i < pow; pow -= 2) { // H_tree 사이즈 설정
		size *= 2;
	}
	size--;


	string ** H_tree = new string*[size]; // 2차원배열 동적할당
	for (int i = 0; i < size; i++) {
		H_tree[i] = new string[size];
	}

	for (int i = 0; i < size; i++) { // H-tree 초기화
		for (int j = 0; j < size; j++) {
			H_tree[i][j] = " ";
		}
	}

	H_tree_form(v, H_tree, 1, center(v.size()), center(v.size()), depth(v.size()), 0, 1, 2, 3, v.size());

	cout << endl << "3. H-tree form";
	for (int i = 0; i < size; i++) { // H-tree 출력
		for (int j = 0; j < size; j++) {
			cout << H_tree[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

void rotated_form(vector<string> v, int n, int space) {
	if (n * 2 + 2 < v.size()) { // 오른쪽에 자식이 있다면 재귀
		rotated_form(v, n * 2 + 2, space + 1);
	}
	for (int i = 0; i < space; i++) cout << "  "; //몇 번 재귀 되었는지에 따라 공백 설정
	cout << v[n] << endl;
	if (n * 2 + 1 < v.size()) { // 왼쪽에 자식이 있다면 재귀
		rotated_form(v, n * 2 + 1, space + 1);
	}
}

void not_rotated_form(vector<string> v) {

	int max = 1; // 가장 오른쪽 출력 확인용
	int space = 1; // 여백 설정용
	int tmp = v.size();
	int pow = 0;
	while (tmp / 2 > 0) {
		pow++;
		tmp /= 2;
	}
	for (int i = 0; i < pow; i++) {  // 최대 여백 설정
		space *= 2;
	}

	for (int i = 0; i < v.size(); i++) {
		for (int i = 0; i < space - 1; i++) {
			cout << " ";
		}
		cout << v[i];
		for (int i = 0; i < space; i++) {
			cout << " ";
		}

		if (i % max + 2 == max || i == 0) { // 가장 오른쪽을 출력한 후에 다음 줄로 넘긴다
			cout << endl;
			max *= 2; // 가장 오른쪽 확인 범위 증가
			space /= 2; // 여백 줄이기
		}
	}
}

void H_tree_form(vector<string> v, string** H_tree, int node, int i, int j, int d, int U, int D, int R, int L, int n) {

	if (node > n) return;

	int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0,1 },{ 0,-1 } }; // H_tree 

	H_tree[i][j] = v[node - 1];

	if (2 * node <= n) {
		H_tree[i + d * V[L][0]][j + d * V[L][1]] = v[2 * node - 1];
		H_tree_form(v, H_tree, 4 * node, i + d * (V[L][0] + V[U][0]), j + d * (V[L][1] + V[U][1]), d / 2, D, U, L, R, n);
		H_tree_form(v, H_tree, 4 * node + 1, i + d * (V[L][0] + V[D][0]), j + d * (V[L][1] + V[D][1]), d / 2, U, D, R, L, n);
	}

	if (2 * node + 1 <= n) {
		H_tree[i + d * V[R][0]][j + d * V[R][1]] = v[2 * node];
		H_tree_form(v, H_tree, 4 * node + 2, i + d * (V[R][0] + V[D][0]), j + d * (V[R][1] + V[D][1]), d / 2, U, D, R, L, n);
		H_tree_form(v, H_tree, 4 * node + 3, i + d * (V[R][0] + V[U][0]), j + d * (V[R][1] + V[U][1]), d / 2, D, U, L, R, n);
	}

}
int center(int n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }
int depth(int n) { return n <= 7 ? 1 : 2 * depth(n / 4); }