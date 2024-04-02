## Caso de solamente devolver la capacidad maxima que se puede llenar
def calcular_maxima_capacidad(capacidad_max, i, suma, canciones):
    if(suma == capacidad_max): 
        return suma
    if(suma > capacidad_max): 
        return -10000
    if(i == len(canciones)):
        return suma
    agrego = calcular_maxima_capacidad(capacidad_max, i + 1, suma + canciones[i], canciones)
    noAgrego = calcular_maxima_capacidad(capacidad_max, i + 1, suma, canciones)
    return max(agrego, noAgrego)

maximas_configuraciones = []
maxima_suma = 0

## Caso en el que devuelvo la combinacion
def calcular_maxima_configuracion(capacidad_max, i, arr, canciones):
    global maxima_suma
    if(sumar_elementos(arr) == capacidad_max):
        if(maxima_suma == capacidad_max): 
            maximas_configuraciones.append(arr)
        else: 
            maxima_suma = capacidad_max 
            maximas_configuraciones.clear()
            maximas_configuraciones.append(arr)
        return arr
    if(i == len(canciones)):
        if len(maximas_configuraciones) > 0: 
            max_anterior = sumar_elementos(maximas_configuraciones[0])
            configuracion_actual = sumar_elementos(arr)
            if configuracion_actual > max_anterior: 
                maximas_configuraciones.clear()
                maximas_configuraciones.append(configuracion_actual)
                maxima_suma = configuracion_actual
            if configuracion_actual == max_anterior:
                maximas_configuraciones.append(configuracion_actual)
        elif len(arr) > 0: 
            maximas_configuraciones.append(arr)
            maxima_suma = sumar_elementos(arr)
        return arr
    noAgrego = calcular_maxima_configuracion(capacidad_max, i + 1, arr, canciones)
    if(sumar_elementos(arr) + canciones[i] <= capacidad_max):
        agrego = calcular_maxima_configuracion(capacidad_max, i + 1, arr + [canciones[i]], canciones)
        
    



    
    
def sumar_elementos(arr):
    res = 0
    for i in range(len(arr)): 
        res += arr[i]
    return res

def main():
    while True:
        try:
            
            linea = input()
            
            
            if not linea:
                break
            
           
            valores = list(map(int, linea.split()))
            N = valores[0]
            duraciones_pistas = valores[2:]
            
            
            calcular_maxima_configuracion(N, 0, [], duraciones_pistas)
            res = maximas_configuraciones[0]
            for elemento in res:
                print(elemento, end=" ")  
            print("sum:", sum(res))
                
        except EOFError:
            break


if __name__ == "__main__":
    
    main()


