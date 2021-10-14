#include "image_utils.h"

image_utils::image_utils()
{

}
int image_utils::get_error()
{
    int count = 0;

    for ( auto &p : image_utils::images ) count += p.second == false;

    return count;
}
void image_utils::list_dir(QString Path){
    image_utils::npos = 0;
    image_utils::images.clear();
    image_utils::entered.clear();

    QStringList nameFilter;

    nameFilter << "*.png" << "*.jpg" << "*.gif" << "*.jpeg";
    QDir path(Path);
    path.setSorting(QDir::Name);
    path.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    path.setNameFilters(nameFilter);

    foreach (const QFileInfo& file, path.entryList()) {
        QString strtmp = Path+QDir::separator()+file.fileName();
        image_utils::images.insert(std::pair<std::string, bool>(strtmp.toStdString(),true));
    }

}
std::map<std::string, bool>::iterator image_utils::get_map_from_index(int n)
{
    auto it = image_utils::images.begin();
    std::advance(it, n);
    return it;
}
float image_utils::get_result()
{
    return (1 - (float)image_utils::get_error()/(float)image_utils::images.size()) * 100;
}
void image_utils::write_result()
{
    std::ofstream buffer;
    std::time_t date = std::time(nullptr);

    if(!image_utils::fileExists("resultado.txt")){
        buffer.open("resultado.txt", std::ofstream::out | std::ofstream::app);
        buffer << "-----------------------------------------------------------------------\n";
        buffer << "Gerado as: " << std::ctime(&date);
        buffer << "-----------------------------------------------------------------------\n";
        buffer << "Incorrect Images\n";
        buffer << "-----------------------------------------------------------------------\n";
        buffer.close();
    }else {
        buffer.open("resultado.txt", std::ofstream::out | std::ofstream::app);
        for ( auto &p : image_utils::images ){
            if(p.second == false && !image_utils::already_entered(p.first)){
                buffer << p.first << "\n";
                image_utils::entered.push_back(p.first);
            }
        }
        buffer.close();
    }
}
void image_utils::write_accuracy()
{
    std::ofstream buffer;
    buffer.open("resultado.txt", std::ofstream::out | std::ofstream::app);
    buffer << "-----------------------------------------------------------------------\n";
    buffer << "Accuracy: " << image_utils::get_result() << "%\n";
    buffer << "-----------------------------------------------------------------------\n";
    buffer.close();
}
bool image_utils::fileExists(std::string file)
{
    std::ifstream infile(file);
    return infile.good();
}
bool image_utils::already_entered(std::string str)
{
    auto it = std::find(image_utils::entered.begin(), image_utils::entered.end(), str);
    if(it != image_utils::entered.end())
    {
        return true;
    }
    return false;
}
