#include "cardwidget.h"
#include "ui_cardwidget.h"

cardwidget::cardwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cardwidget),
    m_number(0),
    m_isOpened(false) // Инициализация переменных
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &cardwidget::on_cardButton_clicked);

    // Изначально скрываем число на карточке
    ui->label->setText("");
}

cardwidget::~cardwidget()
{
    delete ui;
}

void cardwidget::setNumber(int number)
{
    m_number = number;
}

void cardwidget::on_cardButton_clicked()
{
    if (!m_isOpened) {
        // Если карточка не открыта, показываем число и отправляем сигнал
        ui->label->setText(QString::number(m_number));
        m_isOpened = true;
        emit cardClicked(m_number);
    }
}
