# -*- coding: utf-8 -*-
"""
Editor de Spyder

Este es un archivo temporal.
"""


 
alfabetoMinus = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
     'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
alfabetoMayus = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     'M', 'N', 'Ñ', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

'''
Función codificar
Palabra: String a codificar
Avance: int posiciones que avanza en el alfabeto
'''
def Codificar(Palabra, Avance):
    Clave = ''
    AM = len(alfabetoMayus)
    Posicion = 0
    for letra in Palabra:
        for i in range(AM):
            if (i + Avance < AM):
               Posicion = i + Avance
            else:
                Posicion = abs((AM - i) - Avance)
            if letra == alfabetoMinus[i]:
                Clave = Clave + alfabetoMinus[Posicion]
            elif letra == alfabetoMayus[i]:
                Clave = Clave + alfabetoMayus[Posicion]
    return Clave


#***************************************
palabra=input("ingrese texto a cifrar:")
numero=int(input("ingrese numero a recorrer:"))
Clave = Codificar(palabra, numero)

print("----------RESULTADO--------------")
print("la palabra a cifrar es : ",palabra)
print("la palabra cifrada es : ",Clave)
