#ifndef CAR_ITEM_HH
#define CAR_ITEM_HH

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "memsdata.hh"

/*!
 * \brief The CarItem class
 * Klasa odpowiedzialna za zarządzanie obiektem samochodu,
 * poruszaniem samochodu w prawo lub lewo na podstawie odczytanych danych z mikrokontrolera.
 */
class CarItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /*!
     * \brief CarItem
     * Konstruktor klasy
     *\param[in] w - szerekość okna
     *\param[in] h - wysokość okna
     *\param[in] parent - rodzic obiektu
     */
    explicit CarItem(const int &w, const int &h, QObject *parent = nullptr);

    /*!
     * \brief resetPosition
     * Funkcja odpowiedzialna za ustawienie początkowej pozycji samochodu
     */
    void resetPosition();
    /*!
     * \brief move
     * Funkcja odpowiedzialna za ustawienie nowej pozycji samochodu
     * \param [in] data - w parametrze przekazywane dane odpowiedzialne za przesunięcie samochod(odczytane z mikrokontrolera)
     */
    void move(moveData data);

    /*!
     * \brief resize
     * Funkcja realizuje zmianę rozmiaru samochodu
     * \param[in] w - szerekość okna
     * \param[in] h - wysokość okna
     */
    void resize(const int &w, const int &h);

signals:
    /*!
     * \brief crashCar
     * Sygnał wysyłany w momencie zderzenia samochodu z przeszkodą
     */
    void crashCar();

public slots:
    /*!
     * \brief onMoveCar
     * Slot odpowiedzlany za poruszanie samochodem
     */
    void onMoveCar();
    /*!
     * \brief onStopCar
     * Slot odpowiedzialny za zatrzymanie samochodu
     */
    void onStopCar();

private:
    bool _stopCar; //!< Flaga sygnalizująca zatrzymanie ruchu samochodu

    int _w; //!< Szerokość okna
    int _h; //!< Wysokość okna
    QPixmap _pixmap; //!< Przechowuje wczytany obraz
};

#endif // CAR_ITEM_HH
