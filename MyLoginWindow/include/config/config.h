#ifndef CONFIG_H_
#define CONFIG_H_

#include"ConfigurationLoader-XML.h"
#include"LocalizationStringLoader-XML.h"

/*配置文件路径*/
#define PROGRAMMEDATAPATH R"(C:\ProgramData\PasswordManager)";//软件数据根目录
#define CONFIGPATH R"(C:\ProgramData\PasswordManager\config\config.xml)"//配置文件目录
#define ACCOUNTTABLEPATH R"(C:\ProgramData\PasswordManager\config\account.xml)"//注册账户目录
#define DATABASEPATH R"(C:\ProgramData\PasswordManager\database)"//账户密码本存储路径

#endif // !CONFIG_H_
