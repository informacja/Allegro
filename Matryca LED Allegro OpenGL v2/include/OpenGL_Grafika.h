#ifndef OPENGL_GRAFIKA_H
#define OPENGL_GRAFIKA_H

#include <iostream>

#include "cRGBA.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

using namespace std;

//================================================================

class OpenGL_Grafika
{
    private:
        int okno_szerokosc;
        int okno__wysokosc;
        int full_szerokosc;
        int full__wysokosc;

        float fSkala;
        float fObrot;
        float fZoom;
        float fLeft_Right;
        float fUp_Down;

        ALLEGRO_DISPLAY *ekran;
        ALLEGRO_EVENT_QUEUE *event_queue;

        ALLEGRO_EVENT ev;
        ALLEGRO_KEYBOARD_STATE klawiatura;  // Obs³uga klawiszy na standardowym buforze z allegro, bo kolejka ma problem z JEDNOCZENN¥ obslug¹ kilku klawiszy

        bool bPetla_grafiki_dziala;

        void Ustaw_grafike( const bool bFullScreen );
        void Ustaw_kolejke_komunikatow();

        void Pobierz_wymiary_pelnego_ekranu();
        void Przelicz_proporcje_wyswietlania( const bool bFullScreen );
        void Zmien_tryb_wyswietlania( const bool bFullScreen );
        void Sprawdz_czy_w_oknie();

        void Rysuj_kwadrat( cRGBA Led[ 16 ][ 16 ], const int x, const int y, const float fPole );

    public:
         OpenGL_Grafika( const int _szerokosc, const int _wysokosc, const bool bFullScreen );
        ~OpenGL_Grafika();

        bool Petla_dziala();
        void Analizuj_kolejke_komunikatow();

        void Rysuj_scene( cRGBA Led[ 16 ][ 16 ] );
};
//================================================================

#endif // OPENGL_GRAFIKA_H
