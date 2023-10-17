//
// Created by parthu on 10/5/23.
//
#include "article_database.hpp"

std::mutex ArticleDatabase::myMutex = std::mutex{};
auto ArticleDatabase::instance = std::atomic(make_shared<ArticleDatabase>(new ArticleDatabase()));

ArticleDatabase* ArticleDatabase::getInstance(){
    ArticleDatabase* inst = instance.load(std::memory_order_acquire);
    if ( !inst ){
        std::lock_guard<std::mutex> myLock(myMutex);
        inst = instance.load(std::memory_order_relaxed);
        if( !inst ){
            inst = new ArticleDatabase();
            instance.store(inst,std::memory_order_release);
        }
    }
    return inst;
}

bool ArticleDatabase::date_valid(const std::string& date)
{
    // only accept sqlite3 conform time stamps (str, but special)
    // ISO8601 "YYYY-MM-DD HH:MM:SS.SSS"

    // TODO: impl
    return true;
}