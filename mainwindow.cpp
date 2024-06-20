#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameWindow(new GameWindow(this))
{
    ui->setupUi(this);

    connect(ui->edtPin, &QLineEdit::returnPressed, this, &MainWindow::on_edtPin_returnPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{
    if (ui->edtPin->text() == correctPin) {
        gameWindow->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный PIN");
    }
}

void MainWindow::on_edtPin_returnPressed()
{
    on_btnLogin_clicked();
}
