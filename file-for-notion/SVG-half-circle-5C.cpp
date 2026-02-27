/*
SVG-half-circle-5C
2024-08-13
2026-02-26
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
       arc_xy,
       text_x,
       text_y,
       text,
       circle_xy,
       x_int,
       y_int;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
const float alpha   = 1.0; 
int j, k, xy_items = 0;
//
tuple<int, int> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
array<tuple<float, float>, 61> arc_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-5C.svg");
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
void make_arc_tuple(int cx, int cy, float r, int start, int end) {
    float xx = 0.0f, yy = 0.0f;
    int k = 1;
    if (start < end) {
        arc_tuple_array[0] = make_tuple(cx, cy);
        for (int i = start, increment = 6; i < end+1; i += increment) {
            arc_tuple_array[k] = make_tuple(cx+r*cos(i*two_Pi/360), 
                                               cy+r*sin(i*two_Pi/360));
            k++;
        } // end for
        arc_tuple_array[k] = make_tuple(cx, cy);
        xy_items = k+1;
    } // end if
}
//
void show_arc_tuple_value(void) {
    j = 0;
    for (int i = 0; i < xy_items; i++) {
        //
        xy_tuple = arc_tuple_array[i];
        cout << "i: " << i << endl;
        cout << "x: " << get<0>(xy_tuple) << endl;
        cout << "y: " << get<1>(xy_tuple) << endl;
        cout << "--------------------" << endl;
    } // end for  
}
//
void arc_tuple_to_string(void) {
    j = 0;
    arc_xy = "";
    for (int i = 0; i < xy_items; i++) {
        //
        xy_tuple = arc_tuple_array[i];
        x_int = to_string(round(get<0>(xy_tuple)));
        y_int = to_string(round(get<1>(xy_tuple)));
        x_int.erase (x_int.begin() + x_int.rfind('.'), x_int.end());
        y_int.erase (y_int.begin() + y_int.rfind('.'), y_int.end());
        //
        arc_xy = arc_xy + x_int + "," + y_int + " ";
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
    make_arc_tuple(100, 0, 100.0, 0, 180);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(100, 200, 100.0, 180, 360);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(  0, 300, 100.0, -90, 90);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(200, 300, 100.0, 90,270);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(100, 400, 100.0, 0, 180);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(100, 600, 100.0, 180, 360);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    // ---------------------------------------
    //
    make_arc_tuple(200, 100, 100.0, -90, 90);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(400, 100, 100.0, 90, 270);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(300, 200, 100.0, 0, 180);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(300, 400, 100.0, 180, 360);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(200, 500, 100.0, -90, 90);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(400, 500, 100.0, 90, 270);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    // --------------------------------------
    //
    make_arc_tuple(500, 0, 100.0, 0, 180);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(500, 200, 100.0, 180, 360);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(400, 300, 100.0, -90, 90);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(600, 300, 100.0, 90,270);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(500, 400, 100.0, 0, 180);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
    //
    make_arc_tuple(500, 600, 100.0, 180, 360);
    arc_tuple_to_string();
    draw_polygon(arc_xy, "cyan", "black", 3);
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