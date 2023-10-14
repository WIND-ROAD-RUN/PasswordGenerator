#ifndef CONFIGURATIONLOADERABSTRACT_H_
#define CONFIGURATIONLOADERABSTRACT_H_

class ConfigurationLoaderAbstract {
public:
    virtual bool loadConfig() = 0;
    virtual bool storeConfig() = 0;
};

#endif // !CONFIGURATIONLOADER_H_

