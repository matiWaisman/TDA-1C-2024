class Jugador:
    def __init__(self, nombre, ataque, defensa):
        self.nombre = nombre
        self.ataque = ataque
        self.defensa = defensa

def armar_equipo(jugadores, ataque, defensa, i, m_a):
    if(i == len(jugadores)):
        if(sumar_ataque(ataque) == m_a):
            return ataque, defensa
        else: 
            return [], []
    ataque_final_a, defensa_final_a = ataque, defensa
    ataque_final_b, defensa_final_b = ataque, defensa
    if(len(ataque) < 5):
        nuevo_ataque = ataque + [jugadores[i]]
        ataque_final_a, defensa_final_a = armar_equipo(jugadores, nuevo_ataque, defensa, i + 1, m_a)
    if(len(defensa) < 5):
        nueva_defensa = defensa + [jugadores[i]]
        ataque_final_b, defensa_final_b = armar_equipo(jugadores, ataque, nueva_defensa, i + 1, m_a)
    return determinar_final(ataque_final_a, ataque_final_b, defensa_final_a, defensa_final_b)
    
    

def calcular_maximo_ataque(jugadores, k, i, sumatoria):
    if(i == len(jugadores)):
        return sumatoria
    if(k == 0):
        return sumatoria
    return max(calcular_maximo_ataque(jugadores, k, i + 1, sumatoria), calcular_maximo_ataque(jugadores, k - 1, i + 1, sumatoria + jugadores[i].ataque))

def sumar_ataque(j):
    res = 0
    for i in range(len(j)):
        res += j[i].ataque
    return res

def sumar_defensa(j):
    res = 0
    for i in range(len(j)):
        res += j[i].defensa
    return res

def determinar_final(ataque_final_a, ataque_final_b, defensa_final_a, defensa_final_b):
    if(sumar_ataque(ataque_final_a) == sumar_ataque(ataque_final_b)):
        if(sumar_defensa(defensa_final_a) > sumar_defensa(defensa_final_b)):
            return ataque_final_a, defensa_final_a
        else:
            return ataque_final_b, defensa_final_b
    if(sumar_ataque(ataque_final_a) > sumar_ataque(ataque_final_b)):
        return ataque_final_a, defensa_final_a
    else:
        return ataque_final_b, defensa_final_b
    


def main():
    palabras = []
    while True:
        try:
            linea = input().strip()
            if not linea:
                break
            palabras.extend(linea.split())
        except EOFError:
            break
    cantidad_equipos = int(palabras[0])
    equipos = []
    indice = 1  
    
    for _ in range(cantidad_equipos):
        jugadores = []  
        for _ in range(10):
            nombre = palabras[indice]
            ataque = int(palabras[indice + 1])
            defensa = int(palabras[indice + 2])
            jugador = Jugador(nombre, ataque, defensa)
            jugadores.append(jugador)
            indice += 3 
        equipos.append(jugadores)
    for e in range(len(equipos)):
        ma = calcular_maximo_ataque(equipos[e], 5, 0, 0)
        # Ordeno por nombre asi gana el que esta primero alfabeticamente
        equipo_ordenado_por_nombre = sorted(equipos[e], key=lambda x: x.nombre, reverse=True)
        mejor_ataque, mejor_defensa = armar_equipo(equipo_ordenado_por_nombre, [], [], 0, ma)
        # Lo ordeno de nuevo asi esta ordenado alfabeticamente ascendentemente
        ataque_ordenado_por_nombre = sorted(mejor_ataque, key=lambda x: x.nombre)
        defensa_ordenada_por_nombre = sorted(mejor_defensa, key=lambda x: x.nombre)
        print(f"Case {e + 1}:")
        print("(", end="")
        for i, jugador in enumerate(ataque_ordenado_por_nombre):
            print(jugador.nombre, end="")
            if i < len(ataque_ordenado_por_nombre) - 1:
                print(", ", end="")
        print(")")
        print("(", end="")
        for i, jugador in enumerate(defensa_ordenada_por_nombre):
            print(jugador.nombre, end="")
            if i < len(defensa_ordenada_por_nombre) - 1:
                print(", ", end="")
        print(")")




if __name__ == "__main__":
    main()
