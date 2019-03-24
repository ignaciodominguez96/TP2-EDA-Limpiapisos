#include <stdio.h>
#include "Simulation.h"
#include "Floor.h"
#include "Robot.h"
#include "Tile.h"



int draw_floor(ALLEGRO_DISPLAY *display, floor_t * floor)
{
    ALLEGRO_BITMAP *Lines;

    Lines = al_create_bitmap(800,5);


    al_clear_to_color(al_map_rgb(211, 211, 211)); //Set Background to gray


    al_set_target_bitmap(Lines);
    al_clear_to_color(al_map_rgb(255,255,255));



    al_set_target_bitmap(al_get_backbuffer(display)); //Importante setea la pantalla como lugar a dibujar



    //First 6 lanes
    for (int i = 0; i < 800; i += 800/(floor->height))
    {
        for (int j = 0; j < 960; j += 960/(floor->width))
        {
            al_draw_bitmap(Lines, j, i, 0);
        }
    }

    al_destroy_bitmap(Lines);
}


int Draw_robots(ALLEGRO_DISPLAY *display, simulation_t * simulation)
{
  ALLEGRO_BITMAP * Robot;

  Robot = al_create_bitmap(30, 30);

  if(!Robot)//protejo en caso de error
    {
        printf("Failed to create Robot bitmap!\n");
        return -1;
    }

    al_set_target_bitmap(Robot);
    al_clear_to_color(al_map_rgb(0, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    for(i=0 ,i<simulation->cant_robots, i++)
    {
      al_draw_bitmap(Robot, simulation->robots->x, simulation->robots->y, 0);
    }
}


int al_mess_file(ALLEGRO_DISPLAY *display, floor_t * floor)
