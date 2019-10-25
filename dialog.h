#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMultiMap>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    static  QString month;

private slots:
    void on_pushButton_clicked();


    void on_openButton_clicked();


    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
