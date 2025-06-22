/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * eye_object.cc
 */

#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>

#include "eye_object.hpp"
#include "parameter.hpp"

extern std::atomic<bool> running;

void 
EyeObject::Init(WINDOW* win)
{
	m_win = win;
	m_width = 40; 
	m_height = 20; 
	m_pShades = " .:-=+*#%@";
	m_angle = 0.0f;
	m_radius = 0.8f;
}

void 
EyeObject::DrawEye(float angleX, float angleY)
{
    werase(m_win);
    box(m_win, 0, 0);

    for (int y = 0; y < m_height; y++) 
    {
        float v = (float)y / m_height * 2.0f - 1.0f;

        for (int x = 0; x < m_width; x++) 
        {
            float u = (float)x / m_width * 2.0f - 1.0f;
            float z2 = m_radius * m_radius - u * u - v * v;

            if (z2 < 0) 
            {
                mvwaddch(m_win, y + 1, x + 1, ' ');
                continue;
            }

            float z = sqrt(z2);
            float nx = u, ny = v, nz = z;
            float lightX = sin(angleX), lightY = sin(angleY), lightZ = -1.0f;
            float dot = nx * lightX + ny * lightY + nz * lightZ;
            int shadeIndex = std::clamp((int)((dot + 1.0f) * 5), 0, 9);
            mvwaddch(m_win, y + 1, x + 1, m_pShades[shadeIndex]);
        }
    }

    wrefresh(m_win);
}

void
EyeObject::DisplayEye(void)
{
    float angle = 0.0f;
    
    while (running) 
    {
        DrawEye(angle, angle * 0.5f);
        angle += 0.1f;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}