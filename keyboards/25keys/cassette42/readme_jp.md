# Cassette42

![cassette42](https://pbs.twimg.com/media/D63q5S0UcAE9Rfj?format=jpg&name=large)

4個のスイッチと2個のロータリーエンコーダーを搭載したオーディオコントロールパッドです。

* キーボードメンテナー: [monksoffunk](https://github.com/monksoffunk) [@monksoffunkJP](https://twitter.com/monksoffunkJP)
* 対応ハードウェア: Cassette 42 PCB
* ハードウェア販売: [遊舎工房](https://yushakobo.jp/shop/cassette42/)

ビルド環境をセットアップした後、通常のキーマップをビルドする例:

    make cassette42:default

Pro Micro RP2040互換コントローラーを使用する場合のビルド例:

    make 25keys/cassette42:default CONVERT_TO=promicro_rp2040

    qmk compile -kb 25keys/cassette42 -km default -e CONVERT_TO=promicro_rp2040

特別な理由がない限り、Remapに対応している`via`キーマップを書き込むことをお勧めします。

`via` キーマップはRemapに対応しています。Pro Micro RP2040互換コントローラー向けのビルド例:

    make 25keys/cassette42:via CONVERT_TO=promicro_rp2040

    qmk compile -kb 25keys/cassette42 -km via -e CONVERT_TO=promicro_rp2040

詳しくは、[ビルド環境のセットアップ](https://docs.qmk.fm/#/getting_started_build_tools) と
[makeの使い方](https://docs.qmk.fm/#/getting_started_make_guide) を参照してください。
QMKを初めて使う場合は、[Complete Newbs Guide](https://docs.qmk.fm/#/newbs) も参照してください。
