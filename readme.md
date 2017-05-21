# 快速傅立葉轉換及其應用

### 期中考 - 快速傅立葉轉換
 * [快速傅立葉轉換](https://github.com/andylee830914/Fast_Fourier_Transform) ：Implement of radix-2, radix-3 & radix-5 FFT algorithm

### 期末考 - 快速傅立葉轉換的應用
 * [離散餘弦轉換](https://github.com/andylee830914/Fast_Fourier_Transform/tree/DCT) ：Implement of radix-2, radix-3 & radix-5 DCT algorithm
 * [離散正弦轉換](https://github.com/andylee830914/Fast_Fourier_Transform/tree/DST) ：Implement of radix-2 DST algorithm
 * [快速乘法](https://github.com/andylee830914/Fast_Fourier_Transform/tree/multiplication) ：Application of General Discrete Fourier transform
 * [快速卜瓦松解](https://github.com/andylee830914/Fast_Fourier_Transform/tree/FPS) ：Implement of Fast Poisson Solver algorithm. Application of 2D DST.

# 快速計算法期中考：快速傅立葉轉換


## 演算法簡介
###離散傅立葉變換
對於 N 點序列 $\left\{x[n]\right\}_{0\le n <N}$，它的離散傅立葉變換（DFT）為
$$\hat{x}[k]=\sum_{n=0}^{N-1} e^{-i\frac{2\pi}{N}nk}x[n] \qquad k = 0,1,\ldots,N-1$$
其中 $e$ 是自然對數的底數，$i$ 是虛數單位。

引用自[維基百科](http://zh.wikipedia.org/wiki/离散傅里叶变换)


### 庫利－圖基快速傅立葉變換算法
庫利－圖基快速傅立葉變換算法（Cooley-Tukey算法）是最常見的快速傅里葉變換算法。這一方法以分治法為策略遞歸地將長度為 $N = N_1\times N_2$ 的DFT分解為長度分別為 $N_1$ 和 $N_2$ 的兩個較短序列的DFT，以及與旋轉因子的複數乘法。

引用自[維基百科](http://zh.wikipedia.org/wiki/库利－图基快速傅里叶变换算法)

## 作業說明
### 簡介
本程式使用 C 語言實作 radix-2、radix-3、radix-5 的演算法，可用於計算 $N=2^p\times 3^q \times 5^r$ 點的離散傅立葉變換。

註：檔案位於 [midterm] (midterm) 資料夾內

### 函數參數
#### 主要函數
````C
int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N)
````
#### 參數說明

	*x_r：初始序列實部
	*x_i：初始序列虛部
	*y_r：輸出值序列實部
	*y_i：輸出值序列虛部
	   N：執行點數

#### 初始序列設定

目前設定 $\left\{x[n]=n\right\}_{0\le n <N}$ 為初始序列


### 執行測試
#### 測試環境
硬體規格：Mac mini (Late 2014) Intel Core i5 2.8GHz
<br>作業系統：Mac OSX Yosemite 10.10.4
<br>開發環境：Xcode Version 6.3.1
#### 編譯
````Shell
$ gcc -lm main.c fft.c -o fft
````
#### 執行與輸出
````Shell
$ ./fft
hello midterm
input 2^p 3^q 5^r : p q r =>5 5 5
N=24300000
17.514198 secs
````
## 參考資料
1. 老師&老師的 Github [https://github.com/ycshu/midexam](https://github.com/ycshu/midexam)
2. Todd D. Mateer, *The Fast Fourier Transform
A Mathematical Perspective*, <http://www.math.clemson.edu/~janoski/reu/2008/FFT-book.pdf>
