#ifndef MEMSDATA_HH
#define MEMSDATA_HH

#include "qglobal.h"

/*!
 * \brief Struktura rawData
 * Struktura przechowuje dane otrzymane z mikrokontrolera.
 *
 */

struct rawData{
   int X; //!< Wartość przyśpieszenia w osi X w [mg]
   int Y; //!< Wartość przyśpieszenia w osi Y w [mg]
   int Z; //!< Wartość przyśpieszenia w osi Z w [mg]
};

/*!
 * \brief Strukutura moveData
 * Struktura przechwouje dane o ile ma się przesunąć samochód.
 */
struct moveData{
  qreal X; //!< Wartość w osi X o ile trzeba przesunąć samochód
  qreal Y; //!< Wartosć w osi Y o ile ma zmienić się prędkość samochodu
};

#endif // MEMSDATA_HH
