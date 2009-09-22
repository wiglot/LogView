
#include "logview.h"


using namespace Logger;

#include <QtGui>
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogView w;
    w.show();


	QObject::connect(LogPool::instance(), SIGNAL(newLog(LogMessage*)), &w, SLOT(insertLog(LogMessage *)));
    LogPool::warning("Teste");
    LogPool::warning("Teste");
    LogPool::fatal("Teste");
    LogPool::log("Teste");
    LogPool::fatal("Teste");
    LogPool::log("Teste");
    LogPool::log("Teste");
    LogPool::fatal("Teste");



    return a.exec();
}
