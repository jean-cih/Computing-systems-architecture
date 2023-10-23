# Computing-systems-architecture

## Курс «Архитектура вычислительных системы»

### Лабораторная работа No 1

##### Тема: оценка характеристик персонального компьютера (ПК).

##### Задание. Написать bash-скрипт, который выводит на экран характеристики ПК в следующем формате:

## Содержание:

1. [Дата](#дата)
2. [Имя учетной записи](#имя-учетной-записи)
3. [Доменное имя ПК](#доменное-имя-пк)
4. [Процессор](#процессор) \
   4.1. [Модель -](#модель) \
   4.2. [Архитектура -](#архитектура) \
   4.3. [Тактовая частота -](#тактовая-частота) \
   4.4. [Количество ядер -](#количество-ядер) \
   4.5. [Количество потоков на одно ядро -](#количество-потоков-на-одно-ядро)
5. [Оперативная память](#оперативная-память) \
   5.1. [Всего -](#всего) \
   5.2. [Доступно -](#доступно)
6. [Жесткий диск](#жесткий-диск) \
   6.1. [Всего -](#всегo) \
   6.2. [Доступно -](#дoступнo) \
   6.3. [Смонтировано в корневую директорию / -](#смонтировано-в-корневую-директорию-/) \
   6.4. [SWAP всего -](#swap-всего) \
   6.5. [SWAP доступно -](#swap-доступно)
7. [Сетевые интерфейсы](#сетевые-интерфейсы) \
   7.1. [Количество сетевых интерфейсов -](#количество-сетевых-интерфейсов)\
   7.2. [Таблица](#таблица)
8. [Код](#код)

|  №   | Имя сетевого интерфейса | MAC адрес | IP адрес | Скорость соединения |
| :--: | ----------------------- | --------- | -------- | ------------------- |
|      |                         |           |          |                     |
|      |                         |           |          |                     |
|      |                         |           |          |                     |



## 

## Дата

Для того, чтобы вывести текущую дату,  нужно воспользоваться командой 

'$(date)'

## Имя учетной записи

'$USER'

Это системная переменная, которая содержит имя текущего пользователя.

## Доменное имя ПК

Если мы запустим команду `$ hostname` без каких-либо параметров, отобразится текущее имя хоста и доменное имя нашей системы Linux, нашего ПК.

Команда `$ hostname` используется для просмотра имени компьютера и имени домена (DNS) (службы имен доменов).

Нам нужно запустить команду:

'$(hostname -f)'


hostname — это имя, которое присваивается  компьютеру, подключенному к сети, которое однозначно идентифицирует в  сети и, таким образом, позволяет получить доступ к нему без  использования его IP-адреса.

## Процессор

### Модель

Чтобы узнать модель процессора, достаточно выполнить следующую команду: 

'$(lscpu | grep "Model name")'

lscpu  собирает информацию об архитектуре процессора из sysfs и /proc/cpuinfo. 

Утилита grep выполняет поиск образца в текстовых файлах и выдает все строки, содержащие этот образец. 

Опция -E  рассматривает шаблон как расширенное регулярное выражение.

Редактор потоков sed – это неинтерактивный текстовый редактор,  выполняющий операции на данных, поступающих из стандартного ввода или из файла. Sed редактирует информацию построчно.



### Архитектура

Чтобы узнать архитектуру процессора, нужно ввести данную команду: `

'$(lscpu | grep Architecture)'


### Тактовая частота

Чтобы узнать тактовую частоту, выполняем данную команду:

'$(cat /proc/cpuinfo | grep "cpu MHz" | sed s/[^0-9]//g | sed '2, $d')'

### Количество ядер

Чтобы узнать количество ядер, выполняем данную команду: 

'$(cat /proc/cpuinfo | grep "cpu cores" | wc -l)'

### Количество потоков на одно ядро

Количество поток на одно ядро находится благодаря следующей команды: 

'$(lscpu | grep Thread | wc -l)'

## Оперативная память

### Всего

Чтобы определить сколько всего оперативной памяти рабочая машина имеет, следует воспользоваться представленной командой: 

'$(cat /proc/meminfo | grep "MemTotal:" | sed s/[^0-9]//g)'

### Доступно

'$(cat /proc/meminfo | grep "MemAvailable:" | sed s/[^0-9]//g)'

## Жесткий диск

### Всегo

Чтобы узнать сколько всего у нас места на диске, нужно воспользоваться командой с правами суперпользователя:

'$(df -h / | sed '2!D' | awk '{printf $2}')'

### Дoступнo	

Для того, чтобы узнать сколько доступно места на жестком диске, стоит воспользоваться командой: 
`
'$(df -h / | sed '2!D' | awk '{print $4})'

С помощью  `sed` выводим только вторую строку из вывода команды `$ df -h /`, а с помощью `awk` выводим только размер, т.е. 4 столбец.

### Смонтировано в корневую директорию /

Для просмотра сколько смонтировано в корневую директорию /, потребуется ввести данную команду: `

'$(df -h / | sed '2!D' | awk '{print $2}')'

### SWAP всего

SWAP — это механизм виртуальной памяти, при  котором часть данных из оперативной памяти (ОЗУ) перемещается на  хранение на HDD (жёсткий диск), SSD (твёрдотельный накопитель). 

'$(free -h | grep -E '^Swap' | awk '{print $2}')'

### SWAP доступно

'$(free -h | grep -E '^Swap' | awk '{print $4}')'


## Сетевые интерфейсы

### Количество сетевых интерфейсов

'$(ls /sys/class/net | cat -n | tail -1 | awk '{print $1}')'

### Таблица


number=1
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "#" "Name of network interface" "MAC adress" "IP adress" "Speed conection"
for var in $(ls /sys/class/net)
do
MAC=$(ifconfig $var | grep -E 'ether' | awk '{print $2}') 
IP=$(ifconfig $var | grep -E 'inet ' | awk '{print $2}')
if [ $var != "lo" ] && [ ${#IP} != 0 ];
then
speed=$(speedtest --secure | grep -E '^Download' | awk '{print $2, $3}')
else
speed=' '
fi
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "$number" "$var" "$MAC" "$IP" "$speed"  
number=$[$number + 1]
done



## Код

`#!/bin/bash`

echo -e "\nDate: $(date)\nAccount name: $USER"

echo "PC domain name: $(hostname -f)"

echo -e "\nProcessor:\n $(lscpu | grep "Model name")\n $(lscpu | grep Architecture)\n Clock frequency - $(cat /proc/cpuinfo | grep "cpu MHz" | sed s/[^0-9]//g | sed '2, $d') MHz"

echo -e " Number of cores - $(cat /proc/cpuinfo | grep "cpu cores" | wc -l)\n Number of threads per core - $(lscpu | grep Thread | wc -l)\n"

echo "Random access memory:"

echo " Total - $(cat /proc/meminfo | grep "MemTotal:" | sed s/[^0-9]//g) kB"

echo " Available - $(cat /proc/meminfo | grep "MemAvailable:" | sed s/[^0-9]//g) kB"

echo -e "\nHard disk:\n Total - $(df -h / | sed '2!D' | awk '{printf $2}')\n Available - $(df -h / | sed '2!D' | awk '{printf $4}')"

echo " Mounted to the root directory /- $(df -h / | sed '2!D' | awk '{printf $2}')"

echo -e " SWAP total - $(free -h | grep -E 'Swap' | awk '{print $2}')\n SWAP available - $(free -h | grep -E 'Swap' | awk '{print $4}')"

echo -e "\nNetwork interfaces:\n Number of network interfaces - $(ls /sys/class/net | cat -n | tail -1 | awk '{print $1}')"


number=1
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "#" "Name of network interface" "MAC adress" "IP adress" "Speed conection"
for var in $(ls /sys/class/net)
do
MAC=$(ifconfig $var | grep -E 'ether' | awk '{print $2}') 
IP=$(ifconfig $var | grep -E 'inet ' | awk '{print $2}')
if [ $var != "lo" ] && [ ${#IP} != 0 ];
then
speed=$(speedtest --secure | grep -E '^Download' | awk '{print $2, $3}')
else
speed=' '
fi
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "$number" "$var" "$MAC" "$IP" "$speed"  
number=$[$number + 1]
done

