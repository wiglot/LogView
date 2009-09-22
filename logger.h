//
// C++ Interface: logpool
//
// Description: 
//
//
// Author: Wagner de Melo Reck,,, <wagner@wiglotron>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LOGGERLOGPOOL_H
#define LOGGERLOGPOOL_H

#include <QObject>

class QFile;
class QTextStream;

namespace Logger {

/**
	@author Wagner de Melo Reck,,, <wagner@wiglotron>
*/
enum LogType {LOG, WARNING, FATAL};

class LogMessage:public QObject {
Q_OBJECT
public:

	LogMessage(){ }
	~LogMessage(){ }

	void setMessage ( const QString& theValue ){_message = theValue;	}
	
	QString message() const{return _message;	}


	void setType ( const LogType& theValue ){_type = theValue;}

	LogType type() const{return _type;}

private:
	QString _message;
	LogType _type;

};

class LogPool : public QObject
{
Q_OBJECT
private:
	static LogPool * self;

	QList <LogMessage*> messages;


	LogPool(){ }
	~LogPool(){	foreach(LogMessage* msg, messages)	delete msg;	}
	
signals:
	void newLog(LogMessage*);
	void newLog();
public:
	inline static LogPool * instance(){
		if (LogPool::self == 0)
			LogPool::self = new LogPool;
		return LogPool::self;
	}

	static int size(){
		return LogPool::instance()->messages.size();
	}

	static LogMessage * getLog(int index){
		if (index < 0)
			throw (QString("Index Is Negative."));
		if (index >= LogPool::size())
			throw (QString("Index Out of bounds."));
		
		return LogPool::instance()->messages[index];
	}

	static void clearLogs(){
		if (LogPool::self != 0){
			delete 	LogPool::self;
			LogPool::self = 0;
		}
	}

	static void log(LogType type, QString msg){
		LogMessage * l = new LogMessage;
		l->setType(type);
		l->setMessage(msg);
		LogPool::instance()->messages.append(l);

		emit LogPool::instance()->newLog();
		emit LogPool::instance()->newLog(l);
	
	}

	static void warning(QString msg){
		LogPool::log(Logger::WARNING, msg);
	}

	static void log(QString msg){
		LogPool::log(Logger::LOG, msg);
	}
	static void fatal(QString msg){
		LogPool::log(Logger::FATAL, msg);
	}

};


class LogFile : public QObject{
Q_OBJECT
public:
	LogFile(QString fileName = "logFile.log");
	~LogFile();
    void saveAtEach(int value = 0);

public slots:
	void appendLog(LogMessage* log);

private:
	QFile * file;
	QTextStream * textStream;
    int _saveAtEach;
    int _stored;
    int _actual;

    void writeLog(LogMessage * log);
	
};

}

#endif
