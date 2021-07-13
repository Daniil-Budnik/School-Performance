#include "school.h"
#include "begin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    begin s;
    s.show();
    return a.exec();
}
