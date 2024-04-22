# KpqClean_ver2
Benchmark on Korean Post Quantum Cryptography version 2!

## What is KPQClean?
This project was inspired by PQClean (<https://github.com/PQClean/PQClean>).

We removed the dependencies of KpqC algorithms and benchmarked them in the same environment (Intel, Ryzen processors and Apple Silicon).

There are still a lot of works to be done, but the current version may provide basic performance comparisons between KpqC algorithms.

## Source code version
'Round 2 Submission' means the code published in KpqC competition Round 2.

When updated source code was used, indicate the date the source code was updated.

### PKE/KEM
1. NTRUplus: Round 2 Submission.
2. PALOMA: Round 2 Submission.
3. SMAUG-T: Round 2 Submission.
4. REDOG: Round 2 Submission.

### Digital Signature
1. AIMer: Round 2 Submission.
2. HAETAE: Round 2 Submission.
3. MQSign: Round 2 Submission.
4. NCCSign: Round 2 Submission.

## Benchmark result
### Testing Environment1
* OS: Ubuntu 23.01
* CPU: Ryzen 7 4800H (2.90 GHz)
* RAM: 16GB
* Compiler: gcc 13.2.0
* Optimization Level: -O3

### Testing Environment2
* OS: macOS Sonoma 14.4.1
* CPU: Apple M2 (3.23 GHz)
* RAM: 8GB
* Compiler: Apple clang 15.0.0
* Optimization Level: -O3

### Benchmark method
* We used 'rdtsc' instruction to calculate time consumption.
* For Apple Silicon, we used a cycle count inspired by the work of Dougall Johnson (https://gist.github.com/dougallj/5bafb113492047c865c0c8cfbc930155#file-m1_robsize-c-L390).
* Each algorithms 1,000 iterated, average value of the operation cycle is used.

### PKE/KEM (Environment1, -O3)
<details>
<summary>PKE/KEM-Env1-O3 Table (Unit: clock cycles)</summary>
    
|Algorithm     		|  Keygen(Avr.)			| Encapsulation(Avr.) 	| Decapsulation(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|NTRUplus-KEM576			| 332,182 		 		| 81,645				  | 104,401 		 		| 
|NTRUplus-KEM768			| 340,466 		 		| 106,755			    | 135,825 		 		| 
|NTRUplus-KEM864			| 348,919		 		  | 111,143 				| 149,990  		 	| 
|NTRUplus-KEM1152			| 712,237 		 		| 162,622 				| 222,245 		 		| 
|NTRUplus-PKE576			| 318,433 		 		| 83,165  				| 106,562 		 		| 
|NTRUplus-PKE768			| 353,751 		 		| 111,652 				| 143,420 		 		| 
|NTRUplus-PKE864			| 349,104 		 		| 110,053 				| 152,146 		 		| 
|NTRUplus-PKE1152			| 731,388		 		  | 162,449 				| 226,607 		 		| 
|PALOMA-128			        | 128,929,992 		| 131,703 				| 8,337,680 			| 
|PALOMA-192		            | 615,092,474 		| 177,833  		  	| 43,985,795  		| 
|PALOMA-256			        | 725,282,687 	  | 206,778				  | 45,836,617 		 	| 
|SMAUG-T1			        | 145,860 		 		| 47,136 				  | 62,174 		 		| 
|SMAUG-T3		            | 161,114 		 		| 85,677 				  | 117,123 		 		| 
|SMAUG-T5			        | 234,227 		 		| 136,419 				| 165,587  		 	| 
|SMAUG-Timer			    | 144,698 		 		| 46,523 				  |61,796  		 		| 
</details>

### Digital Signature (Environment1, -O3)
<details>
<summary>Digital Signature-Env1-O3 Table (Unit: clock cycles)</summary>
 
    
|Algorithm     		|  Keygen(Avr.)			| Sign(Avr.) 	| Verify(Avr.)	|
|-------------: 	| -------------: 		| -------------:		| -------------:		|
|HAETAE-2			            | 1,086,829 		 	| 5,639,462 				| 160,377 		 		| 
|HAETAE-3			            | 1,897,209		 		| 1,070,599 				| 276,481 		 		| 
|HAETAE-5			            | 2,122,213 		 	| 13,411,296 				| 333,770 		 		| 
|AIMer128f		            | 155,111 		 		| 7,236,172 				| 6,676,185 		 	| 
|AIMer128s		            | 174,830 		 		| 58,055,082 				| 58,217,757 		 	| 
|AIMer192f		            | 284,716 		 		| 13,351,108 				| 12,581,230		 	| 
|AIMer192s		            | 293,584 		 		| 102,426,567 			| 101,274,181 		| 
|AIMer256f		            | 568,675 		 		| 34,666,515 				| 32,126,343 		 	| 
|AIMer256s		            | 585,918  		   	| 268,651,783  			| 265,640,437 		| 
|MQSign_MQLR_256_72_46		| 77,336,141 		 	| 466,869  				  | 690,533 		 		| 
|MQSign_MQLR_256_112_72		| 295,578,451 		| 1,296,108 				| 2,096,399 		 	| 
|MQSign_MQLR_256_148_96		| 1,035,436,225 	| 3,950,994 				| 6,022,689		 		| 
|MQSign_MQRR_256_72_46		| 159,130,687 		| 1,151,192  				| 1,024,099 		 	| 
|MQSign_MQRR_256_112_72		| 651,080,248 		| 3,431,217 				| 3,506,125 		 	| 
|MQSign_MQRR_256_148_96		| 2,283,170,414 	| 13,836,357  			| 13,635,281		 	| 
|NCCSign-1		            | 286,699 		 		| 483,231 				  | 286,951  		 		| 
|NCCSign-3		            | 366,008 		 		| 940,073 				  | 389,236 		 		| 
|NCCSign-5		            | 493,050 		 		| 967,367 				  |  587,347		 		| 
</details>

### PKE/KEM (Environment2, -O3)
<details>
<summary>PKE/KEM-Env2-O3 Table (Unit: clock cycles)</summary>
    
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

### Digital Signature (Environment2, -O3)
<details>
<summary>Digital Signature-Env2-O3 Table (Unit: clock cycles)</summary>
 
    
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


## How to use
### Compile command
Use the following command for KpqC benchmarking compile.

    make
    ./KpqC_bench
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

    
