#include "school.h"
#include "ui_school.h"

School::School(QString DirData, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::School)
{
    ui->setupUi(this);

    // Тут указываем путь к файлу.
    csvRead(DirData);
}

School::~School(){ delete ui; }

// Чтение базы данных и их визуализация
void School::csvRead(QString dir_file)
{
    // Получаем модель CSV
    csvModel1 = new QStandardItemModel(this);
    ui->NAME->setModel(csvModel1);
    csvModel2 = new QStandardItemModel(this);
    ui->TAB->setModel(csvModel2);

    // Экземпляр файла
    QFile file(dir_file);

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) { qDebug() << "Файл не открыт"; }
    else {

        // Создаём поток для извлечения данных из файла
        QTextStream InputFile(&file);

        // Счётчик дней проведённых занятий
        // Формат (data 1-1 1-2 и.т.д.) из за "data" -1
        int Days = -1;

        // Считываем шапку
        QString Date = InputFile.readLine();

        // Данные
        QStringList DataArr = *new QStringList();

        // Собираем данные шапки
        for (QString item : Date.split(",")) {
               DataArr.append(item);
        }

        ui->N_Class->setText(DataArr.at(0));
        ui->N_Obj->setText(DataArr.at(1));
        ui->N_4->setText(DataArr.at(2));
        ui->N_Name->setText(DataArr.at(3));


        // Очищаем
        DataArr.clear();

        // Столбцы
        QStringList InDate1 = *new QStringList();
        QStringList InDate2 = *new QStringList();
        InDate1 << "Ученики"
               << "Ср. балл"
               << "N"
               << "Посещ."
               << "Четв.";

        // Каждый столбец с оценкой назван датой
        Date = InputFile.readLine();

        for (QString item : Date.split(",")) {
           if(Days >= 0){
               InDate2 << item;
           }
            Days += 1;
        }

        // Счётчики для расчёта статистики
        int Students = 0,               // Общее кол-во учащихся
                Num2 = 0,               // Общее кол-во двоек
                Num3 = 0,               // Общее кол-во троек
                Num4 = 0,               // Общее кол-во четвёрок
                Num5 = 0,               // Общее кол-во пятёрок
                NumN = 0,               // Общее кол-во пропусков
                St5 = 0,                // Общее кол-во отличников
                St4 = 0,                // Общее кол-во хорошистов
                St3 = 0,                // Общее кол-во троечников
                St2 = 0,                // Общее кол-во должников
                FullNum = 0,            // Общая оценка класса
                FullAttendance = 0,     // Общая посещаемость класса
                IndexStud = 0,          // Индекс имени ученика
                NA = 0;                 // Кол-во не атестованных

        // Переменные для хранения данных
        QString LineData;
        QList<QStandardItem *> ListData1, ListData2;

        // Считываем данные, пока они есть
        while (!InputFile.atEnd())
        {
            // Подсчёт учащихся
            Students++;

            // Очищаем старые данные
            ListData1.clear();
            ListData2.clear();

            // Читаем новую строку
            LineData = InputFile.readLine();

            // Записываем данные в список
            for (QString item : LineData.split(",")) {
                ListData1.append(new QStandardItem(item));
            }

            // Данные для расчёта
            int Sum = 0;                // Общее кол-во оценок
            float Average = 0;          // Средний балл
            int Skips = 0;              // Пропуски
            float Attendance = 0;       // Посищаемость
            int Quarter = 0;            // Четвертная


            // Обрабатываем данные
            for(int i = 0; i < ListData1.size(); i++){
                LineData = ListData1.at(i)->text();

                // Заполняем список учеников
                if(i == 0){
                    DataArr.append(ListData1.at(0)->text());
                }else{

                    // Проверка оценки и посещения
                    if(LineData == "2"){
                        Num2++;
                        Sum++;
                        Average+=2;
                    }
                    if(LineData == "3"){
                        Num3++;
                        ++Sum;
                        Average+=3;
                    }
                    if(LineData == "4"){
                        Num4++;
                        Sum++;
                        Average+=4;
                    }
                    if(LineData == "5"){
                        Num5++;
                        Sum++;
                        Average+=5;
                    }
                    if(LineData == "n" or
                            LineData == "N" or
                            LineData == "н" or
                            LineData == "Н")
                    {
                        NumN++;
                        Skips++;
                    }
                    ListData2.append(ListData1.at(i));
                }
            }

            // Расчёт посищаемости
            if(Skips > 0 and Days > 0){
                Attendance = 100 - ((float)Skips/((float)Days/100));
            }else{
                Attendance = 100;
            }

            // Расчёт среднего балла
            if(Sum > 0){
                Average = Average / Sum;
            }

            // Если оценок за четверть нет, средняя автоматически 2
            else{
                Average = 0;
            }

            // Четвертная
            if(Average >= 4.5){
                Quarter = 5;
                St5++;
            }
            else if(Average >= 3.5){
                Quarter = 4;
                St4++;
            }
            else if(Average >= 2.5){
                Quarter = 3;
                St3++;
            }
            else{
                Quarter = 2;
                St2++;
                NA++;
            }

            // Очищаем старые данные
            ListData1.clear();

            // Заполняем уже обработанные данные
            for(int i = 0; i < 5; i++){

                // Ср. балл
                if(i == 1){
                    if(Average>0){
                       ListData1.append(new QStandardItem(QString::number((float)qRound(Average*10)/10)));
                    }else{
                        ListData1.append(new QStandardItem("Н/А"));
                    }
                }

                // Пропуски
                else if(i == 2){
                    ListData1.append(new QStandardItem(QString::number(Skips)));
                }

                // Посещаемость
                else if(i == 3){
                    LineData = "%";
                    ListData1.append(new QStandardItem(QString::number((float)qRound(Attendance*10)/10) + LineData));
                    FullAttendance += Attendance;
                }

                // Четвертная
                else if(i == 4){
                    ListData1.append(new QStandardItem(QString::number(Quarter)));
                    FullNum += Quarter;
                }

                // Имя
                else{
                    ListData1.append(new QStandardItem(DataArr.at(IndexStud)));
                    IndexStud++;
                }
            }

            // Добавить данные в столбец
            csvModel1->insertRow(csvModel1->rowCount(), ListData1);
            csvModel2->insertRow(csvModel2->rowCount(), ListData2);
        }

        // Зарктыь файл
        file.close();

        // Общее кол-во оценок
        ui->N2->setText(QString::number(Num2));
        ui->N3->setText(QString::number(Num3));
        ui->N4->setText(QString::number(Num4));
        ui->N5->setText(QString::number(Num5));

        // Статистика учеников
        ui->S2->setText(QString::number(St2));
        ui->S3->setText(QString::number(St3));
        ui->S4->setText(QString::number(St4));
        ui->S5->setText(QString::number(St5));

        // Статистические данные
        LineData = "%";
        ui->NN->setText(QString::number(NumN));
        ui->NP->setText(QString::number((float)qRound(((float)FullAttendance/Students)*10)/10) + LineData);
        ui->NS->setText(QString::number((float)qRound(((float)FullNum/Students )*10)/10));
        ui->NA->setText(QString::number(NA));

        // Кол-во обучающихся
        ui->STUD->setText(QString::number(IndexStud));

        // Успеваемость
        ui->YS->setText(QString::number(int((float(St5+St4+St3)/float(IndexStud))*100)) + "%");

        // Качество знаний
        ui->KH->setText(QString::number(int((float(St5+St4)/float(IndexStud))*100)) + "%");

        // Обученность
        ui->OB->setText(QString::number(int((float(
                                                 float(St5)+
                                                 float(St4*0.64)+
                                                 float(St3*0.36)+
                                                 float(St2*0.16)+
                                                 float((NA-St2)*0.16))
                                             /float(IndexStud))*100)) + "%");

        // Шапка таблицы
        csvModel1->setHorizontalHeaderLabels( InDate1 );
        csvModel2->setHorizontalHeaderLabels( InDate2 );

        // Размеры для табеля учеников по ширине
        ui->NAME->setColumnWidth(0,200);
        ui->NAME->setColumnWidth(1,85);
        ui->NAME->setColumnWidth(2,40);
        ui->NAME->setColumnWidth(3,75);
        ui->NAME->setColumnWidth(4,55);

        // Размеры для табеля учеников по высоте
        for(int i = 0; i < Students; i++){
            ui->NAME->setRowHeight(i,1);
        }

        // Размеры для табеля оценок по ширине
        for(int i = 0; i < Days; i++){
            ui->TAB->setColumnWidth(i,70);
        }

        // Размеры для табеля оценок по высоте
        for(int i = 0; i < Students; i++){
            ui->TAB->setRowHeight(i,1);
        }
    }
}


void School::on_action_21_triggered()
{
    this->close();
}

