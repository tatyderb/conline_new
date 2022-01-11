# Деревья - дополнительные задачи

lesson = 
lang = c_valgrind

## TASKINLINE Частотный словарь

Дан текст. Посчитайте сколько раз в нем встретилось каждое слово без учета регистра.

Напечатайте результат, отсортировав слова по убыванию количества вхождения в текст. При одинаковом количестве отсортируйте в лексикографическом порядке.

При выводе печатайте слово маленькими буквами (только буквы! "Из-за" напечатать как "изза") и через пробел количество его вхождений в текст.

Подсказка 1. Тут данные в узле - это структура из слова и количества его вхождений в обработанный текст.

Подсказка 2. Для сортировки можно создать массив из **указателей** на узлы дерева и сортировать этот массив.

Подсказка 3. В тестах использовался текст из [python zen](https://www.python.org/dev/peps/pep-0020/) и стихотворение [jabberwocky](https://www.poetryfoundation.org/poems/42916/jabberwocky) Льюиса Кэрола.

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
====      

## TASKINLINE Лес

Дан текст. Используя структуру данных "лес" сколько разных слов содержит текст (без учета регистра). 

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
====      

