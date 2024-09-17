#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;

void FileOrganize(const string &path) {
    fs::path dir(path);


    fs::path images = dir / "images";
    fs::path doc = dir / "doc";
    fs::path vid = dir / "vid";
    fs::path other = dir / "other";

    fs::create_directory(images);
    fs::create_directory(doc);
    fs::create_directory(vid);
    fs::create_directory(other);

    for (const auto &file : fs::directory_iterator(dir)) {
        if (fs::is_regular_file(file)) {
            string ext = file.path().extension().string();

            fs::path destination;
            if (ext == ".jpg" || ext == ".png" || ext == ".gif") {
                destination = images / file.path().filename();
            } else if (ext == ".pdf" || ext == ".docx" || ext == ".doc") {
                destination = doc / file.path().filename();
            } else if (ext == ".mp4" || ext == ".avi" || ext == ".mkv") {
                destination = vid / file.path().filename();
            } else {
                destination = other / file.path().filename();
            }


            fs::rename(file.path(), destination);
        }
    }


    ShellExecute(NULL, "explore", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

int main() {
    string path;
    cout << "Enter the path: ";
    getline(cin, path);
    FileOrganize(path);
    return 0;
}

