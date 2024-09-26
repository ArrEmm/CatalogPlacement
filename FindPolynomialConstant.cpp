#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
#include <json/json.h> 


long long ValueOfY(const std::string &value, int base) {
    return std::stoll(value, nullptr, base);
}

double ValueOfPolynomialConstantLagrangeInterpolation(const std::vector<std::pair<int, long long>> &pairs, int k) {
    double result = 0.0;
    
    for (int i = 0; i < k; ++i) {
        double term = pairs[i].second;
        
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - pairs[j].first) / double(pairs[i].first - pairs[j].first);
            }
        }
        
        result += term;
    }
    
    return result;
}

int main() {
    std::string filePath = "polynomial_roots.json";


    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filePath << std::endl;
        return 1;
    }


    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    
    if (!Json::parseFromStream(builder, file, &root, &errs)) {
        std::cerr << "Failed to parse the JSON file: " << errs << std::endl;
        return 1;
    }
    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();
    
    std::vector<std::pair<int, long long>> pairs;
    
    for (Json::Value::const_iterator it = root.begin(); it != root.end(); ++it) {
        if (it.name() != "keys") {
            int x = std::stoi(it.name());
            int base = (*it)["base"].asInt();
            std::string value = (*it)["value"].asString();
            
            long long y = ValueOfY(value, base);
            
            pairs.push_back({x, y});
        }
    }

    double c = ValueOfPolynomialConstantLagrangeInterpolation(pairs, k);
    
    std::cout << "The constant c is: " << std::fixed << std::setprecision(0) << c << std::endl;
    
    return 0;
}
