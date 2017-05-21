# 快速計算法期末考：快速離散餘弦變換


## 演算法簡介
### 離散傅立葉變換
離散餘弦變換（英語：DCT for Discrete Cosine Transform）是與傅立葉變換相關的一種變換，類似於離散傅立葉變換，但是只使用實數。離散餘弦變換相當於一個長度大概是它兩倍的離散傅立葉變換，這個離散傅立葉變換是對一個實偶函數進行的（因為一個實偶函數的傅立葉變換仍然是一個實偶函數），在有些變形裡面需要將輸入或者輸出的位置移動半個單位（DCT有8種標準類型，其中4種是常見的）。

#### DCT-II
$$f_m =
   \sum_{k=0}^{n-1} x_k \cos \left[\frac{\pi}{n} m \left(k+\frac{1}{2}\right) \right]$$

引用自[維基百科](https://zh.wikipedia.org/wiki/离散余弦变换)


### 庫利－圖基快速傅立葉變換算法
庫利－圖基快速傅立葉變換算法（Cooley-Tukey算法）是最常見的快速傅里葉變換算法。這一方法以分治法為策略遞歸地將長度為 $N = N_1\times N_2$ 的DFT分解為長度分別為 $N_1$ 和 $N_2$ 的兩個較短序列的DFT，以及與旋轉因子的複數乘法。

引用自[維基百科](http://zh.wikipedia.org/wiki/库利－图基快速傅里叶变换算法)

## 作業說明
### 簡介
本程式使用 C 語言實作 radix-2、radix-3、radix-5 的演算法，可用於計算 $N=2^p\times 3^q \times 5^r$ 點的離散餘弦變換。

註：檔案位於 [midterm] (midterm) 資料夾內

### 函數參數
#### 主要函數
````C
int dst(double *x_r, double *x_i, double *y_r, double *y_i, int N)
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
hello final : DCT
input 2^p 3^q 5^r : p q r =>2 2 2
N=900
0.001076 secs
````	
## 參考資料
1. 老師&老師的 Github [https://github.com/ycshu/midexam](https://github.com/ycshu/midexam)
2. Todd D. Mateer, *The Fast Fourier Transform
A Mathematical Perspective*, <http://www.math.clemson.edu/~janoski/reu/2008/FFT-book.pdf>



	
