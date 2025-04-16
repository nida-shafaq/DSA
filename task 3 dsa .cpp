#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class TagCheck {
private:
	string stack[100];
	int top;

public:
	TagCheck() {
		top = -1;
	}

	void push(string tag) {
		if (top < 99) {
			top++;
			stack[top] = tag;
		}
		else
			cout << "Stack is full/overflow" << endl;
	}

	string pop() {
		if (top >= 0) {
			string tag = stack[top];
			top--;
			return tag;
		}
		else
			cout << "Stack is empty/underflow" << endl;// If stack is empty
	}

	bool isEmpty() {
		if (top == -1){
			cout << "Stack is empty" << endl;
		}
		else
			cout << "stack is full" << endl;
		return "";
	}

	void checkFile(string fn) {
		ifstream file(fn);
		if (!file.is_open()) {
			cout << "Could not open file: " << fn << endl;
		}

		string line;
		int lineNumber = 0;

		while (getline(file, line)) {
			lineNumber++;

			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '<') {
					string tag = "";
					bool isClosing = false;

					i++;

					if (i < line.length() && line[i] == '/') {
						isClosing = true;
						i++;
					}

					while (i < line.length() && line[i] != '>') {
						tag += line[i];
						i++;
					}

					if (tag.length() > 0) {
						if (isClosing) {
							string lastOpened = pop();
							if (lastOpened != tag) {
								cout << "Error at line " << lineNumber << ": closing tag </" << tag
									<< "> does not match opening tag <" << lastOpened << ">\n";
							}
						}
						else {
							push(tag);
						}
					}
				}
			}
		}

		while (!isEmpty()) {
			string other = pop();
			cout << "Error: unclosed tag <" << other << ">\n";
		}

		file.close();
	}
};

int main() {
	TagCheck checker;
	checker.checkFile("myfile.html");
	system("pause");
	return 0;
}

