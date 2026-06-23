A = [31,41,59,26,41,58]


for i in range(len(A) - 1):
    j = i
    smallest_idx = i
    while j < len(A):
        if A[j] < A[smallest_idx]:
            smallest_idx = j
        j+=1
    temp = A[i]
    A[i] = A[smallest_idx]
    A[smallest_idx] = temp

print(A)
