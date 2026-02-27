/*
SVG-7-vector-effect
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
//
#include <array>
#include <cmath>
#include <vector>
//
using namespace std;
//
string triangle_xy, 
       rectangle_xy,
       border_xy,
       line_h_xy,
       line_v_xy,
       line_1_xy, 
       line_2_xy,
       circle_xy,
       x_int,
       y_int;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
const float alpha   = 1.0; 
int j, xy_items = 0;
//
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
array<tuple<float, float>, 61> circle_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("SVG-7-vector-effect.svg");
//
void draw_polyline(string polyline_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polyline points=\"" 
            << polyline_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + 
               "\" vector-effect=\"non-scaling-stroke\"/> " 
            << std::endl;
}
//
void draw_polygon(string polygon_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + 
               "\" vector-effect=\"non-scaling-stroke\"/> " 
            << std::endl;
}
// c --> 圓心, center
void make_circle_tuple(int cx, int cy, float r, int start, int end) {
    float xx = 0.0f, yy = 0.0f;
    int k = 0;
    if (start < end) {
        for (int i = start, increment = 6; i < end+1; i += increment) {
            circle_tuple_array[k] = make_tuple(cx+r*cos(i*two_Pi/360), 
                                               cy+r*sin(i*two_Pi/360));
            k++;
            xy_items++;
        } // end for
    } // end if
}
//
void show_circle_tuple_value(void) {
    j = 0;
    for (int i = 0; i < xy_items; i++) {
        //
        xy_tuple = circle_tuple_array[i];
        cout << "i: " << i << endl;
        cout << "x: " << get<0>(xy_tuple) << endl;
        cout << "y: " << get<1>(xy_tuple) << endl;
        cout << "--------------------" << endl;
    } // end for  
}
//
void circle_tuple_to_string(void) {
    j = 0;
    for (int i = 0; i < xy_items; i++) {
        //
        xy_tuple = circle_tuple_array[i];
        x_int = to_string(round(get<0>(xy_tuple)));
        y_int = to_string(round(get<1>(xy_tuple)));
        x_int.erase (x_int.begin() + x_int.rfind('.'), x_int.end());
        y_int.erase (y_int.begin() + y_int.rfind('.'), y_int.end());
        //
        circle_xy = circle_xy + x_int + "," + y_int + " ";
    } // end for  
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
    // file-3.svg
    //svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800px\" height=\"600px\">" << std::endl;
    // file-4.svg
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800px\" height=\"600px\">" << std::endl;
    //
    // 添加 border polyline
    border_xy = "0,0 800,0 800,600 0,600 0,0";
    //draw_polygon(border_xy, "black", "lightblue", 2);
    draw_polyline(border_xy, "black", "lightblue", 2);
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
        //cout << "line_h_xy = " << line_h_xy << endl;
        draw_polyline(line_h_xy, "none", "lightblue", 1);
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
        //cout << "line_v_xy = " << line_v_xy << endl;
        draw_polyline(line_v_xy, "none", "lightblue", 1);
    }
    //
    // 添加SVG圖形
    line_1_xy = "50,50 750,550";
    line_2_xy = "50,550 750,50";
    triangle_xy = "150,500 650,500 400,100";
    rectangle_xy = "50,50 750,50 750,550 50,550 50,50";
    //
    draw_polygon(rectangle_xy, "sandybrown", "cyan", 1);
    draw_polyline(line_1_xy, "none", "blue", 1);
    draw_polyline(line_2_xy, "none", "blue", 1);
    draw_polygon(triangle_xy, "green", "cyan", 3);
    //
    circle_xy = "";
    make_circle_tuple(400, 300, 150.0, 0, 360);
    cout << "xy_items = " << xy_items << endl;
    // show_circle_tuple_value();
    circle_tuple_to_string();
    cout << circle_xy << endl;
    draw_polyline(circle_xy, "none", "red", 1);
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