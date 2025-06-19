# Справочные материалы

lesson = 778368

## Таблица приоритетов операций

Операции по убыванию приоритета

| Приоритет | Оператор | Описание | Описание (Eng) | 
|---|----|-----|-----|
| 1 | `++` `--`	| Постфиксный и суффиксный инкремент и декремент | Suffix/postfix increment and decrement |
| 1 | `()` | Вызов функции | Function call | 
| 1 | `[]` | Доступ к элементу массива | Array subscripting |
| 1 | `.` | Доступ к полю структуры или юниона | Structure and union member access |
| 1 | `->` | Доступ к полю структуры или юниона через указатель | Structure and union member access through pointer |
| 1 | `(type){list}` | Составные литералы (С99) | Compound literal |
| | | |
| 2 | `++` `--`	| Префиксный инкремент и декремент | Prefix increment and decrement| 
| 2 | `+` `-` |	**Унарный** плюс и минус | Unary plus and minus |
| 2 | `!` `~` | Логическое и побитовое отрицания | Logical NOT and bitwise NOT |
| 2 | `(type)` | Приведение типа | Cast |
| 2 | `*` | Разыменование | Indirection (dereference) |
| 2 | `&` | Взятие адреса |	Address-of |
| 2 | `sizeof` | Размер | Size-of |
| 2 | `_Alignof` | Требование выравнивания | Alignment requirement(C11) |
| 3 | `*` `/` `%` | Умножение, деление, остаток от деления |	Multiplication, division, and remainder |
| 4 | `+` `-` | Сложение и вычитание |	Addition and subtraction |
| 5 | `<<` `>>` | Побитовые сдвиги | Bitwise left shift and right shift |
| 6 | `<` `<=` | Меньше, меньше или равно |	For relational operators < and ≤ respectively |
| 6 | `>` `>=` | Больше, больше или равно |	For relational operators > and ≥ respectively |
| 7 | `==` `!=` | Равно, не равно |	For relational = and ≠ respectively |
| 8 | `&` | Побитовое И |	Bitwise AND |
| 9 | `^` | Побитовое исключающее ИЛИ |	Bitwise XOR (exclusive or) |
| 10 |	`|` | Побитовое ИЛИ |	Bitwise OR (inclusive or) |
| 11 | `&&` | Логическое И |	Logical AND |
| 12 | `||` | Логическое ИЛИ |	Logical OR |
| 13 |	`?:` | Тернарный оператор |	Ternary conditional |
| 14 | `=` | Присвоение |	Simple assignment |
| 14 | `+=` `-=` | Присвоение со сложением и вычитанием |	Assignment by sum and difference |
| 14 | `*=` `/=` `%=` | Присвоение с умножением, делением, остатком от деления |	Assignment by product, quotient, and remainder |
| 14 | `<<=` `>>=` | Присвоение с побитовым сдвигом |	Assignment by bitwise left shift and right shift |
| 14 | `&=` `^=` `|=` | Присвоение с побитовыми И, ИЛИ, исключающим ИЛИ |	Assignment by bitwise AND, XOR, and OR |
| 15 | `,` | Запятая |	Comma	|

Источник: [https://en.cppreference.com/w/c/language/operator_precedence](https://en.cppreference.com/w/c/language/operator_precedence)
