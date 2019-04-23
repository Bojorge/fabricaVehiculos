//ROUND ROBIN//
#include<iostream>
//#include"conio.h"
using namespace std;

void SearchStack01(int pnt,int tm);
void SearchStack02(int pnt, int tm);
void AddQue(int pnt);
int at[50], bt[50], ct[50]={0}, qt, rqi[50]={0}, c=0, st, flg=0, tm=0, noe=0, pnt=0, btm[50]={0}, tt, wt;
float att, awt;

int main()
{
    cout<<"ALGORITMO ROUND ROBIN : PARA 6 PROCESOS\n";
    cout<<"\n\t\t Aquí algunos atributos usados en el programa \n";
    cout<<"AT = Tiempo de llegada \nBT = Tiempo total de CPU \nCT = Tiempo de finalizacion \nTT = Tiempo de respuesta \nWT = Tiempo de espera \n\n";
    for(int x=0;x<6;x++){
        cout<<"\nProceso "<<x+1;
        cout<<"\nTiempo de llegada = ";
        cin>>at[x];
        cout << "Tiempo total de CPU = ";
        cin>>bt[x];
        btm[x]=bt[x];}
    cout<<"\n Ingrese el quantum : ";
    cin>>qt;
    //system("CLS");
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
        }//if
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
        }//else
        //AssignCTvalue
        if(btm[pnt]==0){
            ct[pnt]=tm;
        }//if
        flg++;1;
        cout<<"]-P"<<pnt+1<<"-["<<tm;
    }while(noe!=0);1;
    cout<<"\n\nPROCESO \t  Tiempo de llegada \t  Tiempo total de CPU \t  Tiempo de finalizacion \t  Tiempo de respuesta \t  Tiempo de espera \n";
    for(int x=0;x<6;x++){
        tt=ct[x]-at[x];
        wt=tt-bt[x];
        cout<<"  P "<<x+1<<"                 "<<at[x]<<"                     "<<bt[x]<<"                          "<<ct[x]<<"                        "<<tt<<"                       "<<wt<<"\n";
        awt=awt+wt;
        att=att+tt;
    }//for
    cout<<"\n Promedio de finalizacion : "<<att/5<<"\n Promedio de espera : "<<awt/5;
}//main
void SearchStack01(int pnt,int tm){
    for(int x=pnt+1;x<6;x++){
        if(at[x]<=tm){
            rqi[noe]=x+1;
            noe++;}
    }//for
}//void
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
    }//for
}//void
void AddQue(int pnt){
    rqi[noe]=pnt+1;
    noe++;
}//void

