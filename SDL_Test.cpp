
#include <iostream>
#include <SDL.h>
#include "Node.h"

int create_window();
SDL_Event create_events();

int main(int argc,char* args[])
{
    SDL_Init(SDL_INIT_VIDEO);
    std::cout << "Window Initializing..!\n";
    create_window();
    return 0;
}

int create_window() {

    const int width = 800;
    const int height = 600;
    int windowShouldClose = -1;

    Node* nodes = (Node*)malloc(sizeof(Node) * 100);

    Uint32* pixels = new Uint32[width * height];

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Window Initializing..!", "Window Initializing. Please Wait",NULL);

    SDL_Window* window = SDL_CreateWindow("Search Algorithms", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_Event event = create_events();

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++) {

            nodes[i + j * 20] = Node(i , j, Node::Status::NORMAL);

            std::cout << i + j * 10 << "\n";
            if (i == 19 && j == 19) {
                nodes[i * 20 + j] = Node(i ,j ,Node::Status::GOAL);
            }
            if (i == 0 && j == 0) {
                nodes[i * 20 + j] = Node(i, j, Node::Status::START);
            }
        }
        
    }

    //Draw grid 
    while (windowShouldClose == -1) {

        SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            windowShouldClose = 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 400; i++) {

            SDL_Rect rect;

            rect.w = 15;
            rect.h = 15;

            rect.x = nodes[i].posX * (20 + 3) ;
            rect.y = nodes[i].posY * (20 + 3);

            if (nodes[i].status == Node::Status::GOAL) {
                SDL_SetRenderDrawColor(renderer, 150, 255, 0, 255);
            }
            else if(nodes[i].status == Node::Status::NORMAL){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else if (nodes[i].status == Node::Status::START) {
                SDL_SetRenderDrawColor(renderer, 200, 125, 90, 255);
            }

            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
        }

        
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

SDL_Event create_events() {
    SDL_Event sdl_event{};
    return sdl_event;
}


