/*
/all/01-nix-cpp-SVG/飛機木裁切多個正三角形/
SVG-cut-equilateral-triangle-6-cm
#
2025-03-10
2026-02-26
//
run on replit.com web platform
1MiB = 1.048MB

How to convert .SVG to PDF?
open the svg image in a browser, press Ctrl + P (print) select save as PDF.

正三角形，又稱等邊三角形 (英語：equilateral triangle),
其三個角大小相等、均為60度。

巴爾沙木(飛機木)，重量是世界上最輕的木材，它的木材質地雖輕，可是結構卻很牢固，是航空、航海以及其他特種工藝的寶貴材料。

木百貨 
高雄市阿蓮區港後里122之1號
電話: 07-6314278 (現場購買請先預約)
service@woodmall.com.tw

5mm 飛機木 巴爾沙木 實木板 10x90cm (10入) NT$891
雷射裁切服務 (雷射切割機)

Convert SVG to DXF Online - Aspose

Autodesk Viewer

1in = 96px or user units
1in = 2.54cm
2.54cm = 96px
1cm = 96/2.54
1cm ≅ 37.795px or user units
90 cm = 90 * 37.795 = 3779.5px

極客雷射 ----------------------
地址:高雄市仁武區八德一路92號
(請先聯繫客服後再前往，以免撲空)
上班時間:每周一至五，早上九點至下午六點

【詢價範例自行修改】
信件主旨：
檔案形式：
材質厚度：
尺寸：
數量：
備註：
傳到這裡或者請寄到：
geeklaser1111@gmail.com

常備材料有:
椴木合板3/5/7mm
黑胡桃木合板3/5mm
松木合板3/5mm
加拿大檜木3.5/5mm
北美冷杉3.5/5mm
※可自備材料或聯繫我們詢問其他材料唷
1.密集板
2.白俄椴木板，因表面顏色淺又具備明顯的木質紋路，
不僅適合作為雷射切割的木板材質，在雕刻時邊緣不容易出現焦黑的狀況，
也更容易凸顯出圖像線條，此外良好的彈性使製作出來的產品不易變形或龜裂，
常用於家具、工藝品、雷射雕刻等用途。

3.楊木合板也是雷射切割木板種類中常見的品項之一，
表面為淡白色且具有均勻的紋理，非常適合作為雷射切割和雕刻材質，
由於其質料輕、強度高，適用於玩具、木質拼圖等。

檔案格式:
1.Illustrator(俗稱AI)。
2.CAD，2004年DXF，並備註尺寸
3.其餘向量軟體(SVG)

加工方式:打磨、上色、上漆、包裝等需確定清楚好方便報價

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
       line_3_xy,
       line_4_xy,
       line_5_xy,
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
//
int in_01_by_px = 90;
int cm_01_by_px = 36;
int cm_10_by_px = 350;
int cm_90_by_px = 3150;
int j, k, xy_items = 0;
int i_set[] = {0,1,2,3,4,5};
//
tuple<float, float> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("5mm-飛機木-巴爾沙木-10x90cm-file-6.svg");
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
    cout << "裁切 N組 4個連在一起的正三角形" << endl;  
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
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"3150px\" height=\"350px\">" << std::endl;
    //
    // dy = 68.75f;
    dy = (311-36)/4.0f;
    cout << "dy = " << dy << endl;
    // r*sin(i*Pi/3)=25.0
    r = dy/sin(Pi/3);
    // r = 79.3857
    cout << "   r = " <<     r << endl;
    cout << "10*r = " << 10*r << endl;
    cout << "38*r = " << 38*r << endl;
    dx = r*cos(Pi/3);
    //
    cout << "  " << endl;
    cout << " 1inch = " << in_01_by_px << endl;
    cout << " 1cm   = " << cm_01_by_px << endl;
    cout << "10cm   = " << cm_10_by_px << endl;
    cout << "90cm   = " << cm_90_by_px << endl;
    cout << "  " << endl;
    //
    // --------------------------------------------------------
    //
    // 添加 border
    border_xy = "0,0 3150,0 3150,350 0,350 0,0";
    draw_polyline(border_xy, "none", "green", 3);
    cout << "out border_xy = " << border_xy << endl;
    cout << "  " << endl;
    //
    // ========================================================
    //
    line_3_xy = to_string(36+3.0*r) + ",36 " +
                to_string(36+1.0*r) + ",36 " +
                to_string(36+0.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+1.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+1.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+2.5*r) + ',' + to_string(36+1*dy);
    //
    draw_polyline(line_3_xy, "none", "red", 1);
    //
    for (int i = 2; i < 36; i=i+2) {
        translate_polyline(make_tuple(i*r, 0), 
                           line_3_xy, "none", "red", 1);
    } // end for
    //
    line_3_xy = to_string(36+3.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+3.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+2.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+3.0*r) + ",36 " + 
                to_string(36+3.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+4.0*r) + ",36 " +
                to_string(36+4.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+2.5*r) + ',' + to_string(36+1*dy);
    //
    translate_polyline(make_tuple(34*r, 0), line_3_xy, "none", "red", 1);
    //
    // ========================================================
    //
    line_4_xy = to_string(36+1.5*r) + ',' + to_string(36+1*dy) + ' ' +
                to_string(36+2.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+2.5*r) + ',' + to_string(36+1*dy);
    //
    draw_polyline(line_4_xy, "none", "red", 1);
    //
    for (int i = 2; i < 45; i=i+2) {
        translate_polyline(make_tuple(i*r, 0), 
                           line_4_xy, "none", "red", 1);
    } // end for
    //
    line_5_xy = to_string(36+1.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+0.5*r) + ',' + to_string(36+3*dy) + ' ' +
                to_string(36+1.0*r) + ',' + to_string(36+4*dy) + ' ' +
                to_string(36+2.0*r) + ',' + to_string(36+4*dy);
    //
    draw_polyline(line_5_xy, "none", "red", 1);
    //
    for (int i = 1; i < 37; i++) {
        translate_polyline(make_tuple(i*r, 0), 
                           line_5_xy, "none", "red", 1);
    } // end for
    //
    line_5_xy = to_string(36+1.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+0.5*r) + ',' + to_string(36+3*dy) + ' ' +
                to_string(36+1.0*r) + ',' + to_string(36+4*dy);
    //
    translate_polyline(make_tuple(37*r, 0), 
                       line_5_xy, "none", "red", 1);
    //
    line_5_xy = to_string(36+1.0*r) + ',' + to_string(36+2*dy) + ' ' +
                to_string(36+1.5*r) + ',' + to_string(36+3*dy) + ' ' +
                to_string(36+1.0*r) + ',' + to_string(36+4*dy);
    //
    translate_polyline(make_tuple(37*r, 0), 
                       line_5_xy, "none", "red", 1);
    //
    line_5_xy = to_string(36+0.5*r) + ',' + to_string(36+3*dy) + ' ' +
                to_string(36+1.5*r) + ',' + to_string(36+3*dy);
    //
    translate_polyline(make_tuple(37*r, 0), 
               line_5_xy, "none", "red", 1);
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