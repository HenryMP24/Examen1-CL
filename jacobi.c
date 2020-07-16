#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>


int convergencia(float M[100][100],int n){
    double may;
    int ind;
    int band=1;
    double aux;
    double acum;
    
    for(int k=0;k<n;k++){
        may=abs(M[k][k]);
        ind=k;
        #pragma omp parallel for shared(n, may)
            for(int l=k+1;l<n;l++){
                if(may<abs(M[l][k])){
                    #pragma omp critical (update_may)
                    {
                        may=abs(M[l][k]);
                        ind=l;
                    }
                }            
            }
     
        if(k!=ind){
            for(int i=0;i<n+1;i++){
                aux=M[k][i];
                M[k][i]=M[ind][i];
                M[ind][i]=aux;
            }
        }
        acum=0;
        #pragma omp parallel for shared(n, acum)
            for(int j=0;j<n;j++){
                if(k!=j){
                    #pragma omp critical (update_acum)
                    {
                        acum=acum+abs(M[k][j]);
                    }
                }
            }
        if(acum>abs(M[k][k])){
            band=0;
            break;
        }
    }    
    return band;
}

int jacobi(float M[100][100],double V[100],int n,float tol){
    double error=0;
    double acum=0;
    double VA[100];
    int iter=0;
    do{
        iter++;
        for(int k=0; k<n; k++){
            acum=M[k][n];
            #pragma omp for
                for(int j=0; j<n; j++){
                    if(k!=j){
                        #pragma omp critical (update_acum)
                        {
                            acum=acum-VA[j]*M[k][j];
                        }
                    }
                
                }
            V[k]=acum/M[k][k];
        }
        
       
        #pragma omp parallel shared(n)
        {
            acum=0;
            #pragma omp for
                for(int i=0;i<n;i++){
                    error=V[i]-VA[i];
                    #pragma omp critical (update_acum)
                    {
                        acum=acum+pow(error,2);
                    }
                }
            error=sqrt(acum);
            
            
            #pragma omp for
                for(int i=0;i<n;i++){
                    VA[i]=V[i];
                }
        }
    }while(error>tol);
    return iter;
}

int main () {
    float M[100][100];
    int n;
    int band;
    double V[100];
    float tol;
    printf("ingrese el numero de ecuaciones:\n");
    scanf("%d", &n);
    printf("ingrese elementos de la matriz aumentada:\n");
    for(int i=0;i<n;i++){
        printf("fila %d\n", i+1);
        for(int j=0;j<n+1;j++){
            printf("\tcolumna %d :", j+1);
            scanf("%f", &M[i][j]);
        }
    }
    
    printf("matriz aumentada:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%.2f\t", M[i][j]);
        }printf("\n");
    }

    band=convergencia(M,n);
    if(band == 1){
        
        printf("se garantiza la convergencia\n");
        printf("matriz diagonalmente dominante:\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n+1;j++){
                printf("%.2f\t", M[i][j]);
            }printf("\n");
        }
        if(band == 1){
            printf("ingrese tolerancia: ");
            scanf("%f", &tol);
            
            printf("-->iteraciones: %d\n", jacobi(M,V,n,tol));
            printf("la solucion es:\n");
            for(int i=0;i<n;i++){
                printf("-->X%d = %.5f\n", i+1, V[i]);
            }
        }    
        
        
        
    }
    else
        printf("no se garantiza convergencia-->la matriz no es diagonalmente dominante\n");
    return 0;
}