
#ifndef LEARNING_CPP_SQLFILTER_H
#define LEARNING_CPP_SQLFILTER_H

#pragma once
#include "utils/checkloginUtils.h"
#include <drogon/HttpFilter.h>
#include <regex>


struct DynamicResult {
    std::ostringstream baseSql;
    std::vector<std::string> parameters;
};

template <typename T>
struct Condition
{
    std::string field;
    std::string op;
    T value;
};

class SqlFilter
{
  public:
    SqlFilter() = default;


    [[gnu::always_inline]] inline static bool FilteredSQLInject(const std::string& str);
};

inline bool SqlFilter::FilteredSQLInject(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    std::string reg = R"((?:')|(?:--)|(\/\*(?:.|[\n\r])*?\*\/)|(\b(select|update|and|or|delete|insert|truncate|char|chr|into|substr|ascii|declare|exec|count|master|into|drop|execute)\b))";
    std::regex re(reg);

    return std::regex_search(str, re);
}

template <typename T>
DynamicResult buildDynamicQuery(const std::string &baseSql, const std::vector<Condition<T>> &conditions)
{

    DynamicResult result;
    result.baseSql << baseSql;
    //std::vector<orm::Field> parameters;

    for (const auto &condition : conditions)
    {
        if (SqlFilter::FilteredSQLInject(condition.value)) {
            throw std::invalid_argument("参数带有sql注入的危险");
        }
        //result.baseSql += " AND " + condition.field + " " + condition.op + " " + condition.value;
        result.baseSql << " AND " << condition.field << " " + condition.op << " '" << condition.value << "'";
        result.parameters.emplace_back(condition.value);
    }

    return result;
}

#endif