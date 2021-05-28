#include <iostream>

using namespace std;

bool is_prime(int n) {
    if (n == 1) {
        return false;
    }
    
    for (int d=2; d<n; d++) {
        if (n % d == 0) {
            return false;
        } 
    }
    return true;
}

int main() {
	for (int i=1; i<=11; i++) {
		if (is_prime(i))
			cout << i << " is prime\n";
		else
			cout << i << " is not prime\n";
	}
}