//ROUND ROBIN//
#include <pthread.h>
#include<iostream>
#include <unistd.h>

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

    int linea1[6]={tiempoProcesoA(),tiempoProcesoB(),tiempoProcesoC(),tiempoProcesoD(),tiempoProcesoE(),tiempoProcesoF()};
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

    int linea2[6]={tiempoProcesoC(),tiempoProcesoA(),tiempoProcesoB(),tiempoProcesoE(),tiempoProcesoD(),tiempoProcesoF()};
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

    int linea3[6]={tiempoProcesoD(),tiempoProcesoE(),tiempoProcesoA(),tiempoProcesoC(),tiempoProcesoB(),tiempoProcesoF()};
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

    int linea4[6]={tiempoProcesoB(),tiempoProcesoC(),tiempoProcesoD(),tiempoProcesoA(),tiempoProcesoF(),tiempoProcesoE()};
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

    int linea5[6]={tiempoProcesoE(),tiempoProcesoF(),tiempoProcesoB(),tiempoProcesoC(),tiempoProcesoA(),tiempoProcesoD()};
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

    int linea6[6]={tiempoProcesoF(),tiempoProcesoD(),tiempoProcesoC(),tiempoProcesoB(),tiempoProcesoE(),tiempoProcesoA()};
};

int tiempoDeLlegada[6], tiempoTotalAux[6], TiempoFinal[6]={0}, quantum, rqi[50]={0}, c=0, st, flag=0, Time=0, noe=0, proceso=0, tiempoTotal[6]={0}, tiempoDeRespuesta, tiempoDeEspera;
float att, awt ;
VehiculoTipo1 vehiculoTipo1;
VehiculoTipo2 vehiculoTipo2;
VehiculoTipo3 vehiculoTipo3;
VehiculoTipo4 vehiculoTipo4;
VehiculoTipo5 vehiculoTipo5;
VehiculoTipo6 vehiculoTipo6;

void SearchStack01(int proceso,int time){
    for(int x=proceso+1;x<6;x++){
        if(tiempoDeLlegada[x]<=time){
            rqi[noe]=x+1;
            noe++;}
    }

}

void SearchStack02(int proceso, int time){
    for(int x=proceso+1;x<6;x++){
        //---CheckQue
        int fl=0;
        for(int y=0;y<noe;y++){
            if(rqi[y]==x+1){
                fl++;}}
        if(tiempoDeLlegada[x]<=time && fl==0 && tiempoTotal[x]!=0){
            rqi[noe]=x+1;
            noe++;}
    }
}

void AddQue(int proceso){
    rqi[noe]=proceso+1;
    noe++;
}


void roundRobin(int lineaProceso[]){
    cout<<"\n \n";
    /* cout<<"\n \n  ALGORITMO ROUND ROBIN : PARA 2 PROCESOS\n";
    cout<<"\n\t\t Aquí algunos atributos usados en el programa \n";
    cout<<"AT = Tiempo de llegada \nBT = Tiempo total de CPU \nCT = Tiempo de finalizacion \nTT = Tiempo de respuesta \nWT = Tiempo de espera \n\n";
    */

    for(int i=0;i<6;i++){
        tiempoTotalAux[i]=lineaProceso[i];
        tiempoTotal[i]=tiempoTotalAux[i];
    }
    for(int i=0;i<6;i++){
        tiempoDeLlegada[i]=i+1;
    }

    /*
     for(int x=0;x<6;x++){
        cout<<"\nProceso "<<x+1;
        cout<<"\nTiempo de llegada en el que se inicia el proceso = ";
        cin>>tiempoDeLlegada[x];
        cout << "Tiempo total de CPU que se requiere para terminar el proceso = ";
        cin>>tiempoTotalAux[x];
        tiempoTotal[x]=tiempoTotalAux[x];}
        */
    //cout<<"\n Ingrese el quantum : ";
    //cin>>qt;
    //Quantum qt
    quantum=1;

    cout<<endl<<"Diagrama GANTT"<<endl;
    //cout<<tiempoDeLlegada[0];
    do{
        if(flag==0){
            st=tiempoDeLlegada[0];
            //---Reduce el tiempo total
            if(tiempoTotal[0]<=quantum){
                Time=st+tiempoTotal[0];
                tiempoTotal[0]=0;
                cout<<"   [el primer proceso finalizo porque el tiempo total es menor o igual al quantum]   ";
                usleep(200000);
                SearchStack01(proceso,Time);}
            else{
                tiempoTotal[0]=tiempoTotal[0]-quantum;
                Time=st+quantum;
                cout<<"   [se ejecuto el primer proceso durante 1 quantum de un segundo aun falta por ejecutarse mas]   ";
                usleep(200000);
                SearchStack01(proceso,Time);
                AddQue(proceso);}
        }
        else{
            proceso=rqi[0]-1;
            st=Time;
            //---Borra de la cola
            for(int x=0;x<noe && noe!=1;x++){
                rqi[x]=rqi[x+1];}
            noe--;
            //cout<<" proceso "<<proceso+1<<" en el tiempo "<<Time<<" ejecutandose ";
            //usleep(200000);
            //---Reduce el tiempo total
            if(tiempoTotal[proceso]<=quantum){
                Time=st+tiempoTotal[proceso];
                tiempoTotal[proceso]=0;
                cout<<"   [el proceso "<<proceso+1<<" termino de ejecutarse porque el tiempo total es menor o igual al quantum]   ";
                usleep(200000);
                SearchStack02(proceso, Time);}
            else{
                tiempoTotal[proceso]=tiempoTotal[proceso]-quantum;
                Time=st+quantum;
                cout<<"   [el proceso "<<proceso+1<<" se ha ejecutado durante 1 quantum de un segundo aun falta por ejecutarse mas]   ";
                usleep(200000);
                SearchStack02(proceso, Time);
                AddQue(proceso);}
        }
        //Asigna el tiempo final
        if(tiempoTotal[proceso]==0){
            TiempoFinal[proceso]=Time;
        }
        flag++;1;
        //cout<<"]-P"<<pnt+1<<"-["<<tm;
        //cout<<" < inicia [Proceso "<<proceso+1<<"]"<<" termina > "<<Time;
        usleep(100000);



    }while(noe!=0);1;
    cout<<"\n\nPROCESO \t  Tiempo de llegada \t  Tiempo total de CPU \t  Tiempo de finalizacion \t  Tiempo de respuesta \t  Tiempo de espera \n";
    for(int x=0;x<6;x++){
        tiempoDeRespuesta=TiempoFinal[x]-tiempoDeLlegada[x];
        tiempoDeEspera=tiempoDeRespuesta-tiempoTotalAux[x];
        cout<<"  P "<<x+1<<"                 "<<tiempoDeLlegada[x]<<"                     "<<tiempoTotalAux[x]<<"                          "<<TiempoFinal[x]<<"                        "<<tiempoDeRespuesta<<"                       "<<tiempoDeEspera<<"\n";
        awt=awt+tiempoDeEspera;
        att=att+tiempoDeRespuesta;
    }
    cout<<"\n Promedio del tiempo de respuesta : "<<att/6<<"\n Promedio de espera : "<<awt/6;
}

/*
void procesosSimultaneosPorLinea(){
    void * vacio;
    pthread_t hilo1;
    pthread_create(&hilo1, NULL,&roundRobin,vacio);
    pthread_join(hilo1, NULL);

    pthread_t hilo2;
    pthread_create(&hilo2, NULL,&roundRobin,vacio);
    pthread_join(hilo2, NULL);

    pthread_t hilo3;
    pthread_create(&hilo3, NULL,&roundRobin,vacio);
    pthread_join(hilo3, NULL);

}
*/
int main()
{

    roundRobin(vehiculoTipo1.linea1);

}







