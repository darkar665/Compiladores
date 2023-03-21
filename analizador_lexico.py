import ply.lex as lex

# Diccionario de palabras reservadas

pReservada = {
    'if' : 'IF',
    'else' : 'ELSE',
    'while' : 'WHILE',
    'for' : 'FOR',
    'fun' : 'FUN',
    'true': 'TRUE',
    'false' : 'FALSE',
    'null' : 'NULL',
    'or' : 'OR',
    'and' : 'AND',
    'print' : 'PRINT',
    'return' : 'RETURN',
    'var' : 'VAR'
}

#Lista de tokens

tokens = [
    'ID',
    'NUMERO',
    'MAS',
    'MENOS'
    'MULTIPLICACION',
    'DIVISION',
    'IGUAL',
    'MAYOR_QUE',
    'MENOR_QUE',
    'MAYOR_IGUAL',
    'MENOR_IGUAL',
    'PARENTESIS_IZQ',
    'PARENTESIS_DER'   
 ] + list(pReservada.values())

#Se definen las expresiones regulares correspondientes a los tokens

t_MAS = r'\+'
t_MENOS = r'-'
t_MULTIPLICACION = r'\*'
t_DIVISION = r'/'
t_IGUAL = r'='
t_MAYOR_QUE = r'>'
t_MENOR_QUE = r'<'
t_MAYOR_IGUAL = r'>='
t_MENOR_IGUAL = r'<='
t_PARENTESIS_IZQ = r'\('
t_PARENTESIS_DER = r'\)'

#Expresion regular para ID es una letra seguido de cero o mas letras o numeros

def t_ID(t):
    r'[a-zA-Z][a-zA-Z0-9]*'
    #Verifica si es el token de una palabra reservada
    t.type = pReservada.get(t.value, 'ID')
    return t

#Expresion regular para numeros si son uno o mas digitos

def t_NUMERO(t):
    r'\d+'
    try:
        t.value = int(t.value)
    except ValueError:
        print("Valor entero muy largo %d", t.value)
        t.value = 0
    return t

#Ignora espacios en blanco y saltos de linea

t_ignore = ' \n'

#Función para detectar errores léxicos

def t_error(t):
    print("Carácter ilegal '%s'" % t.value[0])
    t.lexer.skip(1)

#Crea el analizador léxico
lexer = lex.lex()