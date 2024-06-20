#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>

namespace Ui {
class cardwidget;
}

class cardwidget : public QWidget
{
    Q_OBJECT

public:
    explicit cardwidget(QWidget *parent = nullptr);
    ~cardwidget();

    void setNumber(int number); // Метод для установки числа на карте

signals:
    void cardClicked(int value); // Сигнал, отправляемый при нажатии на карту

private slots:
    void on_cardButton_clicked(); // Слот для обработки нажатия на карту

private:
    Ui::cardwidget *ui;
    int m_number; // Переменная для хранения числа, связанного с картой
    bool m_isOpened; // Флаг, отображающий состояние карточки (открыта или закрыта)
};

#endif // CARDWIDGET_H
