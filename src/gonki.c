#include "includes.h"
#include "functions.h"
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
** *Эта часть представляет собой набор команд для отрисовки меню*
###Вторая часть:
** *Здесь находится основной игровой цикл*
###Третья часть:
** *Цикл для отрисовки машин, уровня и всех объектов*
 *
*/

int main()
{
	int const gorizontal_disp = 800; // ширина экрана
	int const vertical_disp = 600;//высота экрана
	int user_status = 2;// если переменная 0-выйти из игры, если 1-войти в игру, если 2-меню
	int FPS = 60;// частота обновления кадров
	int left_border = 50;//  отрисовка линий
	int rigth_border = 450;//  отрисовка линий
	int cener_line = 250;//отрисовка линий
	int change_dir_to_right = 0;// двигать котика вправо
	int change_dir_to_left = 0;//  двигать котика влево
	int coordinates_player_x = 90;// максимально левое положение игрока
	int coordinates_player_y = 400;// максимальное правое положение игрока
	int enemies[3][3] = {{0,0,0},{0,0,0},{0,0,0}};// массив врагов; первый элемент - наличие врага, второй - его координаты, третий - дорога
	int rest_time = 0;// время задержки перед выходом врагов
	int enemies_spawn = 0;// переменная, которая говорит нужно ли выпускаь врагов
	int timer_of_enemy_go = 0;// время между выходом врагов
	int index_enemy = 0;// номер врага, которого нужно выпускать
	int score = 0;// очки
	int stage = 1;// уровень
	float speed = 0;// скорость игры
 

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   


    al_init_ttf_addon();
    al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer =NULL;
	ALLEGRO_BITMAP *unicorn = NULL;
	ALLEGRO_BITMAP *cat = NULL;
	ALLEGRO_BITMAP *cat_enemy = NULL;
	ALLEGRO_BITMAP *cat_enemy2 = NULL;

 


	display = al_create_display(gorizontal_disp, vertical_disp);
	   if(!display) {
	      fprintf(stderr, "failed to create display!\n");
	      return -1;
	   }
    font = al_load_ttf_font("Res/font.ttf", 16,0);
    timer = al_create_timer(1.0/FPS);
    event_queue = al_create_event_queue();
    unicorn = al_load_bitmap("Res/unicorn.png");
    cat = al_load_bitmap("Res/cat.png");
    cat_enemy = al_load_bitmap("Res/enemy_cat.png");
	cat_enemy2 = al_load_bitmap("Res/enemy_cat2.png");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);



    while(user_status>0)
	   	{
	   		ALLEGRO_EVENT ev;
	   		al_wait_for_event(event_queue, &ev);
			

			menu:
	   		/*  Отрисовываем меню, пока пользователь не нажмет кнопку */
	   		while(user_status == 2){
	   			ALLEGRO_EVENT ev_menu;
	   			al_wait_for_event(event_queue, &ev_menu);
	   			al_draw_textf(font, al_map_rgb(255,255,255), gorizontal_disp/2 , vertical_disp/2.5 ,ALLEGRO_ALIGN_CENTRE, "Press Enter to play the game");
	   			al_draw_textf(font, al_map_rgb(255,255,255), gorizontal_disp/2 , vertical_disp/3 ,ALLEGRO_ALIGN_CENTRE, "Press Esc to exit the game");
	   			al_flip_display();
	   			al_clear_to_color(al_map_rgb(87,87,87));

			 	if(ev_menu.type == ALLEGRO_EVENT_KEY_DOWN)
			 	{
					switch(ev_menu.keyboard.keycode)
					{
		 		 		case ALLEGRO_KEY_ENTER:
			 				user_status = 1;
							break;
						case ALLEGRO_KEY_ESCAPE:
							user_status = 0;
							break;
			 		}
			 	}
	   		}

	   		/* основной игровой цикл */
	   		while(user_status == 1){
	   			ALLEGRO_EVENT ev;
	   			al_wait_for_event(event_queue, &ev);
	   			al_draw_line(left_border , 0, left_border , vertical_disp, al_map_rgb(255,255,255),4); /* отрисовываем границы движения */
	   			al_draw_line(rigth_border, 0, rigth_border, vertical_disp, al_map_rgb(255,255,255),4);
	   			al_draw_line(cener_line-4, 0, cener_line-4, vertical_disp, al_map_rgb(255,255,255),1);
	   			al_draw_line(cener_line+4, 0, cener_line+4, vertical_disp, al_map_rgb(255,255,255),1);
	   			al_draw_bitmap(cat,coordinates_player_x , coordinates_player_y, 0);	
			 					


	   			if(stage%2){
	   				al_draw_bitmap(unicorn, 350 , 180 , 0);
	   			}
	   			else{
	   				al_draw_bitmap(unicorn, 350 , 180 , ALLEGRO_FLIP_HORIZONTAL);
	   			}
	   			/* Распознование нажтых клавиш */
	   			
	   			if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
			 	{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_ESCAPE:
							user_status = 2;
							break;
						case ALLEGRO_KEY_LEFT:
		      				change_dir_to_left = 1;
		      				change_dir_to_right = 0;
		      				break;
		      			case ALLEGRO_KEY_RIGHT:
		      				change_dir_to_right = 1;
		      				change_dir_to_left = 0;
		      				break;
			 		}
			 	}


			 	/* увеличение скорости с уровнями */

			 	speed = get_speed(stage);

			 	/* плавное изменение положения машинки игрока */

			 	if(change_dir_to_left){
			 		coordinates_player_x -= 10*speed;
			 		if(coordinates_player_x<= 90)
			 		{
			 			coordinates_player_x = 90;
			 			change_dir_to_left = 0;
			 		}
			 	}


			 	if(change_dir_to_right){
			 		coordinates_player_x += 10*speed;
			 		if(coordinates_player_x>= 290)
			 		{
			 			coordinates_player_x = 290;
			 			change_dir_to_right = 0;
			 		}
			 	}


			 	/* Задержка перед началом игры*/

			 	rest_time = get_if(rest_time,enemies_spawn);
			 	
			 	if(rest_time >= 180 && enemies_spawn == 0){
			 		rest_time = 0;
			 		enemies_spawn = 1;
			 	}


			 	/* генерация встречных машин */

			 	if(enemies_spawn){

			 		
			 		/* время "выпускания" новой машины*/
			 		if(timer_of_enemy_go > 120/speed){
			 			enemies[index_enemy][0] = 1;
			 			enemies[index_enemy][2] = rand() % 2 - 1 ; 
			 			timer_of_enemy_go = 0;
			 			index_enemy++;
			 			if(index_enemy > 2) index_enemy =0;
			 		}
			 		else{
			 			timer_of_enemy_go++;
			 		}

			 		/* цикл для отрисовки машин */
			 		for(int i = 0; i < 3; i++){
			 			if(enemies[i][0]){
			 				/* цикл проверки на столкновение */
			 				if(enemies[i][2]){
			 					// al_draw_filled_rectangle( 290, enemies[i][1] - 170 , 410, enemies[i][1], al_map_rgb(200,170,150));
			 					al_draw_bitmap(cat_enemy, 290 , enemies[i][1] - 170 , 0);	
			 					if(290 < coordinates_player_x + 120 &&  enemies[i][1] - 170 < coordinates_player_y + 170 
			 						&& enemies[i][1] > coordinates_player_y){
			 						al_flip_display();
			 						al_rest(1.5);
			 						user_status = 2;
			 						change_dir_to_right =0;
			 						change_dir_to_left = 0;
			 						coordinates_player_y = 400;
			 						coordinates_player_x = 90;
			 						timer_of_enemy_go = 0;
			 						enemies_spawn = 0;
			 						stage = 0;
			 						score = 0;
			 						for(int i = 0; i<3; i++){
			 							for(int j = 0; j< 3 ; j++){
			 								enemies[i][j] = 0;
			 							}
			 						}
			 						goto menu;
			 					}
			 				}
			 				else{
			 					// al_draw_filled_rectangle( 90, enemies[i][1] - 170 , 210, enemies[i][1], al_map_rgb(150,170,200));	
			 					al_draw_bitmap(cat_enemy2, 90 , enemies[i][1] - 170 , 0);	
			 					if(210 > coordinates_player_x  &&  enemies[i][1] - 170 < coordinates_player_y + 170 
			 						&& enemies[i][1] > coordinates_player_y){
			 						al_flip_display();
			 						al_rest(1.5);
			 						user_status = 2;
			 						change_dir_to_right =0;
			 						change_dir_to_left = 0;
			 						coordinates_player_y = 400;
			 						coordinates_player_x = 90;
			 						timer_of_enemy_go = 0;
			 						enemies_spawn = 0;
			 						stage = 0;
			 						score = 0;
			 						for(int i = 0; i<3; i++){
			 							for(int j = 0; j< 3 ; j++){
			 								enemies[i][j] = 0;
			 							}
			 						}
			 						goto menu;
			 					}
			 				}
			 				enemies[i][1] += 5*speed;
			 				if(enemies[i][1] >= 770)
			 				{
			 					enemies[i][0] = 0;
			 					enemies[i][1] = 0;
			 					score ++;
			 				}
			 			}
			 		}
			 	}
			 	/* отрисовка уровня и колличества наюранных очков */
			 	al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 150 , 30 ,ALLEGRO_ALIGN_CENTRE, "SCORE: %d" , score);
	   			al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 150 , 60 ,ALLEGRO_ALIGN_CENTRE, "STAGE: %d" , stage);
	   			al_draw_filled_rectangle( 510, 90 , 790, 130, al_map_rgb(17,28,39));
	   			al_draw_textf(font, al_map_rgb(255,255,255), rigth_border + 200 , 100 ,ALLEGRO_ALIGN_CENTRE, "Press Esc to exit to menu");
	   			
	   			/* увеличение уровня, если требуется */
				stage = get_stage(stage, score);

	   			/* отрисовывание всех объектов */
			 	if(al_is_event_queue_empty(event_queue))
		      		{
		      			al_flip_display();
	   					al_clear_to_color(al_map_rgb(148,0,211));
		      		}
			 	
	   		}
	   	}

    

  
   	/* Уничтожение созданных объектов библиотеки аллегро */
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
