/*
All/01-nix-cpp-SVG/旗山中山路95號-Hexagon/
SVG-hexagon-7-translate-BOMB
//
2024-08-18
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

https://www.google.com/maps/search/%E9%AB%98%E9%9B%84%E5%B8%82%E6%97%97%E5%B1%B1%E5%8D%80%E4%B8%AD%E5%B1%B1%E8%B7%AF95%E8%99%9F-hexagon/@22.8877359,120.4794134,17z/data=!3m1!4b1?authuser=0&entry=ttu
台灣本土現存最早的伊斯蘭(回教)幾何圖案
吳基福的老宅 建於日據大正14年(1925年)
在1915(民國4)年由日本人所進行的臺灣宗教調查的成果《臺灣宗教調查報告書》中，看不到任何伊斯蘭教的相關紀錄。
台灣歷史學家連橫撰寫的《臺灣通史》，出版於1920年，看不到任何伊斯蘭教的相關紀錄。

清真寺文化資產價值評估報告書 (2020-01)
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
       line_h_xy, line_v_xy,
       text, text_x, text_y,
       x_int, y_int,
       tx, ty;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
float dy, x_pos, y_pos; 
int j, k, xy_items = 0;
//
tuple<int, int> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-7.svg");
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
            <<     polygon_xy 
            <<     "\" fill=\""   + fill_color + 
                   "\" stroke=\"" + stroke_color +
                   "\" stroke-width=\"" + to_string(stroke_width) + "\"> " + 
               "</polygon> " 
            << endl;
}
//
void translate_hexagon_1(tuple<float,float>tXY_tuple, 
                         string polygon_xy, 
                         string fill_color, 
                         string stroke_color, 
                         int stroke_width)
{
    tx = to_string(get<0>(tXY_tuple));
    ty = to_string(get<1>(tXY_tuple));
    svgFile << "<polygon points=\"" 
            <<     polygon_xy 
            <<     "\" fill=\""   + fill_color + 
                   "\" stroke=\"" + stroke_color +
                   "\" stroke-width=\"" + to_string(stroke_width) + "\"> " 
                   "<animateTransform " +
                        "attributeName=\"transform\" " +
                        "begin=\"0s\" " +
                        "dur=\"4s\" " +
                        "type=\"translate\" " +
                        "from=\"0 0\" " +
                        "to=\"" + tx + " " + ty + "\" " +
                        "fill=\"freeze\"> " +
                   "</animateTransform> " +
               "</polygon> "    
            << endl;
}
//
void translate_hexagon_2(tuple<float,float>tXY_tuple, 
                         string polygon_xy, 
                         string fill_color, 
                         string stroke_color, 
                         int stroke_width)
{
    tx = to_string(get<0>(tXY_tuple));
    ty = to_string(get<1>(tXY_tuple));
    svgFile << "<polygon points=\"" 
            <<     polygon_xy 
            <<     "\" fill=\""   + fill_color + 
                   "\" stroke=\"" + stroke_color +
                   "\" stroke-width=\"" + to_string(stroke_width) + "\"> " 
                   "<animateTransform " +
                        "attributeName=\"transform\" " +
                        "begin=\"6s\" " +
                        "dur=\"9s\" " +
                        "type=\"translate\" " +
                        "from=\"0 0\" " +
                        "to=\"" + tx + " " + ty + "\" " +
                        "fill=\"freeze\"> " +
                   "</animateTransform> " +
               "</polygon> "    
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
    // 添加SVG圖形
    make_hexagon_tuple(300, 300, 100.0);
    xy_tuple_to_string_hexagon();
    dy = 100.0*sqrt(3.0)/2;
    //
    translate_hexagon_1(make_tuple( 0,-2*dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_1(make_tuple( 0, 2*dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_1(make_tuple( 150, dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_1(make_tuple( 150,-dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_1(make_tuple(-150, dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_1(make_tuple(-150,-dy), hexagon_xy, "none", "red", 1);
    translate_hexagon_2(make_tuple( 0,0),     hexagon_xy, "none", "green", 1);
    //draw_polygon(hexagon_xy, "none", "green", 1);
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