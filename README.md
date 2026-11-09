# Libft

## English

A collection of C functions for common tasks such as counting characters, splitting strings, and copying memory. It reimplements basic C library functions and adds string helpers and linked-list operations.

Building creates `libft.a`, a library file that can be linked into another C program. For example, `ft_strlen("Hello")` returns `5`, and `ft_split` returns an array of strings separated by a delimiter.

### Functions

| Category | Examples |
| --- | --- |
| Characters, strings, and memory | `ft_isalpha`, `ft_strlen`, `ft_memcpy`, `ft_atoi` |
| Additional helpers | `ft_split`, `ft_itoa`, `ft_substr`, `ft_putendl_fd` |
| Linked lists | `ft_lstnew`, `ft_lstadd_back`, `ft_lstclear`, `ft_lstmap` |

Declarations and the `t_list` type are in [libft.h](libft.h). A linked list connects each data element to the next through a reference. These functions are included in the default build.

### Build and try

Requires a C compiler and Make. The supplied [main.c](main.c) demonstrates calling the library.

```sh
make
make run
```

`make` builds `libft.a`; `make example` builds the demonstration executable. `make run` prints `Hello, 42!`.

### Tests

```sh
make test
```

Checks character classification, empty strings, zero-length and overlapping memory operations, allocation overflow, integer limits, string splitting, and linked lists.

## 日本語

文字数を数える、文字列を分割する、メモリをコピーするなど、Cプログラムで繰り返し使う処理をまとめた関数集です。C標準ライブラリの基本関数を自作し、文字列処理や連結リストの操作を加えています。

ビルドすると、他のCプログラムに組み込めるライブラリファイル `libft.a` ができます。例えば `ft_strlen("Hello")` は文字数の `5` を返し、`ft_split` は区切り文字で分けた文字列の配列を返します。

### 関数の構成

| 分類 | 主な関数 |
| --- | --- |
| 文字・文字列・メモリ操作 | `ft_isalpha`、`ft_strlen`、`ft_memcpy`、`ft_atoi` |
| 追加関数 | `ft_split`、`ft_itoa`、`ft_substr`、`ft_putendl_fd` |
| 連結リスト | `ft_lstnew`、`ft_lstadd_back`、`ft_lstclear`、`ft_lstmap` |

関数の宣言とリスト型 `t_list` は [libft.h](libft.h) にあります。連結リストは、データと次の要素への参照をつないで扱う構造です。この関数群も通常の `make` でビルドされます。

### ビルドと使用例

Cコンパイラ・Make が必要です。付属の [main.c](main.c) でライブラリの使用例を実行できます。

```sh
make
make run
```

`make` は関数をまとめた `libft.a`、`make example` はそれを呼び出す実行例をビルドします。`make run` では `Hello, 42!` を表示します。

### テスト

```sh
make test
```

文字種、空文字列、ゼロ長・重複領域のメモリ操作、確保サイズのオーバーフロー、整数境界値、文字列分割、連結リストを確認します。
