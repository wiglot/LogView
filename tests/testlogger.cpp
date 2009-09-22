
#include <QtTest/QtTest>

#include "logger.h"

using namespace Logger;

//LogPool * LogPool::self = 0;


class TestLogger : public QObject{
Q_OBJECT
private slots:

	void cleanup(){
		LogPool::clearLogs();
	}

	void initialSizeAndClear(){
		QVERIFY (0 == LogPool::size());
		LogPool::log("A test.");
		LogPool::clearLogs();
		QVERIFY (0 == LogPool::size());
	}

	void fetchNullLog(){
		try{
			LogPool::getLog(0);
			QFAIL("Exceptions about out of bounds don't throwed");
		}catch (QString e){
			QVERIFY("Index Out of bounds." == e);
		}
	
		try{
			LogPool::getLog(-1);
			QFAIL("Exceptions about negative index don't throwed");
		}catch (QString e){
			QVERIFY("Index Is Negative." == e);
		}
	}	
	void insertCustonLog(){
		LogPool::log(Logger::LOG, "A test.");
		QVERIFY (1 == LogPool::size());
		QVERIFY ("A test." == LogPool::getLog(0)->message());
		QVERIFY (Logger::LOG == LogPool::getLog(0)->type());
	}

	void catchSignals(){
 		qRegisterMetaType<LogMessage*>("LogMessage*");

		QSignalSpy spy(LogPool::instance(), SIGNAL(newLog()));
		QSignalSpy spyMessage(LogPool::instance(), SIGNAL(newLog(LogMessage*)));

		LogPool::log("A test.");

		QCOMPARE(spy.count(), 1);
		QCOMPARE(spyMessage.count(), 1);

// 		QList <QVariant> list = spyMessage.takeFirst();
//  		LogMessage * result = qvariant_cast<LogMessage*>(spyMessage.at(0).at(0));
// 		
// 		QVERIFY(result->message() == "A test");
// 		QVERIFY(result->type() == Logger::LOG);
	}

	void insertLog(){
		LogPool::log("A test.");
		QVERIFY (1 == LogPool::size());
		QVERIFY ("A test." == LogPool::getLog(0)->message());
		QVERIFY (Logger::LOG == LogPool::getLog(0)->type());
	}

	void insertWarnig(){
		LogPool::warning("A Warning.");
		QVERIFY (1 == LogPool::size());
		QVERIFY ("A Warning." == LogPool::getLog(0)->message());
		QVERIFY (Logger::WARNING == LogPool::getLog(0)->type());
	}

	void insertFatal(){
		LogPool::fatal("A Fatal.");
		QVERIFY (1 == LogPool::size());
		QVERIFY ("A Fatal." == LogPool::getLog(0)->message());
		QVERIFY (Logger::FATAL == LogPool::getLog(0)->type());
	}
	
	void writeFileLog(){
        LogFile *fileLog = new LogFile("logFile.log");
        QObject::connect(LogPool::instance(), SIGNAL(newLog(LogMessage*)),
             fileLog, SLOT(appendLog(LogMessage*)));
		LogPool::log("A log");
		delete fileLog;

		QFile file("logFile");
        QVERIFY (file.open(QIODevice::ReadOnly | QIODevice::Text));

		QTextStream in(&file);
        QVERIFY (in.readLine() == "Log    : A log");

	}
};
QTEST_MAIN(TestLogger)
 #include "testlogger.moc"

