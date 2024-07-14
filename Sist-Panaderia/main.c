///GRUPO 6:Matias Mauro,Lucas Benitez y Bruno D'Elia
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tan_max 3000
#define tan_ventas 50
#define tan_min 10
typedef struct
{
    char nombre_ingrediente[20];
    float cantidad;  ///en kg o en litro segun el tipo de ingrediente
    char tipo[20]; /// "liquido" "solido"
    float costo; ///costo por kg o por litro según corresponda
} StockIngrediente;
typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} Preparacion;
typedef struct
{
    char nombre_ingrediente[20];
    float cantidad; ///puede ser en litro o en kg
} IngredienteXReceta;
typedef struct
{
    char nombre_preparacion[20];
    IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
    int cantIngredientes; ///los validos de ingredientes
} Receta;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} PreparacionVenta;
typedef struct
{
    char nombre_preparacion[20];
    float precio_venta; ///precio por unidad
} PrecioPreparacion;
typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
} PedidoPreparacion;
typedef struct
{
    int idVenta;
    PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
    int cantItems; ///los validos del arreglo de items_pedido
    float valor_total; ///valor total a pagar
    int baja;
} Venta;

///prototipados
void modificacionStock(StockIngrediente[tan_max],int);
void lecturaStock(StockIngrediente[tan_max], int*);
void lecturaRece(Receta [tan_max],int *);
void lecturaPrepa(Preparacion [tan_max],int *);
void preparacionDemanda(Preparacion [tan_max],StockIngrediente [tan_max], Receta [tan_max],int, int,int,PrecioPreparacion [tan_max],PreparacionVenta [tan_max]);
int cocinacion(StockIngrediente [tan_max],Receta [tan_max],Preparacion [tan_max],int, int,int,int, int, int,PrecioPreparacion [tan_max]);
int buscarMenor(StockIngrediente [tan_max],Receta [tan_max],PreparacionVenta [tan_max],int,int,int,int );
int restaStock(int,Receta [tan_max],StockIngrediente [tan_max],int,int,int,int );
void preciosArchivo (PrecioPreparacion [tan_max],int );
void preparadosParaLaVenta(int [tan_min],int,Preparacion [tan_max],int,PreparacionVenta [tan_max],int );
void costosFinales(float *,PrecioPreparacion [tan_max],int,PreparacionVenta [tan_max]);
void guardarVentas(Venta [tan_ventas],int );
void devolucion(Venta [tan_ventas],PreparacionVenta [tan_max],int,int );
void buscarVentas(int,Venta [tan_ventas],int);
void ventasAlPublico(PrecioPreparacion [tan_max],Venta [tan_ventas],int, int,int *,int,PreparacionVenta[tan_max] );

int main()
{
    FILE fp;

    StockIngrediente s[tan_max];
    Receta r[tan_max];
    Preparacion p[tan_max];
    PreparacionVenta prepaVenta[tan_max];
    PrecioPreparacion precios[tan_max];
    Venta ventaPublico[tan_ventas];
    int validosReceta=0;
    int validosPrepa=0;
    int validosStock=0;
    int aux=0;
    int aux2=0;
    int aux3=0;
    float aux4=0;

    float costoFinal=0;
    int factura=0;
    int cantidad=0;
    int opcionVenta=0;
    int op=-1;
    int op2=-1;
    int venta=0;
    int validosVentaPublico=0;
    float valorTotalVenta=0;
    char continuar;
    float ganancia=0;
    int op3=0;
    float  ingresoDia=0;
    int flag=0;


//PASO 1  INGRESO DE MATERIA PRIMA

    printf("LECTURA DEL STOCK DE INGREDIENTES\n");
    printf("----------------------------------\n");
    printf("---------------------------------- \n");
    lecturaStock(s,&validosStock);  ///PRIMER PASO Lectura del archivo
    printf("\n");
    printf("\n");
    printf("\n");
    system("pause");
    system("cls");

    printf("LECTURA DE LAS RECETAS \n");
    printf("----------------------------------\n");
    printf("---------------------------------- \n");
    lecturaRece(r,&validosReceta);   ///PRIMER PASO lectura de las recetas
    printf("\n");
    printf("\n");
    printf("\n");
    system("pause");
    system("cls");


    printf("LECTURA DE LAS DEMANDAS DEL DIA \n");
    printf("----------------------------------\n");
    printf("---------------------------------- \n");
    lecturaPrepa(p,&validosPrepa); ///PRIMER PASO lectura de las demandas
    printf("\n");
    printf("\n");
    printf("\n");
    system("pause");
    system("cls");


// PASO 2 COCINANDO LOS PREPARADOS

    printf("INICIA LA PREPARACION DE LAS DEMANDAS\n");
    printf("--------------------------------------\n");
    preparacionDemanda(p,s,r,validosPrepa,validosStock,validosReceta,precios,prepaVenta); ///COCINAMOS TODOS LAS DEMANDAS POSIBLES
    printf("\n");

    modificacionStock( s,validosStock);   ///ACTUALIZAMOS EL STOCK
    costosFinales(&costoFinal,precios,validosPrepa,prepaVenta);  ///CALUCULAMOS COSTOS FINALES DE PRODUCCION
    preciosArchivo(precios,validosPrepa);                        ///PRECIOS CARGADOS NORMALES



///PASO 3 VENTA AL PUBLICO
    do
    {
        printf("\n--BIENVENIDO A LA PANADERIA DEL BARRIO--\n");
        printf("Que desea realizar?\n");
        printf("Presione 1 para acceder al stock y a los precios de la demanda preparada el dia de hoy\n");
        printf("Presione 2 para ingresar una nueva venta\n");
        printf("Presione 3 para ingresar a devoluciones\n");
        printf("Presione 4 para ingresar al menu de cierre del dia\n");
        printf("Presione 0 para salir\n");
        scanf("%i",&op2);
        system("cls");




        switch(op2)
        {
        case 1:                         ///STOCKS Y PRECIOS  ////////////
        {
            do
            {
                printf("Presione 1 Para ver el costo individual de cada receta:\n");
                printf("Presione 2 Asignar un nuevo valor para la venta:\n");
                printf("presione 3 para ver los productos sin stock\n");
                printf("Presione 0 Para salir:\n");
                scanf("%i",&op);
                system("cls");
                switch (op)
                {
                case 1:


                {
                    printf("El costo de las preparaciones que pudieron realizarse es de :\n ");
                    printf("----------------\n");
                    printf("----------------\n");
                    while (aux<validosPrepa-1)
                    {
                        if(precios[aux].precio_venta>0)
                        {
                            printf("EL PRODUCTO : ");
                            puts(precios[aux].nombre_preparacion);
                            printf("\n");
                            printf("\t");
                            printf("TIENE EL VALOR ES $%.2f\n",precios[aux].precio_venta);
                            printf("------------\n");
                            printf("------------\n");
                            aux++;
                        }
                        else
                        {
                            aux++;
                        }


                    }
                    aux=0;
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                {
                    printf("A que producto desea ingresar su valor?\n");
                    printf("\n");

                    printf("--------------------------------\n");
                    do
                    {
                        while (aux<validosPrepa-1)
                        {
                            if(precios[aux].precio_venta>0)
                            {

                                printf("%i -para cambiar el  valor de: ",aux);
                                puts(precios[aux].nombre_preparacion);
                                printf("\t");
                                printf("TIENE EL VALOR  DE $%.2f\n",precios[aux].precio_venta);
                                printf("------------\n");
                                printf("------------\n");

                                aux++;
                            }
                            else
                            {
                                aux++;
                            }
                        }

                        aux=0;
                        printf("Ingrese el numero del producto al que desea cambiar el precio?\n");
                        printf("\n");
                        scanf("%i",&aux3);
                        system("cls");
                        printf("Para el producto: ");
                        puts(precios[aux3].nombre_preparacion);
                        printf("Que actualmente cuesta $%.2f\n",precios[aux3].precio_venta);
                        printf("\n");
                        printf("Ingrese el valor que tendra\n");
                        scanf("%f",&aux4);
                        precios[aux3].precio_venta=aux4;

                        printf("Quiere cambiar el valor de otro producto? s/n\n");
                        fflush(stdin);
                        scanf("%c",&continuar);
                        system("cls");
                        preciosArchivo(precios,validosPrepa);




                    }
                    while (continuar!='n');
                    printf("\n--PRECIOS ACTUALIZADOS--\n");
                    for(int i=0; i<validosPrepa; i++)
                    {
                        if(precios[i].precio_venta>0)
                        {
                            printf("\n--%s--\n",precios[i].nombre_preparacion);
                            printf("\n--$%.2f--\n",precios[i].precio_venta);

                        }
                    }
                    printf("\n");
                    printf("\n");
                    system("pause");
                    system("cls");
                    aux=0;
                    break;

                }
                case 3:
                {
                    for(int i=0; i<validosPrepa; i++)
                    {
                        if(precios[i].precio_venta==0)
                        {
                            printf("--PRODUCTO SIN STOCK--");
                            printf("\n--%s--",precios[i].nombre_preparacion);
                            printf("\nCANTIDAD :%.2f--\n",precios[i].precio_venta);
                            printf("-----------------------\n");



                        }
                    }
                    system("pause");
                    system("cls");

                    break;
                }
                default:
                {
                    printf("opcion invalida\n");
                }
                }
            }
            while(op!=0);
            system("cls");
            break;
        }
        case 2:        ///VENTAS AL PUBLICO
        {
            do
            {
                aux=0;
                while (aux<validosPrepa-1)
                {
                    if((precios[aux].precio_venta>0)&& (prepaVenta[aux].cantidad>0))
                    {
                        printf("%i -para seleccionar: ",aux);
                        puts(precios[aux].nombre_preparacion);
                        printf("\t");
                        printf("TIENE EL VALOR  DE %.2f\n",precios[aux].precio_venta);
                        printf("CONTAMOS CON UN STOCK DE %i",prepaVenta[aux].cantidad);
                        printf("------------\n");
                        printf("------------\n");

                        aux++;
                    }
                    else
                    {
                        aux++;
                    }
                }
                printf("Ingrese el numero de producto que desa\n");
                printf("\n");
                scanf("%i",&aux3);
                system("cls");
                printf("Para el producto: ");
                puts(precios[aux3].nombre_preparacion);
                printf("Que tiene un costo de %.2f\n",precios[aux3].precio_venta);
                printf("contamos con un stock de %i\n",prepaVenta[aux3].cantidad);
                printf("\nIngrese cuanto quiere llevar: \n");
                scanf("%i",&aux2);

                if(prepaVenta[aux3].cantidad>=aux2) ///si la cantidad en stock actual es mayor a lo que pide el cliente hace la cuenta
                {
                    prepaVenta[aux3].cantidad=prepaVenta[aux3].cantidad-aux2; ///cuanta que calcula cuanto queda en stock

                    ventasAlPublico(precios,ventaPublico,aux2,aux3,&validosVentaPublico,venta,prepaVenta);


                    printf("La venta %i QUEDA ASI--\n",ventaPublico[venta].idVenta);
                    printf("Producto comprado: ");
                    puts(precios[aux3].nombre_preparacion);
                    printf("Cantidad del producto comprado: %i\n", aux2);
                    ///printf("precio total de %f:\n", aux4);
                    printf("Valor final a pagar: $%.2f\n",ventaPublico[venta].valor_total);
                    guardarVentas(ventaPublico,venta);
                }
                else   ///sino decile que no hay suficiente stock
                {
                    printf("\n- No contamos con el stock suficiente -\n");
                }
                printf("Desea comprar otro producto? (s/n)\n");
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");
            }
            while(continuar=='s');
            validosVentaPublico=0;
            printf("Su total a pagar es de $%.2f",ventaPublico[venta].valor_total);
            printf("\n");
            printf("\n");
            printf("Su ticket (numero de compra) es #%i\n",venta);
            printf("--------------------------------------------\n");
            printf("\n");

            printf("\n-- Recuerde guardar su numero de tiket para poder hacer un reclamo por cualquier inconveniente --\n");
            printf("\n");
            printf("\n-- Gracias por elegirnos y confiar en la panaderia del barrio --\n");

            venta++;
            printf("\n");
            printf("\n");
            printf("\n");
            system("pause");
            system("cls");
            break;
        }
        case 3:    ///DEVOLUCION DE VENTA
        {


            devolucion(ventaPublico,prepaVenta,venta,validosPrepa);
            printf("\n");
            printf("Su devolucion fue completada\n");
            printf("\n");
            printf("\n");
            printf("\n");
            system("pause");

            break;
        }
        case 4:   ///CIERRE DEL DIA
        {
            printf("Bienvenido al menu de cierre de dia\n");
            printf("Ingrese 1  para ver el stock de ingredientes \n");
            printf("Ingrese 2  para ver el stock de preparados  para  la venta \n");
            printf("Ingrese 3  para ver el ingreso del dia y la ganancia total \n");
            printf("Ingrese 0 para salir\n");
            scanf("%i",&op3);
            system("cls");
            switch(op3)
            {
            case 1:
            {

                printf("Ahora ingresara al stock de ingredientes del final del dia\n");
                printf("----------------------------------------------------------\n");
                printf("\n");
                system("pause");
                system("cls");
                printf("STOCK AL CIERRE DEL DIA\n");
                printf("---------------------------\n");
                printf("---------------------------\n\n");

                lecturaStock(s,&validosStock);   /// bien
                printf("\n");
                printf("\n");
                printf("\n");
                system("pause");
                system("cls");
                break;
            }
            case 2:
            {
                for(int i=0; i<validosPrepa; i++)
                {
                    printf("Quedan %i del producto :  ",prepaVenta[i].cantidad);
                    puts(prepaVenta[i].nombre_preparacion);
                    printf("\n");
                    printf("--------------\n");

                }
                printf("\n");
                printf("\n");
                printf("\n");
                system("pause");
                system("cls");

                break;
            }
            case 3:
            {
                ingresoDia=0;
                for(int i=0; i<venta; i++)
                {
                    if(ventaPublico[i].baja==0)
                    {
                        ingresoDia=ingresoDia+ventaPublico[i].valor_total;
                    }
                }


                printf("El  ingreso total del dia es de $ %.2f \n",ingresoDia);
                printf("------------------------------------------------------\n");
                printf("\n");
                printf("\n");

                ganancia=ingresoDia-costoFinal;
                if (ganancia>=0)
                {
                    printf("La ganancia del dia es  de $%.2f ,siendo un ingreso total de $%.2f y un costo de preparacion de $%.2f\n",ganancia,ingresoDia,costoFinal);
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                }
                else
                {
                    printf("La perdida del dia es  de $%.2f ,siendo un ingreso total de $%.2f y un costo de preparacion de $%.2f\n",ganancia,ingresoDia,costoFinal);
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("\n");
                printf("\n");
                printf("\n");
                system("pause");
                system("cls");

                break;
            }



            default:
            {
                printf("Opcion invalida\n");
            }
            }

        }
        }
    }
    while (op2!=0);

    system("cls");
    printf("\t \t \t  Gracias por utilizar el servicio de panaderia digital\n");
    printf("\n");
    printf("\t \t \t \t\tCelebra el chocolate\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    return 0;
}


void modificacionStock(StockIngrediente s[tan_max],int  validosS)
{
    int h=0;
    int j=0;
    FILE* fp;
    fp=fopen("stockingredientes.bin","wb");

    if(fp!=NULL)
    {

        while(h<validosS-1)
        {

            fwrite(&s[h],sizeof(StockIngrediente),1,fp);
            h++;
        }
        fclose(fp);
    }
    else
    {
        printf("no se abrio el archivo");

    }
    printf(" STOCK ACTUALIZADO:\n");
    printf("-----------------------\n");
    printf("-----------------------\n");
    while( j<h-1)
    {
        printf("nombre ingrediente: %s \n", s[j].nombre_ingrediente);
        printf("cantidad de este: %.2f \n", s[j].cantidad);
        printf("tipo: %s \n", s[j].tipo);
        printf("costo: %.2f \n", s[j].costo);
        printf("-----------\n");
        printf("\n");
        j++;
    }
    printf("-----------------------\n");
    printf("-----------------------\n");
    system("pause");
    system("cls");
}

///lectura y pasaje de datos
void lecturaStock(StockIngrediente s[tan_max], int *validos)
{
    FILE *fp;
    int j=0;
    int i=*validos;


    fp=fopen("stockingredientes.bin","rb");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fread(&s[i],sizeof(StockIngrediente),1,fp);
            i++;
        }
    }
    else
    {
        printf("no se abrio el archivo");

    }
    *validos=i-1;


    while( j<i-1)
    {
        printf("nombre ingrediente: %s \n", s[j].nombre_ingrediente);
        printf("cantidad de este: %.2f \n", s[j].cantidad);
        printf("tipo: %s \n", s[j].tipo);
        printf("-----------\n");
        printf("\n");
        j++;
    }




}
void lecturaRece(Receta r[tan_max],int *validos)
{
    FILE *fp;
    int i=*validos;
    int j=0;
    fp=fopen("recetas.bin","rb");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fread(&r[i],sizeof(Receta),1,fp);
            i++;
        }
    }
    else
    {
        printf("error");
    }
    *validos=i-1;
    for(int c=0; c<i-1; c++)
    {
        printf("nombre: %s\n", r[c].nombre_preparacion);
        for(int j=0; j< r[c].cantIngredientes; j++)
        {
            printf("nombre ingre: %s\n", r[c].ingredientes[j].nombre_ingrediente);
            printf("cantidad: %.2f\n", r[c].ingredientes[j].cantidad);

        }
        printf("-------------\n");
        printf("-------------\n");
        printf("\n");

    }

}
void lecturaPrepa(Preparacion p[tan_max],int *validos)
{
    FILE *fp;
    int i=*validos;
    int j=0;
    fp=fopen("demanda.bin","rb");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fread(&p[i],sizeof(Preparacion),1,fp);
            i++;
        }
        fclose(fp);

        *validos=i-1;
    }
    else
    {
        printf("error");
    }

    while(j<i-1)
    {
        printf("nombre: %s\n", p[j].nombre_preparacion);
        printf("cantidad: %i\n", p[j].cantidad);
        printf("-------------\n");
        printf("-------------\n");
        printf("\n");

        j++;
    }

}

///paso 2.1 preparazao

void preparacionDemanda(Preparacion p[tan_max],StockIngrediente s[tan_max], Receta r[tan_max],int validosD, int validosS,int validosR,PrecioPreparacion v[tan_max],PreparacionVenta prepaVenta[tan_max])
{
    int i=0;
    int j=0;
    int e=0;
    int h=0;
    int pedidos[tan_min];
    int validosVenta=0;
    int validosPedidos=0;

    while(e<validosD)
    {
        if(strcmpi(p[j].nombre_preparacion,r[i].nombre_preparacion)==0)///mientras la demanda sea igual a la receta entra
        {


            pedidos[validosPedidos]=cocinacion(s,r,p,j,i,validosS,validosD,e,validosR,v);


            e++;
            j++;
            i=0;
            validosPedidos++;
        }
        else
        {
            i++;
        }
    }
    for(int i=0; i<validosPedidos; i++)
    {

        preparadosParaLaVenta(pedidos,i,p,validosD,prepaVenta,validosVenta); ///
        validosVenta++;
    }

}

int cocinacion(StockIngrediente s[tan_max],Receta r[tan_max],Preparacion p[tan_max],int j, int i,int validosS,int validosD, int demanda, int validosR,PrecioPreparacion v[tan_max])
{

    int e=0;
    int h=0;
    int validosPedidosFinales=0;
    int c=0;
    int x=0;
    int z=0;
    int muetraS=0;
    float pedidos=0;
    int elMenor=0;
    int pedidosFinales[tan_min];
    float huevo=0;
    float canela=0;
    float valorFinal=0;

    printf ("PREPARACION DE LA DEMANDA NUMERO %i\n",demanda+1);
    printf("\n");
    printf("se deben hacer %i unidades de la receta   :",p[demanda].cantidad);
    puts(p[demanda].nombre_preparacion);
    printf("\n ");

    while(e<r[i].cantIngredientes)                                                           ///cantidad de ingredientes necesarios
    {
        while(x<r[i].cantIngredientes)
        {
            if(strcmpi(r[i].ingredientes[z].nombre_ingrediente,s[h].nombre_ingrediente)==0)
            {
                pedidosFinales[validosPedidosFinales]=buscarMenor(s,r,p,i,z,h,demanda);
                validosPedidosFinales++;
                x++;
                z++;
            }
            else
            {
                h++;
            }
            if(h==validosS)
            {
                h=0;
            }
        }

        for(int i=0; i<validosPedidosFinales; i++)///para i que vale 0 i es menor a pedidosFinales
        {
            if(pedidosFinales[i]!=0)
            {
                if (elMenor==0)  ///como menor siempre vale 0 entra aca
                {
                    elMenor=pedidosFinales[i];	///se hace el cambio osea toma la pos 0 como la menor
                }
                else if (elMenor>pedidosFinales[i])///  si el menor es mayor a la siguiente pos se hace el cambio
                {
                    elMenor=pedidosFinales[i];   ///cambio xd
                }
            }
            else
            {
                elMenor=pedidosFinales[i];
                i=validosPedidosFinales;
            }
        }
        if(strcmpi(r[i].ingredientes[e].nombre_ingrediente,s[h].nombre_ingrediente)==0)///si harina es igual a harina
        {
            printf("Hay %.2f de %s en stock ",s[h].cantidad,r[i].ingredientes[e].nombre_ingrediente);
            printf("\n");



            pedidos=restaStock(elMenor,r,s,c,i,e,h);

            if (elMenor!=0)
            {
                canela=s[h].costo*r[i].ingredientes[e].cantidad; //VALOOR POR UNIDAD
                valorFinal=valorFinal+canela;
                huevo=elMenor*r[i].ingredientes[e].cantidad;                     //VOLVERLO PUNTERO PARA HACER EL PASAJE
            }
            printf(" Tras usar la cantidad necesaria para la receta : %.2f  de  \n",huevo);
            puts(r[i].ingredientes[e].nombre_ingrediente);
            printf(" AHORA Quedan %.2f de %s \n",s[h].cantidad,r[i].ingredientes[e].nombre_ingrediente);
            printf("\n");
            e++;
            c=0;
        }
        else
        {
            h++;
        }

        if(h==validosS)
        {
            h=0;
        }
    }
    pedidos=pedidos/r[i].cantIngredientes;
    printf("Termino la receta de  ");
    puts(p[demanda].nombre_preparacion);
    printf("-------------------------\n");
    system("pause");
    system("cls");
    printf("Se han podido realizar un total de %i de pedidos de ",elMenor);
    puts(p[demanda].nombre_preparacion);
    printf(" \n");


    if (valorFinal!=0)
    {
        printf("Cada unidad tiene un costo de %.2f\n",valorFinal);
        printf(" \n");
    }
    strcpy (v[demanda].nombre_preparacion,p[demanda].nombre_preparacion); ///asignacion de precios
    v[demanda].precio_venta=valorFinal;                                   ///
    printf("\n");
    printf("\n");
    system("pause");
    system("cls");


    return elMenor;
}

int buscarMenor(StockIngrediente stock[tan_max],Receta rece[tan_max],PreparacionVenta p[tan_max],int i,int z,int h,int demanda)
{
    float cantStock=stock[h].cantidad;

    float cantRece=rece[i].ingredientes[z].cantidad;
    int c=0;
    int pedidos=0;
    while (c<p[demanda].cantidad)////cantidad de veces que se pide una receta
    {
        if(cantStock>cantRece)//para ver si hay suficiente stock
        {
            cantStock=cantStock - cantRece;
            c++;
        }
        else
        {
            pedidos=c;
            c=p[demanda].cantidad;
        }
        if(cantStock>=cantRece)
        {
            pedidos++;  ///cuando hay stock o el stock es igual
        }
    }

    return pedidos;
}
int restaStock(int elMenor,Receta rece[tan_max],StockIngrediente stock[tan_max],int c,int i,int e,int h)
{
    int pedidos=0;
    while (c<elMenor)////cantidad de veces que se pide una receta
    {
        if(stock[h].cantidad >= rece[i].ingredientes[e].cantidad)//para ver si hay suficiente stock
        {
            stock[h].cantidad=stock[h].cantidad - rece[i].ingredientes[e].cantidad;
            c++;
        }
        else
        {
            c=elMenor;
        }
        pedidos++;
    }

    return pedidos;
}
void preciosArchivo (PrecioPreparacion precios[tan_max],int validosPrepa)
{
    int aux=0;
    FILE *fp;
    fp=fopen("precios.bin","wb");
    if (fopen!=NULL)
    {
        while (aux<validosPrepa)
        {
            fwrite(&precios[aux],sizeof(PrecioPreparacion),1,fp);
            aux++;
        }
        fclose(fp);
    }
    else
    {
        printf("Ocurrio un error\n");
    }
}
void preparadosParaLaVenta(int pedidos[tan_min],int i,Preparacion p[tan_max],int validosD,PreparacionVenta prepaVenta[tan_max],int validosVenta)
{


    prepaVenta[i].cantidad=pedidos[i];



    strcpy(prepaVenta[i].nombre_preparacion,p[i].nombre_preparacion);
    FILE *fp;
    fp=fopen("stockventa.bin","ab");
    if(fp!=NULL)
    {
        fwrite(&prepaVenta[i],sizeof(PreparacionVenta),1,fp);

        fclose(fp);

    }
    else
    {
        printf("hubo un error");
    }


}
void costosFinales(float *costoFinal,PrecioPreparacion precios[tan_max],int validosPrepa,PreparacionVenta prepaVenta[tan_max])
{
    float preciosFinales=0;
    for(int i=0; i<validosPrepa; i++)
    {
        preciosFinales=(prepaVenta[i].cantidad)*(precios[i].precio_venta);
        *costoFinal=*costoFinal+preciosFinales;
    }
}
void ventasAlPublico(PrecioPreparacion precios[tan_max],Venta ventaPublico[tan_ventas],int aux2, int aux3,int *validosVentasPublico,int ventaNum,PreparacionVenta prepaVenta[tan_max])

{

    strcpy(ventaPublico[ventaNum].items_pedido[*validosVentasPublico].nombre_preparacion,precios[aux3].nombre_preparacion); /// copia los nombres
    ventaPublico[ventaNum].items_pedido[*validosVentasPublico].cantidad=aux2;///se copia la cantidad productos que quiere el usuario
    ventaPublico[ventaNum].cantItems=(*validosVentasPublico); ///cantidad de productos que lleva
    (*validosVentasPublico)++;
    ventaPublico[ventaNum].valor_total=ventaPublico[ventaNum].valor_total + (precios[aux3].precio_venta)*aux2;; ///cuenta para saber el precio
    ventaPublico[ventaNum].idVenta=ventaNum;
    ventaPublico[ventaNum].baja=0;
}
void guardarVentas(Venta ventaPublico[tan_ventas],int ventaNum)
{
    FILE *fp=fopen("ventas.bin","wb");
    if(fp!=NULL)
    {
        fwrite(&ventaPublico[ventaNum],sizeof(Venta),1,fp);

        fclose(fp);
    }
    else
    {
        printf("\n-----error-----\n");
    }
}
void devolucion(Venta ventaPublico[tan_ventas],PreparacionVenta prepaVenta[tan_max],int venta,int validosPrepa)
{

    int numeroCompra=0;
    int i=0;
    int z=0;
    int j=0;
    int numValidos=0;
    printf("~~Ingrese su tiket para poder devolver los productos~~\n");
    scanf("%i",&numeroCompra);

    numValidos=ventaPublico[numeroCompra].cantItems;

    buscarVentas(numeroCompra,ventaPublico,venta);

}

void buscarVentas(int i,Venta ventaPublico[tan_ventas],int venta)
{
    FILE *fp=fopen("ventas.bin","r+b");
    if(fp!=NULL)
    {
        fseek(fp,sizeof(ventaPublico)*(i),SEEK_SET);
        ventaPublico[i].baja=1;
        fwrite(&ventaPublico[i],sizeof(Venta),1,fp);
        fclose(fp);
    }
    else
    {
        printf("error");
    }

}
