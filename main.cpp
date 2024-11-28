#include "document.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <ctype.h>

void help()
{
    std::cout << "Для создания нового документа: newdoc + имя документа" << std::endl;
    std::cout << "Для импорта документа из файла: import + имя документа + имя файла" << std::endl;
    std::cout << "Для экспорта документа в файл: export + имя документа + имя файла" << std::endl;
    std::cout << "Для создания графического примитива: create" << std::endl;
    std::cout << "Для удаления графического примитива: delete" << std::endl;
    std::cout << "Для закрытия графического редактора: kill" << std::endl;
}

void handleDocumentCommand(const std::string& command, std::map<std::string, Document>& documents_)
{
    std::string document_name, file_name;
    if (command == "newdoc") 
    {
        std::cin >> document_name;
        Document document;
        document.NewDoc(document_name);
        documents_[document_name] = document;
    }
    else if (command == "import") 
    { 
        std::cin >> document_name >> file_name;
        if (documents_.count(document_name)) 
        {
            Document document;
            document.ImportDoc(document_name, file_name);
            documents_[document_name] = document;
        }
        else
        {
            std::cout << "Нету такого документа." << std::endl;
        }
        
    }
    else if (command == "export") 
    { 
        std::cin >> document_name >> file_name;
        if (documents_.count(document_name)) 
        {
            Document document;
            documents_[document_name].ExportDoc(document_name, file_name);
        }
        else
        {
            std::cout << "Нету такого документа." << std::endl;
        }
    }
}

void gotoDocument(std::map<std::string, Document>& documents_, const std::shared_ptr<Primitive>& primitive)
{
    std::string document_name;
    
    std::cout << "В какой документ засунем?" << std::endl;
    std::cin >> document_name;

    if (documents_.count(document_name)) 
    {
        documents_[document_name].push_back(primitive);
        std::cout << "Создан объект " << primitive->get_type() 
                  << " с именем " << primitive->get_name() 
                  << " в документе " << document_name << std::endl;
    }
    else
    {
        std::cout << "Нету такого документа." << std::endl;
    }
}

bool isNumber(const std::string& str) {
    if(!str.empty())
    {
        for( int i = 0; i < str.length(); i++ ) 
        {
            if( !isdigit( str[i] ) ) { return false; }
            else {return true;}
        }
    }
    else {return false;}
}

void createPrimitive(std::map<std::string, Document>& documents_) {
    std::cout << "Чего желаете? круг(circle), квадраты(square), правильные n-угольники(polygon)" << std::endl;
    std::string type;
    std::cin >> type;
    std::cin.ignore(); // очищаем буфер после ввода типа


    if (type != "circle" && type != "square" && type != "polygon") {
        std::cout << "Неверный тип фигуры." << std::endl;
        return;
    }

    std::string name, input;
    double radius, side;
    unsigned num;

    std::cout << "Введите имя фигуры: ";
    std::getline(std::cin, name);

    if (type == "circle") {
        std::cout << "Введите радиус: ";
        std::getline(std::cin, input);
        while (!isNumber(input) || std::stod(input) <= 0) {
            std::cout << "Неверный радиус. Попробуйте снова: ";
            std::getline(std::cin, input);
        }
        radius = std::stod(input);
        auto primitive = std::make_shared<Circle>(name, radius);
        gotoDocument(documents_, primitive);
    } else if (type == "square") {
        std::cout << "Введите длину стороны: ";
        std::getline(std::cin, input);
        while (!isNumber(input) || std::stod(input) <= 0) {
            std::cout << "Неверная длина стороны. Попробуйте снова: ";
            std::getline(std::cin, input);
        }
        side = std::stod(input);
        auto primitive = std::make_shared<Square>(name, side);
        gotoDocument(documents_, primitive);
    } else if (type == "polygon") {
        std::cout << "Введите длину стороны: ";
        std::getline(std::cin, input);
        while (!isNumber(input) || std::stod(input) <= 0) {
            std::cout << "Неверная длина стороны. Попробуйте снова: ";
            std::getline(std::cin, input);
        }
        side = std::stod(input);
        std::cout << "Введите количество сторон: ";
        std::getline(std::cin, input);
        while (!isNumber(input) || std::stoul(input) < 3) {
            std::cout << "Неверное количество сторон (должно быть не менее 3). Попробуйте снова: ";
            std::getline(std::cin, input);
        }
        num = std::stoul(input);
        auto primitive = std::make_shared<Polygon>(name, side, num);
        gotoDocument(documents_, primitive);
    }
}





int main()
{
    setlocale(LC_ALL, "RU");
    
    std::map<std::string, Document> documents_;
    
    std::string command = "";
    
    std::cout << "Введите help для просмотра команд:\n";
    
    while(command != "kill")
    {
        std::cin >> command;

        if (command == "help")
            help();
        else if (command == "newdoc" || command == "import" || command == "export")
            handleDocumentCommand(command, documents_);
        else if (command == "create")
            createPrimitive(documents_);
        else 
            std::cout << "Нету такой команды" << std::endl;
    }

    return 0;
}