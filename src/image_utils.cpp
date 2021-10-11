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
    buffer.open("resultado.txt");
    buffer << "-----------------------------------------------------------------------\n";
    buffer << "Aproveitamento: ";
    buffer << image_utils::get_result() << "%\n";
    buffer << "-----------------------------------------------------------------------\n";

    for ( auto &p : image_utils::images ){
        if(p.second == false){
            buffer << p.first << "\n";
        }
    }
    buffer << "-----------------------------------------------------------------------\n";
    buffer.close();
}
