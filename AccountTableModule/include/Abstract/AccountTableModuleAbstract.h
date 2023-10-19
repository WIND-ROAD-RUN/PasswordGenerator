#ifndef ACCOUNTTABLEMODULEABSTRACT_H_
#define ACCOUNTTABLEMODULEABSTRACT_H_

#include"NameDefineForAbstract.h"

class AccountTableModuleAbstract {
public:
    /*ģ���㷨*/
    ErrorAccountTableModule
        NewAccountInfo(const ATMAstring& platform, const ATMAstring& account);
public:
    virtual ErrorAccountTableModule
        NewAccountTable(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        NewPlatform(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        ini_module()=0;//������ʼ���࣬��·���Ƿ���󣬻���Ŀ�������Ƿ����
protected:
    /*�½��ڵ�*/
    virtual ErrorAccountTableModule 
        NewAccount(const ATMAstring& platform, const ATMAstring& account) = 0;

    inline virtual ErrorAccountTableModule 
        NewPassword()=0;

    inline virtual ErrorAccountTableModule 
        NewPhoneNumber()=0;

    inline virtual ErrorAccountTableModule 
        NewUser()=0;

    
    inline virtual ErrorAccountTableModule 
        NewEncrpyProperty()=0;

    /*���½ڵ�����ڽڵ�EncrpyProperty��*/
    inline virtual ErrorAccountTableModule 
        NewPasswordLength()=0;/*����ڵ�Ӧ�ð����������Էֱ������ֵ�Լ���Сֵ*/

    inline virtual ErrorAccountTableModule 
        NewhaveSpecialSymbols()=0;

    inline virtual ErrorAccountTableModule 
        NewhaveUppercaseLowercase()=0;

    inline virtual ErrorAccountTableModule 
        NewEncrpyIsIrreversible()=0;

public:
    /*����Ԫ��ֵ*/
    virtual ErrorAccountTableModule 
        setAccount(const ATMAstring& platform, const ATMAstring& account)=0;

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


};


#endif // !ACCOUNTTABLEMODULEABSTRACT_H_

