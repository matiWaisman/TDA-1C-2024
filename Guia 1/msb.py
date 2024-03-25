maximo = 0
# No tiene sentido
def calcular_maxi_subconjunto(matriz, k, f, c, I):
    global maximo
    if f == len(matriz) and c == len(matriz):
        if sumar_conjunto(matriz, I) == maximo:
            print(f"Terminé con el máximo: {sumar_conjunto(matriz, I)}")
            print(I)
            return I
        I = []
        return []
    if k == 0:
        if sumar_conjunto(matriz, I) >= maximo:
            return I
        I = []
        return []
    
    prox_f = f 
    prox_c = c + 1
    if prox_c == len(matriz):
        prox_f = f + 1
        prox_c = prox_f 
    
    valor_al_agregar = sumar_conjunto(matriz, I) + matriz[f][c]
    if valor_al_agregar > maximo:
        maximo = valor_al_agregar
    if k != 0:
        max_combinacion_actual = calcular_mejor_combinacion_restante(matriz, f, c, k, 0)
        max_combinacion_siguiente = calcular_mejor_combinacion_restante(matriz, prox_f, prox_c, k - 1, 0)
        if(max_combinacion_siguiente + matriz[f][c] == max_combinacion_actual):
            nueva_lista = I[:]
            nueva_lista.append((f,c))
            agrego = calcular_maxi_subconjunto(matriz, k - 1, prox_f, prox_c, nueva_lista)
            return agrego
        no_agrego = calcular_maxi_subconjunto(matriz, k, prox_f, prox_c, I)
        return no_agrego
    return I
        
    
def sumar_conjunto(matriz, lista_pos):
    res = 0
    for i in range(len(lista_pos)):
        res += matriz[lista_pos[i][0]][lista_pos[i][1]]
    return res
    
    
def calcular_mejor_combinacion_restante(matriz, f, c, k, sumatoria_total):
    global max
    if(f == len(matriz) and c == len(matriz)):
        return sumatoria_total
    if(k == 0):
        return sumatoria_total

    prox_f = f 
    prox_c = c + 1
    if prox_c == len(matriz):
        prox_f = f + 1
        prox_c = prox_f 
    
    
    return max(calcular_mejor_combinacion_restante(matriz, prox_f, prox_c, k, sumatoria_total), calcular_mejor_combinacion_restante(matriz, prox_f, prox_c, k - 1, sumatoria_total + matriz[f][c]))
    
matriz = [
    [0, 10, 10, 1],
    [0, 0, 5, 2],
    [0, 0, 0, 1],
    [0, 0, 0, 0]
]



resultado = calcular_maxi_subconjunto(matriz, 3, 0, 0, [])
print(resultado)