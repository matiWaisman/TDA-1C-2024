def test_crear_reinas():
    arr = [None] * 4
    crear_reinas(arr, 0)

def crear_reinas(arr, n):
    if n >= len(arr):
        print(arr)
    for i in range(len(arr)): # Con este recorro las columnas
        puedoPoner = True
        for j in range(n): # Con este recorro las filas anteriores para ver las columnas anteriores que ninguna columna mate
            if (arr[j] == i) or (arr[j] == i - n + j) or (arr[j] == n + i - j):
                puedoPoner = False
        if puedoPoner:
            arr[n] = i
            crear_reinas(arr, n+1)

test_crear_reinas()
