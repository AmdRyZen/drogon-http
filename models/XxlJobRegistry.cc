/**
 *
 *  XxlJobRegistry.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "XxlJobRegistry.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::xxl_job;

const std::string XxlJobRegistry::Cols::_id = "id";
const std::string XxlJobRegistry::Cols::_registry_group = "registry_group";
const std::string XxlJobRegistry::Cols::_registry_key = "registry_key";
const std::string XxlJobRegistry::Cols::_registry_value = "registry_value";
const std::string XxlJobRegistry::Cols::_update_time = "update_time";
const std::string XxlJobRegistry::primaryKeyName = "id";
const bool XxlJobRegistry::hasPrimaryKey = true;
const std::string XxlJobRegistry::tableName = "xxl_job_registry";

const std::vector<typename XxlJobRegistry::MetaData> XxlJobRegistry::metaData_={
{"id","int32_t","int(11)",4,1,1,1},
{"registry_group","std::string","varchar(50)",50,0,0,1},
{"registry_key","std::string","varchar(255)",255,0,0,1},
{"registry_value","std::string","varchar(255)",255,0,0,1},
{"update_time","::trantor::Date","datetime",0,0,0,0}
};
const std::string &XxlJobRegistry::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
XxlJobRegistry::XxlJobRegistry(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["registry_group"].isNull())
        {
            registryGroup_=std::make_shared<std::string>(r["registry_group"].as<std::string>());
        }
        if(!r["registry_key"].isNull())
        {
            registryKey_=std::make_shared<std::string>(r["registry_key"].as<std::string>());
        }
        if(!r["registry_value"].isNull())
        {
            registryValue_=std::make_shared<std::string>(r["registry_value"].as<std::string>());
        }
        if(!r["update_time"].isNull())
        {
            auto timeStr = r["update_time"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            registryGroup_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            registryKey_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            registryValue_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

XxlJobRegistry::XxlJobRegistry(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            registryGroup_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            registryKey_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            registryValue_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[4]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

XxlJobRegistry::XxlJobRegistry(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("registry_group"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["registry_group"].isNull())
        {
            registryGroup_=std::make_shared<std::string>(pJson["registry_group"].asString());
        }
    }
    if(pJson.isMember("registry_key"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["registry_key"].isNull())
        {
            registryKey_=std::make_shared<std::string>(pJson["registry_key"].asString());
        }
    }
    if(pJson.isMember("registry_value"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["registry_value"].isNull())
        {
            registryValue_=std::make_shared<std::string>(pJson["registry_value"].asString());
        }
    }
    if(pJson.isMember("update_time"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["update_time"].isNull())
        {
            auto timeStr = pJson["update_time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void XxlJobRegistry::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            registryGroup_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            registryKey_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            registryValue_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[4]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void XxlJobRegistry::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("registry_group"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["registry_group"].isNull())
        {
            registryGroup_=std::make_shared<std::string>(pJson["registry_group"].asString());
        }
    }
    if(pJson.isMember("registry_key"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["registry_key"].isNull())
        {
            registryKey_=std::make_shared<std::string>(pJson["registry_key"].asString());
        }
    }
    if(pJson.isMember("registry_value"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["registry_value"].isNull())
        {
            registryValue_=std::make_shared<std::string>(pJson["registry_value"].asString());
        }
    }
    if(pJson.isMember("update_time"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["update_time"].isNull())
        {
            auto timeStr = pJson["update_time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

const int32_t &XxlJobRegistry::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &XxlJobRegistry::getId() const noexcept
{
    return id_;
}
void XxlJobRegistry::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename XxlJobRegistry::PrimaryKeyType & XxlJobRegistry::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &XxlJobRegistry::getValueOfRegistryGroup() const noexcept
{
    static const std::string defaultValue = std::string();
    if(registryGroup_)
        return *registryGroup_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobRegistry::getRegistryGroup() const noexcept
{
    return registryGroup_;
}
void XxlJobRegistry::setRegistryGroup(const std::string &pRegistryGroup) noexcept
{
    registryGroup_ = std::make_shared<std::string>(pRegistryGroup);
    dirtyFlag_[1] = true;
}
void XxlJobRegistry::setRegistryGroup(std::string &&pRegistryGroup) noexcept
{
    registryGroup_ = std::make_shared<std::string>(std::move(pRegistryGroup));
    dirtyFlag_[1] = true;
}

const std::string &XxlJobRegistry::getValueOfRegistryKey() const noexcept
{
    static const std::string defaultValue = std::string();
    if(registryKey_)
        return *registryKey_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobRegistry::getRegistryKey() const noexcept
{
    return registryKey_;
}
void XxlJobRegistry::setRegistryKey(const std::string &pRegistryKey) noexcept
{
    registryKey_ = std::make_shared<std::string>(pRegistryKey);
    dirtyFlag_[2] = true;
}
void XxlJobRegistry::setRegistryKey(std::string &&pRegistryKey) noexcept
{
    registryKey_ = std::make_shared<std::string>(std::move(pRegistryKey));
    dirtyFlag_[2] = true;
}

const std::string &XxlJobRegistry::getValueOfRegistryValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(registryValue_)
        return *registryValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobRegistry::getRegistryValue() const noexcept
{
    return registryValue_;
}
void XxlJobRegistry::setRegistryValue(const std::string &pRegistryValue) noexcept
{
    registryValue_ = std::make_shared<std::string>(pRegistryValue);
    dirtyFlag_[3] = true;
}
void XxlJobRegistry::setRegistryValue(std::string &&pRegistryValue) noexcept
{
    registryValue_ = std::make_shared<std::string>(std::move(pRegistryValue));
    dirtyFlag_[3] = true;
}

const ::trantor::Date &XxlJobRegistry::getValueOfUpdateTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updateTime_)
        return *updateTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &XxlJobRegistry::getUpdateTime() const noexcept
{
    return updateTime_;
}
void XxlJobRegistry::setUpdateTime(const ::trantor::Date &pUpdateTime) noexcept
{
    updateTime_ = std::make_shared<::trantor::Date>(pUpdateTime);
    dirtyFlag_[4] = true;
}
void XxlJobRegistry::setUpdateTimeToNull() noexcept
{
    updateTime_.reset();
    dirtyFlag_[4] = true;
}

void XxlJobRegistry::updateId(const uint64_t id)
{
    id_ = std::make_shared<int32_t>(static_cast<int32_t>(id));
}

const std::vector<std::string> &XxlJobRegistry::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "registry_group",
        "registry_key",
        "registry_value",
        "update_time"
    };
    return inCols;
}

void XxlJobRegistry::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getRegistryGroup())
        {
            binder << getValueOfRegistryGroup();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRegistryKey())
        {
            binder << getValueOfRegistryKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRegistryValue())
        {
            binder << getValueOfRegistryValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getUpdateTime())
        {
            binder << getValueOfUpdateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> XxlJobRegistry::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    return ret;
}

void XxlJobRegistry::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getRegistryGroup())
        {
            binder << getValueOfRegistryGroup();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRegistryKey())
        {
            binder << getValueOfRegistryKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRegistryValue())
        {
            binder << getValueOfRegistryValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getUpdateTime())
        {
            binder << getValueOfUpdateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value XxlJobRegistry::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getRegistryGroup())
    {
        ret["registry_group"]=getValueOfRegistryGroup();
    }
    else
    {
        ret["registry_group"]=Json::Value();
    }
    if(getRegistryKey())
    {
        ret["registry_key"]=getValueOfRegistryKey();
    }
    else
    {
        ret["registry_key"]=Json::Value();
    }
    if(getRegistryValue())
    {
        ret["registry_value"]=getValueOfRegistryValue();
    }
    else
    {
        ret["registry_value"]=Json::Value();
    }
    if(getUpdateTime())
    {
        ret["update_time"]=getUpdateTime()->toDbStringLocal();
    }
    else
    {
        ret["update_time"]=Json::Value();
    }
    return ret;
}

Json::Value XxlJobRegistry::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getRegistryGroup())
            {
                ret[pMasqueradingVector[1]]=getValueOfRegistryGroup();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getRegistryKey())
            {
                ret[pMasqueradingVector[2]]=getValueOfRegistryKey();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getRegistryValue())
            {
                ret[pMasqueradingVector[3]]=getValueOfRegistryValue();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getUpdateTime())
            {
                ret[pMasqueradingVector[4]]=getUpdateTime()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getRegistryGroup())
    {
        ret["registry_group"]=getValueOfRegistryGroup();
    }
    else
    {
        ret["registry_group"]=Json::Value();
    }
    if(getRegistryKey())
    {
        ret["registry_key"]=getValueOfRegistryKey();
    }
    else
    {
        ret["registry_key"]=Json::Value();
    }
    if(getRegistryValue())
    {
        ret["registry_value"]=getValueOfRegistryValue();
    }
    else
    {
        ret["registry_value"]=Json::Value();
    }
    if(getUpdateTime())
    {
        ret["update_time"]=getUpdateTime()->toDbStringLocal();
    }
    else
    {
        ret["update_time"]=Json::Value();
    }
    return ret;
}

bool XxlJobRegistry::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("registry_group"))
    {
        if(!validJsonOfField(1, "registry_group", pJson["registry_group"], err, true))
            return false;
    }
    else
    {
        err="The registry_group column cannot be null";
        return false;
    }
    if(pJson.isMember("registry_key"))
    {
        if(!validJsonOfField(2, "registry_key", pJson["registry_key"], err, true))
            return false;
    }
    else
    {
        err="The registry_key column cannot be null";
        return false;
    }
    if(pJson.isMember("registry_value"))
    {
        if(!validJsonOfField(3, "registry_value", pJson["registry_value"], err, true))
            return false;
    }
    else
    {
        err="The registry_value column cannot be null";
        return false;
    }
    if(pJson.isMember("update_time"))
    {
        if(!validJsonOfField(4, "update_time", pJson["update_time"], err, true))
            return false;
    }
    return true;
}
bool XxlJobRegistry::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                        const std::vector<std::string> &pMasqueradingVector,
                                                        std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool XxlJobRegistry::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("registry_group"))
    {
        if(!validJsonOfField(1, "registry_group", pJson["registry_group"], err, false))
            return false;
    }
    if(pJson.isMember("registry_key"))
    {
        if(!validJsonOfField(2, "registry_key", pJson["registry_key"], err, false))
            return false;
    }
    if(pJson.isMember("registry_value"))
    {
        if(!validJsonOfField(3, "registry_value", pJson["registry_value"], err, false))
            return false;
    }
    if(pJson.isMember("update_time"))
    {
        if(!validJsonOfField(4, "update_time", pJson["update_time"], err, false))
            return false;
    }
    return true;
}
bool XxlJobRegistry::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                      const std::vector<std::string> &pMasqueradingVector,
                                                      std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool XxlJobRegistry::validJsonOfField(size_t index,
                                      const std::string &fieldName,
                                      const Json::Value &pJson,
                                      std::string &err,
                                      bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 50)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 50)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 255)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 255)";
                return false;
            }

            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 255)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 255)";
                return false;
            }

            break;
        case 4:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
