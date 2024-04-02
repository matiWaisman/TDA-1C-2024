class Casillero:
    def __init__(self, valor, esFijo):
        self.valor = valor
        self.esFijo = esFijo

# Filas -> Columnas



def completar_sudoku(tablero, fila_actual, columna_actual):
    if(columna_actual == len(tablero)): # Caso base en el que "Ya termine"
        if(es_valido(tablero)):
            mostrar_tablero(tablero)
            return True
        else: 
            return False
    if(es_valido(tablero) == False):
        return False
    proxima_fila = fila_actual + 1
    proxima_columna = columna_actual
    if(proxima_fila == len(tablero)):
        proxima_fila = 0
        proxima_columna = columna_actual + 1
    if tablero[fila_actual][columna_actual].esFijo == False: 
        opciones_disponibles = calcular_opciones(tablero, fila_actual, columna_actual)
        for o in range(len(opciones_disponibles)): 
            if opciones_disponibles[o] == True: 
                tablero[fila_actual][columna_actual].valor = o + 1
                # Veo el siguiente desplazamiento
                # Hago la llamada recursiva con la siguiente posicion
                completar_sudoku(tablero, proxima_fila, proxima_columna)
        tablero[fila_actual][columna_actual].valor = 0 # Si no funciona ninguna solucion la reseteo
        return False # Si ninguna opcion disponible es una solucion hago el bt
    completar_sudoku(tablero, proxima_fila, proxima_columna)
    
    

    
    
# No cuenta los 0's, es para evaluar parcialmente
def es_valido(tablero): 
    for i in range(0, len(tablero)):
        if(es_fila_valida(tablero, i) == False or es_columna_valida(tablero, i) == False):
            return False
        f_n = 0 # Recorre las filas en raiz de n asi no paso por todas las casillas que no hace falta
        while f_n < len(tablero):
            c_n = 0 # Recorre las columnas en raiz de n asi no paso por todas las casillas que no hace falta
            while c_n < len(tablero):
                if(es_subgrilla_valida(tablero, f_n, c_n) == False):
                    return False
                c_n += int(len(tablero) ** 0.5)
            f_n += int(len(tablero) ** 0.5) 
    return True

# No cuenta los 0's, es para evaluar parcialmente
def es_fila_valida(tablero, fila): 
    opciones_disponibles = [False] * len(tablero)
    for i in range(len(tablero)):
        if(tablero[fila][i].valor != 0):
            if opciones_disponibles[tablero[fila][i].valor - 1]:
                return False
            else:
                opciones_disponibles[tablero[fila][i].valor - 1] = True
    return True
    

# No cuenta los 0's, es para evaluar parcialmente
def es_columna_valida(tablero, columna):
    opciones_disponibles = [False] * len(tablero)
    for i in range(len(tablero)):
        if(tablero[i][columna].valor != 0):
            if opciones_disponibles[tablero[i][columna].valor - 1]:
                return False
            else:
                opciones_disponibles[tablero[i][columna].valor - 1] = True
    return True

# No cuenta los 0's, es para evaluar parcialmente    
def es_subgrilla_valida(tablero, fila, columna):
    opciones_disponibles = [False] * len(tablero)
    tamaño_subgrilla = int(len(tablero) ** 0.5)
    desde_fila = fila - fila % tamaño_subgrilla
    hasta_fila = desde_fila + tamaño_subgrilla - 1
    desde_columna = columna - columna % tamaño_subgrilla 
    hasta_columna = desde_columna + tamaño_subgrilla - 1
    for f in range(desde_fila, hasta_fila + 1):
        for c in range(desde_columna, hasta_columna + 1):
            if(tablero[f][c].valor != 0):
                if opciones_disponibles[tablero[f][c].valor - 1]:
                    return False
                else:
                    opciones_disponibles[tablero[f][c].valor - 1] = True  
    return True
    
    
def mostrar_tablero(tablero):
    n = len(tablero)
    m = len(tablero[0])
    horizontal_line = "+---" + "+---" * (m - 1) + "+"
    for i in range(n):
        if i % int(n**0.5) == 0:
            print(horizontal_line)
        row = "|"
        for j in range(m):
            if tablero[i][j].valor == 0:
                row += "   "
            else:
                row += " " + str(tablero[i][j].valor) + " "
            if (j + 1) % int(m**0.5) == 0:
                row += "|"
        print(row)
    print(horizontal_line)

def calcular_opciones(tablero, f, c): 
    opciones_disponibles = [True] * len(tablero)
    for i in range(len(tablero)):
        if tablero[f][i].valor != 0:
            opciones_disponibles[tablero[f][i].valor - 1] = False
        if tablero[i][c].valor != 0:
            opciones_disponibles[tablero[i][c].valor - 1] = False
    tamaño_subgrilla = int(len(tablero) ** 0.5)
    desde_fila = f - f % tamaño_subgrilla
    hasta_fila = desde_fila + tamaño_subgrilla - 1
    desde_columna = c - c % tamaño_subgrilla 
    hasta_columna = desde_columna + tamaño_subgrilla - 1
    for fila in range(desde_fila, hasta_fila + 1):
        for columna in range(desde_columna, hasta_columna + 1):
            if tablero[fila][columna].valor != 0:
                opciones_disponibles[tablero[fila][columna].valor - 1] = False
    return opciones_disponibles
    



tablero9 = [
    [Casillero(5, True), Casillero(3, True), Casillero(0, False), Casillero(0, False), Casillero(7, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False)],
    [Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(1, True), Casillero(9, True), Casillero(5, True), Casillero(0, False), Casillero(0, False), Casillero(0, False)],
    [Casillero(0, False), Casillero(9, True), Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True), Casillero(0, False)],
    [Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(3, True)],
    [Casillero(4, True), Casillero(0, False), Casillero(0, False), Casillero(8, True), Casillero(0, False), Casillero(3, True), Casillero(0, False), Casillero(0, False), Casillero(1, True)],
    [Casillero(7, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(2, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True)],
    [Casillero(0, False), Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(2, True), Casillero(8, True), Casillero(0, False)],
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(4, True), Casillero(1, True), Casillero(9, True), Casillero(0, False), Casillero(0, False), Casillero(5, True)],
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(7, True), Casillero(9, True)]
]

tablero_ppt = [
    [Casillero(5, True), Casillero(3, True), Casillero(0, False), Casillero(0, False), Casillero(7, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False)],
    [Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(1, True), Casillero(9, True), Casillero(5, True), Casillero(0, False), Casillero(0, False), Casillero(0, False)],
    [Casillero(0, False), Casillero(9, True), Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True), Casillero(0, False)],
    [Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(3, True)],
    [Casillero(4, True), Casillero(0, False), Casillero(0, False), Casillero(8, True), Casillero(0, False), Casillero(3, True), Casillero(0, False), Casillero(0, False), Casillero(1, True)],
    [Casillero(7, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(2, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(6, True)],
    [Casillero(0, False), Casillero(6, True), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(2, True), Casillero(8, True), Casillero(0, False)],
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(4, True), Casillero(1, True), Casillero(9, True), Casillero(0, False), Casillero(0, False), Casillero(5, True)],
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(8, True), Casillero(0, False), Casillero(0, False), Casillero(7, True), Casillero(9, True)],
]



tablero4f = [
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(4, True)],
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(0, False)],
    [Casillero(2, True), Casillero(0, False), Casillero(0, False), Casillero(3, True)],
    [Casillero(4, True), Casillero(0, False), Casillero(1, True), Casillero(2, True)],
]

tablero4d = [
    [Casillero(0, False), Casillero(0, False), Casillero(0, False), Casillero(3, True)],
    [Casillero(0, False), Casillero(4, True), Casillero(0, False), Casillero(0, False)],
    [Casillero(0, False), Casillero(0, False), Casillero(3, True), Casillero(0, False)],
    [Casillero(4, True), Casillero(0, False), Casillero(0, False), Casillero(2, True)],
]


completar_sudoku(tablero_ppt, 0, 0)