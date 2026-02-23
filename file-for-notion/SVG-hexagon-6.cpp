/*
All/01-nix-cpp-SVG/旗山中山路95號-Hexagon/
SVG-hexagon-6
//
2024-08-18
2025-09-13
//
Gemini dialogue
https://gemini.google.com/app/899264b4d79ccfe6
//
run on replit.com web platform
1MiB = 1.048MB

How to convert .SVG to PDF?
open the svg image in a browser , press Ctrl + P (print) select save as PDF.

台灣本土現存最早的伊斯蘭(回教)幾何圖案
此圖案所在建物產權屬於吳基福家族， 建於日據大正14年(1925年)
在1915(民國 4)年由日本人所進行的臺灣宗教調查的成果《臺灣宗教調查報告書》中，看不到任何伊斯蘭教的相關紀錄。
台灣歷史學家連橫撰寫的《臺灣通史》，出版於1920年，看不到任何伊斯蘭教的相關紀錄。
文化部_清真寺文化資產價值評估報告書 (2020-01)，報告書所列本土清真寺/伊斯蘭教/回教文化資產，其創建年代皆晚於旗山中山路95號建物。

此圖案位於一樓走廊外牆，Google 地圖街景網址
https://www.google.com/maps/search/%E9%AB%98%E9%9B%84%E5%B8%82%E6%97%97%E5%B1%B1%E5%8D%80%E4%B8%AD%E5%B1%B1%E8%B7%AF95%E8%99%9F-hexagon/@22.8877359,120.4794134,17z/data=!3m1!4b1?authuser=0&entry=ttu
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
string x, y,
       fan_line_xy, 
       hexagon_xy,
       border_xy,
       line_h_xy,
       line_v_xy,
       line_1_xy, 
       line_2_xy,
       arc_xy,
       text_x,
       text_y,
       text,
       circle_xy,
       x_int, y_int,
       cx_int, cy_int,
       tx, ty;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
float dx, dy, x_pos, y_pos;
int j, k, xy_items = 0;
int j_set[] = {1,3,5};
//
tuple<float, float> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-6.svg");
//
void draw_polyline(string polyline_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polyline points=\"" 
            << polyline_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + "\" /> " 
            << endl;
}
//
void draw_polygon(string polygon_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) + "\" /> " 
            << endl;
}
//
void translate_polygon(tuple<float,float>tXY_tuple, 
                       string polygon_xy, 
                       string fill_color, 
                       string stroke_color,     
                       int stroke_width)
{
    tx = to_string(get<0>(tXY_tuple));
    ty = to_string(get<1>(tXY_tuple));
    string transform_string = "translate(" +
                              tx + " "  + 
                              ty + ")";
    //cout << transform_string << endl;
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) +
               "\" transform=\"" + transform_string + "\" />"
            << endl;
}
//
void translate_polyline(tuple<float,float>tXY_tuple, 
                        string polyline_xy, 
                        string fill_color, 
                        string stroke_color,     
                        int stroke_width) {
    tx = to_string(get<0>(tXY_tuple));
    ty = to_string(get<1>(tXY_tuple));
    string transform_string = "translate(" +
                              tx + " "  + 
                              ty + ")";
    //cout << transform_string << endl;
    svgFile << "<polyline points=\"" 
            << polyline_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) +
               "\" transform=\"" + transform_string + "\" />"
            << endl;
}
//
void draw_text(string text_x, 
               string text_y,
               string font, 
               string size, 
               string fill_color,
               string text)
{
    svgFile << "<text x=\"" + text_x + "\"" +
                    " y=\"" + text_y 
            << "\" font-family=\"" + font + 
               "\" font-size=\""   + size + 
               "\" fill=\"" + fill_color +
               "\">" +
               text + "</text> " 
            << endl;
}
// c --> 圓心, center
void make_hexagon_tuple(int cx, int cy, float r) {
    k = 0;
    for (int i=0; i < 6; i++) {
        x_pos = cx+r*cos(i*Pi/3);
        y_pos = cy+r*sin(i*Pi/3);
        xy_tuple_array[k] = make_tuple(x_pos, y_pos);
        k++;
    } // end for
    xy_items = k;
}
//
void xy_tuple_to_string(void) {
    j = 0;
    hexagon_xy = "";
    for (int i = 0; i < xy_items; i++) {
        xy_tuple = xy_tuple_array[i];
        x_int = to_string(get<0>(xy_tuple));
        y_int = to_string(get<1>(xy_tuple));
        //cout << x_int << " " << y_int << endl;
        //
        hexagon_xy = hexagon_xy + x_int + "," + y_int + " ";
    } // end for  
}
//
void rotate_polygon(tuple<float,float>tXY_tuple,
                    tuple<int,int>cXY_tuple, 
                    int degree, 
                    string polygon_xy, 
                    string fill_color, 
                    string stroke_color, 
                    int stroke_width)
{
    tx = to_string(get<0>(tXY_tuple));
    ty = to_string(get<1>(tXY_tuple));
    cx_int = to_string(get<0>(cXY_tuple));
    cy_int = to_string(get<1>(cXY_tuple));
    string transform_string = "rotate(" + 
                              to_string(degree) + " " + 
                              cx_int + " " + 
                              cy_int + ") " + 
                              "translate(" +
                              tx + " "  + 
                              ty + ")";
    // when repl run : SVG first translate, then rotate.
    // cout << transform_string << endl;
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) +
               "\" transform=\"" + transform_string + "\" />"
            << endl;
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
    svgFile << "<svg viewBox=\"100 169.5 400 261\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400px\" height=\"261px\">" 
            << std::endl;
    //
    // 添加SVG圖形
    make_hexagon_tuple(300, 300, 50.0);
    xy_tuple_to_string();
    dy = -100.0*sqrt(3.0)/2;
    cout <<  "dy = " << dy << endl;
    //
    vector<vector<float>> t_vec = {
        { 0, (float)1*dy}, {0, (float)-1*dy},
        { 0, (float)2*dy}, {0, (float)-2*dy},
        //
        { 75,(float)0.5*dy}, { 75,(float)-0.5*dy},
        { 75,(float)1.5*dy}, { 75,(float)-1.5*dy},
        {-75,(float)0.5*dy}, {-75,(float)-0.5*dy},
        {-75,(float)1.5*dy}, {-75,(float)-1.5*dy},
        //
        { 150, 0},
        { 150,(float)1*dy}, { 150,(float)-1*dy},
        { 150,(float)2*dy}, { 150,(float)-2*dy},
        {-150, 0},
        {-150,(float)1*dy}, {-150,(float)-1*dy},
        {-150,(float)2*dy}, {-150,(float)-2*dy},
    };
    // =========================================
    int t_vec_len;
    t_vec_len = end(t_vec)-begin(t_vec);
    cout << "t_vec_len = " << t_vec_len << endl;
    //
    for (int i = 0; i < t_vec_len; i++) {
        //cout << t_vec.at(i)[0] << endl;
        //cout << t_vec.at(i)[1] << endl;
        translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                          hexagon_xy, "none", "blue", 1);
    }
    // -----------------------------------------
    fan_line_xy = "";
    for(int j : j_set) {
        xy_tuple = xy_tuple_array[j];
        x = to_string(get<0>(xy_tuple));
        y = to_string(get<1>(xy_tuple));
        fan_line_xy = x + "," + y + " " +"300,300";
        draw_polyline(fan_line_xy, "none", "magenta", 1);
    }
    //
    for (int i = 0; i < t_vec_len; i++) {
        for(int j : j_set) {
            fan_line_xy = "";
            xy_tuple = xy_tuple_array[j];
            x = to_string(get<0>(xy_tuple));
            y = to_string(get<1>(xy_tuple));
            fan_line_xy = x + "," + y + " " +"300,300";
            translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                              fan_line_xy, "none", "blue", 1);
        }
    }
    //
    draw_polygon(hexagon_xy, "none", "green", 1);
    //
    // 添加 border polyline
    border_xy = "100,169.5 500,169.5 500,430.5 100,430.5 100,169.5.5";
    draw_polyline(border_xy, "none", "magenta", 2);
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