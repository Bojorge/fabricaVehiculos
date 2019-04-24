//ROUND ROBIN//
#include <pthread.h>
#include<iostream>

using namespace std;


class VehiculoTipo1{
public:
    int tiempoProcesoA(){
        return 2;
    }
    int tiempoProcesoB(){
        return 2;
    }
    int tiempoProcesoC(){
        return 4;
    }
    int tiempoProcesoD(){
        return 1;
    }
    int tiempoProcesoE(){
        return 3;
    }
    int tiempoProcesoF(){
        return 1;
    }
};

class VehiculoTipo2{
public:
    int tiempoProcesoC(){
        return 2;
    }
    int tiempoProcesoA(){
        return 1;
    }
    int tiempoProcesoB(){
        return 1;
    }
    int tiempoProcesoE(){
        return 2;
    }
    int tiempoProcesoD(){
        return 3;
    }
    int tiempoProcesoF(){
        return 1;
    }
};

class VehiculoTipo3{
public:
    int tiempoProcesoD(){
        return 1;
    }
    int tiempoProcesoE(){
        return 4;
    }
    int tiempoProcesoA(){
        return 3;
    }
    int tiempoProcesoC(){
        return 2;
    }
    int tiempoProcesoB(){
        return 1;
    }
    int tiempoProcesoF(){
        return 1;
    }
};

class VehiculoTipo4{
public:
    int tiempoProcesoB(){
        return 2;
    }
    int tiempoProcesoC(){
        return 1;
    }
    int tiempoProcesoD(){
        return 4;
    }
    int tiempoProcesoA(){
        return 3;
    }
    int tiempoProcesoF(){
        return 2;
    }
    int tiempoProcesoE(){
        return 1;
    }
};

class VehiculoTipo5{
public:
    int tiempoProcesoE(){
        return 4;
    }
    int tiempoProcesoF(){
        return 1;
    }
    int tiempoProcesoB(){
        return 2;
    }
    int tiempoProcesoC(){
        return 4;
    }
    int tiempoProcesoA(){
        return 1;
    }
    int tiempoProcesoD(){
        return 3;
    }
};

class VehiculoTipo6{
public:
    int tiempoProcesoF(){
        return 1;
    }
    int tiempoProcesoD(){
        return 1;
    }
    int tiempoProcesoC(){
        return 2;
    }
    int tiempoProcesoB(){
        return 4;
    }
    int tiempoProcesoE(){
        return 3;
    }
    int tiempoProcesoA(){
        return 4;
    }
};

int at[50], bt[50], ct[50]={0}, qt, rqi[50]={0}, c=0, st, flg=0, tm=0, noe=0, pnt=0, btm[50]={0}, tt, wt;
float att, awt;
VehiculoTipo1 vehiculoTipo1;
VehiculoTipo2 vehiculoTipo2;
VehiculoTipo3 vehiculoTipo3;
VehiculoTipo4 vehiculoTipo4;
VehiculoTipo5 vehiculoTipo5;
VehiculoTipo6 vehiculoTipo6;


void SearchStack01(int pnt,int tm){
    for(int x=pnt+1;x<6;x++){
        if(at[x]<=tm){
            rqi[noe]=x+1;
            noe++;}
    }
}

void SearchStack02(int pnt, int tm){
    for(int x=pnt+1;x<6;x++){
        //---CheckQue
        int fl=0;
        for(int y=0;y<noe;y++){
            if(rqi[y]==x+1){
                fl++;}}
        if(at[x]<=tm && fl==0 && btm[x]!=0){
            rqi[noe]=x+1;
            noe++;}
    }
}

void AddQue(int pnt){
    rqi[noe]=pnt+1;
    noe++;
}


void *roundRobin(void *vacio){
    cout<<"\n \n";
    /* cout<<"\n \n  ALGORITMO ROUND ROBIN : PARA 2 PROCESOS\n";
    cout<<"\n\t\t Aquí algunos atributos usados en el programa \n";
    cout<<"AT = Tiempo de llegada \nBT = Tiempo total de CPU \nCT = Tiempo de finalizacion \nTT = Tiempo de respuesta \nWT = Tiempo de espera \n\n";
    */
     for(int x=0;x<6;x++){
        cout<<"\nProceso "<<x+1;
        cout<<"\nTiempo de llegada en el que se inicia el proceso = ";
        cin>>at[x];
        cout << "Tiempo total de CPU que se requiere para terminar el proceso = ";
        cin>>bt[x];
        btm[x]=bt[x];}
    //cout<<"\n Ingrese el quantum : ";
    //cin>>qt;
    //Quantum qt
    qt=1;

    cout<<endl<<"Diagrama GANTT"<<endl<<at[0];
    do{
        if(flg==0){
            st=at[0];
            //---ReduceBT
            if(btm[0]<=qt){
                tm=st+btm[0];
                btm[0]=0;
                SearchStack01(pnt,tm);}
            else{
                btm[0]=btm[0]-qt;
                tm=st+qt;
                SearchStack01(pnt,tm);
                AddQue(pnt);}
        }
        else{
            pnt=rqi[0]-1;
            st=tm;
            //---DeleteQue
            for(int x=0;x<noe && noe!=1;x++){
                rqi[x]=rqi[x+1];}
            noe--;
            //---ReduceBT
            if(btm[pnt]<=qt){
                tm=st+btm[pnt];
                btm[pnt]=0;
                SearchStack02(pnt, tm);}
            else{
                btm[pnt]=btm[pnt]-qt;
                tm=st+qt;
                SearchStack02(pnt, tm);
                AddQue(pnt);}
        }
        //AssignCTvalue
        if(btm[pnt]==0){
            ct[pnt]=tm;
        }
        flg++;1;
        //cout<<"]-P"<<pnt+1<<"-["<<tm;
        cout<<" < inicia [Proceso "<<pnt+1<<"]"<<" termina > "<<tm;



    }while(noe!=0);1;
    cout<<"\n\nPROCESO \t  Tiempo de llegada \t  Tiempo total de CPU \t  Tiempo de finalizacion \t  Tiempo de respuesta \t  Tiempo de espera \n";
    for(int x=0;x<6;x++){
        tt=ct[x]-at[x];
        wt=tt-bt[x];
        cout<<"  P "<<x+1<<"                 "<<at[x]<<"                     "<<bt[x]<<"                          "<<ct[x]<<"                        "<<tt<<"                       "<<wt<<"\n";
        awt=awt+wt;
        att=att+tt;
    }
    cout<<"\n Promedio del tiempo de respuesta : "<<att/6<<"\n Promedio de espera : "<<awt/6;
}

void procesosSimultaneosPorLinea(){
    void * vacio;
    pthread_t hilo1;
    pthread_create(&hilo1, NULL,&roundRobin,vacio);
    pthread_join(hilo1, NULL);
    /*
    pthread_t hilo2;
    pthread_create(&hilo2, NULL,&roundRobin,vacio);
    pthread_join(hilo2, NULL);

    pthread_t hilo3;
    pthread_create(&hilo3, NULL,&roundRobin,vacio);
    pthread_join(hilo3, NULL);
    */
}

int main()
{

    procesosSimultaneosPorLinea();

}







