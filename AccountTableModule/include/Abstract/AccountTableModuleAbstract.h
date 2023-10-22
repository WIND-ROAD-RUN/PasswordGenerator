#ifndef ACCOUNTTABLEMODULEABSTRACT_H_
#define ACCOUNTTABLEMODULEABSTRACT_H_

#include"NameDefineForATMA.h"

class AccountTableModuleAbstract {
public:
    virtual ErrorAccountTableModule
        NewAccountTable(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        NewPlatform(const ATMAstring& platform) = 0;

    virtual ErrorAccountTableModule
        ini_module()=0;//������ʼ���࣬��·���Ƿ���󣬻���Ŀ�������Ƿ����
    virtual ErrorAccountTableModule
        save() = 0;
public:
    /*�½��ڵ�*/
    virtual ErrorAccountTableModule 
        NewAccount(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ErrorAccountTableModule
        NewAccount(const ATMAstring& platform, const AccountInfo& account) = 0;

    /*����Ԫ��ֵ*/
    virtual ErrorAccountTableModule
        setAccount(const ATMAstring& platform, const AccountInfo& account) = 0;

    virtual ErrorAccountTableModule 
        setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount,const ATMAstring & newAccount)=0;

    virtual ErrorAccountTableModule 
        setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)=0;

    virtual ErrorAccountTableModule 
        setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)=0;

    virtual ErrorAccountTableModule 
        setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)=0;


    virtual ErrorAccountTableModule 
        setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint maximum)=0;

    virtual ErrorAccountTableModule 
        sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveSpecialSymbols)=0;

    virtual ErrorAccountTableModule 
        sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMAbool haveUppercaseLowercase)=0;

    virtual ErrorAccountTableModule 
        setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMAbool EncrpyIsIrreversible)=0;
    
    /*ɾ���ڵ�*/
    virtual ErrorAccountTableModule
        deletePlatform(const ATMAstring & platform)=0;
    virtual ErrorAccountTableModule
        deleteAccount(const ATMAstring & platform,const ATMAstring & account) = 0;
    /*���ض�Ӧ�ڵ����Ϣ*/
    virtual AccountInfo
        Account(const ATMAstring& platform, const ATMAstring& account) = 0;
    
    virtual ATMAstring
        Password(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAstring
        PhoneNumber(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAstring
        User(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMApair
        PasswordLength(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        haveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        haveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account) = 0;

    virtual ATMAbool
        EncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account) = 0;
    virtual ATMAStringList
        getPlatformList()=0;
    virtual ATMAAccountList
        getAccountList(const ATMAstring& platform) = 0;
};


#endif // !ACCOUNTTABLEMODULEABSTRACT_H_
