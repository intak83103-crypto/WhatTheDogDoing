# WhatTheDogDoing
我的刀盾！

計算機概論期末專題：文字互動式刀盾養成遊戲。

玩家可以建立使用者、培養自己的刀盾、查看刀盾資訊、切換刀盾、進入商店購買商品，並透過背包與後續戰鬥系統進行養成。

# 功能介紹
可隨時輸入 H / Help 獲取指令提示

目前完成：

- 使用者建立、切換、刪除與改名
- 刀盾建立、切換與改名
- 刀盾資訊查看
- 商店系統
- 購買確認流程
- 金幣扣款
- 背包系統
- 商品與道具的多型架構


## Build

本專案已拆分成 `include/` 與 `src/` 多檔案架構，使用 `Makefile` 編譯。

```bash
make
```

編譯完成後會產生執行檔：

```text
main
```

如果想清除編譯產物：

```bash
make clean
```

## Run

```
./main
```

## Project Structure

```text
main.cpp          程式入口
Makefile          編譯設定
include/          class 宣告檔
src/              class 實作檔
```

請在專案根目錄執行 `make` 與 `./main`。
