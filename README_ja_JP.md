[In English](README.md)

# ATOMS3 用画像表示

[ATOMS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen?variant=43676991258881)で動作する，SPIFFS 上にある画像を次々と表示するプログラムです。表示方法にはボタンを押すたびに画像を表示する「手動モード」と，一定間隔で画像を表示する「自動モード」があります。

このプログラムは[PlatformIO IDE](https://platformio.org/platformio-ide)環境でコンパイルすることを想定しています。

## 表示する画像の転送方法

SPIFSS はこのリポジトリにあるパーティションテーブル`no_ota_8MB.csv`を使用して 7 MiB の容量を確保しています。

表示する 128px x 128px の画像ファイル（PNG，JPEG，BMP）を`data`ディレクトリに置きます。

PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して画像ファイルを SPIFFS にアップロードします。

## 設定ファイル

`data/image-viewer.json`を SPIFFS に転送すると，自動モードのオン・オフと自動モードのときの画像の切り替え間隔（ミリ秒）を指定することができます。設定ファイルがない場合は自動モード（`AutoMode`）はオフ（`false`），切り替え間隔（`AutoModeInterval`）は 3 秒（3000 ミリ秒）になっています。

```json
{
  "AutoMode": false,
  "AutoModeInterval": 3000
}
```

## 実行方法

ATOMS3 を起動すると，SPIFFS にある画像ファイル（PNG，JPEG，BMP）を順に表示します。画面の向きは ATOMS3 の向きに合わせて自動的に変わります。

表示方法は以下の 2 通りです。

1. 手動モード  
   ボタンを押すたびに表示する画像を切り替えます。
2. 自動モード  
   一定間隔で画像を切り替えます。

通常は設定ファイルで指定したモードで起動します。ボタンを押しながら起動すると，設定にかかわらず自動モードになります。

起動すると以下の画面が表示されます。設定ファイルがない場合`Config:`の情報は表示されません。

```text
Image Viewer v0.0.2
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
Mode:
 Manual, Auto or Auto(Forced)
Image Files:
 画像ファイル1
 画像ファイル2
 ...
 画像ファイルN
```

SPIFFS 上にファイルがない場合は，以下のように表示されます。

```text
Image Viewer v0.0.2
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
Mode:
 Manual, Auto or Auto(Forced)
No image files found
```

画面に画像一覧が表示されてから一定時間（デフォルトは 3 秒）が経過すると表示モードに応じて画面に画像が表示されます。
