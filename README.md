# d2hackmap
## Target
	对整合的d2hackmap源码用vc9编译器Win32平台(vs2008)进行编译，运行不崩溃以后，拓展一个自动刷怪的功能。
__源代码__
- https://gitee.com/andersgong/d2hackmap
- https://github.com/jieaido/d2hackmap

__编译方式__
- vc9（vs2008）
- Win32
## History
- 2021-08-05
	通过vc16(vs2019)编译器Win32平台进行编译，因为涉及到nack关键字不能用x64。编译通过以后，替换原始d2hackmap.dll打开游戏就崩溃，初步判断是暗黑2这款游戏很老，需要保持编译器的一致性。(通过*.vcproj分析到现有用的是vc9)

   
