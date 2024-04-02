def completar_cuadrado(cuadrado, f, c):
    n = len(cuadrado)
    numero_magico = n * (n**2 + 1) // 2
    if(es_valido(cuadrado)):
        imprimir_cuadrado(cuadrado)
        print("Separador")
        return True
    if f == n:
        return False
    proxima_fila = f + 1
    proxima_columna = c
    if(proxima_fila == len(cuadrado)):
        proxima_fila = 0
        proxima_columna = c + 1
    opciones_disponibles = calcular_opciones(cuadrado)
    for i in range(len(opciones_disponibles)):
        if opciones_disponibles[i] == True:
            if (sumar_columna(cuadrado, c) + i <= numero_magico and sumar_fila(cuadrado, f) + i <= numero_magico):
                cuadrado[f][c] = i + 1
                completar_cuadrado(cuadrado, proxima_fila, proxima_columna)
                cuadrado[f][c] = 0
    return False
    
def es_valido(cuadrado):
    opciones_disponibles = [True] * (len(cuadrado) ** 2)
    for f in range(len(cuadrado)):
        for c in range(len(cuadrado)):
            if(opciones_disponibles[cuadrado[f][c] - 1] == False):
                return False
            else:
                opciones_disponibles[cuadrado[f][c] - 1] = False
    n_magico = sumar_fila(cuadrado, 0)
    d_i = sumar_diagonal_izq(cuadrado)
    d_d = sumar_diagonal_derecha(cuadrado)
    if(d_i != n_magico or d_d != n_magico):
        return False
    for i in range(len(cuadrado)):
        if(sumar_fila(cuadrado, i) != n_magico):
            return False
        if(sumar_columna(cuadrado, i) != n_magico):
            return False
    return True

def sumar_fila(cuadrado, f):
    res = 0
    for i in range(len(cuadrado)):
        res += cuadrado[f][i]
    return res

def sumar_columna(cuadrado, c):
    res = 0
    for i in range(len(cuadrado)):
        res += cuadrado[i][c]
    return res

def sumar_diagonal_derecha(cuadrado):
    res = 0
    for i in range(len(cuadrado)):
        res += cuadrado[i][i]
    return res
    
def sumar_diagonal_izq(cuadrado):
    res = 0 
    for i in range(len(cuadrado) - 1, -1, -1):
        res += cuadrado[len(cuadrado) - i - 1][i]
    return res
    
def calcular_opciones(cuadrado):
    opciones_disponibles = [True] * (len(cuadrado) ** 2)
    for f in range(len(cuadrado)):
        for c in range(len(cuadrado)):
            if cuadrado[f][c] != 0:
                opciones_disponibles[cuadrado[f][c] - 1] = False
    return opciones_disponibles

def imprimir_cuadrado(cuadrado):
    for fila in cuadrado:
        print("|", end="")
        for elemento in fila:
            print(f" {elemento} |", end="")
        print("\n" + "-"*(4*len(fila) + 1))

cuadrado = [
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0]
]

completar_cuadrado(cuadrado, 0, 0)
