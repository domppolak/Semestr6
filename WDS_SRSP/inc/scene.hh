#ifndef SCENE_HH
#define SCENE_HH

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSequentialAnimationGroup>
#include "car_item.hh"
#include "road_item.hh"
#include "obstacleCar.hh"

/*!
 * \brief The Scene class
 *  Klasa odpowiedzialna za zarządzanie całą symulacją
 *  (uruchamianie, zatrzymywanie oraz zresetowanie symulacji).
 *  Zarządza wszystkimi obiektami dodanymi do symulacji takimi jak
 *  samochód, droga, przeszkody.
 *
 */
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*!
     * \brief Scene
     * Konstruktor klasy
     * \param[in] parent - rodzic obiektu
     */
    explicit Scene(QObject *parent = nullptr);
    /*!
     * \brief ~Scene
     * Desruktor klasy
     */
    ~Scene();

    /*!
     * \brief addCar
     * Funkcja odpowiedzialna za dodanie samochodu do sceny
     * \param[in] w - szerokość okna symulacji
     * \param[in] h - wykość okna symulacji
     */
    void addCar(const int &w, const int &h);
    /*!
     * \brief addRoad
     * Funkcja odpowiedzialna za dodanie drogi do symulacji
     * \param[in] w - szerokość okna symulacji
     */
    void addRoad(const int &w);
    /*!
     * \brief addObstacles
     * Funkcja dodaje przeszkody do okna symulacji
     * \param[in] w - szerokość okna symulacji
     * \param[in] h - wysokość okna symulacji
     */
    void addObstacles(const int &w, const int &h);
    /*!
     * \brief setCarSpeed
     * Funkcja odpowiedzialna za ustawinie prędkości poruszania się samochodem
     * \param[in] speed - prędkość samochodu
     */
    void setCarSpeed(const int &speed);
    /*!
     * \brief getCarSpeed
     * \return Zwraca prędkość samochodu
     */
    int getCarSpeed() const;
    /*!
     * \brief getConstSpeedState
     * \retval true - jeśli ustawiono stałą prędkość
     * \retval false - jeśli ustawiono zmienną prędkość
     */
    bool getConstSpeedState() const;
    /*!
     * \brief getSimulationState
     * \retval true - jeśli symulacja jest uruchomiona
     * \retval false - jeśli symulacja jest zatrzymana
     */
    bool getSimulationState() const;
    /*!
     * \brief setSimulationState
     * Ustawia flagę na wartość przekazaną w argumencie funkcji
     * \param[in] state - status symulacji
     */
    void setSimulationState(const bool &state);
    /*!
     * \brief resizeSceneItems
     * Funkcja ralizująca zmianę wielkości wszystkich obiektów sceny
     * \param[in] w - wysokość okna symulacji
     * \param[in] h - szerokość okna symulacji
     */
    void resizeSceneItems(const int &w, const int &h);
signals:
    /*!
     * \brief stopSimulationItems
     * Sygnał wysyłany w momencie zatrzymania wszystkich obiektów sceny
     */
    void stopSimulationItems();
    /*!
     * \brief startSimulationItems
     * Sygnał wysyłany w momencie poruszania obiektami sceny
     */
    void startSimulationItems();
    /*!
     * \brief crashInformation
     * Sygnał wysyłany w momencie zderzenia samochodu z przeszkodą
     */
    void crashInformation();

private slots:
    /*!
     * Słot obsługujący nowootrzymane dane. Opowiada za dodanie danych do wykresów.
     * \param[in] data - dane otrzymane z mikrokontrolera
     */
    void newDataArrived(rawData data);

public slots:
    /*!
     * \brief startSimulation
     * Slot odpowiedzialny za uruchomienie symulacji
     */
    void startSimulation();
    /*!
     * \brief stopSimulation
     * Slot odpowiedzialny za zatrzymanie symulacji
     */
    void stopSimulation();
    /*!
     * \brief resetSimulation
     * Slot odpowiedzialny za zresetowanie symulacji
     * \param[in] w - szerokość okna symulacji
     * \param[in] h - wysokość okna symulacji
     */
    void resetSimulation(const int &w, const int &h);
    /*!
     * \brief onConstSpeed
     * Slot odpowiedzialny za ustawienie stałej prędkości,
     * uniemożliwia zmianę prędkości poprzez odczyt danych z mikrokontrolera
     */
    void onConstSpeed();
    /*!
     * \brief onVariableSpeed
     * Slot odpowiedzialny za ustawianie prędkośći poprzez odczytanie danych z mikrokontrolera
     */
    void onVariableSpeed();
    /*!
     * \brief carCrash
     * Funkcja zarządzająca zderzeniem samochodu z przeszkodą
     */
    void carCrash();
    /*!
     * \brief respObstacles
     * Funkcja dodaje przeszkody do sceny
     */
    void respObstacles();
    /*!
     * \brief onObstaclesON
     * Slot realizujący dodanie przeszkód do sceny w momencie otrzymania sygnału włączenia przeszkód
     */
    void onObstaclesON();
    /*!
     * \brief onObstaclesOFF
     * Slot realizujący usunięcie przeszkód ze sceny po otrzymaniu sygnału wyłączenia przeszkód
     */
    void onObstaclesOFF();

private:
    /*!
     * \brief deleteObstacles
     * Funkcja usuwająca przeszkody
     */
    void deleteObstacles();

    bool _simulationON; //!< Flaga sygnalizująca uruchomienie symulacji
    bool _constSpeed; //!< Flaga sygnalizująca czy ustawiono stałą prędkość
    bool _itemDeleted; //!< Flaga sygnalizująca czy przeszkody zostały już usunięte
    bool _obstacleON; //!< Flaga sygnalizująca czy włączono przeszkody
    int _w; //!< Szerokość okna symulacji
    int _h; //!< Wysokość okna symulacji

    CarItem *_mainCar; //!< Wskaźnik na obiekt klasy CarItem
    RoadItem *_road; //!< Wskaźnik na obiekt klasy RoadItem
    ObstacleCar *_obstacleCar; //!< Wskaźnik na obiekt klasy ObstacleCar

};


#endif // SCENE_HH
