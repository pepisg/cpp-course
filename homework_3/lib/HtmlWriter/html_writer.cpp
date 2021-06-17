#include "html_writer.hpp"
#include "fmt/core.h"
#include <string>

void OpenDocument(){
    fmt::print("<!DOCTYPE html>\n<html>\n");
}

void CloseDocument(){
    fmt::print("</html>\n");
}

void AddCSSStyle(const std::string& stylesheet){
    fmt::print("<head>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"{}\" />\n</head>\n", stylesheet);
}

void AddTitle(const std::string& title){
    fmt::print("<title>{}</title>\n", title);
}

void OpenBody(){
    fmt::print("<body>\n");
}

void CloseBody(){
    fmt::print("</body>\n");
}

void OpenRow(){
    fmt::print("<div class=\"row\">\n");
}

void CloseRow(){
    fmt::print("</div>\n");
}

void AddImage(const std::string& img_path, float score, bool highlight = false){
    std::string style_string = highlight ? "border: 5px solid green;" : "";
    fmt::print("<div class=\"column\" style=\"{0}\">\n<h2>{1}</h2>\n<img src=\"{1}\" />\n<p>score = {2}</p>\n</div>\n", style_string, img_path, std::to_string(score));
    
}

int main(){
    OpenDocument();
    AddTitle("Ensayo");
    AddCSSStyle("style.css");
    OpenBody();
    OpenRow();
    AddImage("data/000000.png", 10.0f);
    AddImage("data/000100.png", 50.0f, true);
    CloseRow();
    CloseBody();
    CloseDocument();

    return 0;
}
