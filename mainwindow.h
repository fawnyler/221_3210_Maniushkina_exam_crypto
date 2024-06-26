#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void resetGame();
    void handleCardClick(int value);
    void handleCardScored(int value);
    void checkScoredCards();

private:
    Ui::MainWindow *ui;
    bool m_isStartup = true;
    QString m_correctPin = "1234";
    QList<cardwidget*> m_cardWidgets;
    int m_score = 0;
    QList<int> m_clickedValues;

    void setupCardWidgets();
};

#endif // MAINWINDOW_H
