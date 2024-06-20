#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up login page
    ui->editPin->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentIndex(0);

    for (int i = 0; i < 9; ++i) {
        m_cardWidgets.append(new cardwidget(this));
        ui->gridLayout->addWidget(m_cardWidgets[i], i / 3, i % 3);
        int randomNumber = QRandomGenerator::global()->bounded(-100, 100);
        m_cardWidgets[i]->setNumber(randomNumber);
        m_cardWidgets[i]->showNumber(false);

        connect(m_cardWidgets[i], &cardwidget::cardClicked, this, &MainWindow::handleCardClick);
        connect(m_cardWidgets[i], &cardwidget::scoreCounted, this, &MainWindow::handleCardScored);
    }

    // Set up game page
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
}

MainWindow::~MainWindow()
{
    qDeleteAll(m_cardWidgets);
    m_cardWidgets.clear();

    delete ui;
}

void MainWindow::setupCardWidgets()
{
    for (int i = 0; i < 9; ++i) {
        m_cardWidgets.append(new cardwidget(this));
        ui->gridLayout->addWidget(m_cardWidgets[i], i / 3, i % 3);
        int randomNumber = QRandomGenerator::global()->bounded(-100, 100);
        m_cardWidgets[i]->setNumber(randomNumber);
        m_cardWidgets[i]->showNumber(false);

        connect(m_cardWidgets[i], &cardwidget::cardClicked, this, &MainWindow::handleCardClick);
        connect(m_cardWidgets[i], &cardwidget::scoreCounted, this, &MainWindow::handleCardScored);
    }
}

void MainWindow::resetGame()
{
    m_score = 0;
    ui->scoreLabel->setText("Очки: 0");
    m_clickedValues.clear();

    for (cardwidget *widget : m_cardWidgets) {
        int randomNumber = QRandomGenerator::global()->bounded(-100, 100);
        widget->setNumber(randomNumber);
        widget->showNumber(false);
        widget->setScored(false);
    }
}

void MainWindow::handleCardClick(int value)
{
    for (cardwidget *widget : m_cardWidgets) {
        if (widget->getNumber() == value) {
            widget->showNumber(true);
        }
    }

    m_clickedValues.append(value);

    if (m_clickedValues.size() == 3) {
        int sum = 0;
        bool allScored = true;

        for (int val : m_clickedValues) {
            sum += val;

            bool found = false;
            for (cardwidget *widget : m_cardWidgets) {
                if (widget->getNumber() == val && !widget->isScored()) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                allScored = false;
            }
        }

        if (!allScored) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Сумма очков");
            msgBox.setText("Набрано очков: " + QString::number(sum));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();

            m_score += sum;
            ui->scoreLabel->setText("Очки: " + QString::number(m_score));
        }

        m_clickedValues.clear();

        for (cardwidget *widget : m_cardWidgets) {
            widget->showNumber(false);
        }

        resetGame();
    }
}

void MainWindow::handleCardScored(int value)
{
    m_score += value;
    ui->scoreLabel->setText("Очки: " + QString::number(m_score));
}

void MainWindow::on_loginButton_clicked()
{
    QString enteredPin = ui->editPin->text();

    if (m_isStartup) {
        if (enteredPin == m_correctPin) {
            ui->stackedWidget->setCurrentIndex(1);
            m_isStartup = false;
        } else {
            ui->lblLogin->setText("Неверный пинкод");
            ui->lblLogin->setStyleSheet("color:red;");
        }
    }

    ui->editPin->clear();
}

void MainWindow::checkScoredCards()
{
    if (m_clickedValues.size() >= 3) {
        int sum = 0;
        for (int i = 0; i < 3; ++i) {
            sum += m_clickedValues[i];
        }

        QMessageBox::information(this, "Сумма очков", "Сумма выбранных карточек: " + QString::number(sum));

        m_clickedValues.clear();
    }
}
