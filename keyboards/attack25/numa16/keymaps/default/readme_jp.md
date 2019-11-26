# The numATTACK16 Universal Layout
## 配列

### Default Layer

```
 ,-----------------------.             
 |NumLk|  /  |  *  |  -  |             
 |-----+-----+-----+-----|
 |  7  |  8  |  9  |     |
 |-----+-----+-----|  +  |
 |  4  |  5  |  6  |     |  Tab momentary on...RGB Layer
 |-----+-----+-----+-----|
 |  1  |  2  |  3  |     |  Del momentary on...FN Layer
 |-----+-----+-----| Ent |
 |  0  | 00  |  .  |     |
 `------------------------
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
### Attack25 keyboard 'default' keymap: convenient command line option
##    make ATTACK25=<options> attack25:defualt
##    option= back | under | both | 1led | na | ios
##    ex.
##      make ATTACK25=under    attack25:defualt
##      make ATTACK25=under,ios attack25:defualt
##      make ATTACK25=back     attack25:default
##      make ATTACK25=back,na  attack25:default
##      make ATTACK25=back,ios attack25:default
##      make ATTACK25=1led     attack25:default

```

## カスタマイズに使用できるオプションについて

```

back...バックライトLEDを有効にする場合（キーキャップ側を照らす25個のLEDを実装した場合）
under...アンダーグロウLEDを有効にする場合（底面側を照らす5個のLEDを実装した場合）
both...バックライトLED25個の後にアンダーグロウLED5個を接続した場合
1led...SW1の部分にのみ実装したLEDを有効にする場合（LEDの実装はバックライト、アンダーグロウのどちらでもかまいませんが、バックライトの方がメンテナンスが容易）
na...RGBのアニメーションをオフにする場合
ios...iPad/iPhoneなどのiOS機器に接続する場合（消費電力を制限します）

※keiriおよびkeiri_macは通常RGBバックライトを実装出来ません（アンダーおよび1LEDは実装可能）

```

## カスタマイズを使用したビルドコマンド例

make ATTACK25=back attack25:default
バックライトLEDを有効にするオプションを付与してdefaultキーマップのファームをビルドします

