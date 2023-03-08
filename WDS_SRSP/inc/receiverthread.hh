#ifndef RECEIVERTHREAD_H
#define RECEIVERTHREAD_H

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include "serialportreader.hh"

/*!
 * \brief The ReceiverThread class
 * Klasa odpowiedzialna za zarządzanie wątkiem.
 */
class ReceiverThread : public QThread
{
    Q_OBJECT

public:
    /*!
     * \brief ReceiverThread
     * Konstruktor klasy
     * \param[in] reader - wskaźnik na klasę odpowiedzialną za odczyt danych z mikrokontrolera
     */
    ReceiverThread(SerialPortReader *reader);

signals:
    /*!
     * \brief threadError
     * Sygnał emitowany w momencie zgłoszenia błędu przez wątek
     * \param[out] errorMessage - wiadomość błędu
     */
    void threadError(QString errorMessage);

public slots:
    /*!
     * \brief onPortOpened
     * Slot odpowiedzialny za utworzenie nowego wątku
     */
    void onPortOpened();
    /*!
     * \brief _finished
     * Slot odpowiedzialny za zakończenie pracy wątku
     */
    void _finished();
    /*!
     * \brief _terminate
     * Slot odpowiedzialny za unicestwienie wątku
     */
    void _terminate();

private:
    /*!
     * \brief run
     * Funkcja odpowiedzialna za pracę wątku
     */
    void run() override;

    SerialPortReader *_portReader; //!< Wskaźnik na obiekt klasy SerialPortReader
    QWaitCondition m_cond;
};

#endif // RECEIVERTHREAD_H
