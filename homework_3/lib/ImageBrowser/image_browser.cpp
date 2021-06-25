#include "image_browser.hpp"
#include <lib/HtmlWriter/html_writer.hpp>
#include <string>
#include <tuple>

using ImageRow = image_browser::ImageRow;
using ScoredImage = image_browser::ScoredImage;

void AddFullRow(const ImageRow& row, bool first_row = false)
{
    html_writer::OpenRow();
    for(int i = 0; i < row.size(); i++)
    {
        html_writer::AddImage(std::get<0>(row[i]), std::get<1>(row[i]));
    }
    html_writer::CloseRow();
}

void CreateImageBrowser(const std::string& title, const std::string& stylesheet,
                        const std::vector<ImageRow>& rows)
{
    html_writer::OpenDocument();
    html_writer::AddTitle(title);
    html_writer::AddCSSStyle(stylesheet);
    html_writer::OpenBody();
    for(ImageRow row : rows)
        {
            AddFullRow(row);
        }
    html_writer::CloseBody();
    html_writer::CloseDocument();
}



int main(){
    std::vector<ImageRow> image_raws;
    int current_imgrow = 0;
    for(int i=0; i<3; i++)
        {
        ImageRow m_img_row;
        for(int j=0; j<3; j++)
        {
            std::string img_title = "data/00000"+std::to_string(i*3 + j)+".png";
            m_img_row[j] = std::make_tuple(img_title, (i*3 + j)*0.1f);
        }
        image_raws.push_back(m_img_row);
        }
        CreateImageBrowser("Ensayo2", "style.css", image_raws);
    return 0;
}