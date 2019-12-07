package main

import (
	"fmt"
	"io"
	"log"
	"sync"
)

type LOG_LEVEL int

const (
	ERROR_LEVEL LOG_LEVEL = iota
	WARNING_LEVEL
	INFO_LEVEL
	DEBUG_LEVEL
)

type Logger struct {
	m_logChannel      map[LOG_LEVEL]*log.Logger
	m_currentLogLevel LOG_LEVEL
}

func (lgr *Logger) InitLogger(file_ptr *io.Writer) {

	lgr.m_logChannel = make(map[LOG_LEVEL]*log.Logger, 4)

	lgr.m_logChannel[DEBUG_LEVEL] = log.New(*file_ptr, "DEBUG: ", log.Lshortfile)

	lgr.m_logChannel[INFO_LEVEL] = log.New(*file_ptr, "INFO: ", log.Lshortfile)

	lgr.m_logChannel[WARNING_LEVEL] = log.New(*file_ptr,
		"WARNING: ",
		log.Ldate|log.Ltime|log.Lshortfile)

	lgr.m_logChannel[ERROR_LEVEL] = log.New(*file_ptr,
		"ERROR: ",
		log.Ldate|log.Ltime|log.Lshortfile)

	lgr.m_currentLogLevel = ERROR_LEVEL
}

func (lgr *Logger) SetLogLevel(level LOG_LEVEL) {
	lgr.m_currentLogLevel = level
}

func (lgr *Logger) Debug(v ...interface{}) {
	if lgr.m_currentLogLevel >= DEBUG_LEVEL {
		lgr.m_logChannel[DEBUG_LEVEL].Output(2, fmt.Sprint(v...))
	}
}

func (lgr *Logger) Info(v ...interface{}) {

	if lgr.m_currentLogLevel >= INFO_LEVEL {
		lgr.m_logChannel[INFO_LEVEL].Output(2, fmt.Sprint(v...))
	}
}

func (lgr *Logger) Warning(v ...interface{}) {

	if lgr.m_currentLogLevel >= WARNING_LEVEL {
		lgr.m_logChannel[WARNING_LEVEL].Output(2, fmt.Sprint(v...))
	}
}

func (lgr *Logger) Error(v ...interface{}) {

	if lgr.m_currentLogLevel >= ERROR_LEVEL {
		lgr.m_logChannel[ERROR_LEVEL].Output(2, fmt.Sprint(v...))
	}
}

var singletonLogger *Logger
var once sync.Once

func GetLogger() *Logger {
	once.Do(func() {
		singletonLogger = &Logger{}
	})
	return singletonLogger
}
