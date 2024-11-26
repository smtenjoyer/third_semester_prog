#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include "primitive.h"

class Document {
private:
    std::string name_ = "none";

public:
    std::map<std::string, std::string> prims_;
    Document(const std::string& name) : name_(name) {}
    Document() : name_() {}

    void NewDoc(const std::string& document_name) {
        std::cout << "Создан новый документ " << document_name << std::endl;
    }

    void ImportDoc(const std::string& document_name, const std::string& filename) {
        std::cout << "Документ " << document_name << " импортирован из файла " << filename << std::endl;
    }

    void ExportDoc(const std::string& document_name, const std::string& filename) {
        std::cout << "Документ " << document_name << " экспортирован в файл " << filename << std::endl;
    }

    void rename(const std::string& new_name) {
        name_ = new_name;
    }

    void push_back(const std::shared_ptr<Primitive>& primitive) {
        if (primitive) {
            prims_[primitive->get_type()] = primitive->get_name();
        }
    }
    std::string getName() const { return name_; }
};
