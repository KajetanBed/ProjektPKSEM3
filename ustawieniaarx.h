#ifndef USTAWIENIAARX_H
#define USTAWIENIAARX_H

#include <QDialog>
#include <vector>

namespace Ui {
class UstawieniaARX;
}

class UstawieniaARX : public QDialog
{
    Q_OBJECT

public:
    explicit UstawieniaARX(QWidget *parent = nullptr);
    ~UstawieniaARX();

    // Metody do ustawiania pól w oknie (pre-fill)
    void setWielomianA(const std::vector<double> &a);
    void setWielomianB(const std::vector<double> &b);
    void setK(int k);
    void setSzum(double stdev);
    // ... analogicznie settery dla limitów jeśli chcesz

    // Metody do pobierania danych po zatwierdzeniu
    std::vector<double> getA() const;
    std::vector<double> getB() const;
    int getK() const;
    double getSzum() const;

    // Obsługa limitów
    bool getLimityAktywne() const;
    double getUmin() const;
    double getUmax() const;

private slots:
    void on_btnZatwierdz_clicked();
    void on_btnAnuluj_clicked();

private:
private:
    Ui::UstawieniaARX *ui;
    std::vector<double> parsujWektor(QString tekst) const;

    QString wektorNaTekst(const std::vector<double> &vec);
};

#endif // USTAWIENIAARX_H
