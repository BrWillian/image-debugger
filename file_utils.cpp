#include "file_utils.h"

file_utils::file_utils()
{

}
void file_utils::list_dir(QString dir){
    QStringList nameFilter;

    nameFilter << "*.png" << "*.jpg" << "*.gif" << "*.jpeg";
    QDir path(dir);
    path.setSorting(QDir::Name);
    path.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    path.setNameFilters(nameFilter);

    foreach (const QFileInfo& file, path.entryList()) {
        QString strtmp = dir+QDir::separator()+file.fileName();
        file_utils::list_of_images.push_back(strtmp);
    }
}
