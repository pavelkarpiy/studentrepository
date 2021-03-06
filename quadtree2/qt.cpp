#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;
int Rsize = 128;

template <class ValueT>
struct QTree {
	vector<QTree *> InternalNode;
	ValueT *t = new ValueT;
	bool isvalue = false;
	bool issected = false;
	int CordX, CordY;
	int size;

	QTree(int Size) : InternalNode(0), CordX(0), CordY(0) {
		size = Size;
	}

	void insert(int PositionX, int PositionY, ValueT val) {
		if (PositionX <= size && PositionY <= size && PositionX > 0 && PositionY > 0) {

			if (((InternalNode.size() == 0) && (isvalue == false)) || ((InternalNode.size() == 0) && (CordX == PositionX) && (CordY == PositionY))) {
				*t = val;
				CordX = PositionX;
				CordY = PositionY;
				isvalue = true;
			}
			else {
				if (issected == false) {
					InternalNode.resize(4);
					InternalNode[0] = new QTree(size / 2);
					InternalNode[1] = new QTree(size / 2);
					InternalNode[2] = new QTree(size / 2);
					InternalNode[3] = new QTree(size / 2);
					issected = true;


					if ((CordX > size / 2) && (CordY > size / 2)) {
						InternalNode[0]->insert(CordX - size / 2, CordY - size / 2, *t);
					}
					if ((CordX <= size / 2) && (CordY > size / 2)) {
						InternalNode[1]->insert(CordX, CordY - size / 2, *t);
					}
					if ((CordX <= size / 2) && (CordY <= size / 2)) {
						InternalNode[2]->insert(CordX, CordY, *t);
					}
					if ((CordX > size / 2) && (CordY <= size / 2)) {
						InternalNode[3]->insert(CordX - size / 2, CordY, *t);
					}

					delete t;
					isvalue = false;
				}

				if ((PositionX > size / 2) && (PositionY > size / 2)) {
					InternalNode[0]->insert(PositionX - size / 2, PositionY - size / 2, val);
				}
				if ((PositionX <= size / 2) && (PositionY > size / 2)) {
					InternalNode[1]->insert(PositionX, PositionY - size / 2, val);
				}
				if ((PositionX <= size / 2) && (PositionY <= size / 2)) {
					InternalNode[2]->insert(PositionX, PositionY, val);
				}
				if ((PositionX > size / 2) && (PositionY <= size / 2)) {
					InternalNode[3]->insert(PositionX - size / 2, PositionY, val);
				}
			}
		}
	}

	ValueT* get(int PositionX, int PositionY) {

		if (PositionX <= size && PositionY <= size && PositionY > 0 && PositionX > 0) {
			if ((PositionX > size / 2) && (PositionY > size / 2)) {
				if (InternalNode.size() != 0) { return InternalNode[0]->get(PositionX - size / 2, PositionY - size / 2); }
				else if (isvalue == true && CordX == PositionX && CordY == PositionY) { return t; }
				else { return nullptr; }
			}
			if ((PositionX <= size / 2) && (PositionY > size / 2)) {
				if (InternalNode.size() != 0) { return InternalNode[1]->get(PositionX, PositionY - size / 2); }
				else if (isvalue == true && CordX == PositionX && CordY == PositionY) { return t; }
				else { return nullptr; }
			}
			if ((PositionX <= size / 2) && (PositionY <= size / 2)) {
				if (InternalNode.size() != 0) { return InternalNode[2]->get(PositionX, PositionY); }
				else if (isvalue == true && CordX == PositionX && CordY == PositionY) { return t; }
				else { return nullptr; }
			}
			if ((PositionX > size / 2) && (PositionY <= size / 2)) {
				if (InternalNode.size() != 0) { return InternalNode[3]->get(PositionX - size / 2, PositionY); }
				else if (isvalue == true && CordX == PositionX && CordY == PositionY) { return t; }
				else { return nullptr; }
			}
			else { return nullptr; }
		}
		else { return nullptr; }
	}


	void del(int PositionX, int PositionY) {
		if (get(PositionX, PositionY) != nullptr) {

			if (PositionX <= size && PositionY <= size && PositionY > 0 && PositionX > 0) {
				if ((PositionX > size / 2) && (PositionY > size / 2)) {
					if (InternalNode.size() != 0) { InternalNode[0]->del(PositionX - size / 2, PositionY - size / 2); }
					else if (CordX == PositionX && CordY == PositionY) {
						delete t;
						isvalue = false;
					}

				}
				if ((PositionX <= size / 2) && (PositionY > size / 2)) {
					if (InternalNode.size() != 0) { InternalNode[1]->del(PositionX, PositionY - size / 2); }
					else if (CordX == PositionX && CordY == PositionY) {
						delete t;
						isvalue = false;
					}
				}
				if ((PositionX <= size / 2) && (PositionY <= size / 2)) {
					if (InternalNode.size() != 0) { InternalNode[2]->del(PositionX, PositionY); }
					else if (CordX == PositionX && CordY == PositionY) {
						delete t;
						isvalue = false;
					}
				}
				if ((PositionX > size / 2) && (PositionY <= size / 2)) {
					if (InternalNode.size() != 0) { InternalNode[3]->del(PositionX - size / 2, PositionY); }
					else if (CordX == PositionX && CordY == PositionY) {
						delete t;
						isvalue = false;
					}
				}
			}
		}
	}

	void getnearest(int PositionX, int PositionY, int rad) {
		int a;
		int b;
		int c;
		int d;

		if (PositionX - rad < 0) a = 0;
		else a = PositionX - rad;

		if (PositionX + rad > Rsize) b = Rsize;
		else b = PositionX + rad;

		if (PositionY + rad > Rsize) c = Rsize;
		else c = PositionY + rad;

		if (PositionY - rad < 0) d = 0;
		else d = PositionY - rad;

		for (int i = d; i <= c; i++) {
			for (int j = a; j <= b; j++) {
				if (((PositionY - i) * (PositionY - i) + (PositionX - j) * (PositionX - j)) <= rad * rad) {
					if (get(j, i) != nullptr) {
						cout << *get(j, i) << endl;
					}
				}

			}
		}

	}


};

int main() {
	QTree<int> tree(Rsize);
	system("CLS");
	while (1) {
		string com;
		int ik;
		int ig;
		int value;
		
		cout << "enter command, two numbers, value('0' for command 'get')" << endl;
		cin >> com >> ik >> ig >> value;
		if (com == "exit") {
			break;
		}
		else if (com == "delete") {
			tree.del(ik, ig);
			system("CLS");
		}
		else if (com == "insert") {
			tree.insert(ik, ig, value);
			system("CLS");
		}
		else if (com == "getnearest") {
			tree.getnearest(ik, ig, value);
		}
		else if (com == "get") {
			if (tree.get(ik, ig) != nullptr) cout << *tree.get(ik, ig) << endl;
		};
	}
	return 0;
}