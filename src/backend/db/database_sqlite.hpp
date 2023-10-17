/*
 * Created by parthu on 10/5/23.
 * DB Implementation as Singleton
*/
#pragma once

#include <atomic>
#include <mutex>
#include <memory>

class ArticleDatabase
{
public:
    static std::shared_ptr<ArticleDatabase> getInstance();

    static bool date_valid(const std::string& date);

private:
    ArticleDatabase()= default;
    ~ArticleDatabase()= default;
    ArticleDatabase(const ArticleDatabase&)= delete;
    ArticleDatabase& operator=(const ArticleDatabase&)= delete;

    static std::atomic<std::shared_ptr<ArticleDatabase>> instance;
    static std::mutex myMutex;
};

