#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "CSDLManagerLite.h"

#define PI 3.1415

CSDLManagerLite* CSDLManagerLite::m_instance = NULL;

CSDLManagerLite::CSDLManagerLite() {
    this->m_pWindow = NULL;
    this->m_pRenderer = NULL;
}

CSDLManagerLite* CSDLManagerLite::getInstance() {
    if(m_instance  == NULL)
        m_instance = new CSDLManagerLite();
    return m_instance;
}

int CSDLManagerLite::initializeSDL(int width, int height, const std::string & title) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;

    m_pWindow =      SDL_CreateWindow(
                         title.c_str(),                  // window title
                         SDL_WINDOWPOS_UNDEFINED,           // initial x position
                         SDL_WINDOWPOS_UNDEFINED,           // initial y position
                         width,                               // width, in pixels
                         height,                               // height, in pixels
                         SDL_WINDOW_OPENGL
                     );
    //

    if(m_pWindow == NULL) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize: ", IMG_GetError();
        return -4;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(m_pWindow == NULL) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return -2;
    }

    SDL_GetWindowSize(m_pWindow, &m_w, &m_h);

    return 0;
}

void CSDLManagerLite::drawFrame() {
    SDL_RenderPresent(m_pRenderer);
}


void CSDLManagerLite::delay(int ms) {
    SDL_Delay(ms);
}

void CSDLManagerLite::clean() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}



void CSDLManagerLite::setColor(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(m_pRenderer, r, g, b, alpha);
}

void CSDLManagerLite::drawRectTLCorner(float x, float y, float width, float height) {
    SDL_Rect rec;
    rec.x = x;
    rec.y = y;
    rec.w = width;
    rec.h = height;
    SDL_RenderFillRect(m_pRenderer, &rec);
}

void CSDLManagerLite::drawRectCenter(float x, float y, float width, float height) {
    SDL_Rect rec;
    rec.x = x - width/2;
    rec.y = y - height/2;
    rec.w = width;
    rec.h = height;
    SDL_RenderFillRect(m_pRenderer, &rec);
}

void CSDLManagerLite::drawCircle(int x, int y, float r) {
    int x_1;
    int y_1;
    int x_2;
    int y_2;

    double theta = 0;

    while (theta < 2*PI) {
        x_1 = x+cos(theta)*r;
        y_1 = y-sin(theta)*r;
        theta+=(2*PI/32);
        x_2 = x+cos(theta)*r;
        y_2 = y-sin(theta)*r;
        drawLine(x_1, y_1, x_2, y_2);
    }
}

void CSDLManagerLite::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void CSDLManagerLite::background() {
    setColor(0,0,0,255);
    SDL_RenderClear(m_pRenderer);
}
