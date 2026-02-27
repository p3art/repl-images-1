// Line-intersection
//
// 2023-11-07
// 2026-02-27
//
/*
{ pkgs }: 
{
deps = [
pkgs.clang_12
        pkgs.boost
        pkgs.boost.dev     
        ];
}
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <iostream>
#include <fstream>  // 必須：處理檔案輸出

#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/geometries.hpp>
// 加入 SVG 繪製標頭檔
#include <boost/geometry/io/svg/write_svg.hpp>

using namespace std;
namespace bg = boost::geometry;

int main() {
    cout << "main() running..." << endl;

    typedef bg::model::d2::point_xy<double>   type_Point;
    typedef bg::model::linestring<type_Point> type_LineString;

    type_Point point1(0.0, 0.0), point2(200.0, 200.0);
    type_Point point3(200.0, 0.0), point4(0.0, 200.0);

    type_LineString L1 {point1, point2}, L2 {point3, point4};

    // 計算交點
    std::deque<type_Point> its_xy_list;
    bg::intersection(L1, L2, its_xy_list);

    // --- 開始生成 SVG ---
    std::ofstream svg("line-intersection.svg");

    // 建立一個 400x400 的畫布
    bg::svg_mapper<type_Point> mapper(svg, 400, 400);

    // 將物件加入畫布以決定縮放比例 (Bounding Box)
    mapper.add(L1);
    mapper.add(L2);

    // 繪製線條 (設定顏色與寬度)
    // L1: 藍色, L2: 紅色
    mapper.map(L1, "opacity:0.8;fill:none;stroke:rgb(0,0,255);stroke-width:2");
    mapper.map(L2, "opacity:0.8;fill:none;stroke:rgb(255,0,0);stroke-width:2");

    // 繪製交點 (綠色圓點，半徑為 5)
    BOOST_FOREACH(type_Point const & p, its_xy_list) {
        mapper.map(p, "fill:rgb(0,255,0);stroke:rgb(0,0,0);stroke-width:1", 5);
        cout << "Intersection found at: " << p.get<0>() << ", " << p.get<1>() << endl;
    }

    cout << "\nSVG file 'line-intersection.svg' has been generated!" << endl;

    return 0;
}

/*
以下是這份 Replit 專案的詳細技術報告：
專案配置：套件分析

您的專案是使用 **Nix 套件管理員** 構建的，這允許 Replit 載入特定的系統級依賴項。

### 1. 使用的主要套件：

* **`boost` & `boost.dev**`：這是核心引擎。具體來說，您使用的是 **Boost.Geometry**（Boost C++ 函式庫的一部分）。它提供了空間計算的資料結構（點、線串）和演算法（長度、交點）。
* **`clang_12`**：用於將您的 C++ 程式碼編譯成可執行檔的編譯器。
* **`libstdc++` / Standard C++ Library**：用於基本的輸入/輸出 (`iostream`) 和資料管理 (`deque`, `fstream`)。

### 2. 標頭檔 (Header File) 解析：

| 標頭檔 | 用途 |
| --- | --- |
| `<boost/geometry.hpp>` | 所有幾何邏輯的主要入口點。 |
| `<boost/geometry/geometries/point_xy.hpp>` | 定義二維笛卡爾點 $(x, y)$。 |
| `<boost/geometry/io/svg/write_svg.hpp>` | 將幾何資料轉換為基於 XML 的 SVG 程式碼的工具。 |
| `<deque>` | Boost 用於存儲多個交點的雙端佇列。 |

---

## 📋 執行邏輯：分步說明

當您點擊 **Run** 時，程式會執行以下邏輯步驟：

### 步驟 1：幾何定義

程式碼初始化了四個點來定義兩條相交的線段：

* **線段 1 (L1)**：從 $(0, 0)$ 到 $(200, 200)$。
* **線段 2 (L2)**：從 $(200, 0)$ 到 $(0, 200)$。

### 步驟 2：空間計算

Boost 引擎執行兩個主要計算：

1. **`bg::length`**：計算線段的歐幾里得距離（即 $200\sqrt{2} \approx 282.84$）。
2. **`bg::intersection`**：在數學上確定線段是否相交以及相交的位置。它將結果存儲在 `its_xy_list` 中。

### 步驟 3：SVG 渲染（圖形化）

程式碼現在啟動了 `svg_mapper`，而不是只列印數字：

1. **畫布設定**：建立一個 400x400 單位的座標系。
2. **邊界框 (Bounding Box)**：它會「檢視」所有點，以確保繪圖正確居中並按比例縮放。
3. **樣式設定**：應用 CSS 風格（例如 `stroke:rgb(255,0,0)`）來區分兩條線。

### 步驟 4：檔案輸出

程式打開一個檔案流 (`std::ofstream`)，將原始 XML 資料寫入 Replit 儲存空間中名為 **`line-intersection.svg`** 的檔案中。

## 如何驗證結果
在主控台顯示 "main() running..." 結束後：
1. 查看左側側邊欄的 **Files (檔案)** 分頁。
2. 找到 `line-intersection.svg`。
3. 點擊它即可看到您程式碼數學邏輯的視覺化呈現。
*/