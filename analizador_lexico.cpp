#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;
const int KEY_NUM = 18; // Definir la cantidad de palabras clave
const string KEY_SET[]={ // Colección de palabras clave
        "ademas",
        "falso",
        "para",
        "fun",
        "si",
        "nulo",
        "o",
        "imprimir",
        "retornar",
        "super",
        "este",
        "verdadero",
        "var",
        "mientras",
};
map<string,int> word_num; //Número de palabras
const char* FILE_NAME="./entrada.txt";
char strBuffer[1026]; // Búfer de cadenas
string token;
int line_num=0; // El número de líneas del programa a contar, que representa el número de línea actual, que se utiliza para localizar la ubicación del error.
int char_num=0; // Cuente el número real de caracteres que no son espacios ni comentarios
int state=0; // El estado actual del programa
char getChar(char* &str) // Obtener el carácter en la posición actual del puntero de la cadena
{
    return *str++;
}
bool isDigit(char c)
{
    return (c>='0' && c<='9');
}
bool isLetter(char c)
{
    return (c>='a'&&c<='z') || (c>='A'&& c<='Z');
}
bool isPunctuation(char c) // Determinar si es un signo de puntuación
{
    return c=='+' || c=='-' || c=='*' || c=='(' || c==')' || c=='{'
    || c=='}' || c=='[' || c==']'|| c==';' || c==':' || c=='#' || c=='"' || c==',';
}
bool isKey(string str)
{
    for(int i=0;i<KEY_NUM;i++)
        if( str==KEY_SET[i] )
            return true;
    return false;
}
void error()
{
    printf("Error en la linea %d\n",line_num);
}

void process_string(char* buf) // El contenido de una línea de cadena
{
    if(state != 7) // el estado es 8, lo que significa que es un bloque de comentarios
        state = 0;
    char C=' ';
    int pos=0;
    C = getChar(buf); // Leer un personaje de pero
    while( C!='\n' && C!='\0' ) // No es un carácter de nueva línea, no es un terminador
    {
        char_num++; // Cuenta el número de caracteres
        switch(state){ // Analizar el estado actual
            case 0: // En el estado de lectura de cadena en nombre de, no ha ingresado ningún autómata
                if( isLetter(C) || C=='_' )
                {
                    state = 1; // Ingrese el estado 1
                    token = C;
                    C = getChar(buf);
                }
                else if( isDigit(C) )
                {
                    state = 2;
                    token = C;
                    C = getChar(buf);
                }
                else if( isPunctuation(C) )
                {
                    state = 0;
                    printf("< Caracter ,%c >\n",C);
                    C = getChar(buf);
                }
                else if( C==' ' ) //Espacio
                {
                    state = 0;
                    C = getChar(buf);
                }
                else if( C=='<' )
                {
                    state = 3;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='>' )
                {
                    state = 4;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='=' )
                {
                    state = 5;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='/' )
                {
                    state = 6;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='!' )
                {
                    state = 10;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='&' )
                {
                    state = 11;
                    token = C;
                    C = getChar(buf);
                }
                else if( C=='|' )
                {
                    state = 12;
                    token = C;
                    C = getChar(buf);
                }
                else{
                    error();
                    // Omitir este personaje
                    C = getChar(buf);
                }
                break;
            case 1:
                if( isLetter(C) || C=='_' || isdigit(C) )
                {
                    state=1;
                    token += C;
                    C = getChar(buf);
                }
                else{ // Al separador
                    word_num[token]++; // Cuenta el número total de cada personaje
                    if( isKey(token) )
                    {
                        cout<<"< Palabra Reservada, "<<token<<" >"<<endl;
                    }
                    else
                    {
                        cout<<"< id, "<<token<<" >"<<endl;
                    }

                    state = 0;
                }
                break;
            case 2: // Entero sin signo
                if( isDigit(C) )
                {
                    state = 2;
                    token += C;
                    C = getChar(buf);
                }
                else
                {
                    int num=stoi(token); // La cadena se convierte a int
                    cout<<"< numero, "<<num<<" >"<<endl;
                    state = 0;
                }
                break;
            case 3:
                if(C=='=')
                {
                    state = 0;
                    cout<<"< operacional, <= >"<<endl;
                    C = getChar(buf);
                }
                else
                {
                    state = 0;
                    cout<<"< operacional, < > "<<endl;
                }
                break;
            case 4:
                if(C=='=')
                {
                    state = 0;
                    cout<<"< operacional, >= >"<<endl;
                    C = getChar(buf);
                }
                else
                {
                    state = 0;
                    cout<<"< operacional, > >"<<endl;
                }
                break;
            case 5:
                if(C=='=')
                {
                    state = 0;
                    cout<<"< operacional, == >"<<endl;
                    C = getChar(buf);
                }
                else
                {
                    state = 0;
                    cout<<"< operacional, = >"<<endl;
                }
                break;
            case 6:
                if(C=='*')
                {
                    state = 7;
                    token += C;
                    C = getChar(buf);
                }
                else if(C=='/')
                {
                    state = 9;
                    token += C;
                    // Comenta esta línea de código, ignora el resto
                    cout<<"< //, - >"<<endl;
                    return;
                }
                else{ // Se puede juzgar como el signo de división
                    state = 0;
                    cout<<"< /, - >"<<endl;
                }
                break;
            case 7:
                if(C=='*')
                {
                    state = 8;
                    C = getChar(buf);
                }
                else
                {
                    state = 7;
                    C = getChar(buf);
                }
                break;
            case 8:
                if(C=='*')
                {
                    state = 8;
                    C = getChar(buf);
                }
                else if(C=='/')
                {
                    state = 0;
                    C = getChar(buf);
                }
                else{
                    state = 7;
                    C = getChar(buf);
                }
                break;
            case 9:
                    state = 9;
                    C = getChar(buf);
                break;
            case 10:
                if(C=='=')
                {
                    cout<<"< operacional, != >"<<endl;
                    state = 0;
                    C=getChar(buf);
                }
                else
                {
                    cout<<"< !, - > "<<endl;
                    state = 0;
                }
                break;
            case 11:
                if(C=='&')
                {
                    cout<<"< &&, - >"<<endl;
                    state = 0;
                    C=getChar(buf);
                }
                else{
                    cout<<"< &, - >"<<endl;
                    state=0;
                }
                break;
            case 12:
                if(C=='|')
                {
                    cout<<"< ||, - >"<<endl;
                    state=0;
                    C = getChar(buf);
                }
                else{
                    error();
                    state=0;
                    C = getChar(buf);
                }
        }
    }
}
int main() {
    FILE* file = fopen(FILE_NAME,"r"); // Abra el archivo a escanear en modo de solo lectura
    freopen("./salida.txt","w",stdout); // Redirección de salida, los datos de salida se guardarán en el archivo out.txt en el directorio raíz del Disco D
    if( file==NULL )
    {
        printf("Error al abrir el archivo");
        exit(1);
    }
    // Realice la lectura línea por línea del archivo
    while( !feof(file) )
    {
        line_num++;
        fgets(strBuffer,1024,file);
        process_string(strBuffer); // Cadena de proceso
    }
    fclose(file);

    cout<<"El número de lineas en este programa son: "<<line_num<<endl; // Imprime el número de líneas del contenido del archivo
    cout<<"El número de caracteres es: "<<char_num<<endl;
    map<string,int>::iterator iter;
    iter = word_num.begin();
    while(iter!=word_num.end())
    {
        cout<<iter->first<<' '<<iter->second<<endl;
        iter++;
    }
    return 0;
    
}