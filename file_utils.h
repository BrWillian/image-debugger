#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <QString>
#include <QStringList>
#include <QDir>
#include <vector>

class file_utils
{
public:
    file_utils();
    static void list_dir(QString dir);
    inline static std::vector<QString>list_of_images;
};

#endif // FILE_UTILS_H
