# ATOMS3 用画像表示

[ATOMS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen?variant=43676991258881)で動作する，SPIFFS 上にある画像を次々と表示するプログラムです。表示方法にはボタンを押すたびに画像を表示する「ボタンモード」と，一定間隔で画像が表示される「自動モード」があります。

このプログラムは[PlatformIO IDE](https://platformio.org/platformio-ide)環境でコンパイルすることを想定しています。

## 表示する画像の転送方法

表示する 128px x 128px の画像ファイル（PNG，JPEG，BMP）を`data`ディレクトリに置きます。

PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して設定ファイルを SPIFFS にアップロードします。

## 実行方法

SPIFFS の`/data`ディレクトリにある画像ファイル（PNG，JPEG，BMP）ファイルを順に表示します。

表示方法は以下の 2 通りです。

1. ボタンモード  
   ボタンを押すたびに表示する画像を切り替えます。
2. 自動モード  
   一定間隔（`AUTO_MODE_INTERVAL_MS`（ミリ秒），デフォルトは 3 秒）で画像を切り替えます。

通常はボタンモードで起動します。ボタンを押しながら起動すると自動モードで起動します。

起動すると以下の画面が表示されます。

```text
*** Auto Mode *** もしくは *** Button Mode ***
Image Files:
  画像ファイル1
  画像ファイル2
  ...
  画像ファイルN
```

SPIFFS 上にファイルがない場合は，以下のように表示されます。

```text
*** Auto Mode *** もしくは *** Button Mode ***
No image files found
```

画面に画像一覧が表示されてから 3 病後（`START_INTERVAL_MS`（ミリ秒）で設定）に画像が表示されます。
