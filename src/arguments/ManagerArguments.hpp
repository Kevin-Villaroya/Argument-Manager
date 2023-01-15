#ifndef _MANAGER_ARGUMENTS_H_
#define _MANAGER_ARGUMENTS_H_

#include <vector>
#include <string>
#include <stdexcept>
#include <optional>
#include <sstream>

struct NoValueType{};

class ManagerArguments{
    private:
        std::vector<std::pair<std::string, std::optional<std::string>>> listArgs;

    public:
        ManagerArguments(int argc, char* argv[]){
            listArgs.resize(argc);

            initListArgs(argc, argv);
        }

        void checkRequiredArgument(const std::string& name){
            if(!contains(name)){
                throw std::invalid_argument(name + " is required");
            }
        }

        void launchMethod(const std::string& name){
            
        }

        bool contains(const std::string& name){
            for(unsigned int i = 0; i < listArgs.size(); i++){
                if(listArgs[i].first.compare(name) == 0){
                    return true;
                }
            }

            return false;
        }

        template<typename T>
        T getValue(const std::string& name){
            for(unsigned int i = 0; i < listArgs.size(); i++){
                if(listArgs[i].first.compare(name) == 0){
                    if(listArgs[i].second.has_value()){
                        return castString<T>(listArgs[i].second.value());
                    }else{
                        throw std::invalid_argument("The value of " + name + " doesn't exist");
                    }
                    
                }
            }

            throw std::invalid_argument(name + " doesn't exist");
        }


    private:
        template<typename T>
        T castString(const std::string& value){
            std::istringstream ss(value);
            T result;
            ss >> result;

            return result;
        }

        void initListArgs(int argc, char* argv[]){
            int index = 1;

            while(index < argc){
                if(isArgumentParameter(argv[index])){
                    std::string key = argv[index];
                    std::optional<std::string> value;
                    
                    if(index + 1 < argc && !isArgumentParameter(argv[index + 1])){
                        value = argv[index + 1];
                    }

                    listArgs.push_back(std::pair<std::string, std::optional<std::string>>(key, value));
                    index++;
                }

                index++;
            }
        }

        bool isArgumentParameter(const std::string& name){
            return std::string(name).compare(0, 1, std::string("-")) == 0;
        }
};

#endif