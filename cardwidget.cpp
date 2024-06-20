#include "cardwidget.h"
#include "ui_cardwidget.h"

cardwidget::cardwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cardwidget),
    m_number(0),
    m_isOpened(false),
    m_isScored(false)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &cardwidget::on_cardButton_clicked);
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

void cardwidget::showNumber(bool show)
{
    ui->label->setVisible(show);
}

void cardwidget::setScored(bool scored)
{
    m_isScored = scored;
}

bool cardwidget::isScored() const
{
    return m_isScored;
}

void cardwidget::on_cardButton_clicked()
{
    if (!m_isOpened) {
        ui->label->setText(QString::number(m_number));
        m_isOpened = true;
        emit cardClicked(m_number);

        if (!m_isScored) {
            m_isScored = true;
            emit scoreCounted(m_number);
        }
    }
}
