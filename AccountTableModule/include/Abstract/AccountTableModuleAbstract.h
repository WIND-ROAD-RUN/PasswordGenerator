#ifndef ACCOUNTTABLEMODULEABSTRACT_H_
#define ACCOUNTTABLEMODULEABSTRACT_H_

#include"NameDefineForAbstract.h"

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

    /*����Ԫ��ֵ*/
    virtual ErrorAccountTableModule 
        setAccount(const ATMAstring& platform, const ATMAstring& orginalAccount,const ATMAstring & newAccount)=0;

    virtual ErrorAccountTableModule 
        setPassword(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& password)=0;

    virtual ErrorAccountTableModule 
        setPhoneNumber(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& phoneNumber)=0;

    virtual ErrorAccountTableModule 
        setUser(const ATMAstring& platform, const ATMAstring& account, const ATMAstring& user)=0;


    virtual ErrorAccountTableModule 
        setEncrpyProperty(const ATMAstring& platform, const ATMAstring& account)=0;

    virtual ErrorAccountTableModule 
        setPasswordLength(const ATMAstring& platform, const ATMAstring& account, ATMAint minimum, ATMAint Maximum)=0;

    virtual ErrorAccountTableModule 
        sethaveSpecialSymbols(const ATMAstring& platform, const ATMAstring& account, ATMbool haveSpecialSymbols)=0;

    virtual ErrorAccountTableModule 
        sethaveUppercaseLowercase(const ATMAstring& platform, const ATMAstring& account, ATMbool haveUppercaseLowercase)=0;

    virtual ErrorAccountTableModule 
        setEncrpyIsIrreversible(const ATMAstring& platform, const ATMAstring& account, ATMbool EncrpyIsIrreversible)=0;
    
    /*ɾ���ڵ�*/
    virtual ErrorAccountTableModule
        deletePlatform(const ATMAstring & platform)=0;
    virtual ErrorAccountTableModule
        deletePlatform(const ATMAstring & platform,const ATMAstring & account) = 0;

};


#endif // !ACCOUNTTABLEMODULEABSTRACT_H_

