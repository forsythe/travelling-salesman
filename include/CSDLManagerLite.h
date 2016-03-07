#ifndef CSDLMANAGERLITE_H
#define CSDLMANAGERLITE_H

#include <iostream>
#include <SDL.h>

class CSDLManagerLite {
public:
    static CSDLManagerLite *getInstance();
    inline SDL_Renderer * getRenderer() {
        return m_pRenderer;
    }
    inline SDL_Window * getWindow() {
        return m_pWindow;
    }

    int initializeSDL(int, int, const std::string &);
    void setColor(int, int, int, int);

    void delay(int);
    void clean();
    void drawRectTLCorner(float, float, float, float);
    void drawRectCenter(float, float, float, float);
    void drawCircle(int, int, float);
    void drawLine(int, int, int, int);
    void drawFrame();
    void background();

    inline int getHeight() {
        return m_h;
    }
    inline int getWidth() {
        return m_w;
    }

protected:
private:
    CSDLManagerLite();
    static CSDLManagerLite * m_instance;
    SDL_Window * m_pWindow;
    SDL_Renderer *m_pRenderer;
    SDL_Surface *m_pSurface;

    int m_h;
    int m_w;
    int m_originX;
    int m_originY;
};

#endif // CSDLMANAGERLITE_H
