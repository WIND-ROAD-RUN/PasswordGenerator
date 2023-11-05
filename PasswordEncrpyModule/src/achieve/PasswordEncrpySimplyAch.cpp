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
    return toHex(ivData + encryptedData);
}

std::string PasswordEncrpySimplyAch::decryptAES(const std::string& ciphertext, const std::string& key)
{
    // 提取初始化向量和加密后的数据
    std::string hexData = fromHex(ciphertext);
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

std::string PasswordEncrpySimplyAch::toHex(const std::string& input)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char c : input) {
        ss << std::setw(2) << static_cast<int>(c);
    }
    return ss.str();
}

std::string PasswordEncrpySimplyAch::fromHex(const std::string& input)
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

AccountInfo PasswordEncrpySimplyAch::encrpyForSave(const AccountInfo& accountInfo)
{
    AccountInfo result = accountInfo;
    result.password = encryptAES(accountInfo.password,m_key);
    return result;
}

AccountInfo PasswordEncrpySimplyAch::decrptForUser(const AccountInfo& accountInfo)
{
    AccountInfo result = accountInfo;
    result.password = decryptAES(accountInfo.password, m_key);
    return result;
}

void PasswordEncrpySimplyAch::encrpy_PasswordLength(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_haveSpecialSymbols(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_haveUppercaseLowercase(AccountInfo& accountInfo)
{
}

void PasswordEncrpySimplyAch::encrpy_EncrpyIsIrreversible(AccountInfo& accountInfo)
{
    accountInfo.password = accountInfo.accountName;
}
