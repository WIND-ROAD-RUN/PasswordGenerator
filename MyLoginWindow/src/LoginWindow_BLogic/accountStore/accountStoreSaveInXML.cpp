#include "accountStoreSaveInXML.h"

AccountStoreSaveInXML* AccountStoreSaveInXML::my_instance = nullptr;

void AccountStoreSaveInXML::ini_accountTable()
{
    m_doc.load_file(m_accountFilePath.c_str());
    auto accountTableNode = m_doc.child("accountTable");
    for (const auto & accountNode:accountTableNode.children()) {
        Account account;
        account.account = accountNode.attribute("id").value();
        account.password = accountNode.text().get();
        m_accountTable.push_back(std::move(account));
    }
}

void AccountStoreSaveInXML::clear_registTable()
{
    m_accountTable.clear();
    auto accountTable=m_doc.child("accountTable");
    accountTable.remove_children();
    m_doc.save_file(m_accountFilePath.c_str());
}

bool AccountStoreSaveInXML::search_account(const std::string& account)
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

void AccountStoreSaveInXML::save_account(const std::string& account, const std::string& password)
{
    auto accountTableNode = m_doc.child("accountTable");
    auto newAccountNode=accountTableNode.append_child();
    auto newAttribute = newAccountNode.append_attribute("id");
    newAccountNode.set_name("account");
    newAttribute.set_value(account.c_str());
    newAccountNode.text().set(password.c_str());
    m_doc.save_file(m_accountFilePath.c_str());

    Account maccount{};
    maccount.account = account;
    maccount.password = password;
    m_accountTable.push_back(maccount);
}

bool AccountStoreSaveInXML::save_account_exceptExist(const std::string& account, const std::string& password)
{
    if (search_account(account)) {
        return false;
    }
    else {
        save_account(account, password);
        return true;
    }
}

bool AccountStoreSaveInXML::check_password(const std::string& account, const std::string& password)
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
