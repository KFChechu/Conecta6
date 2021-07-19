#include "main.h"

int main()
{
    int tablero[10][15];            //Matriz que contiene el tablero de Conecta6
    int ocupados[15];               //Array con las posiciones ocupadas de cada columna
    int i, j;                       //Variables auxiliares para los bucles
    int columna=0;                  //Variable de lectura con la columna a usar del tablero
    int turno=1;                    //Variable con el turno actual. Empieza en el turno 1 y llega hasta 151(150 entradas de ficha), turno en el cual acaba la partida en empate
    int empieza;                    //Define quien empieza de forma aleatoria entre 1 y 2, 1 empieza el jugador y 2 empieza la IA
    int cargar=0;                //Variable de carga de fichero
    FILE *f;                        //Fichero de partida guardada

    f=fopen("partida_g.dat","rb");
    if(f)
    {
        do
        {
            printf("\nDesea cargar partida guardada?(1=Si 0=No): ");
            scanf("%d",&cargar);
            fflush(stdin);
        } while (cargar!=0 && cargar!=1);
        printf("\n\n");
    }

    if(cargar==1)
    {
        cargarDeFichero(f,tablero,ocupados,&turno,&empieza);
        fclose (f);

    } else {

        empieza=numAleatorio();

        if(empieza==1)
            printf("\nEmpieza el jugador\n");
        else
            printf("\nEmpieza la IA\n");


        for(i=0; i<10; i++)             //Inicializando tablero
            for(j=0; j<15; j++)
                tablero[i][j]=0;


        for(i=0; i<15; i++)             //Inicializando ocupados
            ocupados[i]=0;

    }


    do
    {
        if(columna!=0)
        printf("\nUltima jugada: %d\n",columna);

        imprimirTablero(tablero,turno);         // Saca el tablero con sus valores actuales por pantalla

        if((empieza==1&&turno%2) || (empieza==2&&turno%2==0))
            do
            {
                printf("\nIntroduzca una columna(1-15):\n");               //Lectura de teclado de columna con control
                scanf("%d",&columna);

                if(columna==100)
                {
                    f=fopen("partida_g.dat","rb");
                    guardarPartida(tablero,ocupados,empieza);
                    columna=0;
                }

                if(columna<0 || columna>15)                                  //Condicion para que la columna este entre 0 y 15, 0 finaliza el programa
                    printf("Columna no disponible.");

                if(columna>0 && columna<16)                                 //Condicion para que no se acepten columnas que ya estan completas
                    if(ocupados[columna-1]==10)
                    {
                        printf("Columna completa, seleccione otra columna:\n");
                        columna=16;
                    }
            }
            while(columna<0 || columna>15 );                        // Si el valor de columna es posible se sale del bucle

        else
        {
            columna=valueCheck(tablero,ocupados,turno)+1;
            if(ocupados[columna-1]==10)

            printf("\n");
        }

        if(columna!=0)
        {
            if((empieza==1&&turno%2) || (empieza==2&&turno%2==0))
                tablero[9-ocupados[columna-1]][columna-1]=1;
            else
                tablero[9-ocupados[columna-1]][columna-1]=2;
            ocupados[columna-1]++;
            turno++;
        }

        switch(comprobarGanador(tablero,turno))
        {
        case 0:     // El juego continua
            break;

        case 1:     // Ganan cruces
            imprimirTablero(tablero,turno);
                printf("\nGANA EL JUGADOR\n");
            columna=0;
            break;

        case 2:     // Ganan caras
            imprimirTablero(tablero,turno);
                printf("\nGANA LA IA\n");
            columna=0;
            break;

        case 3:     // Empate
            imprimirTablero(tablero,turno);
            printf("\nNo quedan casillas disponibles, el juego acaba en TABLAS\n");
            columna=0;
            break;

        }


    }
    while(columna!=0);

    return 0;
}
