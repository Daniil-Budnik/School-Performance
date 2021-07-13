#ifndef OPENTAB_H
#define OPENTAB_H

#include <QMainWindow>
#include <QDebug>
#include "school.h"

namespace Ui {
class OpenTab;
}

class OpenTab : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenTab(QStringList DataBase, QWidget *parent = nullptr);
    ~OpenTab();

private slots:
    void on_ListDataBase_doubleClicked(const QModelIndex &index);
    void on_PUSH_clicked();
    void on_BACK_clicked();
    void on_ListDataBase_currentRowChanged(int currentRow);

private:
    Ui::OpenTab *ui;
    School *SCH;
    QStringList DB;
    int INDEX = 0;
};

#endif // OPENTAB_H
