//
// C++ Implementation: logpool
//
// Description: 
//
//
// Author: Wagner de Melo Reck,,, <wagner@wiglotron>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "logger.h"
#include <QFile>
#include <QTextStream>
#include <QString>

namespace Logger {

    LogPool * LogPool::self = 0;

    LogFile::LogFile(QString fileName){
        file = new QFile(fileName);
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
            throw QString("Can't open the file"+fileName);

        textStream = new QTextStream(file);
        _saveAtEach = 0;
        _stored = _saveAtEach;
        _actual = LogPool::size();
    }

    void LogFile::saveAtEach(int value){
        _saveAtEach = value;
    }

    LogFile::~LogFile(){
        file->close();
        delete textStream;
        delete file;
    }

    void LogFile::appendLog(LogMessage* log){
        LogMessage* retrieved;
        int i;

        if (_stored == 0){
            for (i = 0 ; i < _saveAtEach && _actual < LogPool::size()-1; i++, _actual++){
                retrieved = LogPool::getLog(_actual);
                writeLog(retrieved);
            }
            writeLog(log);
            file->flush();
            _stored = _saveAtEach;
        }else{
            --_stored;
        }
    }

    void LogFile::writeLog(LogMessage* log){
        switch(log->type()){
                case Logger::WARNING : *textStream << "Warning: "; break;
                case Logger::FATAL   : *textStream << "FATAL  : "; break;
                default : *textStream <<              "Log    : ";
            }
        *textStream << log->message() << "\n";
    }
}
