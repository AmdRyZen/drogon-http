//
// Created by 天使之王·彦 on 2021/11/13.
//

#include "../TrieService.h"
#include "fstream"
#include "iostream"

const wchar_t kEndFlag = L'ﾰ';  // unicode: FFB0

TrieNode::TrieNode() = default;

TrieNode::~TrieNode()
{
    for (auto i : subNodes_)
    {
        delete i.second;
    }
    subNodes_.clear();
}

TrieService::TrieService()
{
    root_ = new TrieNode();
}

TrieService::~TrieService()
{
    delete root_;
    root_ = nullptr;
}

void TrieService::insert(const std::wstring& word)
{
    TrieNode* curNode = root_;
    for (wchar_t code : word)
    {
        int unicode = SbcConvertService::charConvert(code);
        TrieNode* subNode = curNode->getSubNode(unicode);

        if (subNode == nullptr)
        {
            subNode = new TrieNode();
            curNode->addSubNode(unicode, subNode);
        }
        curNode = subNode;
    }
    int unicode = SbcConvertService::charConvert(kEndFlag);
    curNode->addSubNode(unicode, new TrieNode());
}

bool TrieService::search(const std::wstring& word)
{
    bool is_contain = false;
    for (size_t i = 0; i < word.length(); ++i)
    {
        int wordLen = getSensitiveLength(word, i);
        if (wordLen > 0)
        {
            is_contain = true;
            break;
        }
    }
    return is_contain;
}

bool TrieService::startsWith(const std::wstring& prefix)
{
    TrieNode* curNode = root_;
    for (wchar_t item : prefix)
    {
        int unicode = SbcConvertService::charConvert(item);
        curNode = curNode->getSubNode(unicode);
        if (curNode == nullptr)
        {
            return false;
        }
    }
    return true;
}

std::set<SensitiveWord> TrieService::getSensitive(const std::wstring& word)
{
    std::set<SensitiveWord> sensitiveSet;
    for (size_t i = 0; i < word.length(); ++i)
    {
        int wordLen = getSensitiveLength(word, i);
        if (wordLen > 0)
        {
            std::wstring sensitiveWord = word.substr(i, wordLen);
            SensitiveWord wordObj;
            wordObj.word = sensitiveWord;
            wordObj.startIndex = i;
            wordObj.len = wordLen;

            sensitiveSet.insert(wordObj);
            i = i + wordLen - 1;
        }
    }
    return sensitiveSet;
}

int TrieService::getSensitiveLength(std::wstring word, int startIndex)
{
    TrieNode* p1 = root_;
    int wordLen = 0;
    bool endFlag = false;
    for (size_t p3 = startIndex; p3 < word.length(); ++p3)
    {
        int unicode = SbcConvertService::charConvert(word[p3]);
        auto subNode = p1->getSubNode(unicode);
        if (subNode == nullptr)
        {
            // 如果是停顿词，直接往下继续查找
            if (stop_words_.find(unicode) != stop_words_.end())
            {
                ++wordLen;
                continue;
            }
            break;
        }
        else
        {
            ++wordLen;
            // 直到找到尾巴的位置，才认为完整包含敏感词
            if (subNode->getSubNode(SbcConvertService::charConvert(kEndFlag)))
            {
                endFlag = true;
                break;
            }
            else
            {
                p1 = subNode;
            }
        }
    }
    // 注意，处理一下没找到尾巴的情况
    if (!endFlag)
    {
        wordLen = 0;
    }
    return wordLen;
}

std::wstring TrieService::replaceSensitive(const std::wstring& word)
{
    std::set<SensitiveWord> words = getSensitive(word);
    std::wstring ret = word;
    for (auto& item : words)
    {
        for (int i = item.startIndex; i < (item.startIndex + item.len); ++i)
        {
            ret[i] = L'👀';
        }
    }
    return ret;
}

void TrieService::loadFromFile(const std::string& file_name)
{
    std::ifstream ifs(file_name, std::ios_base::in);
    std::string str;
    int count = 0;
    while (getline(ifs, str))
    {
        std::wstring utf8_str = SbcConvertService::s2ws(str);
        insert(utf8_str);
        count++;
    }
    std::cout << "load " << count << " words" << std::endl;
}

void TrieService::loadStopWordFromFile(const std::string& file_name)
{
    std::ifstream ifs(file_name, std::ios_base::in);
    std::string str;
    int count = 0;
    while (getline(ifs, str))
    {
        std::wstring utf8_str = SbcConvertService::s2ws(str);
        if (utf8_str.length() == 1)
        {
            stop_words_.insert(utf8_str[0]);
            count++;
        }
        else if (utf8_str.empty())
        {
            stop_words_.insert(L' ');
            count++;
        }
    }
    std::cout << "load " << count << " stop words" << std::endl;
}

void TrieService::loadStopWordFromMemory(std::unordered_set<wchar_t>& words)
{
    for (auto& str : words)
    {
        int unicode = SbcConvertService::charConvert(str);
        stop_words_.emplace(unicode);
    }
}

void TrieService::loadFromMemory(std::unordered_set<std::wstring>& words)
{
    for (auto& item : words)
    {
        insert(item);
    }
}
