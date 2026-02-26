/*
SVG-hexagon-3-rotate-method
2024-08-15
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
const float alpha   = 1.0; 
int j, k, xy_items = 0;
float dy, x_pos, y_pos;
//
tuple<float, float> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-3.svg");
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
void translate_polygon(tuple<int,int>tXY_tuple, 
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
void rotate_polygon(tuple<int,int>tXY_tuple,
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
                              tx_int + " "  + 
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
        x_pos = cx + r*cos(i*Pi/3);
        y_pos = cy + r*sin(i*Pi/3);
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
        cout << x_int << " " << y_int << endl;
        //
        hexagon_xy = hexagon_xy + x_int + "," + y_int + " ";
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
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"600px\" height=\"600px\">" 
            << std::endl;
    //
    // 添加 border polyline
    border_xy = "0,0 600,0 600,600 0,600 0,0";
    draw_polygon(border_xy, "lightsteelblue", "sandybrown", 4);
    //
    // 添加 grid h line
    int i_max = 7;
    int x0, x1, y0, y1;
    x0 = 0;
    x1 = 600;
    for (int i = 0; i < i_max; i++) {
        y0 = i * 100;
        y1 = i * 100;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_h_xy, "none", "gray", 1);
    }
    //
    // 添加 grid v line
    i_max = 7;
    y0 = 0;
    y1 = 600;
    for (int i = 0; i < i_max; i++) {
        x0 = i * 100;
        x1 = i * 100;
        line_v_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_v_xy, "none", "gray", 1);
    }
    //
    // 添加SVG圖形
    k = 0;
    for (int i = 5, increment = 100; i < 600; i += increment) {
        text_x = to_string(i);
        text_y = "20";
        text = to_string(k);
        draw_text(text_x, text_y, "Verdana", "18", "black", text);
        k = k + 100;
    } // end for
    //
    text_x = "562";
    text_y = "20";
    text = to_string(k);
    draw_text(text_x, text_y, "Verdana", "18", "black", text);
    // -------------------------------------------------------
    k = 100;
    for (int i = 120, increment = 100; i < 600; i += increment) {
        text_x = "5";
        text_y = to_string(i);
        text = to_string(k);
        draw_text(text_x, text_y, "Verdana", "18", "black", text);
        k = k + 100;
    } // end for
    //
    text_x = "5";
    text_y = "590";
    text = to_string(k);
    draw_text(text_x, text_y, "Verdana", "18", "black", text);
    //
    make_hexagon_tuple(300, 300, 50.0);
    xy_tuple_to_string();
    draw_polygon(hexagon_xy, "none", "blue", 1);
    // cout << round(-100*sqrt(3)/2.0) << endl;
    dy = round(-100*sqrt(3)/2.0);
    translate_polygon(make_tuple(0,dy), 
                      hexagon_xy, "none", "red", 1);
    //
    // positive angle value, the rotation will be clockwise
    // negative angle value, the rotation will be counterclockwise
    rotate_polygon(make_tuple(0,dy), 
                   make_tuple(300,300), 60, 
                   hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(0,dy), 
           make_tuple(300,300), 120, 
           hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(0,dy), 
           make_tuple(300,300), 180, 
           hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(0,dy), 
           make_tuple(300,300), 240, 
           hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(0,dy), 
           make_tuple(300,300), 300, 
           hexagon_xy, "none", "darkgreen", 1);
    /*
    translate_polygon(hexagon_xy, "none", "red", 1);
    rotate_polygon(make_tuple(300,300), 120, hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(300,300), 240, hexagon_xy, "none", "magenta", 1);
    */
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