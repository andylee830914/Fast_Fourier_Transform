#快速計算法期末考：快速卜瓦松解#


##演算法簡介##
###帕松方程式###
帕松方程式（英語：Poisson's equation）是數學中一個常見於靜電學、機械工程和理論物理的偏微分方程式，因法國數學家、幾何學家及物理學家帕松而得名的。
引用自[維基百科](https://zh.wikipedia.org/wiki/泊松方程)

###離散正弦變換###
離散正弦變換（DST for Discrete Sine Transform）是一種與傅立葉變換相關的變換，類似離散傅立葉變換，但是只用實數矩陣。離散正弦變換相當於長度約為它兩倍，一個實數且奇對稱輸入資料的的離散傅立葉變換的虛數部分（因為一個實奇輸入的傅立葉變換為純虛數奇對稱輸出）。有些變型裡將輸入或輸出移動半個取樣。
####DST-I####
$$X_k = \sum_{n=0}^{N-1} x_n \sin \left[\frac{\pi}{N+1} (n+1) (k+1) \right] \quad \quad k = 0, \dots, N-1$$

####反變換####
DST-I的反變換是把DST-I乘以$\frac{2}{N+1}$。

引用自[維基百科](https://zh.wikipedia.org/wiki/离散正弦变换)


###庫利－圖基快速傅立葉變換算法###
庫利－圖基快速傅立葉變換算法（Cooley-Tukey算法）是最常見的快速傅里葉變換算法。這一方法以分治法為策略遞歸地將長度為 $N = N_1\times N_2$ 的DFT分解為長度分別為 $N_1$ 和 $N_2$ 的兩個較短序列的DFT，以及與旋轉因子的複數乘法。

引用自[維基百科](http://zh.wikipedia.org/wiki/库利－图基快速傅里叶变换算法)

##作業說明##
###簡介###
本程式使用 C 語言利用快速離散正弦變換，可用於計算卜瓦松方程的解。

註：檔案位於 [midterm] (midterm) 資料夾內

###函數參數###
####主要函數####
````C
int Fast_Poisson_Solver(double **F, int N)
````

###執行測試###
####測試環境####
硬體規格：Mac mini (Late 2014) Intel Core i5 2.8GHz
<br>作業系統：Mac OSX Yosemite 10.10.4
<br>開發環境：Xcode Version 6.3.1 
####編譯####
````Shell
$ gcc -lm poisson_framework.c fft.c -o fps
````
####執行與輸出####
````Shell
$ ./fps
N=4,Gauss Elimination: 0.000006 secs
7.771561e-16,1.927711e-01
Fast Poisson Solver: 0.000075 secs
1.927711e-01
N=8,Gauss Elimination: 0.000243 secs
1.332268e-15,4.476185e-02
Fast Poisson Solver: 0.000251 secs
4.476185e-02
N=16,Gauss Elimination: 0.015943 secs
1.665335e-15,1.098931e-02
Fast Poisson Solver: 0.001129 secs
1.098931e-02
N=32,Gauss Elimination: 1.220624 secs
2.997602e-15,2.734955e-03
Fast Poisson Solver: 0.003685 secs
2.734955e-03
````	
##參考資料##
1. 老師&老師的 Github [https://github.com/ycshu/midexam](https://github.com/ycshu/midexam)
2. Todd D. Mateer, *The Fast Fourier Transform
A Mathematical Perspective*, <http://www.math.clemson.edu/~janoski/reu/2008/FFT-book.pdf>



	
