/*
SVG-1
//
2024-05-17
2026-02-29
//
run on replit.com web platform
1MiB = 1.048MB
*/
//
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
//
// --------------------------------------------
//
int main() {
    cout << endl;
    cout << "repl main() running ..." << endl;
    // 
    // 创建SVG文件
    std::ofstream svgFile("SVG-1.svg");

    // 检查文件是否成功打开
    if (!svgFile.is_open()) {
        std::cerr << "无法打开SVG文件！" << std::endl;
        return 1;
    }

    // 写入SVG头部
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;

    // 添加SVG图形
    svgFile << "<rect x=\"50\" y=\"50\" width=\"200\" height=\"100\" fill=\"red\"/>" << std::endl;
    svgFile << "<circle cx=\"150\" cy=\"150\" r=\"50\" fill=\"blue\"/>" << std::endl;
    svgFile << "<line x1=\"50\" y1=\"200\" x2=\"250\" y2=\"200\" stroke=\"green\"/>" << std::endl;
    svgFile << "<line x1=\"50\" y1=\"250\" x2=\"250\" y2=\"250\" stroke=\"magenta\"/>" << std::endl;

    // 写入SVG尾部
    svgFile << "</svg>" << std::endl;

    // 关闭文件
    svgFile.close();

    std::cout << "SVG 文件已生成！" << std::endl;
    //
    cout << endl;
    cout << "exit main() ..." << endl;
    return 0;
}