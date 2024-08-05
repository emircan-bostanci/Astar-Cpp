
#include <iostream>
#include <SDL.h>
#include "Node.h"
#include "Astar.h"

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

    const int width = 300;
    const int height = 200;
    int windowShouldClose = -1;

    const int columnSize = 15;
    const int rowSize = 15;

    Node* nodes = (Node*)malloc(sizeof(Node) * 100);

    Uint32* pixels = new Uint32[width * height];

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Window Initializing..!", "Window Initializing. Please Wait",NULL);

    SDL_Window* window = SDL_CreateWindow("Search Algorithms", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_Event event = create_events();
    Node* start = NULL;
    Node *goal = NULL;

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < columnSize; j++) {

            nodes[i + j * columnSize] = Node(i , j, Node::Status::NORMAL);

            std::cout << i + j * 10<< "\n";
            if (i == rowSize - 1&& j == columnSize - 1) {
                nodes[i * rowSize + j] = Node(i ,j ,Node::Status::GOAL);
                goal = &nodes[i * rowSize + j];
            }
            if (i == 0 && j == 0) {
                nodes[i * rowSize + j] = Node(i, j, Node::Status::START);
                start = &nodes[0];
            }
        }
        
    }
    Astar astar(start,goal,10,10);
    auto pathList = astar.Find();

    //Draw grid 
    while (windowShouldClose == -1) {

        SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            windowShouldClose = 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < rowSize * columnSize; i++) {

            SDL_Rect rect;

            rect.w = 10;
            rect.h = 10;

            rect.x = nodes[i].posX * (11) ;
            rect.y = nodes[i].posY * (11);

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

        for (int i = 0; i < pathList.size(); i++) {

            SDL_Rect rect;

            rect.w = 10;
            rect.h = 10;

            rect.x = pathList[i]->posX * (11) ;
            rect.y = pathList[i]->posY * (11);

            SDL_SetRenderDrawColor(renderer, 130, 140, 150, 255);

            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
        }



        
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //delete[] pixels;

    SDL_Quit();

    return 0;
}

SDL_Event create_events() {
    SDL_Event sdl_event{};
    return sdl_event;
}


