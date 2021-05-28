
def is_prime(n):
    if n % 2 == 0:
        return False
    for i in range(3, n):
        if n % i == 0:
            return False
    return True