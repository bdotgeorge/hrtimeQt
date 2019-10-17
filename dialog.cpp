#include "dialog.h"

#include "ui_dialog.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QPair>
#include <QFileDialog>


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


QString intToString(int a){
    QString outString = "";
    if (a >= 0 && a <= 9){
        switch (a) {
        case 0:
            outString ="0";
            break;
        case 1:
            outString ="1";
            break;
        case 2:
            outString ="2";
            break;
        case 3:
            outString ="3";
            break;
        case 4:
            outString ="4";
            break;
        case 5:
            outString ="5";
            break;
        case 6:
            outString ="6";
            break;
        case 7:
            outString ="7";
            break;
        case 8:
            outString ="8";
            break;
        case 9:
            outString ="9";
            break;
        }

    }else if (a>=10) {
        outString.append(intToString(a/10)).append(intToString(a % 10));

}
    return  outString;
}


QString toMonth (int month){
    QString currentmonth = "";
    switch (month) {
    case 1: currentmonth = "январь";
        break;
    case 2: currentmonth = "февраль";
        break;
    case 3: currentmonth = "март";
        break;
    case 4: currentmonth = "апрель";
        break;
    case 5: currentmonth = "май";
        break;
    case 6: currentmonth = "июнь";
        break;
    case 7: currentmonth = "июль";
        break;
    case 8: currentmonth = "август";
        break;
    case 9: currentmonth = "сентбрь";
        break;
    case 10: currentmonth = "октябрь";
        break;
    case 11: currentmonth = "ноябрь";
        break;
    case 12: currentmonth = "декабрь";
        break;
    }
    return currentmonth;
}

struct EveryPerson
{
    QString month;
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
    s.append(intToString(fullMinutes / 60));
    s.append(":");
    if (fullMinutes% 60 < 9){
        s.append(intToString(0));
         s.append(intToString(fullMinutes % 60));
    }else {
         s.append(intToString(fullMinutes % 60));
}

   // s.append(" ");
    return s;
}

QPair<QString, int> basicStringTokenaser(const QString &stt)
{
    QPair<QString, int> today;
    if (!stt.split("\t", QString::SkipEmptyParts).isEmpty()){
        today.first = stt.split("\t", QString::SkipEmptyParts).at(1);
        today.second = toMinutten(stt.split("\t", QString::SkipEmptyParts).last());
    }

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
        string.append("  ").append(intToString(e)).append(" ");
    }
    if (e > 9) {
        string.append(" ").append(intToString(e)).append(" ");
    }
    return string;
}

int finder(QVector<int> &dates, int &date, int from)
{
    int result = -1;
    if (from == 0) {
        for (int i = 0; i < dates.size(); ++i) {
            if (dates[i] == date) {
                result = i;
            } else if (i == dates.size() && dates[i] != date) {
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
            }
        }
    }

    return result;
}

QString toTextTableForOnePerson(EveryPerson person) // needed correct implimentation
{
    QString out  = "";
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
    out.append("|");
    for (int i = 0; i <= 15; ++i) {
        if (person.dates.contains(i)){
            out.append(printStew(i));
        }else {
            out.append("    ");
}
        out.append("|");
    }
    int separatist = out.size();
    out.append("\n");
    for (int i = 0; i <= person.name.length(); ++i) {
        out.append(" ");
    }
    for (int i = 0; i <= 15; ++i) {
        if (person.dates.contains(i) && i < person.dates.size()) {
            out.append(toNormalHoursAndMinutes(person.jobTime[i-1]));
            out.append("|");
        }else {
            out.append("    |");
}
    }
    out.append("\n");

    for (int i = 0; i <= person.name.length(); ++i) {
        out.append(" ");
    }
    for (int i = 16; i <= 31; ++i) {
        if (person.dates.contains(i)){
            out.append(printStew(i));
        }else {
            out.append("    ");
}
        out.append("|");
    }
    out.append("\n");
    for (int i = 0; i <= person.name.length(); ++i) {
        out.append(" ");
    }


    //out.append(" ");
    for (int i = 16; i <= 31; ++i) {
        if (person.dates.contains(i) && i < person.dates.size()) {
            out.append(toNormalHoursAndMinutes(person.jobTime[i]));
            out.append("|");
        }else {
            out.append("    |");
}
    }
    out.append("\n");
    for (int i = 0; i <= separatist; ++i) {
        out.append("=");
    }
    out.append("\n");
    return out;
}

QString toStolbic(EveryPerson person){
    QString out = "";

    out.append(person.name);
    out.append("\n");
    for (int i = 0; i < person.dates.size(); ++i) {
        out.append("\t");
        out.append(person.month);
        out.append("\n");
        out.append(printStew(person.dates[i]));
        out.append("\t");
        if (person.dates.contains(i) && i < person.dates.size()) {
            out.append(toNormalHoursAndMinutes(person.jobTime[i]));
            out.append("\n");
        }else {
            out.append("\n");
}
    }




    return  out;
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
    if (!list.isEmpty()) {
        slave.name = list.first().split("\t", QString::SkipEmptyParts).first();

        for (int i = 3; i < list.length(); ++i) {
            QPair<QString, int> pair;
            if (list[i].length() > 45) {
                pair = basicStringTokenaser(list[i]);
                int date = pair.first.split(".", QString::SkipEmptyParts).first().toInt();

                if (!slave.dates.contains(date)) {
                    slave.dates.push_back(date);
                    slave.jobTime.push_back(pair.second);
                } else  {
                    slave.jobTime[slave.dates.indexOf(date)] += pair.second;
                }
            }
        }
         //slave.month =toMonth( pair.first.split(".", QString::SkipEmptyParts).at(1).toInt());
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

bool converterWorker(QString &adress, bool flag)
{
    QString outputAdres = adress.mid(0, adress.length() - 4).append(" OUTPUT.txt");

    QString inputtedText = QString(fromFile(adress));
    QStringList stplittedByPersons = separatedByPerson(inputtedText);
    QList<EveryPerson> parcedByPerson = toStructData(stplittedByPersons);
    QString readyText;
    for (EveryPerson e : parcedByPerson) {
        if (flag){
        readyText.append(toTextTableForOnePerson(e));  //вывод в таблица
        }
        else {
            readyText.append(toStolbic(e)); // вывод в столбик
        }
    }
    return toFile(readyText, outputAdres);
}





// end of block

void Dialog::on_pushButton_clicked()
{
    QString adress = ui->lineAdressInput->text();
    if (converterWorker(adress, true)) {
        ui->rsultlLabel->setText("все прошло хорошо ;-)");
        ui->lineAdressInput->clear();

    } else {
        ui->rsultlLabel->setText("Что то пошло не так");
    }

    //QString test = "	Вход	01.08.2019	09:24	Выход	01.08.2019	17:05	7:41";
    // ui->rsultlLabel->setText(toTextTableForOnePerson(testperson()));
    // QMessageBox::information(this, basicStringTokenaser(test).first, basicStringTokenaser(test).second);
}

// open file in dilog window )))))

// george implimentation



void Dialog::on_openButton_clicked()
    {
        QString openfile=QFileDialog::getOpenFileName(
                    this,
                    tr("Окрыть файл"),
                    "C://",
                    "Text File (*.txt)"
                    );
        //QMessageBox::information(this,tr("Имя файла"), openfile);

        QString adress = openfile;




        //доработать открытие файла
        ui->lineAdressInput->setText(adress);
        bool tablecheskbox = ui->checkBox->isDown();

        if (converterWorker(adress, tablecheskbox)) {
            ui->rsultlLabel->setText("таки кашерный файл");
            ui->lineAdressInput->clear();

        } else {
            ui->rsultlLabel->setText(" ты подсовываешь  мне какую то дичь");
        }


    }

