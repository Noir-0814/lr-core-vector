# lr-core-vector

用 C 语言手写一个 `std::vector`：你要做的事只有一件：根据 `include/vector.h` 的描述**把 `src/vector.c` 里的空壳函数填成能用的实现，让 `make test` 全绿**。

[vector 原理可视化](https://lingrui-studio.github.io/vector-playground/)

本题实现的是只存储 `int` 的教学版动态数组，具体约定以 [include/vector.h](include/vector.h) 为准。

## 目录结构

```
lr-core-vector/
├── readme.md         本文件
├── Makefile          构建脚本（不用改）
├── .gitignore        列举 git 需要忽视的文件
├── .clang-format     格式化要求
├── include/
│   └── vector.h      接口声明 + 函数注释（不用改，但要读懂）
├── src/
│   └── vector.c      ★ 你要实现的地方
└── tests/
    └── test.c        单元测试（不用改）
```

## 自检

补全 [include/vector.c](include/vector.c) 中的函数实现后，项目根目录运行 `make test`，若最后输出结果如下即表示你完成了本项目（本项目只有未完成和已完成两种状态，不存在中间值）：

```bash
== 通过 3393 项，失败 0 项 ==
全部通过，可以 commit & push 了
```

测试始终开启 ASan + UBSan，检测到错误会以失败状态退出，不提供关闭开关。常见错误会被直接指出来，例如：

```
ERROR: AddressSanitizer: heap-buffer-overflow on address 0x... at pc 0x...
READ of size 4 at 0x... thread T0
    #0 0x... in get src/vector.c:52
```

行号会直接指到出问题的那一行，看不懂的把完成代码和报错信息复制给 AI 问一下。

## 提交

- 完成下面的`实现思路`一节，简要说明你的各个函数是如何实现的，尤其注意内存管理的说明
- 把所有修改 commit 并 push 到 GitHub 上自己的 vector 仓库
- 在个人仓库的 Actions 页面手动触发一次自动评分工作流

## 实现思路

**在内存分配之前，应该先判断要分配的字节数是否超出上限**  
**老的capacity和size的计算应该在realloc之前进行**

### vector_init
先判断`capacity`是否为零，是否超出上限，再进行内存分配，判断是否分配成功，  
若分配失败或`capacity`为零或超出上限将指针全部置为`NULL`并返回-1  
若成功则返回0

### vector_destroy
释放分配的内存，指针全部置为`NULL`

### size,capacity和empty
若`vector`的`capcity`为零返回0  
若不为零利用指针相减计算`size()`和`capacity()`的返回值  
`empty()`通过`size()`判断数组中是否无有效数据

### get,set,front,back
- `get`和`set`先判断`index`是否超出`size()`，再进行元素的读取/修改
- `front`和`back`先判断数组中有有效数据，再通过指针读取头/尾元素

### push_back
先记录老的`size()`，再判断此时数组的容量是否已满，  
若未满直接在`end`处添加新元素并将`end`后移一个步长  
若已满，判断2倍的`capacity`是否超限或`capacity`为0，再进行内存分配，容量为0时增至1，否则增至原容量的2倍  
然后判断是否分配成功，最后更改三个指针

### pop_back
删除尾部元素，就是将`end`前移一步，返回0  
数组没有有效数据时返回-1

### reserve
先判断新容量是否超限，新容量小于等于原容量时只返回0，大于时进行内存分配  
然后判断是否分配成功，最后更改三个指针

### shrink_to_fit
如果`size`为零，直接释放内存并将三个指针置为`NULL`  
若不为零，重新分配内存，使`capacity`与`size`相等，  
然后判断是否分配成功，最后更改三个指针

### clear
直接让`end`等于`data`，将原来的数据视为无效数据
