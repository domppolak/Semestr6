#ifndef PLOTWINDOW_HH
#define PLOTWINDOW_HH

#include <QDialog>
#include "qcustomplot.h"
#include "memsdata.hh"

namespace Ui {
class PlotWindow;
}

/*!
 * \brief The PlotWindow
 * Klasa odpowiedzialna za utworzenie okna, w którym są rysowane wykresy
 * na podstawie otrzmanych danych z mikrokontrolera.
 */
class PlotWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief PlotWindow
     * Konstruktor klasy
     * \param[in] parent - rodzic obiektu
     */
    explicit PlotWindow(QWidget *parent = nullptr);
    /*!
     * \brief ~PlotWindow
     * Destruktor klasy
     */
    ~PlotWindow();
    /*!
     * \brief retranslate
     * Funkcja wywołująca ponowne przetłumaczenie okna
     */
    void retranslate();

private slots:
    /*!
     * \brief new_data_received
     * Słot obsługujący nowootrzymane dane, odpowiada za dodanie danych do wykresów
     * \param[in] data - dane otrzymane z mikrokontrolera
     */
    void new_data_received(rawData data);

private:
    /*!
     * \brief MakePlot
     * Funkcja ustawia własności i wygląd wykresów
     *(tytuł, liczbę grafów, zakresy, interakcje z użytkownikiem).
     */
    void MakePlot();

    Ui::PlotWindow *ui; //!< Interfejs okna
    double _time; //!< Czas pomiaru
};

#endif // PLOTWINDOW_HH
