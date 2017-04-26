#include "../include/OpenGL_Grafika.h"

//================================================================

OpenGL_Grafika::OpenGL_Grafika( const int _szerokosc, const int _wysokosc, const bool bFullScreen ) :
    okno_szerokosc( _szerokosc ),
    okno__wysokosc( _wysokosc  ),
    fObrot( 0.0f ),
    fZoom( 1.0f ),
    fLeft_Right( 0.0f ),
    fUp_Down( 0.0f )
{
    al_init();

    al_install_keyboard();

    Ustaw_grafike( bFullScreen );

    Ustaw_kolejke_komunikatow();

    bPetla_grafiki_dziala = true;
}
//================================================================

OpenGL_Grafika::~OpenGL_Grafika()
{
    al_destroy_event_queue( event_queue ); // Niszczenie kolejki komunikatów

    al_destroy_display( ekran ); // Niszczenie ekranu, czyszczenie bufora z pamiêci RAM
}
//================================================================

void OpenGL_Grafika::Ustaw_grafike( const bool bFullScreen )
{
    Pobierz_wymiary_pelnego_ekranu();

    Przelicz_proporcje_wyswietlania( bFullScreen );

    al_set_new_display_flags( ALLEGRO_WINDOWED | ALLEGRO_OPENGL );

    ekran = al_create_display( okno_szerokosc, okno__wysokosc );

    glEnable( GL_DEPTH_TEST );  // Bufor głębokości, ale o tym później

    Zmien_tryb_wyswietlania( bFullScreen );
}
//================================================================

void OpenGL_Grafika::Pobierz_wymiary_pelnego_ekranu()
{
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info( 0, &info );
    full_szerokosc = info.x2 - info.x1;
    full__wysokosc = info.y2 - info.y1;
}
//================================================================

void OpenGL_Grafika::Przelicz_proporcje_wyswietlania( const bool bFullScreen )
{
    fSkala = ( bFullScreen ? (float)full_szerokosc / full__wysokosc :
                             (float)okno_szerokosc / okno__wysokosc );
}
//================================================================

void OpenGL_Grafika::Zmien_tryb_wyswietlania( const bool bFullScreen )
{
    Przelicz_proporcje_wyswietlania( bFullScreen );

    al_toggle_display_flag( ekran , ALLEGRO_FULLSCREEN_WINDOW, bFullScreen );
}
//================================================================

void OpenGL_Grafika::Ustaw_kolejke_komunikatow()
{
    event_queue = al_create_event_queue(); // Kolejka komunikatów, na razie tylko po "X" do zamkniêcia

    al_register_event_source( event_queue, al_get_display_event_source( ekran ) ); // Podpiêcie naszej kolejki pod okno ekranu
    //al_register_event_source( event_queue, al_get_keyboard_event_source() );

    al_install_keyboard();
}
//================================================================

bool OpenGL_Grafika::Petla_dziala()
{
    return bPetla_grafiki_dziala;
}
//================================================================

void OpenGL_Grafika::Analizuj_kolejke_komunikatow()
{
    al_get_next_event( event_queue, &ev );  // Pobranie informacji z kolejki komunikatów

    if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )    // Jak "X" to zamykamy
    {
        bPetla_grafiki_dziala = false;

        return;
    }

    // Obsługa klawiszy przez "zwyczajny" bufor klawiatury
    al_get_keyboard_state( &klawiatura );

    if ( al_key_down( &klawiatura, ALLEGRO_KEY_ESCAPE ) )
    {
        bPetla_grafiki_dziala = false;

        return;
    }

    if(      al_key_down( &klawiatura, ALLEGRO_KEY_F1 ) ) // Pełny ekran
    {
        Zmien_tryb_wyswietlania( true );
    }
    else if( al_key_down( &klawiatura, ALLEGRO_KEY_F2 ) ) // Tryb okienkowy
    {
        Zmien_tryb_wyswietlania( false );
    }

    if(      al_key_down( &klawiatura, ALLEGRO_KEY_K ) )
    {
        fObrot += 0.1f;
    }
    else if( al_key_down( &klawiatura, ALLEGRO_KEY_L ) )
    {
        fObrot -= 0.1f;
    }

    if(      al_key_down( &klawiatura, ALLEGRO_KEY_P ) )
    {
        fZoom *= 1.001f;
    }
    else if( al_key_down( &klawiatura, ALLEGRO_KEY_O ) )
    {
        fZoom *= 0.999f;
    }

    if(      al_key_down( &klawiatura, ALLEGRO_KEY_UP ) )
    {
        fUp_Down += 0.001f;
    }
    else if( al_key_down( &klawiatura, ALLEGRO_KEY_DOWN ) )
    {
        fUp_Down -= 0.001f;
    }

    if(      al_key_down( &klawiatura, ALLEGRO_KEY_LEFT ) )
    {
        fLeft_Right -= 0.001f;
    }
    else if( al_key_down( &klawiatura, ALLEGRO_KEY_RIGHT ) )
    {
        fLeft_Right += 0.001f;
    }
}
//================================================================

void OpenGL_Grafika::Rysuj_scene( cRGBA Led[ 16 ][ 16 ] )
{
    glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

    glOrtho( -fSkala, fSkala, -1.0f, 1.0f, -1.0f, 1.0f );

    glPushMatrix();

        // Przesuwanie klawiszami strzałkami do testów
        glTranslatef( fLeft_Right, fUp_Down, 0.0 );

        // Skalowanie klawiszami "o" i "p" do testów
        glScalef( fZoom, fZoom, 1.0 );

        glScalef( 1.0, -1.0, 1.0 );     // odwracanie for Piotr

        // Obroty klawiszami "k" i "l" do testów
        glRotatef( fObrot, 0.0f, 0.0f, 1.0f );

        float fPole = 2.0f / ( 16.0f + 1.0f ); // Wysokość z marginesami, po pół kwadrata od góry i z dołu

        for(     int x = 0; x < 16; x++ )
        {
            for( int y = 0; y < 16; y++ )
            {
                Rysuj_kwadrat( Led, x, y, fPole );
            }
        }

    glPopMatrix();
}
//================================================================

void OpenGL_Grafika::Rysuj_kwadrat( cRGBA Led[ 16 ][ 16 ], const int x, const int y, const float fPole )
{
    cRGBA *led = &( Led[ x ][ y ] );  // Żeby było krócej

    const float fr = led->R / 255.0f; // Żeby było krócej
    const float fg = led->G / 255.0f; // Żeby było krócej
    const float fb = led->B / 255.0f; // Żeby było krócej

    const float fr1 = fr * 0.4f;
    const float fg1 = fg * 0.4f;
    const float fb1 = fb * 0.4f;

    const float fr2 = fr * 0.2f;
    const float fg2 = fg * 0.2f;
    const float fb2 = fb * 0.2f;

    const float  p  = fPole / 2.0f;
    const float p_2 = p * 1.414213562 / 2.0f;
    const float c_y = fPole * ( y + 1 ) + p - 1.0f - p;
    const float c_x = fPole * ( x + 1 ) - p - 8.0f * fPole;

    glBegin( GL_TRIANGLES );
        for(     int xx = -1; xx <= 1; xx += 2 )
        {
            for( int yy = -1; yy <= 1; yy += 2 )
            {
                glColor3f( fr, fg, fb );
                glVertex3f( c_x, c_y, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p * xx, c_y, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p_2 * xx, c_y + p_2 * yy, 0.0f );

                glColor3f( fr2, fg2, fb2 );
                glVertex3f( c_x + p * xx, c_y + p * yy, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p * xx, c_y, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p_2 * xx, c_y + p_2 * yy, 0.0f );

                // 2 ćwiartka

                glColor3f( fr, fg, fb );
                glVertex3f( c_x, c_y, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x, c_y + p * yy, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p_2 * xx, c_y + p_2 * yy, 0.0f );

                glColor3f( fr2, fg2, fb2 );
                glVertex3f( c_x + p * xx, c_y + p * yy, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x, c_y + p * yy, 0.0f );
                glColor3f( fr1, fg1, fb1 );
                glVertex3f( c_x + p_2 * xx, c_y + p_2 * yy, 0.0f );
            }
        }
    glEnd();
}
//================================================================
