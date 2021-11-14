Naveen Mishra, CS21M516, naveen.innocence@gmail.com

# Crypto-Assignment3
To compare the timing difference between RSA with and without Chinese Remainder Theorem.

1. Source code is present in the attached main.c
2. A zipped folder  by name "CryptoAssign3.7z" having Codeblocks project, .out, .exe and source code is also attached.

# Prerequisites
1. OpenSSL libraries must be installed in the system - https://drive.google.com/file/d/1PrE7rD1c9utdYSWAZLXiT-VlLMKTP_tB/view?usp=sharing
2. Add the following Linker libraries in codeblocks project . Project -> Build Options -> Debug -> Linker Settings. 
   Note - Update the paths as per the installed directories in your system.
   ..\..\..\Program Files\OpenSSL-Win64\lib\libcrypto.lib
   ..\..\..\Program Files\OpenSSL-Win64\lib\libssl.lib
3. Add the include file path in codeblocks project. Project -> Build Options -> Debug -> Search Directories
   Note - Update the paths as per the installed directories in your system.
   ..\..\..\Program Files\OpenSSL-Win64\include\
   
# Results
It was found that the Regular RSA implementation took execution time of 1313us whereas that with CRT took around 999us. Please see attached images for details.
Please note that this implemenation was done for a tiny plain text and n. CRT would drastically perform well over regular RSA as plaintext size and n increases.
