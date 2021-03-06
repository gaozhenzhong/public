QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
#CONFIG += -Wpessimizing-move
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
    baseClass.cpp \
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
    muduo/net/Acceptor.cc \
    muduo/net/Buffer.cc \
    muduo/net/Channel.cc \
    muduo/net/Connector.cc \
    muduo/net/EventLoop.cc \
    muduo/net/EventLoopThread.cc \
    muduo/net/EventLoopThreadPool.cc \
    muduo/net/InetAddress.cc \
    muduo/net/Poller.cc \
    muduo/net/Socket.cc \
    muduo/net/SocketsOps.cc \
    muduo/net/TcpClient.cc \
    muduo/net/TcpConnection.cc \
    muduo/net/TcpServer.cc \
    muduo/net/Timer.cc \
    muduo/net/TimerQueue.cc \
    muduo/net/poller/DefaultPoller.cc \
    muduo/net/poller/EPollPoller.cc \
    muduo/net/poller/PollPoller.cc \
    myclass/UDPServer.cpp \
    netTool.cpp

HEADERS += \
    MuduoTest.h \
    baseClass.h \
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
    muduo/net/Acceptor.h \
    muduo/net/Buffer.h \
    muduo/net/Callbacks.h \
    muduo/net/Channel.h \
    muduo/net/Connector.h \
    muduo/net/Endian.h \
    muduo/net/EventLoop.h \
    muduo/net/EventLoopThread.h \
    muduo/net/EventLoopThreadPool.h \
    muduo/net/InetAddress.h \
    muduo/net/Poller.h \
    muduo/net/Socket.h \
    muduo/net/SocketsOps.h \
    muduo/net/TcpClient.h \
    muduo/net/TcpConnection.h \
    muduo/net/TcpServer.h \
    muduo/net/Timer.h \
    muduo/net/TimerId.h \
    muduo/net/TimerQueue.h \
    muduo/net/ZlibStream.h \
    muduo/net/boilerplate.h \
    muduo/net/poller/EPollPoller.h \
    muduo/net/poller/PollPoller.h \
    myclass/UDPServer.h \
    netTool.h

FORMS += \
    netTool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



