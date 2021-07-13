#include "opentab.h"
#include "ui_opentab.h"

OpenTab::OpenTab(QStringList DataBase, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenTab)
{
    ui->setupUi(this);

    DB = DataBase;

    for (const QString &Data : qAsConst(DB)) {
      ui->ListDataBase->addItem(Data);
    }

}


OpenTab::~OpenTab()
{
    delete ui;
}

// Открыть окно базы данных
void OpenTab::on_ListDataBase_doubleClicked(const QModelIndex &index)
{
    SCH = new School("data/" + DB.at(index.row()));
    SCH->show();
    on_BACK_clicked();
}

// Открыть окно базы данных
void OpenTab::on_PUSH_clicked()
{
    SCH = new School("data/" + DB.at(INDEX));
    SCH->show();
    on_BACK_clicked();
}

// Закрыть окно
void OpenTab::on_BACK_clicked()
{
    this->close();
}

// Отслеживание
void OpenTab::on_ListDataBase_currentRowChanged(int currentRow)
{
    INDEX = currentRow;
}
