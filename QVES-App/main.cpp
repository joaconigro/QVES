#include "MainWindow.h"
#include <QApplication>
#include "QIcon"
//#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QTranslator translator;
//    bool result = translator.load(":/QVES_en.qm");

    QApplication a(argc, argv);
//    a.installTranslator(&translator);
    MainWindow w;

    QIcon icon(":/icon.png");
    w.setWindowIcon(icon);

    w.show();

    return a.exec();
}
