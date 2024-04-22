#include <iostream>
#include <fstream>

int main() {
    // Open a file for writing
    std::ofstream file("unique_test_words.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing" << std::endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < 10000; ++i) {
        // Increase count
        count++;

        // Write 'a' count times to the file
        for (int j = 0; j < count; ++j) {
            file << 'a';
        }

        file<<'\n';
    }

    // Close the file
    file.close();

    std::cout << "File 'output.txt' written successfully." << std::endl;

    return 0;
}