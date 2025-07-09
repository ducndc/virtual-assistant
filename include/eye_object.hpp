/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * eye_object.hpp
 */

#ifndef EYE_OBJECT_H
#define EYE_OBJECT_H

#include <ncurses.h>
#include <atomic> 
#include <algorithm>

class EyeObject {
private:
	int m_width; 
	int m_height;  

    WINDOW* m_win;

public:
	void Init(WINDOW* win);

	void DisplayEye(void);
};

#endif /* END EYE_OBJECT_H */