#include <bits/stdc++.h>
using std::unordered_map;
using std::deque;

typedef uint64_t Key;
typedef uint64_t Value;

int TRANSACTIONS_COUNT = 10;

struct Version {
	Value value_;      // The value of this version
	int max_read_id_;  // Largest timestamp of a transaction that read the version
	int version_id_;   // Timestamp of the transaction that created(wrote) the version
};

unordered_map<int, deque<Version*>*> mvcc_data_;

// Print all versions in a deque.
void print_deque(deque<Version*>* deque_, Key key) {
	for (deque<Version*>::iterator it = deque_->begin(); it != deque_->end(); ++it) {
		std::cout << "Transaction ID: " << key << std::endl;
		std::cout << "Value: " <<  (*it)->value_ << std::endl;
		std::cout << "max_read_id_: " << (*it)->max_read_id_ << std::endl;
		std::cout << "version_id_: " << (*it)->version_id_ << std::endl << std::endl;
	}
}

bool Read(Key key, Value *result, int txn_unique_id) {
	// Copy paste your read code from main program here
}

// Check whether apply or abort the write
bool CheckWrite(Key key, int txn_unique_id) {
  // Copy paste your checkwrite code from main program here
}

void Write(Key key, Value value, int txn_unique_id) {
	if (CheckWrite(key, txn_unique_id)) {
		// Copy paste your write code from main program here.
	}
}

int main ()
{
	std::cout << "Begin writing transactions:" << std::endl << std::endl;

	// Insert transactions to key.
	for (int i = 1; i <= TRANSACTIONS_COUNT; i++) {
		Write(i, 0, 0);
		// Check if write function is correct.
		print_deque(mvcc_data_[i], i);
	}

	std::cout << "Please input your test case:" << std::endl << std::endl;
	
	for (int i = 0; i < 100000; i++) {
		// Type: 'r' or 'w'. Read or write...
		char type;
		Key key = 0;
		Value value = 0;
		int version_id = 0;
		std::cin >> type;
		std::cin >> key;
		std::cin >> value;
		std::cin >> version_id;
		if (type == 'r') {
			bool check = Read(key, &value, version_id);	
			std::cout << "VALUE READ: " <<  value << std::endl << std::endl;
			if (check) {
				print_deque(mvcc_data_[key], key);
			}
		} else if (type == 'w') {
			Write(key, value, version_id);
			std::cout << "VALUE WRITTEN: " << value << std::endl << std::endl;
			print_deque(mvcc_data_[key], key);
		}
	}
}

/*
	Test cases:
	1.

	r
	1
	1234  
	3

	2.

	w
	1
	3
	2

	3.

	w
	1
	3
	4

	4.

	r
	1
	3
	4

	5. 

	r
	1
	3
	5

	6.

	r
	1
	3
	3

	7.

	r
	1
	3
	2

	8.

	w
	11
	19
	20
*/

/*
Solution:
1.
VALUE READ: 0

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

2.
VALUE WRITTEN: 3

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0


3.

VALUE WRITTEN: 3

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

Transaction ID: 1
Value: 3
max_read_id_: 4
version_id_: 4

4.

VALUE READ: 3

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

Transaction ID: 1
Value: 3
max_read_id_: 4
version_id_: 4

5.
VALUE READ: 3

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

Transaction ID: 1
Value: 3
max_read_id_: 5
version_id_: 4

6.
VALUE READ: 0

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

Transaction ID: 1
Value: 3
max_read_id_: 5
version_id_: 4


7.

VALUE READ: 0

Transaction ID: 1
Value: 0
max_read_id_: 3
version_id_: 0

Transaction ID: 1
Value: 3
max_read_id_: 5
version_id_: 4


8.
VALUE WRITTEN: 19

Transaction ID: 11
Value: 19
max_read_id_: 20
version_id_: 20

*/