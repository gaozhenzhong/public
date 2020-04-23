QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES     += QT_DEPRECATED_WARNINGS
INCLUDEPATH += /home/code/boost_1_72_0

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MuduoTest.cpp \
    main.cpp \
    muduo/base/AsyncLogging.cc \
    muduo/base/Condition.cc \
    muduo/base/CountDownLatch.cc \
    muduo/base/CurrentThread.cc \
    muduo/base/Date.cc \
    muduo/base/Exception.cc \
    muduo/base/FileUtil.cc \
    muduo/base/LogFile.cc \
    muduo/base/LogStream.cc \
    muduo/base/Logging.cc \
    muduo/base/ProcessInfo.cc \
    muduo/base/Thread.cc \
    muduo/base/ThreadPool.cc \
    muduo/base/TimeZone.cc \
    muduo/base/Timestamp.cc \
    netTool.cpp

HEADERS += \
    MuduoTest.h \
    muduo/base/AsyncLogging.h \
    muduo/base/Atomic.h \
    muduo/base/BlockingQueue.h \
    muduo/base/BoundedBlockingQueue.h \
    muduo/base/Condition.h \
    muduo/base/CountDownLatch.h \
    muduo/base/CurrentThread.h \
    muduo/base/Date.h \
    muduo/base/Exception.h \
    muduo/base/FileUtil.h \
    muduo/base/GzipFile.h \
    muduo/base/LogFile.h \
    muduo/base/LogStream.h \
    muduo/base/Logging.h \
    muduo/base/Mutex.h \
    muduo/base/ProcessInfo.h \
    muduo/base/Singleton.h \
    muduo/base/StringPiece.h \
    muduo/base/Thread.h \
    muduo/base/ThreadLocal.h \
    muduo/base/ThreadLocalSingleton.h \
    muduo/base/ThreadPool.h \
    muduo/base/TimeZone.h \
    muduo/base/Timestamp.h \
    muduo/base/Types.h \
    muduo/base/WeakCallback.h \
    muduo/base/copyable.h \
    muduo/base/noncopyable.h \
    netTool.h

FORMS += \
    netTool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


