#include <string>
#include <iostream>
using namespace std;

int main() {
	string a = "ab";
	string b = "ba";
	if (a[0] == b[1]) {
		cout << "ok" << endl;
	}
	return 0;
}
