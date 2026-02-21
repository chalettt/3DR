#include "visual.h"
#include "camera.h"

Point *handle_args(int argc, char **argv)
{
  Point *origin = malloc(sizeof(Point));
  origin->z = 500;
  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-x"))
      origin->x = atoi(argv[++i]);
    else if (!strcmp(argv[i], "-y"))
      origin->y = atoi(argv[++i]);
    else if (!strcmp(argv[i], "-z"))
      origin->z = atoi(argv[++i]);
  }
  return origin;
}

int main(int argc, char **argv)
{
  if (sdl_init())
    return 1;

  // Creating the window and renderer.
  SDL_Window *window = create_window(WIDTH, HEIGHT);
  SDL_Renderer *renderer = create_renderer(window);

  unsigned running = 1;
  SDL_Event event;

  // Creating the rotating cube.
  Point *origin = handle_args(argc, argv);
  Cube *cube = create_cube(CUBE_SIZE, origin);
  init_camera(0, 0, 0);

  // Rotation speed.
  double alpha = 0.025;
  // Movement speed.
  double delta = 2;

  SDL_SetRelativeMouseMode(SDL_TRUE);

  // Window loop
  while (running)
  {
    double mouse_delta_x, mouse_delta_y = 0.0; 

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        // If the window gets terminated.
        case SDL_QUIT:
          // Exit the loop;
          running = 0;
          break;
        case SDL_MOUSEMOTION:
        {
          mouse_delta_x = event.motion.xrel;
          mouse_delta_y = event.motion.yrel;

          if (mouse_delta_x != 0)
            rotate_camera_y(alpha, mouse_delta_x/10);
          if (mouse_delta_y != 0)
            rotate_camera_x(alpha, -mouse_delta_y/10);
          break;
        }
        case SDL_MOUSEBUTTONDOWN:
          SDL_SetRelativeMouseMode(SDL_TRUE);
          break;
        default:
          break;
      }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    if (state[SDL_SCANCODE_ESCAPE]) {
      SDL_SetRelativeMouseMode(SDL_FALSE);
    }
    
    if (state[SDL_SCANCODE_J]) {
      SDL_Surface *john_surface = SDL_LoadBMP("john.bmp");
        
      if (john_surface) {
        SDL_Texture *john_texture = SDL_CreateTextureFromSurface(renderer, john_surface);
        
        SDL_RenderCopy(renderer, john_texture, NULL, NULL); 
        SDL_RenderPresent(renderer);
        
        SDL_DestroyTexture(john_texture);
        SDL_FreeSurface(john_surface);
      } else {
        LOG("Could not open John not an error: %s\n", SDL_GetError());
      }
    }

    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
      move_camera(LEFT, delta);

    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
      move_camera(RIGHT, delta);

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
      move_camera(FRONT, delta);

    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
      move_camera(BACK, delta);

    if (state[SDL_SCANCODE_SPACE])
      move_camera(UP, delta);

    if (state[SDL_SCANCODE_LCTRL])
      move_camera(DOWN, delta);

    if (state[SDL_SCANCODE_LSHIFT])
      delta = 5;
    else 
      delta = 2;

    // Clears the window.
    SDL_SetRenderDrawColor(renderer, BLACK, 255);
    SDL_RenderClear(renderer);

    // Draws the rotated cube in red.
    rot_cube_y(cube, cube->position, alpha);
    draw_cube(renderer, cube);
    SDL_RenderPresent(renderer);

    // 60 frames a second.
    SDL_Delay(1000 / 60);
  }

  // Properly quits sdl.
  sdl_quit(renderer, window);

  // Frees everything
  destroy_cube(cube);
  free(origin);

  return 0;
}
