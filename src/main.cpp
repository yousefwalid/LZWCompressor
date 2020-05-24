#include "LZW.cpp"
#include <ctime>
#include <chrono>
void calculateStatisticsASCII(const char *inputFile, const char *outputFile)
{
    FILE *file;
    file = fopen(inputFile, "r");
    fseek(file, 0, SEEK_END);
    int inputSize = ftell(file);
    fclose(file);

    file = fopen(outputFile, "r");
    fseek(file, 0, SEEK_END);
    int outputSize = ftell(file);
    fclose(file);

    std::cout << '\n'
              << "Size before encoding: " << inputSize << " byte(s)\n"
              << "Size after encoding: " << outputSize << " byte(s)\n"
              << "Compression ratio = " << (double)(inputSize) / (double)(outputSize) << "\n\n";
}

int main()
{
    LZW compressor;
    std::ifstream original("enwik8", std::ios::binary);
    std::ofstream encoded("bin", std::ios::binary);
    std::cout << "Encoding.." << std::endl;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    compressor.encode(original, encoded);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished encoding, took " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " s. " << std::endl;

    calculateStatisticsASCII("enwik8", "bin");

    std::ifstream encodedStream("bin", std::ios::binary);
    std::ofstream decoded("dec_enwik8", std::ios::binary);
    std::cout << "Decoding.." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    compressor.decode(encodedStream, decoded);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished decoding, took " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " s. " << std::endl;
}