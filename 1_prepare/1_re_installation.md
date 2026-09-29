# Установка средств разработки

lesson = 2612714
lang = c

## Надо ли устанавливать программы для курса?

💡 Совет: если не хотите ничего устанавливать сейчас - используйте встроенный редактор Stepik.

✅ Можно сразу идти [дальше](https://stepik.org/lesson/571830/step/1) изучать язык, писать маленькие программы. Степик позаботился о вас.

❌ Неудобно отлаживаться и писать большие программы.

Можно сейчас пойти вперед и вернуться к установке, когда перестанет хватать встроенного онлайн-редактора. На задачах про массивы и далее.

**Студенты МФТИ устанавливают компилятор, отладчик, систему контроля памяти и редактор или IDE в первую неделю учебы.**

### Что устанавливаем

* Редактор с подсветкой синтаксиса.
* Компилятор.
* Утилиту для контроля памяти (нужно от массивов и далее).

Выбор программ зависит от операционной системы (ОС).


### Утилиты для контроля памяти

Ищут ошибки работы с памятью в C: утечки, выход за границы массива, использование освобождённой памяти.

* **Valgrind** - больше возможностей (динамическая проверка, во время исполнения программы). Не работает на MAC.
* **Address Sanitizer** - статическая проверка, встроен в компилятор.

### Компилятор

* `gcc` (от GNU Compiler Collection)
* `clang` - в него встроен Address Sanitizer

### Отладчик (опционально)

* `gdb`

Или научимся пользоваться отладочной печатью. 

### Редактор с подсветкой синтаксиса

Любой, на ваш вкус, который поддерживает ваша операционная система (ОС).

* [Notepad++](https://notepad-plus-plus.org/) (только Windows)
* [VSCode](https://code.visualstudio.com/) - различные ОС
* [vim](https://www.vim.org/download.php) - различные ОС. Можно поставить графическую версию или запускать в командной строке. Нужно [научиться с ним работать](https://stepik.org/lesson/250622/step/1).

### Что-то пошло не так

... или у вас конфигурация, которая не описана дальше в инструкциях.

Самое время использовать ИИ. Если возникла проблема, пишите что до этого делали, что получили. Подгрузите выведенный текст или снимок экрана. 


## Linux: gcc + valgrind

Запустите терминал. Дальше будем работать в командной строке.

* Если не знаете, какой дистрибутив у вас стоит, запустите
```
cat /etc/os-release
```

### Установка `gcc` и `valgrind`

Проверьте, стоят ли у вас нужные программы. В терминале наберите команды:
```
gcc --version
valgrind --version
```
Если вывод содержит версию, то программа установлена. Иначе устанавливаем и далее проверяем, что установилось корректно.

Для установки программ и системных изменений нужно запускать эти команды с `sudo`.
 
#### Debian / Ubuntu (пакетный менеджер apt)

```
sudo apt update
sudo apt install build-essential gdb valgrind
```

#### Fedora / RHEL / CentOS (dnf/yum)

```cpp
# Fedora
sudo dnf install gcc valgrind

# CentOS 7 (старый, с yum)
sudo yum install gcc valgrind
```

**Важное замечание для CentOS/RHEL 7:** Стандартные репозитории содержат очень старую версию GCC (4.8.5). Если нужен более новый компилятор, используйте `devtoolset`:

```cpp
sudo yum install centos-release-scl
sudo yum install devtoolset-11-toolchain
scl enable devtoolset-11 bash
```

#### openSUSE (zypper)

```cpp
sudo zypper install gcc valgrind
```

#### Arch Linux / Manjaro (pacman)

```cpp
sudo pacman -S gcc valgrind
```

*Пишите уточнения и замечания по инструкциям в комментариях.*

## Linux: устанавливаем IDE

IDE - это продвинутый редактор с возможностью использовать уже установленные компилятор и отладчик. Инструкции для **VS Code**.

#### Универсальный способ через Snap

```
sudo snap install code --classic
```

#### Для Ubuntu / Debian (официальный репозиторий)

Этот метод предпочтителен, если вы хотите получать обновления вместе с системой и избежать возможных проблем с песочницей Snap.

1. Установите зависимости и ключ Microsoft:

```
sudo apt update
sudo apt install -y wget gpg
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
rm packages.microsoft.gpg
```

2. Добавьте репозиторий и установите:

```
echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" | sudo tee /etc/apt/sources.list.d/vscode.list
sudo apt update
sudo apt install code
```

#### Для Fedora / RHEL / openSUSE

Скачайте `.rpm` пакет с официального сайта и установите через терминал:

```
sudo rpm -i code-*.rpm
```
Или используйте менеджер пакетов вашего дистрибутива (`dnf`, `zypper`)

### Альтернативные IDE

Не обязательно ставить VS Code, существует множество других прекрасных IDE.

| Инструмент	| Кому подойдёт	| Установка (Ubuntu/Debian) |
|----|----|----|
| `Geany` |	Новичкам, слабым ПК	| `sudo apt install geany` |
| `CodeLite` |	Лёгкий IDE для C/C++ с GDB	| `sudo apt install codelite` |
| `VSCodium` |	Тем, кто хочет VS Code без телеметрии	| `sudo apt install codium` (через репозиторий) |
| `Code::Blocks` |	Классика для C/C++	| `sudo apt install codeblocks` |

Совсем альтернативная IDE: [vim](https://www.vim.org/download.php) - различные ОС. Можно поставить графическую версию или запускать в командной строке. Нужно [научиться с ним работать](https://stepik.org/lesson/250622/step/1).

*Пишите уточнения и замечания по инструкциям в комментариях.*


## MacOS

В MacOS невозможна работа `valgrind`. Поэтому устанавливаем `AddressSanitizer`.


| Инструмент	| Назначение |
|----|----|
| `clang` |	Компилятор (входит в Xcode CLT) |
| `AddressSanitizer` |	Аналог valgrind, встроен в clang |
| `VS Code` |	Редактор кода, IDE |

Все команды выполняем в терминале.

* Устанавливаем `clang` в составе Xcode CLT
```
xcode-select --install
```
Проверьте, что `clang` установлен:

```
clang --version
```

* Устанавливаем VS Code через Homebrew:

```bash
brew install --cask visual-studio-code
```

*Если у вас MacOS, ищите/напишите более подробную инструкцию в комментариях к шагу.*

## Windows - настраиваем WSL

Без командной строки тяжело запускать программу с большими тестами и нельзя будет запустить `valgrind`. Задача будет работать на вашем компьютере (без проверок `valgrind`) и не будет проходить проверку в курсе (`valgrind` показал ошибку). Тяжело найти ошибку в своем решении.

Поставим на Windows командную строку Linux. Что ставить, зависит от версии Windows.

**Запишите и запомните свой логин и пароль при установке. Он понадобится на следующем шаге.**

* На Windows 11 (если что, берите гайды по windows-10)
    * [https://vc.ru/dev/744877-kak-ustanovit-wsl-na-windows-11](https://vc.ru/dev/744877-kak-ustanovit-wsl-na-windows-11) на русском, в картинках с рамочками и стрелочками.
* На Windows 10 рекомендуем установить **WSL** (Windows Subsystem for Linux) или **WSL2**. На нем можно делать задачи всех курсов МФТИ по С, в том числе курс по IPC. 
    * [Установка WSL на Windows 10](https://docs.microsoft.com/ru-ru/windows/wsl/install-win10)
    * [Установка WSL на Windows 10 еще одна инструкция](https://g-ek.com/kak-zapustit-bash-v-windows-10)
    * [Video]() - Нужно найти нормальное видео, желательно на русском.
* На Windows 7 или 8 установите **cygwin**. На курсе, изучающим IPC UNIX, `cygwin` будет не достаточно.
    * [cygwin](https://cygwin.com/install.html)
    * [Video](https://www.youtube.com/watch?v=2csABC85onI) - установка
    
В WSL могут быть проблемы с настройкой интернета. [Как настроить ssh в bash](https://superuser.com/questions/1111591/how-can-i-ssh-into-bash-on-ubuntu-on-windows-10)

## Где искать файлы Windows в командной строке Linux

* `\` - в Windows, `/` - в Linux,
* Из командной строки в **WSL** файл Windows `C:\work\hello.c` находится в `/mnt/c/work/hello.c`
    * диск Windows нужно искать в `/mnt/имя_диска`
* Из командной строки **cygwin** файл Windows `C:\work\hello.c` находится в `/cygdrive/c/work/hello.c`   
    * диск Windows нужно искать в `/cygdrive/имя_диска`


## Windows - VS Code

Выбирайте, какие IDE и компиляторы вы будете ставить. 

* [WSL + gcc + valgrind + VS Code]()
* [clang + address sanitizer + VS Code]() - в разработке

## Проверка: компиляция и запуск программы

* Создайте файл `hello.c` и скопируйте в него следующий текст. Не забудьте сохранить этот файл после изменения.

```cpp
#include <stdio.h>

int main()
{
    printf("Hello, world!\n");
    
    return 0;
}
```

### Скомпилируйте файл

* `gcc`:

```
gcc hello.c -o hello.exe
```
* `clang`:
```
clang hello.c -o hello.exe
```

В текущей директории должен появиться файл `hello.exe`.

### Запустите файл

* Linux (в том числе WSL в Windows или mingw), MacOS:

```cpp
./hello.exe
```
* Windows (PowerShell или cmd):
```cpp
hello.exe
```

Должно напечататься `Hello, world!`.



## Работаю на чужом компьютере, нельзя ничего установить

Пока можете, работаете во встроенном редакторе Stepik.

Когда заходите отдельно запускать `valgrind`, рекомендуем [replit.com](https://replit.com/~)

Выберите новый repl с языком `С`. В консоли вы найдете командную строку, `gcc` и `valgrind`. 

Там можно включить режим multiplayer и редактировать файл вместе с другом или преподавателем.

## Итого

✅ Выбрали и установили окружение под свою ОС.

✅ Проверили работу компилятора.

✅ Запустили первую программу (опционально).

Если вы не умеете работать в командной строке UNIX и не знакомы с принципами организации файловой системы, то для вас написан следующий модуль.


