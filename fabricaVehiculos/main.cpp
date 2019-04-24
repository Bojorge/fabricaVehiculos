#include <iostream>
#include <gtk/gtk.h>
#include <gtk/gtkmain.h>
#include <thread>
#include <functional>
#include "Lista.h"



using namespace std;
static gboolean movimiento_mouse(GtkWidget *widget, GdkEvent *event, gpointer user_data);

static gboolean btn_press_callback(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
Lista *linea1=new Lista();
Lista *linea2=new Lista();
Lista *linea3=new Lista();
Lista *linea4=new Lista();
Lista *linea5=new Lista();
Lista *linea6=new Lista();

int mousex;
int mousey;

GtkWidget *window;
GtkWidget *tablero, *lienzo, *caja,*barra,*texto;
GdkEvent click;

void *coneccion(void*){
    printf("creando otras conecciones");
}

void *logica(void*) {
    printf("creando logica");
}
void *grafica(void*){
    gtk_main();
};
int main(int argc,char *argv[]) {

    gtk_init(NULL, NULL);
    gdouble mx, my;

    printf("cordenaas: (%u,%u)\n", mousex, mousey);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    lienzo = gtk_fixed_new();
    caja = gtk_event_box_new();
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

    gtk_window_set_title(GTK_WINDOW(window), "Linea de Produccion");

    tablero = gtk_image_new_from_file("pantalla.png");

    gtk_container_add(GTK_CONTAINER(lienzo), gtk_image_new_from_file("pantalla.png"));



    //gtk_container_add(GTK_CONTAINER(fixed),pieza_a);


    //gtk_fixed_put(GTK_CONTAINER(caja),pieza_a,0,0);


    gtk_container_add(GTK_CONTAINER(window), lienzo);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(window), "motion-notify-event", G_CALLBACK(movimiento_mouse), NULL);
    gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(btn_press_callback), NULL);

    gtk_widget_show_all(window);


    pthread_t t3;
    pthread_create(&t3,NULL,&grafica,NULL);


    void*result;
    pthread_t t1;
    pthread_create(&t1,NULL,&coneccion,NULL);
    printf("\n iniciando coneccion");
    pthread_t t2;
    pthread_create(&t2,NULL,&logica,NULL);
    printf("\nsocket iniciadoo\n");
    pthread_join(t2, &result);
    pthread_join(t1,&result);
    pthread_join(t3,&result);


    return 0;
}


static gboolean movimiento_mouse(GtkWidget *widget, GdkEvent *event, gpointer user_data) {



    if (event->type == GDK_MOTION_NOTIFY) {
        gtk_container_add(GTK_CONTAINER(lienzo), gtk_image_new_from_file("pantalla.png"));

        GdkEventMotion *e = (GdkEventMotion *) event;
        mousex = (guint) e->x;
        mousey = (guint) e->y;
        texto=gtk_label_new("Progreso carro 1");

        barra=gtk_progress_bar_new();
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(barra),0.26);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(barra),"progreso");
        gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(barra), true);


        gtk_fixed_put(GTK_FIXED(lienzo),texto,530,85);

        gtk_fixed_put(GTK_FIXED(lienzo),barra,530,100);
        gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("usando.jpg"),45,93);

        //gtk_fixed_put(GTK_FIXED(lienzo), gtk_image_new_from_file("pantalla.png"),0,0);

        //SE PONEN LAS LETRAS DE LAS PALABRAS PRELIMINARES






        gtk_widget_show_all(window);

    }
}


gboolean btn_press_callback(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {

    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        //printf("Coordinates: (%u,%u)\n", mousex, mousey);
        //PONE LA PIEZA EN LA CASILLA INDICADA
        //MANEJO DE BOTONES DE LOS CARROS----------------------------------------
        printf("");
        if (mousex>6 && mousex<109 &&mousey>613){
            printf("boton 1 \n");
        }
        if (mousex>130 && mousex<234 &&mousey>613){
            printf("boton 2\n");
        }
        if (mousex>260 && mousex<358 &&mousey>613){
            printf("boton 3\n");
        }
        if (mousex>380 && mousex<482 &&mousey>613){
            printf("boton 4\n");
        }
        if (mousex>508 && mousex<614 &&mousey>613){
            printf("boton 5\n");
        }
        if (mousex>643 && mousex<742 &&mousey>613){
            printf("boton 6\n");
        }
    }
    

}