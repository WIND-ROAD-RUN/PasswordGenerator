#include "accountStoreSaveInTxt.h"
#include<iostream>
#include<algorithm>
#include<fstream>

AccountStoreSaveInTxt* AccountStoreSaveInTxt::my_instance = nullptr;

void AccountStoreSaveInTxt::ini_accountTable()
{
     if (!m_accountTable.empty()) {
        m_accountTable.clear();
    }
    std::ifstream m_file;
    m_file.open(m_fileName,std::ios::in);
    if (!m_file.is_open()) {
        std::ofstream file(m_fileName);
        file.close();
        m_file.open(m_fileName, std::ios::in);
    }
    else {
        std::string line{};
        int i{ 0 };
        Account account{};
        while (std::getline(m_file, line)) {
            if (i % 2==0) {
                account.account = line;
                ++i;
            }
            else {
                account.password = line;
                m_accountTable.push_back(account);
                ++i;
            }
        }
    }
    m_file.close();
}

void AccountStoreSaveInTxt::clear_registTable()
{
    m_accountTable.clear();
    std::ofstream file(m_fileName, std::ios::out);
    file.close();
}

bool AccountStoreSaveInTxt::search_account(const std::string& account)
{
    auto result = std::find_if(
        m_accountTable.begin(),
        m_accountTable.end(),
        [account](const Account& item) {
            if (item.account == account) { return true; }
            else { return false; }
        });
    if (result == m_accountTable.end()) {
        return false;
    }
    else {
        return true;
    }
}

void AccountStoreSaveInTxt::save_account(const std::string& account, const std::string& password)
{
    std::ofstream file(m_fileName, std::ios::out | std::ios::app);
    file << account << std::endl;
    file << password << std::endl;

    Account maccount{};
    maccount.account = account;
    maccount.password = password;
    m_accountTable.push_back(maccount);
    file.close();
}

bool AccountStoreSaveInTxt::save_account_exceptExist(const std::string& account, const std::string& password)
{
    if (search_account(account)) {
        return false;
    }
    else {
        save_account(account, password);
        return true;
    }
}

bool AccountStoreSaveInTxt::check_password(const std::string& account, const std::string& password)
{
    auto iter = std::find_if(
        m_accountTable.begin(),
        m_accountTable.end(),
        [account, password](const Account& item) {
            if (item.account == account && item.password == password) { return true; }
            else { return false; }
        });
    if (iter == m_accountTable.end()) { return false; }
    else { return true; }
}

