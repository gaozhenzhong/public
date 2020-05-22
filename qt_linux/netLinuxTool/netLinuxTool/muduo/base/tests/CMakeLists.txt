
add_executable(synthesize_test synthesize_test.cc)
target_link_libraries(synthesize_test muduo_base)

add_executable(asynclogging_test AsyncLogging_test.cc)
target_link_libraries(asynclogging_test muduo_base)


add_executable(mutex_test Mutex_test.cc)
target_link_libraries(mutex_test muduo_base)

add_executable(processinfo_test ProcessInfo_test.cc)
target_link_libraries(processinfo_test muduo_base)

add_executable(singleton_test Singleton_test.cc)
target_link_libraries(singleton_test muduo_base)

add_executable(singleton_threadlocal_test SingletonThreadLocal_test.cc)
target_link_libraries(singleton_threadlocal_test muduo_base)

add_executable(thread_bench Thread_bench.cc)
target_link_libraries(thread_bench muduo_base)

add_executable(thread_test Thread_test.cc)
target_link_libraries(thread_test muduo_base)

add_executable(threadlocal_test ThreadLocal_test.cc)
target_link_libraries(threadlocal_test muduo_base)

add_executable(threadlocalsingleton_test ThreadLocalSingleton_test.cc)
target_link_libraries(threadlocalsingleton_test muduo_base)

add_executable(threadpool_test ThreadPool_test.cc)
target_link_libraries(threadpool_test muduo_base)

add_executable(timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(timestamp_unittest muduo_base)
add_test(NAME timestamp_unittest COMMAND timestamp_unittest)

add_executable(timezone_unittest TimeZone_unittest.cc)
target_link_libraries(timezone_unittest muduo_base)
add_test(NAME timezone_unittest COMMAND timezone_unittest)
