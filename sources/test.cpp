#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// Helper function to get a specific line from a file
std::string get_line(std::ifstream& file, int target_line) {
    file.clear();
    file.seekg(0);
    std::string line;
    for (int i = 1; std::getline(file, line); ++i) {
        if (i == target_line)
            return line;
    }
    return "";
}

// Helper function to extract value after a known prefix
std::string extract_value(const std::string& line, const std::string& prefix) {
    auto pos = line.find(prefix);
    if (pos != std::string::npos)
        return line.substr(pos + prefix.length());
    return "";
}

int main() {
    std::string directory = "C:/Docs/01 - Filip/02 - FER/060 - G3S6/00 - PROJEKT/01 - MravljiAlgoritam/01 - REZULTATI/csvExtraction";  // Change to your directory path
    std::string output_csv = "results.csv";

    std::ofstream csv_file(output_csv);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open output CSV file." << std::endl;
        return 1;
    }

    //csv_file << "sep=;\n";  // CSV header

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << entry.path() << std::endl;
                continue;
            }

            std::string line18 = get_line(file, 18);
            std::string line20 = get_line(file, 20);

            std::string fitness = extract_value(line18, "Best fitness: ");
            std::string solution = extract_value(line20, "Best solution: ");

            if (!fitness.empty() || !solution.empty()) {
                csv_file << fitness << ";" << solution << "\n";
            }
        }
    }

    csv_file.close();
    std::cout << "Extraction completed. Data saved to " << output_csv << std::endl;
    return 0;
}