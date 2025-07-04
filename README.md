# KpqClean_ver2
Benchmark on Korean Post Quantum Cryptography version 2!

## What is KPQClean?
This project was inspired by PQClean (<https://github.com/PQClean/PQClean>).

We removed the dependencies of KpqC algorithms and benchmarked them in the same environment (Intel, Ryzen processors and Apple Silicon).

There are still a lot of works to be done, but the current version may provide basic performance comparisons between KpqC algorithms.

## Source code version
'Round 2 Submission' means the code published in KpqC competition Round 2.

When updated source code was used, indicate the date the source code was updated.

**Note:** The following four algorithms have been selected as the final standardized KpqC algorithms:  
- **KEM:** NTRU+, SMAUG-T  
- **DSA:** AIMer, HAETAE  

These standardized algorithms have been incorporated using their latest source code.  

### PKE/KEM

| Algorithm   | Submission Status | Code Update                      | Commit / Tag     | GitHub Repository                             |
|-------------|-------------------|----------------------------------|------------------|------------------------------------------------|
| **NTRU+**   | Round 2           | 2025-06-26                       | 96ff02b          | https://github.com/ntruplus/ntruplus/tree/main |
| PALOMA      | Round 2           | –                                | –                | –                                              |
| **SMAUG-T** |  Round 2               | 2025-05-25 (code), 2024-08-21 (KAT) | HEAD / c5acb07   | https://github.com/hmchoe0528/SMAUG-T_public   |
| REDOG       | Round 2           | –                                | –                | –                                              |

### Digital Signature

| Algorithm | Submission Status | Code Update	       | Link                                                    |
|-----------|-------------------|------------|---------------------------------------------------------|
| **AIMer**  |   Round 2             | 2024-08-01            | https://github.com/samsungsds-research-papers/AIMer                         |
| **HAETAE** |  Round 2    |  -       | (No official repository or pending announcement)                           |
| MQSign    |   Round 2         | –          | –                                                       |
| NCCSign   | Round 2            | –          | –                                                       |


## Benchmark clean result
Performance results for the updated (latest) code will be provided at a later date.  
The measurements shown below reflect the performance of the Round 2 submission code.

### Testing Environment1
* OS: Ubuntu 22.04
* CPU: Ryzen 7 4800H (2.90 GHz)
* RAM: 16GB
* Compiler: gcc 11.4.0
* Optimization Level: -O3

### Testing Environment2
* OS: Ubuntu 23.10.1
* CPU: Intel i5-8259U (2.30 GHz)
* RAM: 16GB
* Compiler: gcc 13.2.0
* Optimization Level: -O3

### Testing Environment3
* OS: macOS Sonoma 14.4.1
* CPU: Apple M2 (3.23 GHz)
* RAM: 8GB
* Compiler: Apple clang 15.0.0
* Optimization Level: -O3

### Benchmark method
* We used 'rdtsc' instruction to calculate time consumption.
* For Apple Silicon, we used a cycle count inspired by the work of Dougall Johnson (https://gist.github.com/dougallj/5bafb113492047c865c0c8cfbc930155#file-m1_robsize-c-L390).
* Each algorithms 10,000 iterated, average value of the operation cycle is used.

### PKE/KEM (Environment1, -O3)
<details>
<summary>PKE/KEM-Env1-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm     		|  Keygen(Avr.)			| Encapsulation(Avr.) 	| Decapsulation(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|NTRUplus-KEM576			| 253,031 		 		| 85,541	 | 110,140 		 		| 
|NTRUplus-KEM768			| 354,704 		 		| 106,690		|141,220  		 		| 
|NTRUplus-KEM864			| 354,592		 		  |128,823  				| 170,729  		 	| 
|NTRUplus-KEM1152			| 659,905 		 		|164,274  				|219,767  		 		| 
|NTRUplus-PKE576			|329,712  		 		|83,245   				|107,302  		 		| 
|NTRUplus-PKE768			|310,102  		 		|107,632  				|140,803  		 		| 
|NTRUplus-PKE864			| 348,486 		 		|128,465  				|169,804  		 		| 
|NTRUplus-PKE1152			|637,652 		 		  |164,153  				|230,312  		 		| 
|PALOMA-128			        |131,189,151  		|133,345  				| 8,424,379 			| 
|PALOMA-192		            |650,967,499  		|176,834   		  	| 41,793,889  		| 
|PALOMA-256			        | 769,657,392 	  | 215,487				  | 43,735,841 		 	| 
|SMAUG-T1			        | 143,625 		 		| 66,403 				  | 104,474 		 		| 
|SMAUG-T3		            | 193,935 		 		| 243,970 				  | 421,956 		 		| 
|SMAUG-T5			        | 1,566,958 		 		| 1,663,364 				| 1,877,628  		 	| 
|SMAUG-Timer			    | 69,234 		 		| 76,165 				  |112,282  		 		| 
</details>

### Digital Signature (Environment1, -O3)
<details>
<summary>Digital Signature-Env1-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm     		|  Keygen(Avr.)			| Sign(Avr.) 	| Verify(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|HAETAE-2			            | 1,160,435 		 	| 5,032,357 				| 158,529 		 		| 
|HAETAE-3			            | 2,103,397		 		| 2,739,863 				| 275,419 		 		| 
|HAETAE-5			            | 1,998,427 		 	| 3,369,567 				| 342,870 		 		| 
|AIMer128f		            | 159,134 		 		| 3,742,915 				| 3,545,576 		 	| 
|AIMer128s		            | 108,704 		 		| 26,541,270 				| 27,013,406 		 	| 
|AIMer192f		            | 201,497 		 		| 8,745,805 				| 7,800,523		 	| 
|AIMer192s		            | 187,591 		 		| 65,094,493 			| 62,821,167 		| 
|AIMer256f		            | 413,606 		 		| 16,706,302 				| 15,776,925 		 	| 
|AIMer256s		            | 454,476  		   	| 119,340,970  			| 119,925,648 		| 
|MQSign_MQLR_256_72_46		| 74,764,874 		 	| 463,964  				  | 733,587 		 		| 
|MQSign_MQLR_256_112_72		|286,180,511  		| 1,289,973 				| 2,016,272 		 	| 
|MQSign_MQLR_256_148_96		|750,300,850  	| 2,762,744 				|4,307,611 		 		| 
|MQSign_MQRR_256_72_46		|100,975,612  		| 809,523  				| 706,565 		 	| 
|MQSign_MQRR_256_112_72		|387,732,599  		|2,057,398  				|1,986,691  		 	| 
|MQSign_MQRR_256_148_96		|997,169,889  	|4,298,168   			|4,272,864 		 	| 
|NCCSign-1		            |300,401  		 		| 479,198 				  |285,502   		 		| 
|NCCSign-3		            | 352,126 		 		|600,143  				  | 356,543 		 		| 
|NCCSign-5		            |455,065  		 		|1,585,378  				  |591,947  		 		| 
</details>


### PKE/KEM (Environment2, -O3)
<details>
<summary>PKE/KEM-Env2-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm             |  Keygen(Avr.)            | Encapsulation(Avr.)     | Decapsulation(Avr.)    |
|-------------:     | -------------:         | -------------:        | -------------:        |
|NTRUplus-KEM576            |209,949                    |81,678                  | 108,342                  | 
|NTRUplus-KEM768            |232,394                    | 101,297                 |125,636                   | 
|NTRUplus-KEM864            |228,042                    | 109,680                 |145,575                | 
|NTRUplus-KEM1152            | 558,996                   |152,931               |212,747                | 
|NTRUplus-PKE576            |207,953                    | 78,594              |98,820                   | 
|NTRUplus-PKE768            |234,498                  |102,024              |129,611                   | 
|NTRUplus-PKE864            |223,966                    |110,043                  | 142,710               | 
|NTRUplus-PKE1152            | 558,631                   |151,692               |212,804               | 
|PALOMA-128                  |147,357,235           |87,441               |8,033,779           | 
|PALOMA-192                | 700,965,299          | 136,963              |41,802,948       | 
|PALOMA-256                  |819,112,319           | 200,987                 | 45,735,541      | 
|SMAUG-T1                    |128,685                    |58,942              | 74,463                  | 
|SMAUG-T3                  |176,020                    | 98,497              | 128,148                  | 
|SMAUG-T5                    |233,829                    | 165,370              | 184,943              | 
|SMAUG-Timer                |61,064                    |58,115               | 73,249               | 
</details>
</details>

### Digital Signature (Environment2, -O3)
<details>
<summary>Digital Signature-Env2-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm             |  Keygen(Avr.)            | Sign(Avr.)     | Verify(Avr.)    |
|-------------:     | -------------:         | -------------:        | -------------:        |
|HAETAE-2                        |1,067,698                 | 1,866,070                 | 170,103                  | 
|HAETAE-3                        | 2,155,146                 | 7,057,356                  |285,845                   | 
|HAETAE-5                        | 2,225,344              |3,389,114                  | 355,867                  | 
|AIMer128f                    |90,968                     | 3,288,188                  | 2,961,062               | 
|AIMer128s                    | 146,339                    |23,324,902                  |22,820,605           | 
|AIMer192f                    |175,871                   |7,292,073               | 6,832,062              | 
|AIMer192s                    | 223,472                  | 57,739,339               | 56,700,184          | 
|AIMer256f                    | 448,151               | 15,639,023              | 14,820,473          | 
|AIMer256s                    |488,242               | 116,361,684              |114,818,217          | 
|MQSign_MQLR_256_72_46        |70,289,113           |423,941                     |656,693               | 
|MQSign_MQLR_256_112_72        | 270,156,039         |1,138,677                   | 1,709,939              | 
|MQSign_MQLR_256_148_96        |682,362,334       |2,370,417                  |3,454,074               | 
|MQSign_MQRR_256_72_46        | 101,307,620         | 753,662               | 643,609              | 
|MQSign_MQRR_256_112_72        | 372,556,356          | 1,812,867                 |1,747,581                  | 
|MQSign_MQRR_256_148_96        |913,690,602       | 3,660,222              |3,359,634               | 
|NCCSign-1                    | 205,450                  | 1,161,522                    |  288,198                 | 
|NCCSign-3                    | 280,512                 | 884,954                   |  391,048                 | 
|NCCSign-5                    | 416,020                  | 1,049,172                  | 630,294                 | 

</details>

### PKE/KEM (Environment3, -O3)
<details>
<summary>PKE/KEM-Env3-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm     		|  Keygen(Avr.)			| Encapsulation(Avr.) 	| Decapsulation(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|NTRUplus-KEM576			| 165,658  		 		| 64,129 				| 75,639 		 		| 
|NTRUplus-KEM768			| 164,191  		 		| 74,306 				| 85,110 		 		| 
|NTRUplus-KEM864			| 173,677  		 		| 84,111 				| 100,120  		 	| 
|NTRUplus-KEM1152			| 415,075  		 		| 110,187  			| 137,234  		 	| 
|NTRUplus-PKE576			| 158,546  		 		| 59,646  			| 68,249 		 		| 
|NTRUplus-PKE768			| 164,528  		 	  | 74,715  			| 85,527 		 		| 
|NTRUplus-PKE864			| 173,810  		 		| 85,018 				| 100,446  		 	| 
|NTRUplus-PKE1152			| 416,032  		 		| 110,185  			| 137,379 		 	| 
|PALOMA-128			      | 117,973,298  		| 58,041  			| 8,063,384  		| 
|PALOMA-192		        | 561,356,686  		| 81,429  			| 39,805,620  	| 
|PALOMA-256			      | 682,457,804  		| 97,059 				| 42,658,333  	| 
|SMAUG-T1			        | 41,363  		 		| 39,849  			| 48,758 		 		| 
|SMAUG-T3		          | 75,708  		 		| 64,798  			| 78,298 		 		| 
|SMAUG-T5			        | 114,736  		 		| 116,486  			| 132,236 		 	| 
|SMAUG-Timer			    | 40,950  		 		| 39,688  			| 47,789  		 	| 
</details>
</details>

### Digital Signature (Environment3, -O3)
<details>
<summary>Digital Signature-Env3-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm     		|  Keygen(Avr.)			| Sign(Avr.) 	| Verify(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|HAETAE-2			            | 863,297 		 	  | 2,670,407 				| 136,342 		 		| 
|HAETAE-3			            | 1,803,954		 		| 2,138,297				  | 238,286 		 		| 
|HAETAE-5			            | 1,982,518 		 	| 2,619,443 				| 299,583 		 		| 
|AIMer128f		            | 71,406 		 		  | 7,817,433				  | 7,189,155  		 	| 
|AIMer128s		            | 71,503 		 		  | 63,790,236 				| 65,001,324  		| 
|AIMer192f		            | 171,355 		 		| 12,310,116  			| 11,319,655 		 	| 
|AIMer192s		            | 172,591 		 		| 97,870,611 			  | 101,761,394 		| 
|AIMer256f		            | 390,021  		     | 33,221,322			  | 29,626,790  		| 
|AIMer256s		            | 385,169  		    | 249,178,468  			| 253,957,585 		| 
|MQSign_MQLR_256_72_46		| 114,471,983  		| 925,457  				  | 1,389,234 	 		| 
|MQSign_MQLR_256_112_72		| 548,203,425 		| 3,146,747  				| 5,193,515 		 	| 
|MQSign_MQLR_256_148_96		| 1,579,111,570  	| 7,179,713 				| 11,774,727 	 		| 
|MQSign_MQRR_256_72_46		| 140,680,597 		| 1,392,204   			| 1,360,443 		 	| 
|MQSign_MQRR_256_112_72		| 648,075,641  		| 4,831,374 				| 5,081,924		 		| 
|MQSign_MQRR_256_148_96		| 1,816,681,327  	| 11,128,693  			| 12,079,540 	 		| 
|NCCSign-1		            | 167,169 		 		| 706,939				    | 217,624 		 		| 
|NCCSign-3		            | 218,250	 		    | 454,822 				  | 279,255 	 		    | 
|NCCSign-5		            | 337,004 		 		| 1,142,698				  | 445,731	 		    | 

</details>


## Benchmark AVX2 result

* ### Testing Environment1
* OS: Ubuntu 23.10.1
* CPU: Intel i5-8259U (2.30 GHz)
* RAM: 16GB
* Compiler: gcc 13.2.0
* Optimization Level: -O3

### Testing Environment2
* OS: Ubuntu 23.10.1
* CPU: Ryzen 7 4800H (2.90 GHz)
* RAM: 16GB
* Compiler: gcc 13.2.0
* Optimization Level: -O3

### PKE/KEM (Environment1, -O3)
<details>
<summary>PKE/KEM-Env1-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm     		|  Keygen(Avr.)			| Encapsulation(Avr.) 	| Decapsulation(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|NTRUplus-KEM576			| 74,709 		| 50,108 				  | 21,075 		 		| 
|NTRUplus-KEM768			| 139,922 		 		|26,990 			    | 17,193 		 		| 
|NTRUplus-KEM864			| 95,277		 		  |57,783  				| 19,382  		 	| 
|NTRUplus-KEM1152			| 159,047 		 		| 38,919 				|25,075  		 		| 
|NTRUplus-PKE576			| 80,669 		 		| 45,700  				|29,788  		 		| 
|NTRUplus-PKE768			|118,228 		 		| 29,529 				| 19,408 		 		| 
|NTRUplus-PKE864			| 95,652 		 		| 46,291 				| 30,918 		 		| 
|NTRUplus-PKE1152			| 156,861		 		  | 38,101 				|25,553  		 		| 
|SMAUG-T1(kem)			        |41,139 		 		|33,704  				  |64,401  		 		| 
|SMAUG-T1(kem 90s)			|70,489 		    |35,396  			|39,227   		 		| 
|SMAUG-T3(kem)		            |64,350 		 		|55,982  				  | 63,344 		 		| 
|SMAUG-T3(kem 90s)			|91,033 		 	|45,414 			|57,594   		 		| 
|SMAUG-T5(kem)			        |146,222  		 		|107,760  				|109,709   		 	|
|SMAUG-T5(kem 90s)			|108,447 		            |62,174   			|85,226  		 		| 

</details>

### Digital Signature (Environment1, -O3)
<details>
<summary>Digital Signature-Env1-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm     		|  Keygen(Avr.)			| Sign(Avr.) 	| Verify(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|HAETAE-2			|834,651  		 	    |4,946,575   				|67,068   		 		| 
|HAETAE-3			|1,423,068 		 		|374,489   			|128,981   		 		| 
|HAETAE-5			|1,924,879   		 	|1,077,729  			|134,969  		 		| 
|AIMer128f                    |40,172                     |811,275                   |783,010                | 
|AIMer128s                    |93,037                     |5,889,742                  |6,494,209           | 
|AIMer192f                    |99,173                   |2,210,305               |2,131,677               | 
|AIMer192s                    |97,972                   |15,833,475                |15,289,548          | 
|AIMer256f                    |236,956                |4,071,768               |3,980,184           | 
|AIMer256s                    |242,895               |29,154,407               |28,753,363          | 
|MQSign_MQLR_256_72_46		| 3,734,999		| 43,696 				| 35,239 	 		| 
|MQSign_MQLR_256_112_72		| 16,398,700 	| 116,982  			| 112,981 		 	| 
|MQSign_MQLR_256_148_96		| 41,712,325  	| 206,425 				| 218,123	 		| 
|MQSign_MQRR_256_72_46		| 5,821,709 	| 61,466   			| 34,617		 	| 
|MQSign_MQRR_256_112_72		| 24,188,893   	| 165,044 				| 111,455 	 		| 
|MQSign_MQRR_256_148_96		| 59,706,652  	| 307,147  			    | 216,810 	 		| 
|NCCSign-1		    | 246,285  		 		| 250,040  				| 165,103   		 	| 
|NCCSign-3		    | 206,074  		 		| 325,247  				| 210,895  		 		| 
|NCCSign-5		    | 309,736  		 		| 508,632  				| 340,775  		 		| 
</details>

### PKE/KEM (Environment2, -O3)
<details>
<summary>PKE/KEM-Env2-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm     		|  Keygen(Avr.)			| Encapsulation(Avr.) 	| Decapsulation(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|NTRUplus-KEM576			|73,798   		|55,179  		    | 19,814 		 		| 
|NTRUplus-KEM768			|140,673   		|37,193 			    |17,330  		 		| 
|NTRUplus-KEM864			|94,406 		 	|51,431   			| 19,302   		 	| 
|NTRUplus-KEM1152			|158,476  		|38,796   			|24,911   		 		| 
|NTRUplus-PKE576			|79,520  	    |61,034   		    |14,639    | 
|NTRUplus-PKE768			|141,808 		 	|26,999   			|17,558  		 		| 
|NTRUplus-PKE864			|80,727  		|64,812   			|21,408  		 		| 
|NTRUplus-PKE1152			| 158,938		 	|44,797   			|26,357  		 		| 
|SMAUG-T1(kem)			    | 131,751		|48,594  			|55,682  		 		| 
|SMAUG-T1(kem 90s)			|72,566 		    |74,438  			|42,832   		 		| 
|SMAUG-T3(kem)		            |162,901 		 	|74,948   			|91,347   		 		| 
|SMAUG-T3(kem 90s)			|132,416 		 	|69,773  			| 67,223  		 		| 
|SMAUG-T5(kem)			        | 224,491 		| 135,314  			| 156,083   		 	| 
|SMAUG-T5(kem 90s)			|153,995 		|76,148   			|102,099  		 		| 
</details>

### Digital Signature (Environment2, -O3)
<details>
<summary>Digital Signature-Env2-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm     		|  Keygen(Avr.)			| Sign(Avr.) 	| Verify(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|HAETAE-2			| 829,349 		 	    |699,815   				|71,242  		 		| 
|HAETAE-3			|1,463,470 		 		| 391,344 			|113,329  		 		| 
|HAETAE-5			|1,902,225  		 	| 439,008 				|134,080  		 		| 
|AIMer128f                    |109,474                     |988,392                   | 990,973               | 
|AIMer128s                    |126,120                     |7,384,692                  |7,334,755           | 
|AIMer192f                    |199,741                   | 2,693,700              |2,674,129               | 
|AIMer192s                    | 211,196                  |20,005,582                | 19,914,200         | 
|AIMer256f                    | 359,442               |5,216,095               |5,184,187           | 
|AIMer256s                    | 294,201              |42,617,762               | 42,199,394         | 
|MQSign_MQLR_256_72_46		|3,737,246 		|46,147  				|35,451  	 		| 
|MQSign_MQLR_256_112_72		|16,810,793  		|126,525   			|117,008   		 	| 
|MQSign_MQLR_256_148_96		|44,255,025   	|211,273  				| 219,523	 		| 
|MQSign_MQRR_256_72_46		|5,690,604  		| 63,070   			|35,065 		 	| 
|MQSign_MQRR_256_112_72		|24,379,382   	| 179,025 				| 120,588	 		| 
|MQSign_MQRR_256_148_96		|61,059,896   	| 300,749  			    | 237,074	 		| 
|NCCSign-1		    | 226,966 		 		| 248,743  				| 163,753  		 		| 
|NCCSign-3		    |233,022  		 		|327,080  				|  213,619		 		| 
|NCCSign-5		    | 398,589 		 		|509,618  				| 341,277 		 		| 
</details>


### Benchmark method
* We used 'rdtsc' instruction to calculate time consumption.
* Each algorithms 10,000 iterated, average value of the operation cycle is used.


## How to use
### Compile command
Use the following command for KpqC benchmarking compile.

For Intel, Ryzen processors

    make
    ./KpqC_bench
    ./PQCgenKAT
    
    make clean

For Apple Silicon

    make
    sudo ./KpqC_bench
    ./PQCgenKAT
    
    make clean

## Contact
* MinJoo Sim: <minjoos9797@gmail.com>
* HwaJeong Seo: <hwajeong84@gmail.com>

### Contributers
* (Ph.D. student) MinJoo Sim
* (Ph.D. student) SiWoo Eum
* (Ph.D. student) GyeongJu Song
* (Master student) MinWoo Lee
* (Master student) SangWong Kim
* (Master student) Minho Song
* (Associate professor) HwaJeong Seo

    
