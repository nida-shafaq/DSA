#include <iostream>
using namespace std;

const int MAX = 100;

class Drone {
public:
	int id;
	int priority;
};

class Stack {
	Drone data[MAX];
	int top;

public:
	Stack() {
		top = -1;
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top >= MAX;
	}

	void push(Drone d) {
		if (!isFull()) {
			data[++top] = d;
		}
		else
			cout << "Stack is full" << endl;
	}

	Drone pop() {
		if (!isEmpty()) {
			return data[top--];
		}
		Drone d = { -1, -1 };//if there is no drone it return dummy values for drone 
		//this step is neccessary bcz of returntype that is not void
		return d;
	}

	Drone peek() {
		if (!isEmpty()) return data[top];
		Drone d = { -1, -1 };
		return d;
	}

	int Size() {
		return top + 1;
	}

	Drone getIndex(int index) {
		if (index >= 0 && index <= top)
			return data[index];
		return{ -1, -1 };
	}

	void remove(int index) {
		for (int i = index; i < top; i++) {
			data[i] = data[i + 1];
		}
		top--;
	}

	void display() {
		for (int i = top; i >= 0; i--) {
			cout << "Drone ID: " << data[i].id << ", Priority: " << data[i].priority << endl;
		}
	}
};

class DroneDispatcher {
	Stack droneStack;

public:
	void addDrone(int id, int priority) {
		Drone d = { id, priority };
		droneStack.push(d);
	}

	void dispatchHighestPriority() {
		if (droneStack.isEmpty()) {
			cout << "No drones to dispatch.\n";
			return;
		}

		int highestPriority = -1;
		int index = -1;
		for (int i = 0; i < droneStack.Size(); i++) {
			Drone d = droneStack.getIndex(i);
			if (d.priority > highestPriority) {
				highestPriority = d.priority;
				index = i;
			}
		}

		if (index != -1) {
			Drone dispatched = droneStack.getIndex(index);
			droneStack.remove(index);
			cout << "Dispatched Drone ID: " << dispatched.id << " with Priority: " << dispatched.priority << endl;
		}
	}

	void display() {
		droneStack.display();
	}
};

int main() {
	DroneDispatcher d;
	d.addDrone(101, 3);
	d.addDrone(102, 5);
	d.addDrone(103, 2);

	cout << "All drones:\n";
	d.display();

	cout << "\nDispatching highest priority drone...\n";
	d.dispatchHighestPriority();

	cout << "\nRemaining drones:\n";
	d.display();
	system("pause");
	return 0;
}