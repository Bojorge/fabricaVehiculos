#include <iostream>
#include <gtk/gtk.h>
#include <gtk/gtkmain.h>
#include <thread>
#include <functional>
#include "Lista.h"



using namespace std;
static gboolean movimiento_mouse(GtkWidget *widget, GdkEvent *event, gpointer user_data);
static gboolean btn_press_callback(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
static void actualizacion(int a);

int linea1;
int carrolisto=NULL;
int btncarros;

GtkWidget *window;
GtkWidget *tablero, *lienzo, *caja,*barra,*texto;
GdkEvent click;


int mousex;
int mousey;
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


void roundRobin(int lineaProceso[],int carro){
    cout<<"\n \n";
    for(int i=0;i<6;i++){
        tiempoTotalAux[i]=lineaProceso[i];
        tiempoTotal[i]=tiempoTotalAux[i];
    }
    for(int i=0;i<6;i++){
        tiempoDeLlegada[i]=i+1;
    }


    quantum=1;

    cout<<endl<<"Diagrama GANTT"<<endl;
    do{
        if(flag==0){
            st=tiempoDeLlegada[0];
            //---Reduce el tiempo total
            if(tiempoTotal[0]<=quantum){
                Time=st+tiempoTotal[0];
                tiempoTotal[0]=0;
                cout<<"   [el primer proceso finalizo porque el tiempo total es menor o igual al quantum]\n   ";
                linea1=NULL;
                linea1=proceso+1;
                actualizacion(carro);
                sleep(2);
                SearchStack01(proceso,Time);
            }
            else{
                tiempoTotal[0]=tiempoTotal[0]-quantum;
                Time=st+quantum;
                cout<<"   [se ejecuto el primer proceso durante 1 quantum de un segundo aun falta por ejecutarse mas]\n   ";
                linea1=NULL;
                linea1=proceso+1;
                actualizacion(carro);
                sleep(2);
                SearchStack01(proceso,Time);
                AddQue(proceso);
            }
        }
        else{
            proceso=rqi[0]-1;
            st=Time;
            //---Borra de la cola
            for(int x=0;x<noe && noe!=1;x++){
                rqi[x]=rqi[x+1];}
            noe--;

            if(tiempoTotal[proceso]<=quantum){
                Time=st+tiempoTotal[proceso];
                tiempoTotal[proceso]=0;
                cout<<"   [el proceso "<<proceso+1<<" termino de ejecutarse porque el tiempo total es menor o igual al quantum]\n   ";
                linea1=NULL;
                linea1=proceso+1;
                actualizacion(carro);

                sleep(2);
                SearchStack02(proceso, Time);}
            else{
                tiempoTotal[proceso]=tiempoTotal[proceso]-quantum;
                Time=st+quantum;
                cout<<"   [el proceso "<<proceso+1<<" se ha ejecutado durante 1 quantum de un segundo aun falta por ejecutarse mas]\n   ";
                linea1=NULL;
                linea1=proceso+1;
                actualizacion(carro);

                sleep(2);
                SearchStack02(proceso, Time);
                AddQue(proceso);}
        }
        if(tiempoTotal[proceso]==0){
            TiempoFinal[proceso]=Time;
        }
        flag++;1;




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
    carrolisto=carro;
    actualizacion(0);
}

void *botones(void*){
    while (true){
        if (btncarros == 1) {
            roundRobin(vehiculoTipo1.linea1, 1);
            btncarros = NULL;
        }
        if (btncarros == 2) {
            roundRobin(vehiculoTipo2.linea2, 2);
            btncarros = NULL;
        }
        if (btncarros == 3) {
            roundRobin(vehiculoTipo3.linea3, 3);
            btncarros = NULL;
        }
        if (btncarros == 4) {
            roundRobin(vehiculoTipo4.linea4, 4);
            btncarros = NULL;
        }
        if (btncarros == 5) {
            roundRobin(vehiculoTipo5.linea5, 5);
            btncarros = NULL;
        }
        if (btncarros == 6) {
            roundRobin(vehiculoTipo6.linea6, 6);
            btncarros = NULL;
        }
    }
    }


void *logica(void*) {
        actualizacion(0);

}


void *grafica(void*){
        gtk_main();
};

int main(int argc,char *argv[]) {

    gtk_init(NULL, NULL);
    gdouble mx, my;
    lienzo=gtk_fixed_new();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    gtk_window_set_title(GTK_WINDOW(window), "Linea de Produccion");
    gtk_container_add(GTK_CONTAINER(window), lienzo);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "motion-notify-event", G_CALLBACK(movimiento_mouse), NULL);
    gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(btn_press_callback), NULL);
    gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 45, 193);
    gtk_widget_show_all(window);


    pthread_t t3;
    pthread_create(&t3,NULL,&grafica,NULL);


    void*result;
    pthread_t t1;
    pthread_create(&t1,NULL,&botones,NULL);
    pthread_t t2;
    pthread_create(&t2,NULL,&logica,NULL);
    pthread_join(t2, &result);
    pthread_join(t1,&result);
    pthread_join(t3,&result);
    return 0;
}


static gboolean movimiento_mouse(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    if (event->type == GDK_MOTION_NOTIFY) {

        GdkEventMotion *e = (GdkEventMotion *) event;
        mousex = (guint) e->x;
        mousey = (guint) e->y;

        gtk_widget_show_all(window);
    }
}

gboolean btn_press_callback(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {

    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        //MANEJO DE BOTONES DE LOS CARROS----------------------------------------
        printf("");
        if (mousex>6 && mousex<109 &&mousey>613){
            printf("boton 1\n");
            btncarros=1;
        }
        if (mousex>130 && mousex<234 &&mousey>613){
            printf("boton 2\n");
            btncarros=2;
        }
        if (mousex>260 && mousex<358 &&mousey>613){
            printf("boton 3\n");
            btncarros=3;
        }
        if (mousex>380 && mousex<482 &&mousey>613){
            printf("boton 4\n");
            btncarros=4;

        }
        if (mousex>508 && mousex<614 &&mousey>613){
            printf("boton 5\n");
            btncarros=5;

        }
        if (mousex>643 && mousex<742 &&mousey>613){
            printf("boton 6\n");
            btncarros=6;
        }
    }
}
void actualizacion(int a) {
    gtk_container_add(GTK_CONTAINER(lienzo), gtk_image_new_from_file("pantalla.png"));
    gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 0, 0);

    if (linea1 == 1) {
        printf("imprimiendo en la fil 1 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 45, 90+84*(a-1));
    }
    if (linea1 == 2) {
        printf("imprimiendo en la fil 2 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 123, 90+84*(a-1));
    }
    if (linea1 == 3) {
        printf("imprimiendo en la fil 3 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 200, 90+84*(a-1));
    }
    if (linea1 == 4) {
        printf("imprimiendo en la fil 4 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 263, 90+84*(a-1));
    }
    if (linea1 == 5) {
        printf("imprimiendo en la fil 5 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"), 341, 90+84*(a-1));
    }
    if (linea1 == 6) {
        printf("imprimiendo en la fil 6 \n");
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"),418, 90+84*(a-1));
    }
    if (carrolisto==1) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo1.png"), 700,72);
    }
    if (carrolisto==2) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo2.png"), 700,157);
    }
    if (carrolisto==3) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo3.png"), 700,240);
    }
    if (carrolisto==4) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo4.png"), 700,324);
    }
    if (carrolisto==5) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo5.png"), 700,407);
    }
    if (carrolisto==6) {
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("listo6.png"), 700,490);
    }


}