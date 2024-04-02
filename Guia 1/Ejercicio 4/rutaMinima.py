# Represento la funcion Pi de 1 a n -> 1 a n como un array de n elementos que la posicion seria el dominio y el valor el codominio

min_actual = 10000
llamadas_recu = 0
# Con poda en caso base

def calcular_ruta_minima(matriz, funcion, i):
    global min_actual
    global llamadas_recu
    if(i == len(funcion)):
        return funcion
    # Poda caso base
    suma_parcial_actual = calcular_suma_parcial(matriz, funcion)
    if(suma_parcial_actual > min_actual):
        return []
    opciones_disponibles = calcular_opciones(funcion)
    funcion_min = funcion[:]
    for o in range(len(opciones_disponibles)):
        if opciones_disponibles[o] == True:
            agrego = funcion[:]
            agrego[i] = o
            llamadas_recu += 1
            funcion_agrego = calcular_ruta_minima(matriz, agrego, i+1)
            if(calcular_suma(matriz, funcion_agrego) < calcular_suma(matriz, funcion_min)): 
                funcion_min = funcion_agrego
                min_actual = calcular_suma(matriz, funcion_agrego)
    return funcion_min
"""

# Con poda antes de agregar
def calcular_ruta_minima(matriz, funcion, i):
    global min_actual
    global llamadas_recu
    if(i == len(funcion)):
        return funcion
    if(cantidad_vacios(funcion) + i > len(matriz)):
        return []
    opciones_disponibles = calcular_opciones(funcion)
    funcion_min = funcion[:]
    for o in range(len(opciones_disponibles)):
        if opciones_disponibles[o] == True:
            agrego = funcion[:]
            agrego[i] = o
            # Poda en el cuerpo
            suma_parcial_actual = calcular_suma_parcial(matriz, agrego)
            if(suma_parcial_actual <= min_actual): 
                llamadas_recu += 1
                funcion_agrego = calcular_ruta_minima(matriz, agrego, i+1)
                if(calcular_suma(matriz, funcion_agrego) < calcular_suma(matriz, funcion_min)): 
                    funcion_min = funcion_agrego
                    min_actual = calcular_suma(matriz, funcion_agrego)
    return funcion_min           
"""

def calcular_suma(matriz, funcion):
    if(len(funcion) == 0 or cantidad_vacios(funcion) > 0):
        return 100000
    res = matriz[funcion[len(matriz) - 1]][funcion[0]]
    for i in range(len(funcion) - 1):
        res += matriz[funcion[i]][funcion[i + 1]]
    return res

def calcular_suma_parcial(matriz, funcion):
    res = 0
    if(funcion[len(matriz) - 1] != -1 and funcion[0] != -1):
        res += matriz[funcion[len(matriz) - 1]][funcion[0]]
    for i in range(len(funcion) - 1):
        if(funcion[i] != -1 and funcion[i + 1] != -1):
            res += matriz[funcion[i]][funcion[i + 1]]
    if res == 0:
        return 10000
    else:
        return res



def calcular_opciones(funcion):
    opciones = [True] * len(funcion)
    for i in range(len(funcion)):
        if(funcion[i] != -1):
            opciones[funcion[i]] = False
    return opciones

def cantidad_vacios(funcion):
    res = 0
    for i in range(len(funcion)):
        if(funcion[i] == -1):
            res += 1
    return res

matriz = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]

funcion = [-1,-1,-1,-1]


ruta_minima = calcular_ruta_minima(matriz, funcion, 0)
print(ruta_minima)