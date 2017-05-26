# Информация о проекте.
Гонки- аркадная двухмерная игра (вид сверху). Данная игра ставит перед игроком заработать как можно больше очков и пройти как можно больше уровней.

## Описание интерфейса
Интерфейс игры состоит из меню и игрового поля- двухполостной дороги. С помощью главного меню пользователь осуществляет управление программой. Во время игры отображается возможность выхода в меню. С помощью стрелок клавиатуры пользователь контролирует положение котика на двухполостной дороге, на экране ведется счет уровней и очков. Главная задача игрока не допускать столкновения с вражескими котиками другого цвета. Во время смены уровня единорог поворачивается в противоположенную сторону.
Главное меню ![Image alt](https://github.com/KateArkhipova/polytech.cs.2017.spring_project/raw/master/doc/play_window.png)
Игровое поле ![Image alt](https://github.com/KateArkhipova/polytech.cs.2017.spring_project/raw/master/doc/unicorn.png)
Котик, управляемый игроком ![Image alt](https://github.com/KateArkhipova/polytech.cs.2017.spring_project/raw/master/doc/cat.png)
Вражеские котики ![Image alt](https://github.com/KateArkhipova/polytech.cs.2017.spring_project/raw/master/doc/enemy_cat.png)
![Image alt](https://github.com/KateArkhipova/polytech.cs.2017.spring_project/raw/master/doc/enemy_cat2.png)
### Структура директория
Код организован следующим образом:

Subdirectory | Description
-------------|-------------------
src/         | программные файлы 
src/tests    | тесты
doc/         | документация 
res/         | ресурсы проекта

### Сборка проекта
Для сборки проекта:
````
make
````
Удаление собранных файлов:
````
make clean
````
Для сборки документации:
````
make doxygen
````
Для сборки документации в формате HTML:
````
make html
````
## Authors
Климентова Ирина - ira23121998@mail.ru
Архипова Екатерина - arkat98@mail.ru
## License

Этот проект лицензирован под MIT License - смотри LICENSE файл для подробностей
