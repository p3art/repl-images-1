/*
SVG-3
//
2024-08-09
2026-02-27
//
run on replit.com web platform
1MiB = 1.048MB
*/
//
#include <string>
#include <thread>  // 多執行緒
#include <fstream>
#include <iostream>
using namespace std;
//
string triangle_xy, 
       rectangle_xy,
       border_xy,
       line_h_xy,
       line_v_xy,
       line_1_xy, 
       line_2_xy;

// 創建SVG文件
std::ofstream svgFile("file-1.svg");
//
void draw_polyline(string polyline_xy, string stroke_color, int stroke_width)
{
    svgFile << "<polyline points=\"" 
            << polyline_xy 
            << "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + "\" /> " 
            << std::endl;
}
//
void draw_polygon(string polygon_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + "\" /> " 
            << std::endl;
}
//
// ----------------------------------------------------
//
int main() {
    cout << endl;
    cout << "repl main() running ..." << endl;
    //  
    // 檢查文件是否成功打開
    if (!svgFile.is_open()) {
        std::cerr << "無法打開SVG文件！" << std::endl;
        return 1;
    }
    // cout means "character output"
    // 寫入SVG頭部, SVG default color is black
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800px\" height=\"600px\">" 
            << std::endl;
    //
    // 添加 border polyline
    border_xy = "0,0 800,0 800,600 0,600 0,0";
    //draw_polygon(border_xy, "black", "lightblue", 4);
    draw_polyline(border_xy, "lightblue", 4);
    //
    // 添加 grid h line
    int i_max = 13;
    int x0, x1, y0, y1;
    x0 = 0;
    x1 = 800;
    for (int i = 0; i < i_max; i++) {
        y0 = i * 50;
        y1 = i * 50;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        cout << "line_h_xy = " << line_h_xy << endl;
        draw_polyline(line_h_xy, "lightblue", 1);
    }
    cout << ' ' << endl;
    //
    // 添加 grid v line
    i_max = 17;
    y0 = 0;
    y1 = 600;
    for (int i = 0; i < i_max; i++) {
        x0 = i * 50;
        x1 = i * 50;
        line_v_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        cout << "line_v_xy = " << line_v_xy << endl;
        draw_polyline(line_v_xy, "lightblue", 1);
    }
    /*
    line_h00_xy = "0,0 800,0";
    line_h01_xy = "0,50 800,50";
    line_h02_xy = "0,100 800,100";
    line_h03_xy = "0,150 800,150";
    line_h04_xy = "0,200 800,200";
    line_h05_xy = "0,250 800,250";
    line_h06_xy = "0,300 800,300";
    line_h07_xy = "0,350 800,350";
    line_h08_xy = "0,400 800,400";
    line_h09_xy = "0,450 800,450";
    line_h10_xy = "0,500 800,500";
    line_h11_xy = "0,550 800,550";
    line_h12_xy = "0,600 800,600";
    //
    draw_polyline(line_h00_xy, "lightblue", 1);
    draw_polyline(line_h01_xy, "lightblue", 1);
    draw_polyline(line_h02_xy, "lightblue", 1);
    draw_polyline(line_h03_xy, "lightblue", 1);
    draw_polyline(line_h04_xy, "lightblue", 1);
    draw_polyline(line_h05_xy, "lightblue", 1);
    draw_polyline(line_h06_xy, "lightblue", 1);
    draw_polyline(line_h07_xy, "lightblue", 1);
    draw_polyline(line_h08_xy, "lightblue", 1);
    draw_polyline(line_h09_xy, "lightblue", 1);
    draw_polyline(line_h10_xy, "lightblue", 1);
    draw_polyline(line_h11_xy, "lightblue", 1);
    draw_polyline(line_h12_xy, "lightblue", 1);
    */
    //
    // 添加SVG圖形
    line_1_xy = "50,250 250,100";
    line_2_xy = "50,100 250,250";
    rectangle_xy = "50,250 250,250 250,100 50,100";
    triangle_xy = "70,230 230,230 150,120";
    //
    draw_polygon(rectangle_xy, "coral", "yellow", 4);
    draw_polyline(line_1_xy, "blue", 4);
    draw_polyline(line_2_xy, "blue", 4);
    draw_polygon(triangle_xy, "green", "cyan", 3);
    //
    // 寫入SVG尾部
    svgFile << "</svg>" << std::endl;
    // 關閉文件
    svgFile.close();
    //
    cout << ' ' << endl;
    cout << "SVG 文件已生成！" << std::endl;
    //
    cout << endl;
    cout << "exit main() ..." << endl;
    return 0;
}