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

    void setNumber(int number);
    void showNumber(bool show);
    void setScored(bool scored);
    bool isScored() const;

    int getNumber() const { return m_number; }

signals:
    void cardClicked(int value);
    void scoreCounted(int value);

private slots:
    void on_cardButton_clicked();

private:
    Ui::cardwidget *ui;
    int m_number;
    bool m_isOpened;
    bool m_isScored;
};

#endif // CARDWIDGET_H
