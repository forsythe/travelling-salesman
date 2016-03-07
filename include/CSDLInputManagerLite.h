#ifndef CSDLINPUTMANAGERLITE_H
#define CSDLINPUTMANAGERLITE_H

class CSDLInputManagerLite {
private:
    static CSDLInputManagerLite* m_pInstance;
    CSDLInputManagerLite();
    ~CSDLInputManagerLite();
    SDL_Event  m_previousEvent;
    SDL_Event  m_currentEvent;

    void onKeyDown();
    void onKeyUp();
    const Uint8 * m_pvKeyStates;
    int m_iNumKeys;
    bool m_bExit;

protected:

public:
    static CSDLInputManagerLite* getInstance();
    void update();
    bool isKeyDown(SDL_Scancode);
    bool isKeyUp(SDL_Scancode);
    bool isExit();
};

#endif // CSDLINPUTMANAGERLITE_H
