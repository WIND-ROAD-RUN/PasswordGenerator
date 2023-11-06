#include "PasswordEncrpySimplyAch.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include<sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string PasswordEncrpySimplyAch::encryptAES(const std::string& plaintext, const std::string& key)
{
    // 设置密钥和初始化向量
    unsigned char iv[EVP_MAX_IV_LENGTH];
    RAND_bytes(iv, EVP_MAX_IV_LENGTH);

    // 创建并初始化加密上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)key.c_str(), iv);

    // 计算加密后的数据长度
    int ciphertext_len = plaintext.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[ciphertext_len];

    // 执行加密操作
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char*)plaintext.c_str(), plaintext.length());
    ciphertext_len = len;

    // 结束加密操作
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // 清理加密上下文
    EVP_CIPHER_CTX_free(ctx);

    // 将加密后的数据和初始化向量转换为十六进制的string类型
    std::string encryptedData(reinterpret_cast<char*>(ciphertext), ciphertext_len);
    std::string ivData(reinterpret_cast<char*>(iv), EVP_MAX_IV_LENGTH);

    delete[] ciphertext;

    // 返回加密后的数据和初始化向量的十六进制表示
    return toHex_forString(ivData + encryptedData);
}

std::string PasswordEncrpySimplyAch::decryptAES(const std::string& ciphertext, const std::string& key)
{
    // 提取初始化向量和加密后的数据
    std::string hexData = fromHex_forString(ciphertext);
    std::string ivData = hexData.substr(0, EVP_MAX_IV_LENGTH);
    std::string encryptedData = hexData.substr(EVP_MAX_IV_LENGTH);

    // 创建并初始化解密上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)key.c_str(), (const unsigned char*)ivData.c_str());

    // 计算解密后的数据长度
    int plaintext_len = encryptedData.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* plaintext = new unsigned char[plaintext_len];

    // 执行解密操作
    int len;
    EVP_DecryptUpdate(ctx, plaintext, &len, (const unsigned char*)encryptedData.c_str(), encryptedData.length());
    plaintext_len = len;

    // 结束解密操作
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    // 清理解密上下文
    EVP_CIPHER_CTX_free(ctx);

    // 将解密后的数据转换为string类型
    std::string decryptedData(reinterpret_cast<char*>(plaintext), plaintext_len);

    delete[] plaintext;

    // 返回解密后的数据
    return decryptedData;
}

std::string PasswordEncrpySimplyAch::toHex_forString(const std::string& input)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char c : input) {
        ss << std::setw(2) << static_cast<int>(c);
    }
    return ss.str();
}

std::string PasswordEncrpySimplyAch::fromHex_forString(const std::string& input)
{
    std::string output;
    output.reserve(input.length() / 2);
    for (std::size_t i = 0; i < input.length(); i += 2) {
        std::string byteString = input.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        output.push_back(byte);
    }
    return output;
}

std::string PasswordEncrpySimplyAch::getHash(const std::string& data)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    ss << std::hex << std::uppercase;

    for (int i = 0; i < 32; i++) {
        ss << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string PasswordEncrpySimplyAch::combineHash(const std::string& first, const std::string second)
{
    return getHash(first + second);
}

std::vector<uint32_t> PasswordEncrpySimplyAch::hashToVector(const std::string& hexString)
{
    std::vector<uint32_t> result;
    for (size_t i = 0; i < hexString.size(); i += 8) {
        std::stringstream ss;
        ss << std::hex << hexString.substr(i, 8);
        uint32_t value;
        ss >> value;
        result.push_back(value);
    }
    return result;
}

std::string PasswordEncrpySimplyAch::getPasswordPart(uint32_t value, const std::string& characterSet)
{
    std::string result;
    while (value > 0) {
        int index = value % characterSet.length();
        result += characterSet[index];
        value /= characterSet.length();
    }
    return result;
}

std::string PasswordEncrpySimplyAch::getSpecialSymbols(uint32_t value)
{
    std::string characterSet = R"(!@#$%^&*)";
    return getPasswordPart(value, characterSet);
}

std::string PasswordEncrpySimplyAch::getNumber(uint32_t value)
{
    std::string characterSet = R"(192837465)";
    return getPasswordPart(value, characterSet);
}

std::string PasswordEncrpySimplyAch::getSmallLetter(uint32_t value)
{
    std::string characterSet = R"(abcdefghijklmnopqrstuvwxyz)";
    return getPasswordPart(value, characterSet);
}

std::string PasswordEncrpySimplyAch::getBigLetter(uint32_t value)
{
    std::string characterSet = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
    return getPasswordPart(value, characterSet);
}

std::string PasswordEncrpySimplyAch::getBigAndSmallLetter(uint32_t forSmall, uint32_t forBig)
{
    std::string result;
    auto small = getSmallLetter(forSmall);
    auto big = getBigLetter(forBig);
    int i = 0;
    while (i != small.size() && i != big.size()) {
        result += small[i];
        result += big[i];
        i++;
    }
    return result;
}

AccountInfo PasswordEncrpySimplyAch::encrptForSave(const AccountInfo& accountInfo)
{
    AccountInfo result = accountInfo;
    encrptForSave(result);
    return result;
}

void PasswordEncrpySimplyAch::encrptForSave(AccountInfo& accountInfo) {
    accountInfo.password = encryptAES(accountInfo.password, m_key);
}

AccountInfo PasswordEncrpySimplyAch::decrptForUser(const AccountInfo& accountInfo)
{
    AccountInfo result = accountInfo;
    decrptForUser(result);
    return result;
}

void PasswordEncrpySimplyAch::decrptForUser(AccountInfo& accountInfo) {
    accountInfo.password= decryptAES(accountInfo.password, m_key);
}

void PasswordEncrpySimplyAch::encrpt_PasswordLength(AccountInfo& accountInfo)
{
    std::string numberStr1 = getNumber(hashToVector(m_passwordHash)[3]);
    std::string numberStr2 = getNumber(hashToVector(m_passwordHash)[4]);
    m_passwordSrc.push_back(numberStr1);
    m_passwordSrc.push_back(numberStr2);
}

void PasswordEncrpySimplyAch::encrpt_haveSpecialSymbols(AccountInfo& accountInfo)
{
    std::string specailSymbols{};
    if (accountInfo.haveSpecialSymbols) {
        specailSymbols = getSpecialSymbols(hashToVector(m_passwordHash)[0]);
    }
    m_passwordSrc.push_back(specailSymbols);
}

void PasswordEncrpySimplyAch::encrpt_haveUppercaseLowercase(AccountInfo& accountInfo)
{
    std::string letterSymbols;
    if (accountInfo.haveUppercaseLowercase) {
        letterSymbols = getBigAndSmallLetter(hashToVector(m_passwordHash)[1], hashToVector(m_passwordHash)[2]);
    }
    else {
        letterSymbols = getSmallLetter(hashToVector(m_passwordHash)[1]);
    }
    m_passwordSrc.push_back(letterSymbols);
}

void PasswordEncrpySimplyAch::encrpt_EncrpyIsIrreversible(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpt_build_hash(AccountInfo& accountInfo)
{
    m_passwordHash = getHash(m_key);
    m_passwordHash = getHash(accountInfo.accountName);
    if (!accountInfo.phoneNumber.empty()) {
        m_passwordHash = combineHash(m_passwordHash,getHash(accountInfo.phoneNumber));
    }
    if (!accountInfo.User.empty()) {
        m_passwordHash = combineHash(m_passwordHash, getHash(accountInfo.User));
    }
}
