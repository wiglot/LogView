#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QtGui/QWidget>
#include "ui_logview.h"

#include "logger.h"
using namespace Logger;

class LogView : public QWidget
{
    Q_OBJECT

public:
    LogView(QWidget *parent = 0);
    ~LogView();

public slots:
	void insertLog(LogMessage * log);

private:
    Ui::LogViewClass ui;

};

#endif // LOGVIEW_H
