/*
/all/01-nix-cpp-SVG/飛機木裁切多個正三角形/
SVG-cut-equilateral-triangle-4
//
2025-03-07
2026-02-26
//
run on replit.com web platform
1MiB = 1.048MB

How to convert .SVG to PDF?
open the svg image in a browser, press Ctrl + P (print) select save as PDF.

正三角形，又稱等邊三角形 (英語：equilateral triangle),
其三個角大小相等、均為60度。

木百貨 
高雄市阿蓮區港後里122之1號
電話: 07-6314278 (現場購買請先預約)
service@woodmall.com.tw

5mm 飛機木 巴爾沙木 實木板 10x90cm (10入) NT$891
雷射裁切服務 (雷射切割機)

Convert SVG to DXF Online - Aspose

ShareCAD
Free online CAD Viewer ...
Autodesk Viewer

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
       tx_int, ty_int;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
float dx, dy, x_pos, y_pos, r;
int j, k, xy_items = 0;
int i_set[] = {0,1,2,3,4,5};
//
tuple<float, float> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-4.svg");
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
    tx_int = to_string(get<0>(tXY_tuple));
    ty_int = to_string(get<1>(tXY_tuple));
    string transform_string = "translate(" +
                              tx_int + " "  + 
                              ty_int + ")";
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
                        int stroke_width)
{
    tx_int = to_string(get<0>(tXY_tuple));
    ty_int = to_string(get<1>(tXY_tuple));
    string transform_string = "translate(" +
                              tx_int + " "  + 
                              ty_int + ")";
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
void rotate_polygon(tuple<float,float>tXY_tuple,
                    tuple<int,int>cXY_tuple, 
                    int degree, 
                    string polygon_xy, 
                    string fill_color, 
                    string stroke_color, 
                    int stroke_width)
{
    tx_int = to_string(get<0>(tXY_tuple));
    ty_int = to_string(get<1>(tXY_tuple));
    cx_int = to_string(get<0>(cXY_tuple));
    cy_int = to_string(get<1>(cXY_tuple));
    string transform_string = "rotate(" + 
                              to_string(degree) + " " + 
                              cx_int + " " + 
                              cy_int + ") " + 
                              "translate(" +
                              tx_int + " " + 
                              ty_int + ")";
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
// ----------------------------------------------------
//
int main() {
    cout << endl;
    cout << "App main() running ..." << endl;   
    cout << "裁切 244 正三角形" << endl;  
    cout << "  " << endl;  
    //  
    // 檢查文件是否成功打開
    if (!svgFile.is_open()) {
        std::cerr << "無法打開SVG文件！" << std::endl;
        return 1;
    }
    // cout means "character output"
    // 寫入SVG頭部, SVG default color is black
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"900px\" height=\"400px\" viewbox=\"0,250,900,350\" preserveAspectRatio=\"xMinYMin meet\">" 
    //
    //svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"650px\" height=\"400px\">" 
            << std::endl;
    //
    dy = 25.0f;
    // r*sin(i*Pi/3)=25.0
    r = 25/sin(Pi/3);
    // r = 28.8675
    cout << "   r = " << r << endl;
    cout << "10*r = " << 10*r << endl;
    cout << "31*r = " << 31*r << endl;
    dx = r*cos(Pi/3);
    // --------------------------------------------------------
    //
    // 添加 h polyline
    int x0, x1, y0, y1;
    x0 = 0;
    x1 = 900;
    for (int i = 0; i < 3; i++) {
        y0 = 300 + i*25;
        y1 = 300 + i*25;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_h_xy, "none", "gray", 1);
    }
    //
    for (int i = 1; i < 3; i++) {
        y0 = 300 - i*25;
        y1 = 300 - i*25;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_h_xy, "none", "gray", 1);
    }
    //   
    // 添加  red polyline for right side
    line_1_xy = "895,250 895,350";
    cout << line_1_xy << endl;
    draw_polyline(line_1_xy, "none", "red", 1);
    //
    // 添加 polyline
    line_1_xy = "0,300 " + to_string(r) + ",350";
    cout << line_1_xy << endl;
    draw_polyline(line_1_xy, "none", "gray", 1);
    //
    line_1_xy = to_string(30*r) + ",250 " +  to_string(31*r) + ",300";
    cout << line_1_xy << endl;
    draw_polyline(line_1_xy, "none", "gray", 1);
    //
    line_1_xy = "0,250 " + to_string(2*r) + ",350";
    cout << line_1_xy << endl;
    draw_polyline(line_1_xy, "none", "gray", 1);
    //
    for (int i = 1; i < 30; i++) {
        translate_polyline(make_tuple(i*r, 0), 
                           line_1_xy, "none", "gray", 1);
    } // end for
    //
    // for right most side
    line_2_xy = to_string(31*r) + ",300 " + to_string(30*r) + ",350";
    cout << line_2_xy << endl;
    draw_polyline(line_2_xy, "none", "gray", 1);
    //
    line_2_xy = to_string(r) + ",250 0,300";
    cout << line_2_xy << endl;
    draw_polyline(line_2_xy, "none", "gray", 1);
    //
    line_2_xy = to_string(2*r) + ",250 0,350";
    cout << line_2_xy << endl;
    draw_polyline(line_2_xy, "none", "gray", 1);
    //
    for (int i = 1; i < 30; i++) {
        translate_polyline(make_tuple(i*r, 0), 
                           line_2_xy, "none", "gray", 1);
    } // end for
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