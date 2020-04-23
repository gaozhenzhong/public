
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"

#include "MuduoTest.h"

MuduoTest::MuduoTest()
{
   // LOG_ERROR<<"MuduoTest init";
    muduo::Logger(__FILE__, __LINE__, muduo::Logger::ERROR).stream()<<"MuduoTest init";
}
