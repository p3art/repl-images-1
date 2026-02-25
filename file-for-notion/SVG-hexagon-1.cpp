/*
All/01-nix-cpp-SVG/旗山中山路95號-Hexagon/
SVG-hexagon-1
//
2024-08-14
2025-09-13
//
run on replit.com web platform
1MiB = 1.048MB

我們可以將正六邊形分割成4個三角形，每個三角形內角合為180度，4x180度=720度。
因此，每個正六邊形的內角為：720度/6=120度。
正六邊形：內角為120度，邊長為外接圓半徑。
何謂正？ 6內角相等，6邊長相等，六頂點至形心的長度等於邊長。

若以圖1的概念，將圖案密鋪於平面上，不是正解。

東京池袋太陽城: 地板紋飾(水舞秀)

台灣本土現存最早的伊斯蘭(回教)幾何圖案
此圖案所在建物產權屬於吳基福家族， 建於日據大正14年(1925年)

根據行政院公布的〈法律統一用字表〉的規定，
凡作為名詞時要用「紀錄」，作動詞時則用「記錄」。

在1915(民國 4)年由日本人所進行的臺灣宗教調查的成果《臺灣宗教調查報告書》中，看不到任何伊斯蘭教的相關紀錄。
台灣歷史學家連橫撰寫的《臺灣通史》，出版於1920年，看不到任何伊斯蘭教的相關紀錄。
文化部_清真寺文化資產價值評估報告書 (2020-01)，報告書所列本土清真寺/伊斯蘭教/回教文化資產，其創建年代皆晚於旗山中山路95號建物。

此圖案位於一樓走廊外牆，
Google 地圖街景 元大證券 旗山分公司
*/

/*
"\""                  # 雙引號
"\'"                  # 單引號
"\\"                  # 反斜線（backslash）
"\0"                  # 空字元(NULL)
"\a"                  # 蜂鳴器警報 (alert bell)
"\b"                  # 退格（backspace）
"\e"                  # 跳脫
"\f"                  # 換頁（formfeed）
"\n"                  # 換行（newline）
"\r"                  # 輸入鍵 (Enter)
"\t"                  # Tab（horizontal tab）
"\v"                  # 垂直 Tab（vertical tab）
"\888"                # 八進位 ASCII 字元
"\xFF"                # 十六進位 ASCII 字元
"\uFFFF"              # 十六進位萬國碼字元 unicode
"\u{0}".."\u{10FFFF}" # 十六進位萬國碼字元
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
string hexagon_xy,
       circle_xy,
       border_xy,
       line_h_xy,
       line_v_xy,
       text_x,
       text_y,
       text,
       x_int,
       y_int;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
float x_pos, y_pos; 
int j, k, xy_items = 0;
//
tuple<int, int> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("./svg/file-1.svg");
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
void translate_polygon(string polygon_xy, string fill_color, string stroke_color, int stroke_width)
{
    svgFile << "<polygon points=\"" 
            << polygon_xy 
            << "\" fill=\""   + fill_color + 
               "\" stroke=\"" + stroke_color +
               "\" stroke-width=\"" + to_string(stroke_width) +
               "\" transform=\"translate(100 0)\" />"
            << endl;
}
//
void rotate_polygon(tuple<int,int>XY_tuple, 
                    int degree, 
                    string polygon_xy, 
                    string fill_color, 
                    string stroke_color, 
                    int stroke_width)
{
    x_int = to_string(get<0>(XY_tuple));
    y_int = to_string(get<1>(XY_tuple));
    //string transform_string = "rotate(" + x_int + " " + y_int + " 25)" + " translate(20 0)";
    string transform_string = "rotate(" + 
                              to_string(degree) + 
                              " " + 
                              x_int + 
                              " " + 
                              y_int + ") " + 
                              "translate(100 0)";
    cout << transform_string << endl;
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
void make_circle_tuple(int cx, int cy, float r, int start, int end) {
    int k = 0;
    if (start < end) {
        for (int i = start, increment = 6; i < end+1; i += increment) {
            xy_tuple_array[k] = make_tuple(cx+r*cos(i*two_Pi/360), 
                                           cy+r*sin(i*two_Pi/360));
            k++;
            xy_items++;
        } // end for
    } // end if
}
//
void make_hexagon_tuple(int cx, int cy, float r) {
    k = 0;
    for (int i=0; i < 6; i++) {
        x_pos = cx+r*cos(i*Pi/3);
        y_pos = cy+r*sin(i*Pi/3);
        xy_tuple_array[k] = make_tuple(x_pos,y_pos);
        k++;
    } // end for
    xy_items = k;
}
//
void xy_tuple_to_string_hexagon(void) {
    j = 0;
    hexagon_xy = "";
    for (int i = 0; i < xy_items; i++) {
        xy_tuple = xy_tuple_array[i];
        x_int = to_string(get<0>(xy_tuple));
        y_int = to_string(get<1>(xy_tuple));
        //
        hexagon_xy = hexagon_xy + x_int + "," + y_int + " ";
    } // end for  
}
//
void xy_tuple_to_string_circle(void) {
    j = 0;
    circle_xy = "";
    for (int i = 0; i < xy_items; i++) {
        xy_tuple = xy_tuple_array[i];
        x_int = to_string(get<0>(xy_tuple));
        y_int = to_string(get<1>(xy_tuple));
        //
        circle_xy = circle_xy + x_int + "," + y_int + " ";
    } // end for  
}
// ----------------------------------------------------
//
int main() {
    cout << endl;
    cout << "C++ repl main() running ..." << endl;
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
    make_circle_tuple(300, 300, 100.0, 0, 360);
    xy_tuple_to_string_circle();
    draw_polyline(circle_xy, "none", "navy", 1);
    //
    make_hexagon_tuple(300, 300, 100.0);
    xy_tuple_to_string_hexagon();
    draw_polygon(hexagon_xy, "none", "blue", 1);
    translate_polygon(hexagon_xy, "none", "red", 1);
    rotate_polygon(make_tuple(300,300), 120, hexagon_xy, "none", "darkgreen", 1);
    rotate_polygon(make_tuple(300,300), 240, hexagon_xy, "none", "magenta", 1);
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
    cout << "exit shell ..." << endl;
    return 0;
}