#include "includes.h"
#define MASS (3)//кориков сказал писать в массиве вместо цифр константы, определенне через диффаин
 /**
\mainpage Gonki
# Gonki_project
Гонки- аркадная двухмерная игра. Она имеет вид сверху.

## Getting Started
Эта игра написана на #С с использованием библиотеки Allegro.

### Directory structure
The source code is organized as follows:

Subdirectory | Description
-------------|-------------------
src/         | source files
src/tests    | unit tests
doc/         | documentation
res/     | static resources

*/
/*!
@file gonki.c
@brief Главная функция проекта
*  Главная функция проекта.В данной функции подключается библиотека Allegro5 и различные ее пакеты.Функция отвечает за работу дисплея .
*@author Klimentova Irina - ira23121998@mail.ru \n
    *@author Arkhipova Ekaterina - arkat98@mail.ru
 \fn int main()
##Игровой цикл можно разделить на 3 части:
###Первая часть:
** *Объявление переменных и отрисовка объектов*
###Вторая часть:
** *Здесь находится меню*
###Третья часть:
** *Игровой цикл*
 *
*/

int main(){
	int gorizontal_disp = 800;//ширина экрана в пикселях
	int vertical_disp = 600;//высота экрана
	int user_status = 2;//состояние игрока переменная если =0 , то выйти из игры, если 1 - то войти в игру, если 2 то войти в меню
	int FPS = 60;// частота обновления экрана
	int left_border = 50;//отрисовка линий левой
	int rigth_border = 450;//отрисовка линии правой
	int cener_line = 250;// отрисовка центральной линии
	int change_dir_right = 0;//двигать котика вправо
	int change_dir_left = 0;//двигать котика влево
	int coordinates_player_x = 90;//максимальное левое положение игрока
	int coordinates_player_y = 400;//максимальное правое положение
	int enemies[MASS][MASS] = {{0,0,0},{0,0,0},{0,0,0}};//массив для 3х врагов и у каждого по три состояния 1й элемент - наличие врага, 2 элемент - координаты врага, 3 элемент - дорога, по которой двигается враг
	int rest_time = 0;//время задержки перед выходом врагов
	int enemies_spawn = 0;//переменная, которая говорит, нужно ли "выпускать врагов"
	int timer_enemy_go = 0;//время, через которое выходит новый враг
	int index_enemy = 0;// номер врага, которого нужно выпустить
	int score = 0;// очки
	int stage = 1;//уровень
	float speed = 0;//скорость игры 


	if(!al_init()){//если аллегро инициализировано то возращает единицу, !- меняет 1 на 0, когда условие выполняется то 1 меняется на 0  и ошибка не выводится, когда условие не выполняется, то 0 меняется на 1 и 1 возвращается и выводится сообщение об ошибке
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}  

	if(!al_init_ttf_addon()) { //тоже самое шрифт
		fprintf(stderr, "failed to initialize allegro ttf_addon!\n");
		return -1;
	}

	if(!al_init_image_addon()) {//картинки
		fprintf(stderr, "failed to initialize allegro image_addon!\n");
		return -1;
	}

	if(!al_init_primitives_addon()) {// примитивы -линии, черточки полосочки 
		fprintf(stderr, "failed to initialize allegro primitives_addon!\n");
		return -1;
	}

	if(!al_install_keyboard()) {//подключение клавы
		fprintf(stderr, "failed to initialize allegro install_keyboard!\n");
		return -1;
	}

	if(!al_init_font_addon()) {//подключение шрифтов
		fprintf(stderr, "failed to initialize allegro font_addon!\n");
		return -1;
	}

	ALLEGRO_DISPLAY *display = NULL;//создали дисплей с помощью указателя и сказали что он равен нулю
	ALLEGRO_FONT *font = NULL;//создали шрифт
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;//создали очередь событий
	ALLEGRO_TIMER *timer =NULL;//создали таймер
	ALLEGRO_BITMAP *unicorn = NULL;//создали единорога
	ALLEGRO_BITMAP *cat = NULL;//котик
	ALLEGRO_BITMAP *cat_enemy = NULL;//враг котика
	ALLEGRO_BITMAP *cat_enemy2 = NULL;// враг котика 2

	display = al_create_display(gorizontal_disp, vertical_disp);//создали	   
	font = al_load_ttf_font("Res/font.ttf", 16,0);//создаем шрифт размером 16 и выгружаем его из папки рес
	timer = al_create_timer(1.0/FPS);//создаем таймер с частотой 1/60 кадров в секунду
	event_queue = al_create_event_queue();//создали очередь
	unicorn = al_load_bitmap("Res/unicorn.png");//загрузили картинку единорога
	cat = al_load_bitmap("Res/cat.png");
	cat_enemy = al_load_bitmap("Res/enemy_cat.png");
	cat_enemy2 = al_load_bitmap("Res/enemy_cat2.png");

	al_register_event_source(event_queue, al_get_keyboard_event_source());//аллегро региструет события из источника( в очередь событий события с клавиатуры)
	al_register_event_source(event_queue, al_get_display_event_source(display));//( с дисплея)
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//( с таймера)
	al_start_timer(timer);//запустили таймер

	while(user_status>0)//начало игрового цикла(если 0 больше нуля игра играет)
		{
			ALLEGRO_EVENT ev;//говорим очереди начинать с этого момента регистрировать
			al_wait_for_event(event_queue, &ev);// ожидай события (вот такого типа вот в эту переменную)
			
			menu:
			//Отрисовываем меню, пока пользователь не нажмет кнопку
			while(user_status == 2){
				ALLEGRO_EVENT ev_menu;//создали овую очередь, которая ожидает событий
				al_wait_for_event(event_queue, &ev_menu);//ожидай очередь 
				al_draw_textf(font, al_map_rgb(255,255,255), gorizontal_disp/2 , //отрисовывай шрифт(шрифт, белй, по х и у)
					vertical_disp/2.5 ,ALLEGRO_ALIGN_CENTRE, "Press Enter to play the game");
				al_draw_textf(font, al_map_rgb(255,255,255), gorizontal_disp/2 , 
					vertical_disp/3 ,ALLEGRO_ALIGN_CENTRE, "Press Esc to exit the game");
				al_flip_display();//выведи то, что мы хотели рисовать
				al_clear_to_color(al_map_rgb(87,87,87));//отчисти экран и закрасить его серым

				if(ev_menu.type == ALLEGRO_EVENT_KEY_DOWN)//если очередель равна зажатие клавиши то выполняется цикл
				{
					switch(ev_menu.keyboard.keycode)//цикл смотрит какая из кнопок нажата
					{
						case ALLEGRO_KEY_ENTER://ЕСЛИ зажатая клавиша оказалась интер, то присваивает значение 1 
							user_status = 1;
							break;//  выходит из цыкла
						case ALLEGRO_KEY_ESCAPE://если зажалось эскйп то 0
							user_status = 0;
							break;
						default://ни одна из кнопок не опознана
							break;
					}
				}
			}

			//основной игровой цикл
			while(user_status == 1){//если пользователь нажал интер
				ALLEGRO_EVENT ev; //ожидаем событие
				al_wait_for_event(event_queue, &ev);
				al_draw_line(left_border , 0, left_border , 
					vertical_disp, al_map_rgb(255,255,255),4); //отрисовываем границы движения
				al_draw_line(rigth_border, 0, rigth_border, 
					vertical_disp, al_map_rgb(255,255,255),4);
				al_draw_line(cener_line-4, 0, cener_line-4,
					vertical_disp, al_map_rgb(255,255,255),1);
				al_draw_line(cener_line+4, 0, cener_line+4,
					vertical_disp, al_map_rgb(255,255,255),1);
				al_draw_bitmap(cat,coordinates_player_x , coordinates_player_y, 0);//отрисовываем котика 
			 	
				if(stage%2){//если уровень делится на 2 без остатка то единорог сотрит влево
					al_draw_bitmap(unicorn, 350 , 180 , 0);
				}
				else{
					al_draw_bitmap(unicorn, 350 , 180 , ALLEGRO_FLIP_HORIZONTAL);
				}
				//Распознование нажтых клавиш

				if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_ESCAPE:// если зажато эск, то выйти в меню
							user_status = 2;
							break;
						case ALLEGRO_KEY_LEFT://если зажато влево то двигаться в лево
							change_dir_left = 1;
							change_dir_right = 0;
							break;
						case ALLEGRO_KEY_RIGHT://если зажато вправо, то двигаться влево
							change_dir_right = 1;
							change_dir_left = 0;
							break;
						default:
							break;
					}
				}

				//увеличение скорости с уровнями

				speed = (10.0+stage)/10.0;// скорость увеличивается на 10 процентов

				//плавное изменение положения машинки игрока

				if(change_dir_left){//котик двигается влево
					coordinates_player_x -= 10*speed;//координата зависит от скорости, с каждым уровнем котик двигется быстрее
					if(coordinates_player_x<= 90)//если ты перепрыгнул за 90, то
					{
						coordinates_player_x = 90;//присвоить тебе 90
						change_dir_left = 0;// и больше не двигать тебя влево
					}
				}

				if(change_dir_right){
					coordinates_player_x += 10*speed;
					if(coordinates_player_x>= 290)
					{
						coordinates_player_x = 290;
						change_dir_right = 0;
					}
				}

				//Задержка перед началом игры

				if(rest_time<180 && enemies_spawn == 0){
					rest_time++;// прибавляется единица
				}

				else if(rest_time >= 180 && enemies_spawn == 0){
					rest_time = 0;
					enemies_spawn = 1;
				}				
				//генерация встречных машин

				if(enemies_spawn){//если появление врагов включено то выполняется цикл

					//время "выпускания" новой машины
					if(timer_enemy_go > 120/speed){// время между врагами должно быть больше
						enemies[index_enemy][0] = 1;//говорит котику что он жив
						enemies[index_enemy][2] = rand() % 2 - 1 ; // говорит по какой дорожке бежать
						timer_enemy_go = 0;//если время между врагами больше 120
						index_enemy++;
						if(index_enemy > 2) index_enemy =0;// если индекс стал равен 3 то снова ноль
					}
					else{
						timer_enemy_go++;
					}

					//цикл для отрисовки машин 
					for(int i = 0; i < 3; i++){//три риза прогоняет цикл
						if(enemies[i][0]){//только для жвыых котиков
							//цикл проверки на столкновение
							if(enemies[i][2]){// если по провой дороже побежит то этот цикл
								al_draw_bitmap(cat_enemy, 290 , enemies[i][1] - 170 , 0);//смещается на 170 вверх	
								if(290 < coordinates_player_x + 120 &&  enemies[i][1] - 170 < coordinates_player_y + 170 
									&& enemies[i][1] > coordinates_player_y){
									al_flip_display();//обновить
									al_rest(1.5);//отдыхаем 1.5 секунды, чтобы ты понял что проиграл
									user_status = 2;
									change_dir_right =0;
									change_dir_left = 0;
									coordinates_player_y = 400;
									coordinates_player_x = 90;
									timer_enemy_go = 0;
									enemies_spawn = 0;
									stage = 0;
									score = 0;
									for(int i = 0; i<3; i++){
										for(int j = 0; j< 3 ; j++){
											enemies[i][j] = 0;//убийство котиков
										}
									}
									goto menu;
								}
							}
							else{
								al_draw_bitmap(cat_enemy2, 90 , enemies[i][1] - 170 , 0);	
								if(210 > coordinates_player_x  &&  enemies[i][1] - 170 < coordinates_player_y + 170 
									&& enemies[i][1] > coordinates_player_y){
									al_flip_display();
									al_rest(1.5);
									user_status = 2;
									change_dir_right =0;
									change_dir_left = 0;
									coordinates_player_y = 400;
									coordinates_player_x = 90;
									timer_enemy_go = 0;
									enemies_spawn = 0;
									stage = 0;
									score = 0;
									for(int i = 0; i<3; i++){
										for(int j = 0; j< 3 ; j++){
											enemies[i][j] = 0;
										}
									}
									goto menu;//откидывй тебя к флагу меню
								}
							}
							enemies[i][1] += 5*speed;//котик быстрее начинает двигаться
							if(enemies[i][1] >= 770)// умирает как только уходит за экран
							{
								enemies[i][0] = 0;
								enemies[i][1] = 0;
								score ++;//как только котик вражеский умирает очки увеличиваются
							}
						}
					}
				}
				// отрисовка уровня и колличества наюранных очков
				al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 150 , 
					30 ,ALLEGRO_ALIGN_CENTRE, "SCORE: %d" , score);
				al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 150 , 
					60 ,ALLEGRO_ALIGN_CENTRE, "STAGE: %d" , stage);
				al_draw_filled_rectangle( 510, 90 , 790, 130, al_map_rgb(17,28,39));
				al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 200 , 
					100 ,ALLEGRO_ALIGN_CENTRE, "Press Esc to exit to menu");

				//увеличение уровня
				if(score == stage * 10) {//уровень зависит от очков, а очки от смерти котиков
					stage ++;
				}

				//отрисовывание всех объектов
				if(al_is_event_queue_empty(event_queue))//если очередь пуста, то обновим дисплей и все закрасим
					{
						al_flip_display();
						al_clear_to_color(al_map_rgb(148,0,211));
					}

			}
		}


	//Уничтожение созданных объектов библиотеки аллегро
	al_flip_display();
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_bitmap(unicorn);
	al_destroy_bitmap(cat);
	al_destroy_bitmap(cat_enemy);
	al_destroy_bitmap(cat_enemy2);

	return 0;
}

