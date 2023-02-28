# ATOMS3 用画像表示

[ATOMS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen?variant=43676991258881)で動作する，SPIFFS 上にある画像を次々と表示するプログラムです。表示方法にはボタンを押すたびに画像を表示する「手動モード」と，一定間隔で画像が表示される「自動モード」があります。

このプログラムは[PlatformIO IDE](https://platformio.org/platformio-ide)環境でコンパイルすることを想定しています。

## 表示する画像の転送方法

表示する 128px x 128px の画像ファイル（PNG，JPEG，BMP）を`data`ディレクトリに置きます。

PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して設定ファイルを SPIFFS にアップロードします。

## 実行方法

ATOMS3 を起動すると，SPIFFS の`/data`ディレクトリにある画像ファイル（PNG，JPEG，BMP）ファイルを順に表示します。

画面の向きはデフォルトでは USB Type-C の差し込み口を下にした向き（`M5.Lcd.setRotation(0)`）になっています。向きを変えたいときは，`M5.Lcd.setRotation()`の引数に渡す数字を変更してください。

- `0`（差し込み口が下）
- `1`（差し込み口が右）
- `2`（の差し込み口が上）
- `3`（の差し込み口が左）

表示方法は以下の 2 通りです。

1. 手動モード  
   ボタンを押すたびに表示する画像を切り替えます。
2. 自動モード  
   一定間隔（デフォルトは 3 秒）で画像を切り替えます。

通常は手動モードで起動します。ボタンを押しながら起動すると自動モードになります。

起動すると以下の画面が表示されます。

```text
*** Auto Mode *** もしくは *** Manual Mode ***
Image Files:
  画像ファイル1
  画像ファイル2
  ...
  画像ファイルN
```

SPIFFS 上にファイルがない場合は，以下のように表示されます。

```text
*** Auto Mode *** もしくは *** Manual Mode ***
No image files found
```

画面に画像一覧が表示されてから一定時間（デフォルトは 3 秒）が経過すると表示モードに応じて画面に画像が表示されます。
