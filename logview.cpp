

#include "logger.h"
using namespace Logger;

#include "logview.h"



LogView::LogView(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

}

LogView::~LogView()
{

}

void LogView::insertLog(LogMessage * log){

	if (log->type() <= ui.logLevel->currentIndex()){
		QListWidgetItem * item = new QListWidgetItem (log->message());
		ui.logList->addItem(item);
		switch (log->type()){
		case Logger::FATAL :
			item->setBackgroundColor(Qt::red);
			break;
		case Logger::WARNING :
			item->setBackgroundColor(Qt::yellow);
			break;
		case Logger::LOG :
			item->setBackgroundColor(Qt::white);
			break;
		}
	}
}
