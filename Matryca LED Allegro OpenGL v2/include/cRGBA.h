#ifndef CRGBA_H
#define CRGBA_H

#include "cRGBA.h"

//================================================================
class cRGBA
{
    public:
        unsigned char R;
        unsigned char G;
        unsigned char B;
        unsigned char A;  // Nieu¿ywane. Jest tylko po to, aby "wyrównaæ" rozmieszczenie co 4 bajty. Zawsze mo¿emy wsadziæ tu jakieœ informacje dodatkowe. :)

         cRGBA();
        ~cRGBA();
};
//================================================================

#endif // CRGBA_H
