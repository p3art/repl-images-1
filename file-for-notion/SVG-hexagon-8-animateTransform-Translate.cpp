/*
All/01-nix-cpp-SVG/旗山中山路95號-Hexagon/
SVG-hexagon-8-animateTransform-Translate
//
2024-08-18
2025-09-13
//
https://github.com/p3art/repl-images-1

回應中的 download_url：
https://raw.githubusercontent.com/p3art/repl-images-1/main/file-for-notion/SVG-hexagon-8-animateTransform-Translate.svg
這就是你可以在 Notion 中直接使用的永久原始圖片連結。

永久保存這個 Alias
在 Replit 中，如果你重啟專案，alias 可能會消失。為了讓它永遠生效，請執行以下指令將其寫入設定檔：
echo 'alias up="for file in file-for-notion/*; do filename=\$(basename \"\$file\"); content=\$(base64 -w 0 \"\$file\"); sha=\$(gh api \"/repos/p3art/repl-images-1/contents/file-for-notion/\$filename\" --jq .sha 2>/dev/null || echo \"\"); if [ -z \"\$sha\" ]; then gh api --method PUT \"/repos/p3art/repl-images-1/contents/file-for-notion/\$filename\" -f message=\"add \$filename\" -f content=\"\$content\" -f branch=\"main\"; else gh api --method PUT \"/repos/p3art/repl-images-1/contents/file-for-notion/\$filename\" -f message=\"update \$filename\" -f content=\"\$content\" -f branch=\"main\" -f sha=\"\$sha\"; fi; echo \"✅ \$filename synced\"; done"' >> ~/.bash_profile && source ~/.bash_profile

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
在1915(民國 4)年由日本人所進行的臺灣宗教調查的成果《臺灣宗教調查報告書》中，看不到任何伊斯蘭教的相關紀錄。
台灣歷史學家連橫撰寫的《臺灣通史》，出版於1920年，看不到任何伊斯蘭教的相關紀錄。
文化部_清真寺文化資產價值評估報告書(2020-01)，報告書所列本土清真寺/伊斯蘭教/回教文化資產，其創建年代皆晚於旗山中山路95號建物。

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
string fan_line_xy, 
       hexagon_xy,
       circle_xy,
       border_xy,
       line_h_xy, line_v_xy,
       text, text_x, text_y,
       x_int, y_int,
       x, y,
       tx, ty;
//
float     Pi = 3.1415926f;
float two_Pi = 3.1415926f * 2.0f;
float dy, x_pos, y_pos; 
int j, k, xy_items = 0;
int j_set[] = {1,3,5};
//
tuple<int, int> posi_xy;
tuple<float, float> xy_tuple;
array<tuple<float, float>, 61> xy_tuple_array;
//
// 創建SVG文件
std::ofstream svgFile("file-8.svg");
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
void translate_hexagon_1(tuple<float,float>tXY_tuple, 
                         string polygon_xy, 
                         string fill_color, 
                         string stroke_color, 
                         int stroke_width,
                         int begin_s, 
                         int dur_s)
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
                        "begin=\"" + to_string(begin_s) + "s\" " +
                        "dur=\"" + to_string(dur_s) + "s\" " +
                        "type=\"translate\" " +
                        "from=\"0 0\" " +
                        "to=\"" + tx + " " + ty + "\" " +
                        "fill=\"freeze\"> " +
                   "</animateTransform> " +
               "</polygon> "    
            << endl;
}
//
void translate_hexagon_2(float t1, float t2,
                         string polygon_xy, 
                         string fill_color, 
                         string stroke_color, 
                         int stroke_width,
                         int begin_s, 
                         int dur_s)
{
    tx = to_string(t1);
    ty = to_string(t2);
    svgFile << "<polygon points=\"" 
            <<     polygon_xy 
            <<     "\" fill=\""   + fill_color + 
                   "\" stroke=\"" + stroke_color +
                   "\" stroke-width=\"" + to_string(stroke_width) + "\"> " 
                   "<animateTransform " +
                        "attributeName=\"transform\" " +
                        "begin=\"" + to_string(begin_s) + "s\" " +
                        "dur=\"" + to_string(dur_s) + "s\" " +
                        "type=\"translate\" " +
                        "from=\"0 0\" " +
                        "to=\"" + tx + " " + ty + "\" " +
                        "fill=\"freeze\"> " +
                   "</animateTransform> " +
               "</polygon> "    
            << endl;
}
//
void translate_polyline_2(float t1, float t2,
                          string polyline_xy, 
                          string fill_color, 
                          string stroke_color, 
                          int stroke_width,
                          int begin_s, 
                          int dur_s)
{
    tx = to_string(t1);
    ty = to_string(t2);
    svgFile << "<polyline points=\"" 
            <<     polyline_xy 
            <<     "\" fill=\""   + fill_color + 
                   "\" stroke=\"" + stroke_color +
                   "\" stroke-width=\"" + to_string(stroke_width) + "\"> " 
                   "<animateTransform " +
                        "attributeName=\"transform\" " +
                        "begin=\"" + to_string(begin_s) + "s\" " +
                        "dur=\"" + to_string(dur_s) + "s\" " +
                        "type=\"translate\" " +
                        "from=\"0 0\" " +
                        "to=\"" + tx + " " + ty + "\" " +
                        "fill=\"freeze\"> " +
                   "</animateTransform> " +
               "</polyline> "    
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
    // 添加 border polyline
    border_xy = "0,0 600,0 600,600 0,600 0,0";
    draw_polygon(border_xy, "lightsteelblue", "sandybrown", 4);
    //
    border_xy = "100,169.5 500,169.5 500,430.5 100,430.5 100,169.5.5";
    draw_polyline(border_xy, "none", "magenta", 2);
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
    xy_tuple_to_string_hexagon();
    dy = 100.0*sqrt(3.0)/2;
    //
    vector<vector<float>> t_vec = {
        { 0, (float)1*dy}, {0, (float)-1*dy},
        //
        { 75,(float)0.5*dy}, { 75,(float)-0.5*dy},
        { 75,(float)1.5*dy}, { 75,(float)-1.5*dy},
        {-75,(float)0.5*dy}, {-75,(float)-0.5*dy},
        {-75,(float)1.5*dy}, {-75,(float)-1.5*dy},
        //
        { 150, 0}, {-150, 0},
        { 150,(float)1*dy}, { 150,(float)-1*dy},
        {-150,(float)1*dy}, {-150,(float)-1*dy},
        {0,0}
    };
    // =========================================
    int t_vec_len;
    t_vec_len = end(t_vec)-begin(t_vec);
    cout << "t_vec_len = " << t_vec_len << endl;
    //
    j = 0;
    for (int i = 0; i < t_vec_len; i++) {
        //cout << t_vec.at(i)[0] << endl;
        //cout << t_vec.at(i)[1] << endl;
        if (i+1 == t_vec_len) {
            translate_hexagon_2(t_vec.at(i)[0], t_vec.at(i)[1], hexagon_xy, "none", "green", 1, j,2);
        } else {
            translate_hexagon_2(t_vec.at(i)[0], t_vec.at(i)[1], hexagon_xy, "none", "red", 1, j,2);
        }
        // end if
        j = j + 2;
        // cout << "j = " << j << endl;
    }
    // ----------------------------------------------
    k = 32;
    for (int i = 0; i < t_vec_len; i++) {
        if (i+1 == t_vec_len) {
            for(int j : j_set) {
                fan_line_xy = "";
                xy_tuple = xy_tuple_array[j];
                x = to_string(get<0>(xy_tuple));
                y = to_string(get<1>(xy_tuple));
                fan_line_xy = x + "," + y + " " +"300,300";
                translate_polyline_2(t_vec.at(i)[0], 
                                     t_vec.at(i)[1], 
                                     fan_line_xy, 
                                     "none", "magenta", 1, k,2);
            }
        } else {
            for(int j : j_set) {
                fan_line_xy = "";
                xy_tuple = xy_tuple_array[j];
                x = to_string(get<0>(xy_tuple));
                y = to_string(get<1>(xy_tuple));
                fan_line_xy = x + "," + y + " " +"300,300";
                translate_polyline_2(t_vec.at(i)[0], 
                                     t_vec.at(i)[1], 
                                     fan_line_xy, 
                                     "none", "blue", 1, k,2);
            }
        }
        //end if
        k = k + 2;
    }
    //end for
    //
    // --------------------------------------------------
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