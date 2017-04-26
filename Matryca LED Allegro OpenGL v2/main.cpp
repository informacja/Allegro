#include <iostream>
#include <ctime>

#include "./include/OpenGL_Grafika.h"
#include "./include/cRGBA.h"

using namespace std;

//================================================================

void Wstaw_do_tablicy( int n, cRGBA Led[ 16 ][ 16 ], int x, int y )
{
    switch( n )
    {
        case 1:
        {
//            Led[ x + 1 ][ y + 0 ].R = 255;
//            Led[ x + 3 ][ y + 0 ].R = 255;
//
//            for( int i = 0; i < 5; i++ )
//            {
//                Led[ x + 2 ][ y + i ].R = 255;
//            }
//
//            Led[ x + 1 ][ y + 3  ].R = 255;
//
//            break;
            Led[ x + 1 ][ y + 1 ].R = 255;

            for( int i = 0; i < 5; i++ )
            {
                Led[ x + 2 ][ y + i ].R = 255;
            }

            Led[ x + 1 ][ y + 4 ].R = 255;
            Led[ x + 3 ][ y + 4 ].R = 255;

            break;
        }

        case 2:
        {
            for( int i = 1; i < 4; i++ )
                Led[ x + i ][ y + 0 ].R = 255;

            Led[ x + 0 ][ y + 1 ].R = 255;
            Led[ x + 4 ][ y + 1 ].R = 255;

            Led[ x + 1 ][ y + 3 ].R = 255;

            Led[ x + 2 ][ y + 2 ].R = 255;
            Led[ x + 3 ][ y + 2 ].R = 255;

            for( int i = 0; i < 5; i++ )
                Led[ x + i ][ y + 4 ].R = 255;

            break;
        }

        case 3:
        {
            for(     int i = 0; i < 5; i += 2 )
            {
                for( int j = 0; j < 4; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }
            Led[ x + 4 ][ y + 3 ].R = 255;
            Led[ x + 4 ][ y + 1 ].R = 255;

            break;
        }

        case 4:
        {
            Led[ x + 0 ][ y + 0 ].R = 255;
            Led[ x + 0 ][ y + 1 ].R = 255;

            for(     int i = 0; i < 5; i++ )
            {
                Led[ x + 3 ][ y + i ].R = 255;
            }

            for(     int i = 0; i < 5; i++ )
            {
                Led[ x + i ][ y + 2  ].R = 255;
            }

            break;
        }

        // 4

        case 5:
        {
             Led[ x + 4 ][ y + 0 ].R = 255;

            for(     int i = 0; i < 5; i += 2 )
            {
                for( int j = 0; j < 4; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }

            Led[ x + 0 ][ y + 1 ].R = 255;
            Led[ x + 4 ][ y + 3 ].R = 255;

            break;
        }

        case 6:
        {
            for(     int i = 0; i < 5; i += 2 )
            {
                for( int j = 0; j < 5; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }

            Led[ x + 0 ][ y + 1 ].R = 255;
            Led[ x + 0 ][ y + 3 ].R = 255;
            Led[ x + 4 ][ y + 3  ].R = 255;

            break;
        }

        // 7

        case 7:
        {
            for(int i = 0; i < 5; i++)
            {
                    Led[ x + i ][ y + 0 ].R = 255;
            }

            Led[ x + 4 ][ y + 1 ].R = 255;
            Led[ x + 3 ][ y + 2 ].R = 255;
            Led[ x + 2 ][ y + 3 ].R = 255;
            Led[ x + 2 ][ y + 4  ].R = 255;

            break;
        }

        case 8:
        {
            for(     int i = 0; i < 5; i += 2 )
            {
                for( int j = 0; j < 5; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }

            Led[ x + 0 ][ y + 3 ].R = 255;
            Led[ x + 4 ][ y + 3 ].R = 255;
            Led[ x + 0 ][ y + 1 ].R = 255;
            Led[ x + 4 ][ y + 1 ].R = 255;

            break;
        }

        case 9:
        {
            for(     int i = 0; i < 5; i += 2 )
            {
                for( int j = 0; j < 5; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }

            Led[ x + 0 ][ y + 1 ].R = 255;
            Led[ x + 4 ][ y + 1 ].R = 255;
            Led[ x + 4 ][ y + 3 ].R = 255;

            break;
        }

        case 0:
        {
            for(     int i = 0; i < 5; i += 4 )
            {
                for( int j = 0; j < 5; j++ )
                {
                    Led[ x + j ][ y + i ].R = 255;
                }
            }

            for(     int i = 0; i < 5; i += 4 )
            {
                for( int j = 1; j < 4; j++ )
                {
                    Led[ x + i ][ y + j ].R = 255;
                }
            }

            //Led[ x + 0 ][ y + 3 ].R = 255;
            //Led[ x + 4 ][ y + 3 ].R = 255;
            //Led[ x + 0 ][ y + 1 ].R = 255;
            //Led[ x + 4 ][ y + 1 ].R = 255;

            break;
        }


    }
}

int main()
{
    // Klasa do lepszego zarządzania grafiką.
    // Wszystkie konieczne operacje "startowe" w konstruktorze
    // Wszystkie konieczne operacje "końcowe" w destruktorze
    OpenGL_Grafika *opengl = new OpenGL_Grafika( 800, 600, false );

    cout << "Okno do debugowania programu..." << endl;

    unsigned int nLicznik( 0 );

    cRGBA Led[ 16 ][ 16 ];

    memset( Led, 32, sizeof( Led ) ); // Zerowawanie tablicy, ustawianie komórek pamięci na 32, tj. prawie czarny

    //Tak na szybko pomalowane LEDy
    /*for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 0 ].G = 255;
        Led[ x ][ 0 ].R = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 1 ].G = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 2 ].B = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 3 ].R = 255;
        Led[ x ][ 3 ].G = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 4 ].R = 255;
        Led[ x ][ 4 ].B = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 5 ].G = 255;
        Led[ x ][ 5 ].B = 255;
    }
    for( int x = 0; x < 16; x++ )
    {
        Led[ x ][ 6 ].R = 255;
        Led[ x ][ 6 ].G = 255;
        Led[ x ][ 6 ].B = 255;
    }*/

    while( opengl->Petla_dziala() )
    {
        // Operacje obliczeniowe nie związane bezposrednio z grafiką
        //
        //
        // Tu różny kod programistyczny. Zmiana kolorów LEDów, to cel jaki chcemy uzyskać. Zmieniamy wartości w tablicy, zmieniamy kolory LEDów.
        //
        //

       time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
//    cout
//        (now->tm_year + 1900) << '-'
//         << (now->tm_mon + 1) << '-'
//         <<  now->tm_mday
   cout << now->tm_hour << ":"
        << now->tm_min  << ":"
        << now->tm_sec
        << endl;

        int nMin = now->tm_min;
        int nSec = now->tm_sec;

        memset( Led, 32, sizeof( Led ) );

//        Wstaw_do_tablicy( nMin / 10, Led, 2, 9 );
//        Wstaw_do_tablicy( nMin % 10, Led, 9, 9 );
//
//        Wstaw_do_tablicy( nSec / 10, Led, 2, 2 );
//        Wstaw_do_tablicy( nSec % 10, Led, 9, 2 );

        // Rotated
        Wstaw_do_tablicy( nMin / 10, Led, 2, 2 );
        Wstaw_do_tablicy( nMin % 10, Led, 9, 2 );

        Wstaw_do_tablicy( nSec / 10, Led, 2, 9 );
        Wstaw_do_tablicy( nSec % 10, Led, 9, 9 );

        if( nLicznik % 20 == 0 )    // 50 klatek na sekunde.
        {
            opengl->Rysuj_scene( Led );

            al_flip_display(); // Zamiana buforow grafiki
        }

        nLicznik++;
        Sleep( 1 );     // Mala przerwa, zeby nie zajechac procesora

        opengl->Analizuj_kolejke_komunikatow(); // Odczyt klawiszy i "X" zamknięcie okna
    }

    delete opengl;
    opengl = NULL;

    return 0;
}
//================================================================
