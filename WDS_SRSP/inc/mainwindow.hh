#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "memsdata.hh"
#include "settingwindow.hh"
#include "serialportreader.hh"
#include "plotwindow.hh"
#include "receiverthread.hh"
#include "scene.hh"

/*!
 * \brief The Language enum
 * Typ wyliczeniowy z możliwymi językami do wyboru
 */
enum Language{pl_PL, en_EN};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 * Klasa zarządzająca głównym oknem aplikacji.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow
     * Konstruktor klasy
     * \param[in] parent - rodzic obiektu
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief ~MainWindow
     * Destruktor klasy
     */
    ~MainWindow();

signals:
    /*!
     * \brief obstacleON
     * Sygnał wysyłany w momencie wybrania opcji włączenia przeszkód
     */
    void obstacleON();
    /*!
     * \brief obstacleOFF
     * Sygnał wysyłany w momencie wybrania opcji wyłączenia przeszkód
     */
    void obstacleOFF();
    /*!
     * \brief constSpeed
     * Sygnał wysyłany w momencie wybrania opcji stałej prędkości
     */
    void constSpeed();
    /*!
     * \brief variableSpeed
     * Sygnał wysyłany w momencie wybrania opcji zmiennej prędkości
     */
    void variableSpeed();

private slots:
    /*!
     * \brief on_ResetPushButton_clicked
     * Slot realizujący obsługę przycisku RESET,
     * przywraca domyślne wartości symulacji
     */
    void on_ResetPushButton_clicked();
    /*!
     * \brief on_StopPushButton_clicked
     * Slot realizujący obsługę przycisku STOP,
     * zatrzymuje symulację
     */
    void on_StopPushButton_clicked();
    /*!
     * \brief on_StartPushButton_clicked
     * Slot realizujący obsługę przycisku START,
     * uruchamia symulację
     */
    void on_StartPushButton_clicked();
    /*!
     * \brief on_FigurePushButton_clicked
     * Slot realizujący obsługę przycisku WYKRES,
     * wyświetla nowe okno z wykresami
     */
    void on_FigurePushButton_clicked();
    /*!
     * \brief on_ObstacleCheckBox_stateChanged
     * Slot realizujący obsługę wyboru stałej prędkości
     * \param[in] arg1 - status pola wyboru
     */
    void on_ObstacleCheckBox_stateChanged(int arg1);
    /*!
     * \brief on_SpeedCheckBox_stateChanged
     * Slot realizujący obsługę wyboru włączenia przeszkód
     * \param arg1 - status pola wyboru
     */
    void on_SpeedCheckBox_stateChanged(int arg1);
    /*!
     * \brief on_SpeedSpinBox_valueChanged
     * Slot ralizujący wybór wartości stałej prędkości
     * \param arg1 - prędkość wybrana przez użytkownika
     */
    void on_SpeedSpinBox_valueChanged(int arg1);
    /*!
     * \brief on_connectAction_triggered
     * Próbuje otworzyć port szeregowy, dla aktualnie zapisanych ustawień
     */
    void on_connectAction_triggered();
    /*!
     * \brief on_disconnectAction_triggered
     * Zamyka aktualnie otwartyu port szeregowy i zatrzymuje symulację
     */
    void on_disconnectAction_triggered();
    /*!
     * \brief on_settingAction_triggered
     * Otwiera okno z ustawieniami kontrolera(portu szeregowego)
     */
    void on_settingAction_triggered();
    /*!
     * \brief on_polishAction_triggered
     *  Realizuje ustawienie języka polskiego dla całej aplikacji
     */
    void on_polishAction_triggered();
    /*!
     * \brief on_englishAction_triggered
     * Realizuje ustawienie języka angielskiego dla całej aplikacji
     */
    void on_englishAction_triggered();
    /*!
     * \brief on_serial_port_opened
     * Realizuje wyświetlenie graficznej reprezentacji połączenia z mikrokonrolerem,
     * ustawia odpowiedni kolor diody sygnalizującej status połączenie
     */
    void on_serial_port_opened();
    /*!
     * \brief ErrorHandler
     * Slot realizuje wyświetlanie okna wraz z informacją o błędzie odebranym z aplikacji
     */
    void ErrorHandler(QString);
    /*!
     * \brief crashInformation
     * Slot realizujacy wyświeltenie okna z przyciskiem RESET
     * w momencie zderzenia samochodu z przeszkodą
     */
    void crashInformation();
    /*!
     * \brief greenLed
     * Funkcja realizująca zmienienie koloru diody na zielony
     */
    void greenLed();
    /*!
     * \brief redLed
     * Funkcja realizująca zmienienie koloru diody na czerwony
     */
    void redLed();



protected:
    /*!
     * \brief resizeEvent
     * Funkcja realizująca zmianę rozmiaru obiektów aplikacji
     * \param[in] event - event zmiany rozmiaru
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    /*!
     * \brief setupScene
     * Funkcja realizująca ustawienie sceny oraz połączeń
     */
    void setupScene();
    /*!
     * \brief setConnections
     * Funkcja realizująca połączenie sygnałów z odpowiednimi slotami
     */
    void setConnections();
    /*!
     * \brief setupSpeedSpinBox
     * Funkcja realizująca ustawienie obiektu SpeedSpinBox,
     * ustawienie minimalnej i maksymalnej wartości
     */
    void setupSpeedSpinBox();
    /*!
     * \brief changeLanguage
     * Funkcja ralizująca zmianę języka aplikacji
     * \param[in] lang - język aplikacji
     * \retval 0 - jeśli uda się zmienić język aplikacji
     * \retval 1 - jeśli nie uda się zmienić języka aplikacji
     */
    int changeLanguage(Language lang);
    /*!
     * \brief retranslate
     * Funkcja realizująca przetłumaczenie całej aplikacji
     */
    void retranslate();
    /*!
     * \brief resetSimulation
     * Funkcja realizująca ustawienie domyślnych wartości symulacji
     */
    void resetSimulation();

    Ui::MainWindow *ui; //!< Interfej użytkownika okna głównego
    SettingWindow *_sWindow; //!< Uchwyt do ustawień kontrolera(portu szeregowego)
    SerialPortReader *_portReader; //!< Wskaźnik na obiekt klasy SerialPortReader, odpowiedzialnej za odczyt danych z mikrokotrolera
    PlotWindow *_plotWindow; //!< Wskaźnik na obiekt klasy PlotWindow, odpowiedzialnej za utworzenie okna z wykresami
    ReceiverThread *_receiverThread; //!< Wskaźnik na obiekt klasy ReceiverThread, odpowiedzialnej za utworzenie nowego wątku
    Scene *_scene; //!< Wskaźnik na obiekt klasy Scene, odpowiedzialnej za zarządzanie sceną aplikacji
    QTranslator *_translator; //!< Wskaźnik na obiekt klasy QTranslator, odpowiedzialnej za tłumaczenia

    int h; //!< Wysokość okna symulacji
    int w; //!< Szerokość okna symulacji
};
#endif // MAINWINDOW_H
