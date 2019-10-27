//
// Created by mihail on 26.10.2019.
//

#include <iostream>
#include "BrokerResolver.h"

int main(int argc, char *argv[]){
    fs::path path_to_ftp = fs::current_path();
    if(argc > 1){
        path_to_ftp = argv[1];
    }
    std::string str("balance_03934520_20180915.txt");
//    boost::regex checker{
//            R"(^(balance)_(\d{8})_([12]\d{3}(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])).txt$)"
//    };
//    boost::smatch res;
//    std::cout << "input path: " << path_to_ftp.string() << std::endl;
//    if(boost::regex_match(str, res,checker )){
//        for (size_t i = 0; i < res.size(); ++i) {
//            boost::ssub_match sub_match = res[i];
//            std::string piece = sub_match.str();
//            std::cout << "  submatch " << i << ": " << piece << '\n';
//        }
//    }
    BrokerResolver Test(path_to_ftp);
}