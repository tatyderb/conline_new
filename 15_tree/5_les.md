# Частотный словарь. Лес

lesson = 311540
lang = c_valgrind


## SKIP VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/FKCToOPxhEg" width="560"></iframe></p>


## Частотный словарь

В узлах дерева могут быть не только числа. Рассмотрим задачу о частотном словаре.

Дан текст. Напечатать слова и указать сколько раз слово встретилось в тексте.

Тип Data должен стать составным - слово и счетчик (сколько раз оно встретилось).

```cpp
typedef struct {
    char * word;    // слово
    unsigned int n; // сколько раз оно встретилось
};
```

Бинарное дерево поиска подойдет для этой задачи. Если слово уже в дереве, нужно увеличить счетчик на 1.

## TASKINLINE Частотный словарь (дополнительная задача)

Дан текст. Посчитайте сколько раз в нем встретилось каждое слово без учета регистра.

Напечатайте результат, отсортировав слова по убыванию количества вхождения в текст. При одинаковом количестве отсортируйте в лексикографическом порядке.

При выводе печатайте слово маленькими буквами (только буквы! "Из-за" напечатать как "изза") и через пробел количество его вхождений в текст.

Подсказка 1. Тут данные в узле - это структура из слова и количества его вхождений в обработанный текст.

Подсказка 2. Для сортировки можно создать массив из **указателей** на значения в узлах дерева (или сами **значения**, указатель и число вместо одного указателя) и сортировать этот массив.

Подсказка 3. В тестах использовался текст из [python zen](https://www.python.org/dev/peps/pep-0020/) и стихотворение [Jabberwocky](https://www.poetryfoundation.org/poems/42916/jabberwocky) Льюиса Кэрола [перевод на русский](https://ru.wikipedia.org/wiki/%D0%91%D0%B0%D1%80%D0%BC%D0%B0%D0%B3%D0%BB%D0%BE%D1%82), русского в тестах нет, перевод приведен для общей эрудиции.

TEST
Bomb? Bomb! BOMB!!!
i have a bomb. you have a bomb.
----
bomb 5
a 2
have 2
i 1
you 1
====
Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one– and preferably only one –obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than right now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea – let's do more of those!
----
is 10
better 8
than 8
the 5
to 5
although 3
be 3
idea 3
never 3
one 3
a 2
complex 2
do 2
explain 2
if 2
implementation 2
it 2
may 2
now 2
obvious 2
of 2
should 2
special 2
unless 2
way 2
ambiguity 1
and 1
are 1
arent 1
at 1
bad 1
beats 1
beautiful 1
break 1
cases 1
complicated 1
counts 1
dense 1
dutch 1
easy 1
enough 1
errors 1
explicit 1
explicitly 1
face 1
first 1
flat 1
good 1
great 1
guess 1
hard 1
honking 1
implicit 1
in 1
its 1
lets 1
more 1
namespaces 1
nested 1
not 1
often 1
only 1
pass 1
practicality 1
preferably 1
purity 1
readability 1
refuse 1
right 1
rules 1
silenced 1
silently 1
simple 1
sparse 1
temptation 1
that 1
there 1
those 1
ugly 1
youre 1
====
’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.

“Beware the Jabberwock, my son!
      The jaws that bite, the claws that catch!
Beware the Jubjub bird, and shun
      The frumious Bandersnatch!”

He took his vorpal sword in hand;
      Long time the manxome foe he sought—
So rested he by the Tumtum tree
      And stood awhile in thought.

And, as in uffish thought he stood,
      The Jabberwock, with eyes of flame,
Came whiffling through the tulgey wood,
      And burbled as it came!

One, two! One, two! And through and through
      The vorpal blade went snicker-snack!
He left it dead, and with its head
      He went galumphing back.

“And hast thou slain the Jabberwock?
      Come to my arms, my beamish boy!
O frabjous day! Callooh! Callay!”
      He chortled in his joy.

’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.
----
the 19
and 14
he 7
in 6
jabberwock 3
my 3
through 3
all 2
as 2
beware 2
borogoves 2
brillig 2
came 2
did 2
gimble 2
gyre 2
his 2
it 2
mimsy 2
mome 2
one 2
outgrabe 2
raths 2
slithy 2
stood 2
that 2
thought 2
toves 2
twas 2
two 2
vorpal 2
wabe 2
went 2
were 2
with 2
arms 1
awhile 1
back 1
bandersnatch 1
beamish 1
bird 1
bite 1
blade 1
boy 1
burbled 1
by 1
callay 1
callooh 1
catch 1
chortled 1
claws 1
come 1
day 1
dead 1
eyes 1
flame 1
foe 1
frabjous 1
frumious 1
galumphing 1
hand 1
hast 1
head 1
its 1
jaws 1
joy 1
jubjub 1
left 1
long 1
manxome 1
o 1
of 1
rested 1
shun 1
slain 1
snickersnack 1
so 1
son 1
sought 1
sword 1
thou 1
time 1
to 1
took 1
tree 1
tulgey 1
tumtum 1
uffish 1
whiffling 1
wood 1
====

## Лес

Попробуем хранить память экономнее. В языке много похожих слов: to, tea, ted, ten, in, inn. Будем хранить в каждом узле не все слово и счетчик, а только 1 букву, спускаясь от корня к листьям мы набираем слово по одной букве. Там, где слово заканчивается, счетчик делает +1. То есть проходя по ветке inn мы видим, что там уже есть слово in и оно имеет свой счетчик.

![Лес](https://stepik.org/media/attachments/lesson/311540/word_freq.png)

При реализации будем хранить массив букв со счетчиками. На малых текстах мы, верояно, проиграем в памяти, но на больших текстах выиграем.

Такая структура данных называется **лес**.

```cpp
struct Letter {
    char c;             // очередная буква слова
    unsigned int count; // счетчик
};
struct Node {
    struct Letter let[26];  // 33 буквы для русского языка
};    
```

## TASKINLINE Лес (дополнительная задача)

Дан текст. Используя структуру данных "лес" найдите сколько разных слов содержит текст (без учета регистра). 

Считаем, что слово прочитано по формату `%s` и из него удалены все символы, кроме латинских букв (от a до z).

TEST
Bomb? Bomb! BOMB!!!
i have a bomb. you have a bomb.
----
5
====
Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one– and preferably only one –obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than right now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea – let's do more of those!
----
80
====
’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.

“Beware the Jabberwock, my son!
      The jaws that bite, the claws that catch!
Beware the Jubjub bird, and shun
      The frumious Bandersnatch!”

He took his vorpal sword in hand;
      Long time the manxome foe he sought—
So rested he by the Tumtum tree
      And stood awhile in thought.

And, as in uffish thought he stood,
      The Jabberwock, with eyes of flame,
Came whiffling through the tulgey wood,
      And burbled as it came!

One, two! One, two! And through and through
      The vorpal blade went snicker-snack!
He left it dead, and with its head
      He went galumphing back.

“And hast thou slain the Jabberwock?
      Come to my arms, my beamish boy!
O frabjous day! Callooh! Callay!”
      He chortled in his joy.

’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.
----
90
====      
