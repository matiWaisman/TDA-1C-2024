def calcular_maxi_subconjunto(matriz, k, f, c, conjunto):
    if(c == len(matriz)):
        return conjunto
    if(len(conjunto) == k):
        return conjunto
    # Calculo cuantos elementos faltan por recorrer
    elementos_restantes_fila_actual = len(matriz) - (c + 1)
    filas_restantes = len(matriz) - (f + 1)
    elementos_filas_restantes = filas_restantes * len(matriz)
    total_elementos_restantes = elementos_restantes_fila_actual + elementos_filas_restantes
    # Asi elimino un par de opciones de conjuntos de menos de k elementos
    if(k > total_elementos_restantes + len(conjunto)):
        return []
    proxima_fila = f + 1
    proxima_columna = c
    if(proxima_fila == len(matriz)):
        proxima_fila = 0
        proxima_columna = c + 1
    agrego = conjunto[:]
    agrego.append(f)
    conjunto_agrego = calcular_maxi_subconjunto(matriz, k, proxima_fila, proxima_columna, agrego)
    conjunto_no_agrego = calcular_maxi_subconjunto(matriz, k, proxima_fila, proxima_columna, conjunto)
    if(sumar_posiciones(matriz, conjunto_agrego) > sumar_posiciones(matriz, conjunto_no_agrego)):
        return conjunto_agrego
    else: 
        return conjunto_no_agrego
    
max_actual = -10000  
llamadas_recu = 0  
    
def calcular_maxi_subconjunto(matriz, k):
    conjunto = [-1] * k
    return msc(matriz, k, conjunto, 0)    
    
def msc(matriz, k, conjunto, i):
    global max_actual
    global llamadas_recu
    if(cantidad_vacios(conjunto) == 0):
        return conjunto
    if(cantidad_vacios(conjunto) + i > k):
        return [-1] * k
    opciones_disponibles = calcular_opciones(conjunto)
    conjunto_max = conjunto[:]
    for o in range(len(opciones_disponibles)):
        if opciones_disponibles[o] == True:
            agrego = conjunto[:]
            agrego[i] = o
            # Poda en el cuerpo
            suma_parcial_actual = sumar_posiciones(matriz, agrego)
            if(suma_parcial_actual > max_actual): 
                llamadas_recu += 1
                conjunto_agrego = msc(matriz, k, agrego, i+1)
                if(sumar_posiciones(matriz, conjunto_agrego) > sumar_posiciones(matriz, conjunto_max)): 
                    conjunto_max = conjunto_agrego
                    max_actual = sumar_posiciones(matriz, conjunto_agrego)
    return conjunto_max          

def cantidad_vacios(conjunto):
    res = 0
    for i in range(len(conjunto)):
        if(conjunto[i] == -1):
            res += 1
    return res

def calcular_opciones(conjunto):
    opciones = [True] * len(conjunto)
    for i in range(len(conjunto)):
        if(conjunto[i] != -1):
            opciones[conjunto[i]] = False
    return opciones

def sumar_posiciones(matriz, conjunto):
    res = 0
    for f in range(len(conjunto)):
        for col in range(len(conjunto)):
            if(conjunto[f] != -1 and conjunto[col] != -1):
                res += matriz[conjunto[f]][conjunto[col]]
    return res

matriz = [
    [0,10,10,1],
    [10,0,5,2],
    [10,5,0,2],
    [1,2,1,0]
]

print(calcular_maxi_subconjunto(matriz, 3))
