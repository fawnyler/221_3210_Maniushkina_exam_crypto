#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up login page
    ui->editPin->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentIndex(0);

    // Set up game page
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < 9; ++i) {
        delete m_cardWidgets[i];
    }

    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString enteredPin = ui->editPin->text();
    
    if (m_isStartup) {
        if (enteredPin == m_correctPin) {
            ui->stackedWidget->setCurrentIndex(1);
            m_isStartup = false;
            for (int i = 0; i < 9; ++i) {
                m_cardWidgets[i] = new cardwidget(this);
                ui->gridLayout->addWidget(m_cardWidgets[i], i / 3, i % 3);
                int randomNumber = QRandomGenerator::global()->bounded(-100, 100);
                m_cardWidgets[i]->setNumber(randomNumber);
                connect(m_cardWidgets[i], &cardwidget::cardClicked, [=](int value) {
                    m_score += value;
                    ui->scoreLabel->setText("Очки: " + QString::number(m_score));
                });
            }
        } else {
            ui->lblLogin->setText("Неверный пинкод");
            ui->lblLogin->setStyleSheet("color:red;");
        }
    }
    
    ui->editPin->clear();
}


void MainWindow::resetGame()
{
    m_score = 0;
    ui->scoreLabel->setText("Очки: 0");

    // Regenerate random numbers for each card
    for (int i = 0; i < 9; ++i) {
        int randomNumber = QRandomGenerator::global()->bounded(-100, 100);
        m_cardWidgets[i]->setNumber(randomNumber);
    }
}






