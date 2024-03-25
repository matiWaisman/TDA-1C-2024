def calcular_maxi_subconjunto(matriz, k, f, c, conjunto):
    if(f == len(matriz) and c == len(matriz)):
        return conjunto
    if(k == 0):
        return conjunto
    proxima_fila = f + 1
    proxima_columna = c
    if(proxima_fila == len(matriz)):
        proxima_fila = 0
        proxima_columna = c + 1
    agrego = conjunto[:]
    agrego.append(f)
    conjunto_agrego = calcular_maxi_subconjunto(matriz, k - 1, proxima_fila, proxima_columna, agrego)
    conjunto_no_agrego = calcular_maxi_subconjunto(matriz, k, proxima_fila, proxima_columna, conjunto)
    if(sumar_posiciones(matriz, conjunto_agrego) > sumar_posiciones(matriz, conjunto_no_agrego)):
        return conjunto_agrego
    else: 
        return conjunto_no_agrego
    
def sumar_posiciones(matriz, conjunto):
    res = 0
    for f in range(len(conjunto)):
        for col in range(len(conjunto)):
            res += matriz[conjunto[f]][conjunto[col]]
    return res

matriz = [
    [0,10,10,1],
    [10,0,5,2],
    [10,5,0,2],
    [1,2,1,0]
]

print(calcular_maxi_subconjunto(matriz, 3, 0, 0, []))
