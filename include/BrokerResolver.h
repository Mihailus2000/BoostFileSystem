//
// Created by mihail on 26.10.2019.
//

#ifndef LAB_04_BOOST_FILESYSTEM_BROKERRESOLVER_H
#define LAB_04_BOOST_FILESYSTEM_BROKERRESOLVER_H

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
namespace fs = boost::filesystem;

class BrokerResolver{
private:
    fs::path _inputPath;
    boost::regex _checker{
            R"(^(balance)_(\d{8})_([12]\d{3}(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])).txt$)"
    };
    enum FileType{
        BALANCE,
        OLD,
        IGNORE
    };
    struct AccountInfo{
        std::string brockerName = "";
        std::string account = "";
//        int year = 0;
//        int month = 0;
//        int day = 0;
        std::string date  ="";
int numFiles = 1;
    };


    std::map<std::string, std::map<std::string, AccountInfo >> storage;
public:
    BrokerResolver() = delete;
    explicit BrokerResolver(fs::path path);
    virtual ~BrokerResolver() = default;
    void FileSystemResearch(fs::path path);
    std::optional<AccountInfo> CheckFileName(fs::path checkingPath);
//    bool ComparisonData(const AccountInfo& existsInfo, const AccountInfo& newAccountInfo);
    void Output();
};



#endif //LAB_04_BOOST_FILESYSTEM_BROKERRESOLVER_H
