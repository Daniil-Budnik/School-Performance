#ifndef BEGIN_H
#define BEGIN_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <qstring.h>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QPushButton>
#include <QTableWidgetItem>

#include "school.h"
#include "opentab.h"

namespace Ui {
class begin;
}

class begin : public QMainWindow
{
    Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    ~begin();


private slots:
    void on_TAB_doubleClicked(const QModelIndex &index);
    void on_OPEN_clicked();

private:
    Ui::begin *ui;

    int IndexDataBase = 0;
    School *SCH;
    OpenTab *OPT;
    QStringList DataBase;
    QStandardItemModel *ListDataBase;

    void DataBS(QString dir_file, int id);
    void ListFilesDataBase();
    bool MoveFileDataBase(QString DataBasePath, QString NewName);
};

#endif // BEGIN_H
