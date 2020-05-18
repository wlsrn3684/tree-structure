// ������ 2018203055

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void rotated_form(vector<string> v, int n, int space);
void not_rotated_form(vector<string> v);
void H_tree_form(vector<string> v, string** H_tree, int node, int i, int j, int d, int U, int D, int R, int L, int n);
int center(int n); // H_tree ���� �� ����� ���� �˷��ִ� �Լ�
int depth(int n); // H_tree ���� depth �� ��ȯ�ϴ� �Լ�

int main(void) {
	vector<string> v;
	string str;
	stringstream ss;

	while (cin >> str) {
		if (str == "EOI") { // EOI��� �Է� ��
			break;
		}
		else if (str == "INS") { // ������ ���� ���ڿ��� �Է�
			cin >> str;
			v.push_back(str);
			push_heap(v.begin(), v.end());
		}
		else if (str == "DEL") { // ��Ʈ��� ����
			pop_heap(v.begin(), v.end()); // ��Ʈ ���� ������ ��带 �ٲ�
			v.pop_back(); // �� ������ ��带 ����
		}
	}

	cout << "1. rotated form" << endl;
	rotated_form(v, 0, 0); // rotated form ���
	
	cout << endl << endl << "2. non rotated form" << endl;
	not_rotated_form(v); // not rotated form ���
	cout << endl << endl;

	int pow = 0;
	int tmp = v.size();
	int size = 2;

	while (tmp > 0) {
		pow++;
		tmp /= 2;
	}

	for (int i = 0; i < pow; pow -= 2) { // H_tree ������ ����
		size *= 2;
	}
	size--;


	string ** H_tree = new string*[size]; // 2�����迭 �����Ҵ�
	for (int i = 0; i < size; i++) {
		H_tree[i] = new string[size];
	}

	for (int i = 0; i < size; i++) { // H-tree �ʱ�ȭ
		for (int j = 0; j < size; j++) {
			H_tree[i][j] = " ";
		}
	}

	H_tree_form(v, H_tree, 1, center(v.size()), center(v.size()), depth(v.size()), 0, 1, 2, 3, v.size());

	cout << endl << "3. H-tree form";
	for (int i = 0; i < size; i++) { // H-tree ���
		for (int j = 0; j < size; j++) {
			cout << H_tree[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

void rotated_form(vector<string> v, int n, int space) {
	if (n * 2 + 2 < v.size()) { // �����ʿ� �ڽ��� �ִٸ� ���
		rotated_form(v, n * 2 + 2, space + 1);
	}
	for (int i = 0; i < space; i++) cout << "  "; //�� �� ��� �Ǿ������� ���� ���� ����
	cout << v[n] << endl;
	if (n * 2 + 1 < v.size()) { // ���ʿ� �ڽ��� �ִٸ� ���
		rotated_form(v, n * 2 + 1, space + 1);
	}
}

void not_rotated_form(vector<string> v) {

	int max = 1; // ���� ������ ��� Ȯ�ο�
	int space = 1; // ���� ������
	int tmp = v.size();
	int pow = 0;
	while (tmp / 2 > 0) {
		pow++;
		tmp /= 2;
	}
	for (int i = 0; i < pow; i++) {  // �ִ� ���� ����
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

		if (i % max + 2 == max || i == 0) { // ���� �������� ����� �Ŀ� ���� �ٷ� �ѱ��
			cout << endl;
			max *= 2; // ���� ������ Ȯ�� ���� ����
			space /= 2; // ���� ���̱�
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