#include "document.h"
void help()
{
    std::cout << "Для создания нового документа: newdoc + имя документа" << std::endl;
    std::cout << "Для импорта документа из файла: import + имя документа + имя файла" << std::endl;
    std::cout << "Для экспорта документа в файл: export + имя документа + имя файла" << std::endl;
    std::cout << "Для создания графического примитива: create" << std::endl;
    std::cout << "Для удаления графического примитива: delete" << std::endl;
    std::cout << "Для закрытия графичекского редактора: kill" << std::endl;
}



int main()
{
    std::map<std::string, Document> documents_;
    setlocale(LC_ALL, "RU"); // RU локализация консоли
    std::string command = "";
    std::cout << "Введите help для просмотра команд:\n";
    while(command != "kill")
    {
        std::cin >> command;
        if (command == "help"){ help(); }
        else if(command == "newdoc" || command == "import" || command == "export" || command == "create" || command == "delete")
        {
            Document document;
            std::string document_name = "";
            if (command == "newdoc") 
            {
                std::cin >> document_name;
                document.NewDoc(document_name);
                documents_[document_name] = (document);
            }
            
            else if (command == "import") 
            { 
                std::string file_name = "";
                std::cin >> document_name;
                std::cin >> file_name;
                document.ImportDoc(document_name, file_name);
                documents_[document_name] = (document);
            }
            else if (command == "export") 
            { 
                std::string file_name = "";
                std::cin >> document_name;
                std::cin >> file_name;
                document.ExportDoc(document_name, file_name);
                documents_[document_name] = (document);
            }

            else if (command == "create") 
            {   
                std::cout << "Чего желаете? круг(circle), квадраты(square), правильные n-угольники(polygon)" << std::endl;
                std::string name = "";
                std::string type = "";
                
                std::cin >> type;
                std::shared_ptr<Primitive> primitive;
                if (type == "circle")
                {
                    std::cout << "Введите имя круга. Еще нужно радиус ввести" << std::endl;
                    double radius;
                    std::cin >> name;
                    
                    std::cin >> radius;
                    primitive = std::make_shared<Circle>(name, radius);
                    std::cout << "В какой документ засунем?" << std::endl;
                    std::cin >> document_name;
                    documents_[document_name].push_back(primitive);
                }
                else if (type == "square")
                {
                    std::cout << "Введите имя квадрата. Еще нужно длину стороны ввести" << std::endl;
                    
                    double side;

                    std::cin >> name;
                    std::cin >> side;
                    
                    primitive = std::make_shared<Square>(name, side); 

                    std::cout << "В какой документ засунем?" << std::endl;
                    std::cin >> document_name;
                    if (documents_.count(document_name)) 
                    {
                        documents_[document_name].push_back(primitive);
                    }else{std::cout << "Нету такого документа " << std::endl;}
                    
                }
                else if (type == "polygon")
                {
                    std::cout << "Введите имя многоугольника. Еще нужно ввести длину грани и их количество" << std::endl;
                    double side;
                    unsigned num;

                    std::cin >> name;
                    std::cin >> side >> num;

                    primitive = std::make_shared<Polygon>(name, side, num); 
                    std::cout << "В какой документ засунем?" << std::endl;
                    
                    std::cin >> document_name;
                    documents_[document_name].push_back(primitive);
                }
                else 
                {
                    std::cout << "Введите имя примитива" << std::endl;
                    std::cin >> name;
                    primitive = std::make_shared<Primitive>(name); 
                    std::cout << "В какой документ засунем?" << std::endl;
                    std::cin >> document_name;
                    documents_[document_name].push_back(primitive);
                }
                std::cout << "Создан объект " << primitive->get_type() << " с именем " << primitive->get_name()<< " в документе " << document_name << std::endl;
            }
            
        }
        else 
        {
            std::cout << "Нету такой команды" << std::endl;
        }
    }
    return 0;
}