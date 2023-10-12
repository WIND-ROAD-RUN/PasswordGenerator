#ifndef LOCALIZATIONSTRINGMODULE_H_
#define LOCALIZATIONSTRINGMODULE_H_

#include<string>

class LocalizationStringModuleAbstract {
public:

    LocalizationStringModuleAbstract() {}
    ~LocalizationStringModuleAbstract() {}

public:

    virtual std::string localString(const std::string & id,const std::string & local="CHN") = 0;

    virtual bool localString(std::string & target ,const std::string & id,const std::string & local="CHN")=0;

    virtual bool storeLocalString(const std::string & id, const std::string& local,const std::string & src) = 0;

    
};

#endif // !HEADER_LOCALIZATIONSTRINGMODULE_H_

