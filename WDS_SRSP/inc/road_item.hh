#ifndef ROAD_ITEM_HH
#define ROAD_ITEM_HH

#define MAX_SPEED 100
#define MIN_SPEED 10

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include "memsdata.hh"

/*!
 * \brief The RoadItem class
 * Klasa obsługująca animację obiektu drogi.
 */
class RoadItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    /*!
     * \brief RoadItem
     * Konstruktor klasy
     * \param[in] w - szerokość sceny
     */
    RoadItem(const int &w);
    /*!
     * \brief ~RoadItem
     * Destruktor klasy
     */
    ~RoadItem();
    /*!
     * \brief setSpeed
     * Funkcja odpowiedzialna za ustawienie szybkości animacji drogi
     * \param[in] speed - szybkość animacji
     */
    void setSpeed(const int &speed);
    /*!
     * \brief getSpeed
     * \return zwraca szybkość animacji drogi
     */
    int getSpeed() const;
    /*!
     * \brief speedChanged
     * Funkcja odpowiedzialna za dynamiczną zmianę prędkości animacji,
     * w zależności od odczytów z mikrokontrolera
     * \param[in] data - w parametrze przechowywane dane odpowiedzialne za poruszanie odczytane z mikrokontrolera
     */
    void speedChanged(moveData data);
    /*!
     * \brief resize
     * Funkcja realizująca zmianę wielkości obiektu
     * \param[in] w - szerokość okna symulacji
     */
    void resize(const int &w);
public slots:
    /*!
     * \brief move
     * Slot odpowiedzialny za ustawienie nowej pozycji drogi
     */
    void move();
    /*!
     * \brief startAnimation
     * Slot odpowiedzialny za uruchomienie animacji drogi
     */
    void startAnimation();
    /*!
     * \brief stopAnimation
     * Slot odpowiedzialny za zatrzymanie animacji drogi
     */
    void stopAnimation();


private:
    int _speed; //!< Prędkość animacji drogi
    QTimer *_timer; //!< Wskaźnik na obiekt klasy QTimer

    QPixmap _pixmap; //!< Obiekt przechowujący wczytany obraz
};

#endif // ROAD_ITEM_HH
