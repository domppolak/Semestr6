#ifndef OBSTACLECAR_HH
#define OBSTACLECAR_HH


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

/*!
 * \brief The ObstacleCar class
 * Klasa zarządzająca obiektem samochodu stanowiącego przeszkodę.
 */
class ObstacleCar : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    /*!
     * \brief ObstacleCar
     * Konstruktor klasy
     * \param[in] w - szerokość okna symulacji
     * \param[in] h - wysokość okna symulacji
     * \param[in] speed - aktualna prędkość symulacji
     * \param[in] parent - rodzic obiektu
     */
    explicit ObstacleCar(const int &w, const int &h, const int &speed, QObject *parent = nullptr);
    /*!
     *\brief ~ObstacleCar
     * Destruktor klasy
     */
    ~ObstacleCar();
    /*!
     * \brief setSpeed
     * Funkcja ustawiająca aktualną prędkość symulacji
     * \param[in] speed - prędkość symulacji
     */
    void setSpeed(const int&speed);

signals:
    /*!
     * \brief crash
     * Sygnał wysyłany w momencie zderzenia samochodu z przeszkodą
     */
    void crash();

public slots:
    /*!
     * \brief move
     * Funkcja realizująca zmianę pozycji przeszkody
     */
    void move();
    /*!
     * \brief stopObstacles
     * Funkcja realizująca zatrzymanie symulacji ruchu przeszkody
     */
    void stopObstacles();
    /*!
     * \brief startObstacles
     * Funkcja realizująca uruchomienie symulacji ruchu przeszkody
     */
    void startObstacles();
    /*!
     * \brief resize
     * Funkcja realizująca zmianę wielkości przeszkody
     * \param[in] w - szerekość okna symulacji
     * \param[in] h - wysokość okna symulacji
     */
    void resize(const int &w, const int&h);
private:
    /*!
     * \brief setRandomPos
     * Funkcja realizująca ustawienie przeszkody w losowym miejscu
     */
    void setRandomPos();

    QTimer *_timer; //!< Wskaźnik na obiekt klasy QTimer
    QPixmap _pixmap; //!< Przechowuje informacje o wczytanym obrazie
    int _speed; //!< Aktualna prędkość symulacji
    int _w; //!< Szerokość okna symulacji
    int _h; //!< Wysokość okna symulacji

};

#endif // OBSTACLECAR_HH
