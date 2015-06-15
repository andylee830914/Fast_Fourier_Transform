#快速計算法期末考：快速乘法#


##演算法簡介##
###數論轉換###
數論轉換是一種計算摺積的快速演算法。計算摺積的快速演算法中最常用的一種是使用快速傅里葉變換，然而快速傅立葉變換具有一些實現上的缺點，舉例來說，資料向量必須乘上複數係數的矩陣加以處理，而且每個複數係數的實部和虛部是一個正弦及餘弦函數，因此大部分的係數都是浮點數，也就是說，我們必須做複數而且是浮點數的運算，因此計算量會比較大，而且浮點數運算產生的誤差會比較大。

引用自[維基百科](https://zh.wikipedia.org/wiki/數論轉換)

###Multiplication algorithm - Fourier transform methods###

![Integer multiplication by FFT](https://upload.wikimedia.org/wikipedia/commons/thumb/6/69/Integer_multiplication_by_FFT.svg/551px-Integer_multiplication_by_FFT.svg.png)

引用自[維基百科](https://en.wikipedia.org/wiki/Multiplication_algorithm)

##作業說明##
###簡介###
本程式使用 C 語言實作快速數論轉換的演算法，可用於計算乘法。

註：檔案位於 [midterm] (midterm) 資料夾內

###函數參數###
####主要函數####
````C
int fft(long *x, long *y, int N,int prime,long W);
````
####參數說明####

		*x：初始序列
		*y：輸出值序列
  	     N：執行點數
     prime：用於計算mod的質數
      	 W：W^N = 1 (mod prime)
     
	   
####初始值設定####

輸入 a 與 b 的值。


###執行測試###
####測試環境####
硬體規格：Mac mini (Late 2014) Intel Core i5 2.8GHz
<br>作業系統：Mac OSX Yosemite 10.10.4
<br>開發環境：Xcode Version 6.3.1 
####編譯####
````Shell
$ gcc -lm main.c fft.c -o fft
````
####執行與輸出####
````Shell
$ ./fft
hello midterm 
Input number a and b (MAXIMUM DIGITS:400)
999999999999999999999999999999
999999999999999999999999999999
999999999999999999999999999999 * 999999999999999999999999999999 = 999999999999999999999999999998000000000000000000000000000001
0.000125 secs
````	
##參考資料##
1. 老師&老師的 Github [https://github.com/ycshu/midexam](https://github.com/ycshu/midexam)
2. Todd D. Mateer, *The Fast Fourier Transform
A Mathematical Perspective*, <http://www.math.clemson.edu/~janoski/reu/2008/FFT-book.pdf>



	
