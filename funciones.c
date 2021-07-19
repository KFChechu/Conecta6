#include "main.h"

void imprimirTablero(int tablero[10][15],int turno)  //Muestra en pantalla el tablero de juego
{
    int i,j;

    if(turno!=1)
        printf("\n");

    printf("                  CONECTA 6\n");
    if (turno!=151) printf("                  Turno: %i \n",turno);
    else            printf("                  Turno: FIN\n");
    printf("===============================================\n");    //Impresion de tablero y ocupados por pantalla
    for (i=0; i<10; i++)
    {
        printf("|");
        for(j=0; j<15; j++)
        {
            if (tablero[i][j]==0)
                printf("   ");
            if (tablero[i][j]==1)
                printf(" X ");
            if (tablero[i][j]==2)
                printf(" O ");
        }
        printf("| %d",10-i);
        printf("\n");
    }
    printf("===============================================\n");
    printf("  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n\n\n\n");
    printf("Pulse '0' para salir sin guardar o '100' para guardar y salir.\n");

}


int numAleatorio()  //Devuelve un numero aleatorio que puede ser 1 o 2
{
    int num;
    srand(time(NULL));
    num=rand()%(2)+1;
    return num;
}


int comprobarGanador(int gameMatrix[10][15], int gameTurn)  //Comprueba si algun jugador tiene 6 fichas en raya
{

    int i,j,k,pl,total[2],forceEnd=0;

//Horizontal + Vertical Check
        for (i=0; i<10&&forceEnd==0; i++)
        {
            for (j=0; j<14&&forceEnd==0; j++)
            {
                total[0]=0;
                total[1]=0;
                for (pl=1; pl<=2&&forceEnd==0; pl++)
                {
                    k=j;
                    while (gameMatrix[i][k]==pl)
                    {
                        total[pl-1]++;
                        k++;
                    }

                    if(total[0]>=6||total[1]>=6)
                    {
                        forceEnd=1;
                    }

                }
            }
        }

        for (j=0; j<15&&forceEnd==0; j++)
        {
            for (i=0; i<5&&forceEnd==0; i++)
            {
                total[0]=0;
                total[1]=0;
                for (pl=1; pl<=2&&forceEnd==0; pl++)
                {
                    k=i;
                    while (gameMatrix[k][j]==pl)
                    {
                        total[pl-1]++;
                        k++;
                    }

                    if(total[0]>=6||total[1]>=6)
                    {
                        forceEnd=1;
                    }

                }
            }
        }

//Diagonal Check
    //Check Routine - Direction 1
    for(k=5; k<10&&forceEnd==0; k++)
    {
        total[0]=0;
        total[1]=0;
        i=k;
        j=0;
        while(i>=0&&j<=14&&forceEnd==0)
        {
            switch(gameMatrix[i][j])
            {
            case 0:
                total[0]=0;
                total[1]=0;
                break;
            case 1:
                total[1]=0;
                total[0]++;
                break;
            case 2:
                total[0]=0;
                total[1]++;
                break;
            }

            if(total[0]>=6||total[1]>=6)
            {
                forceEnd=1;
            }

            i--;
            j++;
        }
    }

    for(k=1; k<9&&forceEnd==0; k++)
    {
        total[0]=0;
        total[1]=0;
        i=9;
        j=k;
        while(i>=0&&j<=14&&forceEnd==0)
        {
            switch(gameMatrix[i][j])
            {
            case 0:
                total[0]=0;
                total[1]=0;
                break;
            case 1:
                total[1]=0;
                total[0]++;
                break;
            case 2:
                total[0]=0;
                total[1]++;
                break;
            }

            if(total[0]>=6||total[1]>=6)
            {
                forceEnd=1;
            }

            i--;
            j++;
        }
    }//Check Routine - Direction 1 End
    //Check Routine - Direction 2
    for(k=0; k<5&&forceEnd==0; k++) //
    {
        total[0]=0;
        total[1]=0;
        i=k;
        j=0;
        while(i<=9&&j<=14&&forceEnd==0)
        {
            switch(gameMatrix[i][j])
            {
            case 0:
                total[0]=0;
                total[1]=0;
                break;
            case 1:
                total[1]=0;
                total[0]++;
                break;
            case 2:
                total[0]=0;
                total[1]++;
                break;
            }

            if(total[0]>=6||total[1]>=6)
            {
                forceEnd=1;
            }

            i++;
            j++;
        }
    }

    for(k=1; k<10&&forceEnd==0; k++)
    {
        i=0;
        j=k;
        total[0]=0;
        total[1]=0;
        while(i<10&&j<15&&forceEnd==0)
        {
            switch(gameMatrix[i][j])
            {
            case 0:
                total[0]=0;
                total[1]=0;
                break;
            case 1:
                total[1]=0;
                total[0]++;
                break;
            case 2:
                total[0]=0;
                total[1]++;
                break;
            }

            if(total[0]>=6||total[1]>=6)
            {
                forceEnd=1;
            }

            i++;
            j++;
        }
    }//Check Routine - Direction 2 End
//Diagonal Check End

//Returns
    if(total[0]>=6)
    {
        return 1;//Cruces ganan (jugador)
    }
    else if (total[1]>=6)
    {
        return 2;//Caras ganan (IA)
    }
    else if (gameTurn==151)
    {
        return 3;//Empate
    }
    else
    {
        return 0;//Continue game
    }
}


int valueCheck(int gameMatrix[10][15], int stackArray[15],int turn)  //Devuelve a la IA la mejor columna en la que puede poner
{

    int i,j,valueArray[15],valP0,valP1,max=0,bestMove=-1,vArray[15];

    for(i=0; i<15; i++)
    {

        valP0=maxValue(gameMatrix,1,stackArray[i],i);
        valP1=maxValue(gameMatrix,2,stackArray[i],i);
        //printf("Ciclo (i,posH=%d, sA,posV=%d), valor P0: %d valor P1: %d\n",i+1,stackArray[i],valP0,valP1);//DEBUG

        valueArray[i]=valP0;
        if(valP1>valP0)
            valueArray[i]=valP1;

    }

    /*printf("\nvalueArray: ");
    for(i=0; i<15; i++)
    {
        printf(" %d",valueArray[i]);
    }*/

    for(i=0; i<15; i++)
    {
        vArray[i]=0;
    }

    for(i=0; i<15; i++)
    {
        if(valueArray[i]>max&&stackArray[i]<10)
        {
            for(j=0; j<15; j++)
            {
                vArray[j]=0;
            }
            vArray[i]=1;
            max=valueArray[i];
        }
        else if (valueArray[i]==max&&stackArray[i]<10)
        {
            vArray[i]=1;
        }
    }

    /*printf("\nvArray: ");
    for(i=0; i<15; i++)
    {
        printf(" %d",vArray[i]);
    }*///DEBUG

    i=0;
    while(bestMove==-1)
    {
        if(vArray[i]==1)
        {
            bestMove=i;
        }
        else if (i<15)
        {
            i++;
        }
        else
        {
            i=0;
        }
    }
    if (turn!=1)
    {
        return bestMove;
    } else
    {
        return 7;
    }


}


//-------------------------------------------------------------

int maxValue(int gameMatrix[10][15], int pl, int posH, int posV) // Función auxiliar que devuelve la cadena mas larga de fichas que un jugador tiene desde una posicion
{

    int i,j,value,total[4];
    for(i=0; i<4; i++)
    {
        total[i]=0;
    }

    posH=9-posH;


    //Horizontal Check
    for(j=posV+1;j<15 && gameMatrix[posH][j]==pl; j++)
    {
        total[0]++;
    }

    for(j=posV-1;j>=0 && gameMatrix[posH][j]==pl; j--)
    {
        total[0]++;
    }

    //Vertical Check

    for(i=posH+1;i<10 && gameMatrix[i][posV]==pl; i++)
    {
        total[1]++;
    }

    //Diagonal Check 1
    i=posH+1;
    j=posV+1;
    while(i<10&&j<15 && gameMatrix[i][j]==pl)
    {
        total[2]++;
        i++;
        j++;
    }

    i=posH-1;
    j=posV-1;
    while(i>=0&&j>=0 && gameMatrix[i][j]==pl)
    {
        total[2]++;
        i--;
        j--;
    }

    //Diagonal Check 2
    i=posH+1;
    j=posV-1;
    while(i<10&&j>=0 && gameMatrix[i][j]==pl)
    {
        total[3]++;
        i++;
        j--;
    }

    i=posH-1;
    j=posV+1;
    while(i>=0&&j<15 && gameMatrix[i][j]==pl)
    {
        total[3]++;
        i--;
        j++;
    }

    value=total[0];
    for(i=1; i<4; i++)
    {
        if(value<total[i])
        {
            value=total[i];
        }
    }
    return value;

}


void cargarDeFichero(FILE *f,int tablero[10][15],int ocupados[10],int *turno,int *empieza) //Carga partida desde fichero
{
    int i,j;
    for(i=0;i<10;i++)
        {
            for(j=0;j<15;j++)
            {
                fread(&tablero[i][j],4,1,f);
            }
        }

    for(i=0;i<15;i++)
        {
            fread(&ocupados[i],4,1,f);
            *turno+=ocupados[i];
        }

    fread(&*empieza,4,1,f);
}


void guardarPartida(int tablero[10][15],int ocupados[10],int empieza) //Guarda la partida en un fichero
{
    FILE *f;
    int i,j;

    f=fopen("partida_g.dat","wb");

    for(i=0; i<10; i++)             //Inicializando tablero
    {
        for(j=0; j<15; j++)
        {
            fwrite(&tablero[i][j],4,1,f);
        }
    }

    for(i=0;i<15;i++)
    {
        fwrite(&ocupados[i],4,1,f);
    }

    fwrite(&empieza,4,1,f);

    fclose(f);
}
