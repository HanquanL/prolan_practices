# example input
A = [1, 0, 1, 1]
B = [0, 1, 1, 0]
C = [0] * (len(A) + 1)
carry = 0

for i in reversed(range(len(A))):
    sum = int( A[i] + B[i] + carry)
    C[i + 1] = sum % 2
    carry = sum / 2
if carry == 1:
    C[0] = 1
else:
    C[0] = 0

print(C)

