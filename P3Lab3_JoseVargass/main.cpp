/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: josevargas
 *
 * Created on October 30, 2020, 12:50 PM
 */

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <sstream>
#include<time.h> 

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::stringstream;


int** rellenarMatriz(int);
void liberarMatriz(int**&,int);
void liberarMatriz(double**&,int);
void printMatriz(int**,int);
void printMatriz(double**,int);
int** adjuntaMatriz(int**,int);
double** inversaMatriz(int** ,int , int );
int determinanteMatriz(int** , int );
int** submatriz(int** ,int , int, int);
double cofactor(int** , int , int , int );
int** invertir(int** , int );


/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(0)); 
    int opcion = 1;
    while(opcion){
        int size = 0;
        cout << "Ingrese el tamaño de la matriz: ";
        cin >> size;
        if(size<3){
            cout << "La matriz debe de ser minimo de 3x3" << endl;
        }else{
            //Matriz A
            int** labMatrix=NULL;
            labMatrix=rellenarMatriz(size);
            cout << "A = " << endl;
            printMatriz(labMatrix, size);
            cout << endl;
            

            //Matriz Adjunta
            int** adjunta =NULL;
            adjunta = adjuntaMatriz(labMatrix, size);
            cout << "adj(A) = " << endl;
            printMatriz(adjunta, size);
            cout << endl;

            //Determinante
            int determinante = 0;
            determinante = determinanteMatriz(labMatrix, size);
            cout << "det(A) = " << determinante << endl;
            cout << endl;
            
            
            //Matriz Inversa
            double** inversa =NULL;
            cout << "A^-1 = " << endl;
            if(determinante == 0){
                cout << "La matriz es singular, no tiene inversa" << endl;
            }else{
                inversa = inversaMatriz(adjunta, size, determinante);
                printMatriz(inversa, size);
                cout << endl;
            }
            //liberar
            liberarMatriz(labMatrix,size);
            liberarMatriz(adjunta,size);
            liberarMatriz(inversa,size);
        }
        cout << "Le gustaria continuar? Si=1/No=0: ";
        cin >> opcion;
    }
    return 0;
}

int** rellenarMatriz(int size){
    int** temporal = NULL;
    temporal = new int*[size];
    for(int i=0; i < size; i++)
        temporal[i] = new int[size];
    for(int i = 0; i< size; i++){
        for(int j = 0; j<size ; j++){
            temporal[i][j] = rand() % 19 - 9;
        }
    }
//    temporal[0][0] = 3; temporal[0][1] = -2; temporal[0][2] = 1;
//    temporal[1][0] = 5; temporal[1][1] = 6; temporal[1][2] = 2;
//    temporal[2][0] = 1; temporal[2][1] = 0; temporal[2][2] = -3;
    return temporal;
    liberarMatriz(temporal,size);
}

void liberarMatriz(int**& matrix,int size){
    if(matrix != NULL){
        for(int i = 0; i < size; i++){
            if(matrix[i] != NULL){
                delete[] matrix[i];
            }
            matrix[i] = NULL;
        }
    }
    
    if(matrix != NULL){
        delete[] matrix;
        matrix = NULL;
    }
}

void liberarMatriz(double**& matrix,int size){
    if(matrix != NULL){
        for(int i = 0; i < size; i++){
            if(matrix[i] != NULL){
                delete[] matrix[i];
            }
            matrix[i] = NULL;
        }
    }
    
    if(matrix != NULL){
        delete[] matrix;
        matrix = NULL;
    }
}



void printMatriz(int** matrix, int size){
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printMatriz(double** matrix, int size){
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}



int** adjuntaMatriz(int** matriz,int size){
    int** B = NULL;
    B = new int*[size];
    for(int i=0; i < size; i++){
        B[i] = new int[size];
    }   
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            B[i][j] = cofactor(matriz, i, j, size);
        }
    }
    
    B = invertir(B, size);
    return B;
}

double** inversaMatriz(int** matriz,int size, int det){
    double** K = NULL;
    K = new double*[size];
    for(int i=0; i < size; i++){
        K[i] = new double[size];
    } 
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            K[i][j] = (double)matriz[i][j]/det;
        }
    }
    return K;
}

int determinanteMatriz(int** matriz, int size){
    int valor = 0;
    if(size == 2){
        valor = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
        return valor;
    }else{
        for(int i = 0; i < size; i++){
            valor+=matriz[0][i]*cofactor(matriz,0,i, size);
        }
    }
    return valor;
}

double cofactor(int** matriz, int i, int j, int size){
    double calculo = 0;
    int** M = NULL;
    M = submatriz(matriz, i, j, size);
    calculo = pow(-1, (i+1) + (j+1)) * determinanteMatriz(M, size-1);
    return calculo;
    liberarMatriz(M, size);
}

int** submatriz(int** matriz,int x, int y, int size){
    int** M = NULL;
    M = new int*[size-1];
    for(int i=0; i < size-1; i++){
        M[i] = new int[size-1];
    }
    
    int minor_row, minor_col;
    for (int i = 0; i < 3; i++) {
        minor_row = i;
        if (i>x)
            minor_row--;
        for (int j = 0; j < 3; j++) {
            minor_col = j;
            if (j>y)
                minor_col--;
            if (i != x && j != y)
                M[minor_row][minor_col] = matriz[i][j];
        }
    }
    return M;
    liberarMatriz(M, size);
}

int** invertir(int** matriz, int size){
    int** temporal = NULL;
    temporal = new int*[size];
    for(int i=0; i < size; i++){
        temporal[i] = new int[size];
    }   
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            temporal[i][j] = matriz[j][i];
        }
    }
    
    return temporal;
}


