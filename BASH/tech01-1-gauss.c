/* RU
Реализуйте программу для командного интерпретатора bash, которая вычисляет вещественные корни системы линейных алгебраических уравнений методом Гаусса.

Единственным аргументом скрипта является csv-файл c матрицей (N,N+1) вида:

2,1,-1,8
-3,-1,2,-11
-2,1,2,-3
Скрипт должен вычислить значения и вывести их в тектовом виде на экран в виде строк со значениями:

2.00000000000000000000
3.00000000000000000000
-1.00000000000000000000
В скрипте допускается использовать только команды ввода-вывода и утилиту bc (для вещественнозначных вычислений).

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.

*/

/* ENG
Implement a program for the bash command interpreter that calculates the real roots of a system of linear algebraic equations by the Gauss method.

The only argument of the script is a csv file with a matrix (N,N+1) of the form:

2,1,-1,8
-3,-1,2,-11
-2,1,2,-3
The script should calculate the values and display them in text form on the screen in the form of strings with values:

2.00000000000000000000
3.00000000000000000000
-1.00000000000000000000
Only I/O commands and the bc utility (for real-valued calculations) can be used in the script.

It is forbidden to use the call of interpreters of high-level languages (Perl, Python, etc.).

*/

#!/usr/bin/env bash

filename=`cat $1`
counter=0
val=0

for l in $filename
do
    IFS=,
    for num in $l
    do 
        matr[$val]=$num
        val=$(($val+1))
    done
    counter=$(($counter+1))
done
cols=$(($counter+1))

for ((i = 0; i < $counter; ++i))
do
    first=$i
    sec=$i

    for ((j = $i; j < $counter; ++j))
    do  
        indd=$(($j * $cols + $i))
        cur=${matr[$indd]}
        if [ "$cur" = "0" ]
        then 
            continue
        fi

        sec=$j
        break
    done

    for ((j = 0; j < $cols; ++j))
    do 
        index_1=$(($first * $cols + $j))
        elem_1=${matr[$index_1]}
        
        index_2=$(($sec * $cols + $j))
        elem_2=${matr[$index_2]}
        
        index_3=$(($first * $cols + $j))
        matr[$index_3]=$elem_2

        index_4=$(($sec * $cols + $j))
        matr[$index_4]=$elem_1
    done

    sw_1[$i]=$first
    sw_2[$i]=$sec

    indd=$(($i * $cols + $i))
    dived=${matr[$indd]}

    for ((j=0; j<$cols; ++j))
    do
        index_1=$(($i * $cols + $j))
        elem=${matr[$index_1]}

        elem=`echo "(($elem)"/"($dived))" | bc -l`

        index_2=$(($i * $cols + $j))
        matr[$index_2]=$elem
    done

    for ((j = 0; j < $counter; ++j))
    do
        if [ $j -eq $i ]
        then
            continue
        fi

        indd=$(($j * $cols + $i))        
        mull=${matr[$indd]}

        if [ "$mull" = "0" ]
        then   
            continue
        fi


        for ((k=0;k<$cols; ++k))
        do
            index_1=$(($i * $cols + $k))
            elem=${matr[$index_1]}

            elem=`echo "(($elem)"*"($mull))" | bc -l`

            index_2=$(($i * $cols + $k))
            matr[$index_2]=$elem
        done


        for ((k=0; k<$cols; ++k))
        do
            index_1=$(($i * $cols + $k))
            elem_1=${matr[$index_1]}

            index_2=$(($j * $cols + $k))
            elem_2=${matr[$index_2]}

            elem_2=`echo "(($elem_2)"-"($elem_1))" | bc -l`

            index_2=$(($j * $cols + $k))
            matr[$index_2]=$elem_2
        done

        for ((k=0; k<$cols; ++k))
        do
            index_1=$(($i * $cols + $k))
            elem=${matr[$index_1]}

            elem=`echo "(($elem)"/"($mull))" | bc -l`

            index_2=$(($i * $cols + $k))
            matr[$index_2]=$elem
        done        
    done
done

for ((i=$counter-1;i>0;--i))
do
    for ((j = 0; j < $cols; ++j))
    do 
        index_1=$(($sw_1[$i] * $cols + $j))
        elem_1=${matr[$index_1]}
        
        index_2=$(($sw_2[$i] * $cols + $j))
        elem_2=${matr[$index_2]}
        
        index_3=$(($sw_1[$i] * $cols + $j))
        matr[$index_3]=$elem_2

        index_4=$(($sw_2[$i] * $cols + $j))
        matr[$index_4]=$elem_1
    done
done

for ((i = 0; i < $counter; ++i))
do
    echo ${matr[$(($counter + $i*$cols))]}
done


