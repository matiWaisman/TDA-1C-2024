maximo = 0

# Este no usa la suma de los siguientes
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
        nueva_lista = I[:]
        nueva_lista.append((f,c))
        agrego = calcular_maxi_subconjunto(matriz, k - 1, prox_f, prox_c, nueva_lista)
        no_agrego = calcular_maxi_subconjunto(matriz, k, prox_f, prox_c, I)
        if sumar_conjunto(matriz, no_agrego) > sumar_conjunto(matriz, agrego):
            return no_agrego
        else:
            return agrego
    print("El resultado es: ")
    return I
        
    
def sumar_conjunto(matriz, lista_pos):
    res = 0
    for i in range(len(lista_pos)):
        res += matriz[lista_pos[i][0]][lista_pos[i][1]]
    return res
    
    
matriz = [
    [0, 10, 10, 1],
    [10, 0, 5, 2],
    [10, 5, 0, 1],
    [1, 2, 1, 0]
]

resultado = calcular_maxi_subconjunto(matriz, 3, 0, 0, [])
print(resultado)
