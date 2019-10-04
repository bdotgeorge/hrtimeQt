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
// block of metods
struct EveryPerson
{
    QString name;
    QVector<int> dates;
    QVector<int> jobTime;
    QMap<int, int> howYouWorkInTisMonth;
};

void toMap(EveryPerson &person)
{
    for (int i = 0; i < person.dates.size(); i++) {
        if (person.howYouWorkInTisMonth.find(person.dates[i] != person.howYouWorkInTisMonth.end())) {
        }

        // person.howYouWorkInTisMonth.insert(person.dates[i],person.jobTime[i]);
    }
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

QStringList separatedByPerson(QString &s)
{
    QStringList byPerson = s.split("времени:", QString::SkipEmptyParts);
    return byPerson;
}

EveryPerson testperson()
{
    EveryPerson person;
    person.name = "name surname lastname"; // test Subject del after
    person.dates = {1, 4, 5, 6, 7, 8, 9, 10}; // test Subject del after
    person.jobTime = {3, 5, 4, 6, 8, 7, 5, 10}; // test Subject del after
    return person;
}

QString toTableForOnePerson(EveryPerson person)
{
    QString out = "";
    out.append(person.name);
    out.append("  | ");

    return out;
}

// end of block

void Dialog::on_pushButton_clicked()
{
    QString adress = ui->lineAdressInput->text();
    QString test = "	Вход	01.08.2019	09:24	Выход	01.08.2019	17:05	7:41";

    // ui->rsultlLabel->setNum(basicStringTokenaser(test).second);

    // QMessageBox::information(this, basicStringTokenaser(test).first, basicStringTokenaser(test).second);
}
