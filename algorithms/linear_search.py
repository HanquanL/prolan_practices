A = [31,41,59,26,41,58]
v1 = 59
v2 = 100

def linear_search(A, v):
    for i in range(len(A)):
        if v == A[i]:
            print(i)
            return i
    print("NIL")
    return None

linear_search(A, v2)  