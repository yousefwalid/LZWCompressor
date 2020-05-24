#include "LZW.cpp"
#include <ctime>
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
    std::ifstream original("enwik8");
    std::ofstream encoded("bin", std::ios::binary);
    std::cout << "Encoding.." << std::endl;

    clock_t startTime = clock();
    compressor.encode(original, encoded);
    std::cout << "Finished encoding, took " << double(clock() - startTime) << " s. " << std::endl;

    calculateStatisticsASCII("enwik8", "bin");

    std::ifstream encodedStream("bin", std::ios::binary);
    std::ofstream decoded("dec_enwik8");
    std::cout << "Decoding.." << std::endl;

    startTime = clock();
    compressor.decode(encodedStream, decoded);
    std::cout << "Finished decoding, took " << double(clock() - startTime) << " s. " << std::endl;
}