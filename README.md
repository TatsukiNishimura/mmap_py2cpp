# mmap_py2cpp
https://github.com/husty530/mmap-template を使って、

画像をcppで読み込んでpythonに投げるテストコード

# 補足
cppでは/share にshared.poolというファイルを作成し、そこに画像のバイナリを書き込む

pyではshared.poolを読み込んで配列として読み込み、画像に変換する

# 使い方
1. 
```
catkin_make
```

2. 
```
chmod +x receive_img_node.py
```

3.
```
roscore
```

4. 
```
rosrun mmap_py2cpp receive_img_node.py 
```

5.
```
rosrun mmap_py2cpp write_node
```

6. imgにreceive.jpgが生成される
