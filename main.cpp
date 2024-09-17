#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include<fstream>

using namespace std;
namespace fs = std::filesystem;

void FileOrganize(const string &path , string &img , string & docm , string &vids) {
    fs::path dir(path);
    ofstream fs("data.txt");


    fs::path images = dir / img;
    fs::path doc = dir / docm;
    fs::path vid = dir / vids;
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

        string path, img, doc, vids;

        cout << "Enter the path: ";
        getline(cin, path);

        cout << "[0] to modify settings" << endl << "[1] to organize a directory" << endl;
        cout << "Note: choose 1 if this is your first time: ";

        int x;
        cin >> x;
        cin.ignore();

        if (x == 0) {

            cout << "Enter image directory name: ";
            getline(cin, img);
            cout << "Enter document directory name: ";
            getline(cin, doc);
            cout << "Enter video directory name: ";
            getline(cin, vids);

            ofstream fs("data.csv");
            if (!fs) {
                cout << "Error opening data.csv for writing." << endl;
                return 1;
            }
            fs << img << endl << doc << endl << vids << endl;
            fs.close();
        } else
        {
            ifstream file("data.csv");
            if (!file) {
                cout << "Error opening data.csv for reading." << endl;
                return 1;
            }

            string line;
            int lineCount = 0;
            while (getline(file, line)) {
                if (lineCount == 0) {
                    img = line;
                } else if (lineCount == 1) {
                    doc = line;
                } else if (lineCount == 2) {
                    vids = line;
                }
                lineCount++;
            }
            file.close();
        }

    FileOrganize(path, img, doc, vids);
        return 0;
    }

