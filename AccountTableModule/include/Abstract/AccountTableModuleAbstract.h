#ifndef ACCOUNTTABLEMODULEABSTRACT_H_
#define ACCOUNTTABLEMODULEABSTRACT_H_

#include"NameDefineForAbstract.h"

class AccountTableModuleAbstract {
public:
    /*模板算法*/
    ErrorAccountTableModule
        NewAccountInfo(const ATMAstring& platform, const ATMAstring& account);
public:
    virtual ErrorAccountTableModule
        NewAccountTable(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        NewPlatform(const ATMAstring& fileName) = 0;

    virtual ErrorAccountTableModule
        ini_module()=0;//用来初始化类，看路径是否错误，或是目标数据是否存在
protected:
    /*新建节点*/
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

    /*以下节点包含在节点EncrpyProperty中*/
    inline virtual ErrorAccountTableModule 
        NewPasswordLength()=0;/*这个节点应该包含两个属性分别是最大值以及最小值*/

    inline virtual ErrorAccountTableModule 
        NewhaveSpecialSymbols()=0;

    inline virtual ErrorAccountTableModule 
        NewhaveUppercaseLowercase()=0;

    inline virtual ErrorAccountTableModule 
        NewEncrpyIsIrreversible()=0;

public:
    /*设置元素值*/
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

