# The VIA Attack25 Layout for MAC/WIN
## 配列

### Default Layer

```
 ,-----------------------------.             
 |NumLk|  /  |  *  |  -  | Esc |             
 |-----+-----+-----+-----+-----|
 |  7  |  8  |  9  |  +  |ScrLk|  ScrLk momentary on...FN Layer
 |-----+-----+-----+-----+-----|
 |  4  |  5  |  6  |BkTab|PrtSc|  PrtSc momentary on...RGB Layer
 |-----+-----+-----+-----+-----|
 |  1  |  2  |  3  | Tab | Del |
 |-----+-----+-----+-----+-----|
 |  0  | 00  |  .  |Enter|BkSpc|
 `------------------------------
```

### FN Layer

```
 ,-----------------------------.             
 | F10 | F11 | F12 |     |     |             
 |-----+-----+-----+-----+-----|
 |  F7 |  F8 |  F9 |     |     |
 |-----+-----+-----+-----+-----|
 |  F4 |  F5 |  F6 |     |     |
 |-----+-----+-----+-----+-----|
 |  F1 |  F2 |  F3 |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 `------------------------------
```
 
### RGB Layer

```
 ,-----------------------------.             
 | TOG | MODF| HINC| SINC| VINC|             
 |-----+-----+-----+-----+-----|
 | RST | MODR| HDEC| SDEC| VDEC|
 |-----+-----+-----+-----+-----|
 |PLAIN|BREAT| SPI |     |     |
 |-----+-----+-----+-----+-----|
 |SWIRL|SNAKE| SPD |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 `------------------------------
```


## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make attack25:default
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make attack25:default:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make attack25:default:clean
```

## カスタマイズ

コマンドラインからオプションを指定してビルドすることが出来ます。

```
### Attack25 keyboard 'via' keymap: convenient command line option
##    make ATTACK25=<options> attack25:via
##    option= back | under | both | 1led | matrix | na | ios | win
##    ex.
##      make ATTACK25=under    attack25:via
##      make ATTACK25=under,ios attack25:via
##      make ATTACK25=back     attack25:via
##      make ATTACK25=back,matrix  attack25:via
##      make ATTACK25=back,na  attack25:via
##      make ATTACK25=back,ios attack25:via
##      make ATTACK25=1led     attack25:via
##      make ATTACK25=win     attack25:via
##    このVIA用キーマップではオプションを付けなくてもbothが有効になります（VIA上でLEDがコントロールできます）
##    デフォルトは、ホスト接続時にMacintoshでもWindowsのNumLock的なレイアウトが可能になるモードが優先になります。
##    接続時にWindows用の動作をするWindowsモード優先となるようにするには、ATTACK=winのオプションを付与してビルドしてください。
##    なお、どちらのモードからもキーコンビネーションによりもう一つのモードへ切り替えることは出来ます（電源が切れると優先されるモードに戻ります）。
```

## カスタマイズに使用できるオプションについて

```

back...バックライトLEDを有効にする場合（キーキャップ側を照らす25個のLEDを実装した場合）
under...アンダーグロウLEDを有効にする場合（底面側を照らす5個のLEDを実装した場合）
both...バックライトLED25個の後にアンダーグロウLED5個を接続した場合
1led...SW1の部分にのみ実装したLEDを有効にする場合（LEDの実装はバックライト、アンダーグロウのどちらでもかまいませんが、バックライトの方がメンテナンスが容易）
matrix...バックライトLED25個を実装、もしくはそれに加えてアンダーグロウLEDを5個実装した際に疑似RGBマトリックス方式を選ぶ場合
na...RGBのアニメーションをオフにする場合
ios...iPad/iPhoneなどのiOS機器に接続する場合（消費電力を制限します）
win...Windowsモード優先にする場合

```

## カスタマイズを使用したビルドコマンド例

make ATTACK25=back,win attack25:via
バックライトLEDを有効にするオプションを付与してviaキーマップのファームをビルドします

