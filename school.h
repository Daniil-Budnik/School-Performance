#ifndef SCHOOL_H
#define SCHOOL_H

#include <QMainWindow>
#include <QDialog>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class School; }
QT_END_NAMESPACE

class School : public QMainWindow
{
    Q_OBJECT

public:
    School(QString DirData, QWidget *parent = nullptr);
    ~School();

private slots:
    void on_action_16_triggered();
    void on_action_21_triggered();

private:
    Ui::School *ui;
    void csvRead(QString dir_files);

    QStandardItemModel *csvModel1;
    QStandardItemModel *csvModel2;

};
#endif // SCHOOL_H
