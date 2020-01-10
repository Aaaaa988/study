#!/bin/bash
sudo clear
echo -e "Дата: \c"
date
echo -e "Имя учетной записи: \c"
whoami
echo -e "Доменное имя ПК: \c"
hostname

echo "Процессор"
echo -e "	* Модель - \c"
lscpu | sed -n "s/^Модель: *//p"
echo -e "	* Архитектура - \c"
lscpu | sed -n "s/^Архитектура: *//p"
echo -e "	* Тактовая частота - \c"
lscpu | grep "Имя модели: " | cut -d" " -f 17
echo -e "	* Количество ядер - \c"
lscpu | awk "/^CPU.s.:/ { print $NF; exit }" | cut -d" " -f 15
echo -e "	* Количество потоков на ядро - \c"
lscpu | sed -n "s/Потоков на ядро: *//p"

echo  "Оперативная память:"
echo -e "	* Всего - \c"
free -h | grep Память | awk '{print $2}'
echo -e "	* Доступно - \c"
free | grep Память | awk '{print $7}'

echo  "Жесткий диск:"
echo -e "	* Всего - \c"
df | grep "/$" | awk '{print $3}'
echo -e "	* Доступно - \c"
df | grep "/$" | awk '{print $4}'
echo -e "	* Смонтировано в корневую директорию - \c"
df | grep "/$" | awk '{print $1}'
echo -e "	* SWAP всего - \c"
free | grep Подкачка | awk '{print $2}'
echo -e "	* SWAP доступно - \c"
free | grep Подкачка | awk '{print $4}'

echo  "Сетевые интерфейсы:"
echo -e "	* Количество сетевых интерфейсов - \c"
ls /sys/class/net | wc -l
echo "---|--------------------------|------------------|----------|---------------------|"
echo "№  |  Имя сетевого интерфейса |     MAC-адрес    | IP-адрес | Скорость соединения |"
echo "---|--------------------------|------------------|----------|---------------------|"
for ((i = 1; i <= $(ls -A /sys/class/net |wc -l); i++))
do
echo -e "$i  |       $(ip a | grep -w -m 1 "$i" | awk '{print $2}' | sed -e s/://g)   \t      | $(ip a  | grep -A 1 -w -m 1 "$i" | grep -w "link/ether" |  awk '{print $2}' ) | $(ip a | grep -m 2 -w -A 3 "$i" | grep -w -m 1 "inet" | awk '{print $2}') | $(sudo ethtool $(ip a | grep -w -m 1 "$i" | awk '{print $2}' | sed -e s/://g) | grep -w "Speed"| awk '{print $2}') "   
done

echo " "; echo " ";





