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
    case 1: currentmonth = "января";
        break;
    case 2: currentmonth = "февраля";
        break;
    case 3: currentmonth = "марта";
        break;
    case 4: currentmonth = "апреля";
        break;
    case 5: currentmonth = "мая";
        break;
    case 6: currentmonth = "июня";
        break;
    case 7: currentmonth = "июля";
        break;
    case 8: currentmonth = "августа";
        break;
    case 9: currentmonth = "сентбря";
        break;
    case 10: currentmonth = "октября";
        break;
    case 11: currentmonth = "ноября";
        break;
    case 12: currentmonth = "декабря";
        break;
    }
    return currentmonth;
}

QString toCurrentMonth (QString month){
    QString currentmonth = "";

    if (month.toLower().contains("янв")){
        currentmonth = "Январь";
    }
    if (month.toLower().contains("февр")){
        currentmonth = "Февраль";
    }
    if (month.toLower().contains("мар")){
        currentmonth = "Март ";
    }
    if (month.toLower().contains("апр")){
        currentmonth = "Апрель ";
    }
    if (month.toLower().contains("мая")){
        currentmonth = "Май";
    }
    if (month.toLower().contains("июн")){
        currentmonth = "Июнь";
    }
    if (month.toLower().contains("июл")){
        currentmonth = "Июль";
    }
    if (month.toLower().contains("авг")){
        currentmonth = "Август";
    }
    if (month.toLower().contains("сент")){
        currentmonth = "Сентябрь";
    }
    if (month.toLower().contains("окт")){
        currentmonth = "Октябрь";
    }
    if (month.toLower().contains("ноя")){
        currentmonth = "Ноябрь";
    }
    if (month.toLower().contains("Декабрь")){
        currentmonth = "Декабрь";
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

int toMinutten(QString &s)
{
    int h = s.split(":", QString::SkipEmptyParts).first().toInt();
    int min = s.split(":", QString::SkipEmptyParts).last().toInt();
    return h * 60 + min;
}

QString toNormalHoursAndMinutes(int fullMinutes)
{
    QString s;
    if (fullMinutes >= 285) { // отнять 45 минут если больше 4 часов  45 минут рабочего дня
        s.append(intToString((fullMinutes - 45) / 60));
    s.append(":");
    if (((fullMinutes - 45) % 60) <= 9){
        s.append(intToString(0));
         s.append(intToString((fullMinutes - 45) % 60));
    }else {
         s.append(intToString((fullMinutes - 45) % 60));
}
    while (s.length()< 5) {
        s.append(" ");
    }
    }
    else { // если меньше 4 часов  45 минут рабочего дня
        s.append(intToString(fullMinutes / 60));
    s.append(":");
    if ((fullMinutes % 60) <= 9){
        s.append(intToString(0));
         s.append(intToString(fullMinutes % 60));
    }else {
         s.append(intToString(fullMinutes % 60));
}
    while (s.length()< 5) {
        s.append(" ");
    }
    }
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
        string.append("  ").append(intToString(e)).append("  ");
    }
    if (e > 9) {
        string.append("  ").append(intToString(e)).append(" ");
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

QString getMonth(QString currentPersonString){
    QString currentMonth;
    if (currentPersonString.split("\n", QString::SkipEmptyParts).size() > 5){
        currentMonth = toMonth(currentPersonString.split("\n", QString::SkipEmptyParts).at(3).split("\t", QString::SkipEmptyParts).at(1).split(".", QString::SkipEmptyParts).at(1).toInt());
    }
   // Dialog::month = currentMonth;

    return  currentMonth;
}



QString toTextTableForOnePerson(EveryPerson person) // needed correct implimentation
{
    QString out  = "\n";
   if (!person.dates.isEmpty()){
      out.append(person.name);
      out.append("  |");
      int tempCounter = 0;

      if (person.dates.size() <= 31){
          for (int i = 0; i < person.dates.size(); ++i) {   //  вывод дат 1 строка

          out.append(printStew(person.dates[i]));
          out.append("|");
               }
      int separatist = out.size();
              out.append("\n");
              for (int i = 0; i <= person.name.length()+1; ++i) {  // сдвиг на длинну имени
                  out.append(" ");
            }
              out.append("|");

              for (int i = 0; i < person.jobTime.size(); ++i) {   //  вывод дат 1 строка

              out.append(toNormalHoursAndMinutes(person.jobTime[i]));
              out.append("|");
                   }
             out.append("\n");
             // разделитель
             for (int i = 0; i <= separatist; ++i) {
                 out.append("=");
             }
            out.append("\n");
      }


   }else {
        out = out.left(out.length()-1);

}
    return out;
    }

QString toStolbic(EveryPerson person){
    QString out = "";
    out.append("\n");
    if (!person.dates.isEmpty()){
        out.append(person.name);
        out.append("\n");
        for (int i = 0; i < person.dates.size(); ++i) {
           // out.append("\t");
            out.append(printStew(person.dates[i]));
            out.append(" ");
            out.append(person.month);
            out.append(" ");
            out.append("\t");
            if (person.dates[i] && i < person.dates.size()) {
                out.append(toNormalHoursAndMinutes(person.jobTime[i]));
                out.append("\n");
            }else {
                out.append("\n");
    }
        }


    }else {
out = out.left(out.length()-1);
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
         slave.month = getMonth(onePersonStr);
    }
    return slave;
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
    readyText.append(toCurrentMonth(parcedByPerson.first().month));
    readyText.append("\n");
    for (EveryPerson e : parcedByPerson) {
        if (flag){

      readyText.append(toStolbic(e)); // вывод в столбик
        }
        else {
        readyText.append(toTextTableForOnePerson(e));  //вывод в таблица
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
}


void Dialog::on_openButton_clicked()
    {
        QString openfile=QFileDialog::getOpenFileName(
                    this,
                    tr("Окрыть файл"),
                    "C://",
                    "Text File (*.txt)"
                    );

        QString adress = openfile;




        ui->lineAdressInput->setText(adress);
        bool tablecheskbox = ui->checkBox->isChecked();

        if (converterWorker(adress, tablecheskbox)) {
            ui->rsultlLabel->setText("Всё прошло хорошо");
            ui->lineAdressInput->clear();

        } else {
            ui->rsultlLabel->setText(" ты подсовываешь  мне какую то дичь");
        }
        QMessageBox::information(this, "Developed by",
                                 "Vladimir  D. Nagaev & George V. Bozhedomov "
                                 "\n "
                                 "LAS Technology Co www.lastechnology.ru",
                                 "Спасибо");


    }



void Dialog::on_checkBox_stateChanged(int arg1)
{

}
