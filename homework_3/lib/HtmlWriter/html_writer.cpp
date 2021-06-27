#include "html_writer.hpp"
#include <string>

namespace fs = boost::filesystem;

void html_writer::OpenDocument(){
    fmt::print("<!DOCTYPE html>\n<html>\n");
}

void html_writer::CloseDocument(){
    fmt::print("</html>\n");
}

void html_writer::AddCSSStyle(const std::string& stylesheet){
    fmt::print("<head>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"{}\" />\n</head>\n", stylesheet);
}

void html_writer::AddTitle(const std::string& title){
    fmt::print("<title>{}</title>\n", title);
}

void html_writer::OpenBody(){
    fmt::print("<body>\n");
}

void html_writer::CloseBody(){
    fmt::print("</body>\n");
}

void html_writer::OpenRow(){
    fmt::print("<div class=\"row\">\n");
}

void html_writer::CloseRow(){
    fmt::print("</div>\n");
}

void html_writer::AddImage(const std::string& img_path, float score, bool highlight){
    if(fs::path(img_path).extension() == ".png" || fs::path(img_path).extension() == ".jpg"){
        std::string style_string = highlight ? "border: 5px solid green;" : "";
        fmt::print("<div class=\"column\" style=\"{0}\">\n<h2>{1}</h2>\n<img src=\"{2}\" />\n<p>score = {3}</p>\n</div>\n", 
        style_string, fs::path(img_path).filename().string(), img_path, fmt::format("{:.2f}", score));
    }else{
        fmt::print(stderr, "Invalid file extension");
    }
}

// int main(){
//     html_writer::OpenDocument();
//     html_writer::AddTitle("Ensayo");
//     html_writer::AddCSSStyle("style.css");
//     html_writer::OpenBody();
//     html_writer::OpenRow();
//     html_writer::AddImage("data/000000.png", 10.0f);
//     html_writer::AddImage("data/000100.png", 50.0f, true);
//     html_writer::CloseRow();
//     html_writer::CloseBody();
//     html_writer::CloseDocument();

//     return 0;
// }
