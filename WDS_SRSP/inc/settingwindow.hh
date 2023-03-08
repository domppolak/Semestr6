#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingWindow;
}

/*!
 * \brief Klasa SettingWindow
 * Klasa odpowiedzialna za otworzenie i skonfigurowanie nowego okna
 * odpowiedzialnego za ustawienia portu szeregowego. Pozwala także na ustawienie
 * ustawień portu szeregowego przez użytkownika.
 */
class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief SettingWindow
     * Konstruktor klasy
     * \param[in] serial_settings - wskaźnik do ustawień portu szeregowego
     * \param[in] parent - rodzic obiektu
     */
    explicit SettingWindow(QSettings *serial_settings, QWidget *parent = nullptr);

    /*!
     * \brief ~SettingWindow()
     * Destruktor klasy
     */
    ~SettingWindow();
    /*!
     * \brief update
     * Funkcja aktualizująca informacje w oknie, a także parametry ustawienia portu
     * szeregowego wybrane przez użytkoniwka
     */
    void update();
    /*!
     * \brief retranslate
     * Funkcja wywołująca ponowne przetłumaczenie okna
     */
    void retranslate();

signals:
    /*!
     * \brief connectToSerialPort
     * Sygnał emitowany w momencie wybrania połączenia z mikrokontrolerem
     */
    void connectToSerialPort();
    /*!
     * \brief disconectFromSerialPort
     * Sygnał emitowany w momencie wybrania zakończenia połączenia z mikrokontrolerem
     */
    void disconectFromSerialPort();

private slots:
    /*!
     * \brief on_serialPortComboBox_currentIndexChanged
     * Slot obsłgujący zmianę w obiekcie serialPortComboBox, pozwala na wybranie
     * portu szeregowego, a następnie wyświetla informacje o wybranym porcie.
     * \param index - indeks aktualnie wybranego pola
     */
    void on_serialPortComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_applyButton_clicked
     * Obsługuje naciśnięcie przycisku applyButton.
     * Aktualizuje ustawienia portów w _serialSettings.
     */
    void on_applyButton_clicked();
    /*!
     * \brief on_disconnectButton_clicked
     * Obsługuje naciśnięcie przycisku rozłącz (obiekt disconnectButton).
     * Wysyła sygnał disconnectFromSerialPort() obsługiwany
     * przez SerialPortReader::closeSerialPort().
     */
    void on_disconnectButton_clicked();
    /*!
     * \brief on_connectButton_clicked
     * Obsługuje naciśnięcie przycisku połącz (obiekt connectButton).
     * Wysyła sygnał connectToSerialPortReader() obsługiwany
     * przez SerialPortReader::openSerialPort().
     */
    void on_connectButton_clicked();

private:
    /*!
     * \brief updateSerialSettings
     * Funkcja aktualizująca ustawienia port szeregowego w _serialSettings.
     */
    void updateSerialSettings();
    /*!
     * \brief fillSerialPortsInfo
     * Funkcja wypełania ComboBoxa (obiekt serialPortComboBox) dostępnymi portami
     * oraz wypisuje najważniejsze informacje o porcie.
     */
    void fillSerialPortsInfo();
    /*!
     * \brief fillSerialPortParameters
     * Fuknckja wypełania ComboBoxy oppowiedzialne za dobór parametrów
     * dostępnymi ustawieniami portu szeregowego. Domyślnie zapisane ustawienia
     * portu zapisuje w ustawieniach _serialSettings.
     */
    void fillSerialPortParameters();
    /*!
     * \brief fillBaudRateParameters
     * Funkcja wypełnia ComboBoxa (obiekt baudRateComboBox) możliwymi parametrami
     * odpowiedzialnymi za ustawienie prędkości transmisji.
     */
    void fillBaudRateParameters();
    /*!
     * \brief fillWordLengthParameters
     * Funkcja wypełnia ComboBoxa (obiekt wordLengthComboBox) możliwymi parametrami
     * odpowiedzialnymi za ustawienie długości wysyłanego słowa.
     */
    void fillWordLengthParameters();
    /*!
     * \brief fillParityParameters
     * Funkcja wypełnia ComboBoxa (obiekt parityComboBox) możliwymi parametrami
     * odpowiedzialnymi za parzystość.
     */
    void fillParityParameters();
    /*!
     * \brief fillStopBitsParameters
     * Funkcja wypełnia ComboBoxa (obiekt stopBitsComboBox) możliwymi parametrami
     * odpowiedzialnymi za ustawienie bitu stopu.
     */
    void fillStopBitsParameters();
    /*!
     * \brief showPortInfo
     * Funkcja odpowiedzialna za wyświetlenie aktulanych informacji o portcie.
     * \param [in] index - indeks wybranego portu szeregowego
     */
    void showPortInfo(int index);
    /*!
     * \brief setDefaultIndexes
     * Funkcja odpowiedzialna za ustawienie domyślnych ustawień portu szeregowego
     * w _serialSettings.
     */
    void setDefaultIndexes();

    Ui::SettingWindow *_ui; //!< Interfejs okna
    QSettings *_serialSettings; //!< Wskaźnik na obiekt klasy QSettings


};

#endif // SETTINGSWINDOW_H
