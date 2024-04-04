/**
 *
 *  XxlJobUser.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "XxlJobUser.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::xxl_job;

const std::string XxlJobUser::Cols::_id = "id";
const std::string XxlJobUser::Cols::_username = "username";
const std::string XxlJobUser::Cols::_password = "password";
const std::string XxlJobUser::Cols::_role = "role";
const std::string XxlJobUser::Cols::_permission = "permission";
const std::string XxlJobUser::primaryKeyName = "id";
const bool XxlJobUser::hasPrimaryKey = true;
const std::string XxlJobUser::tableName = "xxl_job_user";

const std::vector<typename XxlJobUser::MetaData> XxlJobUser::metaData_={
{"id","int32_t","int(11)",4,1,1,1},
{"username","std::string","varchar(50)",50,0,0,1},
{"password","std::string","varchar(50)",50,0,0,1},
{"role","int8_t","tinyint(4)",1,0,0,1},
{"permission","std::string","varchar(255)",255,0,0,0}
};
const std::string &XxlJobUser::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
XxlJobUser::XxlJobUser(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["username"].isNull())
        {
            username_=std::make_shared<std::string>(r["username"].as<std::string>());
        }
        if(!r["password"].isNull())
        {
            password_=std::make_shared<std::string>(r["password"].as<std::string>());
        }
        if(!r["role"].isNull())
        {
            role_=std::make_shared<int8_t>(r["role"].as<int8_t>());
        }
        if(!r["permission"].isNull())
        {
            permission_=std::make_shared<std::string>(r["permission"].as<std::string>());
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
            username_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            password_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            role_=std::make_shared<int8_t>(r[index].as<int8_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            permission_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

XxlJobUser::XxlJobUser(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
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
            username_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            password_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            role_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            permission_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
}

XxlJobUser::XxlJobUser(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("username"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["username"].isNull())
        {
            username_=std::make_shared<std::string>(pJson["username"].asString());
        }
    }
    if(pJson.isMember("password"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["password"].isNull())
        {
            password_=std::make_shared<std::string>(pJson["password"].asString());
        }
    }
    if(pJson.isMember("role"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["role"].isNull())
        {
            role_=std::make_shared<int8_t>((int8_t)pJson["role"].asInt64());
        }
    }
    if(pJson.isMember("permission"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["permission"].isNull())
        {
            permission_=std::make_shared<std::string>(pJson["permission"].asString());
        }
    }
}

void XxlJobUser::updateByMasqueradedJson(const Json::Value &pJson,
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
            username_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            password_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            role_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            permission_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
}

void XxlJobUser::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("username"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["username"].isNull())
        {
            username_=std::make_shared<std::string>(pJson["username"].asString());
        }
    }
    if(pJson.isMember("password"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["password"].isNull())
        {
            password_=std::make_shared<std::string>(pJson["password"].asString());
        }
    }
    if(pJson.isMember("role"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["role"].isNull())
        {
            role_=std::make_shared<int8_t>((int8_t)pJson["role"].asInt64());
        }
    }
    if(pJson.isMember("permission"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["permission"].isNull())
        {
            permission_=std::make_shared<std::string>(pJson["permission"].asString());
        }
    }
}

const int32_t &XxlJobUser::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &XxlJobUser::getId() const noexcept
{
    return id_;
}
void XxlJobUser::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename XxlJobUser::PrimaryKeyType & XxlJobUser::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &XxlJobUser::getValueOfUsername() const noexcept
{
    static const std::string defaultValue = std::string();
    if(username_)
        return *username_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobUser::getUsername() const noexcept
{
    return username_;
}
void XxlJobUser::setUsername(const std::string &pUsername) noexcept
{
    username_ = std::make_shared<std::string>(pUsername);
    dirtyFlag_[1] = true;
}
void XxlJobUser::setUsername(std::string &&pUsername) noexcept
{
    username_ = std::make_shared<std::string>(std::move(pUsername));
    dirtyFlag_[1] = true;
}

const std::string &XxlJobUser::getValueOfPassword() const noexcept
{
    static const std::string defaultValue = std::string();
    if(password_)
        return *password_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobUser::getPassword() const noexcept
{
    return password_;
}
void XxlJobUser::setPassword(const std::string &pPassword) noexcept
{
    password_ = std::make_shared<std::string>(pPassword);
    dirtyFlag_[2] = true;
}
void XxlJobUser::setPassword(std::string &&pPassword) noexcept
{
    password_ = std::make_shared<std::string>(std::move(pPassword));
    dirtyFlag_[2] = true;
}

const int8_t &XxlJobUser::getValueOfRole() const noexcept
{
    static const int8_t defaultValue = int8_t();
    if(role_)
        return *role_;
    return defaultValue;
}
const std::shared_ptr<int8_t> &XxlJobUser::getRole() const noexcept
{
    return role_;
}
void XxlJobUser::setRole(const int8_t &pRole) noexcept
{
    role_ = std::make_shared<int8_t>(pRole);
    dirtyFlag_[3] = true;
}

const std::string &XxlJobUser::getValueOfPermission() const noexcept
{
    static const std::string defaultValue = std::string();
    if(permission_)
        return *permission_;
    return defaultValue;
}
const std::shared_ptr<std::string> &XxlJobUser::getPermission() const noexcept
{
    return permission_;
}
void XxlJobUser::setPermission(const std::string &pPermission) noexcept
{
    permission_ = std::make_shared<std::string>(pPermission);
    dirtyFlag_[4] = true;
}
void XxlJobUser::setPermission(std::string &&pPermission) noexcept
{
    permission_ = std::make_shared<std::string>(std::move(pPermission));
    dirtyFlag_[4] = true;
}
void XxlJobUser::setPermissionToNull() noexcept
{
    permission_.reset();
    dirtyFlag_[4] = true;
}

void XxlJobUser::updateId(const uint64_t id)
{
    id_ = std::make_shared<int32_t>(static_cast<int32_t>(id));
}

const std::vector<std::string> &XxlJobUser::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "username",
        "password",
        "role",
        "permission"
    };
    return inCols;
}

void XxlJobUser::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPassword())
        {
            binder << getValueOfPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRole())
        {
            binder << getValueOfRole();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getPermission())
        {
            binder << getValueOfPermission();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> XxlJobUser::updateColumns() const
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

void XxlJobUser::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPassword())
        {
            binder << getValueOfPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRole())
        {
            binder << getValueOfRole();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getPermission())
        {
            binder << getValueOfPermission();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value XxlJobUser::toJson() const
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
    if(getUsername())
    {
        ret["username"]=getValueOfUsername();
    }
    else
    {
        ret["username"]=Json::Value();
    }
    if(getPassword())
    {
        ret["password"]=getValueOfPassword();
    }
    else
    {
        ret["password"]=Json::Value();
    }
    if(getRole())
    {
        ret["role"]=getValueOfRole();
    }
    else
    {
        ret["role"]=Json::Value();
    }
    if(getPermission())
    {
        ret["permission"]=getValueOfPermission();
    }
    else
    {
        ret["permission"]=Json::Value();
    }
    return ret;
}

Json::Value XxlJobUser::toMasqueradedJson(
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
            if(getUsername())
            {
                ret[pMasqueradingVector[1]]=getValueOfUsername();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getPassword())
            {
                ret[pMasqueradingVector[2]]=getValueOfPassword();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getRole())
            {
                ret[pMasqueradingVector[3]]=getValueOfRole();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getPermission())
            {
                ret[pMasqueradingVector[4]]=getValueOfPermission();
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
    if(getUsername())
    {
        ret["username"]=getValueOfUsername();
    }
    else
    {
        ret["username"]=Json::Value();
    }
    if(getPassword())
    {
        ret["password"]=getValueOfPassword();
    }
    else
    {
        ret["password"]=Json::Value();
    }
    if(getRole())
    {
        ret["role"]=getValueOfRole();
    }
    else
    {
        ret["role"]=Json::Value();
    }
    if(getPermission())
    {
        ret["permission"]=getValueOfPermission();
    }
    else
    {
        ret["permission"]=Json::Value();
    }
    return ret;
}

bool XxlJobUser::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("username"))
    {
        if(!validJsonOfField(1, "username", pJson["username"], err, true))
            return false;
    }
    else
    {
        err="The username column cannot be null";
        return false;
    }
    if(pJson.isMember("password"))
    {
        if(!validJsonOfField(2, "password", pJson["password"], err, true))
            return false;
    }
    else
    {
        err="The password column cannot be null";
        return false;
    }
    if(pJson.isMember("role"))
    {
        if(!validJsonOfField(3, "role", pJson["role"], err, true))
            return false;
    }
    else
    {
        err="The role column cannot be null";
        return false;
    }
    if(pJson.isMember("permission"))
    {
        if(!validJsonOfField(4, "permission", pJson["permission"], err, true))
            return false;
    }
    return true;
}
bool XxlJobUser::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
bool XxlJobUser::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("username"))
    {
        if(!validJsonOfField(1, "username", pJson["username"], err, false))
            return false;
    }
    if(pJson.isMember("password"))
    {
        if(!validJsonOfField(2, "password", pJson["password"], err, false))
            return false;
    }
    if(pJson.isMember("role"))
    {
        if(!validJsonOfField(3, "role", pJson["role"], err, false))
            return false;
    }
    if(pJson.isMember("permission"))
    {
        if(!validJsonOfField(4, "permission", pJson["permission"], err, false))
            return false;
    }
    return true;
}
bool XxlJobUser::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool XxlJobUser::validJsonOfField(size_t index,
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
            if(pJson.isString() && pJson.asString().length() > 50)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 50)";
                return false;
            }

            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
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
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 255)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 255)";
                return false;
            }

            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
