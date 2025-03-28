# Стек

lesson = 300286

## Структура раздела

Дальше в курсе будет изучение структур данных: стека, очереди, деревьев, графов, хеш-таблиц. И их реализация.

Поэтому сначала в этом уроке поговорим о том, что такое структура данных, интерфейс и его реализация.

Потом рассмотрим, где может применяться стек при решении задач.

В конце реализуем стек на основе массива фиксированной длины, а потом - на основе динамического массива различными способами.

[Презентация](https://stepik.org/media/attachments/lesson/300286/c2019_11.pdf)

## VIDEO

<iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/65R5YMxrOzE" width="560"></iframe>

## Интерфейс и реализация

Структура данных - способ хранения и работы с данными.

Интерфейс (interface) - **что делает?** - как можно работать с этими данными.

Программный интерфейс (application programming interface, API) - набор прототипов функций.

Реализация (implementation) - **как устроена** работа с данными.

Реализация программного интерфейса - это реализация функций, описанных в интерфейсе.

<img src="https://stepik.org/media/attachments/lesson/300286/f-interface-implementation.gif"/>

Разберем на примере. Если вам нужно узнать сколько сейчас времени, вы смотрите на часы. Часы предоставляют человеку интерфейс "узнать время", "установить время" и (не всегда) "завести часы".

Один и тот же интерфейс может быть реализован по-разному. Часы бывают механические и электронные, наручные и огромные установленные на зданиях, часы есть в компьютере, раньше для определения времени использовали солнечные часы, водяные часы, песочные часы, огненные часы.

Они делают одно и то же - определяли время. Но как они это делают - зависит от реализации. Выбор конкретных часов зависит от задачи. С какой точностью нужно определять время? Сколько места могут занимать часы? Есть ли электричество или батарейки или придется обходиться без них?

## Интерфейс стек

Стек - структура данных, в которой реализован принцип **LIFO** (last input, first output), последним пришел, первым ушел. 

Пример стека - стопка тарелок или книг, детская пирамидка из колец, вагон метро в час пик. Тарелку можно поставить только на верх стопки и снять тоже - только верхнюю тарелку. Нельзя выдернуть тарелку из середины.

<img src="https://stepik.org/media/attachments/lesson/300286/toy.png"/> 
<img src="https://stepik.org/media/attachments/lesson/300286/stones.jpg"/> 

Основа интерфейса - это метод **push** (добавить элемент на вершину стека) и **pop** (удалить элемент с вершины стека).

<img src="https://stepik.org/media/attachments/lesson/300286/push_pop.png"/> 

## Стек - стакан с красками

Пусть наш стек - это стакан, в который наливают **push** и выливают **pop** слой краски. Эти  слои не смешиваются. 

**top** - посмотреть на вершину стека и сказать, какая сверху краска, но не изменять содержимое стека. (**pop** - изменяет стек).

Введем дополнительные функции:

**is_empty** - проверить, что стек пуст. Из него нельзя достать краску. Ее там нет.

**is_full** - проверить, что стек (стакан) полный. В него больше не получится наливать краску (она прольется через край).

**draw** - нарисовать стакан.

**create** - создать (взять) стакан. Сначала стакан пустой.

Возьмем стакан и начнем наливать туда краски (**push**).

<table>
    <tr>
        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan0.png"/><br/>
        <b>create</span><br/>
        <b>is_empty: true</b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan1.png"/><br/>
        <b>push (<span style="color:#64b0f4">blue</span>)</b><br/>
        <b>top: <span style="color:#64b0f4">blue</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan2.png"/><br/>
        <b>push (<span style="color:#ff4363">red</span>)</b><br/>
        <b>top: <span style="color:#ff4363">red</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan3.png"/><br/>
        <b>push (<span style="color:#66cc66">green</span>)</b><br/>
        <b>top: <span style="color:#66cc66">green</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan4.png"/><br/>
        <b>push (<span style="color:#ff9900">yellow</span>)</b><br/>
        <b>top: <span style="color:#ff9900">yellow</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan5.png"/><br/>
        <b>push (<span style="color:#ff00cc">magenta</span>)</b><br/>
        <b>top: <span style="color:#ff00cc">magenta</span></b>
        </td>
    </tr>
</table>

Стакан полный. В него больше ничего нельзя налить до тех пор, пока не выльем хотя бы 1 слой. Иначе будет **переполнение стека** (stack overflow).

Начнем выливать из стакана функцией **pop**.

<table>
    <tr>
        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan5.png"/><br/>
        <b>is_full: true</b><br/>
        <b>top: <span style="color:#ff00cc">magenta</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan4.png"/><br/>
        <b>pop: <span style="color:#ff00cc">magenta</span></b><br/>
        <b>top: <span style="color:#ff9900">yellow</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan3.png"/><br/>
        <b>pop: <span style="color:#ff9900">yellow</span></b><br/>
        <b>top: <span style="color:#66cc66">green</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan2.png"/><br/>
        <b>pop: <span style="color:#66cc66">green</span></b><br/>
        <b>top: <span style="color:#ff4363">red</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan1.png"/><br/>
        <b>pop: <span style="color:#ff4363">red</span></b><br/>
        <b>top: <span style="color:#64b0f4">blue</span></b>
        </td>

        <td>
        <img src="https://stepik.org/media/attachments/lesson/300286/stackan0.png"/><br/>
        <b>pop: <span style="color:#64b0f4">blue</span></b><br/>
        <b>is_empty: true</b>
        </td>
    </tr>
</table>

Когда стек пустой из него нельзя сделать **pop** - нечего доставать, стек может испортиться.