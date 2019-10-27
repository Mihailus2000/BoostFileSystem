//
// Created by mihail on 26.10.2019.
//

#include <iostream>
#include "BrokerResolver.h"
#include <boost/lexical_cast.hpp>
BrokerResolver::BrokerResolver(fs::path path) : _inputPath(path){
    FileSystemResearch(_inputPath);
    Output();
}

void BrokerResolver::FileSystemResearch(fs::path path) {
    try {
        for(const auto& currentPath : fs::recursive_directory_iterator(path)) {
            fs::path resolved = fs::canonical(currentPath);
            if (fs::exists(currentPath)) {
                if (fs::is_regular_file(currentPath)) {

                    std::optional<AccountInfo> fileNameInfo = CheckFileName(currentPath.path());
                    if(!fileNameInfo)
                        continue;
                    else{
                        if(storage.find(fileNameInfo.value().brockerName) != storage.end()){
                            auto* brokerData = &storage[fileNameInfo.value().brockerName];
                            if((*brokerData).find(fileNameInfo.value().account) != brokerData->end()){
                                fileNameInfo.value().numFiles = ++ (*brokerData)[fileNameInfo.value().account].numFiles;
                                if(fileNameInfo.value().date > (*brokerData)[fileNameInfo.value().account].date){
                                     (*brokerData).erase(fileNameInfo.value().account);
                                    (*brokerData).insert(std::pair<std::string, AccountInfo>(fileNameInfo.value().account, fileNameInfo.value()));
                                }
                            }
                            else{
                                (*brokerData).insert(std::pair<std::string, AccountInfo>(fileNameInfo.value().account, fileNameInfo.value()));
                            }
                        }
                        else{
                            std::map<std::string, AccountInfo> tmp;
                            tmp.insert(std::pair(fileNameInfo.value().account, fileNameInfo.value()));
                            storage.insert(std::pair(fileNameInfo.value().brockerName,std::move(tmp)));
                        }
                    }
                }
                if (fs::is_symlink(currentPath)) {
                    FileSystemResearch(currentPath);
                }
            }
        }
    }
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << ex.what() << '\n';
    }
    catch (const std::exception &exc){
        std::cerr << exc.what() << '\n';
    }

}
std::string FindDirectoryName(std::string path){
    return path.substr(path.find_last_of("/\\")+1);
}
std::optional<BrokerResolver::AccountInfo> BrokerResolver::CheckFileName(fs::path checkingPath) {
    boost::smatch result;
    std::string filename = checkingPath.filename().c_str();
    if(boost::regex_match(filename, result, _checker)){
        AccountInfo info;
        for (size_t i = 1; i < 4; ++i) {
            boost::ssub_match sub_match = result[i];
            switch (i){
                case 1:
                    info.brockerName = FindDirectoryName(checkingPath.parent_path().string());
                    break;
                case 2:
                    info.account = sub_match.str();
                    break;
                case 3:
                    info.date = sub_match.str();
                    break;
            }
        }
        std::cout << info.brockerName << " " << checkingPath.filename().string() << "\n";
        return std::move(info);
    }
    else{
        return std::nullopt;
    }
}

void BrokerResolver::Output() {
    std::cout << "\n\n\t-------------------------FIND-------------------------:\n";
    for(auto broker : storage){
        for(auto account : broker.second){
            std::cout << "\tbroker:" << broker.first << " "
                      << "account:" << account.first << " "
                      << "files:" << account.second.numFiles << " "
                      << "lastdate:" << account.second.date << std::endl;
        }
    }
}
