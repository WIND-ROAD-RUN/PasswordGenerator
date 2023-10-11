#include "pugixml.hpp"
#include<iostream>
#include<string>
using namespace std;
int main() {
    pugi::xml_document doc;
    if (doc.load_file(R"(database\LocalizationStringDatabase.xml)")) {
        cout << "true"<<endl;
    }
    else {
        cout << "false"<<endl;
    }


    pugi::xml_node root = doc.child("MyLocalizationStringModele_strings");

    // 遍历子节点
    for (pugi::xml_node node : root.children()) {
        std::cout << "Node name: " << node.name() << std::endl;

        // 遍历子节点的子节点
        for (pugi::xml_node child : node.children()) {
            std::cout << "  String ID: " << child.attribute("id").value() << std::endl;

            // 遍历语言节点
            for (pugi::xml_node lang : child.children()) {
                std::cout << "    Language: " << lang.attribute("local").value() << std::endl;
                std::cout << "    Text: " << lang.text().get() << std::endl;
            }

            std::cout << std::endl;
        }
    }
    return 0;
}