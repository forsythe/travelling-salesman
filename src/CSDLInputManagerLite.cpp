#include <SDL.h>
#include <iostream>

#include "CSDLInputManagerLite.h"

CSDLInputManagerLite* CSDLInputManagerLite::m_pInstance = NULL;

CSDLInputManagerLite::CSDLInputManagerLite() {
    m_bExit = false;
    m_pvKeyStates = NULL;
}

CSDLInputManagerLite* CSDLInputManagerLite::getInstance() {
    if(m_pInstance == NULL)
        m_pInstance = new CSDLInputManagerLite();
    return m_pInstance;
}

void CSDLInputManagerLite::onKeyDown() {
    m_pvKeyStates = SDL_GetKeyboardState(&m_iNumKeys);
}

void CSDLInputManagerLite::onKeyUp() {
    m_pvKeyStates = SDL_GetKeyboardState(&m_iNumKeys);
}

void CSDLInputManagerLite::update() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if(event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT)) {
            m_bExit = true;
            return;
        }

        switch(event.type) {
        case SDL_QUIT:
            m_bExit = true;
            break;
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        }
    }

}

bool CSDLInputManagerLite::isKeyDown(SDL_Scancode key) {
    if(m_pvKeyStates == NULL)
        return false;

    if(m_pvKeyStates[key] == 1)
        return true;
    else
        return false;
}

bool CSDLInputManagerLite::isKeyUp(SDL_Scancode key) {
    if(m_pvKeyStates == NULL)
        return false;

    if(m_pvKeyStates[key] == 0)
        return true;
    else
        return false;
}

bool  CSDLInputManagerLite::isExit() {
    return m_bExit;
}
