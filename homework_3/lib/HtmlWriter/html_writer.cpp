#include "html_writer.hpp"
#include <string>

namespace fs = boost::filesystem;

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
    if(fs::path(img_path).extension() == ".png" || fs::path(img_path).extension() == ".jpg"){
        std::string style_string = highlight ? "border: 5px solid green;" : "";
        fmt::print("<div class=\"column\" style=\"{0}\">\n<h2>{1}</h2>\n<img src=\"{2}\" />\n<p>score = {3}</p>\n</div>\n", 
        style_string, fs::path(img_path).filename().string(), img_path, fmt::format("{:.2f}", score));
    }else{
        fmt::print(stderr, "Invalid file extension");
    }
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
