*/
Реализуйте скрипт для командного интерпретатора bash, который выполняет поиск имен #include-файлов для заданных имен Си-функций, используя в качестве источника данных третий раздел man-страниц Linux.

В переменной окружения MANPATH перечислены директории, разделённые символом : (аналогично переменной PATH). В этих директориях располагается каталог man3, устроенный аналогично /usr/share/man/man3. Ответ должен быть составлен с использованием этих директорий, использование man и manpath запрещено.

Файлы могут быть как сжатыми утилитой gz, так и распакованными.

Список функций задается на стандартном потоке ввода:

fopen
malloc
unknown_function
strcmp
Если описание функции не найдено, то записывается прочерк из трех дефисов: ---.

Результат необходимо записать в стандартный поток вывода:

stdio.h
stdlib.h
---
string.h
В скрипте допускается использовать только команды ввода-вывода и утилиты sed и gunzip.

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.*/
  
  
  

#!/bin/bash


path=$(echo $MANPATH | sed -E 's/:/ /')

while read -r input
do
	for mpath in $path
	do

		fpath=$(find $mpath -name "$input\.3*" | head -1)

		if [ -n "$fpath" ]
		then
			if [ $(echo $fpath | sed -r 's/.*\.gz/gz/' ) == "gz" ]
	                then
        	                string=$(gunzip -c $fpath | sed -r '/.*include <.*>.*/!d' | head -1)
                	else
                        	string=$(cat $fpath | sed -r '/.*include <.*>.*/!d' | head -1)
			fi

	                answer=$(echo $string | sed -r 's/.*include <(.*)>.*/\1/')

	                echo $answer
			break
		fi
	done

	if [ -z "$fpath" ]
	then
        	echo "---"
	fi
done
