#ifndef LOCALIZATIONSTRINGMODULE_H_
#define LOCALIZATIONSTRINGMODULE_H_

#include<string>


/*
LocalizationStringModule类体系的抽象接口定义了本地化字符串保存的所必须的接口标准
*/



class LocalizationStringModuleAbstract {
public:

    LocalizationStringModuleAbstract() {}
    ~LocalizationStringModuleAbstract() {}

public:
    /*
    这个接口根据id和local来查询对应的本地化字符串，若查询到了应该返回一个string
    若没有查询到则返回空的string这个接口应该由virtual bool localString
    (std::string & target ,const std::string & id,const std::string & local="CHN")=0;实现
    */
    virtual std::string localString(const std::string & id,const std::string & local="CHN") = 0;
    /*
        这个接口根据id，local查询对应的本地化字符串，若查询到了将其赋值给target并返回true，若没有查询到则返回false，
        且target不应该改变。
    */
    virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0;

    virtual bool storeLocalString(const std::string & id, const std::string& local,const std::string & src) = 0;

    virtual bool loadFile()=0;
};

#endif // !HEADER_LOCALIZATIONSTRINGMODULE_H_

