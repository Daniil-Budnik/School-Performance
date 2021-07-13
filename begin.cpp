#include "begin.h"
#include "ui_begin.h"

begin::begin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::begin)
{
    ui->setupUi(this);

    // Таблица стартовой сводки
    QStringList HeaderTab = *new QStringList();
    ListDataBase = new QStandardItemModel();
    ui->TAB->setModel(ListDataBase);

    // Шапка стартовой сводки
    HeaderTab << "Класс" << "Кол-во учеников"
              << "'5'" << "'4'" << "'3'"<< "'2'" << "'Н'"
              << "Успеваемость" << "Качество" << "Обученность";

    // Установка шапки
    ListDataBase->setHorizontalHeaderLabels(HeaderTab);

    // Загрузка данных (из папки data)
    ListFilesDataBase();

    // Работаем с данными
    for(int i = 0; i < DataBase.size(); i++){
        DataBS("data/" + DataBase.at(i),i);
    }

    // Размеры
    ui->TAB->setColumnWidth(0,180);
    ui->TAB->setColumnWidth(1,200);
    ui->TAB->setColumnWidth(2,50);
    ui->TAB->setColumnWidth(3,50);
    ui->TAB->setColumnWidth(4,50);
    ui->TAB->setColumnWidth(5,50);
    ui->TAB->setColumnWidth(6,50);
}

// Деструктор
begin::~begin()
{
    delete ui;
}

// Список файлов в папке
void begin::ListFilesDataBase()
{

    // Путь к БД
    QDir DirDB("data/");

    // Дополнительные переменные
    int INDEX = 0;
    bool Triger = true;
    QString Name = "";

    // Работа с базой данных (массивы)
    DataBase.clear();
    QList<QStandardItem *> LineData;

    // Проверяем все БД в папке data
    for(QString word : DirDB.entryList()){
        if(word != "." and word != ".."){

            // Добавляем имя файла в массив
            DataBase.append(word);

            // Дополнительные переменные
            INDEX++;
            Name = "";
            Triger = true;

            // Пред очистка строки для записи данных в сводку
            LineData.clear();

            // Вывод имени БД без расширения
            for(QString Symb : word){
                if(Symb == "."){
                    Triger = false;
                }
                if(Triger){
                    Name += Symb;
                }
            }

            // Выполняем запись сводки
            LineData.append(new QStandardItem(Name));
            ListDataBase->insertRow(ListDataBase->rowCount(),LineData);
        }
    }
}

// Сводка по базе данных
void begin::DataBS(QString dir_file, int id)
{

    // Экземпляр файла
    QFile file(dir_file);
    QStringList SelectData;

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) { qDebug() << "Файл не открыт"; }
    else {

        // Создаём поток для извлечения данных из файла
        QTextStream InputFile(&file);

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


            // Очищаем
            DataArr.clear();

            // Столбцы
            QStringList InDate1 = *new QStringList();
            QStringList InDate2 = *new QStringList();

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

                    }else{

                        // Проверка оценки и посещения
                        if(LineData == "2"){
                            Num2++;
                            Sum++;
                            Average+=2;
                        }
                        if(LineData == "3"){
                            Num3++;
                            Sum++;
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

                    // Посещаемость
                    if(i == 3){
                        FullAttendance += Attendance;
                    }

                    // Четвертная
                    else if(i == 4){
                        FullNum += Quarter;
                    }

                    // Имя
                    else{
                        IndexStud++;
                    }
                }
            }

            // Зарктыь файл
            file.close();

            // Статистика учеников
            ListDataBase->setItem(id,1, new QStandardItem(QString::number(Students)));
            ListDataBase->setItem(id,2, new QStandardItem(QString::number(St5)));
            ListDataBase->setItem(id,3, new QStandardItem(QString::number(St4)));
            ListDataBase->setItem(id,4, new QStandardItem(QString::number(St3)));
            ListDataBase->setItem(id,5, new QStandardItem(QString::number(St2)));
            ListDataBase->setItem(id,6, new QStandardItem(QString::number(NA)));
            ListDataBase->setItem(id,7, new QStandardItem(QString::number(int((float(St5+St4+St3)/float(Students))*100)) + "%"));
            ListDataBase->setItem(id,8, new QStandardItem(QString::number(int((float(St5+St4)/float(Students))*100)) + "%"));
            ListDataBase->setItem(id,9, new QStandardItem(QString::number(int((float(
                                                                                   float(St5)+
                                                                                   float(St4*0.64)+
                                                                                   float(St3*0.36)+
                                                                                   float(St2*0.16)+
                                                                                   float((NA-St2)*0.16))
                                                                               /float(Students))*100)) + "%"));
        }
    }
}

// Перемещение (НЕ ИСПОЛЬЗУЕТСЯ)
bool begin::MoveFileDataBase(QString DataBasePath, QString NewName)
{
    // Определяем расширение файла
    QString Tag = "";
    for(int i = 4; i > 0; i--){
        Tag += DataBasePath.data()[DataBasePath.size() - i];
    }

    // Если расширение соответствует, делаем копию файла
    if(Tag == "schp" or Tag == ".csv"){
        return QFile::copy(DataBasePath,"data/" + NewName + ".schp");
    }

    // В случае неудачи, false
    return false;
}

// Открывать базу данных по двойному клику в базе данных
void begin::on_TAB_doubleClicked(const QModelIndex &index)
{
    SCH = new School("data/" + DataBase.at(index.row()));
    this->close();
    SCH->show();
}

// Открывать базу данных из списка
void begin::on_OPEN_clicked()
{
    OPT = new OpenTab(DataBase);
    OPT->show();
}
