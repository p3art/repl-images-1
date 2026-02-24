/*
All/01-nix-cpp-SVG/旗山中山路95號-Hexagon/
SVG-hexagon-4
//
2024-08-18
2025-09-13
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
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"600px\" height=\"600px\">" 
            << std::endl;
    //
    // 添加 border polyline
    border_xy = "0,0 600,0 600,600 0,600 0,0";
    draw_polygon(border_xy, "lightsteelblue", "sandybrown", 4);
    //
    // 添加 grid h line
    int x0, x1, y0, y1;
    x0 = 0;
    x1 = 600;
    for (int i = 0; i < 4; i++) {
        y0 = 300 + i*87;
        y1 = 300 + i*87;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_h_xy, "none", "gray", 1);
    }
    //
    for (int i = 1; i < 4; i++) {
        y0 = 300 - i*87;
        y1 = 300 - i*87;
        line_h_xy = to_string(x0) + ',' + 
                    to_string(y0) + ' ' + 
                    to_string(x1) + ',' + 
                    to_string(y1);
        draw_polyline(line_h_xy, "none", "gray", 1);
    }
    //
    // 添加 grid v line
    int i_max = 7;
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
    // 添加SVG Text
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
    // --------------------------------------------------------
    for (int i = 39, increment = 87; i < 600; i += increment) {
        text_x = "5";
        text_y = to_string(i+20);
        text = to_string(i);
        draw_text(text_x, text_y, "Verdana", "17", "black", text);
    } // end for
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
    //
    int t_vec_len;
    t_vec_len = end(t_vec)-begin(t_vec);
    cout << "t_vec_len = " << t_vec_len << endl;
    //
    for (int i = 0; i < t_vec_len; i++) {
        //cout << t_vec.at(i)[0] << endl;
        //cout << t_vec.at(i)[1] << endl;
        if (i < 4) 
            translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                              hexagon_xy, "none", "green", 1);
        else if (i >= 4 && i < 12)
            translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                              hexagon_xy, "none", "red", 1);
        else 
            translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                              hexagon_xy, "none", "green", 1);
    }
    // ============================================================
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
            if (i < 4) {
                translate_polyline(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]),
                                   fan_line_xy, "none", "green", 1);
            } else if (i >= 4 && i < 12) {
                translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                                             fan_line_xy, "none", "red", 1);
            } else {
                translate_polygon(make_tuple(t_vec.at(i)[0], t_vec.at(i)[1]), 
                                  fan_line_xy, "none", "green", 1);
            }
        }
    }
    //
    draw_polygon(hexagon_xy, "none", "blue", 1);
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