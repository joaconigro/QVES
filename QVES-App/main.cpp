#include "MainWindow.h"
#include <QApplication>
#include "QIcon"
#include <QTranslator>
#include <QSettings>
#include <QCoreApplication>

QTranslator* translate(bool &result){
    QCoreApplication::setOrganizationName("Joaco's Soft");
    QCoreApplication::setApplicationName("QVES");
    QSettings settings;
    QTranslator *translator = new QTranslator();

    int language = settings.value("Language").toInt();
    switch (language) {
    case 0:
        //result = translator.load(":/QVES_es.qm");
        break;
    case 1:
        result = translator->load(":/QVES_en.qm");
        break;
    default:
        break;
    }

    return translator;

}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    bool result = false;
    QTranslator* t = translate(result);
    if (result)
        a.installTranslator(t);

    MainWindow w;

    QIcon icon(":/icon.png");
    w.setWindowIcon(icon);

    w.show();

    return a.exec();
}
