## Part 1. Установка ОС

##### Установить **Ubuntu 20.04 Server LTS** без графического интерфейса. (Используем программу для виртуализации - VirtualBox)

 `- cat /etc/issue.`

![img](screenshots/1.png)

## Part 2. Создание пользователя

`- sudo usermod`

##### Создать пользователя, отличного от пользователя, который создавался при установке. Пользователь должен быть добавлен в группу `adm`.
 `- getent group adm`

![img](screenshots/2.png)
 `- cat /etc/passwd`

 ![img](screenshots/2.1.png)

## Part 3. Настройка сети ОС

##### Задать название машины вида user-1 

 `- sudo vim /etc/hostname`

![img](screenshots/3.png)
##### Установить временную зону, соответствующую вашему текущему местоположению.  
 `- sudo timedatectl set-timezone Europe/Moscow`
![img](screenshots/4.png)
##### Вывести названия сетевых интерфейсов с помощью консольной команды.

`- ip addr show`

	lo (loopback device) – виртуальный интерфейс, присутствующий по умолчанию в любом Linux. Он используется для отладки сетевых программ и запуска серверных приложений на локальной машине. С этим интерфейсом всегда связан адрес 127.0.0.1. У него есть dns-имя – localhost.


![img](screenshots/5.1.png)

##### Используя консольную команду получить ip адрес устройства, на котором вы работаете, от DHCP сервера. 

`- hostname -I` 

	Протокол DHCP — это протокол клиента или сервера, который автоматически предоставляет узел протокола IP с его IP-адресом и другие связанные сведения о конфигурации, такие как маска подсети и шлюз по умолчанию.

![img](screenshots/5.png)

##### Определить и вывести на экран внешний ip-адрес шлюза (ip) и внутренний IP-адрес шлюза, он же ip-адрес по умолчанию (gw). 

`- curl http://ipecho.net/plain`
	
	Внешний ip адрес шлюза

![img](screenshots/6.png)

` - ip route`

	Внутренний ip адрес шлюза

![img](screenshots/7.png)

##### Определить и вывести на экран внешний ip-адрес шлюза (ip) и внутренний IP-адрес шлюза, он же ip-адрес по умолчанию (gw). 
##### Задать статичные (заданные вручную, а не полученные от DHCP сервера) настройки ip, gw, dns (использовать публичный DNS серверы, например 1.1.1.1 или 8.8.8.8). 

` - ip route`

![img](screenshots/7.1.png)

`- sudo vim /etc/netplan/*.yaml`

![img](screenshots/8.1.png)

`- ping 1.1.1.1`

![img](screenshots/9.png)

`- ping 8.8.8.8`

![img](screenshots/10.png)

##### Перезагрузить виртуальную машину. Убедиться, что статичные сетевые настройки (ip, gw, dns) соответствуют заданным в предыдущем пункте. 

`- reboot`

## Part 4. Обновление ОС

##### Обновить системные пакеты до последней на момент выполнения задания версии.  

`- sudo apt-get update`

`- sudo apt-get upgrade`

![img](screenshots/11.1.png)

## Part 5. Использование команды **sudo**

##### Разрешить пользователю, созданному в [Part 2](#part-2-создание-пользователя), выполнять команду sudo.

	sudo - это важная для понимания утилита, она позволяет временно поднимать привилегии и выполнять задачи администрирования системы. Суть в том, что в каждом дистрибутиве Linux есть пользователь root, имеющий максимальные права .

`-sudo adduser %username sudo`

	Для проверки используем:

`-sudo -l -U ubuntuserver`

![img](screenshots/12.png)

![img](screenshots/12.1.png)

## Part 6. Установка и настройка службы времени

##### Настроить службу автоматической синхронизации времени. 

`-timedatectl show`

![img](screenshots/13.png)

## Part 7. Установка и использование текстовых редакторов 

##### Установить текстовые редакторы **VIM** (+ любые два по желанию **NANO**, **MCEDIT**, **JOE** и т.д.)  

##### Используя каждый из трех выбранных редакторов, создайте файл *test_X.txt*, где X -- название редактора, в котором создан файл. Напишите в нём свой никнейм, закройте файл с сохранением изменений.

	VIM :wq

![img](screenshots/14.png)

	NANO CTRL + X, Yes

![img](screenshots/15.png)

	MCEDIT F10, Yes

![img](screenshots/16.png)

##### Используя каждый из трех выбранных редакторов, откройте файл на редактирование, отредактируйте файл, заменив никнейм на строку "21 School 21", закройте файл без сохранения изменений.

	VIM :q!

![img](screenshots/17.png)

	NANO CTRL + X, No

![img](screenshots/18.png)

	MCEDIT F10, No

![img](screenshots/19.png)

##### Используя каждый из трех выбранных редакторов, отредактируйте файл ещё раз (по аналогии с предыдущим пунктом), а затем освойте функции поиска по содержимому файла (слово) и замены слова на любое другое.

	VIM :s/stealyro/stealyrosuperuser

![img](screenshots/20.png)

	NANO CTRL + \, ENTER, ENTER

![img](screenshots/21.png)

	MCEDIT F4, NEXT

![img](screenshots/22.png)

## Part 8. Установка и базовая настройка сервиса **SSHD**

##### Установить службу SSHd.  

`- sudo apt install openssh-server -y`

##### Добавить автостарт службы при загрузке системы.

`- sudo systemctl enable ssh`

##### Перенастроить службу SSHd на порт 2022. 

`- sudo vim /etc/ssh/sshd_config`

##### Используя команду ps, показать наличие процесса sshd. Для этого к команде нужно подобрать ключи.

`- ps aux | grep sshd`

![img](screenshots/24.1.png)

`- sudo netstat -plant | grep ssh`

![img](screenshots/24.2.png)

![img](screenshots/24.3.png)

##### Перезагрузить систему.

`- reboot`

## Part 9. Установка и использование утилит **top**, **htop**

##### Установить и запустить утилиты top и htop.  

![img](screenshots/26.png)

![img](screenshots/27.png)

![img](screenshots/28.png)

![img](screenshots/29.png)

![img](screenshots/30.png)

![img](screenshots/31.png)

![img](screenshots/32.png)

![img](screenshots/34.png)

## Part 10. Использование утилиты **fdisk**

##### Запустить команду fdisk -l.

![img](screenshots/35.png)

![img](screenshots/36.png)

## Part 11. Использование утилиты **df** 

##### Запустить команду df.

![img](screenshots/37.png)

##### Запустить команду df -Th.

![img](screenshots/38.png)

## Part 12. Использование утилиты **du**

##### Запустить команду du.
##### Вывести размер папок /home, /var, /var/log (в байтах, в человекочитаемом виде)

![img](screenshots/39.png)

![img](screenshots/40.png)

![img](screenshots/41.png)

![img](screenshots/42.png)


## Part 13. Установка и использование утилиты **ncdu**

![img](screenshots/43.png)

![img](screenshots/44.png)

![img](screenshots/45.png)

## Part 14. Работа с системными журналами
![img](screenshots/46.1.png)

![img](screenshots/46.png)

![img](screenshots/47.png)

## Part 15. Использование планировщика заданий **CRON**

`- crontab -e`

![img](screenshots/48.png)

![img](screenshots/49.png)

`- crontab -r || закомментировать`

![img](screenshots/50.png)