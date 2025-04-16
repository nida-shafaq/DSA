#include <iostream>
using namespace std;

class Command {
private:
	string* buffer;
	int capacity;//to store the capacity that is 4
	int size;// to store the current commands present
	int start;

	void resize() {
		int newCapacity = capacity * 2;
		string* newBuffer = new string[newCapacity];

		// Copy elements in newbuffer
		for (int i = 0; i < size; ++i) {
			newBuffer[i] = buffer[(start + i) % capacity];
		}

		delete[] buffer;
		buffer = newBuffer;
		capacity = newCapacity;
		start = 0;
	}

public:
	Command() {
		capacity = 4;
		size = 0;
		start = 0;
		buffer = new string[capacity];
	}

	void addCommand(string command) {
		if (size == capacity) {
			resize();
		}

		int index = (start + size) % capacity;
		buffer[index] = command;
		size++;

		// Discard oldest if size exceeds 10
		if (size > 10) {
			start = (start + 1) % capacity;
			size--;
		}
	}

	void display() {
		cout << "Current Commands:\n";
		for (int i = 0; i < size; ++i) {
			cout << buffer[(start + i) % capacity] << endl;
		}
	}

	~Command() {
		delete[] buffer;
	}
};

int main() {
	Command robot;

	robot.addCommand("MOVE 10");
	robot.addCommand("TURN LEFT");
	robot.addCommand("MOVE 5");
	robot.addCommand("TURN RIGHT");
	robot.addCommand("MOVE 15");
	robot.addCommand("WAIT");
	robot.addCommand("TURN LEFT");
	robot.addCommand("MOVE 20");
	robot.addCommand("STOP");
	robot.addCommand("TURN RIGHT");
	robot.addCommand("MOVE 30");  // 11th command, oldest will be discarded

	robot.display();

	return 0;
}