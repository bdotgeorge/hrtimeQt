#include "dialog.h"

#include "ui_dialog.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QPair>

#include <iomanip>

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
    // QMap<int, int> howYouWorkInTisMonth;
};
/*
void toMap(EveryPerson &person)
{
    // QMap<int, int>::iterator it = person.howYouWorkInTisMonth.begin();
    for (int i = 0; i < person.dates.size(); i++) {
        if (person.howYouWorkInTisMonth.find(person.dates[i]) != person.howYouWorkInTisMonth.end()) {
            int newValue = person.howYouWorkInTisMonth.value(person.howYouWorkInTisMonth.last()) + person.jobTime[i];
            person.howYouWorkInTisMonth.value(person.howYouWorkInTisMonth.last(), newValue);
        } else {
            person.howYouWorkInTisMonth.insert(person.dates[i], person.jobTime[i]);
        }
        // person.howYouWorkInTisMonth.insert(person.dates[i],person.jobTime[i]);
    }
}
*/
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
    person.jobTime = {53, 55, 54, 56, 58, 57, 55, 30}; // test Subject del after
    return person;
}

QString printStew(int e)
{
    QString string = "";
    if (e <= 0) {
        string.append("  ").append("-").append(" ");
    }
    if (e > 0 && e <= 9) {
        string.append("  ").append(e).append(" ");
    }
    if (e > 9) {
        string.append(" ").append(e).append(" ");
    }
    return string;
}

int finder(QVector<int> &dates, int &date, int from)
{
    int result = -2;
    if (from == 0) {
        for (int i = 0; i < dates.size(); ++i) {
            if (dates[i] == date) {
                result = i;
            } else if (result == -2 && i == dates.size() - 1) {
                result = -1;
            }
        }
    } else {
        for (int i = 0; i < dates.size(); ++i) {
            if (i == from) {
                continue;
            }
            if (dates[i] == date) {
                result = i;
            } else if (result == -2 && i == dates.size() - 1) {
                result = -1;
            }
        }
    }

    return result;
}

QString toTextTableForOnePerson(EveryPerson person) // needed correct implimentation
{
    QString out = "";
    // QTextStream stream(&out);
    /*
    stream << person.name;
    stream << "  |";
    for (int i = 0; i < 31; ++i) {
        stream << printStew(finder(person.dates, i)) << "|";
    }
    stream << "\n";
    for (int i = 0; i < person.name.length(); ++i) {
        stream << " ";
    }
    for (int i = 0; i < 31; ++i) {
        if (finder(person.dates, i) == i) {
            stream << printStew(person.jobTime[i]) << "|";
        }
    }
    */
    out.append(person.name);
    out.append("  |");
    for (int i = 0; i < 31; ++i) {
        out.append(printStew(finder(person.dates, i, 0)));
        out.append("|");
    }
    out.append("\n");
    for (int i = 0; i < person.name.length(); ++i) {
        out.append(" ");
    }
    out.append(" ");
    for (int i = 0; i < 31; ++i) {
        if (finder(person.dates, i, 0) == i) {
            out.append(printStew(person.jobTime[i]));
            out.append("|");
        }
    }
    out.append("\n");
    out.append("\n");
    return out;
}

QString fromFile(const QString &pathFile)
{
    QFile inputFile(pathFile);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File not open: " + pathFile;
    }

    QTextStream stream(&inputFile);
    QString out = stream.readAll();
    return out;
}

bool toFile(QString outPutString, const QString &pathFile)
{
    QDir dir = QFileInfo(pathFile).absoluteDir();
    if (!QDir(dir.absolutePath()).exists())
        QDir().mkpath(dir.absolutePath());

    QFile file(pathFile);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "can't write to file" << pathFile;
        return false;
    }
    QTextStream stream(&file);
    stream << outPutString;

    return true;
}

EveryPerson toStruct(QString &onePersonStr)
{
    EveryPerson slave;
    QStringList list = onePersonStr.split("\n", QString::SkipEmptyParts);
    slave.name = list.first().split("\t", QString::SkipEmptyParts).first();
    for (int i = 4; i < list.length(); ++i) {
        if (list[i].length() > 45) {
            QPair<QString, int> pair = basicStringTokenaser(list[i]);
            int date = pair.first.split(".", QString::SkipEmptyParts).first().toInt();
            if (finder(slave.dates, date, 0) == -1) {
                slave.dates.push_back(date);
                slave.jobTime.push_back(pair.second);
            } else if (finder(slave.dates, date, 0) != -1) {
                slave.jobTime[finder(slave.dates, date, 0)] += pair.second;
            }
        }
    }
    return slave;
}

void personSummator(EveryPerson e) //  not nesessary now cause in Dialog::toStruct it already done
{
    for (int i = 0; i < e.dates.size(); ++i) {
        int position = finder(e.dates, e.dates[i], i);
        if (position != -1) {
            e.dates.erase(&position);
            e.jobTime[i] += e.jobTime[position];
            e.jobTime.erase(&position);
        } else {
            continue;
        }
    }
}

QList<EveryPerson> toStructData(QStringList &listString)
{
    QList<EveryPerson> listForAllPersons;

    for (QString string : listString) {
        listForAllPersons.push_back(toStruct(string));
    }
    return listForAllPersons;
}

bool converterWorker(QString &adress)
{
    QString outputAdres = adress.mid(0, adress.length() - 4).append("OUTPUT.txt");

    QString inputtedText = QString(fromFile(adress));
    QStringList stplittedByPersons = separatedByPerson(inputtedText);
    QList<EveryPerson> parcedByPerson = toStructData(stplittedByPersons);
    QString readyText;
    for (EveryPerson e : parcedByPerson) {
        readyText.append(toTextTableForOnePerson(e));
    }
    return toFile(readyText, outputAdres);
}

// end of block

void Dialog::on_pushButton_clicked()
{
    QString adress = ui->lineAdressInput->text();

    converterWorker(adress);

    //QString test = "	Вход	01.08.2019	09:24	Выход	01.08.2019	17:05	7:41";
    // ui->rsultlLabel->setText(toTextTableForOnePerson(testperson()));
    // QMessageBox::information(this, basicStringTokenaser(test).first, basicStringTokenaser(test).second);
}
