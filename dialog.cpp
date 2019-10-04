#include "dialog.h"

#include "ui_dialog.h"

#include <QMessageBox>
#include <QPair>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

int toMinutten(QString &s)
{
    int h = s.split(":", QString::SkipEmptyParts).first().toInt();
    int min = s.split(":", QString::SkipEmptyParts).last().toInt();
    return h * 60 + min;
}

QString toNormalHoursAndMinutes(int fullMinutes)
{
    QString s;
    s.append(fullMinutes / 60);
    s.append(":");
    s.append(fullMinutes % 60);
    return s;
}

QPair<QString, int> basicStringTokenaser(const QString &stt)
{
    QPair<QString, int> today;
    today.first = stt.split("\t", QString::SkipEmptyParts).at(1);
    today.second = toMinutten(stt.split("\t", QString::SkipEmptyParts).last());
    return today;
}

void Dialog::on_pushButton_clicked()
{
    QString adress = ui->lineAdressInput->text();
    QString test = "	Вход	01.08.2019	09:24	Выход	01.08.2019	17:05	7:41";

    ui->rsultlLabel->setNum(basicStringTokenaser(test).second);

    // QMessageBox::information(this, basicStringTokenaser(test).first, basicStringTokenaser(test).second);
}
