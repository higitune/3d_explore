3d_explore
==========

B3時代のOpenCV OpenGL実験で制作したモノです。

動作時のスクリーンショットは以下のとおりです

![directory-mode](https://raw.githubusercontent.com/higitune/3d_explore/master/directory-mode.png)
![file-mode1](https://raw.githubusercontent.com/higitune/3d_explore/master/file-mode1.png)
![file-mode2](https://raw.githubusercontent.com/higitune/3d_explore/master/file-mode2.png)

以下readme.txtから抜粋

/* * * * * * * * * * * * *
 *      3D Explorer    	 *
 * * * * * * * * * * * * */

/* * * *   概要   * * * */
3D Explorerはディレクトリ構造を3Dで表示し、視覚的にディレクトリ構造を理解するための自己満ソフトです。

/* * * *   機能   * * * */
起動ディレクトリ以下のディレクトリ構造を取得し、3D表示する。
その3Dディレクトリ構造上を移動することができる。ちょっとかっこいい。
現在のディレクトリに保存されているファイルを取得、一覧することができる。その際JPGファイルは表示することができる。その他のファイルはファイル名のみ表示する。これもちょっとかっこいい。

/* * * *   マニュアル   * * * */
左クリックによるドラッグ：カレントディレクトリを中心とした視点の移動。
右クリックによるドラッグ：視点の遠近を移動。
f:同じ階層のディレクトリを一つ進む
b:一つ戻る
u:階層を一つ上がる
d:階層を一つ下がる
o:ディレクトリモードとファイル一覧モードを切り替える。
q/Q/ESC:3D Explorerを閉じる
