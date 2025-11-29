#include <windows.h>
#include <cmath>
#include <string>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Game {
public:
    Game() : ballX(400), ballY(300), ballSpeedX(4), ballSpeedY(4), paddleX(350), paddleY(550), gameOver(false), countdown(3), countdownTime(GetTickCount()), leftPressed(false), rightPressed(false), score(0) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                bricks[i][j] = true;
            }
        }
        ballBrush = CreateSolidBrush(RGB(255, 0, 0));
        paddleBrush = CreateSolidBrush(RGB(0, 0, 255));
        brickBrush = CreateSolidBrush(RGB(0, 255, 0));
    }
    
    ~Game() {
        DeleteObject(ballBrush);
        DeleteObject(paddleBrush);
        DeleteObject(brickBrush);
    }
    
    void update() {
        if (countdown > 0) {
            if (GetTickCount() - countdownTime > 1000) {
                countdown--;
                countdownTime = GetTickCount();
            }
            return;
        }
        if (gameOver) return;
        
        if (leftPressed) {
            paddleX -= 10;
            if (paddleX < 0) paddleX = 0;
        }
        if (rightPressed) {
            paddleX += 10;
            if (paddleX > 700) paddleX = 700;
        }
        
        ballX += ballSpeedX;
        ballY += ballSpeedY;
        if (ballX <= 0 || ballX >= 800) ballSpeedX = -ballSpeedX;
        if (ballY <= 0) ballSpeedY = -ballSpeedY;
        if (ballY >= 600) gameOver = true;
        if (ballY >= paddleY - 10 && ballY <= paddleY + 10 && ballX >= paddleX && ballX <= paddleX + 100) {
            ballSpeedY = -abs(ballSpeedY);
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (bricks[i][j]) {
                    int brickX = j * 80;
                    int brickY = i * 30 + 50;
                    if (ballX >= brickX && ballX <= brickX + 80 && ballY >= brickY && ballY <= brickY + 30) {
                        bricks[i][j] = false;
                        ballSpeedY = -ballSpeedY;
                        score += 10;
                    }
                }
            }
        }
    }
    
    void setKeyState(int key, bool pressed) {
        if (key == VK_LEFT) leftPressed = pressed;
        if (key == VK_RIGHT) rightPressed = pressed;
    }
    
    void draw(HDC hdc) {
        HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
        RECT rect = {0, 0, 800, 600};
        FillRect(hdc, &rect, bgBrush);
        DeleteObject(bgBrush);
        
        if (countdown > 0) {
            std::string countdownText = std::to_string(countdown);
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkColor(hdc, RGB(0, 0, 0));
            TextOutA(hdc, 390, 290, countdownText.c_str(), countdownText.length());
            return;
        }
        
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, ballBrush);
        Ellipse(hdc, ballX - 10, ballY - 10, ballX + 10, ballY + 10);
        
        SelectObject(hdc, paddleBrush);
        Rectangle(hdc, paddleX, paddleY, paddleX + 100, paddleY + 10);
        
        SelectObject(hdc, brickBrush);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (bricks[i][j]) {
                    Rectangle(hdc, j * 80, i * 30 + 50, j * 80 + 80, i * 30 + 80);
                }
            }
        }
        
        SelectObject(hdc, oldBrush);
        std::string scoreText = "Score: " + std::to_string(score);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 10, 10, scoreText.c_str(), scoreText.length());
        
        if (gameOver) {
            TextOutA(hdc, 350, 300, "Game Over", 9);
        }
    }

private:
    int ballX, ballY;
    int ballSpeedX, ballSpeedY;
    int paddleX, paddleY;
    bool bricks[5][10];
    bool gameOver;
    int countdown;
    DWORD countdownTime;
    bool leftPressed;
    bool rightPressed;
    int score;
    HBRUSH ballBrush;
    HBRUSH paddleBrush;
    HBRUSH brickBrush;
};

Game game;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, (LPCSTR)"Breakout", NULL };
    RegisterClassEx(&wc);
    
    HWND hwnd = CreateWindow((LPCSTR)"Breakout", (LPCSTR)"Breakout", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    
    DWORD lastTime = GetTickCount();
    
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            DWORD currentTime = GetTickCount();
            if (currentTime - lastTime >= 16) { // 60 FPS
                game.update();
                InvalidateRect(hwnd, NULL, FALSE);
                UpdateWindow(hwnd);
                lastTime = currentTime;
            }
        }
    }
    
    UnregisterClass((LPCSTR)"Breakout", wc.hInstance);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            game.setKeyState(wParam, true);
            break;
        case WM_KEYUP:
            game.setKeyState(wParam, false);
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            game.draw(hdc);
            EndPaint(hwnd, &ps);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
