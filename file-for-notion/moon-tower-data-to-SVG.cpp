/*
moon-tower-data-to-SVG
//
2024-05-17
2026-02-27
//
run on replit.com web platform
1MiB = 1.048MB

Jules Bourgoin (朱爾斯·布爾戈因) 1879
Catalog No, BOU 103
*/
//
// #include <unistd.h>  // for Linux/Unix 平台, 是Unix Standard的縮寫
#include <array>
#include <string>
#include <thread>  // 多執行緒
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
//
int j = 0, KK = 0;
int moon_vertices_count = 0;
int moon_xy_count = 0;
tuple<float, float, float> xyz_tuple;
array<tuple<float, float, float>,129> moon_tuple_array;
//
// 在OpenGL中，逆時針繪製的面是正面
//
string x_str, y_str;
string moon_vertices_string;
vector<float> vec_of_float;
float moon_xy[129*2]  = {0.0f};
//
// =================================================================
//
void read_file_to_vector(string filename) {
    // Opening the file in read mode
    ifstream in_file(filename);  
    float field_value;
    string line;
    //
    while ( getline(in_file, line, ',') ) {
        // cout << line << endl;
        stringstream ss(line);
        while (ss >> field_value)
        {
            vec_of_float.push_back(field_value);
            if (ss.peek() == ' ') {ss.ignore();}
        }
    }
    in_file.close();
    //
    cout << endl;
    cout << "vec_of_float.size() = " << vec_of_float.size() << endl;
    cout << "total vertice is " << vec_of_float.size()/2 << endl;
    cout << endl;
}
//
void store_vector_to_moon_xy(void) {
    for (int i=0; i < vec_of_float.size(); i++) {
        moon_xy[i] = vec_of_float.at(i);
    }
}
//
void moon_xy_array_to_string(void) {
    j = 0;
    for (int i=0; i < moon_xy_count/2; i++) {
        x_str = to_string(moon_xy[j]*1000);
        y_str = to_string(450-moon_xy[j+1]*1000);
        moon_vertices_string = moon_vertices_string + x_str + "," + y_str + " " ;
        j = j + 2;
    }
}
//
// ----------------------------------------------------------
//
int main() {
    cout << endl;
    cout << "repl main() running ..." << endl;
    //
    vec_of_float.clear();
    read_file_to_vector("zz-moon_boundary.txt");
    store_vector_to_moon_xy();
    moon_xy_count = sizeof(moon_xy)/sizeof(moon_xy[0]);
    cout << "moon_xy_count = " << moon_xy_count << endl;
    cout << " " << endl;
    //
    moon_vertices_string = "";
    moon_xy_array_to_string();
    cout << "moon_vertices_string = " << endl;
    cout << moon_vertices_string << endl;
    //  
    // 創建SVG文件
    std::ofstream svgFile("moon-tower-data-to-SVG.svg");

    // 檢查文件是否成功打開
    if (!svgFile.is_open()) {
        std::cerr << "無法打開SVG文件！" << std::endl;
        return 1;
    }
    // cout means "character output"
    // 寫入SVG頭部
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    svgFile << "<svg x=\"0\" y=\"0\" width=\"600\" height=\"600\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" >" << std::endl;

    // 添加SVG圖形
    svgFile << "<polygon points=\"0,0 600,0 600,600 0,600\" fill=\"lightyellow\" stroke=\"red\" stroke-width=\"3\" /> " << std::endl;
    //
    svgFile << "<polygon points=\"" << moon_vertices_string << "\" fill=\"green\" stroke=\"blue\" stroke-width=\"1\" /> " << std::endl;
    // 寫入SVG尾部
    svgFile << "</svg>" << std::endl;
    // 關閉文件
    svgFile.close();
    //
    std::cout << "SVG 文件已生成！" << std::endl;
    //
    cout << endl;
    cout << "exit main() ..." << endl;
    return 0;
}