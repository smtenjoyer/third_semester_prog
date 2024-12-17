
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/crc.hpp> 

namespace fs = boost::filesystem;
namespace po = boost::program_options;


std::vector<uint32_t> calculate_file_hashes(const fs::path& filePath, size_t blockSize)
{
  // std::cout << "file_processing" << std::endl;
  if (exists(filePath))
    {
      if (is_regular_file(filePath))
      {
        std::vector<uint32_t> hashBlocks; // Вектор для хранения хэшей блоков
        std::ifstream file(filePath, std::ios::binary); // Открываем файл в бинарном режиме
        std::string buffer(blockSize, '\0'); // Буфер для чтения блоков

    while (file.read(&buffer[0], blockSize) || file.gcount() > 0) { // чтение данных из файла блоками
        // Урезаем буфер до фактического размера прочитанных данных
        size_t bytesRead = static_cast<size_t>(file.gcount()); // количество прочитанных байтов
        buffer.resize(bytesRead); // обновление размера буфера до количества прочитанных байтов
        
        // Дополняем до размера блока нулями
        if (bytesRead < blockSize) {
            buffer.resize(blockSize, '\0');
        }
        boost::crc_32_type result;
        result.process_bytes(buffer.data(), blockSize);
        // Вычисляем хэш блока и добавляем в последовательность
        uint32_t hash = result.checksum();
        hashBlocks.push_back(hash);
        }

        return hashBlocks; // Возвращаем вектор хэшей
      }
      else
        std::cout << filePath << " exists, but is not a regular file or directory\n";
        return {};
    }
    else
      std::cout << filePath << " does not exist\n";
      return {};
}

// Функция для сравнения двух файлов по их хэшам
bool are_files_identical(const std::vector<uint32_t>& hash1, const std::vector<uint32_t>& hash2) {
  // std::cout << "compare_hashes" << std::endl;
    if (hash1.size() != hash2.size()) return false; // Если размеры разные, файлы разные

    for (size_t i = 0; i < hash1.size(); ++i) {
        if (hash1[i] != hash2[i]) return false; // Если хотя бы один хэш не совпадает, файлы разные
    }

    return true; // Файлы идентичны
}

void process_file(const fs::directory_entry& entry, const std::vector<fs::path>& exclusions, size_t minSize, 
                        const boost::regex& maskRegex, size_t blockSize, std::vector<std::pair<fs::path, 
                        std::vector<uint32_t>>>& hashVector) {
    if (entry.is_regular_file()) {  
        // Проверка на исключения. если родительская директория в списке исключений, пропускаем файл
        if (std::find(exclusions.begin(), exclusions.end(), entry.path().parent_path()) != exclusions.end()) {
            return;
        }
        
        if (file_size(entry) < minSize) {
       std::cout << "File: " << entry.path() << ", Size: " << file_size(entry) << ", MinSize: " << minSize << std::endl;
       return;
   }

        // Проверка маски имени файла
        if (!boost::regex_match(entry.path().filename().string(), maskRegex)) {
            // std::cout << "wrong mask" << std::endl;
            return;
        }
        auto hashes = calculate_file_hashes(entry.path(), blockSize); 
        hashVector.emplace_back(entry.path(), hashes);   
    }
}

// Функция для поиска дубликатов
void find_duplicates(const std::vector<fs::path>& directories, const std::vector<fs::path>& exclusions, 
                      size_t blockSize, size_t minSize, boost::regex& maskRegex, int scanLevel) {
    
    std::unordered_map<std::string, std::set<fs::path>> hashMap; // Словарь для хранения путей дубликатов
    std::vector<std::pair<fs::path, std::vector<uint32_t>>> hashVector; // Вектор для хранения всех обработанных файлов и их хэшей

    for (const auto& dir : directories) {
        if (!exists(dir) || !is_directory(dir)) {
            std::cerr << "Is not a regular file or directory or does not exist" << dir << std::endl;
            continue;
        }

        
        if (scanLevel == 0) { // Только указанная директория без вложенных
            for (const auto& entry : fs::directory_iterator(dir)) {
                process_file(entry, exclusions, minSize, maskRegex, blockSize, hashVector);
                
            }
        } else { // Рекурсивное сканирование
            for (const auto& entry : fs::recursive_directory_iterator(dir)) {
                process_file(entry, exclusions, minSize, maskRegex, blockSize, hashVector);
                
            }
        }
    }
    // Сравнение хешей и добавление дубликатов в hashMap
    for (size_t i = 0; i < hashVector.size(); ++i) {
        for (size_t j = i + 1; j < hashVector.size(); ++j) {
            if (are_files_identical(hashVector[i].second, hashVector[j].second)) {  // Если файлы идентичны по хэшам
                std::string hashKey(reinterpret_cast<const char*>(hashVector[i].second.data()), hashVector[i].second.size() * sizeof(uint32_t)); // последовательность байтов из вектора хэшей
                hashMap[hashKey].insert(hashVector[i].first);
                hashMap[hashKey].insert(hashVector[j].first);
            }
        }
    }

   for (const auto& pair : hashMap) {
        if (pair.second.size() > 1) {  // Only report if there are duplicates
            std::cout << "Duplicates:\n";
            for (const auto& file : pair.second) {
                std::cout << file << "\n";
            }
            std::cout << "\n";
        }
    }
}


void start_scanning(const std::vector<fs::path>& dirs, const std::vector<fs::path>& excs, int& level, 
                    size_t& filesize, std::string& Mask, size_t& blocksize) {
    // std::cout << "start_scanning" << std::endl;
    boost::regex star_regex("\\*");
    boost::regex question_regex("\\?");
    Mask = "^" + boost::regex_replace(Mask, star_regex, ".*"); // Заменяем * на .*
    Mask = boost::regex_replace(Mask, question_regex, "."); // Заменяем ? на .
    Mask += "$"; // Добавляем конец строки

    boost::regex maskRegex(Mask, boost::regex_constants::icase); // Игнорируем регистр

      find_duplicates(dirs, excs, blocksize, filesize, maskRegex, level);

    // Здесь добавьте вашу логику для сканирования файлов
}

void on_directories(const std::vector<std::string>& dirs) {
    std::cout << "Directories to include:\n";
    for (const auto& dir : dirs) {
        std::cout << dir << "\n";
    }
    std::cout << std::endl;
}

void on_exceptions(const std::vector<std::string>& excs) {
    std::cout << "Directories to exclude: ";
    for (const auto& exc : excs) {
        std::cout << exc << " ";
    }
    std::cout << std::endl;
}


int main(int argc, const char* argv[]) {
    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Help screen")
            ("directories,d", po::value<std::vector<fs::path>>()->multitoken(), "Adding directories (e.g., --directories dir1 dir2)")
            ("exception,e", po::value<std::vector<fs::path>>()->multitoken(), "Excluding directories (e.g., --exception dir3 dir4)")
            ("level,l", po::value<int>(), "Scanning level")
            ("min_file_size,f", po::value<size_t>(), "Minimum file size")
            ("masks,m", po::value<std::string>(), "File name masks")
            ("block_size,s", po::value<size_t>(), "Block size for hashing")
            ("hash", po::value<std::string>(), "Hashing method: crc32, md5")
            ("start,s", "Start scanning");

        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << '\n';
        } 
        else if (vm.count("start")) {
            // Проверка наличия необходимых параметров перед запуском сканирования
            if (!vm.count("directories")) {
                std::cerr << "Error: No directories specified for scanning.\n";
                return 1;
            }

            // Считывание значений
            auto dirs = vm["directories"].as<std::vector<fs::path>>();
            auto excs = vm.count("exception") ? vm["exception"].as<std::vector<fs::path>>() : std::vector<fs::path>{};

            // Использование значения по умолчанию для level
            int level = vm.count("level") ? vm["level"].as<int>() : 1;
            auto filesize = vm.count("min_file_size") ? vm["min_file_size"].as<size_t>() : 0;
            auto Mask = vm.count("masks") ? vm["masks"].as<std::string>() : "";
            auto blocksize = vm.count("block_size") ? vm["block_size"].as<size_t>() : 5;
            // Запуск сканирования
            start_scanning(dirs, excs, level, filesize, Mask, blocksize);
        } 

        else {
            // Обработка других опций
            if (vm.count("level")) {
                int level = vm["level"].as<int>();
                std::cout << "Scanning level: " << level << std::endl;
            }

            if (vm.count("directories")) {
                on_directories(vm["directories"].as<std::vector<std::string>>());
            }

            if (vm.count("exception")) {
                on_exceptions(vm["exception"].as<std::vector<std::string>>());
            }
        }
    }
    catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
    }
    
    return 0;
}
